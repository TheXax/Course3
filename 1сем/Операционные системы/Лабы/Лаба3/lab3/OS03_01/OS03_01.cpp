#include <iostream>
#include <windows.h> //������ � �� (�-��� Sleep)
#include <process.h>

int main()
{
    for (int i = 0; i < 100; i++) {
        Sleep(1000);
        std::cout << _getpid() << "\t";
    }

}