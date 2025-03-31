import sympy as sp

# 2.1. Найдите производную функции f(x) = x^2 + 1
x = sp.symbols('x')
f = x**2 + 1
derivative = sp.diff(f, x)
print("Производная f(x) = x^2 + 1:", derivative)

# 2.2. Найдите интеграл функции f(x) = x^2 + 1 на отрезке [0, 1]
integral = sp.integrate(f, (x, 0, 1))
print("Интеграл f(x) на [0, 1]:", integral)

# 2.3. Найдите предел функции f(x) = 1/(x^2 + 1) при x→∞
limit = sp.limit(1/(x**2 + 1), x, sp.oo)
print("Предел f(x) при x→∞:", limit)