#2. Сформируйте список позитивных и негативных тест-кейсов
#python -m pytest test_api_user.py

import pytest
import requests

BASE_URL = "https://jsonplaceholder.typicode.com"

# Позитивные тест-кейсы
def test_get_users_no_params_positive():
    #Позитивный тест: GET /users без параметров возвращает список пользователей с кодом 200.
    response = requests.get(f"{BASE_URL}/users")
    assert response.status_code == 200, f"Expected status code 200, got {response.status_code}"
    assert isinstance(response.json(), list), "Response should be a list"
    assert len(response.json()) > 0, "Users list should not be empty"

def test_get_user_by_id_positive():
    #Позитивный тест: GET /users/1 возвращает данные пользователя с id=1 с кодом 200.
    response = requests.get(f"{BASE_URL}/users/1")
    assert response.status_code == 200, f"Expected status code 200, got {response.status_code}"
    assert response.json()["id"] == 1, f"Expected user ID 1, got {response.json()['id']}"
    assert "username" in response.json(), "Response should contain username field"

def test_get_users_with_filter_positive():
    #Позитивный тест: GET /users?username=Bret возвращает отфильтрованный список с кодом 200.
    response = requests.get(f"{BASE_URL}/users?username=Antonette")
    assert response.status_code == 200, f"Expected status code 200, got {response.status_code}"
    assert isinstance(response.json(), list), "Response should be a list"
    assert len(response.json()) == 1, "Expected one user in filtered list"
    assert response.json()[0]["username"] == "Antonette", "Expected username Antonette"

def test_get_users_with_valid_header_positive():
    #Позитивный тест: GET /users с заголовком Accept: application/json возвращает JSON с кодом 200.
    headers = {"Accept": "application/json"}
    response = requests.get(f"{BASE_URL}/users", headers=headers)
    assert response.status_code == 200, f"Expected status code 200, got {response.status_code}"
    assert response.headers["Content-Type"].startswith("application/json"), "Response should be JSON"

# Негативные тест-кейсы
def test_get_user_nonexistent_negative():
    #Негативный тест: GET /users/999 возвращает ошибку 404 "Not Found".
    response = requests.get(f"{BASE_URL}/users/999")
    assert response.status_code == 404, f"Expected status code 404, got {response.status_code}"

def test_get_user_invalid_id_negative():
    #Негативный тест: GET /users/abc возвращает ошибку 400 или 404 "Invalid ID".
    response = requests.get(f"{BASE_URL}/users/abc")
    assert response.status_code in [400, 404], f"Expected status code 400 or 404, got {response.status_code}"

def test_get_users_with_invalid_param_negative():
    #Негативный тест: GET /users?invalid_param=123 игнорирует некорректный параметр, возвращает код 200.
    response = requests.get(f"{BASE_URL}/users?invalid_param=123")
    assert response.status_code == 201, f"Expected status code 200, got {response.status_code}"
    assert isinstance(response.json(), list), "Response should still be a valid list"

def test_get_users_with_invalid_header_negative():
    #Негативный тест: GET /users с заголовком Accept: text/plain возвращает JSON с кодом 200.
    headers = {"Accept": "text/plain"}
    response = requests.get(f"{BASE_URL}/users", headers=headers)
    assert response.status_code == 201, f"Expected status code 200, got {response.status_code}"
    assert response.headers["Content-Type"].startswith("application/json"), "Response should remain JSON"