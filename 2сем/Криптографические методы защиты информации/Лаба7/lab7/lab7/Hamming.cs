public static class HammingEncoder
{
    /// <summary>
    /// Кодирует весь массив данных (массив bool) с использованием Hamming(9,5).
    /// </summary>
    public static bool[] Encode(bool[] data)
    {
        List<bool> encoded = new();

        for (int i = 0; i < data.Length; i += 5)
        {
            var block = data.Skip(i).Take(5).ToArray();
            encoded.AddRange(EncodeBlock(block));
        }

        return encoded.ToArray();
    }

    /// <summary>
    /// Декодирует массив данных, исправляя одиночные ошибки. Возвращает восстановленные информационные биты.
    /// </summary>
    public static bool[] Decode(bool[] encodedData)
    {
        List<bool> decoded = new();

        for (int i = 0; i < encodedData.Length; i += 9)
        {
            var block = encodedData.Skip(i).Take(9).ToArray();
            decoded.AddRange(DecodeBlock(block));
        }

        return decoded.ToArray();
    }

    /// <summary>
    /// Кодирует 5-битный блок в 9-битный код Хемминга.
    /// </summary>
    private static bool[] EncodeBlock(bool[] data)
    {
        bool[] block = new bool[9];

        // data bits
        block[2] = data.ElementAtOrDefault(0); // D1
        block[4] = data.ElementAtOrDefault(1); // D2
        block[5] = data.ElementAtOrDefault(2); // D3
        block[6] = data.ElementAtOrDefault(3); // D4
        block[8] = data.ElementAtOrDefault(4); // D5

        // parity bits (Hamming-style)
        block[0] = block[2] ^ block[4] ^ block[6]; // P1
        block[1] = block[2] ^ block[5] ^ block[6]; // P2
        block[3] = block[4] ^ block[5] ^ block[6]; // P3
        block[7] = block[8] ^ block[2] ^ block[5]; // P4 (extra parity)

        return block;
    }

    /// <summary>
    /// Декодирует 9-битный блок, исправляя одиночные ошибки.
    /// Возвращает только информационные биты (5 штук).
    /// </summary>
    private static bool[] DecodeBlock(bool[] block)
    {
        if (block.Length < 9) return new bool[0]; // Некорректный блок

        bool[] copy = (bool[])block.Clone();

        // Проверочные индексы:
        bool p1 = copy[0];
        bool p2 = copy[1];
        bool p3 = copy[3];
        bool p4 = copy[7];

        bool d1 = copy[2];
        bool d2 = copy[4];
        bool d3 = copy[5];
        bool d4 = copy[6];
        bool d5 = copy[8];

        int syndrome = 0;
        if (p1 ^ d1 ^ d2 ^ d4) syndrome += 1;
        if (p2 ^ d1 ^ d3 ^ d4) syndrome += 2;
        if (p3 ^ d2 ^ d3 ^ d4) syndrome += 4;
        if (p4 ^ d5 ^ d1 ^ d3) syndrome += 8;

        if (syndrome > 0 && syndrome <= 9)
        {
            // Исправляем ошибку
            int index = syndrome - 1;
            copy[index] = !copy[index];
        }

        return new bool[]
        {
            copy[2], // D1
            copy[4], // D2
            copy[5], // D3
            copy[6], // D4
            copy[8], // D5
        };
    }
}
