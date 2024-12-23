--Лицензии и места использования

--1.Создать объектные типы данных по своему варианту:
-- Тип для представления лицензий
CREATE OR REPLACE TYPE LicenseTypeObject AS OBJECT (
    id_license NUMBER,
    software_name NVARCHAR2(255),
    place_of_use NVARCHAR2(255),
    purchase_date DATE,
    expiration_date DATE,
    license_cost NUMBER(9, 2),

    -- Дополнительный конструктор
    --Создаёт объект с заданными значениями атрибутов
    CONSTRUCTOR FUNCTION LicenseTypeObject(
        --self - ссылка на текущий объект
        --IN OUT NOCOPY указывает, что объект передаётся по ссылке для повышения производительности
        self IN OUT NOCOPY LicenseTypeObject,
        id_license NUMBER, 
        software_name NVARCHAR2, 
        place_of_use NVARCHAR2,
        purchase_date DATE, 
        expiration_date DATE, 
        license_cost NUMBER
    ) RETURN SELF AS RESULT, --возврат созданного объекта

    -- Метод сравнения
    MAP MEMBER FUNCTION to_map RETURN DATE,

    -- Метод экземпляра: Функция для расчёта оставшихся дней
    MEMBER FUNCTION days_left RETURN NUMBER,

    -- Метод экземпляра: Процедура для обновления стоимости лицензии
    MEMBER PROCEDURE update_cost(new_cost NUMBER)
);

------------------
-- Реализация методов (создаёт тело объектного типа)
CREATE OR REPLACE TYPE BODY LicenseTypeObject AS
    CONSTRUCTOR FUNCTION LicenseTypeObject( --конструктор создаёт экземпляр с параметрами
        self IN OUT NOCOPY LicenseTypeObject,
        id_license NUMBER, 
        software_name NVARCHAR2, 
        place_of_use NVARCHAR2,
        purchase_date DATE, 
        expiration_date DATE, 
        license_cost NUMBER
    ) RETURN SELF AS RESULT IS
    BEGIN --инициализация
        self.id_license := id_license;
        self.software_name := software_name;
        self.place_of_use := place_of_use;
        self.purchase_date := purchase_date;
        self.expiration_date := expiration_date;
        self.license_cost := license_cost;
        RETURN;
    END;
    
    --сортировка по дате истечения лицензии
    MAP MEMBER FUNCTION to_map RETURN DATE IS
    BEGIN
        RETURN expiration_date; -- Сравнение по дате истечения
    END;

    MEMBER FUNCTION days_left RETURN NUMBER IS
    BEGIN
        RETURN expiration_date - SYSDATE;
    END;

    MEMBER PROCEDURE update_cost(new_cost NUMBER) IS
    BEGIN
        self.license_cost := new_cost;
    END;
END;
---------

--реализиция MAP
SELECT * FROM LicenseObjectsNew o ORDER BY VALUE(o).to_map();

--вернёт значения, если до истечения лицензии больше 30 дней
SELECT VALUE(o).id_license AS id_license, VALUE(o).days_left() AS days_left
FROM LicenseObjectsNew o
WHERE VALUE(o).days_left() > 30;


--не работает, не показывать!!!!!
DECLARE
    l LicenseTypeObject;
BEGIN
    -- Создание объекта
    l := LicenseTypeObject(1, 'Windows', 'Office', TO_DATE('2024-07-01', 'YYYY-MM-DD'), TO_DATE('2025-07-01', 'YYYY-MM-DD'), 100.00);
    -- Обновление стоимости
    l.update_cost(120.00);
    -- Вывод обновлённого значения
    --DBMS_OUTPUT.PUT_LINE('Updated cost: ' || l.license_cost);
END;



--2.Скопировать данные из реляционных таблиц в объектные.
CREATE TABLE LicenseObjectsNew OF LicenseTypeObject;

INSERT INTO LicenseObjectsNew
SELECT 
    l.id_license,
    s.softwareName,
    'Default Place', 
    l.purchaseDate,
    l.expirationDate,
    l.license_cost
FROM Licenses l
    JOIN Software s ON l.softwareId = s.id_software;

select * from LicenseObjectsNew

--3.Продемонстрировать применение объектных представлений.
--создание представления
CREATE OR REPLACE VIEW LicenseViewNew OF LicenseTypeObject 
WITH OBJECT IDENTIFIER (id_license)
AS
SELECT 
    l.id_license,
    s.softwareName,
    N'Default Place',
    l.purchaseDate,
    l.expirationDate,
    l.license_cost
FROM Licenses l JOIN Software s ON l.softwareId = s.id_software;

--пример использования
SELECT * FROM LicenseViewNew;

SELECT id_license, software_name, place_of_use
FROM LicenseView
WHERE license_cost > 100;



--4. Создание индекса.
CREATE INDEX idx_license_expiration ON LicenseObjects (expiration_date);

