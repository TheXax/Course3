import unittest
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from webdriver_manager.chrome import ChromeDriverManager
from pages.main_page import MainPage
from pages.cart_page import CartPage
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

class TestBuyBook(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Настройка опций браузера
        options = Options()
        options.add_argument('--ignore-certificate-errors')
        options.add_argument('--start-maximized')  # Запуск в полноэкранном режиме

        # Инициализация браузера
        cls.driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)
        cls.driver.get('https://www.chitai-gorod.ru/')
        WebDriverWait(cls.driver, 10).until(EC.title_contains("Читай-город"))
        print("Главная страница загружена.")

        cls.main_page = MainPage(cls.driver)
        cls.cart_page = CartPage(cls.driver)

    def test_add_book_to_cart(self):
        # 1. Перейти на страницу "Распродажа"
        self.main_page.go_to_sale()
        print("Перешли на страницу распродаж.")

        # 2. Выбрать книгу и добавить в корзину
        self.main_page.add_first_book_to_cart()
        print("Книга добавлена в корзину.")

        # 3. Перейти на страницу корзины
        self.main_page.go_to_cart()
        print("Перешли на страницу корзины.")

        # 4. Убедиться, что книга в корзине
        assert self.cart_page.is_book_in_cart()
        print("Книга успешно добавлена в корзину.")
        print("Тестирование выполнено.")

        # Запись скриншота
        self.main_page.take_screenshot('screenshots/test_buyBook.png')

        # Демонстрация работы с куками
        self.main_page.print_cookies()

    #@unittest.skip("Пропускаем test_search_with_different_params на данный момент.")
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

    @classmethod
    def tearDownClass(cls):
        # Закрытие браузера
        time.sleep(5)  # Задержка для просмотра результатов
        cls.driver.quit()

if __name__ == '__main__':
    unittest.main()