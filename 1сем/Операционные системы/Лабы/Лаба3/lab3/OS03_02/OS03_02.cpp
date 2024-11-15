#include <iostream>
#include <Windows.h>
#include <process.h>

int main()
{
    LPCWSTR an = L"..\\X64\\Debug\\OS03_02_1.exe";
    LPCWSTR an1 = L"..\\X64\\Debug\\OS03_02_2.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION pi, pi1;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (CreateProcessW(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) std::cout << "---Proc 1 created\n";
    else std::cout << "---Proc 1 not created\n";
    if (CreateProcessW(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1)) std::cout << "---Proc 2 created\n";
    else std::cout << "---Proc 2 not created\n";

    for (int i = 0; i < 100; i++) {
        Sleep(1000);
        std::cout << "OS03_02: " << _getpid() << "\n";
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    WaitForSingleObject(pi1.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi1.hProcess);

    return 0;
}
