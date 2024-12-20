#include <iostream>
#include <Windows.h>
#include <ctime>

using namespace std;
//Mutex — это механизм синхронизации, который позволяет ограничить доступ к ресурсу в многопоточной среде.
int mutex = 0; // для управления доступом к критической секции
//Критическая секция - это участок кода, который должен выполняться только одним потоком в одно время.
DWORD WINAPI Thread();
int main() {

	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, NULL);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, NULL);
	WaitForSingleObject(hChild, INFINITE);
	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild);
	CloseHandle(hChild2);
	system("pause");
}

//вход в критическую функцию
void start_critical_section(void)
{
	__asm {
	SpinLoop:
		//lock: Эта префиксная команда указывает, что последующая операция должна быть атомарной.
		lock bts mutex, 0;  //bts устанавливает бит по указанному индексу (в данном случае бит 0) в переменной mutex. Если бит был ранее установлен, это означает, что ресурс занят другим потоком
		jc SpinLoop         //jc проверяет флаг переноса. Если ресурс занят, jc приводит к переходу назад к метке SpinLoop, повторяя попытку установить бит
			//Это создает "петлю ожидания" (spinlock), где поток активно ждет, пока ресурс не станет доступным.
	}
}

void exit_critical_section(void)
{
	__asm lock btr mutex, 0 // обнуляет выбранный бит в mutex. После выполнения этой команды другой поток сможет установить бит и получить доступ к критической секции.
}

DWORD WINAPI Thread()
{
	DWORD tid = GetCurrentThreadId(); //id текущего потока
	start_critical_section();
	for (int i = 1; i < 91; i++)
	{
		cout << "Thread: " << tid << "  " << i << endl;
	}
	exit_critical_section();
	return 0;
}