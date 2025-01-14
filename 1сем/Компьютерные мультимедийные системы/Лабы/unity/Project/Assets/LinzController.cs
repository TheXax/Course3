using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LinaController : MonoBehaviour
{
    public Animator lensAnimator; // Ссылка на Animator линзы
    public Transform handle4; // Ссылка на ручку 4
    public Transform handle8; // Ссылка на ручку 8
    private float rotationSpeed = 100f; // Скорость вращения

    void Update()
    {
        // Вращение ручки 4
        if (Input.GetKey(KeyCode.T))
        {
            handle4.Rotate(Vector3.up, -rotationSpeed * Time.deltaTime); // Влево
            lensAnimator.SetBool("left_right", true);
        }
        else if (Input.GetKey(KeyCode.Y))
        {
            handle4.Rotate(Vector3.up, rotationSpeed * Time.deltaTime); // Вправо
            lensAnimator.SetBool("left_right", false);
        }

        // Вращение ручки 8
        if (Input.GetKey(KeyCode.G))
        {
            handle8.Rotate(Vector3.right, -rotationSpeed * Time.deltaTime); // Вниз
            lensAnimator.SetBool("down_up", true);
        }
        else if (Input.GetKey(KeyCode.H))
        {
            handle8.Rotate(Vector3.right, rotationSpeed * Time.deltaTime); // Вверх
            lensAnimator.SetBool("down_up", false);
        }

        // Если не нажаты клавиши, сбрасываем анимацию
        if (!Input.GetKey(KeyCode.T) && !Input.GetKey(KeyCode.Y))
        {
            lensAnimator.SetBool("left_right", false);
        }
        if (!Input.GetKey(KeyCode.G) && !Input.GetKey(KeyCode.H))
        {
            lensAnimator.SetBool("down_up", false);
        }
    }
}