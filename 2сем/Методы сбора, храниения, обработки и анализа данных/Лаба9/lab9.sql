-- 1. Создание таблиц
CREATE TABLE People (
    person_id NUMBER PRIMARY KEY,
    full_name VARCHAR2(100)
);

CREATE TABLE BusinessTrips (
    trip_id NUMBER PRIMARY KEY,
    person_id NUMBER,
    destination VARCHAR2(100),
    start_date DATE,
    end_date DATE,
    FOREIGN KEY (person_id) REFERENCES People(person_id)
);


-- Создание временных таблиц для выборки данных из коллекций
CREATE GLOBAL TEMPORARY TABLE TempPeople AS SELECT * FROM People WHERE 1=0;
CREATE GLOBAL TEMPORARY TABLE TempBusinessTrips AS SELECT * FROM BusinessTrips WHERE 1=0;


-- 2. Создание объектных типов
CREATE OR REPLACE TYPE PersonType AS OBJECT (
    person_id NUMBER,
    full_name VARCHAR2(100)
);

CREATE OR REPLACE TYPE TripType AS OBJECT (
    trip_id NUMBER,
    destination VARCHAR2(100),
    start_date DATE,
    end_date DATE
);

CREATE OR REPLACE TYPE TripCollection AS TABLE OF TripType;

CREATE OR REPLACE TYPE PersonCollection AS TABLE OF PersonType;

-- 3. Работа с коллекциями
DECLARE
    k1 PersonCollection := PersonCollection();
    k2 TripCollection := TripCollection();
BEGIN
    -- Добавление данных в коллекцию K1 (Люди)
    k1.EXTEND(2);
    k1(1) := PersonType(1, 'Иван Иванов');
    k1(2) := PersonType(2, 'Петр Петров');
    
    -- Добавление данных в коллекцию K2 (Командировки)
    k2.EXTEND(2);
    k2(1) := TripType(101, 'Москва', TO_DATE('2025-02-01', 'YYYY-MM-DD'), TO_DATE('2025-02-05', 'YYYY-MM-DD'));
    k2(2) := TripType(102, 'Минск', TO_DATE('2025-03-10', 'YYYY-MM-DD'), TO_DATE('2025-03-15', 'YYYY-MM-DD'));


    -- Вставка данных из коллекции K1 в временную таблицу
    FOR i IN 1..k1.COUNT LOOP
        INSERT INTO TempPeople VALUES (k1(i).person_id, k1(i).full_name);
    END LOOP;

    -- Вставка данных из коллекции K2 в временную таблицу
    FOR j IN 1..k2.COUNT LOOP
        INSERT INTO TempBusinessTrips VALUES (k2(j).trip_id, NULL, k2(j).destination, k2(j).start_date, k2(j).end_date);
    END LOOP;


    -- Выяснить, какие командировки пересекаются
    FOR i IN 1..k1.COUNT LOOP
        DBMS_OUTPUT.PUT_LINE('Сотрудник: ' || k1(i).full_name || ' отправлялся в командировку:');
        FOR j IN 1..k2.COUNT LOOP
            DBMS_OUTPUT.PUT_LINE('- ' || k2(j).destination || ' (' || TO_CHAR(k2(j).start_date, 'DD.MM.YYYY') || ' - ' || TO_CHAR(k2(j).end_date, 'DD.MM.YYYY') || ')');
        END LOOP;
    END LOOP;

    -- Проверка, является ли элемент частью коллекции K1
    DECLARE
        check_person PersonType := PersonType(1, 'Иван Иванов');
        found BOOLEAN := FALSE;
    BEGIN
        FOR i IN 1..k1.COUNT LOOP
            IF k1(i).person_id = check_person.person_id THEN
                found := TRUE;
                EXIT;
            END IF;
        END LOOP;
        IF found THEN
            DBMS_OUTPUT.PUT_LINE('Элемент найден в K1');
        ELSE
            DBMS_OUTPUT.PUT_LINE('Элемент не найден в K1');
        END IF;
    END;

    -- Поиск пустых коллекций K1
    IF k1 IS EMPTY THEN
        DBMS_OUTPUT.PUT_LINE('Коллекция K1 пуста');
    ELSE
        DBMS_OUTPUT.PUT_LINE('Коллекция K1 содержит данные');
    END IF;

    -- Обмен атрибутами K2 между двумя элементами K1
    IF k1.COUNT > 1 THEN
        DECLARE
            temp PersonType;
        BEGIN
            temp := k1(1);
            k1(1) := k1(2);
            k1(2) := temp;
            DBMS_OUTPUT.PUT_LINE('Атрибуты обменены');
        END;
    END IF;
END;

-- 4. Преобразование коллекции в реляционные данные
SELECT * FROM TempPeople;
SELECT * FROM TempBusinessTrips;

-- 5. Применение BULK операций
DECLARE
    TYPE TripTableType IS TABLE OF TripType INDEX BY PLS_INTEGER;
    t_table TripTableType;
BEGIN
    -- Заполнение временной таблицы данными из коллекции K2
    INSERT INTO TempBusinessTrips (trip_id, destination, start_date, end_date)
    VALUES (101, 'Москва', TO_DATE('2025-02-01', 'YYYY-MM-DD'), TO_DATE('2025-02-05', 'YYYY-MM-DD'));

    INSERT INTO TempBusinessTrips (trip_id, destination, start_date, end_date)
    VALUES (102, 'Минск', TO_DATE('2025-03-10', 'YYYY-MM-DD'), TO_DATE('2025-03-15', 'YYYY-MM-DD'));

    -- Теперь используем BULK COLLECT для выборки данных из временной таблицы
    SELECT TripType(trip_id, destination, start_date, end_date)
    BULK COLLECT INTO t_table FROM TempBusinessTrips;

    -- Перебор собранных данных и вывод информации
    FOR i IN t_table.FIRST .. t_table.LAST LOOP
        DBMS_OUTPUT.PUT_LINE('Командировка: ' || t_table(i).destination);
    END LOOP;
END;

