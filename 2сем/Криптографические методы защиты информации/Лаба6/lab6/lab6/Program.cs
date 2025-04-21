using System;
using System.Text;
using System.Linq;

class Program
{
    //101010100000110100111100101101000010111010010101110010101
    static void Main(string[] args)
    {
        // Дефолтное слово Xk
        string Xk = "10101010101"; // Пример информационного слова
        Console.WriteLine($"Информационное слово Xk: {Xk}"); // Вывод Xk на консоль
        int r = 4; // Длина r     6
        StringBuilder Xn = new StringBuilder(Xk + new string('0', r)); // Временное Xn с добавленными нулями
        Console.WriteLine($"Временное слово Xn (с нулями): {Xn}");

        // Порождающий полином: C(x) = x^6 + x + 1        1, 0, 0, 0, 0, 1, 1
        int[] generatorPolynomial = { 1, 0, 0, 1, 1 }; // Коэффициенты полинома (от старшего к младшему)
        Console.WriteLine($"Порождающий полином: {string.Join("", generatorPolynomial)}");

        // Делим Xn на порождающий полином
        int[] XnPolynomial = ConvertToPolynomial(Xn.ToString());
        //Console.WriteLine($"Полином Xn в двоичном виде: {string.Join("", XnPolynomial.Reverse())}");

        // Вывод полинома Xn в виде x в степени
        Console.WriteLine($"Полином Xn в виде x в степени: {FormatPolynomial(XnPolynomial)}");

        int[] remainder = DividePolynomials(XnPolynomial, generatorPolynomial);
        Console.WriteLine($"Остаток от деления: {string.Join("", remainder.Reverse())}");

        // Записываем остаток в Xn
        for (int i = 0; i < remainder.Length; i++)
        {
            Xn[Xn.Length - 1 - i] = remainder[remainder.Length - 1 - i] == 1 ? '1' : '0';
        }

        Console.WriteLine("Закодированное слово Xn: " + Xn.ToString());

        // Определение матрицы G
        int[,] G = {
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1 }, //1
            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1 },
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
            { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
            { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
            { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
            { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1}, //11
        };

        // Определение матрицы H
        int[,] H = {
            { 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0 },
            { 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0},
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0 },
            { 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1},
        };

        // Вывод матрицы G
        Console.WriteLine("Матрица G:");
        PrintMatrix(G);

        // Вывод матрицы H
        Console.WriteLine("Матрица H:");
        PrintMatrix(H);

        // Генерация ошибок
        Random random = new Random();
        int errorCount = random.Next(0, 3); // Случайное количество ошибок от 0 до 2
        Console.WriteLine($"Количество ошибок: {errorCount}");

        // Вводим ошибки в Xn
        for (int i = 0; i < errorCount; i++)
        {
            int errorPosition = random.Next(0, Xn.Length); // Случайная позиция для ошибки
            Xn[errorPosition] = Xn[errorPosition] == '0' ? '1' : '0'; // Меняем бит
        }

        // Выводим закодированное слово с ошибками
        Console.WriteLine("Закодированное слово с ошибками: " + Xn.ToString());

        // Вывод сообщения об ошибках
        if (errorCount == 0)
        {
            Console.WriteLine("Ошибок нет.");
        }
        else if (errorCount == 1)
        {
            Console.WriteLine("Одна ошибка.");
            int[] YnPolynomial = ConvertToPolynomial(Xn.ToString());
            int[] syndrome = DividePolynomials(YnPolynomial, generatorPolynomial);
            Console.WriteLine($"Синдром: {string.Join("", syndrome.Reverse())}");

            // Логика исправления
            if (syndrome.Length > 0) // Если синдром не нулевой
            {
                // Определение позиции ошибки
                int errorPosition = FindErrorPosition(syndrome, H);
                if (errorPosition >= 0 && errorPosition < Xn.Length)
                {
                    // Исправляем ошибку
                    Xn[errorPosition] = Xn[errorPosition] == '0' ? '1' : '0';
                    Console.WriteLine($"Ошибка исправлена на позиции {errorPosition}. Исправленное слово: {Xn}");
                }
                else
                {
                    Console.WriteLine("Не удалось определить позицию ошибки.");
                }
            }
        }
        else
        {
            Console.WriteLine("Две ошибки. Мы не можем исправить.");
        }
    }

    static int[] ConvertToPolynomial(string binaryString)
    {
        int[] polynomial = new int[binaryString.Length];
        for (int i = 0; i < binaryString.Length; i++)
        {
            polynomial[i] = binaryString[i] - '0'; // Заполняем массив от старшего к младшему
        }
        return polynomial;
    }

    static string FormatPolynomial(int[] polynomial)
    {
        var terms = new System.Collections.Generic.List<string>();
        int firstNonZeroIndex = Array.FindIndex(polynomial, p => p == 1);

        // Если не найдено ни одной единицы
        if (firstNonZeroIndex == -1)
        {
            return "0"; // Полином равен нулю
        }

        // Обрабатываем только значащие нули
        for (int i = firstNonZeroIndex; i < polynomial.Length; i++)
        {
            if (polynomial[i] == 1)
            {
                int power = polynomial.Length - 1 - i; // Степень
                terms.Add($"x^{power}");
            }
        }

        // Если необходимо, добавьте обработку для x^0
        if (terms.Count == 0 || (terms.Count == 1 && terms[0] == "x^0"))
        {
            return "x^0"; // Обработка случая, когда есть только x^0
        }

        return string.Join(" + ", terms);
    }

    static int[] DividePolynomials(int[] dividend, int[] divisor)
    {
        int[] remainder = (int[])dividend.Clone();
        int divisorDegree = divisor.Length;

        for (int i = 0; i <= remainder.Length - divisorDegree; i++)
        {
            if (remainder[i] == 1) // Если старший коэффициент равен 1
            {
                for (int j = 0; j < divisorDegree; j++)
                {
                    remainder[i + j] ^= divisor[j]; // Вычисляем остаток с помощью XOR
                }
            }
        }

        // Удаляем ведущие нули в остатке
        int firstNonZeroIndex = Array.FindIndex(remainder, r => r == 1);
        if (firstNonZeroIndex == -1)
        {
            return new int[] { 0 }; // Остаток равен нулю
        }

        int[] trimmedRemainder = new int[remainder.Length - firstNonZeroIndex];
        Array.Copy(remainder, firstNonZeroIndex, trimmedRemainder, 0, trimmedRemainder.Length);
        return trimmedRemainder;
    }

    static void PrintMatrix(int[,] matrix)
    {
        int rows = matrix.GetLength(0);
        int cols = matrix.GetLength(1);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Console.Write(matrix[i, j] + " ");
            }
            Console.WriteLine();
        }
    }

    static int FindErrorPosition(int[] syndrome, int[,] H)
    {
        // Преобразуем синдром в целое число
        int syndromeValue = 0;
        for (int i = 0; i < syndrome.Length; i++)
        {
            syndromeValue = (syndromeValue << 1) | syndrome[i]; // Сдвигаем влево и добавляем бит
        }

        // Если синдром равен 0, значит, ошибок нет
        if (syndromeValue == 0)
        {
            return -1; // Указываем, что ошибок нет
        }

        // Поиск позиции ошибки в матрице H
        for (int col = 0; col < H.GetLength(1); col++)
        {
            bool match = true;

            // Сравниваем с каждым столбцом матрицы H
            for (int row = 0; row < H.GetLength(0); row++)
            {
                if (H[row, col] != syndrome[row])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                return col; // Возвращаем номер столбца как позицию ошибки
            }
        }

        return -1; // Если синдром не распознан, возвращаем -1
    }
}