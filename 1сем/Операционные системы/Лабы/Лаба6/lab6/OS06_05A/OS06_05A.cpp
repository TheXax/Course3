#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"smwEvent");

	if (he == NULL)
	{
		cout << "OS06_05A: Open error Event\n";
	}
	else
	{
		cout << "OS06_05A: Open Event\n";
	}

	WaitForSingleObject(he, INFINITE);
	for (int i = 1; i <= 90; i++)
	{
		SetEvent(he); //все потоки, ожидающие на этом событии, смогут продолжить выполнение, если они были заблокированы вызовом WaitForSingleObject
		Sleep(100);
		cout << "OS06_05A: " << i << " PID: " << GetCurrentProcessId() << endl;
	}
	CloseHandle(he);
	system("pause");

	return 0;
}