--������� 1
insert into SoftwareType (typeName) values ('����������� ���������');
insert into SoftwareType (typeName) values ('������������ ������');
insert into SoftwareType (typeName) values ('������������ �������');
insert into SoftwareType (typeName) values('������� ����������');
insert into SoftwareType (typeName) values('���������� ��');
insert into SoftwareType (typeName) values ('����');
select * from SoftwareType;


insert into Vendors (vendorName) values ('Microsoft');
insert into Vendors (vendorName) values ('Adobe');
insert into Vendors (vendorName) values('Kaspersky');
insert into Vendors (vendorName) values('JetBrains');
insert into Vendors (vendorName) values ('Oracle');
insert into Vendors (vendorName) values ('NVIDIA');
insert into Vendors (vendorName) values ('Epic Games');
select * from Vendors;

insert into Roles (roleName) values ('�������������');
insert into Roles (roleName) values ('��������');
insert into Roles (roleName) values ('������������');
insert into Roles (roleName) values ('IT-����������');


insert into Software (softwareName, typeID, vendorID) values ('Windows 10', 3, 1);
insert into Software (softwareName, typeID, vendorID) values ('Microsoft Office 2019', 4, 1);
insert into Software (softwareName, typeID, vendorID) values ('Adobe Photoshop', 1, 2);
insert into Software (softwareName, typeID, vendorID) values ('Kaspersky Anti-Virus', 2, 3);
insert into Software (softwareName, typeID, vendorID) values ('IntelliJ IDEA', 5, 4);
insert into Software (softwareName, typeID, vendorID) values ('Oracle Database', 3, 5);
insert into Software (softwareName, typeID, vendorID) values ('NVIDIA GeForce Experience', 6, 6);
insert into Software (softwareName, typeID, vendorID) values ('Fortnite', 6, 7);
select * from Software;

insert into Users (userName, roleId) values ('���� ������', 1);
insert into Users (userName, roleId) values ('���� ������', 2);
insert into Users (userName, roleId) values ('������ �������', 3);
insert into Users (userName, roleId) values ('����� �������', 4);
insert into Users (userName, roleId) values ('���� ������', 1);
insert into Users (userName, roleId) values ('����� �������', 2);
insert into Users (userName, roleId) values ('��������� �����������', 3);
insert into Users (userName, roleId) values ('������� ��������', 4);


INSERT INTO Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (1, 1, TO_DATE('2023-01-15', 'YYYY-MM-DD'), TO_DATE('2024-01-15', 'YYYY-MM-DD'), 199.99);
INSERT INTO Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (2, 1, TO_DATE('2023-02-20', 'YYYY-MM-DD'), TO_DATE('2024-02-20', 'YYYY-MM-DD'), 149.99);
INSERT INTO Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (3, 2, TO_DATE('2023-03-10', 'YYYY-MM-DD'), TO_DATE('2024-03-10', 'YYYY-MM-DD'), 299.99);
INSERT INTO Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (4, 3, TO_DATE('2023-04-05', 'YYYY-MM-DD'), TO_DATE('2024-04-05', 'YYYY-MM-DD'), 39.99);
INSERT INTO Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (5, 4, TO_DATE('2023-05-25', 'YYYY-MM-DD'), TO_DATE('2024-05-25', 'YYYY-MM-DD'), 199.99);
INSERT INTO Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (6, 5, TO_DATE('2023-06-15', 'YYYY-MM-DD'), TO_DATE('2024-06-15', 'YYYY-MM-DD'), 999.99);
INSERT INTO Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (7, 6, TO_DATE('2023-07-01', 'YYYY-MM-DD'), TO_DATE('2024-07-01', 'YYYY-MM-DD'), 0.00); -- ���������� ��������
INSERT INTO Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (8, 7, TO_DATE('2023-08-20', 'YYYY-MM-DD'), TO_DATE('2024-08-20', 'YYYY-MM-DD'), 29.99);
select * from Licenses;


