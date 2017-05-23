num_voices equ 14

include ..\divers\couleur.inc

detect proc far
pushad

;------------decryptage du texte + detection joystick
PUSHA
;cmp [first_time2],1 ;seulement une fois au debut
;je iedeja_fait
;mov [first_time2],1
;xor bl,bl

mov edi,offset first_time2+1
xor cl,cl
xor bl,bl
irmerciaurevoir:
cmp dword ptr [edi],'ÿ“ã'
je iedeja_fait
;----------
mov al,[edi] ;2
sub al,cl ;1
add cl,15 ;1
sub al,bl      ;2
mov bl,al      ;2
;-----------
mov [edi],al
inc edi
jmp irmerciaurevoir
iedeja_fait:
popA
;-----------------------------------------------------

call config_detect ;serra different si on a un bp <> 0 .. dans ce numero

call GET_GUs_MEMORY

cmp [gus_or_sb],1
jne zerertertterter2
mov eax,[MEMOIRE_GUS]
SHR EAX,10
inc ax
;--- si on se retrouve avec 0KB c ke on a donne un faux truc dans mrboom.cfg
cmp ax,0
jne retererttererttyrtyrytrtyrty
mov [gus_or_sb],0
mov ah,9
lea edx,no_gus2
int 21h
        mov bl,0100B ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color


jmp zerertertterter2
retererttererttyrtyrytrtyrty:
;-----------------------------------
or bp,bp
jz retrtedfcvfgdfgdfgdfgdfg2
push ax
mov ah,9
lea edx,gusmess4
int 21h
pop ax
retrtedfcvfgdfgdfgdfgdfg2:
;-----------------------------------
call affsigne
mov dl,'K'
mov ah,2
int 21h
mov dl,'B'
mov ah,2
int 21h
mov dl,')'
mov ah,2
int 21h
mov dl,13
mov ah,2
int 21h
mov dl,10
mov ah,2
int 21h

call gus_init

zerertertterter2:

;call detect_joystick

cmp [gus_or_sb],1
je zerertertterter
mov ah,9
lea edx,no_gus
int 21h
popad
ret
zerertertterter:


popad
ret
;cmp bp,1 ;si on a trouve une gus on regarde combien elle a en RAM...
;jne retertertr
;cmp es:[first_time],0
;jne retertertr
;call GET_GUs_MEMORY
;mov es:[first_time],1
;
;call light_show ;init speciale light show
;
;push bp
;xor bp,bp
;call gus_Init
;pop bp
;
;retertertr:
;
;popad
;ret
detect endp


;mov di,02ch
;mov ax,es:[di]
;mov ds,ax
;mov si,0
;mov ax,rmd_data
;mov es,ax
;mov di,offset header_mod ;ENVIRONMENT
;;important: on efface les ' '
;mov cx,256
;packkkk:
;lodsb
;cmp al,' '
;je erttertt
;stosb
;erttertt:


config_detect proc near


jmp CONFIg_DU_FICHIER

;mov ax,0002
push ds
mov ax,word ptr es:[02ch]
mov es,ax
xor esi,esi
mov edi,offset header_mod
mov ecx,256
errteetrrrrrrrrrrrrr:
mov al,byte ptr es:[esi]
cmp al,97
jb nonezezer
cmp al,122
ja nonezezer
sub al,32 ;met majuscules...
nonezezer:
mov byte ptr [edi],al
inc edi
inc esi
dec ecx
jnz errteetrrrrrrrrrrrrr
pop ds

;mov edi,offset header_mod ;ENVIRONMENT
;mov cx,256
;ererertrte:
;mov dl,[edi]
;mov ah,2
;int 21h
;inc edi
;loop ererertrte
;--------------

