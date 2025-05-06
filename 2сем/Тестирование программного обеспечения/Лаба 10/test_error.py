#Тестирование обработки ошибок
#python -m pytest test_error.py

import pytest
import requests

BASE_URL = "https://jsonplaceholder.typicode.com"

#JSONPlaceholder принимает пустое тело как валидное и возвращает 201, а не 400
def test_empty_body_error():
    response = requests.post(f"{BASE_URL}/users", json={})
    assert response.status_code == 201, "Expected status code 400"

def test_invalid_format_error():
    invalid_data = {"name": None, "username": 123, "email": []}  # Некорректные типы данных
    response = requests.post(f"{BASE_URL}/users", json=invalid_data)
    assert response.status_code == 201, "Expected status code 400"

def test_nonexistent_endpoint():
    response = requests.get(f"{BASE_URL}/invalid")
    assert response.status_code == 404, "Expected status code 404"



#JSONPlaceholder не поддерживает аутентификацию - ДЛЯ СЛЕДУЮЩЕГО ЗАДАНИЯ: НАПИСАНО, ЧТО "Протестируйте ограничения доступа (если в вашем примере это возможно)"