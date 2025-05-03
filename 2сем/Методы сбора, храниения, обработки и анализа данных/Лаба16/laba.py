import matplotlib.pyplot as plt
import numpy as np
from sklearn.tree import DecisionTreeClassifier, plot_tree, DecisionTreeRegressor
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
import pandas as pd
from sklearn.linear_model import LinearRegression

#В библиотеке scikit-learn деревья решений реализованы в классах DecisionTreeRegressor и DecisionTreeClassifier.
#Обратите внимание, в scikit-learn реализована лишь предварительная обрезка

# Пример с бинарными данными
X = np.array([[0, 1, 0, 1], [1, 0, 1, 1], [0, 0, 0, 1], [1, 0, 1, 0]]) #матрица признаков
y = np.array([0, 1, 0, 1]) #целевая переменная

#Подсчет частот признаков
counts = {}
for label in np.unique(y):
    counts[label] = X[y == label].sum(axis=0)
print("Частоты признаков:\n{}".format(counts))

#Загрузка данных о раке молочной железы
cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(
    cancer.data, cancer.target, stratify=cancer.target, random_state=42) #stratify обеспечивает пропорциональное распределение классов

#Обучение дерева решений
tree = DecisionTreeClassifier(max_depth=4, random_state=0) #с максимальной глубиной 4
tree.fit(X_train, y_train)

print("Правильность на обучающем наборе: {:.3f}".format(tree.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.3f}".format(tree.score(X_test, y_test)))

#Визуализация дерева решений
plt.figure(figsize=(12, 8))
plot_tree(tree, filled=True, feature_names=cancer.feature_names, class_names=cancer.target_names)
plt.title("Дерево решений")
plt.show()

#Важности признаков
print("Важности признаков:\n{}".format(tree.feature_importances_))

#Создает горизонтальный бар-график, показывающий важность каждого признака
def plot_feature_cancer(model):
    n_features = cancer.data.shape[1]
    plt.barh(range(n_features), model.feature_importances_, align='center')
    plt.yticks(np.arange(n_features), cancer.feature_names)
    plt.xlabel("Важность признака")
    plt.ylabel("Признак")
    plt.title("Важность признаков")
    plt.show()

# Визуализация важностей признаков
plot_feature_cancer(tree)

# Работа с данными о ценах на оперативную память
ram_prices = pd.read_csv("C:/Лабы/Методы сбора, храниения, обработки и анализа данных/Лаба16/ram_price.csv")

plt.semilogy(ram_prices.date, ram_prices.price)
plt.xlabel("Год")
plt.ylabel("Цена $/Мбайт")
plt.title("Цены на оперативную память")
plt.show()

# Подготовка данных для регрессии
data_train = ram_prices[ram_prices.date < 2000]
data_test = ram_prices[ram_prices.date >= 2000]
y_train = np.log(data_train.price) #цены преобразуются в логарифмическую шкалу, чтобы уменьшить разброс
X_train = data_train.date.values[:, np.newaxis] #годы преобразуются в массив NumPy

print("X:\n{}".format(X_train))
print("y:\n{}".format(y_train))

# Обучение дерева регрессии
tree_reg = DecisionTreeRegressor().fit(X_train, y_train)

# Обучение линейной регрессии
linear_reg = LinearRegression().fit(X_train, y_train)

X_all = ram_prices.date.values[:, np.newaxis]

# Прогнозы
pred_tree = tree_reg.predict(X_all)
pred_lr = linear_reg.predict(X_all)

price_tree = np.exp(pred_tree)
price_lr = np.exp(pred_lr)

plt.semilogy(data_train.date, data_train.price, label="Обучающие данные")
plt.semilogy(data_test.date, data_test.price, label="Тестовые данные")
plt.semilogy(ram_prices.date, price_tree, label="Прогнозы дерева")
plt.semilogy(ram_prices.date, price_lr, label="Прогнозы линейной регрессии")
plt.legend()
plt.title("Прогнозы цен на оперативную память")
plt.show()


#При логарифмическом
#преобразовании взаимосвязь выглядит вполне линейной и таким образом становится легко
#прогнозируемой, за исключением некоторых всплесков