mov edi,offset header_mod ;ENVIRONMENT
mov cx,256
equilibre:
cmp byte ptr [edi],'U'
jne pas_cette_fois_mon_petit
cmp byte ptr [edi+1],'L'
jne pas_cette_fois_mon_petit
cmp byte ptr [edi+2],'T'
jne pas_cette_fois_mon_petit
cmp byte ptr [edi+3],'R'
jne pas_cette_fois_mon_petit
cmp byte ptr [edi+4],'A'
jne pas_cette_fois_mon_petit
cmp byte ptr [edi+5],'S'
jne pas_cette_fois_mon_petit
cmp byte ptr [edi+6],'N'
jne pas_cette_fois_mon_petit
cmp byte ptr [edi+7],'D'
jne pas_cette_fois_mon_petit
cmp byte ptr [edi+8],'='
jne pas_cette_fois_mon_petit
cmp byte ptr [edi+9],'2'
jne pas_cette_fois_mon_petit

;............................regarde le port...

cmp byte ptr [edi+10],'1'
jne aphonia
mov [gus_base],210h
mov ax,210
mov edx,offset gusmess3
call aff_port
jmp apiary
aphonia:
cmp byte ptr [edi+10],'2'
jne aphonia2
mov [gus_base],220h
mov ax,220
mov edx,offset gusmess3
call aff_port
jmp apiary
aphonia2:
cmp byte ptr [edi+10],'3'
jne aphonia3
mov [gus_base],230h
mov ax,230
mov edx,offset gusmess3
call aff_port
jmp apiary
aphonia3:
cmp byte ptr [edi+10],'4'
jne aphonia4
mov ax,240
mov edx,offset gusmess3
call aff_port
mov [gus_base],240h
jmp apiary
aphonia4:
cmp byte ptr [edi+10],'5'
jne aphonia5
mov ax,250
mov edx,offset gusmess3
call aff_port
mov [gus_base],250h
jmp apiary
aphonia5:
cmp byte ptr [edi+10],'6'
jne aphonia6
mov ax,260
mov edx,offset gusmess3
call aff_port
mov [gus_base],260h
jmp apiary
aphonia6:
cmp byte ptr [edi+10],'7'
jne aphonia7
mov ax,270
mov edx,offset gusmess3
call aff_port
mov [gus_base],270h
jmp apiary
aphonia7:
cmp byte ptr [edi+10],'8'
jne aphonia8
mov ax,280
mov edx,offset gusmess3
call aff_port
mov [gus_base],280h
jmp apiary
aphonia8:
JMP pas_cette_fois_mon_petit
apiary:
xor bp,bp ;pour faire comme si on avait pas eu de truc force par le cfg..
apiaryertterertter:
  mov di,[gus_base]
  mov ax,di
  add ax,6
  mov word ptr [gus_status],ax
  mov ax,di
  add ax,102h
  mov word ptr [gus_voice],ax
  mov ax,di
  add ax,103h
  mov word ptr [gus_command],ax
  mov ax,di
  add ax,104h
  mov word ptr [gus_Datalo],ax
  mov ax,di
  add ax,105h
  mov word ptr [gus_Datahi],ax
  mov ax,di
  add ax,107h
  mov word ptr [gus_DramIO],ax

  mov [gus_or_sb],1

ret

pas_cette_fois_mon_petit:
inc edi
dec cx
jnz equilibre

CONFIg_DU_FICHIER:
or bp,bp
jz retrtertertertertertertgfooooooo
;pas trouve, utilise le bp... si ya un bp bien sur
mov [gus_base],bp
jmp apiaryertterertter
retrtertertertertertertgfooooooo:

kosta:

ret
config_detect endp

aff_port proc near

;cmp bp,1 ;no banner mode !!!
;je zererertt

push ax
mov ah,09
int 21h
pop ax
call affsigne

mov dl,'h'
mov ah,2
int 21h
mov dl,','
mov ah,2
int 21h
mov dl,' '

mov ah,2
int 21h
;mov dl,10
;mov ah,2
;int 21h
;zererertt:
ret
aff_port endp

GET_GUs_MEMORY PROC NEAR

;teste si on a 512 KB dans la GUS
mov ebx,0 ;1024*256

