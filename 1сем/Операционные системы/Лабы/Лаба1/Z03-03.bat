@echo off
chcp 65001 >nul
If not exist "TXT" (
mkdir "TXT"
)
set rash=%1
move *.%rash% TXT
echo Все текстовые файлы перемещены в каталог TXT
pause
