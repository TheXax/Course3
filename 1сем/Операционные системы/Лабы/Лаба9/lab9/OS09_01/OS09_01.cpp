#include <Windows.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <codecvt>
#include <locale>
using namespace std;

#define FILE_PATH L"C:/����/������������ �������/����/����9/lab9/OS09_01.txt"

WIN32_FIND_DATA fileData;//��� �������� ���������� � �����

wstring getFileName(wchar_t* filePath) //��������� ��� ����� �� ���� � ����
{
    wstring ws(filePath); //����������� filePath � ������ wstring
    const size_t last_slash_idx = ws.find_last_of(L"\\/"); //������� ��������� ������ / ��� \, ����� �������� ��� ����� �� ����
    if (wstring::npos != last_slash_idx)
        ws.erase(0, last_slash_idx + 1); //������� ��� ������� �� � ������� ��������� ���� � ���������� ������ ��� �����
    return ws;
}

LPCWSTR getFileType(HANDLE file) //����������� ���� �����
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

BOOL printFileInfo(LPWSTR path) //��������� ���� � ������� ����
{
    HANDLE file = CreateFile( //�������� ��� �������� ����� ��� ������
        path,
        GENERIC_READ,
        NULL,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (file == INVALID_HANDLE_VALUE) { //���� ���� �� ������
        wcerr << L"�� ������� ������� ����: " << path << endl;
        return false;
    }

    SYSTEMTIME sysTime; //��������� ���������� � �����
    BY_HANDLE_FILE_INFORMATION fi; //���������� ��� ��������
    BOOL fResult = GetFileInformationByHandle(file, &fi); //GetFileInformationByHandle ��������� ��������� fi ����������� � �����
    if (fResult) //���� ���������� ��������
    {
        wcout << L"File name:\t" << getFileName(path);
        wcout << L"\nFile type:\t " << (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? L"Directory" : L"File"); //�������� �� ���� ����������� ��� ������� ������
        wcout << L"\nFile size:\t" << fi.nFileSizeLow << L" bytes";

        //������������ ����� �������� ����� � �������� ������ � ������� ���
        FileTimeToSystemTime(&fi.ftCreationTime, &sysTime);
        wcout << L"\nCreate time:\t" << setfill(L'0') << setw(2) << sysTime.wHour + 3 << L':' << setw(2) << sysTime.wMinute << L':' << setw(2) << sysTime.wSecond;
        wcout << L" " << setw(4) << sysTime.wYear << L'-' << setw(2) << sysTime.wMonth << L'-' << setw(2) << sysTime.wDay;

        //������� ����� ���������� ��������� �����. � ����� ��������� ���������� �����.
        FileTimeToSystemTime(&fi.ftLastWriteTime, &sysTime);
        wcout << L"\nUpdate time:\t" << setfill(L'0') << setw(2) << sysTime.wHour + 3 << L':' << setw(2) << sysTime.wMinute << L':' << setw(2) << sysTime.wSecond;
        wcout << L" " << setw(4) << sysTime.wYear << L'-' << setw(2) << sysTime.wMonth << L'-' << setw(2) << sysTime.wDay;
    }
    CloseHandle(file);
    return true;
}

BOOL printFileTxt(LPWSTR path)
{
    //��������� ��������� ���� � ������� ��� ����������
    wifstream file(path, ios::binary); //wifstream ��� ������ � �������� ��������
    file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>)); //������������� ��������� UTF-8

    if (!file.is_open()) { //������ �� ����
        wcerr << L"�� ������� ������� ���� ��� ������: " << path << endl;
        return false;
    }

    //������ ��������� � ������� ����
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
    //��������� ��� �������� �����
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "ru");

    LPWSTR path = (LPWSTR)FILE_PATH; //�������� FILE_PATH � ���� LPWSTR

    printFileInfo(path); //����� ���� � �����
    printFileTxt(path); //����������

    return 0;
}
