create database LICENSES;

--Таблица "Типы ПО"--
create table SoftwareType (
	id_type int primary key IDENTITY(1,1),
	typeName nvarchar(255) not null --например, графические редакторы, антивирусные пакеты
);

select * from Licenses;

--Таблица "Роли"--
create table Roles (
	id_role int primary key IDENTITY(1,1),
	roleName nvarchar(255) not null
);


--Таблица "Вендоры(поставщики)"--
create table Vendors (
	id_vendor int primary key IDENTITY(1,1),
	vendorName nvarchar(255) not null --например, "Microsoft", "Adobe"
);

--Таблица "ПО"--
create table Software (
	id_software int primary key IDENTITY(1,1),
	softwareName nvarchar(255) not null, --например, "Windows 10"
	typeID int foreign key references SoftwareType(id_type),
	vendorID int foreign key references Vendors(id_vendor),
);

--Таблица "Пользователи"--
create table Users (
	id_user int primary key IDENTITY(1,1),
	userName nvarchar(255) not null,
	roleId int foreign key references Roles(id_role) not null
);

--Таблица "Лицензии"--
create table Licenses (
	id_license int primary key IDENTITY(1,1),
	softwareId int foreign key references Software(id_software),
	userId int foreign key references Users(id_user),
	purchaseDate date not null, --дата покупки лицензии
	expirationDate date not null, --истечение срока лицензии
	license_cost decimal(9, 2) not null
);
select * from Roles;
drop table Users