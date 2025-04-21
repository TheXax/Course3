#Линейные модели. Метод наименьших квадратов
#Линейные модели для регрессии можно охарактеризовать как регрессионные модели, в которых прогнозом является прямая линия для одного признака,
#плоскость, когда используем два признака,
#или гиперплоскость для большего количества измерений (то есть, когда используем много признаков)
import sklearn
import mglearn
import matplotlib.pyplot as plt
import matplotlib
import numpy as np

#w и b – параметры модели, оцениваемые в ходе обучения, и yˆ – прогноз, выдаваемый моделью
mglearn.plots.plot_linear_regression_wave()
plt.show()

#Лиенйная реграссия
# Линейная регрессия находит параметры w и b, которые минимизируют среднеквадратическую ошибку (mean squared error) между спрогнозированными и фактическими ответами у в обучающем наборе.
#Среднеквадратичная ошибка равна сумме квадратов разностей между спрогнозированными и фактическими значениями

#построение первой модели (линия и точки)
from sklearn.linear_model import LinearRegression
X, y = mglearn.datasets.make_wave(n_samples=60) #Создает синтетический набор данных с 60 образцами, где X — признаки, а y — целевая переменная
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=42)

lr = LinearRegression().fit(X_train, y_train) #Создает объект линейной регрессии и обучает его на обучающих данных X_train и y_train

print("lr.coef_: {}".format(lr.coef_)) #хранение параметров «наклона» (w), называемых весами или коэффициентами
print("lr.intercept_: {}".format(lr.intercept_)) #сдвиг (offset) или константа (intercept), обозначаемая как b

#насколько хорошо модель объясняет вариацию целевой переменной?
print("Правильность на обучающем наборе: {:.2f}".format(lr.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.2f}".format(lr.score(X_test, y_test)))

X, y = mglearn.datasets.load_extended_boston()
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
lr = LinearRegression().fit(X_train, y_train) #Обучает новую модель линейной регрессии на расширенном наборе данных

#выясняется, что мы очень точно предсказываем на обучающем наборе, однако R2 на тестовом наборе имеет довольно низкое значение
#это явный признак переобучения; мы должны найти модель, которая позволит нам контролировать сложность
print("Правильность на обучающем наборе: {:.2f}".format(lr.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.2f}".format(lr.score(X_test, y_test)))

#Гребневая регрессия; нужно, чтобы величина коэффициентов была как можно меньше
from sklearn.linear_model import Ridge
ridge = Ridge().fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.2f}".format(ridge.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.2f}".format(ridge.score(X_test, y_test)))

#Менее сложная модель означает меньшую правильность на обучающем наборе, но лучшую обобщающую способность.
#Поскольку нас интересует только обобщающая способность, мы должны выбрать модель Ridge вместо модели LinearRegression

#Компромисс между простотой модели и качеством работы на обучающем наборе может быть задан пользователем при помощи параметра alpha

#Увеличение alpha заставляет коэффициенты сжиматься до близких к нулю значений, что снижает качество работы модели на обучающем наборе,
#но может улучшить ее обобщающую способность
ridge10 = Ridge(alpha=10).fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.2f}".format(ridge10.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.2f}".format(ridge10.score(X_test, y_test)))

ridge01 = Ridge(alpha=0.1).fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.2f}".format(ridge01.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.2f}".format(ridge01.score(X_test, y_test)))

#внимание на то, как параметр alpha соотносится со сложностью модели
plt.plot(ridge.coef_, 's', label="Гребневая регрессия alpha=1")
plt.plot(ridge10.coef_, '^', label="Гребневая регрессия alpha=10")
plt.plot(ridge01.coef_, 'v', label="Гребневая регрессия alpha=0.1")

#Строит кривые обучения, демонстрирующие качество моделей в зависимости от объема обучающего набора
plt.plot(lr.coef_, 'o', label="Линейная регрессия")
plt.xlabel("Индекс коэффициента")

plt.ylabel("Оценка коэффициента")
plt.hlines(0, 0, len(lr.coef_))
plt.ylim(-25, 25)
plt.legend()
plt.show()

#показывают качество работы модели в виде функции от объема набора данных, их еще называют кривыми обучения
mglearn.plots.plot_ridge_n_samples()
plt.show()

#Лассо
#Альтернативой Ridge как метода регуляризации линейной регрессии является Lasso. Как и гребневая регрессия, лассо также сжимает коэффициенты до близких к нулю значений
from sklearn.linear_model import Lasso
lasso = Lasso().fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.2f}".format(lasso.score(X_train, y_train)))
print("Правильность на контрольном наборе: {:.2f}".format(lasso.score(X_test, y_test)))
print("Количество использованных признаков: {}".format(np.sum(lasso.coef_ != 0)))

lasso001 = Lasso(alpha=0.01, max_iter=100000).fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.2f}".format(lasso001.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.2f}".format(lasso001.score(X_test, y_test)))
print("Количество использованных признаков: {}".format(np.sum(lasso001.coef_ != 0)))

#Чтобы снизить недообучение, давайте попробуем уменьшить alpha. При этом нам нужно увеличить значение max_iter (максимальное количество итераций
lasso00001 = Lasso(alpha=0.0001, max_iter=100000).fit(X_train, y_train)
print("Правильность на обучающем наборе: {:.2f}".format(lasso00001.score(X_train, y_train)))
print("Правильность на тестовом наборе: {:.2f}".format(lasso00001.score(X_test, y_test)))
print("Количество использованных признаков: {}".format(np.sum(lasso00001.coef_ != 0)))

#визуализация лассо-регрессии
plt.plot(lasso.coef_, 's', label="Лассо alpha=1")
plt.plot(lasso001.coef_, '^', label="Лассо alpha=0.01")
plt.plot(lasso00001.coef_, 'v', label="Лассо alpha=0.0001")

plt.plot(ridge01.coef_, 'o', label="Гребневая регрессия alpha=0.1")
plt.legend(ncol=2, loc=(0, 1.05))
plt.ylim(-25, 25)
plt.xlabel("Индекс коэффициента")
plt.ylabel("Оценка коэффициента")
plt.show()