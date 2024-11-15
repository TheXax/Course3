--1. Найти всех начальников (тех, у кого есть подчинённые)
select distinct SR1.EMPL_NUM, SR1.NAME
from SALESREPS SR1
where SR1.EMPL_NUM in (select SR2.MANAGER from SALESREPS SR2 where SR2.MANAGER is not null);

--2. Найти подчинённых 2-го уровня для Sam Clark
select SR3.EMPL_NUM, SR3.NAME
from SALESREPS SR1
join SALESREPS SR2 on SR1.EMPL_NUM = SR2.MANAGER
join SALESREPS SR3 on SR2.EMPL_NUM = SR3.MANAGER
where SR1.NAME = 'Sam Clark';

--3. Вывести иерархию руководителей для Nancy Angelli
select SR1.EMPL_NUM, SR1.NAME, SR1.MANAGER
from SALESREPS SR1
where SR1.NAME = 'Nancy Angelli'
UNION ALL
select SR2.EMPL_NUM, SR2.NAME, SR2.MANAGER
from SALESREPS SR2
where SR2.EMPL_NUM = (select MANAGER from SALESREPS where NAME = 'Nancy Angelli')
UNION ALL
select SR3.EMPL_NUM, SR3.NAME, SR3.MANAGER
from SALESREPS SR3
where SR3.EMPL_NUM = (select MANAGER from SALESREPS where EMPL_NUM = 
    (select MANAGER from SALESREPS where NAME = 'Nancy Angelli'));