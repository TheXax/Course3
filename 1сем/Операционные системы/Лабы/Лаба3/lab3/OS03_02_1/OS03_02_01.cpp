#include <iostream>
#include <Windows.h>
#include <process.h>

int main()
{
	for (int i = 0; i < 50; i++) {
		Sleep(1000);
		std::cout << "OS03_02_1: " << _getpid() << "\n";
	}
	return 0;
}