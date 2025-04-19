import matplotlib.pyplot as plt
import numpy as np

# 5.1. Постройте график функции f(x) = x^2 + 1
x_vals = np.linspace(-5, 5, 100) 
y_vals = x_vals**2 + 1
plt.figure()
plt.plot(x_vals, y_vals, label='f(x) = x^2 + 1')
plt.title('График функции')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.legend()
plt.grid()
plt.show()

# 5.2. Постройте график поверхности функции f(x, y) = x^2 + 2y^2 + 1
X = np.linspace(-5, 5, 100)
Y = np.linspace(-5, 5, 100)
X, Y = np.meshgrid(X, Y) 
Z = X**2 + 2*Y**2 + 1
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis') 
ax.set_title('График поверхности функции')
plt.show()

# 5.3. Постройте несколько видов диаграмм
plt.figure()
plt.bar(['A', 'B', 'C'], [3, 7, 5], color='blue')
plt.title('Столбчатая диаграмма')
plt.ylabel('Значения')
plt.show()

plt.figure()
plt.pie([3, 7, 5], labels=['A', 'B', 'C'], autopct='%1.1f%%')
plt.title('Круговая диаграмма')
plt.show()