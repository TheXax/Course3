/*using System;
using System.Diagnostics;
using System.Threading;

class Program
{
    static int ThreadCount = 16; // Количество потоков
    static Thread[] t = new Thread[ThreadCount];//массив t для хранения ссылок на объекты потоков

    static void WorkThread(object id)
    {
        int threadId = (int)id;
        Console.WriteLine($"Thread {threadId} started with priority {Thread.CurrentThread.Priority}");

        // Имитация работы потока
        MySleep(1);

        Console.WriteLine($"Thread {threadId} finished");
    }

    static void MySleep(int milliseconds)
    {
        Thread.Sleep(milliseconds);
    }

    static void Main()
    {
        // Ограничение количества логических процессоров. Устанавливает маску процессоров, на которых может выполняться текущий процесс
        Process.GetCurrentProcess().ProcessorAffinity = (IntPtr)15; // Используем 4 логических процессора

        for (int i = 0; i < ThreadCount; ++i)
        {
            object o = i;
            t[i] = new Thread(WorkThread);//создаём новый поток
            switch (i % 3)
            {
                case 0:
                    t[i].Priority = ThreadPriority.Lowest;
                    break;
                case 2:
                    t[i].Priority = ThreadPriority.Highest;
                    break;
            }
            t[i].Start(o);
        }

        // Ожидание завершения всех потоков
        foreach (var thread in t)
        {
            thread.Join();
        }

        Console.WriteLine("All threads finished.");
    }
}*/





using System;
using System.Threading;

class Program
{
    const int ThreadCount = 16; // Количество потоков
    const int ThreadLifeTime = 10; // Продолжительность работы каждого потока в секундах
    const int ObservationTime = 30; // Время наблюдения в секундах
    static int[,] Matrix = new int[ThreadCount, ObservationTime];//хранение результатов работы каждого потока в течение времени наблюдения
    static DateTime StartTime = DateTime.Now;

    // Метод, который выполняет вычисления
    static void WorkThread(object o)
    {
        int id = (int)o;
        for (int i = 0; i < ThreadLifeTime * 20; i++)
        {
            DateTime CurrentTime = DateTime.Now;
            //Вычисляет количество секунд, прошедших с момента старта, с небольшим сдвигом (уменьшение на 0.49 секунды для округления)
            int ElapsedSeconds = (int)Math.Round(CurrentTime.Subtract(StartTime).TotalSeconds - 0.49);

            if (ElapsedSeconds >= 0 && ElapsedSeconds < ObservationTime) // Проверка на границы
            {
                Matrix[id, ElapsedSeconds] += 50;
            }

            MySleep(50); // Вычисления, которые занимают время
        }
    }

    // Метод для выполнения "сна" в течение заданного времени
    static Double MySleep(int ms)
    {
        double sum = 0, temp;
        for (int t = 0; t < ms; ++t)
        {
            temp = 0.711 + (double)t / 10000.0;
            for (int k = 0; k < 5500; ++k)
            {
                double nt = temp - k / 27000.0;
                double a = Math.Sin(nt);
                double b = Math.Cos(nt);
                double c = Math.Cos(nt / 2.0);
                double d = Math.Sin(nt / 2);
                double e = Math.Abs(1.0 - a * a - b * b) + Math.Abs(1.0 - c * c - d * d);
                sum += e;
            }
        }
        return sum;
    }

    static void Main(string[] args)
    {
        Thread[] t = new Thread[ThreadCount];
        for (int i = 0; i < ThreadCount; ++i)
        {
            object o = i;
            t[i] = new Thread(WorkThread);

            // Установка приоритета потоков
            if (i < 2) 
                t[i].Priority = ThreadPriority.Lowest; //BellowNormal
            else
                t[i].Priority = ThreadPriority.Highest; //Normal

            t[i].Start(o);
        }

        Console.WriteLine("Ожидание завершения потоков...");
        for (int i = 0; i < ThreadCount; ++i)
        {
            t[i].Join();//чтобы главный поток ожидал завершения всех созданных потоков
        }

        // Вывод результатов в виде таблицы
        Console.WriteLine("Результаты работы потоков:");
        //Создает новый массив длиной ThreadCount (в вашем случае 10) и заполняет его строками вида "Поток 0", "Поток 1" и т.д.
        //Объединяет все строки из массива в одну строку, разделяя их символами " | "
        Console.WriteLine("Секунда | " + string.Join(" | ", Array.ConvertAll(new int[ThreadCount], x => $"Поток {Array.IndexOf(new int[ThreadCount], x)}")));
        Console.WriteLine(new string('-', 60));

        for (int s = 0; s < ObservationTime; s++)
        {
            Console.Write("{0,3}:  ", s);
            for (int th = 0; th < ThreadCount; th++)
            {
                Console.Write(" {0,5}", Matrix[th, s]);
            }
            Console.WriteLine();
        }
    }
}