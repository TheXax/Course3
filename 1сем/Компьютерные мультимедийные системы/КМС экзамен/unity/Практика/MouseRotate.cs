using UnityEngine;

public class MouseRotate : MonoBehaviour
{
    public float rotationSpeed = 100f;

    void Update()
    {
        // Получение движений мыши
        float mouseX = Input.GetAxis("Mouse X") * rotationSpeed * Time.deltaTime;
        float mouseY = Input.GetAxis("Mouse Y") * rotationSpeed * Time.deltaTime;

        // Поворот объекта вокруг осей Y и X
        transform.Rotate(Vector3.up, -mouseX);
        transform.Rotate(Vector3.left, -mouseY);
    }
}