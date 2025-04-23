using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class Analyzer
    {
        public int CompareMessages(bool[] original, bool[] recovered)
        {
            int errors = 0;
            for (int i = 0; i < Math.Min(original.Length, recovered.Length); i++)
            {
                if (original[i] != recovered[i])
                    errors++;
            }
            return errors;
        }

        public void Analyze(List<(bool[] original, bool[] corrupted)> tests)
        {
            int total = tests.Count;
            int success = 0;

            foreach (var (original, corrupted) in tests)
            {
                int err = CompareMessages(original, corrupted);
                if (err == 0)
                    success++;
            }

            Console.WriteLine($"Успешно восстановлено: {success}/{total}");
            Console.WriteLine($"Эффективность: {(double)success / total:P2}");
        }

        

    }

}
