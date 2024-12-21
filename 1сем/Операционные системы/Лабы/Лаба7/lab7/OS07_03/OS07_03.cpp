#include <iostream>
#include <Windows.h>

int main() {

    //дискриптор ожидаемого таймера
    HANDLE hTimer = CreateWaitableTimer(nullptr, TRUE, L"Timer");
  
    const LONG period = 1000; //срабатывание таймера
    const LONG outputInterval = 3000;  
    const LONG totalDuration = 15000; 


    LARGE_INTEGER dueTime; //для хранения времени срабатывания таймера
    dueTime.QuadPart = -10 * 1000 * period; 
    SetWaitableTimer(hTimer, &dueTime, period, nullptr, nullptr, FALSE);

    int iteration = 0;
    DWORD lastOutputTime = GetTickCount();  //сохраняет текущее время в миллисекундах с момента старта системы, чтобы отслеживать время последнего вывода

    DWORD startTime = GetTickCount();
    while (true) {
        DWORD waitResult = WaitForSingleObject(hTimer, INFINITE); //ожидание срабатывания таймера
        if (waitResult == WAIT_OBJECT_0) {
              iteration++;
        }

        DWORD currentTime = GetTickCount();
        if (currentTime - lastOutputTime >= outputInterval) { //прошло ли 3 секунды
            std::cout << "Iteration count: " << iteration << std::endl;
            lastOutputTime = currentTime; 
        }

        DWORD elapsedTime = currentTime - startTime; //вычисляет общее время выполнения программы
        if (elapsedTime >= totalDuration) {
            std::cout << "Total iteration count: " << iteration << std::endl;
            break;
        }
    }

    CancelWaitableTimer(hTimer);
    CloseHandle(hTimer);

    return 0;
}