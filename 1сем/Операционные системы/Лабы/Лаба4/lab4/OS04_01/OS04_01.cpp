#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 10000; i++)
    {
        cout << i << " " << "PID: " << pid << " " << " TID: " << tid << " " << endl;
        Sleep(1000);
    }
}