using System;
using System.Threading;

class Program
{
    // Поток Z работает 10 секунд 
    static void ThreadZed()
    {
        for (int i = 0; i < 10; i++)
        {
            Console.Write(" (Z-{0}) ", Thread.CurrentThread.ManagedThreadId); //Получает уникальный идентификатор текущего потока
            Thread.Sleep(1000);
        }
        Console.WriteLine(" Поток Z завершается ");
    }

    // Поток работает 20 секунд, параметр - строка-идентификатор 
    static void ThreadWithParam(object o)
    {
        for (int i = 0; i < 20; i++)
        {
            Console.Write(" ({0}-{1}) ", o.ToString(),
                Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(1000);
        }
        Console.WriteLine(" Поток {0} завершается ", o.ToString());
    }

    static void Main(string[] args)
    {
        //создание потоков
        var t1 = new Thread(ThreadZed);
        var t1a = new Thread(ThreadWithParam);
        var t1b = new Thread(ThreadWithParam);

        t1.IsBackground = true;//фоновой поток, который не блокирует завершение приложения, если другие потоки завершились
        t1a.IsBackground = true;
        t1b.IsBackground = true;

        t1.Start();
        t1a.Start("Вероника");
        t1b.Start("Стрелковская");

        // Главный поток работает 5 секунд 
        for (int i = 0; i < 5; i++)
        {
            Console.Write(" (*-{0}) ", Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(1000);
        }

        Console.WriteLine("Главный поток завершается");
    }
}