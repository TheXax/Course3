#include <Windows.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <codecvt>
#include <locale>
using namespace std;

#define FILE_PATH L"C:/Лабы/Операционные системы/Лабы/Лаба9/lab9/OS09_01.txt"

WIN32_FIND_DATA fileData;//для хранения информации о файле

wstring getFileName(wchar_t* filePath) //извлекает имя файла из пути к нему
{
    wstring ws(filePath); //Преобразует filePath в строку wstring
    const size_t last_slash_idx = ws.find_last_of(L"\\/"); //Находит последний символ / или \, чтобы отделить имя файла от пути
    if (wstring::npos != last_slash_idx)
        ws.erase(0, last_slash_idx + 1); //Удаляет все символы до и включая последний слэш и возвращает только имя файла
    return ws;
}

LPCWSTR getFileType(HANDLE file) //определение типа файла
{
    switch (GetFileType(file))
    {
    case FILE_TYPE_UNKNOWN:
        return L"FILE_TYPE_UNKNOWN";
    case FILE_TYPE_DISK:
        return L"FILE_TYPE_DISK";
    case FILE_TYPE_CHAR:
        return L"FILE_TYPE_CHAR";
    case FILE_TYPE_PIPE:
        return L"FILE_TYPE_PIPE";
    case FILE_TYPE_REMOTE:
        return L"FILE_TYPE_REMOTE";
    default:
        return L"[ERROR]: WRITE FILE TYPE";
    }
}

BOOL printFileInfo(LPWSTR path) //открывает файл и выводит инфу
{
    HANDLE file = CreateFile( //открытие или создание файла для чтения
        path,
        GENERIC_READ,
        NULL,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (file == INVALID_HANDLE_VALUE) { //если файл не открыт
        wcerr << L"Не удалось открыть файл: " << path << endl;
        return false;
    }

    SYSTEMTIME sysTime; //получение информации о файле
    BY_HANDLE_FILE_INFORMATION fi; //переменная для хранения
    BOOL fResult = GetFileInformationByHandle(file, &fi); //GetFileInformationByHandle заполняет структуру fi информацией о файле
    if (fResult) //если информация получена
    {
        wcout << L"File name:\t" << getFileName(path);
        wcout << L"\nFile type:\t " << (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? L"Directory" : L"File"); //является ли файл директорией или обычным файлом
        wcout << L"\nFile size:\t" << fi.nFileSizeLow << L" bytes";

        //Конвертирует время создания файла в читаемый формат и выводит его
        FileTimeToSystemTime(&fi.ftCreationTime, &sysTime);
        wcout << L"\nCreate time:\t" << setfill(L'0') << setw(2) << sysTime.wHour + 3 << L':' << setw(2) << sysTime.wMinute << L':' << setw(2) << sysTime.wSecond;
        wcout << L" " << setw(4) << sysTime.wYear << L'-' << setw(2) << sysTime.wMonth << L'-' << setw(2) << sysTime.wDay;

        //Выводит время последнего изменения файла. В конце закрывает дескриптор файла.
        FileTimeToSystemTime(&fi.ftLastWriteTime, &sysTime);
        wcout << L"\nUpdate time:\t" << setfill(L'0') << setw(2) << sysTime.wHour + 3 << L':' << setw(2) << sysTime.wMinute << L':' << setw(2) << sysTime.wSecond;
        wcout << L" " << setw(4) << sysTime.wYear << L'-' << setw(2) << sysTime.wMonth << L'-' << setw(2) << sysTime.wDay;
    }
    CloseHandle(file);
    return true;
}

BOOL printFileTxt(LPWSTR path)
{
    //Открывает текстовый файл и выводит его содержимое
    wifstream file(path, ios::binary); //wifstream для работы с широкими строками
    file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>)); //устанавливает кодировку UTF-8

    if (!file.is_open()) { //открыт ли файл
        wcerr << L"Не удалось открыть файл для чтения: " << path << endl;
        return false;
    }

    //читает построчно и выводит инфу
    wcout << L"\n\n\tPrint file:\n";
    wstring line;
    while (getline(file, line)) {
        wcout << line << endl;
    }
    file.close();
    return true;
}

int main()
{
    //кодировка для русского языка
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "ru");

    LPWSTR path = (LPWSTR)FILE_PATH; //приводит FILE_PATH к типу LPWSTR

    printFileInfo(path); //вывод инфы о файле
    printFileTxt(path); //содержимое

    return 0;
}
