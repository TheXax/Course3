using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SwitchController : MonoBehaviour
{
    public Animator animator; // Ссылка на Animator
    private bool isOn = false; // Состояние выключателя

    // Метод, который вызывается при нажатии на выключатель
    public void ToggleSwitch()
    {
        isOn = !isOn; // Переключаем состояние
        animator.SetBool("SimulatorOn", isOn); // Устанавливаем значение переменной "turn"
    }

    // Метод для обработки нажатия на клавиши (можно использовать для тестирования)
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space)) // Нажмите пробел для переключения
        {
            ToggleSwitch();
        }
    }
}