--������� 2
select 
    TO_CHAR(purchaseDate, 'YYYY-MM') as month,
    SUM(license_cost) as total_cost_monthly,
    SUM(case when EXTRACT(MONTH FROM purchaseDate) IN (1, 2, 3) then license_cost else 0 end) as total_cost_first_quarter,
    SUM(case when EXTRACT(MONTH FROM purchaseDate) IN (4, 5, 6) then license_cost else 0 end) as total_cost_second_quarter,
    SUM(case when EXTRACT(MONTH FROM purchaseDate) IN (7, 8, 9) then license_cost else 0 end) as total_cost_third_quarter,
    SUM(case when EXTRACT(MONTH FROM purchaseDate) IN (10, 11, 12) then license_cost else 0 end) as total_cost_fourth_quarter,
    SUM(case when EXTRACT(MONTH FROM purchaseDate) BETWEEN 1 AND 6 then license_cost else 0 end) as total_cost_first_half,
    SUM(case when EXTRACT(MONTH FROM purchaseDate) BETWEEN 7 AND 12 then license_cost else 0 end) as total_cost_second_half,
    SUM(license_cost) as total_cost_yearly
from Licenses
join Software on Licenses.softwareId = Software.id_software
where  Software.typeID = 3
group by TO_CHAR(purchaseDate, 'YYYY-MM')
order by month;


--������� 3
with TotalLicenses as (
    select 
        COUNT(*) as total_count,
        SUM(license_cost) as total_cost
    from Licenses
),
SpecificSoftwareLicenses as (
    select 
        COUNT(*) as specific_count,
        SUM(license_cost) as specific_cost
    from Licenses
    join Software on Licenses.softwareId = Software.id_software
    where Software.typeID = 6 -- ID ���� ��
)

select 
    s.specific_count,
    s.specific_cost,
    t.total_count,
    t.total_cost,
    ROUND((s.specific_count / t.total_count) * 100, 3) as percent_count,
    ROUND((s.specific_cost / t.total_cost) * 100, 3) as percent_cost
from 
    SpecificSoftwareLicenses s,
    TotalLicenses t;


--������� 4
insert into Users (userName, roleId) values ('���� �������', 1);
insert into Users (userName, roleId) values ('����� �������', 2);
insert into Users (userName, roleId) values ('������ ��������', 3);
insert into Users (userName, roleId) values ('���� ������', 1);
insert into Users (userName, roleId) values ('���� ������', 2);
insert into Users (userName, roleId) values ('������ ��������', 3);
insert into Users (userName, roleId) values ('������� ����������', 1);
insert into Users (userName, roleId) values ('��������� ������������', 2);
insert into Users (userName, roleId) values ('����� �������', 3);
insert into Users (userName, roleId) values ('����� �������', 1);
insert into Users (userName, roleId) values ('������� ��������', 2);
insert into Users (userName, roleId) values ('������� ���������', 3);
insert into Users (userName, roleId) values ('�������� ����������', 1);
insert into Users (userName, roleId) values ('���� �����', 2);
insert into Users (userName, roleId) values ('������ ��������', 3);
insert into Users (userName, roleId) values ('����� �������', 1);
insert into Users (userName, roleId) values ('������ ��������', 2);

select * from Users;

select 
    id_user,
    userName,
    roleId
from Users
order by id_user
OFFSET 0 ROWS FETCH NEXT 20 ROWS ONLY;  -- ��� ������ ��������


select 
    id_user,
    userName,
    roleId
from Users
order by id_user
OFFSET 20 ROWS FETCH NEXT 20 ROWS ONLY;  -- ��� ������ ��������



