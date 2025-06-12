#include "ServiceUtils.h"
#include <windows.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;
//ЭТО ДОБАВИЛА -----------
// Значения по умолчанию для логирования
const std::string DEFAULT_SOURCE_DIR = "C:\\projectSP";
const std::string DEFAULT_TARGET_DIR = "C:\\Users\\User\\AppData\\Roaming\\DemoService\\Reserved";
const std::string DEFAULT_LOG_DIR = "C:\\Users\\User\\AppData\\Roaming\\DemoService\\Logs";
const int DEFAULT_INTERVAL_MINUTES = 60;
//------------------------------
//target_dir = C:\\Users\\User\\AppData\\Roaming\\DemoService\\Reserved - из файла


std::string sourceDir, targetDir, logDir; //глобавльные переменные для файлов
int intervalMinutes = 60; //интервал между операциями копирования
std::ofstream logFile;

//принимает константную ссылку на строку s
std::string Trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n"); //находит первый символ, который не является пробелом и т.д.
    size_t end = s.find_last_not_of(" \t\r\n"); //находит последний символ
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1); //если равен первому значению, то возвращает пустую строку, иначе - подстроку от первого до последнего символа
}

//возвращает строку с текущей датой и временем
std::string GetCurrentTimeStr() {
    SYSTEMTIME st; //для хранения времени
    GetLocalTime(&st); //заполняем
    char buf[100];
    sprintf_s(buf, "%04d%02d%02d-%02d%02d%02d",
        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond); //формат строки
    return std::string(buf); //преобразуем в массив
}

bool LoadConfig(const char* configPath) { //принимает путь к конфигурационному файлу
    std::ifstream in(configPath); //для чтения из файла
    bool configLoaded = false;
    bool hasSourceDir = false, hasTargetDir = false, hasLogDir = false, hasInterval = false;
    if (!in) {
        std::cerr << "Failed to open config.ini. Using default values.\n";
        //ЭТО ДОБАВИЛА ------------------
        sourceDir = DEFAULT_SOURCE_DIR;
        targetDir = DEFAULT_TARGET_DIR;
        logDir = DEFAULT_LOG_DIR;
        intervalMinutes = DEFAULT_INTERVAL_MINUTES;
        configLoaded = true; // Устанавливаем как успешно загружено с дефолтами
        //-------------------------------
    }
    else {
    std::string line; //для хранения строк из файла
    while (getline(in, line)) {
            if (line.find("source_dir") != std::string::npos) {
                std::string value = Trim(line.substr(line.find('=') + 1));
                if (!value.empty()) {
                    sourceDir = value;
                    hasSourceDir = true;
                }
            }
            else if (line.find("target_dir") != std::string::npos) {
                std::string value = Trim(line.substr(line.find('=') + 1));
                if (!value.empty()) {
                    targetDir = value;
                    hasTargetDir = true;
                }
            }
            else if (line.find("log_dir") != std::string::npos) {
                std::string value = Trim(line.substr(line.find('=') + 1));
                if (!value.empty()) {
                    logDir = value;
                    hasLogDir = true;
                }
            }
            else if (line.find("interval_minutes") != std::string::npos) {
                std::string value = Trim(line.substr(line.find('=') + 1));
                if (!value.empty()) {
                    try {
                        intervalMinutes = std::stoi(value);
                        hasInterval = true;
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Error parsing interval_minutes: " << e.what() << ". Using default: " << DEFAULT_INTERVAL_MINUTES << std::endl;
                        intervalMinutes = DEFAULT_INTERVAL_MINUTES;
                        hasInterval = true; // Устанавливаем как валидное значение
                    }
                }
            }
        }
        in.close();

        // Подстановка значений по умолчанию, если параметры отсутствуют
        if (!hasSourceDir) {
            sourceDir = DEFAULT_SOURCE_DIR;
            std::cerr << "source_dir not specified in config.ini. Using default: " << DEFAULT_SOURCE_DIR << "\n";
        }
        if (!hasTargetDir) {
            targetDir = DEFAULT_TARGET_DIR;
            std::cerr << "target_dir not specified in config.ini. Using default: " << DEFAULT_TARGET_DIR << "\n";
        }
        if (!hasLogDir) {
            logDir = DEFAULT_LOG_DIR;
            std::cerr << "log_dir not specified in config.ini. Using default: " << DEFAULT_LOG_DIR << "\n";
        }
        if (!hasInterval) {
            intervalMinutes = DEFAULT_INTERVAL_MINUTES;
            std::cerr << "interval_minutes not specified in config.ini. Using default: " << DEFAULT_INTERVAL_MINUTES << "\n";
        }

        configLoaded = true; // Успешно загружено, даже если использовались дефолты
    }
    
    
    /*while (getline(in, line)) { //построчное чтение
        if (line.find("source_dir") != std::string::npos) //есть ли подстрока
            sourceDir = Trim(line.substr(line.find('=') + 1)); //берём данные после =
        else if (line.find("target_dir") != std::string::npos)
            targetDir = Trim(line.substr(line.find('=') + 1));
        else if (line.find("log_dir") != std::string::npos)
            logDir = Trim(line.substr(line.find('=') + 1));
        else if (line.find("interval_minutes") != std::string::npos) {
            try {
                intervalMinutes = std::stoi(Trim(line.substr(line.find('=') + 1)));
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing interval_minutes: " << e.what() << std::endl;
                return false;
            }
        }
    }*/

    if (logDir.empty()) { //является ли пустой строкой
        std::cerr << "log_dir is empty. Using default: " << DEFAULT_LOG_DIR << "\n";
        //ЗАМЕНИЛА---------------------
        //return false;
        logDir = DEFAULT_LOG_DIR;
    }

    try { //попытка создать каталог
        fs::create_directories(fs::path(logDir));
    }
    catch (const std::exception& e) {
        std::cerr << "Error creating log directory: " << e.what() << std::endl;
        return false;
    }

    //формируем путь к лог-файлу
    std::string logPath = logDir + "\\" + GetCurrentTimeStr() + "-service.log";
    if (logFile.is_open()) { //если файл открыт, закрываем, чтобы открыть другой лог-файл
        logFile.close();
    }
    logFile.open(logPath, std::ios::app); //открываем в режиме добавления
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << logPath << std::endl;
        return false;
    }

    //Логирование всех параметров
    LogMessage("Current source directory: " + sourceDir);
    LogMessage("Current target directory: " + targetDir);
    LogMessage("Current log directory: " + logDir);
    LogMessage("Current interval (minutes): " + std::to_string(intervalMinutes));

    return configLoaded;
}

