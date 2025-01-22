using UnityEngine;

public class RotateObject : MonoBehaviour
{
    public float rotationSpeed = 100f; // Скорость вращения

    void Update()
    {
        // Получаем ввод с клавиатуры
        float rotateX = Input.GetAxis("Vertical") * rotationSpeed * Time.deltaTime; // Вращение по оси X
        float rotateY = Input.GetAxis("Horizontal") * rotationSpeed * Time.deltaTime; // Вращение по оси Y

        // Вращаем объект
        transform.Rotate(-rotateX, -rotateY, 0);
    }
}