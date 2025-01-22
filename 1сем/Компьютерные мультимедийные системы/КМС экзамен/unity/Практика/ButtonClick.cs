using UnityEngine;
using UnityEngine.UI; // Для работы с UI компонентами

public class ButtonClick : MonoBehaviour
{
    // Ссылка на кнопку
    public Button button;

    // Этот метод вызывается при старте
    void Start()
    {
        // Проверяем, что кнопка назначена
        if (button != null)
        {
            // Подключаем метод, который будет вызываться при клике
            button.onClick.AddListener(OnButtonClick);
        }
    }

    // Метод для обработки клика по кнопке
    void OnButtonClick()
    {
        Debug.Log("Кнопка была нажата!");
    }
}
