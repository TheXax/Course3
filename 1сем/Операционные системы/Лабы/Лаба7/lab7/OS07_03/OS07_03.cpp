#include <iostream>
#include <Windows.h>

int main() {

    //���������� ���������� �������
    HANDLE hTimer = CreateWaitableTimer(nullptr, TRUE, L"Timer");
  
    const LONG period = 1000; //������������ �������
    const LONG outputInterval = 3000;  
    const LONG totalDuration = 15000; 


    LARGE_INTEGER dueTime; //��� �������� ������� ������������ �������
    dueTime.QuadPart = -10 * 1000 * period; 
    SetWaitableTimer(hTimer, &dueTime, period, nullptr, nullptr, FALSE);

    int iteration = 0;
    DWORD lastOutputTime = GetTickCount();  //��������� ������� ����� � ������������� � ������� ������ �������, ����� ����������� ����� ���������� ������

    DWORD startTime = GetTickCount();
    while (true) {
        DWORD waitResult = WaitForSingleObject(hTimer, INFINITE); //�������� ������������ �������
        if (waitResult == WAIT_OBJECT_0) {
              iteration++;
        }

        DWORD currentTime = GetTickCount();
        if (currentTime - lastOutputTime >= outputInterval) { //������ �� 3 �������
            std::cout << "Iteration count: " << iteration << std::endl;
            lastOutputTime = currentTime; 
        }

        DWORD elapsedTime = currentTime - startTime; //��������� ����� ����� ���������� ���������
        if (elapsedTime >= totalDuration) {
            std::cout << "Total iteration count: " << iteration << std::endl;
            break;
        }
    }

    CancelWaitableTimer(hTimer);
    CloseHandle(hTimer);

    return 0;
}