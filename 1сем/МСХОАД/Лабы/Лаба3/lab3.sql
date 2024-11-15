create table Employee (
    employee_id int primary key,
    first_name nvarchar(50),
    last_name nvarchar(50),
    boss_id int,
    stage int,
    position nvarchar(50),
    foreign key (boss_id) 
    references Employee(employee_id) 
);
drop table Employee
select * from Employee

insert into Employee values(1, N'����', N'������', NULL, 1, N'��������');
insert into Employee values(2, N'����', N'������', 1, 2, N'��������');
insert into Employee values(3, N'������', N'�������', 2, 3, N'��������');
insert into Employee values(4, N'������', N'�������', 3, 4, N'�����������');
insert into Employee values(5, N'�������', N'��������', 4, 5, N'�����������');
insert into Employee values(6, N'�������', N'��������', 4, 6, N'��������');
insert into Employee values(7, N'��������', N'����������', 4, 7, N'���������');
insert into Employee values(8, N'���������', N'�����������', 7, 8, N'����������');
insert into Employee values(9, N'������', N'��������', 1, 9, N'���������');
insert into Employee values(10, N'�������', N'��������', 2, 10, N'�����');

-------
alter table Employee add HIERARCHY_COLUMN hierarchyid;

select * from Employee;

-- �������� �������� --
begin
	update Employee
	set HIERARCHY_COLUMN = hierarchyid::GetRoot()
	where employee_id = 1; 

	update Employee
	set HIERARCHY_COLUMN = '/1/'
	WHERE employee_id = 2; 

	update Employee
	set HIERARCHY_COLUMN = '/1/2/'
	WHERE employee_id = 2; 

	UPDATE Employee
	set HIERARCHY_COLUMN = '/1/2/3/'
	where employee_id = 3; 

	update Employee
	set HIERARCHY_COLUMN = '/1/2/3/4/'
	where employee_id = 4; 

	update Employee
	set HIERARCHY_COLUMN = '/1/2/3/4/5/'
	where employee_id = 5; 

	update Employee
	set HIERARCHY_COLUMN = '/1/2/3/4/6/'
	where employee_id = 6; 

	update Employee
	set HIERARCHY_COLUMN = '/1/2/3/4/7/'
	where employee_id = 7; 

	update Employee
	set HIERARCHY_COLUMN = '/1/2/3/4/7/8/'
	where employee_id = 8; 

	update Employee
	set HIERARCHY_COLUMN = '/1/9/'
	where employee_id = 9; 

	update Employee
	set HIERARCHY_COLUMN = '/1/10/'
	where employee_id = 10; 
end;


select
    *,
    HIERARCHY_COLUMN.ToString() as Hierarchy,
    HIERARCHY_COLUMN.GetLevel() as Level
from Employee;


-- ������� 2 --
--������� ���������, ������� ��������� ��� ����������� ���� � ��������� ������ ��������--
create procedure GetSubordinates (@id int) as
	begin
		declare @h hierarchyid
		set @h = (select HIERARCHY_COLUMN from Employee where employee_id = @id);

		select 
			employee_id,
			boss_id,
			first_name,
			last_name,
			HIERARCHY_COLUMN.GetLevel() as Level,
			HIERARCHY_COLUMN.ToString() as Hierarchy
		from Employee
		--�������� �� ������� ���� (��������) ����������� ���������� ���� @h, ���� ��, �� 1. ��������� ������ ���������.
		where HIERARCHY_COLUMN.IsDescendantOf(@h) = 1 AND employee_id != @id;
	end

exec GetSubordinates @id = 7;



--������� 3--
--������� ���������, ������� ������� ����������� ����.--
drop procedure AddSubordinate
create procedure AddSubordinate
    @parent_id int,
    @first_name nvarchar(50),
    @last_name nvarchar(50),
    @stage int,
    @position nvarchar(50)
as
begin
    -- ���������, ���������� �� ��������
    declare @parent_hierarchy hierarchyid;

    select @parent_hierarchy = HIERARCHY_COLUMN 
    from Employee 
    where employee_id = @parent_id;

    if @parent_hierarchy IS NULL
    begin
        print '������������ ���� �� ������.';
        return;
    end

    -- ���������� ����� ������� ��� ������������ ����
    declare @new_hierarchy hierarchyid;
	SET @new_hierarchy = @parent_hierarchy.GetDescendant(NULL, NULL); -- ���������� GetDescendant ��� �������� ������ ����
    insert into Employee (employee_id, first_name, last_name, boss_id, stage, position, HIERARCHY_COLUMN)
    values ( 
        (select ISNULL(MAX(employee_id), 0) + 1 from Employee), -- ���������� ����� ID
        @first_name,
        @last_name,
        @parent_id,
        @stage,
        @position,
        @new_hierarchy
    );
end;


exec AddSubordinate 
    @parent_id = 2, 
    @first_name = N'����', 
    @last_name = N'������', 
    @stage = 11, 
    @position = N'�����';

	delete from Employee where employee_id = 11;
	select *, HIERARCHY_COLUMN.ToString() as Hierarchy, HIERARCHY_COLUMN.GetLevel() as Level 
	from Employee;



--������� 4--
--������� ���������, ������� ���������� ��� ����������� ����� (������ �������� � �������� �������� ������������� ����, ������ �������� � �������� ����, � ������� ���������� �����������).--
create procedure MoveSubtree
    @source_id int,
    @target_id int
as
begin
    -- ���������, ���������� �� ����, ������� �� ����������
    declare @source_hierarchy hierarchyid;
    select @source_hierarchy = HIERARCHY_COLUMN from Employee where employee_id = @source_id;

    if @source_hierarchy IS NULL
    begin
        print '�������� ���� �� ������.';
        return;
    end

    -- ���������, ���������� �� ������� ����
    declare @target_hierarchy hierarchyid;
    select @target_hierarchy = HIERARCHY_COLUMN from Employee where employee_id = @target_id;

    if @target_hierarchy IS NULL
    begin
        print '������� ���� �� ������.';
        return;
    end

    -- ���������, �� �������� �� ������� ���� �������� ��������� ����
    if @source_hierarchy.IsDescendantOf(@target_hierarchy) = 1
    begin
        print '������ ����������� ����, ��� ��� �� �������� �������� �������� ����.';
        return;
    end

    -- ����������� ���������� �����
    declare @new_hierarchy hierarchyid;
    set @new_hierarchy = @target_hierarchy.GetDescendant(NULL, NULL);

    -- ��������� HIERARCHY_COLUMN ��� ���� ���������� �����
    update Employee
    set HIERARCHY_COLUMN = @new_hierarchy.GetAncestor(1).GetDescendant(NULL, NULL).GetAncestor(0).GetDescendant(HIERARCHY_COLUMN, NULL)
    where HIERARCHY_COLUMN.IsDescendantOf(@source_hierarchy) = 1;

    -- ��������� HIERARCHY_COLUMN ��� ������ ������������� ����
    update Employee
    set HIERARCHY_COLUMN = @new_hierarchy
    where employee_id = @source_id;

    print '���������� ����� ������� ����������.';
end;

select *, HIERARCHY_COLUMN.ToString() as Hierarchy, HIERARCHY_COLUMN.GetLevel() as Level 
	from Employee;


exec MoveSubtree @source_id = 7, @target_id = 2; -- ���������� ���� � ��������������� 4 � ���� � ��������������� 2
