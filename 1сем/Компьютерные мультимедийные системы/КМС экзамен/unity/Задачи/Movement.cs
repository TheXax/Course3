using UnityEngine;

public class Movement: MonoBehaviour
{
    public float moveSpeed = 5f; // Скорость движения
    public float rotateSpeed = 100f; // Скорость вращения

    void Update()
    {
        // Получаем ввод с клавиатуры
        float move = Input.GetAxis("Vertical") * moveSpeed * Time.deltaTime; // Вперед/Назад
        float rotate = Input.GetAxis("Horizontal") * rotateSpeed * Time.deltaTime; // Влево/Вправо

        // Двигаем объект
        transform.Translate(0, 0, move);

        // Вращаем объект
        transform.Rotate(0, -rotate, 0);
    }
}