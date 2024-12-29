using System;
using System.Threading;

class Program
{
    private static readonly object lockObject = new object(); // Объект для синхронизации
    static void Main(string[] args)
    {
        Console.WriteLine("Запуск приложения OS08_02 (Platform Target x86)");
        Console.WriteLine("Каждые 5 секунд создается новый объект размером 128 МБ.");

        // Список для хранения объектов (чтобы избежать их очистки сборщиком мусора)
        var memoryList = new System.Collections.Generic.List<byte[]>();
        //var memoryList = new List<byte[]>();// с lock

        // Поток для случайного заполнения памяти
        /*Thread fillerThread = new Thread(() =>
        {
            Random random = new Random();
            while (true)
            {
                lock (lockObject) // Блокируем коллекцию для изменений
                {
                    foreach (var memoryChunk in memoryList)
                    {
                        for (int i = 0; i < memoryChunk.Length; i++)
                        {
                            memoryChunk[i] = (byte)random.Next(0, 256); // Заполнение случайными байтами
                        }
                    }
                }
                Thread.Sleep(1000); // Пауза между итерациями
            }
        });
        fillerThread.IsBackground = true; // Устанавливаем поток фоновым
        fillerThread.Start();*/


        while (true)
        {
            try
            {
                // Создаем объект размером 128 МБ
                byte[] memoryChunk = new byte[128 * 1024 * 1024];
                memoryList.Add(memoryChunk);
                /*lock (lockObject) // Блокируем коллекцию для добавления
                {
                    memoryList.Add(memoryChunk);
                }*/

                // Заполняем память данными для гарантии выделения
                for (int i = 0; i < memoryChunk.Length; i++)
                {
                    memoryChunk[i] = 1;
                }

                // Вывод используемой памяти
                Console.WriteLine($"Создан объект: 128 МБ. Используемая память: {GC.GetTotalMemory(false) / 1024 / 1024} МБ."); //GC.GetTotalMemory(false) используется для получения объема памяти, занятой управляемыми объектами в байтах. false означает, что перед измерением объема памяти не нужно вызывать сборщик мусора
            }
            catch (OutOfMemoryException)
            {
                Console.WriteLine("Недостаточно памяти для создания нового объекта.");
                break;
            }

            // Задержка 5 секунд
            Thread.Sleep(5000);
        }

        Console.WriteLine("Программа завершена.");
    }
}
