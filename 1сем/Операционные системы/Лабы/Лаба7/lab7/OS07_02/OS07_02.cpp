#include <Windows.h>
#include <iostream>
#include <ctime>
using namespace std;


int main() 
{
	clock_t start = clock(); //кол-во тактов процессора с запуска программы
	int i = 0;
	bool flag5 = true, flag10 = true;

	while (true) 
	{
		i++;
		if ((clock() - start) / CLOCKS_PER_SEC == 5 && flag5) { //CLOCKS_PER_SEC - преобразование тактов в секунды
			cout << "Iterations after 5s: " << i << '\n';
			flag5 = false;
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 10 && flag10) {
			cout << "Iterations after 10s: " << i << '\n';
			flag10 = false;
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 15) {
			cout << "Iterations after 15s: " << i << '\n';
			break;
		}
	}

	return 0;
}