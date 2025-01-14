using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Help : MonoBehaviour, IPointerExitHandler
{

	public bool IsOpen;

	public GameObject helpWindow;

	public void UpdateWindow()
	{
		IsOpen = !IsOpen;

		helpWindow.SetActive(IsOpen);
	}

	public void OnPointerExit(PointerEventData eventData)
	{
        IsOpen = false;

        helpWindow.SetActive(IsOpen);
	}
}
