using UnityEngine;
using System.Collections.Generic;
using UnityEngine.UI;

public class TableController : MonoBehaviour
{
    public BarabanController barabanController;

    public InputField nmInputField; //значение, введённое пользователем

    public float gamma = 2.83e-5f; // γ = 2.83 · 10^-5
    public float m = 1f; // Примерное значение m

    public int currentIndex = 0; //текущее значение в списке результатов

    private List<CalculationResult> results = new List<CalculationResult>(); //сохранение всех расчётов
    public List<Row> resultsText = new List<Row>();

    public void CalculateAndSave()
    {
        float nm;
        if (float.TryParse(nmInputField.text, out nm))
        {
            float lightLength = barabanController.CurrentLightLength; //получение значения цвета от барабана

            // Вычисляем Dm и Dm2
            float Dm = nm * gamma;
            float Dm2 = 4 * m * lightLength * lightLength;

            //сохраняем результаты
            CalculationResult result = new CalculationResult(nm, Dm, Dm2, lightLength);
            results.Add(result);

            //заполнение таблицы Canvas
            resultsText[currentIndex].Number.text = (currentIndex + 1).ToString();
            resultsText[currentIndex].Nm.text = nm.ToString();
            resultsText[currentIndex].Dm.text = Dm.ToString();
            resultsText[currentIndex].Dm2.text = Dm2.ToString();

            if (currentIndex > 0)
            {
                CalculationResult prevResult = results[currentIndex - 1]; //предыдущий результат
                float R = (((Mathf.Abs(D2(Dm2) - D2(prevResult.Dm2)))) / (4 * (nm - prevResult.Nm) * lightLength));
                Debug.Log(nm + " " + prevResult.Nm + " " + lightLength);

                resultsText[currentIndex].R.text = R.ToString();
            }
            else
            {
                resultsText[currentIndex].R.text = "-";
            }

            currentIndex++;
        }
        else
        {
            Debug.LogError("Некорректный ввод Nm. Убедитесь, что вы ввели число.");
        }
    }

    public void ClearResults()
    {
        results.Clear();
        currentIndex = 0;

        foreach (var row in resultsText)
        {
            row.Number.text = "";
            row.Nm.text = "";
            row.Dm.text = "";
            row.Dm2.text = "";
            row.R.text = "";
        }
    }

    private float D2(float value)
    {
        return value * value;
    }
}