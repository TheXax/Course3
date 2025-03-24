using System;
using System.IO;
using System.Text;
using System.Linq;

class Program
{
    static void Main()
    {
        string filePath = "input.txt"; // Исходный файл
        string base64FilePath = "output_base64.txt"; // Файл после кодировки

        // Чтение исходного файла
        string inputText = File.ReadAllText(filePath, Encoding.UTF8);
        Console.WriteLine("Исходный текст:\n" + inputText);

        // Кодирование в Base64
        string base64Encoded = Convert.ToBase64String(Encoding.UTF8.GetBytes(inputText));
        File.WriteAllText(base64FilePath, base64Encoded);
        Console.WriteLine("\nТекст в Base64:\n" + base64Encoded);

        // Анализ частот символов
        AnalyzeFrequency(inputText, "Исходный файл");
        AnalyzeFrequency(base64Encoded, "Base64 файл");

        // Вычисление энтропии
        double entropyOriginal = CalculateEntropy(inputText);
        double entropyBase64 = CalculateEntropy(base64Encoded);
        Console.WriteLine($"\nЭнтропия исходного файла (Шеннон): {entropyOriginal}");
        Console.WriteLine($"Энтропия Base64 файла (Шеннон): {entropyBase64}");

        // Вычисление энтропии Хартли
        double hartleyEntropyOriginal = CalculateHartleyEntropy(inputText.Length);
        double hartleyEntropyBase64 = CalculateHartleyEntropy(base64Encoded.Length);
        Console.WriteLine($"Энтропия исходного файла (Хартли): {hartleyEntropyOriginal}");
        Console.WriteLine($"Энтропия Base64 файла (Хартли): {hartleyEntropyBase64}");

        // Вычисление избыточности
        double redundancyOriginal = CalculateRedundancy(entropyOriginal, hartleyEntropyOriginal);
        double redundancyBase64 = CalculateRedundancy(entropyBase64, hartleyEntropyBase64);
        Console.WriteLine($"Избыточность исходного файла: {redundancyOriginal}");
        Console.WriteLine($"Избыточность Base64 файла: {redundancyBase64}");

        // Операция XOR
        string xorResult = XORStrings(inputText, base64Encoded);
        Console.WriteLine("\nРезультат XOR:\n" + xorResult);

        // Пример использования функции XOR для фамилии и имени
        string surname = "Strelkovskaya"; // Фамилия
        string name = "Veronika"; // Имя
        string xorNameResult = XORStrings(surname, name);
        Console.WriteLine($"\nРезультат XOR для '{surname}' и '{name}': {xorNameResult}");

        // Результат операции a XOR b XOR b
        string finalResult = XORStrings(xorNameResult, name);
        Console.WriteLine($"Результат операции '{surname} XOR {name} XOR {name}': {finalResult}");
    }

    static void AnalyzeFrequency(string text, string description)
    {
        var frequency = text.GroupBy(c => c)
                            .ToDictionary(g => g.Key, g => g.Count());

        Console.WriteLine($"\nЧастотный анализ ({description}):");
        foreach (var kvp in frequency.OrderByDescending(x => x.Value))
        {
            Console.WriteLine($"'{kvp.Key}': {kvp.Value}");
        }
    }

    static double CalculateEntropy(string text)
    {
        var frequency = text.GroupBy(c => c)
                            .ToDictionary(g => g.Key, g => (double)g.Count() / text.Length);

        return -frequency.Values.Sum(p => p * Math.Log2(p));
    }

    static double CalculateHartleyEntropy(int length)
    {
        // Максимальная энтропия для ASCII (256 символов)
        return Math.Log2(256) * length;
    }

    static double CalculateRedundancy(double entropy, double maxEntropy)
    {
        return maxEntropy - entropy;
    }

    static string XORStrings(string str1, string str2)
    {
        int length = Math.Max(str1.Length, str2.Length); // Определяем длину, равную большей из двух строк
        char[] result = new char[length];

        for (int i = 0; i < length; i++)
        {
            char char1 = i < str1.Length ? str1[i] : '\0'; // Дополнение нулями
            char char2 = i < str2.Length ? str2[i] : '\0'; // Дополнение нулями
            result[i] = (char)(char1 ^ char2);
        }

        return new string(result);
    }
}