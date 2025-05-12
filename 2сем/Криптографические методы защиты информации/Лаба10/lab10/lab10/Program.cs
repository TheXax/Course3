using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LZ77Compression
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Введите текст для сжатия:");
            string inputText = Console.ReadLine();
            Console.WriteLine("Введите размер окна словаря (n1):");
            int dictSize = int.Parse(Console.ReadLine());
            Console.WriteLine("Введите размер буфера данных (n2):");
            int bufferSize = int.Parse(Console.ReadLine());

            // Сжатие
            var compressed = Compress(inputText, dictSize, bufferSize);
            Console.WriteLine("\nСжатое сообщение (триады):");
            foreach (var triad in compressed)
            {
                Console.Write($"({triad.p},{triad.q},{triad.s})");
            }

            // Распаковка
            string decompressed = Decompress(compressed, dictSize);
            Console.WriteLine("\n\nРаспакованное сообщение:");
            Console.WriteLine(decompressed);

            // Оценка эффективности
            double compressionRatio = (double)inputText.Length * 8 / (compressed.Count * 3 * 8); // Примерная оценка
            Console.WriteLine($"\nКоэффициент сжатия: {compressionRatio:F2}");

            Console.ReadKey();
        }

        public struct Triad
        {
            public int p; // Начало повторяющейся последовательности
            public int q; // Длина повторяющейся последовательности
            public char s; // Следующий символ
            public Triad(int p, int q, char s)
            {
                this.p = p;
                this.q = q;
                this.s = s;
            }
        }

        public static List<Triad> Compress(string input, int dictSize, int bufferSize)
        {
            List<Triad> result = new List<Triad>();
            string dictionary = new string('0', dictSize); // Инициализация словаря нулями
            int inputIndex = 0;

            while (inputIndex < input.Length)
            {
                int maxMatchLength = 0;
                int maxMatchPos = 0;
                char nextChar = input[inputIndex];
                int searchLength = Math.Min(bufferSize, input.Length - inputIndex);

                // Поиск наибольшего совпадения в словаре
                for (int i = 0; i < dictionary.Length; i++)
                {
                    int matchLength = 0;
                    while (matchLength < searchLength &&
                           i + matchLength < dictionary.Length &&
                           inputIndex + matchLength < input.Length &&
                           dictionary[i + matchLength] == input[inputIndex + matchLength])
                    {
                        matchLength++;
                    }
                    if (matchLength > maxMatchLength)
                    {
                        maxMatchLength = matchLength;
                        maxMatchPos = i;
                        if (inputIndex + matchLength < input.Length)
                            nextChar = input[inputIndex + matchLength];
                    }
                }

                // Формирование триады
                result.Add(new Triad(maxMatchPos, maxMatchLength, nextChar));

                // Обновление словаря
                int shift = maxMatchLength + 1;
                if (shift > 0)
                {
                    dictionary = dictionary.Substring(Math.Min(shift, dictionary.Length));
                    dictionary += input.Substring(inputIndex, Math.Min(shift, input.Length - inputIndex));
                    inputIndex += shift;
                }
                else
                {
                    dictionary = dictionary.Substring(1) + input[inputIndex];
                    inputIndex++;
                }
            }

            return result;
        }

        public static string Decompress(List<Triad> compressed, int dictSize)
        {
            string dictionary = new string('0', dictSize); // Инициализация словаря нулями
            StringBuilder result = new StringBuilder();

            foreach (var triad in compressed)
            {
                string sequence = "";
                if (triad.q > 0)
                {
                    // Копируем повторяющуюся последовательность из словаря
                    sequence = dictionary.Substring(triad.p, triad.q);
                }
                sequence += triad.s; // Добавляем следующий символ

                // Добавляем в результат
                result.Append(sequence); 


                // Обновляем словарь
                int shift = triad.q + 1;
                dictionary = dictionary.Substring(Math.Min(shift, dictionary.Length)) + sequence;
            }

            return result.ToString();
        }
    }
}