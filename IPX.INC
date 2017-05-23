
open_socket MACRO sochette
local rttrrtyrtyrtytyrtyrtyrtyr
local reussi
;-----------------
;Open Socket:
;    Before calling:
;        bx=0000h
;        al=socket longevity flag
;            00h the socket will remain open until a Close Socket call or the
;                application terminates
;            01h the socket will remain open until a Close Socket call
;        dx=socket (big-endian)
;            0000h IPX will chose an available socket between 4000h and 5000h
;            !0000h IPX will attempt to open the specified socket
;    After calling:
;        al=completion code
;            00h Success
;            FFh Socket Already Open
;            FEh Socket Table Is Full
;        dx=assigned socket number
;    Notes:
rttrrtyrtyrtytyrtyrtyrtyr:
;;xor bx,bx
;;mov al,00h
xor edx,edx
mov dx,sochette ;!!!
add dx,[grosse_sochette]


;push eax
;mov eax,edx
;call num
;pop eax

;;int 07ah

;----------------------

call clear_call_int
mov [call_int+10h],0
mov [call_int+1Ch],0

;mov word ptr [call_int+14h],dx

mov [call_int+14h],edx

;call_int dd 0 ;           00h     4       EDI
;dd 0 ;           04h     4       ESI
;dd 0 ;           08h     4       EBP
;dd 0 ;           0ch     4       reserved, ignored
;dd 0 ;           10h     4       EBX
;dd 0 ;           14h     4       EDX
;dd 0 ;           18h     4       ECX
;dd 0 ;           1ch     4       EAX
;dw 0 ;           20h     2       CPU status flags
;dw 0 ;           22h     2       ES
;dw 0 ;           24h     2       DS
;dw 0 ;           26h     2       FS
;dw 0 ;           28h     2       GS
;dw 0 ;           2ah     2       IP
;dw 0 ;           2ch     2       CS
;dw 0 ;           2eh     2       SP
;dw 0 ;           30h     2       SS

;  AX     = 0300h
;  BL     = interrupt number
;  BH     = must be 0
;  CX     = number of words to copy from the protected mode stack to the real
;           mode stack
;  ES:EDI = selector:offset of real mode register data structure in the
;           following format:
push es
mov ax,ds
mov es,ax
mov edi,offset call_int
mov cx,0
mov bh,0
mov bl,07ah
mov ax,300h
int 31h
pop es

;jmp reussi ;!!


;mov eax,[call_int+14h]
;call num

mov eax,[call_int+1ch]
and eax,255
;call num
;call affsigne

;mov ax,word ptr [call_int+14h]
;call affsigne

;------------------

or ax,ax ;al,al
jz reussi

;on ferme la socket.
;
;xor edx,edx
;mov dx,sochette
;add dx,[grosse_sochette]
;call ferme_socket
;
;;-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-
;;on la ferme ???
;
;;        dx=socket number (big-endian)
;mov bx,01h
;mov dx,sochette ;!!!
;add dx,[grosse_sochette]
;;call dword ptr [fcall]
;int 07ah
;jmp rttrrtyrtyrtytyrtyrtyrtyr
;;----------------------------------------

;and ax,0FFH
;call affsigne

mov edx,offset socketipx
mov ah,09h
int 21h
  MOV     AX,04C00H
  INT     21H
reussi:

;mov [socket],ax
;call affsigne

ENDM

init_ipx proc near
pushad
push es ds

cmp modeinfo,1
jne ertrerertrtrererrr
mov [grosse_sochette],0
ertrerertrtrererrr:


;Getting IPX entry address:
;    mov ax,7A00h
;    int 2Fh
;
;    if IPX is loaded:
;        al is set to 0FFh
;        ES:DI points to the IPX far call entry address
;    otherwise:
;        al is unchanged

cmp [ipx_],1 ; dd 1 ;1:oui_ par default... (indique teste serra fait...)
             ;0:non...
jne onenveutpas

;lea edx,tectewn
;,sub edx,offset tectewn
;neg edx
;mov [tecte2],edx
;
;mov ebx,offset tected
;
;cmp [master],1
;jne trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2R
;mov ebx,offset tecte_sl
;trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2R:
;
;add ebx,[tecte2]
;inc [tecte2]


lea edx,warning_ipx
mov ah,09h
int 21h
mov dl,13
mov ah,2
int 21h



;mov ax,07a00h
;int 2fh
;-------
pushall
call clear_call_int
mov [call_int+1ch],07a00h
;call_int dd 0 ;           00h     4       EDI
;dd 0 ;           04h     4       ESI
;dd 0 ;           08h     4       EBP
;dd 0 ;           0ch     4       reserved, ignored
;dd 0 ;           10h     4       EBX
;dd 0 ;           14h     4       EDX
;  AX     = 0300h
;  BL     = interrupt number
;  BH     = must be 0
;  CX     = number of words to copy from the protected mode stack to the real
;           mode stack
;  ES:EDI = selector:offset of real mode register data structure in the
;           following format:
mov ax,ds
mov es,ax
mov edi,offset call_int
xor cx,cx
mov bh,0
mov bl,02fh
mov ax,300h
int 31h

popall
mov eax,[call_int+1ch]
and eax,0FFFFh


cmp al,0ffh
je okrrtereertrte

   mov edx,offset pasipx
   mov ah,09h
   int 21h
        mov bl,0100B ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color

onenveutpas: ;cas de demande de pas ipx dans ligne de commande.
cmp windows,0
jne nonon_deja_mis_mode_w95
lea edx,tected
sub edx,offset tected2
neg edx
mov [tecte2],edx
nonon_deja_mis_mode_w95:

mov [ipx_],0
mov [master],0 ;devient master.
mov [max_packet],15000 ;

   pop ds es
   popad
ret
;   MOV     AX,04C00H
;   INT     21H
okrrtereertrte:

;--- il y a du ipx !
cmp windowsnetwork,1
jne mklkljkmlrtkmljerkmjltrkmjltrkjlmrtkjlmtrkjmlremjklretlmjree
lea edx,tected
sub edx,offset tectewn
neg edx
mov [tecte2],edx
mklkljkmlrtkmljerkmjltrkmjltrkjlmrtkjlmtrkjmlremjklretlmjree:


