#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <locale>
#include <codecvt>
#include <sstream>

#define FILE_PATH L"C:/����/������������ �������/����/����9/lab9/OS09_01.txt"
#define READ_BYTES 1000
using namespace std;


BOOL printFileText(LPWSTR fileName)
{
    try
    {
        wcout << L"\n\n\t---------RESULT----------\n";
        HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hf == INVALID_HANDLE_VALUE) throw "[ERROR] Create or open file failed.";
        DWORD n = NULL;
        char buf[1024];

        ZeroMemory(buf, sizeof(buf));
        BOOL b = ReadFile(hf, &buf, READ_BYTES, &n, NULL); //������ ������ �� �����
        if (!b) throw "[ERROR] Read file failed";

        string str(buf, n); //����������� ����� � ������
        wstring_convert<codecvt_utf8<wchar_t>> conv; //����������� � wstring
        wstring wstr = conv.from_bytes(str);

        //����� �����������
        wcout << wstr << endl;
        CloseHandle(hf);
        return true;
    }
    catch (const char* em)
    {
        wcout << L"[ERROR] " << em << endl;
        return false;
    }
}


//������� ������ � ��������� ���
BOOL insRowFileTxt(LPWSTR fileName, LPWSTR str, DWORD row)
{
    try
    {
        wcout << L"\n----------Insert row: " << row << L"\n\n";
        HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hf == INVALID_HANDLE_VALUE)
        {
            CloseHandle(hf);
            throw "[ERROR] Create or open file failed";
        }

        //������ ������ � ����
        DWORD n = NULL;
        char buf[1024];
        BOOL b;

        ZeroMemory(buf, sizeof(buf));
        b = ReadFile(hf, &buf, sizeof(buf) - 1, &n, NULL);  // ������ � ������������
        if (!b)
        {
            CloseHandle(hf);
            throw "[ERROR] Read file unsuccessful";
        }

        buf[n] = '\0'; // ��������� ������
        wstring_convert<codecvt_utf8<wchar_t>> conv; //������������� ������ � wstring
        string strBuf(buf);
        wstring wstrBuf = conv.from_bytes(strBuf);

        //������ �� ���������
        wcout << L"\t\tBEFORE:\n" << wstrBuf << endl;
        CloseHandle(hf);

        //�������� ��� ������
        HANDLE hAppend = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hAppend == INVALID_HANDLE_VALUE)
            throw "[ERROR] Unable to open file for writing.";

        wstringstream stream(wstrBuf); //��������� wstring � wstringstream ��� ����������� ������.
        wstring line;
        wstring editedBuf;
        DWORD currentRow = 1;

        //���������� ������
        while (getline(stream, line))
        {
            if (currentRow == row) //���� ����� ������� ������ ��������� � row, ��������� ������
            {
                editedBuf += str;
                editedBuf += L"\r\n";
            }
            editedBuf += line + L"\r\n";
            currentRow++;
        }

        if (currentRow <= row) //���� ��������� ������ ������, ��� ����� ���������� �����, ��������� ����� ������ � �����
        {
            editedBuf += str;
            editedBuf += L"\r\n";
        }

        string editedStr = conv.to_bytes(editedBuf); //�������������� ������ � string
        DWORD written;
        //������ ������ � ����
        b = WriteFile(hAppend, editedStr.c_str(), (DWORD)editedStr.size(), &written, NULL);
        if (!b)
        {
            CloseHandle(hAppend);
            throw "[ERROR] Write file unsuccessful";
        }

        //������ ����� ���������
        wcout << L"\t\tAFTER:\n" << editedBuf << endl;
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
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "ru");

    LPWSTR file = (LPWSTR)FILE_PATH;

    wchar_t strToIns[] = L"1. ����� ������";

    insRowFileTxt(file, strToIns, 1);
    insRowFileTxt(file, strToIns, -1);
    insRowFileTxt(file, strToIns, 5);
    insRowFileTxt(file, strToIns, 7);

    printFileText(file);
}
