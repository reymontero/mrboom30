
envois3 MACRO ecb2,header_envois,sook
                 ;entree ESI: source sur adresse envois
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

;mov ax,[esi+10] ;prend la socket a partie de l'adresse que l'on a donn‚.
;                ;adresse ou on envois

mov esi,offset ecb2

;mov ax,socket_jeu ;[socket]
mov word ptr [esi+10],sook

push ax
mov ax,[grosse_sochette]
add word ptr [esi+10],ax
pop ax


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
push word ptr [last_packet_size]
pop word ptr [esi+46]
;call dword ptr [fcall]
;int 07ah

;mov ebx,9                    ;valeur de ebx...
;mov esi,offset notreadresse  ;sera comvertit en ES:SI en real...
call special_essi


;     db  0   ;    9       completion code                     BYTE

;movzx ax,byte ptr [ecb2+9]
;call affsigne

POPALL
endM


envois2 MACRO ecb2,header_envois,packet_data_size,sook
                 ;entree ESI: source sur adresse envois
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

;mov ax,[esi+10] ;prend la socket a partie de l'adresse que l'on a donn‚.
;                ;adresse ou on envois

mov esi,offset ecb2

;mov ax,socket_jeu ;[socket]
mov word ptr [esi+10],sook

push ax
mov ax,[grosse_sochette]
add word ptr [esi+10],ax
pop ax


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

POPALL
endM



envois98 MACRO ecb2,header_envois,packet_data_size,sook
                 ;entree ESI: source sur adresse envois
                 ;       ebp: source sur ce qu'on envois. ;offset donnee
;pareil ke envois 2 deux mais sans grosse sauchette
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

;mov ax,[esi+10] ;prend la socket a partie de l'adresse que l'on a donn‚.
;                ;adresse ou on envois

mov esi,offset ecb2

;mov ax,socket_jeu ;[socket]
mov word ptr [esi+10],sook

;push ax
;mov ax,[grosse_sochette]
;add word ptr [esi+10],ax
;pop ax


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

POPALL
endM



ecoute2 MACRO ecb1,recu_data,header_ecoute,packet_data_size,sokky
local erreur_dans_ecoute
local erterrterte3
PUSHALL

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
mov word ptr [esi+10],sokky

push ax
mov ax,[grosse_sochette]
add word ptr [esi+10],ax
pop ax


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
erterrterte3:
POPALL
ENDM

ecoute98 MACRO ecb1,recu_data,header_ecoute,packet_data_size,sokky
local erreur_dans_ecoute
local erterrterte3
PUSHALL

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
mov word ptr [esi+10],sokky

;push ax
;mov ax,[grosse_sochette]
;add word ptr [esi+10],ax
;pop ax


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
erterrterte3:
POPALL
ENDM


get_all_infos2 MACRO
local retrtrtrtrtrtrteteOOO
local non_cancelle_juste_avant
local non_il_doit_pas_etre_ko
local teterertrteterrteterterterterterertterter
local rzrteertertert
local terzertrteertertert1
local trtyrtyrtyretertdgrfgdtrdfgdfgdfg
local treertertertertertert
local ok_ca_va_il_est_ok
local ROUUUND_ANd_ROUUUUNDtt
local NONONONONON2
PUSHALL
;------------- ;ordy local...
push ds
pop  es
mov esi,offset donnee2
mov edi,offset total_t
mov ecx,touches_size
rep movsb
;------------------
;edi est bien plac‚...

xor ecx,ecx

teterertrteterrteterterterterterertterter:
cmp ecx,8 ;nombre max d'ordy ;[nb_ordy_connected]
je rzrteertertert

PUSHALL

;*** RECUPERATION DES TOUCHES SUR CHACUN DES ORDY...

;liste_adresse   db nb_max_ordy*16 dup (0)
  PUSHALL
  shl ecx,4 ;ecx * 16
  lea ebp,packed_data
  lea esi,[liste_adresse+ecx]

  cmp dword ptr [esi+12],'koko'
  je ok_ca_va_il_est_ok
;---- il est OUT !!!! ---- deco ou perte de ligne pr‚c‚dant...------
;---- ou ya jamais eu d'ordinateur ici ---
  popall
  popall
  inc ecx
  jmp teterertrteterrteterterterterterertterter
;--------------------------------------------------------------------
ok_ca_va_il_est_ok:

;packets_jeu_envoyes dw 0
;packets_jeu_recus   dw 0
inc [packets_jeu_envoyes]

push eax
mov eax,[last_packet_size]
add [kb_packets_jeu_envoyes],eax
pop eax

envois3 ecb2 header_envois socket_jeu
;  si pour le jeu...
;  ou envois2 ecb2 header_envois taille_block_slave_menu socket_jeu
;  si pour menu
  POPALL
;  ecoute2 ecb1 recu_data header_ecoute touches_size socket_jeu

cmp [rien_recu],1
je non_cancelle_juste_avant

ecoute2 ecb1 recu_data header_ecoute touches_size socket_jeu

non_cancelle_juste_avant:
mov [rien_recu],0

;  xor ebx,ebx
   xor ecx,ecx  ; !

