#include <iostream>
#include <Windows.h>
#include <ctime>

using namespace std;
//Mutex � ��� �������� �������������, ������� ��������� ���������� ������ � ������� � ������������� �����.
int mutex = 0; // ��� ���������� �������� � ����������� ������
//����������� ������ - ��� ������� ����, ������� ������ ����������� ������ ����� ������� � ���� �����.
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

//���� � ����������� �������
void start_critical_section(void)
{
	__asm {
	SpinLoop:
		//lock: ��� ���������� ������� ���������, ��� ����������� �������� ������ ���� ���������.
		lock bts mutex, 0;  //bts ������������� ��� �� ���������� ������� (� ������ ������ ��� 0) � ���������� mutex. ���� ��� ��� ����� ����������, ��� ��������, ��� ������ ����� ������ �������
		jc SpinLoop         //jc ��������� ���� ��������. ���� ������ �����, jc �������� � �������� ����� � ����� SpinLoop, �������� ������� ���������� ���
			//��� ������� "����� ��������" (spinlock), ��� ����� ������� ����, ���� ������ �� ������ ���������.
	}
}

void exit_critical_section(void)
{
	__asm lock btr mutex, 0 // �������� ��������� ��� � mutex. ����� ���������� ���� ������� ������ ����� ������ ���������� ��� � �������� ������ � ����������� ������.
}

DWORD WINAPI Thread()
{
	DWORD tid = GetCurrentThreadId(); //id �������� ������
	start_critical_section();
	for (int i = 1; i < 91; i++)
	{
		cout << "Thread: " << tid << "  " << i << endl;
	}
	exit_critical_section();
	return 0;
}