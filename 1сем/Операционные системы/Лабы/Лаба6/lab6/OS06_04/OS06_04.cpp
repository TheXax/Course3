#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    PROCESS_INFORMATION pi1, pi2;
    DWORD PID = GetCurrentProcessId();
    LPCWSTR an1 = L"C:\\Лабы\\Операционные системы\\Лабы\\Лаба6\\lab6\\x64\\Debug\\OS06_04A.exe";
    LPCWSTR an2 = L"C:\\Лабы\\Операционные системы\\Лабы\\Лаба6\\lab6\\x64\\Debug\\OS06_04B.exe";
    HANDLE hs = CreateSemaphore(NULL, 2, 2, L"smwSem"); //2: Начальное значение счетчика семафора (количество разрешений, доступных сразу); 2: Максимальное значение счетчика семафора(максимальное количество разрешений).
    {
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
        {
            cout << "--Process OS06_04A created\n";
        }
        else
        {
            cout << "--Process OS06_04A not created\n";
        }
    }
    {
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
        {
            cout << "--Process OS06_04B created\n";
        }
        else
        {
            cout << "--Process OS06_04B not created\n";
        }

        LONG prevcount = 0; //для хранения предыдущего значения счетчика семафора
        for (int i = 1; i <= 90; i++)
        {
            if (i == 30)
            {
                WaitForSingleObject(hs, INFINITE);
            }
            if (i == 60)
            {
                ReleaseSemaphore(hs, 1, &prevcount); //Освобождает семафор, увеличивая его счетчик на 1
                cout << "OS06_04: prevcount = " << prevcount << endl;
            }
            cout << "PID = " << PID << ", Main Thread: " << i << endl;
            Sleep(100);
        }

        WaitForSingleObject(pi1.hProcess, INFINITE);
        WaitForSingleObject(pi2.hProcess, INFINITE);
        CloseHandle(hs);
        CloseHandle(pi1.hProcess);
        CloseHandle(pi2.hProcess);

        return 0;
    }
}