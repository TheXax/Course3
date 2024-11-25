using System;
using System.Net.Http;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Calculator
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private async void CalculateResult(object sender, EventArgs args)
        {
            string firstNum = _firstNum.Text;
            string secondNum = _secondNum.Text;

            int result = await GetResultFromServer(firstNum, secondNum);

            _resultField.Text = result.ToString();
        }

        private async Task<int> GetResultFromServer(string firstNum, string secondNum)
        {
            string serverSumCalculationPath = $@"https://localhost:7271/getSum?ParamA={firstNum}&ParamB={secondNum}";

            try
            {
                using (HttpClient client = new HttpClient())
                {
                    HttpResponseMessage response = await client.PostAsync(serverSumCalculationPath, null);

                    response.EnsureSuccessStatusCode();

                    var responseBody = await response.Content.ReadAsStringAsync();

                    return int.Parse(responseBody);
                }
            }
            catch (Exception exception)
            {
                return 0;
            }
        }

    }
}
