#python -m pytest test_3.py
import pytest
import requests

BASE_URL = "https://jsonplaceholder.typicode.com"

def test_get_users_positive():
    response = requests.get(f"{BASE_URL}/users")
    assert response.status_code == 200, "Expected status code 200"
    assert isinstance(response.json(), list), "Response should be a list"
    assert len(response.json()) > 0, "Users list should not be empty"

def test_get_user_by_id_positive():
    response = requests.get(f"{BASE_URL}/users/1")
    assert response.status_code == 200, "Expected status code 200"
    assert response.json()["id"] == 1, "User ID should be 1"

def test_get_user_nonexistent_negative():
    response = requests.get(f"{BASE_URL}/users/999")
    assert response.status_code == 404, "Expected status code 404"

def test_get_user_invalid_id_negative():
    response = requests.get(f"{BASE_URL}/users/abc")
    assert response.status_code == 400 or response.status_code == 404, "Expected error status code"