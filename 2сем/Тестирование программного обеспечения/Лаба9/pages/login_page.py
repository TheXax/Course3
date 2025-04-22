from selenium.webdriver.common.by import By

class LoginPage:
    def __init__(self, driver):
        self.driver = driver

    def enter_username(self, username):
        self.driver.find_element(By.NAME, 'log').send_keys(username)

    def enter_password(self, password):
        self.driver.find_element(By.NAME, 'pwd').send_keys(password)

    def submit(self):
        self.driver.find_element(By.NAME, 'pwd').submit()