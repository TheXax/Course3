using UnityEngine;

public class PrefabSpawner : MonoBehaviour
{
    public GameObject cubePrefab; // Шаблон объекта

    void Update()
    {
        // Проверка нажатия клавиши P
        if (Input.GetKeyDown(KeyCode.P))
        {
            // Создание экземпляра объекта из шаблона
            Instantiate(cubePrefab, new Vector3(Random.Range(-5f, 5f), 1, Random.Range(-5f, 5f)), Quaternion.identity);
        }
    }
}