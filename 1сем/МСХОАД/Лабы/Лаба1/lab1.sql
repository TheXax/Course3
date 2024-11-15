create database LICENSES;

--������� "���� ��"--
create table SoftwareType (
	id_type int primary key IDENTITY(1,1),
	typeName nvarchar(255) not null --��������, ����������� ���������, ������������ ������
);

select * from Licenses;

--������� "����"--
create table Roles (
	id_role int primary key IDENTITY(1,1),
	roleName nvarchar(255) not null
);


--������� "�������(����������)"--
create table Vendors (
	id_vendor int primary key IDENTITY(1,1),
	vendorName nvarchar(255) not null --��������, "Microsoft", "Adobe"
);

--������� "��"--
create table Software (
	id_software int primary key IDENTITY(1,1),
	softwareName nvarchar(255) not null, --��������, "Windows 10"
	typeID int foreign key references SoftwareType(id_type),
	vendorID int foreign key references Vendors(id_vendor),
);

--������� "������������"--
create table Users (
	id_user int primary key IDENTITY(1,1),
	userName nvarchar(255) not null,
	roleId int foreign key references Roles(id_role) not null
);

--������� "��������"--
create table Licenses (
	id_license int primary key IDENTITY(1,1),
	softwareId int foreign key references Software(id_software),
	userId int foreign key references Users(id_user),
	purchaseDate date not null, --���� ������� ��������
	expirationDate date not null, --��������� ����� ��������
	license_cost decimal(9, 2) not null
);
select * from Roles;
drop table Users