sucre:
mov dx,[gus_command]
mov al,044h     ;pour specifier l'adresse High dans memoire de la GUS!!!
out dx,al
mov dx,[gus_datahi]
push ebx
shr ebx,16
mov al,bl
out dx,al       ;on place l'adresse high...
pop ebx

mov dx,[gus_command]
mov al,043h     ;pour specifier l'adresse LOW dans memoire de la GUS!!!
out dx,al
mov dx,[gus_datalo]
mov ax,bx
out dx,ax

mov dx,[gus_dramio]
mov al,'R'
out dx,al            ;ecris l'octet dans la GUS..

  call delay
  call delay
  call delay
  call delay
  call delay
  call delay

mov dx,[gus_dramio]

in al,dx             ;ecris l'octet dans la GUS..
cmp al,'R'
jne finicetest


add ebx,1024*256

cmp ebx,1024*256*4
jne sucre ;jne sucre
finicetest:

dec ebx
mov [MEMOIRE_GUS],ebx

ret
GET_GUs_MEMORY ENDP


delay proc near
  mov dx,300h
  in al,dx
  in al,dx
  in al,dx
  in al,dx
  in al,dx
  in al,dx
  in al,dx
  in al,dx
  ret
delay endp

gus_Init proc near ;entree bp=1 mode silencieux
pusha

cmp [gus_or_sb],1
jne ertzerertertterter2

;cmp bp,1
;je silencieux

  mov bx,word ptr [gus_Command]
  mov cx,word ptr [gus_datahi]
  mov dx,bx
  mov al,4ch                    ; Choisir le registre d'initialisation
  out dx,al
  mov dx,cx
  mov al,0                      ; ExÇcuter l'initialisation
  out dx,al
  call delay
  call delay
  mov dx,bx
  mov al,4ch
  out dx,al
  mov dx,cx
  mov al,1                      ; Terminer l'initialisation
  out dx,al
  call delay
  call delay
  mov dx,bx                     ; Reset du DMA Control Register
  mov al,41h
  out dx,al
  mov dx,cx
  mov al,0
  out dx,al
  mov dx,bx                     ; Reset du Timer Control Register
  mov al,45h
  out dx,al
  mov dx,cx
  mov al,0
  out dx,al
  mov dx,bx                     ; Reset du Sampling Control Register
  mov al,49h
  out dx,al
  mov dx,cx
  mov al,0
  out dx,al

  mov dx,bx                     ; Poser le nombre de voix
  mov al,0Eh
  out dx,al
  add dx,2
  mov al,Num_Voices
  or  al,0C0h
  out dx,al
  mov dx,word ptr [gus_status]  ;Vider Çventuellement les interrupts DMA
  in al,dx
  mov dx,bx
  mov al,41h
  out dx,al
  mov dx,cx
  in al,dx
  mov dx,bx                 ; Vider Çventuellement les interrupts de sampling
  mov al,49h
  out dx,al
  mov dx,cx
  in al,dx
  mov dx,bx                       ; Lire le registre d'Çtat de l'IRQ
  mov al,8Fh                      ; ==> Il n'y a plus d'interruptions
  out dx,al                       ;     non traitÇes
  mov dx,cx
  in al,dx
silencieux:
  push bx                         ; DÇsactive les voix dans la boucle
  push cx
  mov cx,0
@VoiceClearLoop:
  mov dx,word ptr [gus_Voice]    ;Choisir les voix
  mov al,cl
  out dx,al
  inc dx
  mov al,0                        ; Poser le mode Voice
  out dx,al

  add dx,2
  mov al,3                        ; Arràter les voix
  out dx,al
  sub dx,2                        ; Poser le volume sur 0

;cmp bp,1
;je erretert
  mov al,0dh
  out dx,al
  add dx,2
  mov al,3
  out dx,al
;erretert:
  inc cx
  cmp cx,32                     ; RÇpÇter pour toutes les voix
  jnz @VoiceClearLoop
  pop cx
  pop bx
