#python -m pytest test_pagin.py

import pytest
import requests

BASE_URL = "https://jsonplaceholder.typicode.com"

def test_pagination():
    response = requests.get(f"{BASE_URL}/users?id=1")
    assert response.status_code == 200, "Expected status_code 200"
    assert len(response.json()) == 1, "Expected one user"

def test_out_of_range_pagination():
    response = requests.get(f"{BASE_URL}/users?id=999")
    assert response.status_code == 200, "Expected status code 200"
    assert len(response.json()) == 0, "Expected empty list"