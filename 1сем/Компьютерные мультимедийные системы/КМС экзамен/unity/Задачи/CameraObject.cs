using UnityEngine;

public class CameraObject : MonoBehaviour
{
    public Transform target; // Целевой объект, вокруг которого будем вращаться
    public float distance = 5.0f; // Расстояние от камеры до объекта
    public float sensitivity = 5.0f; // Чувствительность мыши

    private float currentAngle = 0; // Текущий угол вокруг Y-оси
    private float currentHeight = 0; // Текущая высота

    void Update()
    {
        // Получаем ввод с мыши
        if (Input.GetMouseButton(1)) // Правый клик мыши
        {
            currentAngle += Input.GetAxis("Mouse X") * sensitivity;
            currentHeight -= Input.GetAxis("Mouse Y") * sensitivity;
            currentHeight = Mathf.Clamp(currentHeight, -20, 20); // Ограничиваем высоту
        }

        // Вычисляем новую позицию камеры
        Vector3 direction = new Vector3(0, currentHeight, -distance);
        Quaternion rotation = Quaternion.Euler(currentHeight, currentAngle, 0);
        transform.position = target.position + rotation * direction;

        // Направляем камеру на объект
        transform.LookAt(target);
    }
}