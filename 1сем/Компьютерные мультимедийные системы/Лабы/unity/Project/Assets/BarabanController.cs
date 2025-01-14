using UnityEngine;
using System.Collections.Generic;

public class BarabanController : MonoBehaviour
{
    public float rotationAngle = 72f;
    private int currentSection = 0;
    public float rotationSpeed = 200f;

    private Quaternion targetRotation;

    public List<Material> materials = new List<Material>(); //список материалов (цвета барабана)
    public List<float> lightLength = new List<float>(); //значения цветовой волны

    public GameObject indicator;

    public float CurrentLightLength { get { return lightLength[currentSection]; } } //возвращает длину света относительно индикатора

    void Start()
    {
        targetRotation = transform.rotation;
        UpdateIndicatorMaterial();
    }

    void OnMouseDown()
    {
        currentSection = (currentSection + 1) % materials.Count;
        float angle = currentSection * rotationAngle;
        targetRotation = Quaternion.Euler(0, 0, angle);
        UpdateIndicatorMaterial();
    }

    void Update()
    {
        transform.rotation = Quaternion.RotateTowards(transform.rotation, targetRotation, rotationSpeed * Time.deltaTime);
    }

    private void UpdateIndicatorMaterial()
    {
        if (materials.Count > 0 && indicator != null)
        {
            Renderer indicatorRenderer = indicator.GetComponent<Renderer>();
            if (indicatorRenderer != null)
            {
                indicatorRenderer.material = materials[currentSection];
            }
        }
    }
}