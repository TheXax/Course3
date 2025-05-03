#Линейные модели для мультиклассовой классификации

#Общераспространненный подход, позволяющий распространить алгоритм бинарной классификации на случай мультиклассовой классификации называет подходом один против остальных (one-vs.-rest).
#В подходе «один против остальных» для каждого класса строится бинарная модель, которая пытается отделить этот класс от всех остальных

#Используя бинарный классификатор для каждого класса, мы получаем один вектор коэффициентов (w) и одну константу (b) по каждому классу
import mglearn
import sklearn
import matplotlib.pyplot as plt
import numpy as np

#получим  двумерный синтетический набор данных, содержащий три класса
from sklearn.datasets import make_blobs
X, y = make_blobs(random_state=42)
mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
plt.xlabel("Признак 0")
plt.ylabel("Признак 1")
plt.legend(["Класс 0", "Класс 1", "Класс 2"])
plt.show()

#обучаем классификатор LinearSVC на этом наборе данных
from sklearn.svm import LinearSVC
linear_svm = LinearSVC().fit(X, y)
print("Форма коэффициента: ", linear_svm.coef_.shape) #имеет форму (3, 2), это означает, что каждая строка coef_ содержит вектор коэффициентов для каждого из трех классов, а каждый столбец содержит коэффициент для конкретного признака
print("Форма константы: ", linear_svm.intercept_.shape) #является одномерным массивом, в котором записаны константы классов

#получаем график с границами принятия решений, полученными с помощью трех бинарных классификаторов в рамках подхода «один против остальных»
mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
line = np.linspace(-15, 15)

for coef, intercept, color in zip(linear_svm.coef_, linear_svm.intercept_, ['b', 'r', 'g']):
    plt.plot(line, -(line * coef[0] + intercept) / coef[1], c=color)
plt.ylim(-10, 15)
plt.xlim(-10, 8)
plt.xlabel("Признак 0")
plt.ylabel("Признак 1")

plt.legend(['Класс 0', 'Класс 1', 'Класс 2', 'Линия класса 0', 'Линия класса 1', 'Линия класса 2'], loc=(1.01, 0.3))
plt.show()

#показывает прогнозы для всех областей двумерного пространства
mglearn.plots.plot_2d_classification(linear_svm, X, fill=True, alpha=.7)
mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
line = np.linspace(-15, 15)
for coef, intercept, color in zip(linear_svm.coef_, linear_svm.intercept_, ['b', 'r', 'g']):
    plt.plot(line, -(line * coef[0] + intercept) / coef[1], c=color)
plt.legend(['Класс 0', 'Класс 1', 'Класс 2', 'Линия класса 0', 'Линия класса 1',
'Линия класса 2'], loc=(1.01, 0.3))
plt.xlabel("Признак 0")
plt.ylabel("Признак 1")
plt.show()