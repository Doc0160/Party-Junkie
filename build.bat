@echo off

cd D:\___\Party-Junkie\html
rm *
rem git rm *

cd D:\___\Party-Junkie\php
php generateCustom.php

cd D:\___\Party-Junkie\
git add *
git commit -m "%time% %date%"
git push
