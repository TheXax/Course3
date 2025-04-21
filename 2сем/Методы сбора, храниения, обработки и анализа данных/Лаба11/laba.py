import sklearn
import mglearn
import matplotlib.pyplot as plt #для создания графиков
import matplotlib
import numpy as np

X, y = mglearn.datasets.make_forge() #генерирует простую двумерную выборку данных (X) и метки классов (y) для задачи классификации
mglearn.discrete_scatter(X[:, 0], X[:, 1], y) #отображает точки на графике, где X[:, 0] — это значения первого признака
#ниже устанавливается легенда для классов, а также подписываются оси графика
plt.legend(["Класс 0", "Класс 1"], loc=4)
plt.xlabel("Первый признак")
plt.ylabel("Второй признак")
print("форма массива X: {}".format(X.shape))
plt.show()

#диаграмма рассеяния (scatter plot), которая визуализирует взаимосвязь между двумя переменными: "Признак" (по оси X) и "Целевая переменная" (по оси Y)
X, y = mglearn.datasets.make_wave(n_samples=40) #генерирует набор данных для регрессии с 40 образцами
plt.plot(X, y, 'o') #Отображает точки на графике, где X — это признак, а y — целевая переменная
plt.ylim(-3, 3) #установка пределов
plt.xlabel("Признак")
plt.ylabel("Целевая переменная")
plt.show()

#данные о раке
from sklearn.datasets import load_breast_cancer
cancer = load_breast_cancer()
print("Ключи cancer(): \n{}".format(cancer.keys()))

#Набор данных включает 569 точек данных и 30 признаков.
print("Форма массива data для набора cancer: {}".format(cancer.data.shape))

#Из 569 точек данных 212 помечены как злокачественные, а 357 как доброкачественные.
print("Количество примеров для каждого класса:\n{}".format(
{n: v for n, v in zip(cancer.target_names, np.bincount(cancer.target))})) #np.bincount() подсчитывается количество образцов для каждого класса

#данные о жилье
from sklearn.datasets import fetch_california_housing
housing = fetch_california_housing()
print("форма массива data для набора housing: {}".format(housing.data.shape))

X, y = mglearn.datasets.load_extended_boston()
print("форма массива X: {}".format(X.shape))

#Классификация с помощью k ближайших соседей
mglearn.plots.plot_knn_classification(n_neighbors=1) #Отображает график классификации для одного соседа
plt.show()

mglearn.plots.plot_knn_classification(n_neighbors=3)
plt.show()

#разделим наши данные на обучающий и тестовый наборы, чтобы оценить обобщающую способность модели
from sklearn.model_selection import train_test_split

X, y = mglearn.datasets.make_forge()
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)

from sklearn.neighbors import KNeighborsClassifier
clf = KNeighborsClassifier(n_neighbors=3)

#классификатор, используя обучающий набор
clf.fit(X_train, y_train)

#Для каждой точки тестового набора он вычисляет ее ближайших соседей в обучающем наборе и находит среди них наиболее часто встречающийся класс
print("Прогнозы на тестовом наборе: {}".format(clf.predict(X_test)))

print("Правильность на тестовом наборе: {:.2f}".format(clf.score(X_test, y_test)))

#визуализирует границы принятия решений для одного, трех и девяти соседей
fig, axes = plt.subplots(1, 3, figsize=(10, 3)) #Создается фигура с 3 подграфиками для отображения границ принятия решений

#Для каждого значения соседей (1, 3, 9) обучается модель и отображаются границы принятия решений, а также точки данных.
for n_neighbors, ax in zip([1, 3, 9], axes):
    #создаем объект-классификатор и подгоняем в одной строке
 clf = KNeighborsClassifier(n_neighbors=n_neighbors).fit(X, y)
 mglearn.plots.plot_2d_separator(clf, X, fill=True, eps=0.5, ax=ax, alpha=.4)
 mglearn.discrete_scatter(X[:, 0], X[:, 1], y, ax=ax)
 ax.set_title("количество соседей:{}".format(n_neighbors))
 ax.set_xlabel("признак 0")
 ax.set_ylabel("признак 1")
axes[0].legend(loc=3) #обавляется легенда и отображаются все три графика
plt.show()

from sklearn.datasets import load_breast_cancer
cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(
 cancer.data, cancer.target, stratify=cancer.target, random_state=66)

training_accuracy = []
test_accuracy = []

#пробуем n_neighbors от 1 до 10
neighbors_settings = range(1, 11)

for n_neighbors in neighbors_settings:
    #строим модель
    clf = KNeighborsClassifier(n_neighbors=n_neighbors)
    clf.fit(X_train, y_train)
    #записываем правильность на обучающем наборе
    training_accuracy.append(clf.score(X_train, y_train))
    #записываем правильность на тестовом наборе
    test_accuracy.append(clf.score(X_test, y_test))

#графики
plt.plot(neighbors_settings, training_accuracy, label="правильность на обучающем наборе")
plt.plot(neighbors_settings, test_accuracy, label="правильность на тестовом наборе")
plt.ylabel("Правильность")
plt.xlabel("количество соседей")
plt.legend()
plt.show()

mglearn.plots.plot_knn_regression(n_neighbors=1) #график для регрессии с 1 соседом
plt.show()

mglearn.plots.plot_knn_regression(n_neighbors=3)

plt.show()
from sklearn.neighbors import KNeighborsRegressor
X, y = mglearn.datasets.make_wave(n_samples=40)
#разбиваем набор данных wave на обучающую и тестовую выборки
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
#создаем экземпляр модели и устанавливаем количество соседей равным 3
reg = KNeighborsRegressor(n_neighbors=3)
#подгоняем модель с использованием обучающих данных и обучающих ответов
reg.fit(X_train, y_train)

print("Прогнозы для тестового набора:\n{}".format(reg.predict(X_test)))

#Вычисляется и выводится коэффициент детерминации R² на тестовом наборе - относительно хорошее качество подгонки модели
print("R^2 на тестовом наборе: {:.2f}".format(reg.score(X_test, y_test)))

#Создается фигура с 3 подграфиками и создается линия для визуализации предсказаний
fig, axes = plt.subplots(1, 3, figsize=(15, 4))
line = np.linspace(-3, 3, 1000).reshape(-1, 1)

# Для каждого значения соседей (1, 3, 9) обучается регрессор, прогнозы отображаются на графиках, а также показываются обучающие и тестовые данные
for n_neighbors, ax in zip([1, 3, 9], axes):
 reg = KNeighborsRegressor(n_neighbors=n_neighbors)

 reg.fit(X_train, y_train)
 ax.plot(line, reg.predict(line))
 ax.plot(X_train, y_train, '^', c=mglearn.cm2(0), markersize=8)
 ax.plot(X_test, y_test, 'v', c=mglearn.cm2(1), markersize=8)
 ax.set_title(
 "{} neighbor(s)\n train score: {:.2f} test score: {:.2f}".format(
 n_neighbors, reg.score(X_train, y_train), reg.score(X_test, y_test)))
 ax.set_xlabel("Признак")
 ax.set_ylabel("Целевая переменная")
axes[0].legend(["Прогнозы модели", "Обучающие данные/ответы","Тестовые данные/ответы"], loc="best")
plt.show()