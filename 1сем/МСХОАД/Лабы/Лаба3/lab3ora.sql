CREATE TABLE Employee (
    employee_id NUMBER PRIMARY KEY,
    first_name VARCHAR2(50),
    last_name VARCHAR2(50),
    boss_id NUMBER,
    
    FOREIGN KEY (boss_id) 
    REFERENCES Employee(employee_id) 
);
DROP TABLE Employee;

select* from Employee;
INSERT INTO Employee VALUES(1, '����', '�������', NULL);
INSERT INTO Employee VALUES(2, '����', '������', 1);
INSERT INTO Employee VALUES(3, '��������', '��������', 2);
INSERT INTO Employee VALUES(4, '������', '�������', 3);
INSERT INTO Employee VALUES(5, '����', '��������', 4);
INSERT INTO Employee VALUES(6, '�������', '��������', 4);
INSERT INTO Employee VALUES(7, '��������', '����������', 4);
INSERT INTO Employee VALUES(8, '���������', '�����������', 7);
INSERT INTO Employee VALUES(9, '������', '��������', 1);
INSERT INTO Employee VALUES(10, '�������', '��������', 9);
commit;

UPDATE Employee
SET boss_id = NULL
WHERE employee_id = 1;
UPDATE Employee
SET boss_id = 1
WHERE employee_id = 2;
UPDATE Employee
SET boss_id = 2
WHERE employee_id = 3;
UPDATE Employee
SET boss_id = 3
WHERE employee_id = 4;
UPDATE Employee
SET boss_id = 4
WHERE employee_id = 5;
UPDATE Employee
SET boss_id = 4
WHERE employee_id = 6;
UPDATE Employee
SET boss_id = 4
WHERE employee_id = 7;
UPDATE Employee
SET boss_id = 7
WHERE employee_id = 8;
UPDATE Employee
SET boss_id = 1
WHERE employee_id = 9;
UPDATE Employee
SET boss_id = 9
WHERE employee_id = 10;
commit;

CREATE OR REPLACE PROCEDURE DisplayHierarchy (p_id IN NUMBER) AS
  v_hierarchy VARCHAR2(4000);
BEGIN
  -- �������� � ���������� ���������� � ��������� ����� �� ��������
  FOR rec IN (
    SELECT employee_id, first_name, last_name
    FROM Employee
    START WITH employee_id = p_id
    CONNECT BY NOCYCLE PRIOR boss_id = employee_id
    ORDER BY LEVEL DESC
  ) LOOP
    -- ��������� ��� � ID ���������� � ������ ��������
    v_hierarchy := v_hierarchy || ' -> ' || rec.first_name || ' ' || rec.last_name || ' (ID: ' || rec.employee_id || ')';
  END LOOP;

  -- ������� ������ ������� ' -> ' �� ������ ��������
  IF v_hierarchy IS NOT NULL THEN
    v_hierarchy := SUBSTR(v_hierarchy, 5);
  END IF;

  -- ������� ������ ��������
  DBMS_OUTPUT.PUT_LINE(v_hierarchy);
END DisplayHierarchy;

EXEC DisplayHierarchy(11);

--SELECT employee_id, first_name, last_name, boss_id
--FROM Employee
--START WITH boss_id IS NULL
--CONNECT BY PRIOR employee_id = boss_id;



-- 2. ��������� ��� ����������� ���� � ��������� ������ ��������
CREATE OR REPLACE PROCEDURE ShowSubordinates (
    p_employee_id IN INT
) AS
BEGIN
    FOR rec IN (
        SELECT employee_id, first_name, last_name, LEVEL AS hierarchy_level
        FROM Employee
                WHERE  employee_id != p_employee_id
        CONNECT BY PRIOR employee_id = boss_id
        START WITH employee_id = p_employee_id
    ) LOOP
        DBMS_OUTPUT.PUT_LINE('ID: ' || rec.employee_id || ', Name: ' || rec.first_name || ' ' || rec.last_name || ', Level: ' || rec.hierarchy_level);
    END LOOP;
END;

    exec ShowSubordinates(3);
    

-- 3. ������� ����������� ����.
CREATE OR REPLACE PROCEDURE AddSubordinate (
    p_employee_id IN INT,
    p_first_name IN VARCHAR2,
    p_last_name IN VARCHAR2,
    p_boss_id IN INT
) AS
BEGIN
    INSERT INTO Employee (employee_id, first_name, last_name, boss_id)
    VALUES (p_employee_id, p_first_name, p_last_name, p_boss_id);
    
    COMMIT;
END;

BEGIN
    AddSubordinate(
        p_employee_id => 12,
        p_first_name => '����',
        p_last_name => '��������',
        p_boss_id => 2   
    );
END;

select * from Employee;


-- 4 ���������� ��� ����������� ����� 
CREATE OR REPLACE PROCEDURE MoveSubtree (
    p_new_parent_id IN INT,
    p_child_id IN INT
) AS
    v_old_parent_id INT;
BEGIN
    -- �������� ������������� ������� ��������
    SELECT boss_id INTO v_old_parent_id FROM Employee WHERE employee_id = p_child_id;

    -- ����������� ���������� �����
    UPDATE Employee
    SET boss_id = p_new_parent_id
    WHERE boss_id = v_old_parent_id OR employee_id = p_child_id;

    COMMIT;
END;

exec MoveSubtree(2, 12);
select * from Employee;