//платформа с кольцами
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CirclesController : MonoBehaviour
{
    public float maxX;
    public float minX;
    public float maxY;
    public float minY;
    public Transform platform;
    public Slider horizontalSlider;
    public Slider verticalSlider;

    private Vector3 initialPosition;

    void Start()
    {
        initialPosition = platform.position; //текущее положение

        //подписка на события изменения
        horizontalSlider.onValueChanged.AddListener(HandleHorizontalSlider);
        verticalSlider.onValueChanged.AddListener(HandleVerticalSlider);
    }

    public void HandleHorizontalSlider(float value)
    {
        float newX = initialPosition.x - value;

        newX = Mathf.Clamp(newX, initialPosition.x + minX, initialPosition.x + maxX); //ограничение диапазона

        platform.position = new Vector3(newX, platform.position.y, platform.position.z);
    }

    public void HandleVerticalSlider(float value)
    {
        float newY = initialPosition.z - value;

        newY = Mathf.Clamp(newY, initialPosition.z + minY, initialPosition.z + maxY);

        platform.position = new Vector3(platform.position.x, platform.position.y, newY);
    }
}