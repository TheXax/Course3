#Ядерный метод опорных векторов – это модели, обладающие мощной прогнозной силой и хорошо работающие на различных наборах данных
import sklearn
import mglearn
import matplotlib.pyplot as plt
import numpy as np

from sklearn.datasets import make_blobs
X, y = make_blobs(centers=4, random_state=8)
y = y % 2

mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
plt.xlabel("Признак 0")
plt.ylabel("Признак 1")
plt.show()
#на графике получаем Набор данных с двух классовой классификацией, в котором классы линейно неразделимы

from sklearn.svm import LinearSVC
linear_svm = LinearSVC().fit(X, y)

#Линейная модель классификации может отделить точки только с помощью прямой линии и не может дать хорошее качество для этого набора данных
mglearn.plots.plot_2d_separator(linear_svm, X)
mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
plt.xlabel("Признак 0")
plt.ylabel("Признак 1")
plt.show()

#добавляем второй признак, возведенный в квадрат
X_new = np.hstack([X, X[:, 1:] ** 2])
from mpl_toolkits.mplot3d import Axes3D, axes3d
figure = plt.figure()
# визуализируем в 3D
ax = Axes3D(figure, elev=-152, azim=-26)
mask = y == 0

#сначала размещаем на графике все точки с y == 0, затем с y == 1 mask = y == 0
ax.scatter(X_new[mask, 0], X_new[mask, 1], X_new[mask, 2], c='b', cmap=mglearn.cm2, s=60)
ax.scatter(X_new[~mask, 0], X_new[~mask, 1], X_new[~mask, 2], c='r', marker='^', cmap=mglearn.cm2, s=60)
ax.set_xlabel("признак0")
ax.set_ylabel("признак1")
ax.set_zlabel("признак1 ** 2")
plt.show()
#получаем на графике  Расширение набора данных, показанного на рис. 2, за счет добавления третьего признака, полученного на основе признака 1

linear_svm_3d = LinearSVC().fit(X_new, y)
coef, intercept = linear_svm_3d.coef_.ravel(), linear_svm_3d.intercept_

#показать границу принятия решений линейной модели
figure = plt.figure()
ax = Axes3D(figure, elev=-152, azim=-26)

xx = np.linspace(X_new[:, 0].min() - 2, X_new[:, 0].max() + 2, 50)
yy = np.linspace(X_new[:, 1].min() - 2, X_new[:, 1].max() + 2, 50)

XX, YY = np.meshgrid(xx, yy)
ZZ = (coef[0] * XX + coef[1] * YY + intercept) / -coef[2]

ax.plot_surface(XX, YY, ZZ, rstride=8, cstride=8, alpha=0.3)
ax.scatter(X_new[mask, 0], X_new[mask, 1], X_new[mask, 2], c='b', cmap=mglearn.cm2, s=60)
ax.scatter(X_new[~mask, 0], X_new[~mask, 1], X_new[~mask, 2], c='r', marker='^', cmap=mglearn.cm2, s=60)

ax.set_xlabel("признак0")
ax.set_ylabel("признак1")
ax.set_zlabel("признак1 ** 2")
plt.show()
#получаем на графике Граница принятия решений, найденная линейным SVM для расширенного трехмерного набора данных

ZZ = YY**2
dec = linear_svm_3d.decision_function(np.c_[XX.ravel(), YY.ravel(), ZZ.ravel()])
plt.contourf(XX, YY, dec.reshape(XX.shape), levels=[dec.min(), 0, dec.max()], cmap=mglearn.cm2, alpha=0.5)
mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
plt.xlabel("Признак 0")
plt.ylabel("Признак 1")
plt.show()



#«ядерный трюк» (kernel trick) и он непосредственно вычисляет евклидовы расстояния (более точно, скалярные произведения точек данных),
#чтобы получить расширенное пространство признаков без фактического добавления новых признаков


#Опорные вектора - часть точек обучающего набора, важная для определения границы принятия решений: точки, которые лежат на границе между классами.
from sklearn.svm import SVC
X, y = mglearn.tools.make_handcrafted_dataset()
svm = SVC(kernel='rbf', C=10, gamma=0.1).fit(X, y)
mglearn.plots.plot_2d_separator(svm, X, eps=.5)
mglearn.discrete_scatter(X[:, 0], X[:, 1], y)
sv = svm.support_vectors_
sv_labels = svm.dual_coef_.ravel() > 0

