using System;

class Program
{
    static void CalculatePowers(double x, out double x2, out double x5, out double x17)
    {
        x2 = x * x;           // 1-я операция
        double x4 = x2 * x2;  // 2-я операция
        double x8 = x4 * x4;  // 3-я операция
        x5 = x2 * x4;         // 4-я операция
        x17 = x8 * x8 * x;    // 5-я и 6-я операции
    }

    static void Main()
    {
        Console.Write("Input number: ");
        double x = Convert.ToDouble(Console.ReadLine());

        CalculatePowers(x, out double x2, out double x5, out double x17);

        Console.WriteLine($"x^2 = {x2}");
        Console.WriteLine($"x^5 = {x5}");
        Console.WriteLine($"x^17 = {x17}");

        Console.WriteLine("\nPress Enter to exit...");
        Console.ReadLine(); // Ожидание нажатия Enter
    }
}