@echo off
cd D:\___\Party-Junkie\html
git rm *
cd D:\___\Party-Junkie\
php php/generateCustom.php
git add *
git commit -m "yah"
git push
