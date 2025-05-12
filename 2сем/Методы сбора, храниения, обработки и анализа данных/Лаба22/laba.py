
#Анализ главных компонентов
#представляет собой метод, который осуществляет вращение данных с тем, чтобы преобразованные признаки не коррелировали между собой.
import mglearn
import sklearn
import matplotlib.pyplot as plt
import numpy as np
from sklearn.model_selection import train_test_split

# результат применения PCA к синтетическому двумерному массиву данных
mglearn.plots.plot_pca_illustration()
plt.show()
#Первый рис. (вверху слева) показывает исходные точки данных, выделенные
#цветом для лучшей дискриминации. Алгоритм начинает работу с того, что сначала
#находит направление максимальной дисперсии, помеченное как «компонента 1». Речь
#идет о направлении (или векторе) данных, который содержит большую часть
#информации, или другими словами, направление, вдоль которого признаки коррелируют
#друг с другом сильнее всего. Затем алгоритм находит направление, которое содержит
#наибольшее количество информации, и при этом ортогонально (расположено под
#прямым углом) первому направлению.
#Направления, найденные с помощью этого
#алгоритма, называются главными компонентами (principal components), поскольку они
#являются основными направлениями дисперсии данных.

#Второй график (вверху справа) показывает те же самые данные, но теперь
#овернутые таким образом, что первая главная компонента совпадает с осью х, а вторая
#главная компонента совпадает с осью у. Перед вращением из каждого значения данных
#вычитается среднее, таким образом, преобразованные данные центрированы около
#нуля.

#Мы можем использовать PCA для уменьшения размерности, сохранив лишь
#есколько главных компонент. В данном примере мы можем оставить лишь первую
#главную компоненту, как показано на третьем графике рис.1 (внизу слева). Это
#уменьшит размерность данных: из двумерного массива данных получаем одномерный
#массив данных.

#И, наконец, мы можем отменить вращение и добавить
#обратно среднее значение к значениям данных. В итоге получим данные, показанные на
#последнем графике


from sklearn.datasets import load_breast_cancer


cancer = load_breast_cancer()

#Преобразование данных с помощью PCA
fig, axes = plt.subplots(15, 2, figsize=(10, 20))
malignant = cancer.data[cancer.target == 0]
benign = cancer.data[cancer.target == 1]
ax = axes.ravel()
for i in range(30):
    _, bins = np.histogram(cancer.data[:, i], bins=50)
    ax[i].hist(malignant[:, i], bins=bins, color=mglearn.cm3(0), alpha=.5)
    ax[i].hist(benign[:, i], bins=bins, color=mglearn.cm3(2), alpha=.5)
    ax[i].set_title(cancer.feature_names[i])
    ax[i].set_yticks(())
    ax[0].set_xlabel("Значение признака")
    ax[0].set_ylabel("Частота")
ax[0].legend(["доброкачественная", "злокачественная"], loc="best")
fig.tight_layout()
plt.show()
#В данном случае мы строим для каждого признака гистограмму, подсчитывая
#частоту встречаемости точек данных в пределах границ интервалов (этот интервал еще
#называют бином). Каждый график содержит две наложенные друг на друга гистограммы,
#первая – для всех точек, относящихся к классу «доброкачественная опухоль» (синий
#цвет), а вторая – для всех точек, относящихся к классу «злокачественная опухоль» (зеленый цвет)
#позволяет нам строить предположения о том, какие признаки лучше всего дискриминируют злокачественные и доброкачественные опухоли

#отмасштабируем наши данные таким образом, чтобы каждый признак имел единичную дисперсию
from sklearn.datasets import load_breast_cancer
cancer = load_breast_cancer()
from sklearn.preprocessing import StandardScaler
scaler = StandardScaler()
scaler.fit(cancer.data)
X_scaled = scaler.transform(cancer.data)


from sklearn.decomposition import PCA


# оставляем первые две главные компоненты
pca = PCA(n_components=2)
# подгоняем модель PCA на наборе данных breast cancer
pca.fit(X_scaled)
# преобразуем данные к первым двум главным компонентам
X_pca = pca.transform(X_scaled)
print("Форма исходного массива: {}".format(str(X_scaled.shape)))
print("Форма массива после сокращения размерности: {}".format(str(X_pca.shape)))


# строим график первых двух главных компонент, классы выделены цветом
plt.figure(figsize=(8, 8))
mglearn.discrete_scatter(X_pca[:, 0], X_pca[:, 1], cancer.target)
plt.legend(cancer.target_names, loc="best")
plt.gca().set_aspect("equal")
plt.xlabel("Первая главная компонента")
plt.ylabel("Вторая главная компонента")
plt.show()
#Двумерная диаграмма рассеяния для набора данных Breast Cancer с использованием первых двух главных компонент

#Недостаток PCA заключается в том, что эти две оси графика часто бывает сложно интерпретировать

