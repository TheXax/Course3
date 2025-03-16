using System;

class Program
{
    static void CalculatePowers(double x, out double x2, out double x5, out double x17)
    {
        x2 = x * x;           // 1-� ��������
        double x4 = x2 * x2;  // 2-� ��������
        double x8 = x4 * x4;  // 3-� ��������
        x5 = x2 * x4;         // 4-� ��������
        x17 = x8 * x8 * x;    // 5-� � 6-� ��������
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
        Console.ReadLine(); // �������� ������� Enter
    }
}