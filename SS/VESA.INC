
MODE_SVGA=101h ;640*480 256c

INIT_VESA PROC NEAR
pusha
push ds es
;** determiner les performance de la carte SVGA **

;mov edi,offset data_vesa  ;buffer_vesa2     ;buffer en ES:DI attendu par la sous fonction 0
;mov ah,04fh ;numero fonction
;mov al,0    ;sous fonction
;int 10h
;cmp al,04fh ;indique fonction du Bios soutenues par la carte video.
;je c_ok
;jmp probleme_vesa
;c_ok:
;cmp ah,0    ;si =0 la fonction s'est executee correctement.
;jne probleme_vesa
;jmp c_bon_la_carte_est_bien_initialisee
;probleme_vesa:
;
;mov edx,offset pas_de_vesa
;mov ah,09h
;int 21h
;jmp byebyebye
;c_bon_la_carte_est_bien_initialisee:
;
;mov edi,offset data_vesa+0eh ;vise sur un pointeur far visant sur la liste
;                             ;des numeros de code des modes video soutenus.
;
;mov eax,ds:[edi]
;
;mov si,ax
;shr eax,16
;mov ds,ax
;;on cherche du bx=256 640*480 en 256 couleurs.
;mov bx,MODE_SVGA
;erererererer:
;lodsw
;cmp bx,ax
;je rrerererere3
;;call num
;cmp ax,0FFFFh
;jne erererererer
;mov ax,c
;mov ds,ax
;mov es,ax
;mov dx,offset pas_cette_reso_suportee
;mov ah,09h
;int 21h
;
;jmp byebyebye
;rrerererere3:
;-- LIRE un mode video determine.
;mov ax,c
;mov ds,ax
;mov es,ax
;mov cx,MODE_SVGA ;trouve au pif... (utilisation de cx)





;mov bx,MODE_SVGA
;mov edi,offset data_vesa    ;buffer en ES:DI attendu par la sous fonction 1
;mov ah,04fh ;numero fonction
;mov al,1    ;sous fonction
;int 10h
;cmp ah,1    ;si =0 la fonction s'est executee correctement.
;je probleme_vesa

;mov di,offset score+4 ;14h
;mov ax,es:[di]
;;call num
;mov    es:[gran],ax
;
;and eax,0ffffh
;shl eax,10 ;mutliplie par 1024!
;
;mov es:[nombre_de_pixel_par_page_avec_cette_granularite],eax
;

;-- ACTIVER UN MODE --
;mov bx,MODE_SVGA
;mov ah,04fh ;numero fonction
;mov al,2    ;sous fonction
;int 10h

;
;..................
;
;mov     edi,640*0+0 ;310
;mov     eax,edi
;movzx   ebx,word ptr es:[gran]
;shl     ebx,10
;xor     edx,edx
;div     ebx     ; ax=nø de fenˆtre et dx=reste=offset dans a000h
;mov     di,dx
;mov     dx,ax
;xor     bx,bx
;mov     ax,4f05h
;int     10h
;push    es
;push    0a000h
;pop     es
;mov     al,31
;mov cx,20
;rep stosb
;pop     es
;
;-----------------------------

;----------------------------

;mov     dx,03d4h
;mov     ax,0ff0ch    ;ah=data et al=reg.
;out     dx,ax

;--- finito
byebyebye:
pop  es ds
popa

ret
INIT_VESA endp

