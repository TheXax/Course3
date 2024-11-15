insert into SoftwareType (typeName) values
('����������� ���������'),
('������������ ������'),
('������������ �������'),
('������� ����������'),
('���������� ��'),
('����');
select * from Software;


insert into Vendors (vendorName) values
('Microsoft'),
('Adobe'),
('Kaspersky'),
('JetBrains'),
('Oracle'),
('NVIDIA'),
('Epic Games');


insert into Roles (roleName) values
('�������������'),
('��������'),
('������������'),
('IT-����������');


insert into Software (softwareName, typeID, vendorID) values
('Windows 10', 3, 1),
('Microsoft Office 2019', 4, 1),
('Adobe Photoshop', 1, 2),
('Kaspersky Anti-Virus', 2, 3),
('IntelliJ IDEA', 5, 4),
('Oracle Database', 3, 5),
('NVIDIA GeForce Experience', 6, 6),
('Fortnite', 6, 7);


insert into Users (userName, roleId) values
('���� ������', 1),
('���� ������', 2),
('������ �������', 3),
('����� �������', 4),
('���� ������', 1),
('����� �������', 2),
('��������� �����������', 3),
('������� ��������', 4);


insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) values
(1, 1, '2023-01-15', '2024-01-15', 199.99),
(2, 1, '2023-02-20', '2024-02-20', 149.99),
(3, 2, '2023-03-10', '2024-03-10', 299.99),
(4, 3, '2023-04-05', '2024-04-05', 39.99),
(5, 4, '2023-05-25', '2024-05-25', 199.99),
(6, 5, '2023-06-15', '2024-06-15', 999.99),
(7, 6, '2023-07-01', '2024-07-01', 0.00), -- ���������� ��������
(8, 7, '2023-08-20', '2024-08-20', 29.99);
select * from Licenses;
select * from Software;


--������� 2
--���������� ������ ��������� ������������� ���� �� ���������, �� �������, �� �������, �� ���.
select 
    FORMAT(purchaseDate, 'yyyy-MM') as month,
    SUM(license_cost) as total_cost_monthly,
    SUM(case when MONTH(purchaseDate) IN (1, 2, 3) then license_cost else 0 end) as total_cost_first_quarter,
    SUM(case when MONTH(purchaseDate) IN (4, 5, 6) then license_cost else 0 end) as total_cost_second_quarter,
    SUM(case when MONTH(purchaseDate) IN (7, 8, 9) then license_cost else 0 end) as total_cost_third_quarter,
    SUM(case when MONTH(purchaseDate) IN (10, 11, 12) then license_cost else 0 end) as total_cost_fourth_quarter,
    SUM(case when MONTH(purchaseDate) BETWEEN 1 AND 6 then license_cost else 0 end) as total_cost_first_half,
    SUM(case when MONTH(purchaseDate) BETWEEN 7 AND 12 then license_cost else 0 end) as total_cost_second_half,
    SUM(license_cost) as total_cost_yearly
from Licenses
join Software on Licenses.softwareId = Software.id_software
where  Software.typeID = 2
group by FORMAT(purchaseDate, 'yyyy-MM')
order by month;


--������� 3
--���������� ������ ��������� ������������� ���� �� �� ������: ���������� � ��������� ��������; ��������� �� � ����� ���������� �������� (� %); ��������� �� � ����� ���������� �������� (� %).
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
    ROUND((CAST(s.specific_count as float) / t.total_count) * 100, 3) as percent_count,
    ROUND((CAST(s.specific_cost as float) / t.total_cost) * 100, 3) as percent_cost
from 
    SpecificSoftwareLicenses s,
    TotalLicenses t;

--������� 4
--����������������� ���������� ������� ������������ ROW_NUMBER() ��� ��������� ����������� ������� �� �������� (�� 20 ����� �� ������ ��������).
insert into Users (userName, roleId) values
('���� �������', 1),
('����� �������', 2),
('������ ��������', 3),
('���� ������', 1),
('���� ������', 2),
('������ ��������', 3),
('������� ����������', 1),
('��������� ������������', 2),
('����� �������', 3),
('����� �������', 1),
('������� ��������', 2),
('������� ���������', 3),
('�������� ����������', 1),
('���� �����', 2),
('������ ��������', 3),
('����� �������', 1),
('������ ��������', 2);

select * from Users;

with RankedUsers as (
    select 
        id_user,
        userName,
        roleId,
        ROW_NUMBER() over (order by id_user) as RowNum
    from  Users
)

select 
    id_user,
    userName,
    roleId
from RankedUsers
where RowNum BETWEEN 1 AND 20;  -- ��� ������ ��������


with RankedUsers as (
    select 
        id_user,
        userName,
        roleId,
        ROW_NUMBER() over (order by id_user) as RowNum
    from Users
)

select 
    id_user,
    userName,
    roleId
from RankedUsers
where RowNum BETWEEN 21 AND 40;  -- ��� ������ ��������


--������� 5
--����������������� ���������� ������� ������������ ROW_NUMBER() ��� �������� ����������.
--��� ������ � �������
insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) values
(1, 1, '2024-01-10', '2025-01-10', 150.00),
(2, 2, '2024-02-15', '2025-02-15', 200.00),
(3, 1, '2024-03-20', '2025-03-20', 120.00),
(4, 3, '2024-04-25', '2025-04-25', 80.00),
(5, 4, '2024-05-30', '2025-05-30', 250.00),
(1, 1, '2024-06-10', '2025-06-10', 150.00), -- ��������
(2, 2, '2024-07-15', '2025-07-15', 200.00), -- ��������
(3, 5, '2024-08-20', '2025-08-20', 120.00);

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

select * from Licenses;

--������� 6
--������� ��� ������� ������� ����� ����������� �� �������������� ������� �� ��������� 6 ������� ���������.
select 
    v.vendorName,
    YEAR(l.purchaseDate) as YearDate,
    MONTH(l.purchaseDate) as MonthDate,
    SUM(l.license_cost) as TotalSpent
from Licenses l
join  Software s on l.softwareId = s.id_software
join Vendors v on s.vendorID = v.id_vendor
where l.purchaseDate >= DATEADD(MONTH, -6, GETDATE())  -- ��������� ��������� 6 �������
group by 
    v.vendorName,
    YEAR(l.purchaseDate),
    MONTH(l.purchaseDate)
order by
    v.vendorName,
    YearDate,
    MonthDate;


--������� 7
--����� ��� ������������ ����������� ������������� ���������� ����� ��� ��� ��������� ������������� ����? ������� ��� ���� �����.
create table Devices (
    id_device int primary key identity(1,1),
    deviceType varchar(50) NOT NULL
);

insert into Devices (deviceType) values
('Desktop'),
('Laptop'),
('Tablet'),
('Smartphone');

alter table Software add deviceId int;
UPDATE Software set deviceId = 1 where id_software IN (1, 2); -- ���������� ���� Desktop
UPDATE Software set deviceId = 2 where id_software IN (3, 4); -- ���������� ���� Laptop
UPDATE Software set deviceId = 3 where id_software IN (5, 8); -- ���������� ���� Tablet
UPDATE Software set deviceId = 4 where id_software IN (6, 7); -- ���������� ���� Smartphone

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
    join Devices d ON s.deviceId = d.id_device
    group by st.typeName, d.deviceType
)

select 
    deviceType,
    typeName,
    UsageCount
from SoftwareUsage
where Rank = 1;
