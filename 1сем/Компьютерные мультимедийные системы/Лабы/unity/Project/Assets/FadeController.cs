using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FadeController : MonoBehaviour {
    private bool isActive = false; //активно ли затемнение
    public float timeUntilFade;
    public Animator animator;
    public GameObject mainCanvas;
    public GameObject simulatorInterface;
    public CameraMoverToPoint camMover;
    public CameraMoverToPoint moveBackwards;
    public CameraMoverToPoint currentMover;
    public CameraMove cameraMove;

    public void StartDellayedFadeAndMove()
    {
        StartCoroutine(Fade());
        isActive = true;
        currentMover = camMover;
    }

    public void HandleFadeEnd()
    {
        mainCanvas.SetActive(!isActive);
        simulatorInterface.SetActive(isActive);
        cameraMove.enabled = false;
        currentMover.SetSpeed(15);
        currentMover.MoveCamera();
    }

    public void HandleExit()
    {
        StartCoroutine(Fade());
        isActive = false;
        currentMover = moveBackwards;
    }

    private IEnumerator Fade()
    {
        yield return new WaitForSeconds(timeUntilFade); //приостанавливает выполнение на заданное время

        animator.SetTrigger("Fade"); //вызов анимации затемнения
    }
}
