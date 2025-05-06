#1. Получите список доступных методов API

#Для JSONPlaceholder доступные конечные точки: /users, /posts, /comments, и т.д. Методы: GET, POST, PUT, DELETE.
#python connect.py
import requests

response = requests.get("https://jsonplaceholder.typicode.com/users")
print(response.status_code)  # 200
print(response.json())  # Список пользователей