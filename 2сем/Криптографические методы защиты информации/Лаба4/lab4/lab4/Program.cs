using System;
using System.Text;

class HammingCode
{
    static void Main()
    {
        // Исходное сообщение
        string message = "TEST";
        string binaryMessage = StringToBinary(message);
        Console.WriteLine($"Бинарное представление: {binaryMessage}");

        // Вычисляем длины
        int k = binaryMessage.Length;
        int r = CalculateRedundantBits(k);
        int n = k + r;

        Console.WriteLine($"Длина исходного сообщения (k): {k}");
        Console.WriteLine($"Количество избыточных битов (r): {r}");
        Console.WriteLine($"Общая длина кодового слова (n): {n}");

        // Строим проверочную матрицу Хемминга
        int[,] H = BuildHammingMatrix(n, r);
        Console.WriteLine("\nПроверочная матрица Хемминга:");
        PrintMatrix(H);

        //вычисление избыточных символов
        CalculateRedundantSymbols(binaryMessage, H, r);

        // Генерация кодового слова с избыточными битами
        string encodedMessage = EncodeHamming(binaryMessage, n, r);
        Console.WriteLine($"\nЗакодированное сообщение: {encodedMessage}");

        // Вносим случайную ошибку
        Random rnd = new Random();
        int errorCount = rnd.Next(3);
        string corruptedMessage = IntroduceErrors(encodedMessage, errorCount);
        Console.WriteLine($"Сообщение с {errorCount} ошибками: {corruptedMessage}");

        CalculateRedundantSymbolsWithErrors(corruptedMessage, H, r);

        // Исправляем ошибки
        AnalyzeSyndrome(corruptedMessage, H, r, errorCount);
    }

    static string StringToBinary(string text)
    {
        StringBuilder sb = new StringBuilder();
        foreach (char c in text)
            sb.Append(Convert.ToString(c, 2).PadLeft(8, '0'));
        return sb.ToString();
    }

    static int CalculateRedundantBits(int m)
    {
        int r = 0;
        while (Math.Pow(2, r) < m + r + 1)
            r++;
        return r;
    }

