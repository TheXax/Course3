#обучение без учителя
#Машинное обучение без учителя включает в себя все виды машинного обучения, когда ответ неизвестен и отсутствует учитель, указывающий ответ алгоритму.

#два вида машинного обучения без учителя: преобразования данных и кластеризацию.

#Неконтролируемые преобразования (unsupervised transformations) – это
#алгоритмы, создающие новое представление данных, которое в отличие от исходного
#представления человеку или алгоритму машинного обучения будет обработать легче.

#Главная проблема машинного обучения без учителя – оценка полезности информации, извлеченной алгоритмом
#мы не знаем, каким должен быть правильный ответ
import mglearn
import sklearn
import matplotlib.pyplot as plt


"In[2]:"
# Различные способы масштабирования и предварительной обработки данных
mglearn.plots.plot_scaling()
plt.show()

#Первый график на рис. 1 соответствует синтетическому двуклассовому набору данных с
#двумя признаками. Первый признак (ось x) принимает значения в диапазоне от 10 до 15. Второй
#признак (ось y) принимает значения примерно в диапазоне от 1 до 9.
#Следующие четыре графика показывают четыре различных способа преобразования
#данных, которые дают более стандартные диапазоны значений. Применение StandardScaler в scikitlearn гарантирует, что для каждого признака среднее будет равно 0, а дисперсия будет равна 1, в
#результате чего все признаки будут иметь один и тот же масштаб. Однако это масштабирование не
#арантирует получение каких-то конкретных минимальных и максимальных значений признаков.
#RobustScaler аналогичен StandardScaler в том плане, что в результате его применения признаки
#будут иметь один и тот же масштаб. Однако RobustScaler вместо среднего и дисперсии использует
#медиану и квартили. Это позволяет RobustScaler игнорировать точки данных, которые сильно
#отличаются от остальных (например, ошибки измерений). Эти странные точки данных еще
#называются выбросами (outliers) и могут стать проблемой для остальных методов масштабирования.
#С другой стороны, MinMaxScaler сдвигает данные таким образом, что все признаки
#аходились строго в диапазоне от 0 до 1. Для двумерного набора данных это означает, что все
#данные помещаются в прямоугольник, образованный осью х с диапазоном значений от 0 и 1 и осью
#у с диапазоном значений от 0 и 1.
#И, наконец, Normalizer осуществляет совершенно иной вид масштабирования. Он
#масштабирует каждую точку данных таким образом, чтобы вектор признаков имел евклидову
#длину 1. Другими словами, он проецирует точку данных на окружность с радиусом 1 (или сферу в
#случае большого числа измерений). Вектор умножается на инверсию своей длины. Подобная
#нормализация используется тогда, когда важным является направление (но не длина) вектора
#признаков.


"In[3]:"
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(cancer.data, cancer.target, random_state=1)
print(X_train.shape)
print(X_test.shape)


"In[4]:"
#импортируем класс, который осуществляет предварительную обработку, а затем создаем его экземпляр
from sklearn.preprocessing import MinMaxScaler
scaler = MinMaxScaler()


"In[5]:"
scaler.fit(X_train) #вычисляет минимальное и максимальное значения каждого признака на обучающем наборе


"In[6]:"
#масштабирование
min_on_training = X_train.min(axis=0)
range_on_training = (X_train - min_on_training).max(axis=0)
X_train_scaled = (X_train - min_on_training) / range_on_training
print("форма преобразованного массива: {}".format(X_train_scaled.shape))
print("min значение признака до масштабирования:\n {}".format(X_train.min(axis=0)))
print("max значение признака до масштабирования:\n {}".format(X_train.max(axis=0)))
print("min значение признака после масштабирования:\n {}".format( X_train_scaled.min(axis=0)))
print("max значение признака после масштабирования:\n {}".format( X_train_scaled.max(axis=0)))


"In[7]:"
X_test_scaled = (X_test - min_on_training) / range_on_training
print("min значение признака после масштабирования:\n{}".format(X_test_scaled.min(axis=0)))
print("max значение признака после масштабирования:\n{}".format(X_test_scaled.max(axis=0)))