;cmp bp,1
;je silencieux2

  mov dx,bx                     ; Traiter les interruptions
  mov al,41h                    ; Çventuelles
  out dx,al
  mov dx,cx
  in al,dx
  mov dx,bx
  mov al,49h
  out dx,al
  mov dx,cx
  in al,dx
  mov dx,bx
  mov al,8fh
  out dx,al
  mov dx,cx
  in al,dx
  mov dx,bx                       ; ExÇcuter un reset
  mov al,4ch
  out dx,al
  mov dx,cx                   ; Activer l'IRQ master GF1
  mov al,7
  out dx,al

ertzerertertterter2:
;silencieux2:
popa
  ret
gus_Init endp

LOAD_BONUS_SAMPLE PROC NEAR
;ECX: OFFSET
;! dans EaX NUMERO DU SAMPLE *4 !
;MOV eBP,32*4

push es ds di si edx ecx ebx eax

cmp [gus_or_sb],1
je cuneguskona

jmp kinderdelice
cuneguskona:

shl eax,2
mov ebp,eax ;!!!!

;header_IFF DB 78   DUP (?) ;on charge ici le header de l'IFF en cours de

;...ouverture fichier....

mov edx,offset iff_file_name
mov ah,03dh ;ouverture du fichier avec handle.
mov al,00h  ;ouverture du fichier pour lecture.
int 21h
jc erreur_file_macarena ;saute si carry=1
;dans ax:handle fichier

mov word ptr [handle_IFF_file],ax

;... deplacement a l'interieur du fichier IFF
mov word ptr bx,[handle_IFF_file]
mov ah,042h
mov al,00h              ;debut du fichier
mov dx,cx
shr ecx,16
;dans cx:dx deplacement a l'interieur du fichier
int 21h
jc erreur_file_macarena ;saute si carry=1

;...lecture du fichier...
mov word ptr bx,[handle_IFF_file]
mov ah,03fh
mov cx,78               ;pour charger header IFF
mov edx,offset header_IFF
int 21h
jc erreur_file_macarena ;saute si carry=1

mov  ebx,[MEMOIRE_GUS_UTILISEE]


mov [adresse_debut_sample_gus+ebp],ebx
mov [adresse_loop_sample_gus+ebp],ebx

mov esi,offset header_IFF
xor eax,eax
mov ax,word ptr [esi+52] ;longueur du sample
ROL AX,8

push eax ;taille du sample (1)
add  eax,ebx
mov [adresse_fin_sample_gus+ebp],eax

;push dx eax
;call affsigne
;mov dl,' '
;mov ah,2
;int 21h
;pop eax dx

mov [MEMOIRE_GUS_UTILISEE],eax

;cmp eax,es:[MEMOIRE_GUS];----------------------------test si assez de mem
;jb okyaassezdeplaceE
;mov bp,4  ;pas assez de memoire dans la GUS
;pop eax
;jmp kinderdelice
;okyaassezdeplaceE:
;;---------------------------------------------------------------

;..............par default on met sample non loopeur...

mov edi,ebp
shr edi,1 ;numero du sample *2

mov word ptr [longueur_loop_sample+edi],0

;mov ax,rmd_data
;mov es,ax

xor eax,eax
mov ax,word ptr [esi+60] ;REPEAT LENGHT
ROL AX,8

;call affsigne ;longueur loop

or  ax,ax
je pas_loopeur_encore

mov word ptr [longueur_loop_sample+edi],ax

;dans ax on a la longueur de la loop

xor ecx,ecx
mov cx,ax

xor eax,eax
mov ax,word ptr [esi+56] ;REPEAT
ROL AX,8
;call num

add [adresse_loop_sample_gus+ebp],eax

mov eax,[adresse_loop_sample_gus+ebp]

add eax,ecx   ;debut loop+longueur loop

mov [adresse_fin_sample_gus+ebp],eax

pas_loopeur_encore:
                           ;ebx: adresse dans la GUS
                           ;ecx: taille du sample

pop ecx ;taille du sample (1)

;********************************* RECOPIE FICHIER->DRAM

cmp ecx,taille_buffer_load ;1024 ;5000
jb mfini_juste

