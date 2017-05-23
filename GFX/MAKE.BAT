copy ..\p.exe

gonfle
copy /B p.exe+GAME1.PCX+GAME2.PCX+GAME3.PCX+SPRITE.PCX+SPRITE2.PCX+menu.PCX+sprite3.pcx+DRAW1.PCX+DRAW2.PCX
copy /B p.exe+med.pcx+med3.pcx+vic1.pcx+vic2.pcx+vic3.pcx+vic4.pcx+neige1.pcx+neige2.pcx+neige3.pcx
copy /B p.exe+pic.pcx+mrfond.pcx+micro.pcx+nuage1.pcx+nuage2.pcx+foret.pcx+feuille.pcx
copy /B p.exe+pause.pcx+medc.pcx+medg.pcx+neige1.mrb+micro1.mrb
copy /B p.exe+jungle1.mrb+rose1.mrb+fete1.mrb+crayon.pcx+crayon2.pcx+nuage1.mrb
copy /B p.exe+lapin1.pcx+mort.pcx+lapin2.pcx+lapin3.pcx+lapin4.pcx+foot.pcx+foot1.mrb+foot2.mrb+fete2.mrb
copy /B p.exe+neige2.mrb+rose2.mrb+jungle2.mrb+micro2.mrb+nuage2.mrb+soucoupe.pcx
copy /B p.exe+soccer.pcx+footanim.pcx+lune1.mrb+lune2.mrb
copy /B p.exe+\p\iff\iff.dat
ren p.exe mrboom30.exe
del ..\mrboom30.exe
copy mrboom30.exe ..
del mrboom30.exe
c
