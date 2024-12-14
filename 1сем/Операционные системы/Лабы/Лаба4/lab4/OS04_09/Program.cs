using System;
using System.Threading.Tasks;

class Program
{
    const int TaskCount = 16; // Количество задач
    const int TaskLifeTime = 10; // Продолжительность работы каждой задачи в секундах
    const int ObservationTime = 30; // Время наблюдения в секундах
    static int[,] Matrix = new int[TaskCount, ObservationTime];
    static DateTime StartTime = DateTime.Now;

    // Метод, который выполняет вычисления
    static void Work(object o)
    {
        int id = (int)o;
        for (int i = 0; i < TaskLifeTime * 20; i++)
        {
            DateTime CurrentTime = DateTime.Now;
            int ElapsedSeconds = (int)Math.Round(CurrentTime.Subtract(StartTime).TotalSeconds - 0.49);

            // Проверка на границы
            if (ElapsedSeconds >= 0 && ElapsedSeconds < ObservationTime)
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
        Task[] tasks = new Task[TaskCount];//значения задач
        int[] numbers = new int[TaskCount];//идентификаторы
        for (int i = 0; i < TaskCount; i++)
            numbers[i] = i;

        Console.WriteLine("A student ... is creating tasks...");

        // Создание задач
        for (int i = 0; i < TaskCount; i++)
        {
            int taskId = i; // Локальная переменная для избежания замыкания
            tasks[i] = Task.Run(() => Work(taskId));//Запускает метод Work в новой задаче
        }

        Console.WriteLine("A student ... is waiting for tasks to finish...");
        Task.WaitAll(tasks);

        // Вывод результатов в виде таблицы
        Console.WriteLine("Результаты работы задач:");
        Console.WriteLine("Секунда | " + string.Join(" | ", Array.ConvertAll(new int[TaskCount], x => $"Задача {Array.IndexOf(new int[TaskCount], x)}")));
        Console.WriteLine(new string('-', 60));

        for (int s = 0; s < ObservationTime; s++)
        {
            Console.Write("{0,3}:  ", s);
            for (int th = 0; th < TaskCount; th++)
            {
                Console.Write(" {0,5}", Matrix[th, s]);
            }
            Console.WriteLine();
        }
    }
}