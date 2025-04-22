import unittest
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
from pages.dorama_page import DoramaPage
import time

class TestDoramaGenres(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Настраиваем опции браузера
        options = webdriver.ChromeOptions()
        options.add_argument('--ignore-certificate-errors')
        options.add_argument('--start-maximized')  # Запуск в полноэкранном режиме

        # Запускаем браузер
        cls.driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)
        cls.dorama_page = DoramaPage(cls.driver)
        cls.dorama_page.open()
        print("Главная страница загружена.")

    def test_select_genre_melodrama(self):
        self.dorama_page.click_genres_menu()
        self.dorama_page.wait_for_genres_dropdown()
        print("Открыт выпадающий список 'Жанры'.")

        self.dorama_page.select_melodrama()
        print("Выбран жанр 'Мелодрама'.")

        self.assertTrue(self.dorama_page.is_on_melodrama_page())
        print("Переход на жанр 'Мелодрама' успешно выполнен.")

        # Запись скриншота
        self.dorama_page.take_screenshot('screenshots/test_screenshot_list.png')

        # Демонстрация работы с куками
        self.dorama_page.print_cookies()

    #@unittest.skip("Пропускаем test_search_with_different_params на данный момент.")
    def test_search_with_different_params(self):
        search_params = [
            ('БТС на лужайке', 'БТС на лужайке')
        ]

        for search_term, expected_text in search_params:
            with self.subTest(search_term=search_term): #оздает подтест для каждого значения (позволяет изолировать результаты)
                search_box = self.dorama_page.search_element_by_name('s')
                search_box.clear()  # Очищаем поле ввода
                search_box.send_keys(search_term) #ввод данных
                search_box.submit()  # Отправляем форму

                time.sleep(5)  # Задержка для загрузки результатов

                # Проверка наличия ожидаемого текста на странице
                self.assertIn(expected_text, self.driver.page_source)
                print(f'Поиск по "{search_term}" выполнен успешно.')

    @classmethod
    def tearDownClass(cls):
        # Немного подождать и закрыть браузер
        time.sleep(2)
        cls.driver.quit()

if __name__ == '__main__':
    unittest.main()