void LogMessage(const std::string& msg) { //запись в лог-файл
    SYSTEMTIME st;
    GetLocalTime(&st);
    char timeBuf[16];
    sprintf_s(timeBuf, "[%02d:%02d:%02d] ", st.wHour, st.wMinute, st.wSecond);
    if (logFile.is_open()) { //запись, если открыт
        logFile << timeBuf << msg << std::endl;
    }
    else {
        std::cerr << "Logging error: " << msg << std::endl;
    }
}

void CopyFilesOnce() { //однократное копирование файлов
    if (!fs::exists(sourceDir)) {
        LogMessage("Error: Source directory does not exist.");
        return;
    }

    if (!fs::exists(targetDir)) { //есть ли каталог для копирования в него
        fs::create_directories(targetDir); //создаётся
        LogMessage("Created directory: " + targetDir);
    }
    else {
        LogMessage("Target directory exists: " + targetDir);
    }

    for (auto& entry : fs::directory_iterator(sourceDir)) { //перебор всех эл-тов в исходном каталоге
        if (entry.is_regular_file()) { //является ли файлом
            try {
                std::string targetPath = targetDir + "\\" + entry.path().filename().string();
                fs::copy_file(entry.path(), targetPath, fs::copy_options::overwrite_existing);
                LogMessage("Copied " + entry.path().filename().string() + " to " + targetPath);
                /*fs::copy_file(entry.path(), targetDir + "\\" + entry.path().filename().string(),
                    fs::copy_options::overwrite_existing); //перезапись файла, если уже существует
                */
            }
            catch (const std::exception& e) {
                LogMessage("Error copying file: " + std::string(e.what()));
            }
        }
    }

    LogMessage("Files copied successfully.");
}

void LogLastError(const char* context) { //записывает в лог последнюю системную ошибку Windows с указанным контекстом
    DWORD errorCode = GetLastError(); //код ошибки
    LPSTR messageBuffer = nullptr;

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        errorCode,
        0,
        (LPSTR)&messageBuffer,
        0,
        nullptr
    );

    if (messageBuffer) {
        std::string fullMessage = std::string(context) + ": " + messageBuffer;
        LogMessage(fullMessage);
        LocalFree(messageBuffer);
    }
    else {
        LogMessage(std::string(context) + ": unknown error");
    }
}
