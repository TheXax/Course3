using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ArithmeticCoding
{
    class Program
    {
        static void Main(string[] args)
        {
            string message1 = "достопримечательность";
            string message2 = "достопримечательностьсорокадневный";

            Console.WriteLine("Сжатие сообщения 1: " + message1);
            var result1 = Compress(message1);
            Console.WriteLine($"Сжатое число: {result1.Item1}, Длина сообщения: {result1.Item2}");
            string decompressed1 = Decompress(result1.Item1, result1.Item2, result1.Item3);
            Console.WriteLine("Распакованное сообщение 1: " + decompressed1);

            Console.WriteLine("\nСжатие сообщения 2: " + message2);
            var result2 = Compress(message2);
            Console.WriteLine($"Сжатое число: {result2.Item1}, Длина сообщения: {result2.Item2}");
            string decompressed2 = Decompress(result2.Item1, result2.Item2, result2.Item3);
            Console.WriteLine("Распакованное сообщение 2: " + decompressed2);

            Console.WriteLine("\nОценка переполнения: Переполнение может возникнуть при длинных сообщениях из-за увеличения требуемой точности для представления интервала. Для предотвращения рекомендуется использовать целочисленную арифметику или периодическую нормализацию интервала.");

            Console.WriteLine("\nСравнение с вероятностными алгоритмами: Арифметическое сжатие эффективнее для символов с вероятностями, не кратными степеням 2, так как позволяет кодировать последовательности целиком, а не отдельные символы, в отличие от метода Хаффмана.");

            Console.ReadLine();
        }

        static (double, int, Dictionary<char, (double, double)>) Compress(string message)
        {
            // Подсчет частоты символов
            var freq = message.GroupBy(c => c)
                              .ToDictionary(g => g.Key, g => (double)g.Count() / message.Length);

            // Создание интервалов для каждого символа
            var intervals = new Dictionary<char, (double, double)>();
            double currentLow = 0.0; // Переименовано из 'low' во избежание конфликта
            foreach (var pair in freq.OrderBy(p => p.Key))
            {
                intervals[pair.Key] = (currentLow, currentLow + pair.Value);
                currentLow += pair.Value;
            }

            // Прямое преобразование
            double a = 0.0, b = 1.0;
            foreach (char c in message)
            {
                double range = b - a;
                double high = intervals[c].Item2;
                double low = intervals[c].Item1;

                b = a + range * high;
                a = a + range * low;
            }

            // Возвращаем нижнюю границу интервала, длину сообщения и интервалы
            return (a, message.Length, intervals);
        }

        static string Decompress(double code, int length, Dictionary<char, (double, double)> intervals)
        {
            StringBuilder result = new StringBuilder();
            double currentCode = code;

            for (int i = 0; i < length; i++)
            {
                // Находим символ, соответствующий текущему коду
                foreach (var pair in intervals)
                {
                    if (currentCode >= pair.Value.Item1 && currentCode < pair.Value.Item2)
                    {
                        result.Append(pair.Key);

                        // Обновляем код для следующего шага
                        double range = pair.Value.Item2 - pair.Value.Item1;
                        currentCode = (currentCode - pair.Value.Item1) / range;
                        break;
                    }
                }
            }

            return result.ToString();
        }
    }
}





/*
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ArithmeticCoding
{
    class Program
    {
        static void Main(string[] args)
        {
            string message1 = "достопримечательность";
            string message2 = "достопримечательностьсорокадневный";

            Console.WriteLine("Сжатие сообщения 1: " + message1);
            var result1 = Compress(message1);
            Console.WriteLine($"Сжатое число: {result1.Item1:F10}, Длина сообщения: {result1.Item2}");
            string decompressed1 = Decompress(result1.Item1, result1.Item2, result1.Item3);
            Console.WriteLine("Распакованное сообщение 1: " + decompressed1);
            Console.WriteLine("Совпадение с исходным: " + (message1 == decompressed1 ? "Да" : "Нет"));

            Console.WriteLine("\nСжатие сообщения 2: " + message2);
            var result2 = Compress(message2);
            Console.WriteLine($"Сжатое число: {result2.Item1:F10}, Длина сообщения: {result2.Item2}");
            string decompressed2 = Decompress(result2.Item1, result2.Item2, result2.Item3);
            Console.WriteLine("Распакованное сообщение 2: " + decompressed2);
            Console.WriteLine("Совпадение с исходным: " + (message2 == decompressed2 ? "Да" : "Нет"));

            Console.WriteLine("\nОценка переполнения: Переполнение может возникнуть при длинных сообщениях из-за увеличения требуемой точности. Рекомендуется использовать целочисленную арифметику или нормализацию.");
            Console.WriteLine("Сравнение с вероятностными алгоритмами: Арифметическое сжатие эффективнее для некратных вероятностей, кодируя последовательности целиком.");

            Console.ReadLine();
        }

        static (double, int, Dictionary<char, (double, double)>) Compress(string message)
        {
            var freq = message.GroupBy(c => c)
                              .ToDictionary(g => g.Key, g => (double)g.Count() / message.Length);
            var intervals = new Dictionary<char, (double, double)>();
            double currentLow = 0.0;
            foreach (var pair in freq.OrderBy(p => p.Key))
            {
                intervals[pair.Key] = (currentLow, currentLow + pair.Value);
                currentLow += pair.Value;
            }

            double a = 0.0, b = 1.0;
            foreach (char c in message)
            {
                double range = b - a;
                double high = intervals[c].Item2;
                double low = intervals[c].Item1;
                b = a + range * high;
                a = a + range * low;
            }

            return (a, message.Length, intervals);
        }

        static string Decompress(double code, int length, Dictionary<char, (double, double)> intervals)
        {
            StringBuilder result = new StringBuilder();
            double currentCode = code;

            for (int i = 0; i < length; i++)
            {
                Console.WriteLine($"\nШаг {i + 1}: Текущий код = {currentCode:F10}");
                foreach (var pair in intervals.OrderBy(p => p.Value.Item1))
                {
                    if (currentCode >= pair.Value.Item1 && currentCode < pair.Value.Item2)
                    {
                        result.Append(pair.Key);
                        Console.WriteLine($"Найден символ: {pair.Key}, Интервал: [{pair.Value.Item1:F10}, {pair.Value.Item2:F10})");
                        double range = pair.Value.Item2 - pair.Value.Item1;
                        currentCode = (currentCode - pair.Value.Item1) / range;
                        Console.WriteLine($"Новый код: {currentCode:F10}");
                        break;
                    }
                }
            }

            return result.ToString();
        }
    }
}
 */