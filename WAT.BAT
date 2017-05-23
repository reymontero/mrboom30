@echo off
REM on peut remplacer TASMX par TASM..
tasmx /mu /m9 /q %1
wlink @c:\watcom\pmode\pmodew.lnk system pmodew file %1
REM call %1.exe
