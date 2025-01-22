using UnityEngine;

public class QuaternionRotate : MonoBehaviour
{
    public float rotationSpeed = 50f;

    void Update()
    {
        // Вычисление угла поворота
        float angle = rotationSpeed * Time.deltaTime;

        // Создание кватерниона для поворота вокруг оси Y
        Quaternion rotation = Quaternion.Euler(0, angle, 0);

        // Применение поворота к текущему объекту
        transform.rotation *= rotation;
    }
}