msinger_cest:
;.... remplis le buffer .........
push ecx
push ebx
mov ecx,taille_buffer_load ;1024 ;5000
mov word ptr bx,[handle_IFF_file]
mov edx,offset header_mod ;BUFFER_LOAD_GUS
mov ah,03fh
int 21h
pop ebx
mov ecx,taille_buffer_load ;1024 ;5000

;entree EBx: adresse dans la gravis (EBX est modifie par BUFFER_2GUS)
;       ecx: longueur du sample...

call BUFFER_2GUS
add ebx,taille_buffer_load ;1024 ;5000

pop  ecx
sub  ecx,taille_buffer_load ;1024 ;5000
cmp ecx,taille_buffer_load ;1024 ;5000
jnb msinger_cest
;.........fini precisement...
mfini_juste:
;.... remplis le buffer ......... ;dans ecx: ce k'il reste a remplir
cmp ecx,0
je mcfini
push ecx
push ebx
;mov ecx,5000
mov word ptr bx,[handle_IFF_file]
mov edx,offset header_mod ;BUFFER_LOAD_GUS
mov ah,03fh
int 21h
pop ebx
pop ecx

;entree EBx: adresse dans la gravis (EBX est modifie par BUFFER_2GUS)
;       ecx: longueur du sample...

call BUFFER_2GUS
mcfini:
;****************************************************************
;...fermeture fichier..
mov word ptr bx,[handle_IFF_file]
mov ah,03eh
int 21h
jc erreur_file_macarena ;saute si carry=1

;mov bp,0 ;succeded
xor bp,bp
jmp kinderdelice
erreur_file_macarena:
mov bp,2 ;error loading file.
jmp kinderdelice

kinderdelice:
pop eax ebx ecx edx si di ds es
ret
LOAD_BONUS_SAMPLE ENDP


BUFFER_2GUS PROC NEAR

;entree EBx: adresse dans la gravis
;       ecx: longueur du sample...
push ebx eax ecx edx ds
mov esi,offset header_mod ;BUFFER_LOAD_GUS


mov dx,[gus_command]
mov al,044h     ;pour specifier l'adresse High dans memoire de la GUS!!!
out dx,al
mov dx,[gus_datahi]
push ebx
shr ebx,16
mov al,bl
out dx,al       ;on place l'adresse high...
pop ebx

tencore_un_octet:

mov dx,[gus_command]
mov al,043h     ;pour specifier l'adresse LOW dans memoire de la GUS!!!
out dx,al
mov dx,[gus_datalo]
mov ax,bx
out dx,ax

mov dx,[gus_dramio]
lodsb
out dx,al            ;ecris l'octet dans la GUS..

inc ebx
or bx,bx
jnz terreererreer ;cas particulier:on doit changer de segment.

mov dx,[gus_command]
mov al,044h     ;pour specifier l'adresse High dans memoire de la GUS!!!
out dx,al
mov dx,[gus_datahi]
push ebx
shr ebx,16
mov al,bl
out dx,al       ;on place l'adresse high...
pop ebx

terreererreer:
dec cx
jnz tencore_un_octet

pop  ds edx ecx eax ebx
ret
BUFFER_2GUS ENDP


;mov bp,0

play_fx proc near

pushall

xor eax,eax
xor ecx,ecx
xor ebp,ebp
xor edx,edx


xor ebp,ebp
xor ebx,ebx
ice9606A:

cmp word ptr [blow_what+ebp],0
je riendenouveau
xor dx,dx
xor cx,cx
mov dl,byte ptr [blow_what+ebp]   ;32 ;numero du sample
mov cx,dx ;panning...

shr cx,4 ;dans CL panning...
shl dx,2
xor ax,ax
mov al,byte ptr [blow_what+1+ebp] ;30 ;numero de la note.

shl dx,2
and dx,011111111B
mov word ptr [blow_what+ebp],0

push ebp ebx
;shl bx,1
add bx,bx
mov bp,bx
call PLaY_BONUS_SAMPLE
pop ebx ebp
riendenouveau:

