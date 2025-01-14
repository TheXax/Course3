using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;


public class ComponentsButton : MonoBehaviour, IPointerEnterHandler, IPointerExitHandler
{
    public string Text;
    public Material DefaultMaterial;
    public Material OrangeMaterial;
    public GameObject Component;
    public Text InformField;
    public Image Button;
    public Color DefaultColor;
    public Color HighliteColor;

    private void Start()
    {
        Button = GetComponent<Image>();
    }

    public void OnPointerEnter(PointerEventData evenData)
    {
        Component.GetComponent<MeshRenderer>().material = OrangeMaterial;
        Button.color = HighliteColor;
        InformField.text = Text;
    }

    public void OnPointerExit(PointerEventData evenData)
    {
        Component.GetComponent<MeshRenderer>().material = DefaultMaterial;
        Button.color = DefaultColor;
        InformField.text = "";
    }

}
