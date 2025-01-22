using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems; // Для обработки событий UI

public class ButtonOver : MonoBehaviour, IPointerEnterHandler, IPointerExitHandler
{
    public GameObject cylinder; // Ссылка на цилиндр

    

    // Метод, вызываемый при наведении курсора мыши на кнопку
    public void OnPointerEnter(PointerEventData eventData)
    {
        Debug.Log("Курсор на кнопке!");
        if (cylinder != null)
        {
            // Изменяем цвет цилиндра на зеленый
            cylinder.GetComponent<Renderer>().material.color = Color.yellow;
        }
    }

    // Метод, вызываемый при уходе курсора мыши с кнопки
    public void OnPointerExit(PointerEventData eventData)
    {
        Debug.Log("Курсор покинул кнопку!");
        if (cylinder != null)
        {
            // Изменяем цвет цилиндра на зеленый
            cylinder.GetComponent<Renderer>().material.color = Color.white;
        }
    }
}