from selenium.webdriver.common.by import By
#from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

class MainPage:
    def __init__(self, driver):
        self.driver = driver #для работы с эл-тами на странице

    def search_element_by_id(self, element_id):
        return self.driver.find_element(By.ID, element_id)

    def search_element_by_name(self, name):
        return self.driver.find_element(By.NAME, name)

    def get_promotion_link(self):
        return self.driver.find_element(By.XPATH, '//a[contains(@href, "promotions") and contains(text(), "Акции")]')

    def go_to_sale(self):
        WebDriverWait(self.driver, 10).until(
            EC.presence_of_element_located((By.XPATH, "//*[contains(text(), 'Распродажа')]"))
        ).click()

    def add_first_book_to_cart(self):
        WebDriverWait(self.driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//div[@class='button action-button blue'][1]//span"))
        ).click()

    def go_to_cart(self):
        WebDriverWait(self.driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//a[@href='/cart']"))
        ).click()

    def take_screenshot(self, filename):
        self.driver.save_screenshot(filename)

    def print_cookies(self):
        cookies = self.driver.get_cookies()
        print("Текущие куки:")
        for cookie in cookies:
            print(cookie)