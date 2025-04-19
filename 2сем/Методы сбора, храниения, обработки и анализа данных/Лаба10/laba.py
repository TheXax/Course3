import pandas as pds # для работы с табличными данными
import mglearn #инструменты для машинного обучения и визуализации данных
import matplotlib.pyplot as plt #создание графики и визуализации данных
import numpy as np
from sklearn.datasets import load_iris
iris_dataset = load_iris()
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split( #для разделения данных на обучающую и тестовую выборки
iris_dataset['data'], iris_dataset['target'], random_state=0)
print("форма массива X_train: {}".format(X_train.shape))
print("форма массива y_train: {}".format(y_train.shape))
print("форма массива X_test: {}".format(X_test.shape))
print("форма массива y_test: {}".format(y_test.shape))

iris_dataframe = pds.DataFrame(X_train, columns=iris_dataset.feature_names) #задает названия столбцов
from pandas.plotting import scatter_matrix #позволяет создавать парные диаграммы рассеяния
grr = scatter_matrix(iris_dataframe, c=y_train, figsize=(15, 15), marker='o',
 hist_kwds={'bins': 20}, s=60, alpha=.8, cmap=mglearn.cm3)
 #Алгоритм классификации на основе метода k ближайших соседей реализован в классификаторе KNeighborsClassifier модуля neighbors

from sklearn.neighbors import KNeighborsClassifier
knn = KNeighborsClassifier(n_neighbors=1) #n_neighbors=1 - кол-во соседий (1)

#knn будет хранить обучающий набор.
#knn включает в себя алгоритм, который будет использоваться для построения модели на обучающих данных, а также алгоритм, который сгенерирует прогнозы для новых точек данных
knn.fit(X_train, y_train) #Для построения модели на обучающем наборе

X_new = np.array([[5, 2.9, 1, 0.2]]) # scikit-learn работает с двумерными массивами данных
print("форма массива X_new: {}".format(X_new.shape))
prediction = knn.predict(X_new) #Чтобы сделать прогноз/ для предсказания класса нового примера
print("Прогноз: {}".format(prediction))
print("Спрогнозированная метка: {}".format(iris_dataset['target_names'][prediction]))
y_pred = knn.predict(X_test) #Предсказывает классы для тестового набора данных
print("Прогнозы для тестового набора:\n {}".format(y_pred))
print("Правильность на тестовом наборе: {:.2f}".format(np.mean(y_pred == y_test)))
print("Правильность на тестовом наборе: {:.2f}".format(knn.score(X_test, y_test))) #вычисляет правильность модели для тестового набора

##Набор данных Iris состоит из двух массивов NumPy: один содержит данные и в scikit-learn обозначается как X, другой содержит правильные или нужные ответы и обозначается как y.
#Массив Х представляет собой двумерный массив признаков, в котором одна строка соответствует одной точке данных, а один столбец – одному признаку.
#Массив у представляет собой одномерный массив, который для каждого примера содержит метку класса, целое число от 0 до 2

X_train, X_test, y_train, y_test = train_test_split(
 iris_dataset['data'], iris_dataset['target'], random_state=0)
knn = KNeighborsClassifier(n_neighbors=1)
knn.fit(X_train, y_train)
print("Правильность на тестовом наборе: {:.2f}".format(knn.score(X_test, y_test)))


#Мы создали объект-экземпляр класса, задав параметры.
#Затем мы построили модель, вызвав метод fit и передав обучающие данные (X_train) и обучающие ответы (y_train) в качестве параметров.
#Мы оценили качество модели с использованием метода score, который вычисляет правильность модели.
#Мы применили метод score к тестовым данным и тестовым ответам и обнаружили, что наша модель демонстрирует правильность около 97%.
#Это означает, что модель выдает правильные прогнозы для 97% наблюдений тестового набора