--�������� � ����� �������������

--1.������� ��������� ���� ������ �� ������ ��������:
-- ��� ��� ������������� ��������
CREATE OR REPLACE TYPE LicenseTypeObject AS OBJECT (
    id_license NUMBER,
    software_name NVARCHAR2(255),
    place_of_use NVARCHAR2(255),
    purchase_date DATE,
    expiration_date DATE,
    license_cost NUMBER(9, 2),

    -- �������������� �����������
    --������ ������ � ��������� ���������� ���������
    CONSTRUCTOR FUNCTION LicenseTypeObject(
        --self - ������ �� ������� ������
        --IN OUT NOCOPY ���������, ��� ������ ��������� �� ������ ��� ��������� ������������������
        self IN OUT NOCOPY LicenseTypeObject,
        id_license NUMBER, 
        software_name NVARCHAR2, 
        place_of_use NVARCHAR2,
        purchase_date DATE, 
        expiration_date DATE, 
        license_cost NUMBER
    ) RETURN SELF AS RESULT, --������� ���������� �������

    -- ����� ���������
    MAP MEMBER FUNCTION to_map RETURN DATE,

    -- ����� ����������: ������� ��� ������� ���������� ����
    MEMBER FUNCTION days_left RETURN NUMBER,

    -- ����� ����������: ��������� ��� ���������� ��������� ��������
    MEMBER PROCEDURE update_cost(new_cost NUMBER)
);

------------------
-- ���������� ������� (������ ���� ���������� ����)
CREATE OR REPLACE TYPE BODY LicenseTypeObject AS
    CONSTRUCTOR FUNCTION LicenseTypeObject( --����������� ������ ��������� � �����������
        self IN OUT NOCOPY LicenseTypeObject,
        id_license NUMBER, 
        software_name NVARCHAR2, 
        place_of_use NVARCHAR2,
        purchase_date DATE, 
        expiration_date DATE, 
        license_cost NUMBER
    ) RETURN SELF AS RESULT IS
    BEGIN --�������������
        self.id_license := id_license;
        self.software_name := software_name;
        self.place_of_use := place_of_use;
        self.purchase_date := purchase_date;
        self.expiration_date := expiration_date;
        self.license_cost := license_cost;
        RETURN;
    END;
    
    --���������� �� ���� ��������� ��������
    MAP MEMBER FUNCTION to_map RETURN DATE IS
    BEGIN
        RETURN expiration_date; -- ��������� �� ���� ���������
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

--���������� MAP
SELECT * FROM LicenseObjectsNew o ORDER BY VALUE(o).to_map();

--����� ��������, ���� �� ��������� �������� ������ 30 ����
SELECT VALUE(o).id_license AS id_license, VALUE(o).days_left() AS days_left
FROM LicenseObjectsNew o
WHERE VALUE(o).days_left() > 30;


--�� ��������, �� ����������!!!!!
DECLARE
    l LicenseTypeObject;
BEGIN
    -- �������� �������
    l := LicenseTypeObject(1, 'Windows', 'Office', TO_DATE('2024-07-01', 'YYYY-MM-DD'), TO_DATE('2025-07-01', 'YYYY-MM-DD'), 100.00);
    -- ���������� ���������
    l.update_cost(120.00);
    -- ����� ����������� ��������
    --DBMS_OUTPUT.PUT_LINE('Updated cost: ' || l.license_cost);
END;



--2.����������� ������ �� ����������� ������ � ���������.
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

--3.������������������ ���������� ��������� �������������.
--�������� �������������
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

--������ �������������
SELECT * FROM LicenseViewNew;

SELECT id_license, software_name, place_of_use
FROM LicenseView
WHERE license_cost > 100;



--4. �������� �������.
CREATE INDEX idx_license_expiration ON LicenseObjects (expiration_date);

