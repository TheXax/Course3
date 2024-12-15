use lab5_qgis;


--�����
SELECT TOP 100 * FROM dbo.qgisxml;

--���������� ��� ���������������� ������ �� ���� ��������
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE DATA_TYPE IN ('geometry', 'geography');

--���������� SRID (���������� �������� ������ ���������)
SELECT DISTINCT Geometry.STSrid AS SRID
FROM SpatialData;

-- ���������� ������������ �������
SELECT COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_NAME = 'SpatialData';

--������� �������� ���������������� �������� � ������� WKT (��������� ������������� �������������� ��������)
SELECT Geometry.STAsText() AS WKT, *
FROM SpatialData;

--���������� ����������� ��������
SELECT a.ID, b.ID, a.Geometry.STIntersection(b.Geometry) AS Intersection
FROM SpatialData a, SpatialData b
WHERE a.Geometry.STIntersects(b.Geometry) = 1;

--���������� ����������� ��������
SELECT a.ID, b.ID, a.Geometry.STUnion(b.Geometry) AS UnionResult
FROM SpatialData a, SpatialData b;

-- ���������� ����������� ��������
SELECT a.ID, b.ID
FROM SpatialData a, SpatialData b
WHERE a.Geometry.STWithin(b.Geometry) = 1;

--��������� ����������������� �������
SELECT Geometry.STSimplify(0.01) AS SimplifiedGeometry
FROM SpatialData;

--���������� ��������� ������
SELECT Geometry.STAsText() FROM SpatialData;

--���������� ����������� ��������
SELECT Geometry.STDimension() AS Dimension FROM SpatialData;

--���������� ����� � �������
SELECT Geometry.STLength() AS Length, Geometry.STArea() AS Area
FROM SpatialData;

--���������� ���������� ����� ���������
SELECT a.ID, b.ID, a.Geometry.STDistance(b.Geometry) AS Distance
FROM SpatialData a, SpatialData b;

-- �������� ���������������� ������
--�����:
INSERT INTO SpatialData (ID, Name, Geometry)
VALUES (9, 'Point', geography::STPointFromText('POINT(30 10)', 4326));

--�����
INSERT INTO SpatialData (ID, Name, Geometry)
VALUES (5, 'Line', geometry::STLineStringFromText('LINESTRING(0 0, 10 10)', 4326));

--�������:
INSERT INTO SpatialData (ID, Name, Geometry)
VALUES (8, 'Polygon', geography::STPolyFromText('POLYGON((0 0, 0 10, 10 10, 10 0, 0 0))', 4326));

--�������, � ����� ������� �������� ��������� ���� �������
SELECT a.ID, b.ID
FROM SpatialData a, SpatialData b
WHERE a.Geometry.STWithin(b.Geometry) = 1;

select * from dbo.qgisxml;