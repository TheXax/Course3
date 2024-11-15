-- Представление для отслеживания срока действия лицензий
create view ExpiringLicensesView as
select
    Software.softwareName,
    Users.UserName,
    Licenses.purchaseDate,
    Licenses.expirationDate
from
    Licenses
JOIN Software on Licenses.softwareId = Software.id_software
JOIN Users on Licenses.userId = Users.id_user
where
    Licenses.expirationDate BETWEEN sysdate AND sysdate + 30;
	
select * from ExpiringLicensesView;

-- Индекс для ускорения запроса по стоимости лицензий
create index IX_LicenseCost on Licenses(license_cost);

-- Процедура для добавления нового пользователя
create or replace procedure AddUser (p_userName in varchar2, p_roleId in number)
as
begin
    insert into Users (userName, roleId) values (p_userName, p_roleId);
    commit;
end;

begin
    AddUser('Anna', 1);
end;

select * from Users;


-- Процедура для обновления информации о лицензии
create or replace procedure UpdateLicense (p_licenseId in number, p_expirationDate in date)
as
begin
    update Licenses
    set expirationDate = p_expirationDate
    where id_license = p_licenseId;
    commit;
end;


select * from Licenses
begin
    UpdateLicense(2, to_date('2025-12-30', 'YYYY-MM-DD'));
end;

--Функция для подсчета общей стоимости лицензий пользователя:
create or replace function CalculateTotalLicenseCost(p_userId in number)
return number as k_totalCost number := 0;
begin
    select sum(license_cost)into k_totalCost from Licenses
    where userId = p_userId;
    return NVL(k_totalCost, 0); -- 0, если нет лицензии
end;

select * from Users


select CalculateTotalLicenseCost(1) as Сумма from dual;