;mov word ptr [fcall],di  on s'en fout on utilise l'int 7ah.
;mov ax,es
;mov word ptr [fcall+2],ax

;Get max packet size:
;    Before calling:
;        bx=001Ah
;    After calling:
;        ax=maximum packet size
;        cx=IPX retry count
;    Notes:
;        Max packet size will never be less than 576 bytes.
;
xor eax,eax


;mov bx,01ah
;call dword ptr [fcall]
;int 07ah

mov ebx,01ah
call appelle_interruption

;call_int dd 0 ;           00h     4       EDI
;dd 0 ;           04h     4       ESI
;dd 0 ;           08h     4       EBP
;dd 0 ;           0ch     4       reserved, ignored
;dd 0 ;           10h     4       EBX
;dd 0 ;           14h     4       EDX
;dd 0 ;           18h     4       ECX
;dd 0 ;           1ch     4       EAX
;dw 0 ;           20h     2       CPU status flags
;dw 0 ;           22h     2       ES
;dw 0 ;           24h     2       DS
;dw 0 ;           26h     2       FS
;dw 0 ;           28h     2       GS
;dw 0 ;           2ah     2       IP
;dw 0 ;           2ch     2       CS
;dw 0 ;           2eh     2       SP
;dw 0 ;           30h     2       SS

;mov ax,word ptr
;[call_int+01ch]
;call affsigne

xor eax,eax
mov ax,word ptr [call_int+01ch]
sub eax,packet_header_size
mov [max_packet],eax
;call num


;dans ax on l'a...
;call affsigne
;****************************************************************************
;Get internetwork address:
;    Before calling:
;        bx=0009h
;        es:si=request buffer address
;    After calling:
;        si destroyed
;    Notes:
;        Request Buffer:
;            offset  field               type        order
;            0       network address     BYTE[4]     big-endian
;            4       network node        BYTE[4]     big-endian
;

mov ebx,9                    ;valeur de ebx...
mov esi,offset notreadresse  ;sera comvertit en ES:SI en real...
call special_essi            ;puis appelle l'interruption ...

mov edx,offset ipx
mov ah,09h
int 21h


;socket_jeu equ 576 ;sockette transferts pendant le jeu



;socket_system equ 577 ;socket envois massif: DEMANDE CONNECTION.
;socket_system2 equ 578 ;socket de r‚ponse a une demande de connection.
                       ;+ test si network marche...



;open_socket 9c86h
;socket_jeu
;open_socket socket_jeu
;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h
;
;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h
;
;open_socket 9d86h
;socket_system
;open_socket 9e86h
;socket_system2

socket_jeu equ 0ac86h ;sockette transferts pendant le jeu
socket_system equ 0ad86h ;socket envois massif: DEMANDE CONNECTION.
socket_system2 equ 0ae86h ;socket de r‚ponse a une demande de connection.
                       ;+ test si network marche...

open_socket socket_jeu

;open_socket socket_jeu
;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h


;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h

open_socket socket_system
open_socket socket_system2

mov word ptr [notreadresse+10],socket_jeu
mov word ptr [toutes_adresse+10],socket_jeu

push ax
mov ax,[grosse_sochette]
add word ptr [notreadresse+10],ax
add word ptr [toutes_adresse+10],ax
pop ax

cmp stat_ou_pas,1
jne klmjklljkjlkm
mov esi,offset notreadresse
call aff_adresse
klmjklljkjlkm:

;call affiche_les_adresses

;----------------------------
;mov edx,offset test1
;mov ah,9
;int 21h
;
;renvois_encore___bizarre:
;ecoute2 ecb3 recu_data3 header_ecoute3 1 socket_system2
;mov ebp,offset donnee3                ;
;mov esi,offset notreadresse           ;
;mov byte ptr [donnee3],44             ;test reso...
;mov word ptr [esi+10],socket_system2
;envois2 ecb4 header_envois4 1 socket_system2
;mov ecx,15
;herve:
;push ecx
;call vbl
;pop ecx
;dec ecx
;jz foireeee
;
;cmp byte ptr [ecb3+8],0
;jne  herve
;;cmp byte ptr [recu_data3],44 ;test reso...
;;jne  renvois_encore___bizarre
;
;mov edx,offset test2
;mov ah,9
;int 21h
;
;;-----------------------------------
;
pop ds es
popad
ret
;foireeee:
;
;mov edx,offset test3
;mov ah,9
;int 21h
;
;call de_init_ipx
;
;pop ds es
;popad
;
;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h
;
;ret
init_ipx endp


de_init_ipx proc near
cmp [ipx_],0 ;si pas ipx load‚..
jne bon_nu3
ret
bon_nu3:
pushall
lea edx,warning_ipx2
mov ah,9
int 21h
mov dl,13
mov ah,2
int 21h


;Close Socket:
;    Before calling:
;        bx=0001h
;        dx=socket number (big-endian)




;mov bx,01h
xor edx,edx

mov dx,socket_jeu
add dx,[grosse_sochette]
call ferme_socket
;int 07ah
;mov ax,66
;call affsigne

;mov bx,01h
mov dx,socket_system2
add dx,[grosse_sochette]
call ferme_socket
;int 07ah



;mov bx,01h
mov dx,socket_system
add dx,[grosse_sochette]
call ferme_socket
;int 07ah

;mov ax,66
;call affsigne



;xor ax,ax
;mov bx,01h
;mov dx,socket_system2
;add dx,[grosse_sochette]
;int 07ah


lea edx,warning_ipx3
mov ah,9
int 21h
mov dl,13
mov ah,2
int 21h
popall
ret
de_init_ipx endp

clear_call_int proc near
push ds es
pushad
mov ax,ds
mov es,ax
mov edi,offset call_int
mov ecx,032h
rep stosb
popad
pop es ds
ret
clear_call_int endp

envois proc near ;entree ESI: source sur adresse envois
                 ;       ebp: source sur ce qu'on envois. ;offset donnee
PUSHALL


;--------- vide le l'ecb et le header...
mov ax,ds
mov es,ax
mov edi,offset ecb2
mov ecx,78
xor eax,eax
rep stosb
;---------------------------------------

;---------------envois -*-
;Send Packet:
;    Before calling:
;        bx=0003h
;        es:si=ECB address
;    After calling:
;        nothing is returned
;    Notes:

;dw 07777h ;16     ;sockette...


