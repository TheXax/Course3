#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void calculate_powers(double x, double* x2, double* x5, double* x17) {
    *x2 = x * x;         // 1-я операция
    double x4 = *x2 * *x2; // 2-я операция
    double x8 = x4 * x4;  // 3-я операция
    *x5 = *x2 * x4;      // 4-я операция
    *x17 = x8 * x8 * x;  // 5-я и 6-я операции
}

int main() {
    double x, x2, x5, x17;
    printf("Input number: ");
    scanf("%lf", &x);

    calculate_powers(x, &x2, &x5, &x17);

    printf("x^2 = %lf\n", x2);
    printf("x^5 = %lf\n", x5);
    printf("x^17 = %lf\n", x17);

    printf("\nPress Enter to exit...");
    getchar();
    getchar(); // Ожидание нажатия Enter
    return 0;
}