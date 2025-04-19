exec sp_configure 'show advanced options', 1
RECONFIGURE;
exec sp_configure 'clr enabled', 1
RECONFIGURE;
exec sp_configure 'clr strict security', 0
RECONFIGURE;
alter database LICENSES set trustworthy on;

create assembly REader
from 'C:\Лабы\Методы сбора, храниения, обработки и анализа данных\Лаба10\ClassLibrary3\ClassLibrary3\bin\Debug\ClassLibrary3.dll'
with permission_set = unsafe;
--drop assembly REader
create procedure ReadFile
@REadFile nvarchar(200),
@Context nvarchar(1000) output
as
external name REader.[ClassLibrary3.FileReader].ReadFile;
go
declare
@C nvarchar(1000);
exec ReadFile 'C:\Лабы\Методы сбора, храниения, обработки и анализа данных\Лаба10\lab10.txt', @C output;
print @C;