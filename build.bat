@echo off

rem cd D:\___\Party-Junkie\html
rem del * /q
rem git rm *

cd D:\___\Party-Junkie\php
php generateCustom.php

cd D:\___\Party-Junkie\
git add *
git commit -m "%time% %date%"
git push
