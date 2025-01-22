using UnityEngine;

public class SoundManager : MonoBehaviour
{
    // Ссылка на AudioSource для воспроизведения звука
    public AudioSource audioSource;
    public AudioClip soundClip1; // Звук 1
    public AudioClip soundClip2; // Звук 2
    private bool isPlayingSound1 = false;

    void Start()
    {
        // Устанавливаем начальный звук
        audioSource.Play();
    }

    void Update()
    {
        // Переключение звуков при нажатии клавиш
        if (Input.GetKeyDown(KeyCode.Space)) // При нажатии Space переключаем звук
        {
            if (isPlayingSound1)
            {
                audioSource.clip = soundClip2;
            }
            else
            {
                audioSource.clip = soundClip1;
            }
            isPlayingSound1 = !isPlayingSound1;
            audioSource.Play();
        }
    }
}