;erzertrteertertert:
;
;;recu_data     db '??????????????????????????????????????????????????????????????',10,13,'$'
;;cmp byte ptr [sortie2],1 ;F2
;;je rtyrtyrtyretertdgrfgd
;
;incrementation_ecx_vbl
;cmp ecx,max_lost
;je quitte_baby

  xor ax,ax
  terzertrteertertert1:

;---------------- detection d'un (nouveau) mort ------------

incrementation_ecx_vbl

cmp [kli_option],1
jne ROUUUND_ANd_ROUUUUNDtt
cmp ecx,max_lost_master
jb ROUUUND_ANd_ROUUUUNDtt
cmp byte ptr [clavier+1],1 ;sauf sil presse ESC
je ROUUUND_ANd_ROUUUUNDtt
dec ecx
ROUUUND_ANd_ROUUUUNDtt:

  cmp ecx,max_lost_master
  jb NONONONONON2
     push dx ax
     xor ax,ax
     mov   dx,3c8h
     out   dx,al
     mov   dx,3c9h
     mov al,cl
     and al,31
     out   dx,al
     xor ax,ax
     out   dx,al
     out   dx,al
     pop ax dx
;cmp byte ptr [clavier+88],0 ;F12
jmp non_il_doit_pas_etre_ko
NONONONONON2:


;-------------------------------------------------

  ;     /********************************************************\
;  cmp byte ptr [clavier+59],1 ;F1... donne la periode d'attente pour la comm
;                            ;avec un ordy...
  cmp [affiche_raster],0
  je treertertertertertert
  ;- raster vert -
  inc ax
  push dx ax
     mov   dx,3c8h
  push ax
  xor ax,ax
     out   dx,al
     mov   dx,3c9h
     out   dx,al
  pop ax
     out   dx,al
  xor ax,ax
     out   dx,al
  pop ax dx
  ;- raster vert -
  treertertertertertert:
  ;     \********************************************************/
;  cmp byte ptr [sortie2],1 ;F2
;  je trtyrtyrtyretertdgrfgdtrdfgdfgdfg
  cmp byte ptr [ecb1+8],0
  jne terzertrteertertert1
  call raster2
  trtyrtyrtyretertdgrfgdtrdfgdfgdfg:
  ;-------
  ;***
  POPALL
inc [packets_jeu_recus]
  pushall
  ;mov ax,gs
  ;mov es,ax
  push ds
  pop es
  ;recu_data     db '??????????????????????????????????????????????????????????????',10,13,'$'
  ;ecx: numero de l'ordy.. (0=premier non local..)
  mov esi,offset recu_data
  mov edi,offset total_t ;+32   ;;offset donnee2
  inc ecx
  shl ecx,6 ;*64
  add edi,ecx
  mov ecx,touches_size ;6*4+2
  rep movsb
  popall

;si le slave presse ESC, on le butte cash !
;cmp sortie_slave,0 ;cmp sortie,0 ;
cmp byte ptr [recu_data+8*7+1],1
jne retrtrtrtrtrtrteteOOO
pushall
  shl ecx,4 ;ecx * 16
  lea esi,[liste_adresse+ecx]
  mov dword ptr [esi+12],'daed'
  dec [nb_ordy_connected]  ;dd 0 ;*16 en fait.
popall
retrtrtrtrtrtrteteOOO:
;--------

inc ecx

jmp teterertrteterrteterterterterterertterter
;--- masscre d'un ordy !!!
non_il_doit_pas_etre_ko:

;--------N-7A----BX0006-----------------------
;INT 7A - Novell NetWare - IPX Driver - CANCEL EVENT
;        BX = 0006h
;        ES:SI -> Event Control Block (see BX=0003h)
;Return: AL = return code (see #2225)

popall
pushall
  shl ecx,4 ;ecx * 16
;  mov ebp,offset packed_data
  lea esi,[liste_adresse+ecx]
  mov dword ptr [esi+12],'daed'
popall
inc ecx

;ATTENTION pour eviter plantage a la fin:
; il ne faut pas remettre la socket en ecoute
; si elle a rien recu... (pas plus d'1 fois sinon...)
dec [nb_ordy_connected]  ;dd 0 ;*16 en fait.

mov [rien_recu],1

jmp teterertrteterrteterterterterterertterter
;---------------------
rzrteertertert:

POPALL
ENDM

get_all_infos3 MACRO
local non_il_doit_pas_etre_ko
local ROUUUND_ANd_ROUUUUNDttt
local teterertrteterrteterterterterterertterter
local rzrteertertert
local terzertrteertertert1
local trtyrtyrtyretertdgrfgdtrdfgdfgdfg
local treertertertertertert
local ok_ca_va_il_est_ok
local non_cancelle_juste_avant
local yretrtrtrtrtrtrteteOOO
PUSHALL
;------------- ;ordy local...
push ds
pop  es
mov esi,offset donnee2
mov edi,offset total_t
mov ecx,touches_size
rep movsb
;------------------
;edi est bien plac‚...

xor ecx,ecx

teterertrteterrteterterterterterertterter:
cmp ecx,8 ;nombre max d'ordy ;[nb_ordy_connected]
je rzrteertertert

PUSHALL

;*** RECUPERATION DES TOUCHES SUR CHACUN DES ORDY...

;liste_adresse   db nb_max_ordy*16 dup (0)
  PUSHALL
  shl ecx,4 ;ecx * 16
  lea ebp,ordre ; db 'M'texte1 ;envois du texte du menu
  lea esi,[liste_adresse+ecx]

  cmp dword ptr [esi+12],'koko'
  je ok_ca_va_il_est_ok
;---- il est OUT !!!! ---- deco ou perte de ligne pr‚c‚dant...------
;---- ou ya jamais eu d'ordinateur ici ---
  popall
  popall
  inc ecx
  jmp teterertrteterrteterterterterterertterter
;--------------------------------------------------------------------
ok_ca_va_il_est_ok:

envois2 ecb2 header_envois taille_block_slave_menu socket_jeu
;  si pour le jeu...
;  ou envois2 ecb2 header_envois taille_block_slave_menu socket_jeu
;  si pour menu
  POPALL
;  ecoute2 ecb1 recu_data header_ecoute touches_size socket_jeu

cmp [rien_recu],1
je non_cancelle_juste_avant

ecoute2 ecb1 recu_data header_ecoute touches_size socket_jeu

non_cancelle_juste_avant:
mov [rien_recu],0


;  xor ebx,ebx
   xor ecx,ecx  ; !

;erzertrteertertert:
;
;;recu_data     db '??????????????????????????????????????????????????????????????',10,13,'$'
;;cmp byte ptr [sortie2],1 ;F2
;;je rtyrtyrtyretertdgrfgd
;
;incrementation_ecx_vbl
;cmp ecx,max_lost
;je quitte_baby

  xor ax,ax
  terzertrteertertert1:

;---------------- detection d'un (nouveau) mort ------------

incrementation_ecx_vbl

cmp [kli_option],1
jne ROUUUND_ANd_ROUUUUNDttt
cmp ecx,max_lost_master
jne ROUUUND_ANd_ROUUUUNDttt
cmp byte ptr [clavier+1],1 ;sauf sil presse ESC
je ROUUUND_ANd_ROUUUUNDttt
dec ecx
ROUUUND_ANd_ROUUUUNDttt:

  cmp ecx,max_lost_master
  ;je quitte_baby
  je non_il_doit_pas_etre_ko

NONONONONON2reteerer:

;-------------------------------------------------

;  ;     /********************************************************\
;  cmp byte ptr [clavier+59],1 ;F1... donne la periode d'attente pour la comm
;                            ;avec un ordy...
;  jne treertertertertertert
  cmp [affiche_raster],0
  je treertertertertertert

  ;- raster vert -
  inc ax
  push dx ax
     mov   dx,3c8h
  push ax
  xor ax,ax
     out   dx,al
     mov   dx,3c9h
     out   dx,al
  pop ax
     out   dx,al
  xor ax,ax
     out   dx,al
  pop ax dx
  ;- raster vert -
  treertertertertertert:
  ;     \********************************************************/
;  cmp byte ptr [sortie2],1 ;F2
;  je trtyrtyrtyretertdgrfgdtrdfgdfgdfg
  cmp byte ptr [ecb1+8],0
  jne terzertrteertertert1
  call raster2
  trtyrtyrtyretertdgrfgdtrdfgdfgdfg:
  ;-------
  ;***
  POPALL

  pushall
  ;mov ax,gs
  ;mov es,ax
  push ds
  pop es
  ;recu_data     db '??????????????????????????????????????????????????????????????',10,13,'$'
  ;ecx: numero de l'ordy.. (0=premier non local..)
  mov esi,offset recu_data
  mov edi,offset total_t ;+32   ;;offset donnee2
  inc ecx
  shl ecx,6 ;*64
  add edi,ecx
  mov ecx,touches_size
  rep movsb
  popall

;si le slave presse ESC, on le butte cash !
cmp byte ptr [recu_data+8*7+1],1
jne yretrtrtrtrtrtrteteOOO
pushall
  shl ecx,4 ;ecx * 16
  lea esi,[liste_adresse+ecx]
  mov dword ptr [esi+12],'daed'
dec [nb_ordy_connected]  ;dd 0 ;*16 en fait.
popall
yretrtrtrtrtrtrteteOOO:
;--------

inc ecx

jmp teterertrteterrteterterterterterertterter
;--- masscre d'un ordy !!!
non_il_doit_pas_etre_ko:
popall
pushall
  shl ecx,4 ;ecx * 16
;  mov ebp,offset packed_data
  lea esi,[liste_adresse+ecx]
  mov dword ptr [esi+12],'daed'
popall
inc ecx
;ATTENTION pour eviter plantage a la fin:
; il ne faut pas remettre la socket en ecoute
; si elle a rien recu... (pas plus d'1 fois sinon...)

dec [nb_ordy_connected]  ;dd 0 ;*16 en fait.
mov [rien_recu],1

jmp teterertrteterrteterterterterterertterter
;---------------------
rzrteertertert:

POPALL
ENDM


