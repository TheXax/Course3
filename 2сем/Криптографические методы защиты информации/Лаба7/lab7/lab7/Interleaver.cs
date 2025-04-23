using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class Interleaver
    {
        private int columns;

        public Interleaver(int columns)
        {
            this.columns = columns;
        }

        public bool[] Interleave(bool[] input)
        {
            int rows = (int)Math.Ceiling((double)input.Length / columns);
            bool[,] matrix = new bool[rows, columns];
            int index = 0;

            // Заполнение по строкам
            for (int r = 0; r < rows && index < input.Length; r++)
                for (int c = 0; c < columns && index < input.Length; c++)
                    matrix[r, c] = input[index++];

            // Считывание по столбцам
            List<bool> result = new();
            for (int c = 0; c < columns; c++)
                for (int r = 0; r < rows; r++)
                    result.Add(matrix[r, c]);

            return result.ToArray();
        }

        public bool[] Deinterleave(bool[] input)
        {
            int rows = (int)Math.Ceiling((double)input.Length / columns);
            bool[,] matrix = new bool[rows, columns];
            int index = 0;

            // Заполнение по столбцам
            for (int c = 0; c < columns && index < input.Length; c++)
                for (int r = 0; r < rows && index < input.Length; r++)
                    matrix[r, c] = input[index++];

            // Считывание по строкам
            List<bool> result = new();
            for (int r = 0; r < rows; r++)
                for (int c = 0; c < columns; c++)
                    result.Add(matrix[r, c]);

            return result.ToArray();
        }
    }

}
