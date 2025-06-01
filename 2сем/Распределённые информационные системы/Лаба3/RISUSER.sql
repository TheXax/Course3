CREATE DATABASE LINK DIV_TO_SVA
  CONNECT TO DIV IDENTIFIED BY "1111"  -- логин и пароль для студента DIV
  USING 'RIS';  -- Название TNS-сервиса для подключения к серверу DIV
 
  SELECT * FROM RISV@DIV_TO_SVA;
  
  CREATE TABLE RISD (
   id NUMBER PRIMARY KEY,
   name VARCHAR2(255) NOT NULL
);

select * from RISD

Delete from RISD
drop table RISD
INSERT INTO RISD (id, name) VALUES (1, 'Alice');
INSERT INTO RISD (id, name) VALUES (2, 'Bob');
INSERT INTO RISD (id, name) VALUES (3, 'Charlie');
INSERT INTO RISD (id, name) VALUES (4, 'David');
INSERT INTO RISD (id, name) VALUES (5, 'Ivan');
COMMIT;
SELECT * FROM RISD

//Транзакции
--4)Разработка SQL-скрипта для распределённых транзакций
--INSERT/INSERT
BEGIN
   INSERT INTO RISD (id, name) VALUES (1, 'Misha');
   INSERT INTO RISV@DIV_TO_SVA(id, name) VALUES (2, 'Pasha');
   COMMIT;
END;

select *from RISD
SELECT * FROM RISV@DIV_TO_SVA;

--INSERT/UPDATE
BEGIN
   INSERT INTO RISD (id, name) VALUES (3, 'Sasha');
   UPDATE RISV@DIV_TO_SVA SET name = 'Sasha' WHERE id = 1;
   COMMIT;
END;

--UPDATE/INSERT
BEGIN
   UPDATE RISD SET name = 'Gleb' WHERE id = 3;
   INSERT INTO RISV@DIV_TO_SVA (id, name) VALUES (4, 'Vlad');
   COMMIT;
END;

--5)Смоделировать ошибку нарушения целостности
--Транзакция с нарушением ограничения целостности
BEGIN
   INSERT INTO RISD (id, name) VALUES (5, 'Petr');
   INSERT INTO RISV@DIV_TO_SVA (id, name) VALUES (1, 'Invalid Item');
   COMMIT;
END;

--6)Смоделировать блокировку ресурсов
-- блокировка
BEGIN
    INSERT INTO RISD (id, name) VALUES (5, 'Petr');
   DELETE FROM RISV@DIV_TO_SVA WHERE id = 1;
END;
-- разблокировка
   COMMIT;
-- ожидание
BEGIN
   -- Эта транзакция будет пытаться обновить строку с id = 1, которая заблокирована на сервере DIV
   UPDATE RISD SET name = 'Grace Updated' WHERE id = 1;
   COMMIT;
END;