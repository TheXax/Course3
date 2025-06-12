#include <windows.h>
#include "ServiceUtils.h"

SERVICE_STATUS serviceStatus = {};
//Необходим для регистрации обработчика сигналов и отправки статуса сервиса в SCM
SERVICE_STATUS_HANDLE statusHandle; //дескриптор используется для взаимодействия с SCM.

bool running = true;
bool paused = false;

//файл для установки путей по умолчанию
char* configPath = "C:\\Лабы\\СП\Лаба5\\lab5_last\\DemoService\\config.ini";

// Обработчик сигналов сервиса
void WINAPI ServiceCtrlHandler(DWORD ctrlCode) {
    switch (ctrlCode) {
    case SERVICE_CONTROL_STOP: //сигнал остановки
        LogMessage("Received STOP signal.");
        serviceStatus.dwCurrentState = SERVICE_STOPPED; 
        SetServiceStatus(statusHandle, &serviceStatus);
        running = false;
        break;

    case SERVICE_CONTROL_PAUSE: //сигнал паузы
        LogMessage("Received PAUSE signal.");
        paused = true;
        serviceStatus.dwCurrentState = SERVICE_PAUSED;
        SetServiceStatus(statusHandle, &serviceStatus);
        break;

    case SERVICE_CONTROL_CONTINUE: //сигнал возобновления
        LogMessage("Received CONTINUE signal.");
        paused = false;
        serviceStatus.dwCurrentState = SERVICE_RUNNING;
        SetServiceStatus(statusHandle, &serviceStatus);
        break;

    case SERVICE_CONTROL_PARAMCHANGE: //сигнал перечитывания конфигурации
        LogMessage("Received PARAMCHANGE signal. Reloading configuration...");
        if (LoadConfig(configPath)) {
            LogMessage("Configuration reloaded successfully.");
        }
        else {
            LogMessage("Failed to reload configuration.");
        }
        break;

    case 138: //пользовательский сигнал
        LogMessage("Hello, this is a test code from DemoService!");
        break;

    default:
        break;
    }
}

// Основная функция сервиса
void WINAPI ServiceMain(DWORD argc, LPSTR* argv) { //WINAPI задаёт соглашение о вызовах

    statusHandle = RegisterServiceCtrlHandler("DemoService", ServiceCtrlHandler); //регистрация обратки сигналов
    if (!statusHandle) return;

    serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS; //сервис работает как отдельный процесс
    serviceStatus.dwCurrentState = SERVICE_START_PENDING; //установка начального состояния сервиса
    serviceStatus.dwControlsAccepted = 0; //сервис не принимает никакие управляющие сигналы
    serviceStatus.dwServiceSpecificExitCode = 0;
    serviceStatus.dwCheckPoint = 1; //указываем, что сервис в процессе инициализации
    serviceStatus.dwWaitHint = 10000; //максимальное время ожидания следующего обновления статуса 10 сек

    SetServiceStatus(statusHandle, &serviceStatus); //изменение статуса сервиса

    //передан ли путь к конфигурационному файлу через аргументы командной строки
    if (argc > 1) {
        configPath = argv[1];
    }

    //чтения конфигурационного файла по пути
    if (!LoadConfig(configPath)) {
        LogMessage("Error while loading configuration.");
        serviceStatus.dwCurrentState = SERVICE_STOPPED;
        SetServiceStatus(statusHandle, &serviceStatus); //обновляем статус сервиса в SCM
        return;
    }

    LogMessage("Success! DemoService initialized."); //если конфигурация успешно загружена


    serviceStatus.dwCurrentState = SERVICE_RUNNING; //установка состояния сервиса (полностью инициализирован и работает)
    serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE |
        SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PARAMCHANGE; //указывает, какие сигнал готов принимать

    serviceStatus.dwWin32ExitCode = NO_ERROR; //код выхода сервиса (ошибок нет)
    serviceStatus.dwCheckPoint = 0;
    serviceStatus.dwWaitHint = 0; //т.к. сервис не требует ожидания, ведь уже работает

    SetServiceStatus(statusHandle, &serviceStatus); //обновление статуса, сообщая о сотоянии и принятии сигналов

    while (running) {
        if (!paused) { //приостановлен ли сервис
            CopyFilesOnce(); //копирование файлов
        }
        Sleep(intervalMinutes * 60 * 1000); //приостановка выполнения потока на 60 мин
    }

    serviceStatus.dwControlsAccepted = 0; //предотвращение обработки сигналов
    serviceStatus.dwCurrentState = SERVICE_STOPPED; //состояние стопа
    SetServiceStatus(statusHandle, &serviceStatus); //обновление состояния

    LogMessage("DemoService stopped.");
    logFile.close(); //закрытие лог-файла
}

int main() {
    SERVICE_TABLE_ENTRY ServiceTable[] = { //массив, содержащий инфу о сервисах
        { "DemoService", ServiceMain },
        { NULL, NULL }
    };

    StartServiceCtrlDispatcher(ServiceTable);

    return 0;
}