"In[8]:"
#если бы мы использовали минимальное значение и ширину диапазона, отдельно вычисленные для тестового набора
from sklearn.datasets import make_blobs
X, _ = make_blobs(n_samples=50, centers=5, random_state=4, cluster_std=2)
X_train, X_test = train_test_split(X, random_state=5, test_size=.1)
fig, axes = plt.subplots(1, 3, figsize=(13, 4))
axes[0].scatter(X_train[:, 0], X_train[:, 1],
    c=mglearn.cm2(0), label="Обучающий набор", s=60)
axes[0].scatter(X_test[:, 0], X_test[:, 1], marker='^',
    c=mglearn.cm2(1), label="Тестовый набор", s=60)
axes[0].legend(loc='upper left')
axes[0].set_title("Исходные данные")

scaler = MinMaxScaler()
scaler.fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)

axes[1].scatter(X_train_scaled[:, 0], X_train_scaled[:, 1],
    c=mglearn.cm2(0), label="Обучающий набор", s=60)

axes[1].scatter(X_test_scaled[:, 0], X_test_scaled[:, 1], marker='^', c=mglearn.cm2(1), label="Тестовый набор", s=60)
axes[1].set_title("Масштабированные данные")

test_scaler = MinMaxScaler()
test_scaler.fit(X_test)
X_test_scaled_badly = test_scaler.transform(X_test)

axes[2].scatter(X_train_scaled[:, 0], X_train_scaled[:, 1],
c=mglearn.cm2(0), label="Обучающий набор", s=60)

axes[2].scatter(X_test_scaled_badly[:, 0], X_test_scaled_badly[:, 1], marker='^', c=mglearn.cm2(1), label="Тестовый набор", s=60)

axes[2].set_title("Неправильно масштабированные данные")
for ax in axes:
    ax.set_xlabel("Признак 0")
    ax.set_ylabel("Признак 1")
plt.show()
# Результаты одинакового масштабирования обучающего и тестового наборов (центр) и отдельного масштабирования обучающего и тестового наборов (справа)

#Первый график – это немасштабированный двумерный массив данных, наблюдения
#обучающего набора показаны кружками, а наблюдения тестового набора показаны
#треугольниками.
#Второй график – те же самые данные, но масштабированы с помощью
#MinMaxScaler. Здесь мы вызвали метод для обучающего набора, а затем вызвали метод
#transform для обучающего и тестового наборов. Как видите, набор данных на втором графике
#дентичен набору, приведенному на первом графике, изменились лишь метки осей. Теперь все
#признаки принимают значения в диапазоне от 0 до 1. Кроме того, видно, что минимальные и
#максимальные значения признаков в тестовом наборе (треугольники) не равны 0 и 1.
#Третий график показывает, что произойдет, если отмасштабируем обучающий и тестовый
#наборы по отдельности. В этом случае минимальные и максимальные значения признаков в
#обучающем и тестовом наборах равны 0 и 1. Но теперь набор данных выглядит иначе. Тестовые
#точки причудливым образом сместились, поскольку масштабированы по-другому. Мы изменили
#расположение данных произвольным образом. Очевидно, это совсем не то. что нам нужно.

"In[9]:"
from sklearn.preprocessing import StandardScaler
scaler = StandardScaler()
X_scaled = scaler.fit(X).transform(X)
X_scaled_d = scaler.fit_transform(X)


"In[10]:"
#подгоним SVC на исходных данных
from sklearn.svm import SVC
X_train, X_test, y_train, y_test = train_test_split(cancer.data, cancer.target, random_state=0)
svm = SVC(C=100)
svm.fit(X_train, y_train)
print("Правильность на тестовом наборе: {:.2f}".format(svm.score(X_test, y_test)))


"In[11]:"
#Масшабируем
scaler = MinMaxScaler()
scaler.fit(X_train)

X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)
svm.fit(X_train_scaled, y_train)
print("Правильность на масштабированном тестовом наборе: {:.2f}".format( svm.score(X_test_scaled, y_test)))


"In[12]:"
from sklearn.preprocessing import StandardScaler
scaler = StandardScaler()
scaler.fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)
svm.fit(X_train_scaled, y_train)
print("Правильность SVM на тестовом наборе: {:.2f}".format(svm.score(X_test_scaled, y_test)))