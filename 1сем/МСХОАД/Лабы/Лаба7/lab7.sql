
--������������
CREATE TABLE LicensePlanB (
    year NUMBER,
    month NUMBER,
    room_class VARCHAR2(100),
    initial_licenses NUMBER,
    growth_rate NUMBER,
    obsolete_rate NUMBER
);


-- ������� ����� ������� ��� �������� ��������
CREATE TABLE LicensePlanBCalculated AS
SELECT year, month, room_class, initial_licenses, growth_rate, obsolete_rate, 0 AS licenses
FROM LicensePlanB;


ALTER TABLE LicensePlanBCalculated
ADD CONSTRAINT unique_year_month_room_class UNIQUE (year, month, room_class);


ALTER SESSION SET NLS_NUMERIC_CHARACTERS = '. ';

BEGIN
   FOR y IN 2023..2024 LOOP
      FOR m IN 1..12 LOOP
         FOR rc IN (SELECT 'ClassA' AS room_class FROM dual UNION ALL SELECT 'ClassB' AS room_class FROM dual) LOOP
            INSERT INTO LicensePlanB (year, month, room_class, initial_licenses, growth_rate, obsolete_rate) 
            SELECT y, m, rc.room_class, 
                   TRUNC(100 + DBMS_RANDOM.VALUE(0, 50)), -- ���������� TRUNC ������ ROUND ��� ����� �����
                   ROUND(0.03 + DBMS_RANDOM.VALUE(0, 0.02), 3), -- ������������� �������� �� 3 ������
                   ROUND(0.01 + DBMS_RANDOM.VALUE(0, 0.02), 3)  -- ������������� �������� �� 3 ������
            FROM dual
            WHERE NOT EXISTS (
               SELECT 1 FROM LicensePlanB 
               WHERE year = y AND month = m AND room_class = rc.room_class
            );
         END LOOP;
      END LOOP;
   END LOOP;
   COMMIT;
END;

SELECT * 
FROM LicensePlanB
ORDER BY year, month, room_class;


-- ��������� ������ ��� ������
INSERT INTO LicensePlanBCalculated (year, month, room_class, licenses)
SELECT year, month, room_class,
       ROUND(initial_licenses * (1 + growth_rate), 3) AS licenses
FROM LicensePlanB
WHERE month = 1;

-- ������ ��� ��������� �������
BEGIN
  FOR m IN 2..12 LOOP
    UPDATE LicensePlanBCalculated lc
    SET lc.licenses = (SELECT lc_prev.licenses * (1 - lc_prev.obsolete_rate)
                       FROM LicensePlanBCalculated lc_prev
                       WHERE lc_prev.year = lc.year
                         AND lc_prev.month = lc.month - 1
                         AND lc_prev.room_class = lc.room_class)
    WHERE lc.month = m;
  END LOOP;
END;


-- ����� ����������
SELECT c.year, c.month, c.room_class, 
       p.initial_licenses, p.growth_rate, p.obsolete_rate, c.licenses
FROM LicensePlanBCalculated c
LEFT JOIN LicensePlanB p
  ON c.year = p.year AND c.month = p.month AND c.room_class = p.room_class
ORDER BY c.year, c.month, c.room_class;
--����� ���������� �������� � ����������� �� ����������� ����� ������ (GROWTH_RATE) � ������������ (OBSOLETE_RATE).


--INITIAL_LICENSES:
--��� ������� ��������� (ROOM_CLASS) � ���������� ���� (YEAR) � ������ (MONTH) ���� ��������� ���������� ��������

--������������ ����� (GROWTH_RATE) � ����������� (OBSOLETE_RATE):
--����������� ����� (GROWTH_RATE) � ��������� ������������� ���������� �������� ��-�� ���������� ����� ������� ��� ���������.
-- ����������� (OBSOLETE_RATE) � ��������� ����������� ���������� �������� ��-�� ����������� ������������.

--������ �������� (LICENSES):
--�������: ���������� �������� = ������� ���������� �������� ? (1 + ����������� �����) ? (1 - ����������� �����������)

-----------------------------------------------------------------------------------
CREATE TABLE RoomLicenses (
    year NUMBER,               -- ���
    month NUMBER,              -- �����
    room_class VARCHAR2(50),   -- ����� ���������
    initial_licenses NUMBER,   -- ��������� ���������� ��������
    growth_rate NUMBER,        -- ���� ����� �������� (% � ���� ���������� �����)
    obsolete_rate NUMBER       -- ���� ����������� (% � ���� ���������� �����)
);

INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2024, 1, 'ClassA', 100, 0.05, 0.02);

INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2024, 1, 'ClassB', 200, 0.03, 0.01);

INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2024, 1, 'ClassC', 150, 0.04, 0.015);

-- ������ ��� 2025 ����
INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2025, 1, 'ClassA', 110, 0.04, 0.025); -- ����������������� ��������� �������� ��������

INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2025, 1, 'ClassB', 215, 0.02, 0.015);

INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2025, 1, 'ClassC', 165, 0.03, 0.02);

-- ������ ��� 2026 ����
INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2026, 1, 'ClassA', 120, 0.03, 0.03); -- ����������������� ��������� �������� ��������

INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2026, 1, 'ClassB', 225, 0.015, 0.02);

INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2026, 1, 'ClassC', 180, 0.02, 0.025);

-- ������ ��� 2027 ����
INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2027, 1, 'ClassA', 130, 0.02, 0.035);

INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2027, 1, 'ClassB', 235, 0.01, 0.025);

INSERT INTO RoomLicenses (year, month, room_class, initial_licenses, growth_rate, obsolete_rate)
VALUES (2027, 1, 'ClassC', 195, 0.015, 0.03);

WITH BaseData AS (
    SELECT year, 
           month, 
           room_class, 
           initial_licenses, 
           growth_rate, 
           obsolete_rate,
           CAST(NULL AS NUMBER) AS licenses -- ��������� ������� ��� ����������
    FROM RoomLicenses
)
SELECT year, 
       month, 
       room_class, 
       ROUND(licenses, 3) AS licenses -- ��������� ���������
FROM BaseData
MODEL
    PARTITION BY (room_class)
    DIMENSION BY (year, month) -- ���������� ��� � ����� ��� ���������
    MEASURES (initial_licenses, growth_rate, obsolete_rate, licenses)
    RULES AUTOMATIC ORDER (
        -- �������� ��� ������� ������
        licenses[ANY, 1] = initial_licenses[CV(year), 1] * (1 + growth_rate[CV(year), 1]),
        -- �������� ��� ��������� �������
        licenses[ANY, FOR month FROM 2 TO 12 INCREMENT 1] =
            NVL(licenses[CV(year), CV(month) - 1], 0) * 
            (1 - NVL(obsolete_rate[CV(year), CV(month)], 0)) * 
            (1 + NVL(growth_rate[CV(year), CV(month)], 0))
    )
ORDER BY room_class, year, month;


//������ ClassA, ClassB � ClassC � ��� ��������� ��������� (��� ������������, ���� ������ ��������)
//LICENSES � ������ ��������� � ��� ��������� ���������� �������� �� ����������� �����������, ����������� ��� ������� ������ (ClassA, ClassB, ClassC) �� �������� ����� � ���



//2.	������� ��� ������ ����������� MATCH_RECOGNIZE() ������, ������� ������������� �������: 
//����, �������, ���� ��������� �������� ��� ������� ���� ��
CREATE TABLE LicenseCostsCost (
    software_type VARCHAR2(50), -- ��� ��
    year NUMBER,               -- ���
    month NUMBER,              -- �����
    cost NUMBER                -- ��������� ��������
);

-- ������ ������
INSERT INTO LicenseCostsCost VALUES ('SoftwareA', 2024, 1, 100);
INSERT INTO LicenseCostsCost VALUES ('SoftwareA', 2024, 2, 110);
INSERT INTO LicenseCostsCost VALUES ('SoftwareA', 2024, 3, 105);
INSERT INTO LicenseCostsCost VALUES ('SoftwareA', 2024, 4, 115);
INSERT INTO LicenseCostsCost VALUES ('SoftwareA', 2024, 5, 120);

INSERT INTO LicenseCostsCost VALUES ('SoftwareB', 2024, 1, 200);
INSERT INTO LicenseCostsCost VALUES ('SoftwareB', 2024, 2, 190);
INSERT INTO LicenseCostsCost VALUES ('SoftwareB', 2024, 3, 195);
INSERT INTO LicenseCostsCost VALUES ('SoftwareB', 2024, 4, 185);
INSERT INTO LicenseCostsCost VALUES ('SoftwareB', 2024, 5, 210);


SELECT *
FROM LicenseCostsCost
MATCH_RECOGNIZE (
    PARTITION BY software_type -- ��������� ������ �� ����� ��
    ORDER BY year, month       -- ������������� �� �������
    MEASURES 
        FIRST(up.cost) AS start_cost, -- ��������� ���������
        LAST(down.cost) AS lowest_cost, -- ����������� ���������
        LAST(rise.cost) AS end_cost -- �������� ���������
    PATTERN (up down rise)       -- ������ "���� -> ������� -> ����"
    DEFINE 
        up AS up.cost < NEXT(up.cost),  -- ����: ������� ��������� ������ ���������
        down AS down.cost > NEXT(down.cost), -- �������: ������� ��������� ������ ���������
        rise AS rise.cost < NEXT(rise.cost)  -- ����: ������� ��������� ������ ���������
);



