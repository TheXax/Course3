using UnityEngine;

public class MouseClick : MonoBehaviour
{
    // Флаг, который отслеживает текущий цвет объекта
    private bool isRed = false;

    // Метод Update вызывается каждый кадр
    void Update()
    {
        // Проверяем, был ли произведен клик левой кнопкой мыши
        if (Input.GetMouseButtonDown(0))
        {
            // Создаем луч от камеры к позиции мыши
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;

            // Проверяем, попал ли луч в какой-либо объект
            if (Physics.Raycast(ray, out hit))
            {
                // Если луч попал в объект, выводим его имя в консоль
                Debug.Log("Вы кликнули на объект: " + hit.collider.gameObject.name);

                // Если объект не был красным, меняем его цвет на красный
                if (isRed)
                {
                    hit.collider.gameObject.GetComponent<Renderer>().material.color = Color.white;
                }
                else
                {
                    hit.collider.gameObject.GetComponent<Renderer>().material.color = Color.red;
                }

                // Переключаем состояние флага
                isRed = !isRed;
            }
        }
    }
}
