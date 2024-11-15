using System;
using System.Threading;

class Program 
{ 
    const int ThreadCount = 16; // Количество потоков
    const int ThreadLifeTime = 10; // Продолжительность работы каждого потока в секундах
    const int ObservationTime = 30; // Время наблюдения в секундах
    static int[,] Matrix = new int[ThreadCount, ObservationTime]; 
    static DateTime StartTime = DateTime.Now; 

    // Метод, который выполняет вычисления
    static void WorkThread(object o) 
    { 
        int id = (int)o; 
        for (int i = 0; i < ThreadLifeTime * 20; i++) 
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
        Console.WriteLine("A student ... is placing threads to the pool..."); 

        // Запускаем потоки в пуле
        for (int i = 0; i < ThreadCount; ++i) 
        { 
            object o = i; 
            ThreadPool.QueueUserWorkItem(WorkThread, o); //Запускает метод WorkThread в пуле потоков, передавая идентификатор потока o
        } 

        Console.WriteLine("A student ... is waiting for the threads to finish..."); 
        Thread.Sleep(1000 * ObservationTime); 

        // Вывод результатов в виде таблицы
        Console.WriteLine("Результаты работы потоков:");
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
//Пул - это механизм управления потоками, который позволяет эффективно использовать ресурсы процессора, управляя набором потоков, готовых к выполнению задач.