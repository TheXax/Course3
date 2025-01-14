using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour
{
    public Transform centralObject; // Объектная переменная для центрального объекта
    public float rotationSpeed = 5f;
    public float moveSpeed = 5f;
    public int moveLimitX = 2; //Пределы перемещения по X
    public int moveLimitZ = 2; //Пределы перемещения по Z

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    private void Update()
    {
        // Вращение камеры вокруг центрального объекта
        if (Input.GetMouseButton(1)) // Правая кнопка мыши
        {
            float rotationX = Input.GetAxis("Mouse X") * rotationSpeed;
            transform.RotateAround(centralObject.position, Vector3.up, rotationX);
        }

        // Движение камеры в стороны с учетом ограничений
        float moveHorizontal = Input.GetAxis("Horizontal") * moveSpeed * Time.deltaTime; // A/D
        float moveVertical = Input.GetAxis("Vertical") * moveSpeed * Time.deltaTime; // W/S

        Vector3 newPosition = transform.position + transform.right * moveHorizontal + transform.forward * moveVertical;
        newPosition.x = Mathf.Clamp(newPosition.x, centralObject.position.x - moveLimitX, centralObject.position.x + moveLimitX);
        newPosition.z = Mathf.Clamp(newPosition.z, centralObject.position.z - moveLimitZ, centralObject.position.z + moveLimitZ);

        transform.position = newPosition;

        // Приближение и удаление камеры
        float scrollData = Input.GetAxis("Mouse ScrollWheel");
        transform.position += transform.forward * scrollData * moveSpeed;
    }
}