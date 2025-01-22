using UnityEngine;

public class HorizontalVertical : MonoBehaviour
{
    // Скорость движения
    public float moveSpeed = 5f;

    // Обновление каждый кадр
    void Update()
    {
        // Получение значений для горизонтальной и вертикальной оси
        float moveHorizontal = Input.GetAxis("Horizontal"); // Стрелки влево/вправ или клавиши A/D
        float moveVertical = Input.GetAxis("Vertical"); // Стрелки вверх/вниз или клавиши W/S

        // Двигаем объект, преобразуя оси в движение
        Vector3 movement = new Vector3(moveHorizontal, 0, moveVertical) * moveSpeed * Time.deltaTime;

        // Перемещаем объект
        transform.Translate(movement);
    }
}