-------------------------------------------------------------------------------
CREATE TABLE NewLic (
    ClassID NUMBER , -- ��� ��
    Month NUMBER,               -- ���
    Year NUMBER,              -- �����
    LicenseCount NUMBER                -- ��������� ��������
);

INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES
(1, 1, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 2, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 3, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 4, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 5, 2023, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 6, 2023, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 7, 2023, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 8, 2023, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 9, 2023, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 10, 2023, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 11, 2023, 19);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 12, 2023, 19);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 1, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 2, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 3, 2023, 11);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 4, 2023, 12);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 5, 2023, 12);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 6, 2023, 14);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 7, 2023, 14);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 8, 2023, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 9, 2023, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 10, 2023, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 11, 2023, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 12, 2023, 18);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 1, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 2, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 3, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 4, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 5, 2024, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 6, 2024, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 7, 2024, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 8, 2024, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 9, 2024, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 10, 2024, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 11, 2024, 19);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 12, 2024, 19);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 1, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 2, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 3, 2024, 11);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 4, 2024, 12);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 5, 2024, 12);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 6, 2024, 14);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 7, 2024, 14);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 8, 2024, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 9, 2024, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 10, 2024, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 11, 2024, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 12, 2024, 18);

SELECT ClassID, Month, Year, LicenseCount
FROM NewLic
MODEL
    PARTITION BY (ClassID)
    DIMENSION BY (Month, Year)
    MEASURES (LicenseCount)
    RULES (
        LicenseCount[ANY, 2024] = LicenseCount[CV(Month), 2023] * 1.1 --(1.1 ����������)
    );

UPDATE NewLic
SET LicenseCount = LicenseCount * 0.9 --(0.9 ����������)
WHERE Year = 2024;



-------2
CREATE TABLE PO (
    po_id NUMBER,
    date_po DATE,
    type_po VARCHAR2(50), -- ������� ����� ��� VARCHAR2
    cost_po NUMBER
);


INSERT INTO PO(po_id,  date_po, type_po,cost_po) VALUES (1, TO_DATE('2024-01-01', 'YYYY-MM-DD'), 'BLUE',10);
INSERT INTO PO (po_id,  date_po,type_po, cost_po) VALUES (1, TO_DATE('2024-01-02', 'YYYY-MM-DD'), 'BLUE',5);
INSERT INTO PO (po_id,  date_po,type_po, cost_po) VALUES (1, TO_DATE('2024-01-03', 'YYYY-MM-DD'),'BLUE', 12);
INSERT INTO PO (po_id,  date_po,type_po, cost_po) VALUES (1, TO_DATE('2024-01-04', 'YYYY-MM-DD'), 'BLUE',9);
INSERT INTO PO (po_id,  date_po,type_po, cost_po) VALUES (2, TO_DATE('2024-01-01', 'YYYY-MM-DD'), 'RED',15);
INSERT INTO PO (po_id,  date_po,type_po, cost_po) VALUES (2, TO_DATE('2024-01-02', 'YYYY-MM-DD'), 'RED',32);
INSERT INTO PO (po_id,  date_po,type_po, cost_po) VALUES (2, TO_DATE('2024-01-03', 'YYYY-MM-DD'), 'RED',45);
INSERT INTO PO (po_id, date_po,type_po, cost_po) VALUES (2, TO_DATE('2024-01-04', 'YYYY-MM-DD'), 'RED',13);


SELECT *
FROM PO
MATCH_RECOGNIZE (
    PARTITION BY po_id
    ORDER BY date_po
    MEASURES 
        MATCH_NUMBER() AS match_num,
        classifier() AS pattern
    PATTERN (A B C)
    DEFINE
        A AS cost_po < PREV(cost_po),
        B AS cost_po > PREV(cost_po),
        C AS cost_po < PREV(cost_po))MR;









-------------------------------------------------------------------------------------
--������� 1
CREATE TABLE NewLic (
    ClassID NUMBER ,    -- ��� ��
    Month NUMBER,       -- ���
    Year NUMBER,        -- �����
    LicenseCount NUMBER -- ��������� ��������
);

select * from NewLic;

INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 1, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 2, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 3, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 4, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 5, 2023, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 6, 2023, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 7, 2023, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 8, 2023, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 9, 2023, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 10, 2023, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 11, 2023, 19);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 12, 2023, 19);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 1, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 2, 2023, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 3, 2023, 11);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 4, 2023, 12);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 5, 2023, 12);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 6, 2023, 14);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 7, 2023, 14);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 8, 2023, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 9, 2023, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 10, 2023, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 11, 2023, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 12, 2023, 18);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 1, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 2, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 3, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 4, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 5, 2024, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 6, 2024, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 7, 2024, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 8, 2024, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 9, 2024, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 10, 2024, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 11, 2024, 19);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(1, 12, 2024, 19);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 1, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 2, 2024, 10);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 3, 2024, 11);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 4, 2024, 12);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 5, 2024, 12);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 6, 2024, 14);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 7, 2024, 14);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 8, 2024, 15);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 9, 2024, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 10, 2024, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 11, 2024, 17);
INSERT INTO NewLic (ClassID, Month, Year, LicenseCount)
VALUES(2, 12, 2024, 18);

SELECT ClassID, Month, Year, LicenseCount
FROM NewLic
MODEL --������������� ��� ���������� ������� ��������� ����� � ������������� ��������
    PARTITION BY (ClassID) --��������� ������ �� ������ �� ClassID
    DIMENSION BY (Month, Year) --���������, ��� ������ ����� ����������� �� ���� ����������
    MEASURES (LicenseCount) --�������� ����� ����������� � ������������ � ���������
    RULES ( --������� ����� ����������� �� ���� ������� 2024 ����
    --CV(Month) ���������� ������� �����, ������� �������������� � �����. ����� �������, ��� ������� ����� ���������� �������� �� ��� �� ����� � 2023 ���� � ����������� ��� �� 10% (������� �� 1.1)
        LicenseCount[ANY, 2024] = LicenseCount[CV(Month), 2023] * 1.1 --(1.1 ����������)
    );

UPDATE NewLic
SET LicenseCount = LicenseCount * 0.9 --(0.9 ����������)
WHERE Year = 2024

select * from NewLic;


//2.	������� ��� ������ ����������� MATCH_RECOGNIZE() ������, ������� ������������� �������: 
//����, �������, ���� ��������� �������� ��� ������� ���� ��
CREATE TABLE LicenseCostsCost (
    software_type VARCHAR2(50), -- ��� ��
    year NUMBER,               -- ���
    month NUMBER,              -- �����
    cost NUMBER                -- ��������� ��������
);
select * from LicenseCostsCost

-- ������ ������
INSERT INTO LicenseCostsCost VALUES ('SoftwareA', 2024, 1, 100);
INSERT INTO LicenseCostsCost VALUES ('SoftwareA', 2024, 2, 110);
INSERT INTO LicenseCostsCost VALUES ('SoftwareA', 2024, 3, 105);
INSERT INTO LicenseCostsCost VALUES ('SoftwareA', 2024, 4, 115);
INSERT INTO LicenseCostsCost VALUES ('SoftwareA', 2024, 5, 120);

INSERT INTO LicenseCostsCost VALUES ('SoftwareB', 2024, 1, 200);
INSERT INTO LicenseCostsCost VALUES ('SoftwareB', 2024, 2, 190);
INSERT INTO LicenseCostsCost VALUES ('SoftwareB', 2024, 3, 195);
INSERT INTO LicenseCostsCost VALUES ('SoftwareB', 2024, 4, 185);
INSERT INTO LicenseCostsCost VALUES ('SoftwareB', 2024, 5, 210);


SELECT *
FROM LicenseCostsCost
MATCH_RECOGNIZE ( --������������ ��� ������������� �������� � ������������������ ������
    PARTITION BY software_type -- ��������� ������ �� ����� ��
    ORDER BY year, month       -- ������������� �� �������
    MEASURES --����� �������� ����� ���������� � ����������
        FIRST(up.cost) AS start_cost, -- ��������� ���������
        LAST(down.cost) AS lowest_cost, -- ����������� ���������
        LAST(rise.cost) AS end_cost -- ���������� ��������� (��������) ��������� �� ������� rise
    PATTERN (up down rise)       -- ������ "���� -> ������� -> ����"
    DEFINE --������� ��� ������� �������� �������
        up AS up.cost < NEXT(up.cost),  -- ����: ������� ��������� ������ ���������
        down AS down.cost > NEXT(down.cost), -- �������: ������� ��������� ������ ���������
        rise AS rise.cost < NEXT(rise.cost)  -- ����: ������� ��������� ������ ���������
);



