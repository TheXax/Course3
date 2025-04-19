# 1. Списки
print("Списки:")
fruits = ["apple", "banana", "cherry"]
print("Изначальный список:", fruits)

# Добавление элемента
fruits.append("orange")
print("После добавления элемента:", fruits)

# Удаление элемента
fruits.remove("banana")
print("После удаления элемента:", fruits)

# Индексация
print("Первый фрукт в списке:", fruits[0])

# 2. Кортежи
print("\nКортежи:")
colors = ("red", "green", "blue")
print("Изначальный кортеж:", colors)

# Индексация
print("Второй цвет в кортеже:", colors[1])

# Попытка изменить кортеж вызовет ошибку (кортежи неизменяемы)
# colors[1] = "yellow"

# 3. Словари
print("\nСловари:")
person = {
    "name": "Nika",
    "age": 19,
    "city": "Minsk"
}
print("Изначальный словарь:", person)

# Добавление новой пары ключ-значение
person["email"] = "nika@example.com"
print("После добавления email:", person)

# Изменение значения
person["age"] = 20
print("После изменения возраста:", person)

# Удаление пары ключ-значение
del person["city"]
print("После удаления города:", person)

# Доступ к значению по ключу
print("Имя человека:", person["name"])