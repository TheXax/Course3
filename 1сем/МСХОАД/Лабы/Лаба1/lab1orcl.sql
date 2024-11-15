create SEQUENCE SoftwareTypesSeq
   start with 1
   increment BY 1
   nocache
   nocycle;
   
   
create SEQUENCE RoleSeq
   start with 1
   increment BY 1
   nocache
   nocycle;
   
create SEQUENCE VendorsSeq
   start with 1
   increment BY 1
   nocache
   nocycle;
   
   
create SEQUENCE SoftwareSeq
   start with 1
   increment BY 1
   nocache
   nocycle;
   
   
create SEQUENCE UsersSeq
   start with 1
   increment BY 1
   nocache
   nocycle;
   
   
create SEQUENCE LicensesSeq
   start with 1
   increment BY 1
   nocache
   nocycle;
   
DROP SEQUENCE SoftwareTypesSeq;
DROP SEQUENCE RoleSeq;
DROP SEQUENCE VendorsSeq;
DROP SEQUENCE SoftwareSeq;
DROP SEQUENCE UsersSeq;
DROP SEQUENCE LicensesSeq;

--Таблица "Типы ПО"--
create table SoftwareType (
	id_type number default SoftwareTypesSeq.NEXTVAL primary key,
	typeName nvarchar2(255) not null --например, графические редакторы, антивирусные пакеты
);
drop table SoftwareType;


insert into SoftwareType (typeName) values ('графические редакторы');


--Таблица "Роли"--
create table Roles (
	id_role number default RoleSeq.NEXTVAL primary key,
	roleName nvarchar2(255) not null 
);
drop table Roles;


insert into Roles (roleName) values ('пользователь');
insert into Roles (roleName) values ('админ');

select * from Roles;

--Таблица "Вендоры(поставщики)"--
create table Vendors (
	id_vendor number default VendorsSeq.NEXTVAL primary key,
	vendorName nvarchar2(255) not null --например, "Microsoft", "Adobe"
);
drop table Vendors;


insert into Vendors (vendorName) values ('Microsoft');

select * from Software

--Таблица "ПО"--
create table Software (
	id_software number default SoftwareSeq.NEXTVAL primary key,
	softwareName nvarchar2(255) not null, --например, "Windows 10"
	typeID number references SoftwareType(id_type),
	vendorID number references Vendors(id_vendor)
);
drop table Software;


insert into Software (softwareName, typeID, vendorID) values ('Блокнот', 3, 1);


--Таблица "Пользователи"--
create table Users (
	id_user number default UsersSeq.NEXTVAL primary key,
	userName nvarchar2(255) not null,
    roleId number references Roles(id_role)
);
drop table Users;


--Таблица "Лицензии"--
create table Licenses (
	id_license number default LicensesSeq.NEXTVAL primary key,
	softwareId number references Software(id_software),
	userId number references Users(id_user),
	purchaseDate date not null, --дата покупки лицензии
	expirationDate date not null, --истечение срока лицензии
    license_cost number(9, 2) not null
);
drop table Licenses;

select * from Licenses

insert into Licenses (softwareId, userId, purchaseDate, expirationDate, license_cost) values (3, 1, sysdate, TO_DATE('2025-10-14', 'YYYY-MM-DD'), 50);
delete from Licenses where id_license = 4;



