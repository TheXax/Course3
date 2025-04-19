#Это пример задачи классификации (classification). Возможные ответы (различные сорта ириса) называются классами (classes).
#Cорт, к которому принадлежит цветок (конкретная точка данных), называется меткой (label)
import sys
import pandas as pds #для работы с табличными данными
import mglearn #инструменты для машинного обучения и визуализации
import matplotlib #для создания графиков и визуализаций данных
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp #функции для научных и инженерных расчетов
import IPython
import sklearn
#Загрузка набора данных Iris
from sklearn.datasets import load_iris
iris_dataset = load_iris() #Объект iris, возвращаемый load_iris, является объектом Bunch, который очень похож на словарь
print("Ключи iris_dataset: \n{}".format(iris_dataset.keys())) 
print(iris_dataset['DESCR'][:193] + "\n...")#Значение ключа DESCR – это краткое описание набора данных
print("Названия ответов: {}".format(iris_dataset['target_names'])) #Значение ключа target_names – это массив строк, содержащий сорта цветов
print("Названия признаков: \n{}".format(iris_dataset['feature_names'])) #feature_names – это список строк с описанием каждого признака
print("Тип массива data: {}".format(type(iris_dataset['data'])))
#В машинном обучении отдельные элементы называются примерами (samples), а их свойства – характеристиками или
#признаками (feature). Форма (shape) массива данных определяется количеством примеров, умноженным на количество признаков
print("Форма массива data: {}".format(iris_dataset['data'].shape)) #Строки в массиве data соответствуют цветам ириса, а столбцы представляют собой четыре признака
print("Первые пять строк массива data:\n{}".format(iris_dataset['data'][:5]))
print("Тип массива target: {}".format(type(iris_dataset['target']))) #Массив target содержит сорта уже измеренных цветов, тоже записанные в виде массива NumPy
print("Форма массива target: {}".format(iris_dataset['target'].shape)) #Значения чисел задаются массивом iris['target_names']: 0 – setosa, 1 – versicolor, а 2 – virginica
print("Ответы:\n{}".format(iris_dataset['target']))
#Для оценки эффективности модели, мы предъявляем ей новые размеченные данные (размеченные данные, которые она не видела раньше).
#Обычно это делается путем разбиения собранных размеченных данных (в данном случае 150 цветов) на две части.
#Одна часть данных используется для построения нашей модели машинного обучения и называется обучающими данными (training data) или обучающим набором (training set).
#Остальные данные будут использованы для оценки качества модели, их называют тестовыми данными (test data), тестовым набором (test set) или контрольным набором (hold-out set).


from sklearn.model_selection import train_test_split #перемешивает набор данных и разбивает его на две части

#Выводом функции train_test_split являются X_train, X_test, y_train и y_test, которые все являются массивами Numpy. X_train содержит 75% строк набора данных, а X_test содержит оставшиеся 25%:

X_train, X_test, y_train, y_test = train_test_split( #данные обозначаются заглавной X: метки обозначаются строчной у.
iris_dataset['data'], iris_dataset['target'], random_state=0) #генератор псевдослучайных чисел с фиксированным стартовым значением (чтобы в точности повторно воспроизвести полученный результат)
print("форма массива X_train: {}".format(X_train.shape))
print("форма массива y_train: {}".format(y_train.shape))
print("форма массива X_test: {}".format(X_test.shape))
print("форма массива y_test: {}".format(y_test.shape))


#матрица диаграмм рассеяния
iris_dataframe = pds.DataFrame(X_train, columns=iris_dataset.feature_names) #преобразовываем массив NumPy в DataFrame (основный тип данных в библиотеке pandas)
from pandas.plotting import scatter_matrix #В pandas есть функция для создания парных диаграмм рассеяния под названием scatter_matrix
grr = scatter_matrix(iris_dataframe, c=y_train, figsize=(15, 15), #создаем матрицу рассеяния из dataframe, цвет точек задаем с помощью y_trainmarker='o',
hist_kwds={'bins': 20}, s=60, alpha=.8, cmap=mglearn.cm3)
plt.show()