;mov ax,[socket]

PUSHALL
mov ax,ds
mov es,ax
mov edi,offset header_envois+6 ;copie adresse complete de destination
mov ecx,12
rep movsb
POPALL

PUSHALL               ;copie nodeadd de destination
mov ax,ds
mov es,ax
mov edi,offset ecb2+28
add esi,4
mov ecx,6
rep movsb
POPALL

mov ebx,3

mov ax,[esi+10] ;prend la socket a partie de l'adresse que l'on a donn‚.
                ;adresse ou on envois

mov esi,offset ecb2

;mov ax,socket_jeu ;[socket]
mov [esi+10],ax

;     db  0   ;    14      immediate address                   BYTE

mov word ptr [esi+4],0 ;offset procedurea ;0  ;ESR
mov word ptr [esi+6],0 ;cs ;offset procedurea ;0  ;ESR

mov word ptr [esi+34],2  ;     dw  0   ;    34      fragment count

push eax dx
push esi
mov esi,ebp ;offset donnee
call offset_2_adresse_physique ;ds:esi pm -- > dx:ax rm
pop esi
mov word ptr [esi+42],ax
mov word ptr [esi+44],dx
pop dx eax

push eax dx
push esi
mov esi,offset header_envois
call offset_2_adresse_physique ;ds:esi pm -- > dx:ax rm
pop esi
mov word ptr [esi+36],ax
mov word ptr [esi+38],dx
pop dx eax


;mov word ptr [esi+42],offset envoye_data                  ;?
;mov word ptr [esi+42+2],polly2 ;?
;mov word ptr [esi+36],offset header2     ;?
;mov word ptr [esi+36+2],polly2           ;?

mov word ptr [esi+40],packet_header_size ;taille header2 ;?
mov word ptr [esi+46],packet_data_size
;call dword ptr [fcall]
;int 07ah

;mov ebx,9                    ;valeur de ebx...
;mov esi,offset notreadresse  ;sera comvertit en ES:SI en real...
call special_essi


;     db  0   ;    9       completion code                     BYTE

;movzx ax,byte ptr [ecb2+9]
;call affsigne

finto:
POPALL
ret
envois endp

ecoute proc near ;dans AX: SOCKETTE.
PUSHALL
push ax

;--------- vide le l'ecb et le header...
mov ax,ds
mov es,ax
xor eax,eax
mov edi,offset ecb1
mov ecx,78
rep stosb
;---------------------------------------

;Listen for Packet:
;    Before calling:
;        bx=0004h
;        es:si=ECB address
;    After calling:
;        al=completion code
;            00h Success
;            FFh Listening Socket Does Not Exist

mov esi,offset ecb1

;
pop word ptr [esi+10]

mov  word ptr [esi+4],0 ;offset procedurea   ;ESR
mov  word ptr [esi+6],0 ;cs                  ;ESR

mov  word ptr [esi+34],2                     ;fragment count

push eax dx
push esi
mov esi,offset recu_data
call offset_2_adresse_physique ;ds:esi pm -- > dx:ax rm
pop esi
mov word ptr [esi+42],ax                     ;fragment address 2
mov word ptr [esi+44],dx                     ;fragment size 2
pop dx eax

push eax dx
push esi
mov esi,offset header_ecoute
call offset_2_adresse_physique ;ds:esi pm -- > dx:ax rm
pop esi
mov word ptr [esi+36],ax                    ;fragment address 1
mov word ptr [esi+38],dx                    ;fragment size 1
pop dx eax

mov word ptr [esi+40],packet_header_size    ;fragment size 1
mov word ptr [esi+46],packet_data_size      ;fragment size 2

mov ebx,4

;mov ebx,9                    ;valeur de ebx...
;mov esi,offset notreadresse  ;sera comvertit en ES:SI en real...
call special_essi

cmp al,0                      ;si erreur....
jne erreur_dans_ecoute

;mov edx,offset ecoute_msg
;mov ah,9
;int 21h
jmp erterrterte3

erreur_dans_ecoute:
mov edx,offset erreur_dans_ecoute2
mov ah,9
int 21h
POPALL
ret

erterrterte3:
POPALL
ret
ecoute endp



;push eax
;mov eax,offset header2
;call offset_2_adresse_lineaire
;mov dword ptr [esi+36],eax
;pop eax

offset_2_adresse_physique proc near ;source ds:esi
                                    ;adresse physique (dx:ax)

;2.4 - Function 0006h - Get Segment Base Address:
;------------------------------------------------
;  Returns the 32bit linear base address from the descriptor table for the
;specified segment.
;In:
;  AX     = 0006h
;  BX     = selector
;ut:
;  if successful:
;    carry flag clear
;    CX:DX  = 32bit linear base address of segment

push bx
mov ax,006h
mov bx,ds
int 31h
movzx eax,cx
shl eax,16
mov ax,dx
add eax,esi ;offset notreadresse
;dans eax on a donc l'adresse physique
push ax
shr eax,4
mov dx,ax ;dans DX on recup le ds: du mode reel
pop ax
and ax,01111B ;dans ax, le si
pop  bx
ret
offset_2_adresse_physique endp



special_essi proc near


push ebx
push esi

call clear_call_int

;mov ax,ds
;mov es,ax
;mov esi,offset notreadresse

;---- faut transformer en mode real...
pop esi
call offset_2_adresse_physique ;ds:esi pm -- > dx:ax rm

mov word ptr [call_int+22h],dx  ;ES
mov word ptr [call_int+04h],ax   ; dd 0 ;           04h     4       ESI

pop eax
mov dword ptr [call_int+10h],eax ;9  ;EBX

;;call dword ptr [fcall]
;int 07ah

;  AX     = 0300h
;  BL     = interrupt number
;  BH     = must be 0
;  CX     = number of words to copy from the protected mode stack to the real
;           mode stack
;  ES:EDI = selector:offset of real mode register data structure in the
;           following format:
mov ax,ds
mov es,ax
mov edi,offset call_int
mov cx,0
mov bh,0
mov bl,07ah
mov ax,300h
int 31h
;jnc r4534534534534retteeeeeeeee
;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h
;r4534534534534retteeeeeeeee:
;**************************************************************************
ret
special_essi endp

appelle_interruption proc near
push es

push ebx
push esi
call clear_call_int

