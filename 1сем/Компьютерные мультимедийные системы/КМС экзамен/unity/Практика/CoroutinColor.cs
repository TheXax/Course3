using UnityEngine;
using System.Collections;

public class CoroutinColor : MonoBehaviour
{
    // Метод Start вызывается при старте сцены
    void Start()
    {
        // Запуск корутины
        StartCoroutine(PerformActionsWithDelay());
    }

    // Корутина для задержки выполнения действий
    private IEnumerator PerformActionsWithDelay()
    {
        Debug.Log("Начало действия");

        // Меняем цвет объекта на красный
        GetComponent<Renderer>().material.color = Color.red;
        yield return new WaitForSeconds(2f);

        Debug.Log("Цвет изменен на красный");

        // Меняем цвет объекта на синий
        GetComponent<Renderer>().material.color = Color.blue;
        yield return new WaitForSeconds(3f);

        Debug.Log("Цвет изменен на синий");

        // Меняем цвет объекта на зеленый
        GetComponent<Renderer>().material.color = Color.green;
        yield return new WaitForSeconds(1f);

        Debug.Log("Цвет изменен на зеленый");

        // Завершаем выполнение
        Debug.Log("Действие завершено");
    }
}
