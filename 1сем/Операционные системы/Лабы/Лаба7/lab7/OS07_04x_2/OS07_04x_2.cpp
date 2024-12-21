#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;


bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "rus");

    clock_t start = clock(); //���������� �������� �������
    int iteration = 0;
    int number = 2; //������ ������� �����

    cout << "��� ������� �����:\n";


    while (true) {
        int elapsedSeconds = (clock() - start) / CLOCKS_PER_SEC; //������� ���������� ������� � ������ �������� ������ � �������

        if (isPrime(number)) {
            cout << iteration + 1 << ": " << number << ", Time: " << elapsedSeconds << " seconds\n";
            iteration++;
        }

        number++;

        if (elapsedSeconds == 120) {
            break;
        }
        Sleep(100);
    }
    Sleep(1000);
    cout << "����� ���������� ������� �����: " << iteration << '\n';

}