--������� 5
--��� ������ � �������
insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (1, 1, TO_DATE('2024-01-10', 'YYYY-MM-DD'), TO_DATE('2025-01-10', 'YYYY-MM-DD'), 150.00);
insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (2, 2, TO_DATE('2024-02-15', 'YYYY-MM-DD'), TO_DATE('2025-02-15', 'YYYY-MM-DD'), 200.00);
insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (3, 1, TO_DATE('2024-03-20', 'YYYY-MM-DD'), TO_DATE('2025-03-20', 'YYYY-MM-DD'), 120.00);
insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (4, 3, TO_DATE('2024-04-25', 'YYYY-MM-DD'), TO_DATE('2025-04-25', 'YYYY-MM-DD'), 80.00);
insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (5, 4, TO_DATE('2024-05-30', 'YYYY-MM-DD'), TO_DATE('2025-05-30', 'YYYY-MM-DD'), 250.00);
insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (1, 1, TO_DATE('2024-06-10', 'YYYY-MM-DD'), TO_DATE('2025-06-10', 'YYYY-MM-DD'), 150.00); -- ��������
insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (2, 2, TO_DATE('2024-07-15', 'YYYY-MM-DD'), TO_DATE('2025-07-15', 'YYYY-MM-DD'), 200.00); -- ��������
insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) VALUES (3, 5, TO_DATE('2024-08-20', 'YYYY-MM-DD'), TO_DATE('2025-08-20', 'YYYY-MM-DD'), 120.00);

with RankedLicenses as (
    select 
        id_license,
        softwareId,
        userId,
        purchaseDate,
        expirationDate,
        license_cost,
        ROW_NUMBER() over (partition by softwareId, userId order by id_license) as RowNum
    from Licenses
)

select 
    id_license,
    softwareId,
    userId,
    purchaseDate,
    expirationDate,
    license_cost
from RankedLicenses
where RowNum = 1;  -- ��������� ������ ������ ������ ��� ������� ����������� ��������� softwareId � userId


--������� 6
select 
    v.vendorName,
    EXTRACT(YEAR from l.purchaseDate) AS YearDate,
    EXTRACT(MONTH from l.purchaseDate) AS MonthDate,
    SUM(l.license_cost) AS TotalSpent
from Licenses l
join  Software s on l.softwareId = s.id_software
join Vendors v on s.vendorID = v.id_vendor
where l.purchaseDate >= ADD_MONTHS(SYSDATE, -6)  -- ��������� ��������� 6 �������
group by 
    v.vendorName,
    EXTRACT(YEAR from l.purchaseDate),
    EXTRACT(MONTH from l.purchaseDate)
order by
    v.vendorName,
    YearDate,
    MonthDate;


--������� 7
create SEQUENCE DevicesSeq
   start with 1
   increment BY 1
   nocache
   nocycle;
   
create table Devices (
	id_devices number default DevicesSeq.NEXTVAL primary key,
    deviceType varchar(50) NOT NULL
);

insert into Devices (deviceType) values ('Desktop');
insert into Devices (deviceType) values ('Laptop');
insert into Devices (deviceType) values ('Tablet');
insert into Devices (deviceType) values ('Smartphone');

-- ��������� ������� deviceId � ������� Software
alter table Software add deviceId number;

-- ��������� ������� Software
update Software set deviceId = 1 where id_software in (1, 2); -- ���������� ���� Desktop
update Software set deviceId = 2 where id_software in (3, 4); -- ���������� ���� Laptop
update Software set deviceId = 3 where id_software in (5, 8); -- ���������� ���� Tablet
update Software set deviceId = 4 where id_software in (6, 7); -- ���������� ���� Smartphone

alter table Software add deviceId int;
UPDATE Software set deviceId = 1 where id_software IN (1, 2); -- ���������� ���� Desktop
UPDATE Software set deviceId = 2 where id_software IN (3, 4); -- ���������� ���� Laptop
UPDATE Software set deviceId = 3 where id_software IN (5, 8);    -- ���������� ���� Tablet
UPDATE Software set deviceId = 4 where id_software IN (6, 7);    -- ���������� ���� Smartphone

select * from Software

with SoftwareUsage as (
    select 
        st.typeName,
		d.deviceType,
        COUNT(l.id_license) as UsageCount,
        RANK() OVER (PARTITION BY d.deviceType ORDER BY COUNT(l.id_license) DESC) as Rank
    from Licenses l
    join Software s ON l.softwareId = s.id_software
    join SoftwareType st ON s.typeID = st.id_type
    join Devices d ON s.deviceId = d.id_devices
    group by st.typeName, d.deviceType
)

select 
    deviceType,
    typeName,
    UsageCount
from SoftwareUsage
where Rank = 1;





