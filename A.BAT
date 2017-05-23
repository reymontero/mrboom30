@echo off
REM on peut remplacer TASMX par TASM..
tasmx /mu /m9 /q \p\p.asm
REM tasm /m9 \p\p.asm
cd\watcom\pmode
wlink @c:\watcom\pmode\pmodew.lnk system pmodew file \p\p.obj , \p\ss\remdy-pm.obj
REM call %1.exe
cd\p
