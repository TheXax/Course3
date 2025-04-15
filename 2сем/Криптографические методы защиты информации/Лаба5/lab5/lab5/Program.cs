using System;
using System.Collections.Generic;

class HammingApplication
{
    static void Main()
    {
        // Дефолтное двоичное представление информационного слова (32 бита)
        string input = "11010011001101010101011000100101"; // Замените на любое 32-битовое слово
        Console.WriteLine($"Используемое двоичное представление: {input}");
        int k = input.Length;

        // 1. Ввод двоичного представления в матрицу 4x8
        int[,] matrix = FillMatrix(input);
        PrintMatrix(matrix);

        // 2. Вычисление проверочных битов
        int[] parityBits = CalculateParityBits(matrix, 2); 
        Console.WriteLine($"Проверочные биты: {string.Join("", parityBits)}");

        // 3. Формирование кодового слова Xn
        string codeword = FormCodeword(input, parityBits);
        Console.WriteLine($"Кодовое слово Xn: {codeword}");

        // 4. Генерация ошибок
        //string erroneousCodeword = IntroduceErrors(codeword, 2); // Генерация 2 ошибок
        string erroneousCodeword = IntroduceErrors(codeword); // Генерация 2 ошибок

        Console.WriteLine($"Кодовое слово Yn: {erroneousCodeword}");

        // 5. Определение и исправление ошибок
        string correctedCodeword = CorrectErrors(erroneousCodeword, parityBits);
        Console.WriteLine($"Кодовое слов Yn': {correctedCodeword}");

        // 6. Анализ корректирующей способности
        AnalyzeErrorCorrection(codeword, correctedCodeword);
    }

    static int[,] FillMatrix(string input)
    {
        // Фиксированная матрица 4x8
        int[,] matrix = new int[4, 8];

        // Заполнение матрицы
        for (int i = 0; i < input.Length; i++)
        {
            matrix[i / 8, i % 8] = input[i] - '0';
        }

        return matrix;
    }

    static void PrintMatrix(int[,] matrix)
    {
        for (int i = 0; i < matrix.GetLength(0); i++)
        {
            for (int j = 0; j < matrix.GetLength(1); j++)
            {
                Console.Write(matrix[i, j] + " ");
            }
            Console.WriteLine();
        }
    }

    static int[] CalculateParityBits(int[,] matrix, int direction)
    {
        int rows = matrix.GetLength(0);
        int cols = matrix.GetLength(1);
        List<int> parityBits = new List<int>();

        // Проверка по строкам и запись паритетов сверху вниз
        for (int i = 0; i < rows; i++)
        {
            int sum = 0;
            for (int j = 0; j < cols; j++)
                sum += matrix[i, j];
            parityBits.Add(sum % 2); // Паритет для строки
        }

        // Проверка по столбцам и запись паритетов справа налево
        for (int j = cols - 1; j >= 0; j--)
        {
            int sum = 0;
            for (int i = 0; i < rows; i++)
            {
                sum += matrix[i, j]; // Суммируем по столбцу
            }
            parityBits.Add(sum % 2); // Паритет для столбца
        }

        return parityBits.ToArray();
    }

    static string FormCodeword(string input, int[] parityBits)
    {
        return input + string.Join("", parityBits);
    }

    static string IntroduceErrors(string codeword)
    {
        Random rnd = new Random();
        char[] corrupted = codeword.ToCharArray();

        // Генерация случайного количества ошибок от 0 до 2
        int errorCount = rnd.Next(0, 3); // 0, 1 или 2 ошибки
        Console.WriteLine($"Количество допущенных ошибок: {errorCount}");

        for (int i = 0; i < errorCount; i++)
        {
            int pos;
            do
            {
                pos = rnd.Next(corrupted.Length);
            } while (corrupted[pos] == 'X'); // Избегаем повторных позиций
            corrupted[pos] = corrupted[pos] == '0' ? '1' : '0'; // Меняем бит
        }

        return new string(corrupted);
    }

    static string CorrectErrors(string received, int[] parityBits)
    {
        int rows = 4; // Количество строк в матрице
        int cols = 8; // Количество столбцов в матрице
        int[] calculatedParityBits = new int[rows + cols];

        // 1. Вычисляем проверочные биты для полученного кода
        for (int i = 0; i < rows; i++)
        {
            int sum = 0;
            for (int j = 0; j < cols; j++)
                sum += received[i * cols + j] - '0';
            calculatedParityBits[i] = sum % 2; // Паритет для строки
        }

        for (int j = 0; j < cols; j++)
        {
            int sum = 0;
            for (int i = 0; i < rows; i++)
            {
                sum += received[i * cols + j] - '0'; // Суммируем по столбцу
            }
            calculatedParityBits[rows + j] = sum % 2; // Паритет для столбца
        }

        // 2. Определяем позицию ошибки
        int errorRow = -1;
        int errorCol = -1;

        for (int i = 0; i < rows; i++)
        {
            if (calculatedParityBits[i] != parityBits[i])
            {
                errorRow = i; // Найдена строка с ошибкой
                break;
            }
        }

        for (int j = 0; j < cols; j++)
        {
            if (calculatedParityBits[rows + j] != parityBits[rows + j])
            {
                errorCol = j; // Найден столбец с ошибкой
                break;
            }
        }

        // 3. Исправление ошибки, если она одна
        if (errorRow != -1 && errorCol != -1)
        {
            int errorPosition = errorRow * cols + errorCol; // Позиция ошибки
            char[] corrected = received.ToCharArray();
            corrected[errorPosition] = corrected[errorPosition] == '0' ? '1' : '0'; // Исправляем бит
            return new string(corrected);
        }

        // Если ошибки не найдены, возвращаем исходное слово
        return received;
    }

    static void AnalyzeErrorCorrection(string original, string corrected)
    {
        // Логика анализа корректирующей способности
        // Для простоты примера просто сравним слова
        if (original == corrected)
        {
            Console.WriteLine("Ошибки успешно исправлены.");
        }
        else
        {
            Console.WriteLine("Ошибки не были исправлены.");
        }
    }
}