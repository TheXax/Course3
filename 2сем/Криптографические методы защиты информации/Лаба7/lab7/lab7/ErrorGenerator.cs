using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class ErrorGenerator
    {
        private Random random = new();

        public bool[] InjectGroupError(bool[] input, int groupSize)
        {
            int maxStart = input.Length - groupSize;
            int startIndex = random.Next(0, maxStart + 1);
            bool[] corrupted = (bool[])input.Clone();

            for (int i = 0; i < groupSize; i++)
                corrupted[startIndex + i] = !corrupted[startIndex + i]; // Инвертируем бит

            return corrupted;
        }

        public List<bool[]> GenerateMultipleCorruptedSequences(bool[] original, int groupSize, int count)
        {
            List<bool[]> result = new();
            for (int i = 0; i < count; i++)
            {
                result.Add(InjectGroupError(original, groupSize));
            }
            return result;
        }
    }

}
