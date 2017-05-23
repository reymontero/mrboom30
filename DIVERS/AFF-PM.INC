
noping proc near
push cx
mov cx,300
changer:
push cx
mov cx,01000h
il:
nop
loop il
pop cx
loop changer
pop cx
ret
noping endp

PUSHALL MACRO     ; Pushes all registers onto stack = 18c
PUSHAD
PUSH DS ES
ENDM

POPALL MACRO      ; Pops all registers from stack = 18c
POP ES DS
POPAD
ENDM

affsigne proc near
push ax
pushf
;add ax,0
;jns nonsigne
;push ax
;mov al,'-'
;call affascii
;pop ax
;neg ax
;jmp sdfsdfsdf
;nonsigne:
;push ax
;mov al,'+'
;call affascii
;pop ax
sdfsdfsdf:
call affdecimal
push ax
mov al,' '
call affascii
pop ax
push ax
mov al,' '
call affascii
pop ax
popf
pop ax
ret
affsigne endp
affascii proc near
push ax
push dx
mov dl,al
mov ah,2
int 21h
pop dx
pop ax
ret
affascii endp

affdecimal proc near
push bx
push cx
mov bx,10
mov cx,0
decompose:
mov dx,0
div bx
push dx
inc cx
cmp ax,0
jnz decompose
affichage:
pop ax
call affchiffre2
dec cx
JNZ affichage
pop cx
pop bx
ret
affdecimal endp
affchiffre2 proc near
push ax
push dx
add al,48
mov dl,al
mov ah,2
int 21h
pop ax
pop dx
ret
affchiffre2 endp

num proc near ;entree eax:juska 9999999999
push dx esi
push ebx eax ecx

;mov eax,0543212345

mov ebx,eax

mov esi,offset liste_de_machin
mov ecx,[esi]
errrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr:
mov ax,0
rrtetrertertretertterert:
cmp ebx,ecx ;10000
jb reerrereerret
sub ebx,ecx ;10000
inc ax
jmp rrtetrertertretertterert
reerrereerret:
;affchiffre
push ax
push dx
add al,48
mov dl,al
mov ah,2
int 21h
pop ax
pop dx


add esi,4
mov ecx,[esi]
or ecx,ecx
jz reererreer
jmp errrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
reererreer:

mov dl,' '
mov ah,2
int 21h

pop ecx eax ebx
pop esi dx
ret
endp
liste_de_machin dd 1000000000,100000000,10000000,1000000,100000,10000,1000,100,10,1,0

;
trucs db '0123456789ABCDEF'

;----- aff hexa.
;notreadresse db 4 dup (0FFh) ;netadd
;             db 6 dup (0FFh) ;nodeadd
;             dw 0FFFFh       ;sockette...

aff_adresse proc near  ; ds:si sur adresse
push ds es
Pushad

mov cx,10
dds:
call hexa

cmp cx,1
je ertertertertert

mov dl,'.'

cmp cx,9
jne reterertert
mov dl,' '
reterertert:

cmp cx,3
jne reterertertu
mov dl,' '
reterertertu:


mov ah,2
int 21h
loop dds
ertertertertert:


mov dl,10
mov ah,2
int 21h
mov dl,13
mov ah,2
int 21h


popad
pop es ds
ret
aff_adresse endp

hexa proc near ; ds:si sur variable

xor ax,ax
lodsb
push ax
shr ax,4
movzx ebx,ax
mov dl,cs:[trucs+ebx]
mov ah,2
int 21h

pop ax
and al,01111B
movzx ebx,ax
mov dl,cs:[trucs+ebx]
mov ah,2
int 21h

ret
hexa endp