    // Функция для построения матрицы Хемминга
    static int[,] BuildHammingMatrix(int n, int r)
    {
        int[,] H = new int[r, n];

        // Строим матрицу A (первые r столбцов)
        int col = 0;
        for (int i = 1; col < n - r; i++)
        {
            // Генерация столбца в двоичной форме
            string binary = Convert.ToString(i, 2).PadLeft(r, '0');
            int onesCount = CountOnes(binary);

            // Если столбец содержит меньше 2 единиц, пропускаем его
            if (onesCount < 2)
                continue;

            // Заполняем столбец в матрице
            for (int j = 0; j < r; j++)
            {
                H[j, col] = binary[j] - '0';
            }

            col++;
        }

        // Заполняем единичную матрицу в правой части
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < r; j++)
            {
                H[i, n - r + j] = (i == j) ? 1 : 0;
            }
        }

        return H;
    }

    static int CountOnes(string binary)
    {
        int count = 0;
        foreach (char c in binary)
        {
            if (c == '1')
                count++;
        }
        return count;
    }

    static void PrintMatrix(int[,] matrix)
    {
        for (int i = 0; i < matrix.GetLength(0); i++)
        {
            for (int j = 0; j < matrix.GetLength(1); j++)
                Console.Write(matrix[i, j] + " ");
            Console.WriteLine();
        }
    }

    static void CalculateRedundantSymbols(string binaryMessage, int[,] H, int r)
    {
        int dataLength = binaryMessage.Length;
        // Подготовка вектора для бит данных (в виде массива целых чисел)
        int[] dataBits = new int[dataLength];
        for (int i = 0; i < dataLength; i++)
        {
            dataBits[i] = binaryMessage[i] - '0';
        }

        // Подготовка массива для избыточных символов
        int[] redundantSymbols = new int[r];

        // Вычисление избыточных символов с использованием матрицы Хемминга
        for (int i = 0; i < r; i++)
        {
            int sum = 0;
            for (int j = 0; j < dataLength; j++)
            {
                // Учитываем только соответствующие части H
                if (H[i, j] == 1)
                {
                    sum += dataBits[j];
                }
            }
            // Избыточный символ - это бит четности
            redundantSymbols[i] = sum % 2;
        }

        // Вывод вычисленных избыточных символов
        Console.WriteLine("\nВычисленные избыточные символы:");
        for (int i = 0; i < r; i++)
        {
            Console.WriteLine($"r{i + 1}: {redundantSymbols[i]}");
        }
    }

    static string EncodeHamming(string data, int n, int r)
    {
        // Создаем массив для кодированного сообщения
        char[] code = new char[n];
        int dataIdx = 0;

        // Заполняем массив кодированного сообщения
        for (int i = 0; i < n; i++)
        {
            if ((i & (i + 1)) == 0) // Проверка, является ли позиция избыточным битом
                code[i] = '0'; // Позиция избыточного бита
            else
                code[i] = data[dataIdx++]; // Заполнение битами данных
        }

        // Вычисляем избыточные символы
        int[] redundantSymbols = new int[r];
        for (int i = 0; i < r; i++)
        {
            int sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (((j + 1) & (1 << i)) != 0) // Проверка, включает ли текущая позиция избыточный бит
                    sum += (code[j] - '0');
            }
            redundantSymbols[i] = sum % 2; // Избыточный символ - это бит четности
        }

        // Формируем строку из исходных данных
        StringBuilder encodedMessage = new StringBuilder(data);

        // Добавляем избыточные символы в зеркальном порядке
        for (int i = r - 1; i >= 0; i--)
        {
            encodedMessage.Append(redundantSymbols[i]);
        }

        return encodedMessage.ToString(); // Возвращаем итоговое закодированное сообщение
    }

    static string IntroduceErrors(string data, int numErrors)
    {
        Random rnd = new Random();
        char[] corrupted = data.ToCharArray();
        for (int i = 0; i < numErrors; i++)
        {
            int errorPos;
            do { errorPos = rnd.Next(data.Length); }
            while (corrupted[errorPos] == 'X');
            corrupted[errorPos] = corrupted[errorPos] == '0' ? '1' : '0';
        }
        return new string(corrupted);
    }

    static void CalculateRedundantSymbolsWithErrors(string receivedMessage, int[,] H, int r)
    {
        int totalLength = receivedMessage.Length;
        // Подготовка вектора для закодированных бит (в виде массива целых чисел)
        int[] receivedBits = new int[totalLength];
        for (int i = 0; i < totalLength; i++)
        {
            receivedBits[i] = receivedMessage[i] - '0';
        }

        // Подготовка массива для новых избыточных символов
        int[] newRedundantSymbols = new int[r];

        // Вычисление новых избыточных символов с использованием матрицы Хемминга
        for (int i = 0; i < r; i++)
        {
            int sum = 0;
            for (int j = 0; j < totalLength; j++)
            {
                // Учитываем только соответствующие части H
                if (H[i, j] == 1)
                {
                    sum += receivedBits[j];
                }
            }
            // Новый избыточный символ - это бит четности
            newRedundantSymbols[i] = sum % 2;
        }

        // Вывод вычисленных новых избыточных символов
        Console.WriteLine("\nВычисленные новые избыточные символы (Yr'):");
        for (int i = 0; i < r; i++)
        {
            Console.WriteLine($"Yr{i + 1}: {newRedundantSymbols[i]}");
        }
    }

    //Синдром и исправление ошибки
    static void AnalyzeSyndrome(string receivedMessage, int[,] H, int r, int errorCount)
    {
        // Вычисляем новые избыточные символы
        int totalLength = receivedMessage.Length;
        int[] receivedBits = new int[totalLength];

        for (int i = 0; i < totalLength; i++)
        {
            receivedBits[i] = receivedMessage[i] - '0';
        }

        // Вычисляем синдром
        int[] syndrome = new int[r];
        for (int i = 0; i < r; i++)
        {
            int sum = 0;
            for (int j = 0; j < totalLength; j++)
            {
                if (H[i, j] == 1)
                {
                    sum += receivedBits[j];
                }
            }
            syndrome[i] = sum % 2;
        }

        // Вывод синдрома
        Console.WriteLine("\nСиндром:");
        for (int i = 0; i < r; i++)
        {
            Console.Write(syndrome[i] + " ");
        }
        Console.WriteLine();

        // Проверка на количество ошибок
        if (errorCount > 1)
        {
            Console.WriteLine("Наличие 2 ошибок. Исправить нельзя!");
            return; // Завершаем выполнение функции
        }

        // Проверка на наличие одной ошибки
        int errorPos = 0;
        for (int i = 0; i < r; i++)
        {
            if (syndrome[i] == 1)
            {
                errorPos += (1 << i);
            }
        }

        for (int j = 0; j < totalLength; j++)
        {
            // Проверяем, совпадает ли синдром с j-м столбцом H
            bool match = true;
            for (int i = 0; i < r; i++)
            {
                if (H[i, j] != syndrome[i])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                errorPos = j + 1; // +1 для 1-индексированной позиции
                break;
            }
        }

        // Исправление ошибки, если она найдена
        if (errorPos > 0)
        {
            Console.WriteLine($"Ошибка обнаружена на позиции: {errorPos}");
            receivedBits[errorPos - 1] ^= 1; // Исправление бита

            // Вывод исправленного сообщения
            Console.WriteLine("Исправленное сообщение:");
            foreach (var bit in receivedBits)
            {
                Console.Write(bit);
            }
            Console.WriteLine(); // Переход на новую строку
        }
        else
        {
            Console.WriteLine("Ошибок не обнаружено.");
        }
    }
}