;mov ax,ds
;mov es,ax
;mov esi,offset notreadresse

;---- faut transformer en mode real...
pop esi

;call offset_2_adresse_physique ;ds:esi pm -- > dx:ax rm
;
;mov word ptr [call_int+22h],dx  ;ES
;mov word ptr [call_int+04h],ax   ; dd 0 ;           04h     4       ESI

pop eax
mov dword ptr [call_int+10h],ebx ;9  ;EBX

;mov bx,01ah
;call dword ptr [fcall]
;int 07ah


;;call dword ptr [fcall]
;int 07ah

;  AX     = 0300h
;  BL     = interrupt number
;  BH     = must be 0
;  CX     = number of words to copy from the protected mode stack to the real
;           mode stack
;  ES:EDI = selector:offset of real mode register data structure in the
;           following format:
mov ax,ds
mov es,ax
mov edi,offset call_int
mov cx,0
mov bh,0
mov bl,07ah
mov ax,300h
int 31h
;jnc r4534534534534retteeeeeeeee
;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h
;r4534534534534retteeeeeeeee:
;**************************************************************************
pop es
ret
appelle_interruption endp


dyna_net proc near

cmp [ipx_],0 ;si pas ipx load‚..
jne bon_nu2
ret
bon_nu2:

cmp [assez_de_memoire],1
je erettererttrtyrtyyrtrtyrereerre
pushall
mov pic_de_tout_debut,1
mov cx,16
regtrtetrtrtrtrtete:
push cx
mov esi,1966080+64000*21
call copie_page
call aff_page2
call pal_visage
call vbl
pop cx
dec cx
jnz regtrtetrtrtrtrtete
mov pic_de_tout_debut,0
popall
erettererttrtyrtyyrtrtyrereerre:

PUSHALL

cmp [assez_de_memoire],1
jne erettererttrtyrtyyrtrtyrereerreeretetet
mov dl,13
mov ah,2
int 21h
mov edx,offset cnx1
mov ah,9
iNT 21h
mov dl,13
mov ah,2
int 21h
mov edx,offset cnx2
mov ah,9
iNT 21h
erettererttrtyrtyyrtrtyrereerreeretetet:

ecoute2 ecb3 recu_data3 header_ecoute3 2 socket_system2
mov cx,25
oerzertrteertertert1:
push cx


cmp [assez_de_memoire],1
je erettererttrtyrtyyrtrtyrereerreeretetetereeeeeeeeeeeeeeeeeeerrhhtrlkerjerjhet
pushall
mov esi,1966080+64000*21
call copie_page
pushall
push ds
pop es
push fs
pop  ds
mov esi,1966080+64000*22+107     ;foot 7896000+384000+46080+64000+64000+11
mov edi,offset buffer+100+192*320
test cx,1
jz rerettrOooooOOooOOoo
aff_spt 6 126
rerettrOooooOOooOOoo:
popall
call aff_page2
popall
erettererttrtyrtyyrtrtyrereerreeretetetereeeeeeeeeeeeeeeeeeerrhhtrlkerjerjhet:

;******** ENVOIS A TOUS UNE DEMANDE DE CONNECTION *******
mov ebp,offset donnee3
mov esi,offset toutes_adresse
mov word ptr [toutes_adresse+10],socket_system

push ax
mov ax,[grosse_sochette]
add word ptr [toutes_adresse+10],ax
pop ax

mov byte ptr [donnee3],version_du_jeu  ;recherche de master...

;----------------------- le slave se r‚volte ??? --------------------------
cmp byte ptr [clavier+59],1 ;F1 press‚
jne erertrterterte
cmp byte ptr [clavier+59],1 ;F12 press‚
jne erertrterterte
mov byte ptr [donnee3],99  ;killage du master !!!!!
erertrterterte:
;---------------------
;call vbl2
envois2 ecb4 header_envois4 1 socket_system
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3

;******************************************************
;cmp byte ptr [sortie2],1 ;F2
;je ertteertrerterteert2

cmp [assez_de_memoire],1
jne erettererttrtyrtyyrtrtyrereerreeretetetEE
mov dl,'.'
mov ah,2
int 21h
erettererttrtyrtyyrtrtyrereerreeretetetEE:

;call vbl2
cmp byte ptr [ecb3+8],0
jne  terertterertertertteertrerterteert

cmp byte ptr [recu_data3],55 ;recu un WELCOME !!! du master..
je  ertteertrerterteert ;bien recu... found a network

cmp byte ptr [recu_data3],56 ;recu un WELCOME !!! reviens vite dans le jeu...
                             ;kezax a fait le malin...
jne erertterertooityuioutyklmtyutyuyut
mov [kezax],2
jmp ertteertrerterteert ;bien recu... found a network
erertterertooityuioutyklmtyutyuyut:

cmp byte ptr [recu_data3],76 ;recu 'un degages lamer'
je  restes_tranquilles

;r‚‚coute...
ecoute2 ecb3 recu_data3 header_ecoute3 2 socket_system2
terertterertertertteertrerterteert:
pop cx
dec cx
jnz oerzertrteertertert1

;;---
;cmp trygain,1
;jne iiio
;push cx
;jmp  restes_tranquilles
;iiio:
;;------------------------

cmp [assez_de_memoire],1
jne terettererttrtyrtyyrtrtyrereerreeretetetEE
mov edx,offset no_dyna
mov ah,9
int 21h
mov bx,15 ;blanc sans clignotant.
call last_color
terettererttrtyrtyyrtrtyrereerreeretetetEE:

mov [master],0 ;je suis master.

;----
mov dx,socket_system2
add dx,[grosse_sochette]
call ferme_socket
open_socket socket_system2

ecoute2 ecb3 recu_data3 header_ecoute3 2 socket_system
POPALL

;call de_init_ipx
;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h


ret
ertteertrerterteert: ;found a network

;mov edx,offset connect
;mov ah,9
;int 21h
;mov bx,15 ;blanc sans clignotant.
;call last_color

mov [master],1 ;pas master...
mov [tecte2],0

;r‚cupere l'adresse du master...
;adresse_master db 00,00,00,00,00,040h,05h,2ah,3dh,8fh,40h,02h
;        ; 18source
; db 4 dup (0) ;netadd         ;REMPLIS AUTOMATIQUEMENT QUAND ON RECOIT
; db 6 dup (0) ;nodeadd        ;contient l'adresse d'ou provient le message.
; dw 0           ;sockette...
;header_ecoute  dw 0   ; 0 checksum

