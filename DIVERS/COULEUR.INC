last_color proc near

PUSHALL
;------------
;dans BX: la couleur k'on veut !!!
;mov bl,0100B ;rouge
;mov bh,10000000B ;indique clignotement
push bx
;mov ax,0b800h
;mov es,ax
;mov ds,ax
push ds
pop es

mov edi,0b8000h
mov esi,0b8000h
;xor di,di
;xor si,si
;-----
mov ah,03h
mov bh,0
int 10h
;dans dh ligne du curseur
dec dh ; car toujours > 1 vu k'on balance apres avoir afficvh‚

;movzx edx,dh ;*128
shr dx,8
and edx,255
mov eax,edx
shl edx,7
shl eax,5
add edx,eax
add esi,edx
add edi,edx
mov cx,80
pop bx

nooon:
inc edi
inc esi

lodsb
or al,bh
and al,11110000B
or  al,bl
stosb
dec cx
jne nooon
;---------------------------------
POPALL
ret
last_color endp

