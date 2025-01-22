using UnityEngine;

public class MouseClick : MonoBehaviour
{
    private Renderer objectRenderer;

    void Start()
    {
        // Получаем компонент Renderer объекта
        objectRenderer = GetComponent<Renderer>();
    }

    void OnMouseDown()
    {
        // Генерируем случайный цвет
        Color newColor = new Color(Random.value, Random.value, Random.value);
        // Применяем новый цвет к материалу объекта
        objectRenderer.material.color = newColor;
    }
}
