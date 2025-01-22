using UnityEngine;

public class EnterExit : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        // Проверяем, если объект - это Player
        if (other.gameObject.CompareTag("TriggerPlayer"))
        {
            // Изменяем цвет объекта триггера на красный
            other.GetComponent<Renderer>().material.color = Color.red;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        // Проверяем, если объект - это Player
        if (other.gameObject.CompareTag("TriggerPlayer"))
        {
            // Изменяем цвет объекта триггера обратно на белый
            other.GetComponent<Renderer>().material.color = Color.white;
        }
    }
}