mov ax,ds
mov es,ax
mov esi,offset header_ecoute3+18
mov edi,offset adresse_master
mov ecx,10/2
rep movsW
mov ax,socket_jeu
add ax,[grosse_sochette]
stosw


;mov esi,offset adresse_master
;call aff_adresse

;commence son boulo...

;****************** ENVOiS L'ACCUS‚ DE R‚CEPTiON... *************************
PUSHALL
mov ebp,offset donnee3
mov esi,offset adresse_master
mov word ptr [adresse_master+10],socket_system2
push ax
mov ax,[grosse_sochette]
add word ptr [adresse_master+10],ax
pop ax

mov byte ptr [donnee3],77  ;accus‚ de reception...
envois2 ecb4 header_envois4 1 socket_system2
mov word ptr [adresse_master+10],socket_jeu
push ax
mov ax,[grosse_sochette]
add word ptr [adresse_master+10],ax
pop ax

popall
;*********************************************************************

ecoute2 ecb1 packed_data header_ecoute taille_bloc_the_total socket_jeu

        cmp [assez_de_memoire],1
        jne eretterertrteertterrteertterrteerertrteertyrtrtyyutr
mov edx,offset no_dyna2
mov ah,9
int 21h
mov bx,15 ;blanc sans clignotant.
call last_color
eretterertrteertterrteertterrteerertrteertyrtrtyyutr:
pop cx
POPALL
ret
ertteertrerterteert2: ;esc pressed
pop cx
POPALL
ret
restes_tranquilles:

;        mov ax,3h
;        int 10h
mov [lost_conney],1
        mov ax,3h
        int 10h

mov edx,offset busy ;affiche ke connection refusee
mov ah,9
int 21h
        mov bx,1000000000000100B ;indique clignotement
        call last_color

cmp byte ptr [recu_data3+1],11 ;car trop de connectes.
jne restes_tranquillesreerterert
mov edx,offset busy2
mov ah,9
int 21h
restes_tranquillesreerterert:

cmp byte ptr [recu_data3+1],128 ;car trop de connectes.
jb restes_tranquillesreerterertey
mov edx,offset version2
mov ah,9
int 21h
mov al,version_du_jeu ; EQU 10010111B
and al,127
shr al,4
mov dl,'0'
add dl,al
mov ah,2
int 21h
mov dl,'.'
mov ah,2
int 21h
mov al,version_du_jeu ; EQU 10010111B
and al,01111B
mov dl,'0'
add dl,al
mov ah,2
int 21h
mov edx,offset version2B
mov ah,9
int 21h
mov al,byte ptr [recu_data3+1]
and al,127
shr al,4
mov dl,'0'
add dl,al
mov ah,2
int 21h
mov dl,'.'
mov ah,2
int 21h
mov al,byte ptr [recu_data3+1]
and al,01111B
mov dl,'0'
add dl,al
mov ah,2
int 21h
mov dl,' '
mov ah,2
int 21h
mov dl,'!'
mov ah,2
int 21h
mov dl,13
mov ah,2
int 21h
mov dl,10
mov ah,2
int 21h

restes_tranquillesreerterertey:

mov dl,''
mov ah,2
int 21h

pop cx
popall
jmp busy_ou
dyna_net ENDP

master_net proc near

cmp [ipx_],0 ;si pas ipx load‚..
jne bon_nu
ret
bon_nu:

pushall

cmp byte ptr [ecb3+8],0
jne  reterrterteertteertrerterteert

cmp byte ptr [recu_data3],99 ;killage !!!!  par un nouveau connect‚
je  killage

cmp byte ptr [recu_data3],98 ;demande d'information :)
je  donne_information

;cmp byte ptr [recu_data3],128 ;demande de connection ???
;jb  reterrterteertteertrerterteert ;si v

;******* on a recu une demande de connection... (enfin je crois...) ********
mov al,byte ptr [recu_data3]
mov [invite_recu],al

connection:
;****************** on r‚cupere l'adresse du joyeux nouveau connect‚ *******

;liste_adresse   db nb_max_ordy*16 dup (0)
;;adresse des autres ordinateurs connect‚s... 10 premiers octets...
;nb_ordy_connected dd 0
;                db 00,00,00,00,00,0c0h,0a8h,40h,06h,03h,40h,02h ; ordy num‚ro 1

mov eax,[nb_ordy_connected]  ;dd 0 ;*16 en fait.

mov [save_banke],-1

; --- regarde si on n'a pas deja recup l'adresse ---
; peut arriver ke le slave ait envoy‚ deja un autre packet avant k'il ait
; recu de r‚ponse du pr‚c‚dent...
pushall
mov ax,ds
mov es,ax
mov esi,offset header_ecoute3+18
mov edi,offset liste_adresse
mov ecx,8 ;[nb_ordy_connected]
or ecx,ecx
jz careoule
zerrzezererzzerzerzerzerezr:
push ecx
mov ecx,10/2
rep cmpsw
jne pas_dans_la_banque

;cmp dword ptr [edi+2],'eerf' ;signifie, a d‚ja ‚t‚ dans la banque. mais pas
;                           ;dans le jeu actuel.
;je pas_dans_la_banque      ;donc: on attend...

cmp dword ptr [edi+2],'daed' ;deja dans la banque.. mais mort...
jne pas_dans_la_banque1       ;donc on peut le reprendre...
push edi
sub edi,10;
mov [save_banke],edi   ;sauvegarde la position k'il a dans la banque.
pop edi
                       ;cas particulier... pour reprendre cette position
                       ;indispencable car si 2 pc avaient reboot‚ ils s'
                       ;‚echangeraient leurs places et leurs commandes !!!
jmp pas_dans_la_banque
pas_dans_la_banque1:

;cmp byte ptr [ordre],'S' ;si on est dans le menu. on refuse k'il se ramene
;je pas_dans_la_banque    ;directement dans le jeu.
;mov [kezax],1            ;mais on le prend kan meme..
;jmp pas_dans_la_banque
;pas_dans_la_banque2:
  pop ecx
  popall
  jmp deja_dans_la_banque
