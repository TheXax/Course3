#include <Windows.h> 
#include <iostream> 

DWORD WINAPI threadProc(LPVOID); //функция threadProc, которая будет выполняться в созданных потоках. LPVOID — это указатель на любые данные, которые могут быть переданы в функцию


int main()
{
    HANDLE hThread;//дескриптор потока
    DWORD dwThreadId;//id потока
    for (int Count = 0; Count < 1000000; Count++)
    {
        hThread = CreateThread( NULL, 0, threadProc, NULL, CREATE_SUSPENDED, &dwThreadId); //CREATE_SUSPENDED - поток создаётся в приостановленном состоянии
        if (hThread == INVALID_HANDLE_VALUE || hThread == NULL) {
            printf("CreateThread failed (error %d) after %d threads\n",
                GetLastError(), Count);
            break;
        }
        ResumeThread(hThread);//используется для запуска приостановленного потока
        CloseHandle(hThread);//После запуска потока дескриптор закрывается с помощью CloseHandle, чтобы освободить ресурсы
        if (Count % 1000 == 0)
            printf("%d\n", Count);
    }
    printf("Thread Main exited\n");
    return 0;
}

DWORD WINAPI threadProc(LPVOID args)
{
    Sleep(600000);
    return 0;
}