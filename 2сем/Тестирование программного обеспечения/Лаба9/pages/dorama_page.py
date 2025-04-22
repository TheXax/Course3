# pages/dorama_page.py
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

class DoramaPage:
    def __init__(self, driver):
        self.driver = driver

    def open(self):
        self.driver.get("https://doramy.club")

    def click_genres_menu(self):
        genres_menu = WebDriverWait(self.driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//div[contains(@class, 'knop m1')]"))
        )
        genres_menu.click()

    def wait_for_genres_dropdown(self):
        WebDriverWait(self.driver, 10).until(
            EC.visibility_of_element_located((By.XPATH, "//ul[contains(@class, 'drop m1') and @style='display: block;']"))
        )

    def select_melodrama(self):
        melodrama_link = WebDriverWait(self.driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//ul[contains(@class, 'drop m1')]//a[contains(text(),'Мелодрама')]"))
        )
        melodrama_link.click()

    def is_on_melodrama_page(self):
        return WebDriverWait(self.driver, 10).until(
            EC.url_to_be("https://doramy.club/genre/melodrama")
        )

    def search_element_by_name(self, name):
        return self.driver.find_element(By.NAME, name)

    def is_dorama_present(self, product_name):
        WebDriverWait(self.driver, 10).until(
            EC.presence_of_element_located((By.XPATH, f"//*[contains(text(), '{product_name}')]"))
        )
        return product_name in self.driver.page_source

    def go_to_dorama(self, product_name):
        WebDriverWait(self.driver, 10).until(
            EC.presence_of_element_located((By.XPATH, f"//*[contains(text(), '{product_name}')]"))
        ).click()

    def take_screenshot(self, filename):
        self.driver.save_screenshot(filename)

    def print_cookies(self):
        cookies = self.driver.get_cookies() # возвращает список всех куки, хранящихся в текущем сеансе браузера
        print("Текущие куки:")
        for cookie in cookies:
            print(cookie)