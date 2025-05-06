#3. Напишите автоматизированные тесты
import requests

#запрос с корректными параметрами
def test_get_users():
    response = requests.get('https://jsonplaceholder.typicode.com/users')
    assert response.status_code == 200
    assert isinstance(response.json(), list)  # Проверяем, что это список

#пропустк обязательных полей(для GET-запроса не применимо, можно протестировать с неправильным URL)
def test_get_invalid_user():
    response = requests.get('https://jsonplaceholder.typicode.com/users/9999')  # Не существующий ID
    assert response.status_code == 404  # Ожидаем 404 Not Found


#интеграционное тестирование методов CRUD
#Create
def create_user():
    url = 'https://jsonplaceholder.typicode.com/users'
    payload = {
        'name': 'John Doe',
        'username': 'johndoe',
        'email': 'john@example.com'
    }
    response = requests.post(url, json=payload)
    assert response.status_code == 201
    print(f"Created User: {response.json()}")  # Отладочный вывод
    return response.json()  # Возвращаем созданного пользователя


#Read
def get_user(user_id):
    response = requests.get(f'https://jsonplaceholder.typicode.com/users/{user_id}')
    print(f"Status Code: {response.status_code}")  # Отладочный вывод
    assert response.status_code == 200
    return response.json()  # Возвращаем данные пользователя


#Update
def update_user(user_id):
    url = f'https://jsonplaceholder.typicode.com/users/{user_id}'
    payload = {
        'name': 'Jane Doe'
    }
    response = requests.put(url, json=payload)
    assert response.status_code == 200
    return response.json()  # Возвращаем обновленные данные


#Delete
def delete_user(user_id):
    response = requests.delete(f'https://jsonplaceholder.typicode.com/users/{user_id}')
    assert response.status_code == 204  # Ожидаем 204 No Content



#Тестирование обработки ошибок
def test_empty_request():
    response = requests.post('https://jsonplaceholder.typicode.com/users', json={})  # Пустое тело
    assert response.status_code == 400  # Ожидаем 400 Bad Request


#Тестирование валидации данных
def test_long_string():
    payload = {
        'name': 'a' * 256  # Слишком длинная строка
    }
    response = requests.post('https://jsonplaceholder.typicode.com/users', json=payload)
    assert response.status_code == 400  # Ожидаем 400 Bad Request


#Тестирование пагинации
def test_pagination():
    response = requests.get('https://jsonplaceholder.typicode.com/users?_page=1&_limit=5')
    assert response.status_code == 200
    assert len(response.json()) <= 5  # Проверяем, что не больше 5 пользователей



#Выполнение тестов
if __name__ == "__main__":
    test_get_users()
    test_get_invalid_user()
    user = create_user()
    user_id = user['id']
    print(f"User ID: {user_id}")  # Отладочный вывод
    #print(get_user(user_id))
    #print(update_user(user_id))
    #delete_user(user_id)
    test_empty_request()
    test_long_string()
    test_pagination()