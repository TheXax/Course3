#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	//для хранения дескриптора семафора
	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"smwSem");
	if (hs == NULL)
	{
		cout << "OS06_04A: Open error Semaphore\n";
	}
	else
	{
		cout << "OS06_04A: Open Semaphore\n";
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
			cout << "OS06_04A: prevcount = " << prevcount << endl;
		}
		Sleep(100);
		cout << "OS06_04A: " << i << " PID: " << GetCurrentProcessId() << endl;
	}

	CloseHandle(hs);
	system("pause");

	return 0;
}