pas_dans_la_banque:
;sauf si il est Dead !!!!

pop ecx
sub esi,10
add edi,6
dec ecx
jnz zerrzezererzzerzerzerzerezr
careoule:
popall

mov [kezax],0

cmp byte ptr [ordre],'S' ;si menu: fait regarder
je ertetterertter
mov [kezax],1
ertetterertter:

;------------ regarde si ya pas deja trop de cpu connect‚...
cmp [nb_ordy_connected],7 ;max 7 + master
jne cbon_

mov ebp,offset donnee3
mov esi,offset header_ecoute3+18 ;renvois a l'envoyer.. mais en sockette2
mov byte ptr [donnee3],76  ;refus. Cat‚gorique.
mov byte ptr [donnee3+1],11  ;raison trop de connectes.
mov word ptr [esi+10],socket_system2

push ax
mov ax,[grosse_sochette]
add word ptr [esi+10],ax
pop ax

envois2 ecb4 header_envois4 2 socket_system2
  jmp trop_de_becanes_deja

cbon_:
;------------ regarde si ca serait pas une mauvaise version...
cmp [invite_recu],version_du_jeu
je sisiscuncommemoio

mov ebp,offset donnee3
mov esi,offset header_ecoute3+18 ;renvois a l'envoyer.. mais en sockette2
mov byte ptr [donnee3],76  ;refus. Cat‚gorique.
mov byte ptr [donnee3+1],version_du_jeu  ;version du jeu
mov word ptr [esi+10],socket_system2

push ax
mov ax,[grosse_sochette]
add word ptr [esi+10],ax
pop ax



envois2 ecb4 header_envois4 2 socket_system2
  jmp trop_de_becanes_deja

sisiscuncommemoio:

inc [nb_ordy_connected]

bruit 1 40 fx

;add eax,eax
;lea edi,[liste_adresse+eax*8]
;recherche la premiere place libre dans la liste_d'adresse...

cmp dword ptr [save_banke],-1
je jamais_vu
;sub edi,10
;mov [save_banke],edi   ;sauvegarde la position k'il a dans la banque.
mov edi,[save_banke]    ;cas de retours d'un breubie galeuse...
jmp highlander
jamais_vu:

lea edi,liste_adresse-16
erertertertertertert:
add edi,16
cmp dword ptr [edi+12],'koko'
je erertertertertertert
highlander:
;-----

;------------

push edi
mov ax,ds
mov es,ax
mov esi,offset header_ecoute3+18
mov ecx,10/2
rep movsW
mov ax,socket_jeu
;push ax
add ax,[grosse_sochette]
;add word ptr [adresse_master+10],ax
;pop ax

stosw
;12 premiers octets: adresse, puis ACTIVIt‚ 'okok' ca roule
;                                           'dead' plus de r‚ponse...

mov eax,'koko'
stosd
pop esi

mov ebp,offset donnee3
mov esi,offset header_ecoute3+18 ;renvois a l'envoyer.. mais en sockette2
mov byte ptr [donnee3],55  ;acceptation...

cmp [kezax],1
jne reertertertertter
mov byte ptr [donnee3],56  ;acceptation... speciale kezax
reertertertertter:

mov word ptr [esi+10],socket_system2

push ax
mov ax,[grosse_sochette]
add word ptr [esi+10],ax
pop ax


envois2 ecb4 header_envois4 1 socket_system2

; /-*0*-\ on doit attendre l'accus‚ de reception pour commencer...
; |o   o|   accus‚ du SLAVE...
ecoute2 ecb3 recu_data3 header_ecoute3 2 socket_system2
;envois2 ecb4 header_envois4 1 socket_system2

xor ecx,ecx
reterrterteertteertrerterteert4:


;;--- gros probleme ??? jamais d'accuse de reception
  incrementation_ecx_vbl
  cmp ecx,max_lost_master2
  jne gdfffffffffffffffffffffffffffopp
;POPALL
;
        mov ax,3h
        int 10h
mov edx,offset test1
mov ah,9
int 21h
        mov bl,0100B ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color

mov edx,offset test2
mov ah,9
int 21h

mov dl,''
mov ah,2
int 21h

;call de_init_ipx

       mov al,2
       mov ah,4ch                    ; AH=4Ch - Exit To DOS
       int 21h                         ; DOS INT 21h
gdfffffffffffffffffffffffffffopp:
;;--------------------------------------------------------------

cmp byte ptr [ecb3+8],0
jne  reterrterteertteertrerterteert4
cmp byte ptr [recu_data3],77 ;accus‚ de reception ???
jne  reterrterteertteertrerterteert4

deja_dans_la_banque:
trop_de_becanes_deja:
ecoute2 ecb3 recu_data3 header_ecoute3 2 socket_system

reterrterteertteertrerterteert:
POPALL
ret
probleme:
sagouin reception
POPALL
ret
donne_information:

mov ebp,offset donnee98
mov esi,offset header_ecoute3+18 ;renvois a l'envoyer.. mais en sockette2
;mov byte ptr [donnee98],'!'  ;refus. Cat‚gorique.



pushall
;--- marke le numero de sous-reso
mov eax,[nombre_de_dyna]
add al,'0'
mov donnee98+24,al

mov ax,[grosse_sochette]
shr ax,2+8

add al,'0'

mov donnee98+1,al
mov donnee98,'#'

;ordre2         db ?         ;ordre 2...
mov eax,dword ptr [game_]

cmp action_replay,2
jne kkhkkhkhjjhjhzeezzerzrezre
mov eax,dword ptr [demo_]
kkhkkhkhjjhjhzeezzerzrezre:

cmp on_les_dans_le_menu,1
jne kkhkkhkhjjhjh
mov eax,dword ptr [menu_]
kkhkkhkhjjhjh:
mov dword ptr [donnee98+39],eax

;-- recopie les noms des joueurs ---

lea edi,donnee98+79-32
xor ebx,ebx
push ds
pop es
terertcharmant:
mov esi,offset nick_t
add esi,[control_joueur+ebx]
;lodsd
movsd

