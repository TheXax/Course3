using UnityEngine;

public class QuaternionZ : MonoBehaviour
{
    public float rotationSpeed = 50f; // Скорость вращения
    public Vector3 rotationAxis = new Vector3(0, 1, 0); // Ось вращения

    void Update()
    {
        // Вычисляем вращение по времени
        float angle = rotationSpeed * Time.deltaTime;

        // Создаем кватернион для вращения
        Quaternion rotation = Quaternion.AngleAxis(angle, rotationAxis);

        // Применяем вращение к объекту
        transform.rotation = rotation * transform.rotation;
    }
}