add ebp,2
inc ebx

cmp ebx,14
jne ice9606A

POPALL
ret 4
endp

PLAY_BONUS_SAMPLE2 PROC NEAR

tonaunegus:

;................ frequence/note
mov ebx,ebp ;numero de voix*2
shr ebx,1

push bx ax
mov al,[panning_GUS+eBx]
call balance
pop ax bx

mov bh,al

push bx dx
xor cx,cx
call FREQ_VOIX
pop dx bx

ret
PLAY_BONUS_SAMPLE2 ENDP

FREQ_VOIX PROC NEAR

;entree bl:numero de la voix...
;dans bh: ce kon doit utiliser pour piocher la frequence dans gusfreq
;         BRUT! tel k'il est dans les pattern format remdy.
;         (on va le multiplier par 4 ensuite...)
; CX: ce k'on ajoute a la frequence... (utile pour portamento...)

mov dx,[gus_voice]   ;choisis la voix concernee...
mov al,bl
out dx,al

mov dx,[gus_command] ;ontorle frequence.
mov al,1
out dx,al

shr bx,8
shl bx,2

and ebx,01111111111111111B
mov eax,[gusfreq+eBX]

add ax,cx
;---parre fous
jns rrereert
sub ax,cx
mov ax,10000
or cx,cx
jns rrereert
mov ax,50
rrereert:
;----------
mov dx,[gus_datalo]

mov [freq_joue_gus+ebp],ax

out dx,ax
ret

FREQ_VOIX ENDP

BALANcE_VOIX PROC NEAR

;entree bl:numero de la voix...
;entree: al:mode d'envois de la voix...

push ax

mov dx,[gus_voice]   ;choisis la voix concernee...
mov al,bl             ;numero de la voix concernee
out dx,al

mov dx,[gus_command] ;fonction controle des voix!
mov al,0
out dx,al

mov dx,[gus_datahi]

pop ax
out dx,al

push ax
call delay
pop  ax
;----------- double!!!
push ax

mov dx,[gus_voice]   ;choisis la voix concernee...
mov al,bl             ;numero de la voix concernee
out dx,al

mov dx,[gus_command] ;fonction controle des voix!
mov al,0
out dx,al

mov dx,[gus_datahi]

pop ax
out dx,al

ret
BALANcE_VOix eNdP


balance proc near

push ax bx dx
push ax

mov dx,[gus_voice] ;choisis vOIX!
mov al,bl
out dx,al
mov dx,[gus_command]
mov al,0ch
out dx,al
mov dx,[gus_datahi]
pop ax
out dx,al
pop dx bx ax

ret
balance ENDP

PLAY_BONUS_SAMPLE PROC NEAR

push dx ;(1)

;................ frequence/note
mov bx,bp ;numero de voix*2
shr bx,1
;dans bX (bl) numero de voix


push bx ax
mov al,cl ;[panning_GUS+eBx]
call balance
pop ax bx

mov bh,al

;DAns bh on a le numero de la nouvelle note a jouer...


push eax bx ;.........;met le volume a 0-------
push ax
xor eax,eax
;VOLUME_DUNE_VOIX
mov ax,bp ;VOIX*2
shr ax,1  ;voix
pop bx    ;AL=VOIX
mov ah,0 ;AH=volume... ;on met
;al=voix
;ah=63 volume
call volume_dune_voix
pop bx eax

push ax bx
;entree bl:numero de la voix...
;entree: al:mode d'envois de la voix...
mov bx,bp
shr bx,1
mov al,1
call BALANcE_VOix
pop  bx ax

