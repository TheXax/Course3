using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMoverToPoint : MonoBehaviour {
    public Transform Point;
    public Transform Component;

    public CamMover camera;

    public void MoveCamera()
    {
        camera.StartMovement(Point, Component);
        camera.GetComponent<CameraMove>().enabled = false;
    }

    public void SetSpeed(float speedOneTime)
    {
        camera.speed = speedOneTime;
    }
}
