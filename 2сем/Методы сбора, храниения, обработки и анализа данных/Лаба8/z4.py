import numpy as np
import pandas as pd

# Создание одномерного массива из 20 целых случайных чисел
array_1d = np.random.randint(0, 10, size=20)
print("Одномерный массив:", array_1d)

# Создание объектов Series
series_from_array = pd.Series(array_1d)
series_from_dict = pd.Series({'a': 1, 'b': 2, 'c': 3})

print("Series из массива:\n", series_from_array)
print("Series из словаря:\n", series_from_dict)

# Математические операции с Series
print("Сумма Series:", series_from_array.sum())
print("Среднее Series:", series_from_array.mean())

# Создание объектов DataFrame из массива NumPy и словаря
df_from_array = pd.DataFrame(array_1d.reshape(4, 5))
df_from_dict = pd.DataFrame({'col1': [1, 2], 'col2': [3, 4]})

print("DataFrame из массива:\n", df_from_array)
print("DataFrame из словаря:\n", df_from_dict)