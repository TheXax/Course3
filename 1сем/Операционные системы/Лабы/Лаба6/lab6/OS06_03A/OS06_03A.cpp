#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	//для хранения дескриптора мьютекса. Функция открывает существующий мьютекс с именем "smwMutex"
	HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"smwMutex"); //SYNCHRONIZE: Запрашивает разрешение на синхронизацию. FALSE: Указывает, что мьютекс не должен быть создан, если его нет.
	if (hm == NULL)//мьютекс не был открыт
	{
		cout << "OS06_03A: Open err Mutex\n";
	}
	else
	{
		cout << "OS06_03A: Open  Mutex\n";
	}

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hm, INFINITE);
		}
		if (i == 60)
		{
			ReleaseMutex(hm); //Освобождает мьютекс, позволяя другим потокам или процессам продолжить выполнение
		}
		Sleep(100);
		cout << "OS06_03A: " << i << " PID: " << GetCurrentProcessId() << endl;
	}
}