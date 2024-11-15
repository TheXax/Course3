-- ������������� ��� ������������ ����� �������� ��������
create view ExpiringLicensesView as
select
    Software.softwareName,
    Users.UserName,
    Licenses.purchaseDate,
    Licenses.expirationDate
from Licenses
JOIN Software on Licenses.softwareId = Software.id_software
JOIN Users on Licenses.userId = Users.id_user
where
    Licenses.expirationDate BETWEEN getdate() AND dateadd(month, 1, getdate());
	
select * from ExpiringLicensesView;

-- ������ ��� ��������� ������� �� ��������� ��������
create index IX_LicenseCost on Licenses(license_cost);

-- ������������������ ��� ��������� ���������� ID ��� ����� ��������
create sequence LicenseIdSeq
start with 1
increment by 1;

-- ��������� ��� ���������� ������ ������������
create procedure AddUser
    @userName nvarchar(255),
	@roleId int
as
begin
    insert into Users (userName, roleId) values (@UserName, @roleId);
end;

exec AddUser @UserName = 'Anna', @roleId = 1;


-- ��������� ��� ���������� ���������� � ��������
create procedure UpdateLicense
    @licenseId int,
    @expirationDate date
as
begin
    update Licenses
    set expirationDate = @expirationDate
    where id_license = @licenseId;
end;

exec UpdateLicense @licenseId = 1, @expirationDate = '2023-12-30';


--������� ��� �������� ����� ��������� �������� ������������:
create function CalculateTotalLicenseCost(@id_user int)
returns decimal(9, 2)
as
begin
    declare @TotalCost decimal(9, 2);
    select @TotalCost = sum(Licenses.license_cost) from Licenses
    where Licenses.userId = @id_user;
    return @TotalCost;
end;

select dbo.CalculateTotalLicenseCost(1)
