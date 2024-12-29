#define _CRT_SECURE_NO_WARNINGS //отключает предупреждение о небезопасных функциях
#include <Windows.h>
#include <iostream>
#include <locale>
#include <codecvt>
#include <sstream>
using namespace std;

#define FILE_PATH L"C:/Лабы/Операционные системы/Лабы/Лаба9/lab9/OS09_01.txt"
#define READ_BYTES 500 //максимальное количество байт, которое будет прочитано из файла

BOOL printFileText(LPWSTR fileName)//открывает файл и выводит содержимое
{
    try
    {
        wcout << L"\n\n\t------[RESULT]------\n";
        HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); //открытие файла
        if (hf == INVALID_HANDLE_VALUE) throw "[ERROR] Create or open file failed."; //если не открылся
        DWORD n = NULL;
        char buf[1024];

        ZeroMemory(buf, sizeof(buf));
        BOOL b = ReadFile(hf, &buf, READ_BYTES, &n, NULL); //читает данные из файла
        if (!b) throw "[ERROR] Read file failed";

        string str(buf, n);  //преобразует прочитанные байты в строку
        wstring_convert<codecvt_utf8<wchar_t>> conv; //преобразует в wstring
        wstring wstr = conv.from_bytes(str);

        //вывод содержимого и закрытие дескриптора
        wcout << wstr << endl;
        CloseHandle(hf);
        return true;
    }
    catch (const char* em)
    {
        wcout << em << endl;
        return false;
    }
}

//удаление строк
BOOL delRowFileTxt(LPWSTR fileName, DWORD row)
{
    char filepath[260]; //преобразование filepath в char массив???? что это и зачем
    wcstombs(filepath, fileName, 260);
    wcout << L"\n======  Удаление строки: " << row << L"\n\n";

    try
    {
        //открытие файла для чтения
        HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hf == INVALID_HANDLE_VALUE)
        {
            CloseHandle(hf);
            throw "[ERROR] Create or open file failed";
        }

        //чтение в буфер
        DWORD n = NULL;
        char buf[1024];
        BOOL b;

        ZeroMemory(buf, sizeof(buf));
        b = ReadFile(hf, &buf, sizeof(buf), &n, NULL);
        if (!b)
        {
            CloseHandle(hf);
            throw "[ERROR] Read file unsuccessful";
        }

        //Преобразует данные в wstring
        wstring_convert<codecvt_utf8<wchar_t>> conv;
        string str(buf, n);
        wstring wstr = conv.from_bytes(str);

        //вывод и закрытие файла
        wcout << L"\t\tДО:\n" << wstr << endl;
        CloseHandle(hf);

        HANDLE hAppend = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hAppend == INVALID_HANDLE_VALUE)
            throw "[ERROR] Unable to open file for writing.";

        //Переводит wstring в wstringstream для построчного чтения
        wstringstream stream(wstr);
        //переменные для обработки строк
        wstring line;
        wstring editedWstr;
        DWORD currentRow = 1;

        //построчное чтение файла
        while (getline(stream, line))
        {
            if (currentRow != row)
            {
                editedWstr += line + L"\n"; //запись в editedWstr, если номера не совпадают с row 
            }
            currentRow++;
        }

        //существует ли строка для удаления
        if (currentRow <= row)
        {
            CloseHandle(hAppend);
            throw "[ERROR] Can't find this row.\n";
        }

        string editedStr = conv.to_bytes(editedWstr); //преобразование строки в string
        DWORD written;
        b = WriteFile(hAppend, editedStr.c_str(), (DWORD)editedStr.size(), &written, NULL); //записывает её в файл
        if (!b)
        {
            CloseHandle(hAppend);
            throw "[ERROR] Write file unsuccessful";
        }

        //результат после удаления
        wcout << L"\n\t\tПОСЛЕ:\n" << editedWstr << endl;
        CloseHandle(hAppend);
        wcout << L"\n==========================================\n";
        return true;
    }
    catch (const char* em)
    {
        wcout << em << L" \n";
        wcout << L"==========================================\n";
        return false;
    }
}

int main()
    //установка кодировки
{
    //установка кодировки
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "ru");

    LPWSTR file = (LPWSTR)FILE_PATH; //риводит FILE_PATH к типу LPWSTR??? зачем

    //указание какие строки удалить
    delRowFileTxt(file, 1);
    delRowFileTxt(file, 3);
    delRowFileTxt(file, 8);
    delRowFileTxt(file, 10);

    printFileText(file); //вывод содержимого

    return 0;
}
