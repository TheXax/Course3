import unittest
from selenium import webdriver
from selenium.webdriver.common.by import By
import time

class TestChitaiGorod(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Инициализация браузера
        cls.driver = webdriver.Chrome()
        cls.driver.get('https://www.chitai-gorod.ru/')
        time.sleep(5)  # Задержка для загрузки страницы

    def test_find_elements(self):
        results = []

        # Поиск элемента по ID
        try:
            element = self.driver.find_element(By.ID, '__nuxt')
            results.append(f'Найден элемент по ID: {element.get_attribute("placeholder")}')
        except Exception:
            results.append('Элемент не найден по ID')

        # Поиск элемента по имени
        try:
            element = self.driver.find_element(By.NAME, 'search')
            results.append(f'Найден элемент по NAME: {element.get_attribute("placeholder")}')
        except Exception:
            results.append('Элемент не найден по NAME')

        # Поиск по CSS-селектору
        try:
            element = self.driver.find_element(By.CSS_SELECTOR, 'button.header__catalog-menu')
            results.append(f'Найден элемент по CSS: {element.text}')
        except Exception:
            results.append('Элемент не найден по CSS')

        # Поиск по CSS-селектору (пример 2)
        try:
            element = self.driver.find_element(By.CSS_SELECTOR, 'input[type="text"].search-form__input')
            results.append(f'Найден элемент по CSS (пример 2): {element.get_attribute("placeholder")}')
        except Exception:
            results.append('Элемент не найден по CSS (пример 2)')

        # Поиск по XPath
        try:
            element = self.driver.find_element(By.XPATH, '//a[contains(@href, "promotions") and contains(text(), "Акции")]')
            results.append(f'Найден элемент по XPath: {element.text}')
        except Exception:
            results.append('Элемент не найден по XPath')

        # Поиск по XPath (пример2)
        try:
            element = self.driver.find_element(By.XPATH, '//a[@class="header-bottom-item" and contains(text(), "Распродажа")]')
            results.append(f'Найден элемент по XPath (пример2): {element.text}')
        except Exception:
            results.append('Элемент не найден по XPath (пример2)')

        # Поиск по частичному тексту ссылки
        try:
            link = self.driver.find_element(By.PARTIAL_LINK_TEXT, 'Акции')
            results.append(f'Найден элемент по частичному тексту: {link.text}')
        except Exception:
            results.append('Элемент не найден по частичному тексту')

        # Поиск нескольких элементов (например, товары в каталоге)
        try:
            elements = self.driver.find_elements(By.CSS_SELECTOR, '.header-bottom')
            results.append('Найденные элементы в каталоге:')
            for el in elements:
                results.append(el.text)
        except Exception:
            results.append('Элементы не найдены')

        # Вывод результатов
        for result in results:
            print(result)

    @classmethod
    def tearDownClass(cls):
        # Закрытие браузера
        cls.driver.quit()

if __name__ == '__main__':
    unittest.main()