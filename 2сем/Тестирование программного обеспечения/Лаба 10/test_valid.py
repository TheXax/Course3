#Тестирование валидации данных

#python -m pytest test_valid.py
import pytest
import requests

BASE_URL = "https://jsonplaceholder.typicode.com"

#JSONPlaceholder не ограничивает длину строк и возвращает 201, а не 400
def test_long_string_validation():
    long_string = "a" * 1000
    response = requests.post(f"{BASE_URL}/users", json={"name": long_string})
    assert response.status_code == 201, "Expected status code 400"
    # Проверка структуры ответа
    assert isinstance(response.json(), dict), "Response should be a dictionary"
    assert "id" in response.json(), "Response should contain user ID"
    assert response.json()["name"] == long_string, "Name should match the sent long string"

#JSONPlaceholder не проверяет тип данных для email и возвращает 201
def test_invalid_email_format():
    response = requests.post(f"{BASE_URL}/users", json={"name": "Test", "email": 123})
    assert response.status_code == 201, "Expected status code 400"
    # Проверка структуры ответа
    assert isinstance(response.json(), dict), "Response should be a dictionary"
    assert "id" in response.json(), "Response should contain user ID"
    assert response.json()["email"] == 123, "Email should match the sent value"

#JSONPlaceholder не считает name обязательным и возвращает 201
def test_missing_required_field():
    response = requests.post(f"{BASE_URL}/users", json={"email": "test@example.com"})
    assert response.status_code == 201, "Expected status code 400"
    # Проверка структуры ответа
    assert isinstance(response.json(), dict), "Response should be a dictionary"
    assert "id" in response.json(), "Response should contain user ID"
    assert "name" not in response.json() or response.json()["name"] is None, "Name should be absent or None"