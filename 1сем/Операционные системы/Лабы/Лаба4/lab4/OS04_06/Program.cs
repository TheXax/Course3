using System;
using System.Threading;

class Program
{
    // Общая переменная
    static int Count = 0;

    static void WorkThread()
    {
        for (int i = 0; i < 5000000; ++i)
        {
            // Увеличиваем счетчик без блокировки
            Count++;
        }
    }

    static void Main(string[] args)
    {
        Thread[] threads = new Thread[20];

        // Запускаем 20 потоков
        for (int i = 0; i < 20; ++i)
        {
            threads[i] = new Thread(WorkThread);
            threads[i].Start();
        }

        // Ожидаем завершения всех потоков
        for (int i = 0; i < 20; ++i)
            threads[i].Join(); // Метод Join используется для ожидания завершения каждого потока

        // Выводим результат
        Console.WriteLine("Общее значение Count: " + Count);
        Console.WriteLine("Ожидаемое значение: " + (20 * 5000000));
    }
}