;*** transformation lettres 0-9 ! . vers asci...
cmp byte ptr es:[edi-2],'z'
jna nooOooOooo_o
cmp byte ptr es:[edi-2],'z'+13
ja nooOooOooo_o
push eax ebx
xor ebx,ebx
mov bl,es:[edi-2]
sub bl,'z'+1
mov al,es:[transformateur_98+ebx]
mov byte ptr es:[edi-2],al
pop ebx eax
nooOooOooo_o:
;---
cmp byte ptr es:[edi-3],'z'
jna rnooOooOooo_o
cmp byte ptr es:[edi-3],'z'+13
ja rnooOooOooo_o
push eax ebx
xor ebx,ebx
mov bl,es:[edi-3]
sub bl,'z'+1
mov al,es:[transformateur_98+ebx]
mov byte ptr es:[edi-3],al
pop ebx eax
rnooOooOooo_o:
;---
cmp byte ptr es:[edi-4],'z'
jna tnooOooOooo_o
cmp byte ptr es:[edi-4],'z'+13
ja tnooOooOooo_o
push eax ebx
xor ebx,ebx
mov bl,es:[edi-4]
sub bl,'z'+1
mov al,es:[transformateur_98+ebx]
mov byte ptr es:[edi-4],al
pop ebx eax
tnooOooOooo_o:
;***

cmp dword ptr es:[edi-4],'‡upc'
jne ertrtrrtrtrttrtrt90
mov dword ptr es:[edi-4],' ---'
ertrtrrtrtrttrtrt90:
mov byte ptr es:[edi-1],' '
add ebx,4
cmp ebx,4*8
jne terertcharmant
popall
;---


mov word ptr [esi+10],socket_system2

;push ax
;mov ax,[grosse_sochette]
;add word ptr [esi+10],ax
;pop ax

envois98 ecb4 header_envois4 80 socket_system2
  jmp trop_de_becanes_deja

;----- killage du master par un slave !
killage:

cmp [jesus_mode],1   ;killage !!!!  par un nouveau connect‚
                     ;sauf si satan a ‚t‚ invoqu‚...
                     ;fait un simple demande de connection
je connection

popall
        mov ax,3h
        int 10h
mov edx,offset kill
mov ah,9
int 21h

        mov bl,0100B ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color
jmp busy_ou
master_net endp

;donnee dw 20,20,277,277,150,200,250,280  ;x du dynablaster
;       dw 9,170,9,170,78,98,98,10 ;y du dynablaster
;       dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna
;nombre_de_dyna   dd nbd ;en tout..
;briques dw 1+19*13*2 dup (0)  ;nombre de brique, source de la brique, destination
;                              ;dans buffer video
;bombes  dw 1+19*13*2 dup (0)  ; pareil pour les bombes & explosion & bonus

compact proc near
pushall
mov ax,ds
mov es,ax
;xor ecx,ecx
;mov cx,[briques]
;mov esi,offset briques
;lea edi,[esi+ecx*2+2]
;mov cx,[bombes]
;
;or ecx,ecx
;jz erzertrteert2
;
;inc ecx
;rep movsw
;erzertrteert2:
mov esi,offset donnee4
mov edi,offset packed_data

;donnee dw 20,20,277,277,150,200,250,280  ;x du dynablaster
;       dw 9,170,9,170,78,98,98,10 ;y du dynablaster
;       dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna
;nombre_de_dyna   dd nbd ;en tout..
mov ecx,offset briques
sub ecx,offset donnee4
rep movsb

cmp byte ptr [ordre2],'' ;uniqUEMENT si on est dans le jeu.
jne ertterterertrteert
;------------------------ packet special pendant le jeu -------------
xor ecx,ecx
mov cx,[briques]
mov esi,offset briques
rep movsd
movsw
xor ecx,ecx
mov cx,[bombes]
mov esi,offset bombes
rep movsd
movsw
jmp finito
;-------------------------------------------------------------------
ertterterertrteert:

cmp byte ptr [ordre2],'Z' ;uniqUEMENT si on est dans m‚daille.
jne ertterterertrteertOOO
;add edi,32 ;pour les 8*4 octets des noms des 8 joueurs...
mov ecx,8
rep movsd
movsb ;clignotement...
jmp finito
ertterterertrteertOOO:

finito:
sub edi,offset packed_data

;cmp edi,125
;je e89rertert
mov [last_packet_size],edi
;e89rertert:

cmp edi,[max_packet]
jb retretertertert

        mov ax,3h
        int 10h

mov eax,edi
call affsigne

mov eax,[max_packet]
call affsigne

lea edx,erreur3
mov ah,9
int 21h

popall
        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h


retretertertert:
;max_packet dd ?

popall
ret
endp

decompact proc near
pushall
mov ax,ds
mov es,ax
;xor ecx,ecx
;mov cx,[briques]
;lea esi,[briques+ecx*2+2]
;mov edi,offset bombes
;mov cx,[esi]
;or ecx,ecx
;jz erzertrteert
;inc ecx
;rep movsw
;erzertrteert:

;mov edi,offset donnee
;mov esi,offset packed_data

mov edi,offset donnee4
mov esi,offset packed_data

mov ecx,offset briques
sub ecx,offset donnee4
rep movsb

cmp byte ptr [ordre2],'' ;uniqUEMENT si on est dans le jeu.
jne ertterterertrteertert
;------------------------ packet special pendant le jeu -------------
xor ecx,ecx
mov cx,word ptr [esi]
mov edi,offset briques
rep movsd
movsw
;xor ecx,ecx
mov cx,word ptr [esi]
mov edi,offset bombes
rep movsd
movsw
ertterterertrteertert:
;-----------------------------------------------------------------

cmp byte ptr [ordre2],'Z' ;uniqUEMENT si on est dans m‚daille.
jne ertterterertrteertOOOT
;add edi,32 ;pour les 8*4 octets des noms des 8 joueurs...
;jmp finito
mov ecx,8
mov edi,offset briques
rep movsd
movsb ;clignotement
ertterterertrteertOOOT:


popall
ret
endp

zget_information proc near
pushall

cmp [ipx_],0 ;si pas ipx load‚..
jne bon_nu2e
popall
ret
bon_nu2e:

lea edx,setup_x
mov ah,09h
int 21h

ecoute98 ecb3 recu_data header_ecoute3 80 socket_system2

mov [grosse_sochette],0
okeeeeeeeeeeeeeeeeeeeeeeeeeeey:

;mov cx,25
;toerzertrteertertert1:
;push cx

