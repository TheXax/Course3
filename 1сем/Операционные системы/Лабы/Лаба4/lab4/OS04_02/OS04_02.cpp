#include <Windows.h>
#include <iostream>

DWORD pid = NULL;
using namespace std;

//WINAPI — это соглашение о вызовах, которое используется в API Windows.
	DWORD WINAPI ChildThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 50; i++)
	{
		cout << i << " " << "OS04_02_T1: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI ChildSecondThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 125; i++)
	{
		cout << i << " " << "OS04_02_T2: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
	}

	return 0;
}

int main()
{
	pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId(); //Получает идентификатор текущего потока, который будет родительским
	//для хранения идентификаторов дочерних потоков
	DWORD childId = NULL;
	DWORD childSecondId = NULL;
	//Создание нового потока
	//Это тип данных в Windows API, который представляет собой абстракцию для управления различными ресурсами в операционной системе
	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &childId);
	HANDLE hChildSecond = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildSecondThread, NULL, 0, &childSecondId);

	for (int i = 0; i < 100; i++)
	{
		cout << i << " " << "Parent Thread: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
	}

	WaitForSingleObject(hChild, INFINITE);
	WaitForSingleObject(hChildSecond, INFINITE);
	CloseHandle(hChild);
	CloseHandle(hChildSecond);
}