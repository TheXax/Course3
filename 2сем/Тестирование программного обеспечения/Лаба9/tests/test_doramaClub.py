import unittest
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from webdriver_manager.chrome import ChromeDriverManager
from pages.login_page import LoginPage
from pages.dorama_page import DoramaPage
import time
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

class TestDoramaClub(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Настройка опций браузера
        options = Options()
        options.add_argument('--ignore-certificate-errors')
        options.add_argument('--start-maximized')  # Запуск в полноэкранном режиме

        # Инициализация браузера
        cls.driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)
        cls.driver.get('https://doramy.club/regs-login')
        time.sleep(2)  # Задержка для загрузки страницы
        cls.login_page = LoginPage(cls.driver)
        cls.dorama_page = DoramaPage(cls.driver)

    def test_login_and_find_dorama(self):
        # Авторизация
        self.login_page.enter_username('Melkaya05')
        self.login_page.enter_password('05052001')
        self.login_page.submit()
        print("Выполнен вход в систему.")

        # Явное ожидание для открытия главной страницы
        WebDriverWait(self.driver, 10).until(EC.url_to_be('https://doramy.club/'))
        print("Главная страница загружена.")

        # Тест-кейсы
        # 1. Проверка наличия дорамы
        self.driver.get('https://doramy.club/regs-view/?preview=true')
        product_name = 'Остров'
        assert self.dorama_page.is_dorama_present(product_name)
        print(f"Дорама '{product_name}' найдена на странице.")

        # 2. Ожидание и переход на страницу дорамы
        self.dorama_page.go_to_dorama(product_name)
        assert product_name in self.driver.title
        print(f"Открыта страница дорамы '{product_name}'.")

        # Запись скриншота
        self.dorama_page.take_screenshot('screenshots/test_doramaClub.png')

        # Демонстрация работы с куками
        self.dorama_page.print_cookies()

    #@unittest.skip("Пропускаем test_search_with_different_params на данный момент.")
    def test_search_with_different_params(self):
        search_params = [
            ('Деловое', 'Деловое')
        ]

        for search_term, expected_text in search_params:
            with self.subTest(search_term=search_term):
                search_box = self.dorama_page.search_element_by_name('s')
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