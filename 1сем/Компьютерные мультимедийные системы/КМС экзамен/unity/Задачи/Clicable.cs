using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Clicable : MonoBehaviour
{
    void OnMouseDown()
    {
        Debug.Log("Object clicked: " + gameObject.name);
    }
}


