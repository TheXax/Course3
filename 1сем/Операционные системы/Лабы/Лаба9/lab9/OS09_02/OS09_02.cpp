#define _CRT_SECURE_NO_WARNINGS //��������� �������������� � ������������ ��������
#include <Windows.h>
#include <iostream>
#include <locale>
#include <codecvt>
#include <sstream>
using namespace std;

#define FILE_PATH L"C:/����/������������ �������/����/����9/lab9/OS09_01.txt"
#define READ_BYTES 500 //������������ ���������� ����, ������� ����� ��������� �� �����

BOOL printFileText(LPWSTR fileName)//��������� ���� � ������� ����������
{
    try
    {
        wcout << L"\n\n\t------[RESULT]------\n";
        HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); //�������� �����
        if (hf == INVALID_HANDLE_VALUE) throw "[ERROR] Create or open file failed."; //���� �� ��������
        DWORD n = NULL;
        char buf[1024];

        ZeroMemory(buf, sizeof(buf));
        BOOL b = ReadFile(hf, &buf, READ_BYTES, &n, NULL); //������ ������ �� �����
        if (!b) throw "[ERROR] Read file failed";

        string str(buf, n);  //����������� ����������� ����� � ������
        wstring_convert<codecvt_utf8<wchar_t>> conv; //����������� � wstring
        wstring wstr = conv.from_bytes(str);

        //����� ����������� � �������� �����������
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

//�������� �����
BOOL delRowFileTxt(LPWSTR fileName, DWORD row)
{
    char filepath[260]; //�������������� filepath � char ������???? ��� ��� � �����
    wcstombs(filepath, fileName, 260);
    wcout << L"\n======  �������� ������: " << row << L"\n\n";

    try
    {
        //�������� ����� ��� ������
        HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hf == INVALID_HANDLE_VALUE)
        {
            CloseHandle(hf);
            throw "[ERROR] Create or open file failed";
        }

        //������ � �����
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

        //����������� ������ � wstring
        wstring_convert<codecvt_utf8<wchar_t>> conv;
        string str(buf, n);
        wstring wstr = conv.from_bytes(str);

        //����� � �������� �����
        wcout << L"\t\t��:\n" << wstr << endl;
        CloseHandle(hf);

        HANDLE hAppend = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hAppend == INVALID_HANDLE_VALUE)
            throw "[ERROR] Unable to open file for writing.";

        //��������� wstring � wstringstream ��� ����������� ������
        wstringstream stream(wstr);
        //���������� ��� ��������� �����
        wstring line;
        wstring editedWstr;
        DWORD currentRow = 1;

        //���������� ������ �����
        while (getline(stream, line))
        {
            if (currentRow != row)
            {
                editedWstr += line + L"\n"; //������ � editedWstr, ���� ������ �� ��������� � row 
            }
            currentRow++;
        }

        //���������� �� ������ ��� ��������
        if (currentRow <= row)
        {
            CloseHandle(hAppend);
            throw "[ERROR] Can't find this row.\n";
        }

        string editedStr = conv.to_bytes(editedWstr); //�������������� ������ � string
        DWORD written;
        b = WriteFile(hAppend, editedStr.c_str(), (DWORD)editedStr.size(), &written, NULL); //���������� � � ����
        if (!b)
        {
            CloseHandle(hAppend);
            throw "[ERROR] Write file unsuccessful";
        }

        //��������� ����� ��������
        wcout << L"\n\t\t�����:\n" << editedWstr << endl;
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
    //��������� ���������
{
    //��������� ���������
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "ru");

    LPWSTR file = (LPWSTR)FILE_PATH; //������� FILE_PATH � ���� LPWSTR??? �����

    //�������� ����� ������ �������
    delRowFileTxt(file, 1);
    delRowFileTxt(file, 3);
    delRowFileTxt(file, 8);
    delRowFileTxt(file, 10);

    printFileText(file); //����� �����������

    return 0;
}
