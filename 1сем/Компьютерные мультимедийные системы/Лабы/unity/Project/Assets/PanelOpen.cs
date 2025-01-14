using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PanelOpen : MonoBehaviour {

	public bool IsOpen;
	 
	public GameObject Panel;

	public void ChangePanel()
	{
		IsOpen = !IsOpen;

		Panel.SetActive(IsOpen);
	}
}
