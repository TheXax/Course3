using System;
using System.Diagnostics;
using System.Linq;
using System.Text;

class BWT
{
    // Прямое преобразование BWT
    public static (string, int) Compress(string input)
    {
        // Добавляем уникальный конечный символ
        string s = input;
        int len = s.Length;

        // Создаём все циклические сдвиги
        string[] rotations = new string[len];
        for (int i = 0; i < len; i++)
        {
            rotations[i] = s.Substring(i) + s.Substring(0, i);
        }

        // Сортируем сдвиги
        Array.Sort(rotations);

        // Извлекаем последнюю колонку
        StringBuilder lastColumn = new StringBuilder();
        for (int i = 0; i < len; i++)
        {
            lastColumn.Append(rotations[i][len - 1]);
        }

        // Находим индекс исходной строки
        int index = Array.IndexOf(rotations, s);

        return (lastColumn.ToString(), index);
    }

    // Обратное преобразование BWT
    public static string Decompress(string lastColumn, int index)
    {
        int len = lastColumn.Length;
        string[] table = new string[len];

        // Инициализируем таблицу
        for (int i = 0; i < len; i++)
        {
            table[i] = "";
        }

        // Строим таблицу итеративно
        for (int j = 0; j < len; j++)
        {
            for (int i = 0; i < len; i++)
            {
                table[i] = lastColumn[i] + table[i];
            }
            Array.Sort(table);
        }

        // Возвращаем строку по индексу
        return table[index].TrimEnd('$');
    }

    // Преобразование символов в бинарную последовательность (Unicode)
    public static string CharToBinary(string input, int charCount)
    {
        StringBuilder binary = new StringBuilder();
        for (int i = 0; i < Math.Min(charCount, input.Length); i++)
        {
            int unicodeValue = (int)input[i];
            string binaryChar = Convert.ToString(unicodeValue, 2).PadLeft(16, '0');
            binary.Append(binaryChar).Append(" ");
        }
        return binary.ToString().Trim();
    }


    static void Main()
    {
        string myName = "Вероника";
        string message2 = "Стрелковская";
        string message3 = "достопримечательность";
        string message4 = message3.Substring(0, 3); // "дос"

        // Перевод первых 3 символов в бинарную последовательность
        string binaryRepresentation = CharToBinary(message4, 3);
        Console.WriteLine("Первые 3 символа: " + message4);
        Console.WriteLine("Бинарное представление (Unicode): " + binaryRepresentation);


        // Сжатие и распаковка первого сообщения
        var (compressed1, index1) = Compress(myName);
        string decompressed1 = Decompress(compressed1, index1);

        // Сжатие и распаковка второго сообщения
        var (compressed2, index2) = Compress(message2);
        string decompressed2 = Decompress(compressed2, index2);

        // Сжатие и распаковка третьего сообщения
        var (compressed3, index3) = Compress(message3);
        string decompressed3 = Decompress(compressed3, index3);

        // Сжатие и распаковка первых 3 символов с замером времени
        Stopwatch stopwatch = new Stopwatch();

        stopwatch.Start();
        var (compressed4, index4) = Compress(message4);
        stopwatch.Stop();
        double compressTime = stopwatch.ElapsedTicks / (double)TimeSpan.TicksPerMillisecond;

        stopwatch.Restart();
        string decompressed4 = Decompress(compressed4, index4);
        stopwatch.Stop();
        double decompressTime = stopwatch.ElapsedTicks / (double)TimeSpan.TicksPerMillisecond;

        // Вычисление коэффициента сжатия (без учёта индекса)
        double compressionRatio1 = (double)myName.Length / compressed1.Length;
        double compressionRatio2 = (double)message2.Length / compressed2.Length;
        double compressionRatio3 = (double)message3.Length / compressed3.Length;
        double compressionRatio4 = (double)message4.Length / compressed4.Length;

        // Вывод результатов
        Console.WriteLine("Сообщение 1: Вероника");
        Console.WriteLine($"Сжатое: {compressed1}, Индекс: {index1}");
        Console.WriteLine($"Распакованное: {decompressed1}");
        Console.WriteLine($"Коэффициент сжатия: {compressionRatio1:F2}");

        Console.WriteLine("\nСообщение 2: Стрелковская");
        Console.WriteLine($"Сжатое: {compressed2}, Индекс: {index2}");
        Console.WriteLine($"Распакованное: {decompressed2}");
        Console.WriteLine($"Коэффициент сжатия: {compressionRatio2:F2}");
        
        Console.WriteLine("\nСообщение 3: достопримечательность");
        Console.WriteLine($"Сжатое: {compressed3}, Индекс: {index3}");
        Console.WriteLine($"Распакованное: {decompressed3}");
        Console.WriteLine($"Коэффициент сжатия: {compressionRatio3:F2}");

        Console.WriteLine("\nСообщение 4: дос");
        Console.WriteLine($"Сжатое: {compressed4}, Индекс: {index4}");
        Console.WriteLine($"Распакованное: {decompressed4}");
        Console.WriteLine($"Коэффициент сжатия: {compressionRatio4:F2}");
        Console.WriteLine($"Время сжатия: {compressTime:F3} мс");
        Console.WriteLine($"Время распаковки: {decompressTime:F3} мс");
    }
}