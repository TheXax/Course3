import unittest
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

class TestDoramaGenres(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Запускаем браузер
        cls.driver = webdriver.Chrome()
        cls.driver.get("https://doramy.club")
        print("Главная страница загружена.")

    def test_select_genre_melodrama(self):
        # Явное ожидание появления меню "Жанры"
        genres_menu = WebDriverWait(self.driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//div[contains(@class, 'knop m1')]"))
        )
        genres_menu.click()

        # Ждем, пока подменю станет видимым (display: block)
        WebDriverWait(self.driver, 10).until(
            EC.visibility_of_element_located((By.XPATH, "//ul[contains(@class, 'drop m1') and @style='display: block;']"))
        )
        print("Открыт выпадающий список 'Жанры'.")

        # Кликаем на "Мелодрама"
        melodrama_link = WebDriverWait(self.driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//ul[contains(@class, 'drop m1')]//a[contains(text(),'Мелодрама')]"))
        )
        melodrama_link.click()
        print("Выбран жанр 'Мелодрама'.")

        # Проверяем, что открыта страница жанра "Мелодрама"
        WebDriverWait(self.driver, 10).until(
            EC.url_to_be("https://doramy.club/genre/melodrama")
        )
        print("Переход на жанр 'Мелодрама' успешно выполнен.")

    @classmethod
    def tearDownClass(cls):
        # Немного подождать и закрыть браузер
        time.sleep(2)
        cls.driver.quit()

if __name__ == '__main__':
    unittest.main()