using UnityEngine;
using UnityEngine.UI;

public class PanelOpen : MonoBehaviour
{
    public GameObject textWindow; // Ссылка на текстовое окно

    public void ToggleTextWindow()
    {
        // Меняем состояние текстового окна
        textWindow.SetActive(!textWindow.activeSelf);
    }
}