;on sauvegarde la frequence (enfin ce k'on va rajouter pour obtenir la frequence
;(utile pour les effets...) (effet 0)

;ush ;bx
;shr bx,8
;mov es:[SAUVE_VISEUR_DANS_SBFREQ+BP],BX
;pop bx

;*********
;FREQ_VOIX:
;entree bl:numero de la voix...
;dans bh: ce kon doit utiliser pour piocher la frequence dans gusfreq
;         BRUT! tel k'il est dans les pattern format remdy.
;         (on va le multiplier par 4 ensuite...)
;cx: ce k'on ajoute a la freq (utile pour portamento)

;mov es:[portamento_gus+bp],0 ;pour effet portemento

push bx dx
xor cx,cx
call FREQ_VOIX
pop dx bx

;........................definit le sample en question....
;mov bx,es:[sample_joue_en_ce_moment+bp] ;+numero voix*2
;shl bx,1
;dans bx: numero du sample joue *2 ;!

;PUSH BX  ;(1) NUMERO SAMPLE JOUE *2
;
;;;**** ETTEINT D'ABORD LA VOIX
;push ax bx
;mov bx,bp
;shr bx,1
;mov al,1 ;mode etteint voix
;call BALANcE_VOIX
;pop bx ax
;;;****
;
;POP BX  ;(1) NUMERO SAMPLE JOUE *2

pop bx ;(1)       ;NUMERO SAMPLE JOUE *4

mov ax,bp
shr ax,1

push bx ;(2)
push bp ;(1)
mov bp,BX ;NUMERO SAMPLE JOUE *4

mov bl,al ;dans bl=numero de VOIX

;*********
;DEF_VOIX:
;entree bl:numero de la voix...
;eax: adresse du debut du sample dans la gus k'on veut jouer...
;edx: adresse de la fin du sample dans la gus k'on veut jouer...
;ecx: adresse de la boucle dans le sample dans la gus k'on veut jouer...

mov eax,[adresse_debut_sample_GUS+ebp]
mov edx,[adresse_fin_sample_GUS+ebp]
mov ecx,[adresse_loop_sample_GUS+ebp]

;push eax
;mov eax,ecx
;call num
;pop eax

dec edx

push eax edx ecx
call def_voix
pop  ecx edx eax
pop bp ;(1)

;;BALANCE_VOIX:
;;entree bl:numero de la voix...
;;entree: al:mode d'envois de la voix...

pop dx ;(2)

xor ax,ax ;ici choisis le mode de la voix
          ;0=normal
push bp

mov bx,bp
shr bx,1 ;dans bl= voix.
;
push bp
;mov dx,32 dans dx numero du sample*4;es:[sample_joue_en_ce_moment+bp]

shr dx,1
mov bp,dx ;dans dx on a garde le numero du sample *2

;push ax
;mov ax,dx
;call affsigne
;pop ax

;----cas particulier
cmp dx,0 ;si on a demande le sample 0: on fais rien!!!
jne ipas_de_boucle3re
mov al,1 ;ARRET LE SAMPLE...
jmp ipas_de_boucle3
ipas_de_boucle3re:
;------------------

cmp word ptr [longueur_loop_sample+ebp],0
je ipas_de_boucle3
mov al,8                  ;mode boucle
ipas_de_boucle3:
pop bp

;mov es:[NOTE_DELAY2+bp],ax ;sauvegarde si la voix est en mode loop ou non

push bx

;entree bl:numero de la voix...
;entree: al:mode d'envois de la voix...

call BALANcE_VOix
pop bx

pop bp


;-----------------------met le bon volume a la voix............
mov ax,63 ; es:[volume_de_la_voix+bp]
push ax
;VOLUME_DUNE_VOIX
mov ax,bp ;VOIX*2
shr ax,1  ;voix
pop bx    ;AL=VOIX
mov ah,bl
;al=voix
;ah=63 volume
call volume_dune_voix_FX
;-----------------------

ret

PLAY_BONUS_SAMPLE ENDP

DEF_VOIX PROC NEAR ;tous les parametres d'une voix...

;entree bl:numero de la voix...
;eax: adresse du debut du sample dans la gus k'on veut jouer...
;edx: adresse de la fin du sample dans la gus k'on veut jouer...
;ecx: adresse de la boucle dans le sample dans la gus k'on veut jouer...
push edx  ;(1)

push eax
mov dx,[gus_voice]   ;choisis la voix concernee...
mov al,bl
out dx,al
mov dx,[gus_command] ;definir le debut de la voix.
mov al,0ah            ;definir adresse hi!
out dx,al
pop eax
;sur 20 bits...
;les bits 12 a 0 representent les 13 bits superieur dans la memoire de la gus

push  eax
;mov bx,ax
;shl bx,9

shr eax,7
;or  ax,bx

mov dx,[gus_datalo]
out dx,ax
;------------------
mov dx,[gus_command] ;definir le debut de la voix.
mov al,0bh            ;definir adresse low!
out dx,al
pop eax
;les 7 bits inferieurs de l'adresse sont definis par les bits 15 a 9
push  eax
shl eax,9
mov dx,[gus_datalo]
out dx,ax
pop eax

;.............definir debut boucle...
mov eax,ecx
push eax
mov dx,[gus_command] ;definir
mov al,02            ;definir adresse hi!
out dx,al
pop eax
;sur 20 bits...
;les bits 12 a 0 representent les 13 bits superieur dans la memoire de la gus

push  eax
;mov bx,ax
;shl bx,9

shr eax,7
;or  ax,bx

mov dx,[gus_datalo]
out dx,ax
;------------------
mov dx,[gus_command] ;definir
mov al,03            ;definir adresse low!
out dx,al
pop eax
;les 7 bits inferieurs de l'adresse sont definis par les bits 15 a 9
push  eax
shl eax,9
mov dx,[gus_datalo]
out dx,ax
pop eax

;.........longueur sample...
pop edx  ;(1)
mov eax,edx
push eax
mov dx,[gus_command] ;definir
mov al,04             ;definir adresse hi!
out dx,al
pop eax
;sur 20 bits...
;les bits 12 a 0 representent les 13 bits superieur dans la memoire de la gus

push  eax
;mov bx,ax
;shl bx,9

shr eax,7
;or  ax,bx

mov dx,[gus_datalo]
out dx,ax
;------------------
mov dx,[gus_command] ;definir le debut de la voix.
mov al,05             ;definir adresse low!
out dx,al
pop eax
;les 7 bits inferieurs de l'adresse sont definis par les bits 15 a 9
push  eax
shl eax,9
mov dx,[gus_datalo]
out dx,ax
pop eax

ret
DEF_VOIX ENDP





VOLUME_DUNE_VOIX PROC NEAr


;push bx cx
;mov cl,al
;mov   bl,30 ;es:[music_volume]
;movzx bx,bl
;sub   bx,63
;;dans bx on a volume-63= chiffre negatif de ce k'on doit retirer au vrais
;;volume
;
;shr ax,8
;add ax,bx
;jns zzzerrere
;mov ax,0
;zzzerrere:
;shl ax,8
;mov al,cl
;pop cx bx

push ax

mov dx,[gUs_VOICE] ;choisis la voix concernee...
out dx,al


mov dx,[gus_command]
mov al,9  ;commande pour le volume...
out dx,al


pop ax
mov dx,[gus_datalo]
mov edi,offset TABLE_Volumes_GUS
shr ax,8
add ax,[music_volume] ;(les 64 premieres valaures correspondent a 0 en fait..)
;shl ax,1
add ax,ax

and eax,01111111111111111B
add edi,eax

mov ax,[edi]
out dx,ax


ret
VOLUME_DUNE_VOIX ENDP

VOLUME_DUNE_VOIX_FX PROC NEAr
;mov al,0  ;VOIX
;mov ah,63 ;VOLUME

push ax

mov dx,[gUs_VOICE] ;choisis la voix concernee...
out dx,al


mov dx,[gus_command]
mov al,9  ;commande pour le volume...
out dx,al


pop ax
mov dx,[gus_datalo]
mov edi,offset TABLE_Volumes_GUS
shr ax,8
add ax,[fx_volume] ;(les 64 premieres valaures correspondent a 0 en fait..)
;shl ax,1
add ax,ax

and eax,01111111111111111B
add edi,eax
mov ax,[edi]
out dx,ax


ret
VOLUME_DUNE_VOIX_FX ENDP