mglearn.discrete_scatter(sv[:, 0], sv[:, 1], sv_labels, s=15, markeredgewidth=3)
plt.xlabel("Признак 0")
plt.ylabel("Признак 1")
plt.show()
#Рис. 10.7 показывает результат обучения машины опорных векторов на двумерном 2-ух
#классовом наборе данных. Граница принятия решений показана черным цветом, а опорные
#векторы – это точки большего размера, обведенные широким контуром.


#результаты при изменении пар-ров C (параметр регуляризации) и gamma (задает степень близости расположения точек)
fig, axes = plt.subplots(3, 3, figsize=(15, 10))

for ax, C in zip(axes, [-1, 0, 3]):
    for a, gamma in zip(ax, range(-1, 2)):
        mglearn.plots.plot_svm(log_C=C, log_gamma=gamma, ax=a)

axes[0, 0].legend(["class 0", "class 1", "sv class 0", "sv class 1"], ncol=4,
loc=(.9, 1.2))
plt.show()

#Перемещаясь слева направо, мы увеличиваем значение параметра gamma c 0.1 до 10.
#Небольшое значение gamma соответствует большому радиусу гауссовского ядра, это означает, что
#многие точки рассматриваются как расположенные поблизости. Это приводит к получению очень
#гладких границ принятия решений, показанных в левой части графика, а границы, которые больше
#фокусируются на отдельных точках, расположились в правой части графика. Низкое значение
#gamma означает медленное изменение решающей границы, которое дает модель низкой
#сложности, в то время как высокое значение gamma дает более сложную модель


#Перемещаясь сверху вниз, мы увеличиваем параметр C с 0.1 до 1000. Как и в случае с
#линейными моделями, небольшое значение C соответствует модели с весьма жесткими
#ограничениями, в которой каждая точка данных может иметь лишь очень ограниченное влияние. В
#левом верхнем углу рис. можно увидеть, что граница принятия решений выглядит как почти
#линейная, неправильно классифицированные точки почти не влияют на линию. Увеличение
#значения C, как показано в левом нижнем углу, позволяет этим точкам оказывать более сильное
#влияние на модель и делает решающую границу изогнутой, позволяя правильно классифицировать
#данные точки.



from sklearn.model_selection import train_test_split
from sklearn.datasets import load_breast_cancer
cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split( cancer.data, cancer.target,
random_state=0)
svc = SVC()
svc.fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.2f}".format(svc.score(X_train,
y_train)))
print("Правильность на тестовом наборе: {:.2f}".format(svc.score(X_test, y_test)))
plt.show()

plt.plot(X_train.min(axis=0), 'o', label="min")
plt.plot(X_train.max(axis=0), '^', label="max")
plt.legend(loc=4)
plt.xlabel("Индекс признака")
plt.ylabel("Величина признака")
plt.yscale("log")
plt.show()
#признаки в наборе данных Breast Cancer
#имеют совершенно различные порядки величин. Для ряда моделей (например, для линейных
#моделей) данный факт может быть в некоторой степени проблемой, однако для ядерного SVM он
#будет иметь разрушительные последствия.


#вычисляем минимальное значение для каждого признака обучающего набора
min_on_training = X_train.min(axis=0)
#вычисляем ширину диапазона для каждого признака (max - min) обучающего набора
range_on_training = (X_train - min_on_training).max(axis=0)
#вычитаем минимальное значение и затем делим на ширину диапазона
#min=0 и max=1 для каждого признака
X_train_scaled = (X_train - min_on_training) / range_on_training
print("Минимальное значение для каждого признака\n{}".format(X_train_scaled.min(axis=0)))
print("Максимальное значение для каждого признака\n{}".format(X_train_scaled.max(axis=0)))

#используем ТО ЖЕ САМОЕ преобразование для тестового набора
X_test_scaled = (X_test - min_on_training) / range_on_training
svc = SVC()
svc.fit(X_train_scaled, y_train)
print("Правильность на обучающем наборе: {:.3f}".format( svc.score(X_train_scaled,
y_train)))
print("Правильность на тестовом наборе: {:.3f}".format(svc.score(X_test_scaled,
y_test)))

svc = SVC(C=1000)
svc.fit(X_train_scaled, y_train)
print("Правильность на обучающем наборе: {:.3f}".format( svc.score(X_train_scaled,
y_train)))
print("Правильность на тестовом наборе: {:.3f}".format(svc.score(X_test_scaled,
y_test)))