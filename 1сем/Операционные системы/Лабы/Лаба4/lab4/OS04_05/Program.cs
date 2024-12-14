using System;
using System.Diagnostics;

class Program
{
    static void Main(string[] args)
    {
        // Тестируем MySleep на 10 секунд
        int duration = 10000; // 10 секунд в миллисекундах
        Console.WriteLine($"Запуск MySleep на {duration} миллисекунд...");

        // Запускаем таймер
        Stopwatch stopwatch = Stopwatch.StartNew();
        double result = MySleep(duration);
        stopwatch.Stop();

        // Выводим результат
        Console.WriteLine($"MySleep завершился за {stopwatch.ElapsedMilliseconds} миллисекунд.");
        Console.WriteLine($"Результат вычислений: {result}");
    }

    static double MySleep(int ms)
    {
        double sum = 0;
        DateTime startTime = DateTime.Now;
        while ((DateTime.Now - startTime).TotalMilliseconds < ms)
        {
            double temp = 0.711 + (DateTime.Now - startTime).TotalSeconds / 10.0;
            double a, b, c, d, e, nt;
            for (int k = 0; k < 5500; ++k)
            {
                nt = temp - k / 27000.0;
                a = Math.Sin(nt);
                b = Math.Cos(nt);
                c = Math.Cos(nt / 2.0);
                d = Math.Sin(nt / 2);
                e = Math.Abs(1.0 - a * a - b * b) + Math.Abs(1.0 - c * c - d * d);
                sum += e;
            }
            Thread.Sleep(1); // Спим 1 миллисекунду, чтобы не перегружать ЦП
        }
        return sum;
    }
}