using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class ButoonPraktika : MonoBehaviour {

    public string Text;

    public Text Information;

    public void OutputInformation()
    {
        Information.text = Text;
    }
}
