#include <iostream>
#include <Windows.h>

using namespace std;
DWORD PID = NULL;
CRITICAL_SECTION cs;

DWORD WINAPI ChildThreadA()
{
	DWORD TID = GetCurrentThreadId();

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs); //вход в критическую секцию
		}
		if (i == 60)
		{
			LeaveCriticalSection(&cs); //выход
		}
		cout << "PID = " << PID << ", Child Thread A: " << "TID = " << TID << ": " << i << endl;
		Sleep(100);

		if (i == 60)
		{
			EnterCriticalSection(&cs);
			LeaveCriticalSection(&cs);
		}
	}
	return 0;
}

DWORD WINAPI ChildThreadB()
{
	DWORD TID = GetCurrentThreadId();

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}
		if (i == 60)
		{
			LeaveCriticalSection(&cs);
		}

		cout << "PID = " << PID << ", Child Thread B: " << "TID = " << TID << ": " << i << endl;
		Sleep(100);

		if (i == 60)
		{
			EnterCriticalSection(&cs);
			LeaveCriticalSection(&cs);
		}
	}

	return 0;
}

int main()
{
	PID = GetCurrentProcessId();
	DWORD TID = GetCurrentThreadId();//id главного потока
	DWORD childIdA = NULL;
	DWORD childIdB = NULL;

	HANDLE hChildA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreadA, NULL, 0, &childIdA);
	HANDLE hChildB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreadB, NULL, 0, &childIdB);

	InitializeCriticalSection(&cs);

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}
		if (i == 60)
		{
			LeaveCriticalSection(&cs);;
		}
		cout << "PID = " << PID << ", Main Thread: " << "TID = " << TID << ": " << i << endl;
		Sleep(100);
		if (i == 60)
		{
			EnterCriticalSection(&cs);
			LeaveCriticalSection(&cs);
		}
	}
	WaitForSingleObject(hChildA, INFINITE);
	WaitForSingleObject(hChildB, INFINITE);

	DeleteCriticalSection(&cs);

	CloseHandle(hChildA);
	CloseHandle(hChildB);

	system("pause");
	return 0;
}