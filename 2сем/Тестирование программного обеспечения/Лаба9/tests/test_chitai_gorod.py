import unittest
from selenium import webdriver
from pages.main_page import MainPage #класс, который реализует POM для главной страницы
import time

class TestChitaiGorod(unittest.TestCase):
    @classmethod
    def setUpClass(cls): #запуск перед выполнением всех тестов
        options = webdriver.ChromeOptions()
        options.add_argument('--ignore-certificate-errors') #Настраивается браузер Chrome с опцией игнорирования ошибок сертификатов.
        cls.driver = webdriver.Chrome(options=options)
        cls.driver.get('https://www.chitai-gorod.ru/')
        time.sleep(5)
        cls.main_page = MainPage(cls.driver)

    def test_find_elements(self):
        results = []

        # Поиск элемента по ID
        try:
            element = self.main_page.search_element_by_id('__nuxt')
            results.append(f'Найден элемент по ID: {element.get_attribute("placeholder")}')
        except Exception:
            results.append('Элемент не найден по ID')

        # Поиск элемента по имени
        try:
            element = self.main_page.search_element_by_name('search')
            results.append(f'Найден элемент по NAME: {element.get_attribute("placeholder")}')
        except Exception:
            results.append('Элемент не найден по NAME')

        # Поиск по XPath
        try:
            link = self.main_page.get_promotion_link()
            results.append(f'Найден элемент по XPath: {link.text}')
        except Exception:
            results.append('Элемент не найден по XPath')

        # Запись скриншота
        self.main_page.take_screenshot('screenshots/test_screenshot.png')

        # Вывод результатов
        for result in results:
            print(result)

        # Демонстрация работы с куками
        self.main_page.print_cookies()

    @unittest.skip("Пропускаем test_search_with_different_params на данный момент.")
    def test_search_with_different_params(self):
        search_params = [
            ('Аватар', 'Аватар')
        ]

        for search_term, expected_text in search_params:
            with self.subTest(search_term=search_term):
                search_box = self.main_page.search_element_by_name('search')
                search_box.clear()  # Очищаем поле ввода
                search_box.send_keys(search_term)
                search_box.submit()  # Отправляем форму

                time.sleep(5)  # Задержка для загрузки результатов

                # Проверка наличия ожидаемого текста на странице
                self.assertIn(expected_text, self.driver.page_source)
                print(f'Поиск по "{search_term}" выполнен успешно.')
    
    #закрытие браузера
    @classmethod
    def tearDownClass(cls):
        cls.driver.quit()

if __name__ == '__main__':
    unittest.main()