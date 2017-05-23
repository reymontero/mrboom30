ECHO creating a .DAT file with NON.IFF, OUI.IFF and TRIPTO13.RMD !!!
del main3.DAT
copy /B NON.IFF main3.dat
copy /B main3.dat+OUI.IFF
copy /B main3.dat+TRIPTO13.RMD
echo assembling...
tasm main3 /M6
tlink main3 remdy-05,main3.exe /3


