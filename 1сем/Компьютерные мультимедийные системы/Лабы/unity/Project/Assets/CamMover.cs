using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CamMover : MonoBehaviour {
    public float speed = 1.0f;

    public bool shouldMove;
    public bool shouldEnableMovement;

    public Transform Point;
    public Transform Component; 

    public void StartMovement(Transform point, Transform component)
    {
        Point = point;
        Component = component;

        gameObject.GetComponent<CameraMove>().enabled = false;
        shouldMove = true;

        Move();
    }

    public void Move()
    {
        gameObject.transform.position = Vector3.MoveTowards(gameObject.transform.position, Point.position, speed * Time.deltaTime);

        gameObject.transform.rotation = Quaternion.LookRotation(Component.position - gameObject.transform.position);

        if (Vector3.Distance(gameObject.transform.position, Point.position) < 0.01f)
        {
            shouldMove = false; 
            gameObject.GetComponent<CameraMove>().enabled = false;
            speed = 5;
        }
    }

    void Update()
    {
        if (shouldMove)
        {
            Move(); 
        }
    }
}
