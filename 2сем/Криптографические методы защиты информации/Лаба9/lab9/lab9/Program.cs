using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace HuffmanCoding
{
    public class HuffmanNode
    {
        public char Symbol { get; set; } //символ в узле
        public int Frequency { get; set; } //частота символа
        public HuffmanNode Left { get; set; } //ссылка на левого потомка
        public HuffmanNode Right { get; set; } //ссылка на правого потомка

        //инициализация
        public HuffmanNode(char symbol, int frequency)
        {
            Symbol = symbol;
            Frequency = frequency;
        }
    }

    public class HuffmanCoding
    {
        private HuffmanNode root; //корень дерева
        private Dictionary<char, string> huffmanCodes; //словарь символов

        //инициализация словаря
        public HuffmanCoding()
        {
            huffmanCodes = new Dictionary<char, string>();
        }

        //построение дерева
        public void BuildHuffmanTree(string text)
        {
            // Подсчет частоты каждого символа
            Dictionary<char, int> frequencies = new Dictionary<char, int>();
            foreach (char c in text)
            {
                if (!frequencies.ContainsKey(c))
                    frequencies[c] = 0;
                frequencies[c]++;
            }

            // Создание списка узлов
            List<HuffmanNode> nodes = frequencies.Select(kvp => new HuffmanNode(kvp.Key, kvp.Value)).ToList();

            // Построение дерева Хаффмана
            while (nodes.Count > 1)
            {
                nodes = nodes.OrderBy(node => node.Frequency).ToList(); //сортируем узлы по частоте
                //удаляем два узла с наименьшей частотой
                HuffmanNode left = nodes[0];
                HuffmanNode right = nodes[1];
                nodes.RemoveAt(0);
                nodes.RemoveAt(0);

                //создаём родительский узел и задаём частоту (сумма двух дочерних узлов)
                HuffmanNode parent = new HuffmanNode('\0', left.Frequency + right.Frequency)
                {
                    Left = left,
                    Right = right
                };

                nodes.Add(parent); //добавляем родительский узел в список
            }

            root = nodes.FirstOrDefault();
            GenerateCodes(root, "");
        }

        //генерация кодов для символов
        private void GenerateCodes(HuffmanNode node, string code)
        {
            if (node == null)
                return;

            if (node.Symbol != '\0')
                huffmanCodes[node.Symbol] = code;

            GenerateCodes(node.Left, code + "0"); //для левого узла 0
            GenerateCodes(node.Right, code + "1"); //для правого узла 1
        }


        //кодированная строка
        public string Encode(string text)
        {
            StringBuilder encoded = new StringBuilder();
            foreach (char c in text)
            {
                encoded.Append(huffmanCodes[c]);
            }
            return encoded.ToString();
        }

        //декодирование
        public string Decode(string encoded)
        {
            StringBuilder decoded = new StringBuilder();
            HuffmanNode current = root;

            foreach (char bit in encoded)
            {
                current = bit == '0' ? current.Left : current.Right;

                if (current.Symbol != '\0')
                {
                    decoded.Append(current.Symbol);
                    current = root;
                }
            }

            return decoded.ToString();
        }

        //возвращаем декодированную строку
        public Dictionary<char, string> GetHuffmanCodes()
        {
            return huffmanCodes;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            string input = "Вероника Стрелковская";
            Console.WriteLine($"Исходный текст: {input}");

            HuffmanCoding huffman = new HuffmanCoding();
            huffman.BuildHuffmanTree(input);

            // Вывод кодов Хаффмана для каждого символа
            Console.WriteLine("\nКоды Хаффмана для символов:");
            foreach (var code in huffman.GetHuffmanCodes())
            {
                Console.WriteLine($"Символ: {code.Key}, Код: {code.Value}");
            }

            // Кодирование
            string encoded = huffman.Encode(input);
            Console.WriteLine($"\nЗакодированный текст: {encoded}");

            // Декодирование
            string decoded = huffman.Decode(encoded);
            Console.WriteLine($"Декодированный текст: {decoded}");

            // Проверка корректности
            Console.WriteLine($"\nДекодированный текст совпадает с исходным: {input == decoded}");
        }
    }
}