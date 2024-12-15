create database lab5_qgis;
 use lab5_qgis;
CREATE TABLE SpatialData (
    ID INT PRIMARY KEY,
    Name VARCHAR(255),
    Geometry GEOGRAPHY
);

INSERT INTO SpatialData (ID, Name, Geometry)
VALUES (1, 'Point A', geography::STGeomFromText('POINT(30 10)', 4326)),
       (2, 'Line A', geography::STGeomFromText('LINESTRING(30 10, 40 40, 20 40)', 4326)),
       (3, 'Polygon A', geography::STGeomFromText('POLYGON((30 10, 40 40, 20 40, 30 10))', 4326));