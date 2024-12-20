#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    PROCESS_INFORMATION pi1, pi2;
    DWORD PID = GetCurrentProcessId();
    LPCWSTR an1 = L"C:\\Лабы\\Операционные системы\\Лабы\\Лаба6\\lab6\\x64\\Debug\\OS06_03A.exe";
    LPCWSTR an2 = L"C:\\Лабы\\Операционные системы\\Лабы\\Лаба6\\lab6\\x64\\Debug\\OS06_03B.exe";
    HANDLE hm = CreateMutex(NULL, false, L"smwMutex"); //false - мьютекс не должен быть захвачен сразу после создания.
    {
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
        {
            cout << "--Process OS06_03A created\n";
        }
        else
        {
            cout << "--Process OS06_03A not created\n";
        }
    }
    {
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
        {
            cout << "--Process OS06_03B created\n";
        }
        else
        {
            cout << "--Process OS06_03B not created\n";
        }

        for (int i = 1; i <= 90; i++)
        {
            if (i == 30)
            {
                WaitForSingleObject(hm, INFINITE);
            }
            if (i == 60)
            {
                ReleaseMutex(hm);
            }
            cout << "PID = " << PID << ", Main Thread: " << i << endl;
            Sleep(100);

        }

        WaitForSingleObject(pi1.hProcess, INFINITE);
        WaitForSingleObject(pi2.hProcess, INFINITE);
        CloseHandle(hm);
        CloseHandle(pi1.hProcess);
        CloseHandle(pi2.hProcess);

        return 0;
    }
}