@echo off
chcp 65001 >nul
mkdir TXT 2>nul
move *.txt TXT
echo Все .txt файлы перемещены в каталог TXT
pause