#include <iostream>
#include <Windows.h>
#include <process.h>

int main()
{
	for (int i = 0; i < 125; i++) {
		Sleep(1000);
		std::cout << "OS03_02_2: " << _getpid() << "\n";
	}
	return 0;
}