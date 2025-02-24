-- 1. �������� ������
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


-- �������� ��������� ������ ��� ������� ������ �� ���������
CREATE GLOBAL TEMPORARY TABLE TempPeople AS SELECT * FROM People WHERE 1=0;
CREATE GLOBAL TEMPORARY TABLE TempBusinessTrips AS SELECT * FROM BusinessTrips WHERE 1=0;


-- 2. �������� ��������� �����
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

-- 3. ������ � �����������
DECLARE
    k1 PersonCollection := PersonCollection();
    k2 TripCollection := TripCollection();
BEGIN
    -- ���������� ������ � ��������� K1 (����)
    k1.EXTEND(2);
    k1(1) := PersonType(1, '���� ������');
    k1(2) := PersonType(2, '���� ������');
    
    -- ���������� ������ � ��������� K2 (������������)
    k2.EXTEND(2);
    k2(1) := TripType(101, '������', TO_DATE('2025-02-01', 'YYYY-MM-DD'), TO_DATE('2025-02-05', 'YYYY-MM-DD'));
    k2(2) := TripType(102, '�����', TO_DATE('2025-03-10', 'YYYY-MM-DD'), TO_DATE('2025-03-15', 'YYYY-MM-DD'));


    -- ������� ������ �� ��������� K1 � ��������� �������
    FOR i IN 1..k1.COUNT LOOP
        INSERT INTO TempPeople VALUES (k1(i).person_id, k1(i).full_name);
    END LOOP;

    -- ������� ������ �� ��������� K2 � ��������� �������
    FOR j IN 1..k2.COUNT LOOP
        INSERT INTO TempBusinessTrips VALUES (k2(j).trip_id, NULL, k2(j).destination, k2(j).start_date, k2(j).end_date);
    END LOOP;


    -- ��������, ����� ������������ ������������
    FOR i IN 1..k1.COUNT LOOP
        DBMS_OUTPUT.PUT_LINE('���������: ' || k1(i).full_name || ' ����������� � ������������:');
        FOR j IN 1..k2.COUNT LOOP
            DBMS_OUTPUT.PUT_LINE('- ' || k2(j).destination || ' (' || TO_CHAR(k2(j).start_date, 'DD.MM.YYYY') || ' - ' || TO_CHAR(k2(j).end_date, 'DD.MM.YYYY') || ')');
        END LOOP;
    END LOOP;

    -- ��������, �������� �� ������� ������ ��������� K1
    DECLARE
        check_person PersonType := PersonType(1, '���� ������');
        found BOOLEAN := FALSE;
    BEGIN
        FOR i IN 1..k1.COUNT LOOP
            IF k1(i).person_id = check_person.person_id THEN
                found := TRUE;
                EXIT;
            END IF;
        END LOOP;
        IF found THEN
            DBMS_OUTPUT.PUT_LINE('������� ������ � K1');
        ELSE
            DBMS_OUTPUT.PUT_LINE('������� �� ������ � K1');
        END IF;
    END;

    -- ����� ������ ��������� K1
    IF k1 IS EMPTY THEN
        DBMS_OUTPUT.PUT_LINE('��������� K1 �����');
    ELSE
        DBMS_OUTPUT.PUT_LINE('��������� K1 �������� ������');
    END IF;

    -- ����� ���������� K2 ����� ����� ���������� K1
    IF k1.COUNT > 1 THEN
        DECLARE
            temp PersonType;
        BEGIN
            temp := k1(1);
            k1(1) := k1(2);
            k1(2) := temp;
            DBMS_OUTPUT.PUT_LINE('�������� ��������');
        END;
    END IF;
END;

-- 4. �������������� ��������� � ����������� ������
SELECT * FROM TempPeople;
SELECT * FROM TempBusinessTrips;

-- 5. ���������� BULK ��������
DECLARE
    TYPE TripTableType IS TABLE OF TripType INDEX BY PLS_INTEGER;
    t_table TripTableType;
BEGIN
    -- ���������� ��������� ������� ������� �� ��������� K2
    INSERT INTO TempBusinessTrips (trip_id, destination, start_date, end_date)
    VALUES (101, '������', TO_DATE('2025-02-01', 'YYYY-MM-DD'), TO_DATE('2025-02-05', 'YYYY-MM-DD'));

    INSERT INTO TempBusinessTrips (trip_id, destination, start_date, end_date)
    VALUES (102, '�����', TO_DATE('2025-03-10', 'YYYY-MM-DD'), TO_DATE('2025-03-15', 'YYYY-MM-DD'));

    -- ������ ���������� BULK COLLECT ��� ������� ������ �� ��������� �������
    SELECT TripType(trip_id, destination, start_date, end_date)
    BULK COLLECT INTO t_table FROM TempBusinessTrips;

    -- ������� ��������� ������ � ����� ����������
    FOR i IN t_table.FIRST .. t_table.LAST LOOP
        DBMS_OUTPUT.PUT_LINE('������������: ' || t_table(i).destination);
    END LOOP;
END;

