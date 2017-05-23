
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
;push ax
;mov al,' '
;call affascii
;pop ax

;push ax
;mov al,' '
;call affascii
;pop ax

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

