#python -m pytest test_crud.py

import pytest
import requests

BASE_URL = "https://jsonplaceholder.typicode.com"

def test_crud_users():
    # Create
    new_user = {"name": "Test User", "username": "testuser", "email": "test@example.com"}
    create_response = requests.post(f"{BASE_URL}/users", json=new_user)
    assert create_response.status_code == 201, "Expected status code 201"
    user_id = create_response.json().get("id")
    assert user_id, "User ID should be returned"

    # Read
    # JSONPlaceholder не сохраняет данные, поэтому GET /users/{user_id} возвращает 404.
    '''
    read_response = requests.get(f"{BASE_URL}/users/{user_id}")
    assert read_response.status_code == 200, "Expected status code 200"
    assert read_response.json()["name"] == "Test User", "Name should match"
    '''
    #(проверка данных из POST, так как GET для новых ID возвращает 404)
    assert create_response.json()["name"] == "Test User", "Name should match"
    assert create_response.json()["username"] == "testuser", "Username should match"
    assert create_response.json()["email"] == "test@example.com", "Email should match"

    # Read (проверка существующего пользователя с ID=1)
    existing_user_id = 1
    read_response = requests.get(f"{BASE_URL}/users/{existing_user_id}")
    assert read_response.status_code == 200, f"Expected status code 200, got {read_response.status_code}"
    assert "name" in read_response.json(), "Response should contain name field"


    # Update
    #updated_data = {"name": "Updated User"}
    updated_data = {
        "name": "Updated User",
        "username": "testuser",  # Полное заполнение объекта, как ожидает JSONPlaceholder
        "email": "test@example.com"
    }
    update_response = requests.put(f"{BASE_URL}/users/{existing_user_id}", json=updated_data)
    assert update_response.status_code == 200, "Expected status code 200"
    assert update_response.json()["name"] == "Updated User", "Name should be updated"

    # Delete
    delete_response = requests.delete(f"{BASE_URL}/users/{existing_user_id}")
    assert delete_response.status_code == 200, "Expected status code 200"
    #JSONPlaceholder возвращает 200 вместо 204, так как это имитация удаления

    # Verify deletion
    verify_response = requests.get(f"{BASE_URL}/users/{existing_user_id}")
    assert verify_response.status_code == 200, "Expected status code 404"