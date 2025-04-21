import unittest
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

class TestDoramaClub(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Инициализация браузера
        cls.driver = webdriver.Chrome()
        cls.driver.get('https://doramy.club/regs-login')
        time.sleep(2)  # Задержка для загрузки страницы

    def test_login_and_find_dorama(self):
        # Авторизация
        self.driver.find_element(By.NAME, 'log').send_keys('MyName')
        self.driver.find_element(By.NAME, 'pwd').send_keys('password', Keys.RETURN)
        print("Выполнен вход в систему.")

        # Явное ожидание для открытия главной страницы
        WebDriverWait(self.driver, 10).until(EC.url_to_be('https://doramy.club/'))
        print("Главная страница загружена.")

        # Тест-кейсы
        # 1. Проверка наличия дорамы
        self.driver.get('https://doramy.club/regs-view/?preview=true')
        product_name = 'Остров'
        WebDriverWait(self.driver, 10).until(EC.presence_of_element_located((By.XPATH, f"//*[contains(text(), '{product_name}')]")))
        assert product_name in self.driver.page_source
        print(f"Дорама '{product_name}' найдена на странице.")

        # 2. Ожидание и переход на страницу дорамы
        WebDriverWait(self.driver, 10).until(EC.presence_of_element_located((By.XPATH, f"//*[contains(text(), '{product_name}')]"))).click()
        assert product_name in self.driver.title
        print(f"Открыта страница дорамы '{product_name}'.")

    @classmethod
    def tearDownClass(cls):
        # Закрытие браузера
        time.sleep(5)  # Задержка для просмотра результатов
        cls.driver.quit()

if __name__ == '__main__':
    unittest.main()
