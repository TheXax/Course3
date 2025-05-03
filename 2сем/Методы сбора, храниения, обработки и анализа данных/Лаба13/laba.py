#Линейные модели для классификации

#граница принятия решений (decision boundary) является линейной функцией аргумента.
#Другими словами, (бинарный) линейный классификатор – это классификатор, который разделяет два класса с помощью линии, плоскости или гиперплоскости.
import mglearn
import sklearn
import matplotlib.pyplot as plt

#получаем рисунок с границами принятия решений линейного SVM и логистической регрессии для набора
from sklearn.linear_model import LogisticRegression #алгоритм линейной классификации - логистическая регрессия
from sklearn.svm import LinearSVC ##линейный метод опорных векторов
X, y = mglearn.datasets.make_forge()
#Создаем графики с двумя подграфиками (axes) для визуализации
fig, axes = plt.subplots(1, 2, figsize=(10, 3))

for model, ax in zip([LinearSVC(), LogisticRegression()], axes):
    clf = model.fit(X, y) #oбучаем текущую модель на данных X и y
    mglearn.plots.plot_2d_separator(clf, X, fill=False, eps=0.5, ax=ax, alpha=.7) #cтроим границу принятия решений
    mglearn.discrete_scatter(X[:, 0], X[:, 1], y, ax=ax) #Визуализируем данные
    ax.set_title("{}".format(clf.__class__.__name__))
    ax.set_xlabel("Признак 0")
    ax.set_ylabel("Признак 1")
axes[0].legend()
plt.show()

#Для LogisticRegression и LinearSVC компромиссный параметр, который определяет степень регуляризации, называется C.
#Более высокие значения C соответствуют меньшей регуляризации

#Использование низких значений C приводит к тому, что алгоритмы пытаются подстроиться под «большинство» точек данных,
#тогда как использование более высоких значений C подчеркивает важность того, чтобы каждая отдельная точка данных была классифицирована правильно.

mglearn.plots.plot_linear_svc_regularization() #Визуализируем, как регуляризация влияет на линейный SVC
plt.show()

#неплохое качество модели, но есть шанс недоубучния
from sklearn.datasets import load_breast_cancer
cancer = load_breast_cancer()
from sklearn.model_selection import train_test_split
#разделяем данные на обучающий набор и тестовый набор
X_train, X_test, y_train, y_test = train_test_split(
    cancer.data, cancer.target, stratify=cancer.target, random_state=42)
logreg = LogisticRegression().fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.3f}".format(logreg.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.3f}".format(logreg.score(X_test, y_test)))

#более высокой правильности на обучающей выборке, а также немного увеличилась правильность на тестовой выборке,
#что подтверждает наш довод о том, что более сложная модель должна сработать лучше
logreg100 = LogisticRegression(C=100).fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.3f}".format(logreg100.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.3f}".format(logreg100.score(X_test, y_test)))

#правильность снизилась
logreg001 = LogisticRegression(C=0.01).fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.3f}".format(logreg001.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.3f}".format(logreg001.score(X_test, y_test)))

#Коэффициенты, полученные с помощью логистической регрессии с разными значениями C
plt.plot(logreg.coef_.T, 'o', label="C=1")
plt.plot(logreg100.coef_.T, '^', label="C=100")
plt.plot(logreg001.coef_.T, 'v', label="C=0.001")
plt.xticks(range(cancer.data.shape[1]), cancer.feature_names, rotation=90)
plt.hlines(0, 0, cancer.data.shape[1]) #рисуем горизонтальную линию
plt.ylim(-5, 5)
plt.xlabel("Индекс коэффициента")
plt.ylabel("Оценка коэффициента")
plt.legend()
plt.show()

for C, marker in zip([0.001, 1, 100], ['o', '^', 'v']):
    lr_l1 = LogisticRegression(C=C, penalty="l2").fit(X_train, y_train)
    print("Правильность на обучении для логрегрессии l1 с C={:.3f}: {:.2f}".format( C,
lr_l1.score(X_train, y_train)))
    print("Правильность на тесте для логрегрессии l1 с C={:.3f}: {:.2f}".format( C,
lr_l1.score(X_test, y_test)))

plt.plot(lr_l1.coef_.T, marker, label="C={:.3f}".format(C))
plt.xticks(range(cancer.data.shape[1]), cancer.feature_names, rotation=90)
plt.hlines(0, 0, cancer.data.shape[1])
plt.xlabel("Индекс коэффициента")
plt.ylabel("Оценка коэффициента")
plt.ylim(-5, 5)
plt.legend(loc=3)
plt.show()