import unittest
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

class TestChitaiGorod(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Инициализация браузера
        cls.driver = webdriver.Chrome()
        cls.driver.get('https://www.chitai-gorod.ru/')
        WebDriverWait(cls.driver, 10).until(EC.title_contains("Читай-город"))
        print("Главная страница загружена.")

    def test_add_book_to_cart(self):
        # 1. Перейти на страницу "Распродажа"
        WebDriverWait(self.driver, 10).until(EC.presence_of_element_located((By.XPATH, "//*[contains(text(), 'Распродажа')]"))).click()
        print("Перешли на страницу распродаж.")

        # 2. Выбрать книгу и добавить в корзину
        WebDriverWait(self.driver, 10).until(EC.element_to_be_clickable((By.XPATH, "//div[@class='button action-button blue'][1]//span"))).click()
        print("Книга добавлена в корзину.")

        # 3. Перейти на страницу корзины
        WebDriverWait(self.driver, 10).until(EC.element_to_be_clickable((By.XPATH, "//a[@href='/cart']"))).click()
        print("Перешли на страницу корзины.")

        # 4. Убедиться, что книга в корзине
        WebDriverWait(self.driver, 10).until(EC.presence_of_element_located((By.XPATH, "//div[@class='cart-item']")))
        print("Книга успешно добавлена в корзину.")

        # Проверяем, что книга действительно добавлена в корзину
        assert "Книга" in self.driver.page_source
        print("Тестирование выполнено.")

    @classmethod
    def tearDownClass(cls):
        # Закрытие браузера
        time.sleep(5)  # Задержка для просмотра результатов
        cls.driver.quit()

if __name__ == '__main__':
    unittest.main()