import numpy as np

# 3.1. Создайте одномерный массив из 20 целых случайных чисел
array_1d = np.random.randint(0, 10, size=20)
print("Одномерный массив:", array_1d)

# 3.2. Преобразуйте массив в двумерный размером [4, 5]
array_2d = array_1d.reshape(4, 5)
print("Двумерный массив:\n", array_2d)

# 3.3. Разделите полученный массив на 2 массива
array_1 = array_2d[:, :3] 
array_2 = array_2d[:, 3:] 
print("Первый массив:\n", array_1)
print("Второй массив:\n", array_2)

# 3.4. Найдите все заданные значения в первом массиве, равные 6
values_equal_6 = array_1[array_1 == 6]
print("Значения равные 6:", values_equal_6)

# 3.5. Подсчитайте количество найденных элементов
count_of_sixes = len(values_equal_6)
print("Количество элементов равных 6:", count_of_sixes)

# 3.6. Во втором массиве найдите мин, макс и среднее
min_val = np.min(array_2)
max_val = np.max(array_2)
mean_val = np.mean(array_2)
print("Мин:", min_val, "Макс:", max_val, "Среднее:", mean_val)