;******** ENVOIS A TOUS UNE DEMANDE DE CONNECTION *******
mov ebp,offset donnee3
mov esi,offset toutes_adresse
mov word ptr [toutes_adresse+10],socket_system

push ax
mov ax,[grosse_sochette]
add word ptr [toutes_adresse+10],ax
pop ax

mov byte ptr [donnee3],98  ;demande info
envois2 ecb4 header_envois4 1 socket_system

call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3
call vbl3

cmp byte ptr [ecb3+8],0
jne  iterertterertertertteertrerterteert

mov [recu_data+80],'$'
lea edx,recu_data
mov ah,9
int 21h

        mov bh,00000000B ;indique clignotement
        mov bl,2 ;5 ;rouge


cmp byte ptr [recu_data+39],'g'
jne tejrejljktrjlkmerjklmerljrklmjeljkjlmet
        mov bl,12 ;orange
tejrejljktrjlkmerjklmerljrklmjeljkjlmet:

cmp recu_data+24,'8'
jne ejrejljktrjlkmerjklmerljrklmjeljkjlmet
        mov bl,4 ;rouge
ejrejljktrjlkmerjklmerljrklmjeljkjlmet:

cmp byte ptr [recu_data+39],'d'
jne tejrejljktrjlkmerjklmerljrklmjeljkjlmet2
        mov bl,2 ;vert
tejrejljktrjlkmerjklmerljrklmjeljkjlmet2:


        call last_color


ecoute98 ecb3 recu_data header_ecoute3 80 socket_system2

jmp tyttytytytytyttyrt
iterertterertertertteertrerterteert:
xor ax,ax
mov al,byte ptr [grosse_sochette+1]
shr ax,2
add al,'0'
mov [no_server_+1],al
lea edx,no_server_
mov ah,9
int 21h
tyttytytytytyttyrt:


;pop cx
;dec cx
;jnz toerzertrteertertert1

add [grosse_sochette],(4*256)
cmp [grosse_sochette],(4*256)*10
jne okeeeeeeeeeeeeeeeeeeeeeeeeeeey


mov [grosse_sochette],0
        call de_init_ipx

lea edx,select_server_
mov ah,9
int 21h

;        mov bl,4 ;bleu ciel
;        mov bh,10000000B ;indique clignotement
;        call last_color

quitte_babyrerer:

;               db '7 (right)       '  ;71
;               db '8 (right)       '  ;72
;               db '9 (right)       '
;               db '- (right)       '
;               db '4 (right)       '  ;75
;               db '5 (right)       '
;               db '6 (right)       '  ;77
;               db '+ (right)       '  ;
;               db '1 (right)       '  ;79
;               db '2 (right)       '  ;80
;               db '3 (right)       '
;               db '0/INSER         '  ;82

touches_pavnum 82 0
touches_pavnum 79 1
touches_pavnum 80 2
touches_pavnum 81 3
touches_pavnum 75 4
touches_pavnum 76 5
touches_pavnum 77 6
touches_pavnum 71 7
touches_pavnum 72 8
touches_pavnum 73 9

cmp [last_sucker],2
jb nonononononezrzer
cmp [last_sucker],10
ja nonononononezrzer
xor ax,ax
mov al,[last_sucker]
dec al
directos_allegro:
shl ax,2+8
mov [grosse_sochette],ax
jmp continue_coco
nonononononezrzer:

cmp [last_sucker],11
jne nonononononezrzereer
mov [grosse_sochette],0
jmp continue_coco
nonononononezrzereer:

;               db '1 (left)        '  ;2
;               db '2 (left)        '  ;3
;               db '3 (left)        '  ;4
;               db '4 (left)        '  ;5
;               db '5 (left)        '  ;6
;               db '6 (left)        '  ;7
;               db '7 (left)        '  ;8
;               db '8 (left)        '  ;9
;               db '9 (left)        '  ;10
;               db '0 (left)        '  ;11


cmp clavier+1,1
jne ecassos_baby
popall
        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h
ecassos_baby:
jmp quitte_babyrerer
continue_coco:

mov dl,10
mov ah,2
int 21h
mov dl,13
mov ah,2
int 21h

open_socket socket_jeu
open_socket socket_system
open_socket socket_system2

mov word ptr [notreadresse+10],socket_jeu
mov word ptr [toutes_adresse+10],socket_jeu

push ax
mov ax,[grosse_sochette]
add word ptr [notreadresse+10],ax
add word ptr [toutes_adresse+10],ax
pop ax

popall

ret
endp

;mov bx,01h
;mov dx,socket_system2
;add dx,[grosse_sochette]
;call ferme_socket
;int 07ah

ferme_socket proc near

;INT 7A U - Novell NetWare - IPX Driver - internal - TERMINATE SOCKETS
;        BX = 000Eh

pushall

;!
;push eax
;mov eax,edx
;call num
;pop eax
;!

call clear_call_int
mov [call_int+10h],01h
mov [call_int+14h],edx
;call_int dd 0 ;           00h     4       EDI
;dd 0 ;           04h     4       ESI
;dd 0 ;           08h     4       EBP
;dd 0 ;           0ch     4       reserved, ignored
;dd 0 ;           10h     4       EBX
;dd 0 ;           14h     4       EDX
;dd 0 ;           18h     4       ECX
;dd 0 ;           1ch     4       EAX
;dw 0 ;           20h     2       CPU status flags
;dw 0 ;           22h     2       ES
;dw 0 ;           24h     2       DS
;dw 0 ;           26h     2       FS
;dw 0 ;           28h     2       GS
;dw 0 ;           2ah     2       IP
;dw 0 ;           2ch     2       CS
;dw 0 ;           2eh     2       SP
;dw 0 ;           30h     2       SS

;  AX     = 0300h
;  BL     = interrupt number
;  BH     = must be 0
;  CX     = number of words to copy from the protected mode stack to the real
;           mode stack
;  ES:EDI = selector:offset of real mode register data structure in the
;           following format:
mov ax,ds
mov es,ax
mov edi,offset call_int
xor cx,cx
mov bh,0
mov bl,07ah
mov ax,300h
int 31h
;jnc kkljlkljkljkljkljk
;
;mov ax,789
;caLl affsigne
;kkljlkljkljkljkljk:

;mov eax,[call_int+1ch]
;and eax,0FFFFh
;call affsigne


popall
ret
endp