print("форма главных компонент: {}".format(pca.components_.shape))

#Каждая строка в атрибуте components_ соответствует одной главной компоненте
#и они отсортированы по важности (первой приводится первая главная компонента и т.д.).
#Столбцы соответствуют атрибуту исходных признаков для объекта PCA
print("компоненты PCA:\n{}".format(pca.components_))

#Кроме того, с помощью тепловой карты можно визуализировать коэффициенты, чтобы упростить их интерпретацию
plt.matshow(pca.components_, cmap='viridis')
plt.yticks([0, 1], ["Первая компонента", "Вторая компонента"])
plt.colorbar()
plt.xticks(range(len(cancer.feature_names)), cancer.feature_names, rotation=60, ha='left')
plt.xlabel("Характеристика")
plt.ylabel("Главные компоненты")
plt.show()
#Тепловая карта первых двух главных компонент для набора данных рака Breast Cancer

#Вы можете увидеть, что в первой компоненте коэффициенты всех признаков
#имеют одинаковый знак (они положительные, но, как мы уже говорили ранее, не имеет
#значения, какое направление указывает стрелка). Это означает, что существует общая
#корреляция между всеми признаками.

#Во второй компоненте коэффициенты признаков имеют разные знаки


# conda install -c anaconda openssl
from sklearn.datasets import fetch_lfw_people

#отображение изображений
people = fetch_lfw_people(min_faces_per_person=20, resize=0.7)
image_shape = people.images[0].shape
fix, axes = plt.subplots(2, 5, figsize=(15, 8), subplot_kw={'xticks': (), 'yticks': ()})
for target, image, ax in zip(people.target, people.images, axes.ravel()):
    ax.imshow(image)
    ax.set_title(people.target_names[target])
plt.show()
print("форма массива изображений лиц: {}".format(people.images.shape))
print("количество классов: {}".format(len(people.target_names)))


# вычисляем частоту встречаемости каждого ответа
counts = np.bincount(people.target)
# печатаем частоты рядом с ответами
for i, (count, name) in enumerate(zip(counts, people.target_names)):
    print("{0:25} {1:3}".format(name, count), end=' ')
    if (i + 1) % 3 == 0:
        print()
#ы будем рассматривать не более 50 изображений каждого человека
mask = np.zeros(people.target.shape, dtype=np.bool)
for target in np.unique(people.target):
    mask[np.where(people.target == target)[0][:50]] = 1
X_people = people.data[mask]
y_people = people.target[mask]
# для получения большей стабильности масштабируем шкалу оттенков серого так, чтобы значения
# были в диапазоне от 0 до 1 вместо использования шкалы значений от 0 до 255
X_people = X_people / 255.

#использовать классификатор одного ближайшего соседа, который ищет лицо, наиболее схожее с классифицируемым
from sklearn.neighbors import KNeighborsClassifier

# разбиваем данные на обучающий и тестовый наборы
X_train, X_test, y_train, y_test = train_test_split(X_people, y_people, stratify=y_people, random_state=0)
# строим KNeighborsClassifier с одним соседом
knn = KNeighborsClassifier(n_neighbors=1)
knn.fit(X_train, y_train)
print("Правильность на тестовом наборе для 1-nn: {:.2f}".format(knn.score(X_test, y_test)))

#Преобразование данных с использованием выбеливания
mglearn.plots.plot_pca_whitening()
plt.show()


pca = PCA(n_components=100, whiten=True, random_state=0).fit(X_train)
X_train_pca = pca.transform(X_train)
X_test_pca = pca.transform(X_test)
print("обучающие данные после PCA: {}".format(X_train_pca.shape))

knn = KNeighborsClassifier(n_neighbors=1)
knn.fit(X_train_pca, y_train)
print("Правильность на тестовом наборе: {:.2f}".format(knn.score(X_test_pca, y_test)))

print("форма pca.components_: {}".format(pca.components_.shape))

# fix, axes = plt.subplots(3, 5, figsize=(15, 12),
# subplot_kw={'xticks': (), 'yticks': ()})
# for i, (component, ax) in enumerate(zip(pca.components_, axes.ravel())):
# ax.imshow(component.reshape(image_shape), cmap='viridis')
# ax.set_title("{}. component".format((i + 1))
# plt.show()

#Здесь мы визуализируем результаты реконструкции некоторых лиц, используя 10, 50, 100, 500 и 2000 компонент
#у меня не отображается
mglearn.plots.plot_pca_faces(X_train, X_test, image_shape)
plt.show()

#для визуализации всех лиц набора на диаграмме рассеяния
mglearn.discrete_scatter(X_train_pca[:, 0], X_train_pca[:, 1], y_train)
plt.xlabel("Первая главная компонента")
plt.ylabel("Вторая главная компонента")
plt.show()
# Диаграмма рассеяния для набора лиц, использующая первые две главные компоненты