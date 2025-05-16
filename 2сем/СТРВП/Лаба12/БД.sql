CREATE TABLE faculty (
    faculty VARCHAR(10) PRIMARY KEY,
    faculty_name NVARCHAR(100) NOT NULL
);

CREATE TABLE pulpit (
    pulpit VARCHAR(10) PRIMARY KEY,
    pulpit_name NVARCHAR(100) NOT NULL,
    faculty VARCHAR(10) FOREIGN KEY REFERENCES faculty(faculty)
);

CREATE TABLE subject (
    subject VARCHAR(10) PRIMARY KEY,
    subject_name NVARCHAR(100) NOT NULL,
    pulpit VARCHAR(10) FOREIGN KEY REFERENCES pulpit(pulpit)
);

CREATE TABLE teacher (
    teacher VARCHAR(10) PRIMARY KEY,
    teacher_name NVARCHAR(100) NOT NULL,
    pulpit VARCHAR(10) FOREIGN KEY REFERENCES pulpit(pulpit)
);

CREATE TABLE auditoriumtype (
    auditorium_type VARCHAR(10) PRIMARY KEY,
    auditorium_typename NVARCHAR(100) NOT NULL
);

CREATE TABLE auditorium (
    auditorium VARCHAR(10) PRIMARY KEY,
    auditorium_name NVARCHAR(100) NOT NULL,
    auditorium_capacity NVARCHAR(100) NOT NULL,
    auditorium_type VARCHAR(10) FOREIGN KEY REFERENCES auditoriumtype(auditorium_type)
);


-- Заполнение таблицы faculty
INSERT INTO faculty (faculty, faculty_name) VALUES
('F1', N'Информатика'),
('F2', N'Механика'),
('F3', N'Физика');

-- Заполнение таблицы pulpit
INSERT INTO pulpit (pulpit, pulpit_name, faculty) VALUES
('P1', N'Программирование', 'F1'),
('P2', N'Механика машин', 'F2'),
('P3', N'Теоретическая физика', 'F3');

-- Заполнение таблицы subject
INSERT INTO subject (subject, subject_name, pulpit) VALUES
('S1', N'Структуры данных', 'P1'),
('S2', N'Теория механизмов', 'P2'),
('S3', N'Квантовая механика', 'P3');

-- Заполнение таблицы teacher
INSERT INTO teacher (teacher, teacher_name, pulpit) VALUES
('T1', N'Иванов И.И.', 'P1'),
('T2', N'Петров П.П.', 'P2'),
('T3', N'Сидоров С.С.', 'P3');

-- Заполнение таблицы auditoriumtype
INSERT INTO auditoriumtype (auditorium_type, auditorium_typename) VALUES
('AT1', N'Лекционная'),
('AT2', N'Лабораторная'),
('AT3', N'Практическое занятие');

-- Заполнение таблицы auditorium
INSERT INTO auditorium (auditorium, auditorium_name, auditorium_capacity, auditorium_type) VALUES
('A1', N'Аудитория 101', '50', 'AT1'),
('A2', N'Лаборатория 202', '30', 'AT2'),
('A3', N'Практическое занятие 303', '20', 'AT3');





SELECT * FROM faculty;
SELECT * FROM pulpit;
SELECT * FROM subject;
SELECT * FROM auditoriumtype;
SELECT * FROM auditorium;