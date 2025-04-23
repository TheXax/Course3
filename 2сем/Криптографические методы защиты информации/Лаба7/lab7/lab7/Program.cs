using lab7;

int messageLengthBits = 14 * 8; // 14 байт
int[] burstLengths = { 4, 6, 8 };
int testCount = 30;

ShowStepByStepTest(burstLengths[0]);

Console.WriteLine("Анализ восстановления при пакетных ошибках в коде Хемминга (9,5)\n");

foreach (int burst in burstLengths)
{
    Console.WriteLine($"Тестирование при длине ошибки {burst} бит:");

    Analyzer analyzer = new();
    ErrorGenerator generator = new();
    Interleaver interleaver = new(columns: 9); // 9 — длина закодированного блока

    List<(bool[] original, bool[] recovered)> results = new();

    for (int i = 0; i < testCount; i++)
    {
        // 1. Генерация исходного сообщения
        bool[] originalMessage = GenerateRandomBits(messageLengthBits);

        // 2. Кодирование
        bool[] encoded = HammingEncoder.Encode(originalMessage);

        // 3. Перемежение
        bool[] interleaved = interleaver.Interleave(encoded);

        // 4. Внесение пакетной ошибки
        bool[] corrupted = generator.InjectGroupError(interleaved, burst);

        // 5. Деперемежение
        bool[] deinterleaved = interleaver.Deinterleave(corrupted);

        // 6. Декодирование
        bool[] decoded = HammingEncoder.Decode(deinterleaved);

        // 7. Сравнение
        results.Add((originalMessage, decoded));
    }

    analyzer.Analyze(results);
    Console.WriteLine();
}

Console.WriteLine("Анализ завершён.");
        

        /// <summary>
        /// Генерация случайного массива бит заданной длины.
        /// </summary>
bool[] GenerateRandomBits(int count)
{
    Random rnd = new();
    return Enumerable.Range(0, count).Select(_ => rnd.Next(2) == 1).ToArray();
}


void ShowStepByStepTest(int burstLength)
{
    int messageLengthBits = 14 * 8;
    ErrorGenerator generator = new();
    Interleaver interleaver = new(columns: 9);
    Analyzer analyzer = new();

    // 1. Сгенерировать исходное сообщение
    bool[] original = GenerateRandomBits(messageLengthBits);
    Console.WriteLine("1. Исходное сообщение:");
    PrintBits(original);

    // 2. Закодировать сообщение (Hamming)
    bool[] encoded = HammingEncoder.Encode(original);
    Console.WriteLine("\n2. Закодированное сообщение (Hamming):");
    PrintBits(encoded);

    // 3. Перемежение
    bool[] interleaved = interleaver.Interleave(encoded);
    Console.WriteLine("\n3. После перемежения:");
    PrintBits(interleaved);

    // 4. Внесение групповой ошибки
    bool[] corrupted = generator.InjectGroupError(interleaved, burstLength);
    Console.WriteLine($"\n4. Повреждённое сообщение (ошибка {burstLength} бита):");
    PrintBits(corrupted);

    // 5. Деперемежение
    bool[] deinterleaved = interleaver.Deinterleave(corrupted);
    Console.WriteLine("\n5. После деперемежения:");
    PrintBits(deinterleaved);

    // 6. Декодирование
    bool[] decoded = HammingEncoder.Decode(deinterleaved);
    Console.WriteLine("\n6. Декодированное сообщение:");
    PrintBits(decoded);

    // 7. Сравнение
    int errors = analyzer.CompareMessages(original, decoded);
    Console.WriteLine($"\n7. Ошибок после декодирования: {errors}");
}

static void PrintBits(bool[] bits, int group = 8)
{
    for (int i = 0; i < bits.Length; i++)
    {
        Console.Write(bits[i] ? "1" : "0");
        if ((i + 1) % group == 0) Console.Write(" ");
    }
    Console.WriteLine();
}
