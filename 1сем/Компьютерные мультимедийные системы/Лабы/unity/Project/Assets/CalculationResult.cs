using System;
using UnityEngine;
using UnityEngine.UI;

public struct CalculationResult
{
    public float Nm;
    public float Dm;
    public float Dm2;
    public float LightLength;

    public CalculationResult(float nm, float dm, float dm2, float lightLength)
    {
        Nm = nm;
        Dm = dm;
        Dm2 = dm2;
        LightLength = lightLength;
    }
}

[Serializable]
public class Row
{
    public Text Number;
    public Text Nm;
    public Text Dm;
    public Text Dm2;
    public Text R;
}
