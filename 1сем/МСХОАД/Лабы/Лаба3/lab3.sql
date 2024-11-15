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

insert into Employee values(1, N'Иван', N'Иванов', NULL, 1, N'Директор');
insert into Employee values(2, N'Петр', N'Петров', 1, 2, N'Менеджер');
insert into Employee values(3, N'Сергей', N'Сергеев', 2, 3, N'Аналитик');
insert into Employee values(4, N'Андрей', N'Андреев', 3, 4, N'Разработчик');
insert into Employee values(5, N'Алексей', N'Алексеев', 4, 5, N'Тестировщик');
insert into Employee values(6, N'Дмитрий', N'Дмитриев', 4, 6, N'Дизайнер');
insert into Employee values(7, N'Владимир', N'Владимиров', 4, 7, N'Продажник');
insert into Employee values(8, N'Александр', N'Александров', 7, 8, N'Маркетолог');
insert into Employee values(9, N'Михаил', N'Михайлов', 1, 9, N'Бухгалтер');
insert into Employee values(10, N'Николай', N'Николаев', 2, 10, N'Юрист');

-------
alter table Employee add HIERARCHY_COLUMN hierarchyid;

select * from Employee;

-- Создание иерархии --
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


-- задание 2 --
--Создать процедуру, которая отобразит все подчиненные узлы с указанием уровня иерархии--
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
		--является ли текущий узел (работник) подчиненным указанному узлу @h, есди да, то 1. исключаем самого работника.
		where HIERARCHY_COLUMN.IsDescendantOf(@h) = 1 AND employee_id != @id;
	end

exec GetSubordinates @id = 7;



--задание 3--
--Создать процедуру, которая добавит подчиненный узел.--
drop procedure AddSubordinate
create procedure AddSubordinate
    @parent_id int,
    @first_name nvarchar(50),
    @last_name nvarchar(50),
    @stage int,
    @position nvarchar(50)
as
begin
    -- Проверяем, существует ли родитель
    declare @parent_hierarchy hierarchyid;

    select @parent_hierarchy = HIERARCHY_COLUMN 
    from Employee 
    where employee_id = @parent_id;

    if @parent_hierarchy IS NULL
    begin
        print 'Родительский узел не найден.';
        return;
    end

    -- Определяем новый уровень для подчиненного узла
    declare @new_hierarchy hierarchyid;
	SET @new_hierarchy = @parent_hierarchy.GetDescendant(NULL, NULL); -- Используем GetDescendant для создания нового узла
    insert into Employee (employee_id, first_name, last_name, boss_id, stage, position, HIERARCHY_COLUMN)
    values ( 
        (select ISNULL(MAX(employee_id), 0) + 1 from Employee), -- Генерируем новый ID
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
    @first_name = N'Олег', 
    @last_name = N'Олегов', 
    @stage = 11, 
    @position = N'Стажёр';

	delete from Employee where employee_id = 11;
	select *, HIERARCHY_COLUMN.ToString() as Hierarchy, HIERARCHY_COLUMN.GetLevel() as Level 
	from Employee;



--задание 4--
--Создать процедуру, которая переместит всю подчиненную ветку (первый параметр – значение верхнего перемещаемого узла, второй параметр – значение узла, в который происходит перемещение).--
create procedure MoveSubtree
    @source_id int,
    @target_id int
as
begin
    -- Проверяем, существует ли узел, который мы перемещаем
    declare @source_hierarchy hierarchyid;
    select @source_hierarchy = HIERARCHY_COLUMN from Employee where employee_id = @source_id;

    if @source_hierarchy IS NULL
    begin
        print 'Исходный узел не найден.';
        return;
    end

    -- Проверяем, существует ли целевой узел
    declare @target_hierarchy hierarchyid;
    select @target_hierarchy = HIERARCHY_COLUMN from Employee where employee_id = @target_id;

    if @target_hierarchy IS NULL
    begin
        print 'Целевой узел не найден.';
        return;
    end

    -- Проверяем, не является ли целевой узел потомком исходного узла
    if @source_hierarchy.IsDescendantOf(@target_hierarchy) = 1
    begin
        print 'Нельзя переместить узел, так как он является потомком целевого узла.';
        return;
    end

    -- Перемещение подчинённых узлов
    declare @new_hierarchy hierarchyid;
    set @new_hierarchy = @target_hierarchy.GetDescendant(NULL, NULL);

    -- Обновляем HIERARCHY_COLUMN для всех подчинённых узлов
    update Employee
    set HIERARCHY_COLUMN = @new_hierarchy.GetAncestor(1).GetDescendant(NULL, NULL).GetAncestor(0).GetDescendant(HIERARCHY_COLUMN, NULL)
    where HIERARCHY_COLUMN.IsDescendantOf(@source_hierarchy) = 1;

    -- Обновляем HIERARCHY_COLUMN для самого перемещаемого узла
    update Employee
    set HIERARCHY_COLUMN = @new_hierarchy
    where employee_id = @source_id;

    print 'Подчинённая ветка успешно перемещена.';
end;

select *, HIERARCHY_COLUMN.ToString() as Hierarchy, HIERARCHY_COLUMN.GetLevel() as Level 
	from Employee;


exec MoveSubtree @source_id = 7, @target_id = 2; -- Перемещаем узел с идентификатором 4 в узел с идентификатором 2
