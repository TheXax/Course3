#include <Windows.h> 
#include <iostream> 

DWORD WINAPI threadProc(LPVOID); //������� threadProc, ������� ����� ����������� � ��������� �������. LPVOID � ��� ��������� �� ����� ������, ������� ����� ���� �������� � �������


int main()
{
    HANDLE hThread;//���������� ������
    DWORD dwThreadId;//id ������
    for (int Count = 0; Count < 1000000; Count++)
    {
        hThread = CreateThread( NULL, 0, threadProc, NULL, CREATE_SUSPENDED, &dwThreadId); //CREATE_SUSPENDED - ����� �������� � ���������������� ���������
        if (hThread == INVALID_HANDLE_VALUE || hThread == NULL) {
            printf("CreateThread failed (error %d) after %d threads\n",
                GetLastError(), Count);
            break;
        }
        ResumeThread(hThread);//������������ ��� ������� ����������������� ������
        CloseHandle(hThread);//����� ������� ������ ���������� ����������� � ������� CloseHandle, ����� ���������� �������
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