use lab5_qgis;


--вывод
SELECT TOP 100 * FROM dbo.qgisxml;

--Определите тип пространственных данных во всех таблицах
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE DATA_TYPE IN ('geometry', 'geography');

--Определите SRID (уникальные значения систем координат)
SELECT DISTINCT Geometry.STSrid AS SRID
FROM SpatialData;

-- Определите атрибутивные столбцы
SELECT COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_NAME = 'SpatialData';

--Верните описания пространственных объектов в формате WKT (текстовое представление геометрических объектов)
SELECT Geometry.STAsText() AS WKT, *
FROM SpatialData;

--Нахождение пересечения объектов
SELECT a.ID, b.ID, a.Geometry.STIntersection(b.Geometry) AS Intersection
FROM SpatialData a, SpatialData b
WHERE a.Geometry.STIntersects(b.Geometry) = 1;

--Нахождение объединения объектов
SELECT a.ID, b.ID, a.Geometry.STUnion(b.Geometry) AS UnionResult
FROM SpatialData a, SpatialData b;

-- Нахождение вложенности объектов
SELECT a.ID, b.ID
FROM SpatialData a, SpatialData b
WHERE a.Geometry.STWithin(b.Geometry) = 1;

--Упрощение пространственного объекта
SELECT Geometry.STSimplify(0.01) AS SimplifiedGeometry
FROM SpatialData;

--Нахождение координат вершин
SELECT Geometry.STAsText() FROM SpatialData;

--Нахождение размерности объектов
SELECT Geometry.STDimension() AS Dimension FROM SpatialData;

--Нахождение длины и площади
SELECT Geometry.STLength() AS Length, Geometry.STArea() AS Area
FROM SpatialData;

--Нахождение расстояния между объектами
SELECT a.ID, b.ID, a.Geometry.STDistance(b.Geometry) AS Distance
FROM SpatialData a, SpatialData b;

-- Создайте пространственный объект
--Точка:
INSERT INTO SpatialData (ID, Name, Geometry)
VALUES (9, 'Point', geography::STPointFromText('POINT(30 10)', 4326));

--Линия
INSERT INTO SpatialData (ID, Name, Geometry)
VALUES (5, 'Line', geometry::STLineStringFromText('LINESTRING(0 0, 10 10)', 4326));

--Полигон:
INSERT INTO SpatialData (ID, Name, Geometry)
VALUES (8, 'Polygon', geography::STPolyFromText('POLYGON((0 0, 0 10, 10 10, 10 0, 0 0))', 4326));

--Найдите, в какие объекты попадают созданные вами объекты
SELECT a.ID, b.ID
FROM SpatialData a, SpatialData b
WHERE a.Geometry.STWithin(b.Geometry) = 1;

select * from dbo.qgisxml;