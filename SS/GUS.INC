
num_voices equ 14

;  u_base     dw 260h
;  u_status   dw u_base+006h
;  u_voice    dw u_base+102h
;  u_command  dw u_base+103h
;  u_Datalo   dw u_base+104h
;  u_Datahi   dw u_base+105h
;  u_DramIO   dw u_base+107h

gus_Init proc near ;entree bp=1 mode silencieux
pusha
push es ds bp
mov ax,rmd_data
mov es,ax

cmp bp,1
je silencieux

  mov bx,word ptr es:[gus_Command]
  mov cx,word ptr es:[gus_datahi]
  mov dx,bx
  mov al,4ch                    ; Choisir le registre d'initialisation
  out dx,al
  mov dx,cx
  mov al,0                      ; Ex‚cuter l'initialisation
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
  mov dx,word ptr es:[gus_status]  ;Vider ‚ventuellement les interrupts DMA
  in al,dx
  mov dx,bx
  mov al,41h
  out dx,al
  mov dx,cx
  in al,dx
  mov dx,bx                 ; Vider ‚ventuellement les interrupts de sampling
  mov al,49h
  out dx,al
  mov dx,cx
  in al,dx
  mov dx,bx                       ; Lire le registre d'‚tat de l'IRQ
  mov al,8Fh                      ; ==> Il n'y a plus d'interruptions
  out dx,al                       ;     non trait‚es
  mov dx,cx
  in al,dx
silencieux:
  push bx                         ; D‚sactive les voix dans la boucle
  push cx
  mov cx,0
@VoiceClearLoop:
  mov dx,word ptr es:[gus_Voice]    ;Choisir les voix
  mov al,cl
  out dx,al
  inc dx
  mov al,0                        ; Poser le mode Voice
  out dx,al

  add dx,2
  mov al,3                        ; Arrˆter les voix
  out dx,al
  sub dx,2                        ; Poser le volume sur 0

cmp bp,1
je erretert
  mov al,0dh
  out dx,al
  add dx,2
  mov al,3
  out dx,al
erretert:
  inc cx
  cmp cx,32                     ; R‚p‚ter pour toutes les voix
  jnz @VoiceClearLoop
  pop cx
  pop bx
cmp bp,1
je silencieux2

  mov dx,bx                     ; Traiter les interruptions
  mov al,41h                    ; ‚ventuelles
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
  mov dx,bx                       ; Ex‚cuter un reset
  mov al,4ch
  out dx,al
  mov dx,cx                   ; Activer l'IRQ master GF1
  mov al,7
  out dx,al

silencieux2:
pop  bp es ds
popa
  ret
gus_Init endp

;ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
light_show proc near

mov ax,rmd_data
mov es,ax

;mov dx,offset joystick_2
;mov ah,9
;int 21h
;
JMP rtrtyrtyrtyrty

            cli
;            call U_SetInterface
;            call U_Probe
            mov dx,es:[gus_base]
            add dx,103h

            mov al,41h
            out dx,al
            add dl,2
            mov al,0
            out dx,al
            sub dl,2
            mov al,45h
            out dx,al
            add dl,2
            mov al,0
            out dx,al
            sub dl,2
            mov al,49h
            out dx,al
            add dl,2
            mov al,0
            out dx,al
            sub dl,2

            mov al,0Eh
            out dx,al
            add dl,2
;            mov eax,[Number_Channel]
;            add eax,[Number_Channel_Sfx]
;            cmp al,15
;            jae @@Ok1
            mov al,15
@@Ok1:
;            movzx ebx,[ChanTab+2*eax-2*14]
;            mov [Replay_Rate],ebx
            dec al
            or al,0c0h
            out dx,al

            mov dx,es:[Gus_base]
            add dl,6
            in al,dx
            mov dx,es:[Gus_base]
            add dx,103h
            mov al,41h
            out dx,al
            add dl,2
            in al,dx
            sub dl,2
            mov al,49h
            out dx,al
            add dl,2
            in al,dx
            sub dl,2
            mov al,8Fh
            out dx,al
            add dl,2
            in  al,dx
            xor ecx,ecx
            xor ebx,ebx
@@Ok2:
            mov dx,es:[Gus_base]
            add dx,102h
            mov al,cl
            out dx,al
            inc dl
            mov al,9
            out dx,al
            inc dl
            mov ax,40004/256 ;[Gus_Volume]
            out dx,ax
            dec dl
            xor al,al
            out dx,al
            add dl,2
            mov al,3                ; Turn voice off
            out dx,al
            call Delay
            out dx,al
            sub dl,2
            mov al,0Dh
            out dx,al
            add dl,2
            mov al,3
            out dx,al
            call Delay
            out dx,al
            sub dl,2
            mov al,06h
            out dx,al
            add dl,2
            mov al,3fh
            out dx,al
            sub dl,2
            mov al,0ch
            out dx,al
            add dl,2
 ;           mov al,[PanRegs+ebx]
;            out dx,al
            sub dl,2
            inc cl
            inc ebx
            cmp cl,32
            jne @@Ok2


            mov dx,es:[Gus_base]
            add dx,103h
            mov al,41h
            out dx,al
            add dl,2                        ; 105h
            in  al,dx
            sub dl,2                        ; 103h
            mov al,49h
            out dx,al
            add dl,2                        ; 105h
            in  al,dx
            sub dl,2                        ; 103h
            mov al,8Fh
            out dx,al
            add dl,2                        ; 105h
            in  al,dx
            sub dl,2                        ; 103h
            mov al,4Ch
            out dx,al
            add dl,2                        ; 105h
            mov al,7
            out dx,al
            sti
            ret

StatusPort      Equ 6h
TimerCtrlPort	Equ 8h
TimerDataPort	Equ 9h
MidiCtrlPort	Equ 100h
MidiDataPort	Equ 101h
ActiveVoicePort	Equ 102h
CommandPort	Equ 103h
DataLowPort	Equ 104h
DataHighPort	Equ 105h
DRAMIOPort	Equ 107h

WriteVoiceMode	Equ 00h
SetVoiceFreq	Equ 01h		; Value=Freq/Divisor
LoopStartLo	Equ 02h
LoopStartHi	Equ 03h
SampleEndLo	Equ 04h
SampleEndHi	Equ 05h
VolRampRate	Equ 06h
VolRampStart	Equ 07h
VolRampEnd	Equ 08h
SetVolume	Equ 09h
SampleStartLo	Equ 0Ah
SampleStartHi	Equ 0Bh
VoiceBalance	Equ 0Ch
VolumeCtrl	Equ 0Dh
VoicesActive	Equ 0Eh
DMACtrl		Equ 41h
DRAMAddrLo	Equ 43h
DRAMAddrHi	Equ 44h
Initialize	Equ 4Ch
ReadVolume	Equ 89h
VoicePosLo	Equ 8Ah
VoicePosHi	Equ 8Bh
ReadVolCtrl	Equ 8Dh

; Divisors



rtrtyrtyrtyrty:

  mov bx,es:[gus_base]
	mov	cx,bx
	add	bx,CommandPort
	add	cx,DataHighPort
	mov	dx,bx
	mov	al,Initialize
	out	dx,al
	mov	dx,cx
	mov	al,0
	out	dx,al
  mov dx,es:[gus_base]
	Rept	6
	in	al,dx
	EndM
	mov	dx,bx
	mov	al,4Ch
	out	dx,al
	mov	dx,cx
	mov	al,1
	out	dx,al
  mov dx,es:[gus_base]
	Rept	6
	in	al,dx
	EndM

	mov	dx,bx
	mov	al,DMACtrl
	out	dx,al
	mov	dx,cx
	mov	al,0
	out	dx,al
	mov	dx,bx
	mov	al,45h
	out	dx,al
	mov	dx,cx
	mov	al,0
	out	dx,al
	mov	dx,bx
	mov	al,49h
	out	dx,al
	mov	dx,cx
	mov	al,0
	out	dx,al

	mov	dx,bx
	mov	al,VoicesActive
	out	dx,al
	mov	dx,cx
  mov al,14
	dec	al
	or	al,0C0h
	out	dx,al

  mov dx,es:[gus_base]
	add	dx,StatusPort
	in	al,dx
	mov	dx,bx
	mov	al,DMACtrl
	out	dx,al
	mov	dx,cx
	in	al,dx
	mov	dx,bx
	mov	al,49h
	out	dx,al
	mov	dx,cx
	in	al,dx
	mov	dx,bx
	mov	al,8Fh
	out	dx,al
	mov	dx,cx
	in	al,dx

	push	cx
	mov	cx,32
VoiceClearLoop:
  mov dx,es:[gus_base]
	add	dx,ActiveVoicePort
	mov	al,cl
	dec	al
	out	dx,al
	inc	dx
	mov	al,0
	out	dx,al
	add	dx,2
	mov	al,3	; Voice Off
	out	dx,al
	sub	dx,2
	mov	al,0Dh
	out	dx,al
	add	dx,2
	mov	al,3	; Ramp Off
	out	dx,al
	loop	VoiceClearLoop
	pop	cx

	mov	dx,bx
	mov	al,DMACtrl
	out	dx,al
	mov	dx,cx
	in	al,dx
	mov	dx,bx
	mov	al,49h
	out	dx,al
	mov	dx,cx
	in	al,dx
	mov	dx,bx
	mov	al,8Fh
	out	dx,al
	mov	dx,cx
	in	al,dx

	mov	dx,bx
	mov	al,Initialize
	out	dx,al
	mov	dx,cx
	mov	al,7
	out	dx,al

  mov cx,20
SetRampRateLoop:
  mov dx,es:[gus_base]
	add	dx,ActiveVoicePort
  mov al,20
	sub	al,cl
	out	dx,al
  mov dx,es:[gus_base]
	add	dx,CommandPort
	mov	al,VolRampRate
	out	dx,al
	mov	al,00111111b
  mov dx,es:[gus_base]
	add	dx,DataHighPort
	out	dx,al

  mov dx,es:[gus_base]
	add	dx,CommandPort
	mov	al,SetVolume
	out	dx,al
  mov ax,40004/256 ;volume
  mov dx,es:[gus_base]
	add	dx,DataLowPort
	out	dx,ax
	loop	SetRampRateLoop

ret


light_show endp

delay proc pascal
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

detect_gusreg proc near
;DANS BX on va mettre la valeur en decimal pour l'affichage !!!
mov bx,190
  mov di,1F0h
encoreunefois:
  add bx,10
  add di,10h
  mov dx,di
  add dx,103h
  mov al,4Ch
  out dx,al
  mov dx,di
  add dx,105h
  mov al,0
  out dx,al

  call delay
  call delay
  mov dx,di
  add dx,103h
  mov al,4Ch
  out dx,al
  mov dx,di
  add dx,105h
  mov al,1
  out dx,al

  mov dx,di
  add dx,103h
  mov al,43h
  out dx,al
  mov dx,di
  add dx,105h
  mov al,0h
  out dx,al

  mov dx,di
  add dx,103h
  mov al,44h
  out dx,al
  mov dx,di
  add dx,105h
  mov al,0h
  out dx,al
  mov dx,di
  add dx,107h
  mov al,'!'
  out dx,al
  call delay
  call delay
  call delay
  call delay
  call delay
  call delay
  xor ax,ax
  mov dx,di
  add dx,107h
  in  al,dx
  cmp al,'!'
  je  victoiree
  cmp di,280h
  ja  rien
  jmp encoreunefois
victoiree:
mov ax,rmd_data
mov es,ax
mov ds,ax
  mov word ptr es:[gus_base],di
  mov ax,di
  add ax,6
  mov word ptr es:[gus_status],ax
  mov ax,di
  add ax,102h
  mov word ptr es:[gus_voice],ax
  mov ax,di
  add ax,103h
  mov word ptr es:[gus_command],ax
  mov ax,di
  add ax,104h
  mov word ptr es:[gus_Datalo],ax
  mov ax,di
  add ax,105h
  mov word ptr es:[gus_Datahi],ax
  mov ax,di
  add ax,107h
  mov word ptr es:[gus_DramIO],ax

mov es:[gus_or_sb],1
mov ax,bx
mov dx,offset gusmess2
call aff_port

  rien:
  ret
detect_gusreg endp


BUFFER_2GUS PROC NEAR

;entree EBx: adresse dans la gravis
;       ecx: longueur du sample...
push ebx eax ecx edx ds
mov ax,rmd_data
mov ds,ax
mov si,offset header_mod ;BUFFER_LOAD_GUS


mov dx,es:[gus_command]
mov al,044h     ;pour specifier l'adresse High dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datahi]
push ebx
shr ebx,16
mov al,bl
out dx,al       ;on place l'adresse high...
pop ebx

tencore_un_octet:

mov dx,es:[gus_command]
mov al,043h     ;pour specifier l'adresse LOW dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datalo]
mov ax,bx
out dx,ax

mov dx,es:[gus_dramio]
lodsb
out dx,al            ;ecris l'octet dans la GUS..

inc ebx
or bx,bx
jnz terreererreer ;cas particulier:on doit changer de segment.

mov dx,es:[gus_command]
mov al,044h     ;pour specifier l'adresse High dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datahi]
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

GET_GUs_MEMORY PROC NEAR

mov ax,rmd_data
mov es,ax

;teste si on a 512 KB dans la GUS
mov ebx,0 ;1024*256

sucre:
mov dx,es:[gus_command]
mov al,044h     ;pour specifier l'adresse High dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datahi]
push ebx
shr ebx,16
mov al,bl
out dx,al       ;on place l'adresse high...
pop ebx

mov dx,es:[gus_command]
mov al,043h     ;pour specifier l'adresse LOW dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datalo]
mov ax,bx
out dx,ax

mov dx,es:[gus_dramio]
mov al,'R'
out dx,al            ;ecris l'octet dans la GUS..

  call delay
  call delay
  call delay
  call delay
  call delay
  call delay

mov dx,es:[gus_dramio]

in al,dx             ;ecris l'octet dans la GUS..
cmp al,'R'
jne finicetest


add ebx,1024*256

cmp ebx,1024*256*4
jne sucre ;jne sucre
finicetest:

dec ebx
mov es:[MEMOIRE_GUS],ebx

ret
GET_GUs_MEMORY ENDP

GUS_2BUFFER PROC NEAR

;entree EBx: adresse dans la gravis
;       ecx: longueur du truc a copier...

mov di,offset PATTERN_LOAD

mov dx,es:[gus_command]
mov al,044h     ;pour specifier l'adresse High dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datahi]
push ebx
shr ebx,16
mov al,bl
out dx,al       ;on place l'adresse high...
pop ebx

stencore_un_octet:

mov dx,es:[gus_command]
mov al,043h     ;pour specifier l'adresse LOW dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datalo]
mov ax,bx
out dx,ax

mov dx,es:[gus_dramio]
in al,dx
stosb        ;lis l'octet dans la GUS..

inc ebx
or bx,bx
jnz sterreererreer ;cas particulier:on doit changer de segment.

mov dx,es:[gus_command]
mov al,044h     ;pour specifier l'adresse High dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datahi]
push ebx
shr ebx,16
mov al,bl
out dx,al       ;on place l'adresse high...
pop ebx

sterreererreer:
dec cx
jnz stencore_un_octet

ret
GUS_2BUFFER ENDP


SAMPLE_MEM2GUS PROC NEAR

;entree ds,SI source du sample en mem normalle..
;entree EBx: adresse dans la gravis
;       ecx: longueur du sample...


mov dx,es:[gus_command]
mov al,044h     ;pour specifier l'adresse High dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datahi]
push ebx
shr ebx,16
mov al,bl
out dx,al       ;on place l'adresse high...
pop ebx

encore_un_octet:

mov dx,es:[gus_command]
mov al,043h     ;pour specifier l'adresse LOW dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datalo]
mov ax,bx
out dx,ax

mov dx,es:[gus_dramio]
lodsb

out dx,al            ;ecris l'octet dans la GUS..

inc ebx
or bx,bx
jnz erreererreer ;cas particulier:on doit changer de segment.

mov dx,es:[gus_command]
mov al,044h     ;pour specifier l'adresse High dans memoire de la GUS!!!
out dx,al
mov dx,es:[gus_datahi]
push ebx
shr ebx,16
mov al,bl
out dx,al       ;on place l'adresse high...
pop ebx

erreererreer:
dec cx
jnz encore_un_octet

ret
SAMPLE_MEM2GUS ENDP

;*********
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

mov dx,es:[gUs_VOICE] ;choisis la voix concernee...
out dx,al


mov dx,es:[gus_command]
mov al,9  ;commande pour le volume...
out dx,al


pop ax
mov dx,es:[gus_datalo]
mov di,offset TABLE_Volumes_GUS
shr ax,8
add ax,es:[music_volume] ;(les 64 premieres valaures correspondent a 0 en fait..)
;shl ax,1
add ax,ax
add di,ax

mov ax,es:[di]
out dx,ax


ret
VOLUME_DUNE_VOIX ENDP

;*********
VOLUME_DUNE_VOIX_FX PROC NEAr
;mov al,0  ;VOIX
;mov ah,63 ;VOLUME

push ax

mov dx,es:[gUs_VOICE] ;choisis la voix concernee...
out dx,al


mov dx,es:[gus_command]
mov al,9  ;commande pour le volume...
out dx,al


pop ax
mov dx,es:[gus_datalo]
mov di,offset TABLE_Volumes_GUS
shr ax,8
add ax,es:[fx_volume] ;(les 64 premieres valaures correspondent a 0 en fait..)
;shl ax,1
add ax,ax

add di,ax
mov ax,es:[di]
out dx,ax


ret
VOLUME_DUNE_VOIX_FX ENDP


DEF_VOIX PROC NEAR ;tous les parametres d'une voix...

;entree bl:numero de la voix...
;eax: adresse du debut du sample dans la gus k'on veut jouer...
;edx: adresse de la fin du sample dans la gus k'on veut jouer...
;ecx: adresse de la boucle dans le sample dans la gus k'on veut jouer...
push edx  ;(1)

push eax
mov dx,es:[gus_voice]   ;choisis la voix concernee...
mov al,bl
out dx,al
mov dx,es:[gus_command] ;definir le debut de la voix.
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

mov dx,es:[gus_datalo]
out dx,ax
;------------------
mov dx,es:[gus_command] ;definir le debut de la voix.
mov al,0bh            ;definir adresse low!
out dx,al
pop eax
;les 7 bits inferieurs de l'adresse sont definis par les bits 15 a 9
push  eax
shl eax,9
mov dx,es:[gus_datalo]
out dx,ax
pop eax

;.............definir debut boucle...
mov eax,ecx
push eax
mov dx,es:[gus_command] ;definir
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

mov dx,es:[gus_datalo]
out dx,ax
;------------------
mov dx,es:[gus_command] ;definir
mov al,03            ;definir adresse low!
out dx,al
pop eax
;les 7 bits inferieurs de l'adresse sont definis par les bits 15 a 9
push  eax
shl eax,9
mov dx,es:[gus_datalo]
out dx,ax
pop eax

;.........longueur sample...
pop edx  ;(1)
mov eax,edx
push eax
mov dx,es:[gus_command] ;definir
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

mov dx,es:[gus_datalo]
out dx,ax
;------------------
mov dx,es:[gus_command] ;definir le debut de la voix.
mov al,05             ;definir adresse low!
out dx,al
pop eax
;les 7 bits inferieurs de l'adresse sont definis par les bits 15 a 9
push  eax
shl eax,9
mov dx,es:[gus_datalo]
out dx,ax
pop eax

ret
DEF_VOIX ENDP
;FREQ_VOIX2 PROC NEAR
;
;;entree bl:numero de la voix...
;; CX: FREQUENCE TELLE K'on LA BALANCe!!!
;
;mov dx,es:[gus_voice]   ;choisis la voix concernee...
;mov al,bl
;out dx,al
;
;mov dx,es:[gus_command] ;ontorle frequence.
;mov al,1
;out dx,al
;
;mov dx,es:[gus_datalo]
;mov ax,cx
;out dx,ax
;ret
;
;FREQ_VOIX2 ENDP

FREQ_VOIX PROC NEAR

;entree bl:numero de la voix...
;dans bh: ce kon doit utiliser pour piocher la frequence dans gusfreq
;         BRUT! tel k'il est dans les pattern format remdy.
;         (on va le multiplier par 4 ensuite...)
; CX: ce k'on ajoute a la frequence... (utile pour portamento...)

mov dx,es:[gus_voice]   ;choisis la voix concernee...
mov al,bl
out dx,al

mov dx,es:[gus_command] ;ontorle frequence.
mov al,1
out dx,al

shr bx,8
shl bx,2

mov eax,es:[gusfreq+BX]

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
mov dx,es:[gus_datalo]

mov es:[freq_joue_gus+bp],ax

out dx,ax
ret

FREQ_VOIX ENDP

BALANcE_VOIX PROC NEAR

;entree bl:numero de la voix...
;entree: al:mode d'envois de la voix...

push ax

mov dx,es:[gus_voice]   ;choisis la voix concernee...
mov al,bl             ;numero de la voix concernee
out dx,al

mov dx,es:[gus_command] ;fonction controle des voix!
mov al,0
out dx,al

mov dx,es:[gus_datahi]

pop ax
out dx,al

push ax
call delay
pop  ax
;----------- double!!!
push ax

mov dx,es:[gus_voice]   ;choisis la voix concernee...
mov al,bl             ;numero de la voix concernee
out dx,al

mov dx,es:[gus_command] ;fonction controle des voix!
mov al,0
out dx,al

mov dx,es:[gus_datahi]

pop ax
out dx,al

ret
BALANcE_VOix eNdP


PLay_SONg_GUS PROC NEAR

call gus_Init

mov ax,rmd_data
mov es,ax
;.............................. pour la vitesse..............................
call calc_new_speed_GUS    ;calcule un nouvelle table de speed.
                       ;il_faut_maintenant_mettre_a_jour_le_speed_compteu
mov ax,es:[speed_song]
shl ax,2 ;multiplie par 4...
mov di,offset Speed_wait
add di,ax
mov eax,es:[di]
mov es:[speed_compteur_save],eax
mov es:[speed_compteur],eax

call calcule_la_duree_dun_tick
mov es:[compteur_effect_entre_ligne_save],ax

;.............................................................................

PUSHA
PUSH DS ES
MOV ax,rmd_data
mov ds,ax

mov ax,3508h
int 21h

mov ax,es
push ax
mov ax,rmd_data
mov es,ax
pop ax
mov word ptr es:[old_int8],bx
mov word ptr es:[old_int8+2],ax

push ds
mov ax,cs
mov ds,ax
mov dx,offset sortie_directe_GUS
mov ax,2508h
int 21h
pop ds
POP ES DS
POPA

cli
mov ax,954 ; ;(1193180/1250)=...
push ax
mov dx,043h
mov al,036h
out dx,al ;036h
mov dx,040h
pop ax
out dx,al
mov al,ah
out dx,al
sti

ret
PLay_SONg_GUS endp

;nombre_de_voix db ?                 ;nombre de voix dans le mod...
;PATTERN_LOAD   DB 8*4 DUP (?)       ;ou on place la ligne de pattern lu dans
;
;numero_de_ligne_dans_pattern    dd 0 ;dans le pattern courant.
;viseur_dans_arrangement_chanson dw 0 ;
;
;nombre_total_de_pattern_chanson dw ? ;nombre total dans l'arrangemement de
;                                     ;la chanson.
;nombre_total_de_pattern_mod     db ? ;nombre total de pattern dans le mod.
;arrangement_de_la_chanson db 128 dup (?)    ;ordre des patterns a executer.

LOAD_LIGNE_DE_PATTERN PROC NEAR ;entree: ES sur rmd_data

xor ecx,ecx
mov cl,es:[nombre_de_voix]
shl ecx,2 ;mutiplie par 4 (4 ... octets par VOIX!)
;dans ECX nombre d'octet par ligne...

;mov eax,ecx
;shl eax,6 ;mutliplie par 2^6=64
;;Dans EAX on a le nombre d'octet par pattern...
;
;mov si,offset arrangement_de_la_chanson
;add si,es:[viseur_dans_arrangement_chanson]
;xor bx,bx
;mov bl,es:[si] ;dans bx on a le numero du pattern dans lekel il faut viser..

mov ebx,es:[viseur_dans_pattern]

call GUS_2BUFFER ;entree ECX: nombre d'octet a recopier,EBX:viseur dans DRAM
;xor ax,ax
;
;mov al,es:[PATTERN_LOAD]
;call affsigne
ret
LOAD_LIGNE_DE_PATTERN ENDP


lit_pattern_GUS proc near

call LOAD_LIGNE_DE_PATTERN

;on anule les effect ki durent entre les ligneS...
;pour les 8 voix.
mov es:[table_de_saut],offset nopper
mov es:[table_de_saut+2],offset nopper
mov es:[table_de_saut+4],offset nopper
mov es:[table_de_saut+6],offset nopper

mov es:[table_de_saut+8],offset nopper
mov es:[table_de_saut+10],offset nopper
mov es:[table_de_saut+12],offset nopper
mov es:[table_de_saut+14],offset nopper

;mov bp,0   ;nuemro de voix*2
xor bp,bp
gencore_une_voix:

mov ax,rmd_data
;mov es,ax
mov ds,ax
mov esi,offset PATTERN_LOAD

movzx eax,bp  ;note:...on incremente de 4 par note...car on lit pas le meme octet!!
;shl ax,1
add ax,ax
add esi,eax
                                ;
                                ;valeur k'on additionne pour
                                ;piocher dans le segment pattern
xor ax,ax
lodsb

or al,al ;important si c'est le sample 0; aucune modification a faire
jz gpas_de_modif_sample
;----- Quand on change un sample: c'est ici k'on change le volume.
;      pas ailleur...on change donc juste:le volume et le prochain sample
;      qui sera joue...

mov es:[sample_joue_en_ce_moment+bp],ax ;+numero voix*2
                                     ;note: si on met 0 il n'y a pas
                                     ;de sample joue du tout.
                                     ;...
                                     ;or si le numero du sample  est a 0
                                     ;ici on se contente de joue du dernier
mov bx,ax                                  ;instrument.
;shl bx,1
add bx,bx

;dans bx: numero du sample joue *2 ;!
mov ax,es:[volume_sample+bx] ;(bx=+numero sample*2)
mov es:[volume_de_la_voix+bp],ax ;+numero voix*2


push bx
mov bx,bp
shr bx,1
mov al,es:[panning_GUS+Bx]
call balance
pop bx


;..........................................
gpas_de_modif_sample:


;;**** ETEINT D'ABORD LA VOIX
;push ax bx
;mov bx,bp
;shr bx,1
;mov al,1 ;mode etteint voix
;call BALANcE_VOIX
;pop bx ax
;;;****

mov dx,es:[sample_joue_en_ce_moment+bp]
shl dx,2  ;dans dx on garde le numero du sample *4

;................ frequence/note
mov bx,bp ;numero de voix*2
shr bx,1
;dans bX (bl) numero de voix

xor ax,ax
lodsb ;charge deuxieme octet format remdy

cmp al,-1 ;code special indique k'il n'y a pas de note...
je gpas_de_noteee ;ya PAS de une nouvelle note

mov bh,al
;DAns bh on a le numero de la nouvelle note a jouer...


push ax bx ;.........;met le volume a 0-------
push ax
;VOLUME_DUNE_VOIX
mov ax,bp ;VOIX*2
shr ax,1  ;voix
pop bx    ;AL=VOIX
mov ah,0 ;AH=volume... ;on met
;al=voix
;ah=63 volume
call volume_dune_voix
pop bx ax

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

push bx
shr bx,8
mov es:[SAUVE_VISEUR_DANS_SBFREQ+BP],BX
pop bx

;*********
;FREQ_VOIX:
;entree bl:numero de la voix...
;dans bh: ce kon doit utiliser pour piocher la frequence dans gusfreq
;         BRUT! tel k'il est dans les pattern format remdy.
;         (on va le multiplier par 4 ensuite...)

;cx: ce k'on ajoute a la freq (utile pour portamento+vibrato)

mov es:[portamento_gus+bp],0 ;pour effet portemento
mov es:[vibrato_gus+bp],0    ;pour effet vibrato

push bx dx
xor cx,cx
call FREQ_VOIX
pop dx bx

;........................definit le sample en question....
mov bx,es:[sample_joue_en_ce_moment+bp] ;+numero voix*2
;shl bx,1
add bx,bx

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


;shl bx,1 ;NUMERO SAMPLE JOUE *4
add bx,bx ;NUMERO SAMPLE JOUE *4

mov ax,bp
shr ax,1

push bp ;(1)
mov bp,BX ;NUMERO SAMPLE JOUE *4

mov bl,al ;dans bl=numero de VOIX

;*********
;DEF_VOIX:
;entree bl:numero de la voix...
;eax: adresse du debut du sample dans la gus k'on veut jouer...
;edx: adresse de la fin du sample dans la gus k'on veut jouer...
;ecx: adresse de la boucle dans le sample dans la gus k'on veut jouer...

mov eax,es:[adresse_debut_sample_GUS+bp]
mov edx,es:[adresse_fin_sample_GUS+bp]
mov ecx,es:[adresse_loop_sample_GUS+bp]
dec edx

;.........sauvegarde de ces informations... (utile pour effet 9 offset)

;push ax
;mov ax,bx
;and ax,0FFH
;call affsigne
;pop  ax

push eax edx ecx
call def_voix
pop  ecx edx eax
pop bp ;(1)

;.........sauvegarde de ces informations... (utile pour effet 9 offset)
mov  bx,bp
;shl  bx,1 ;bx= voix*4
add bx,bx ;bx= voix*4
mov es:[gus_adresse_debut_sample_GUS+bx],eax
mov es:[gus_adresse_fin_sample_GUS+bx],edx
mov es:[gus_adresse_loop_sample_GUS+bx],ecx
;...............

;;BALANCE_VOIX:
;;entree bl:numero de la voix...
;;entree: al:mode d'envois de la voix...

xor ax,ax ;ici choisis le mode de la voix
          ;0=normal
push bp

mov bx,bp
shr bx,1 ;dans bl= voix.

mov dx,es:[sample_joue_en_ce_moment+bp]
;shl dx,1
add dx,dx
mov bp,dx ;dans dx on a garde le numero du sample *2

cmp word ptr es:[longueur_loop_sample+bp],0
je pas_de_boucle3
mov al,8                  ;mode boucle
pas_de_boucle3:

mov es:[NOTE_DELAY2+bp],ax ;sauvegarde si la voix est en mode loop ou non

push bx

;entree bl:numero de la voix...
;entree: al:mode d'envois de la voix...

call BALANcE_VOix

pop bx

pop bp


;-----------------------met le bon volume a la voix............
mov ax,es:[volume_de_la_voix+bp]
push ax
;VOLUME_DUNE_VOIX
mov ax,bp ;VOIX*2
shr ax,1  ;voix
pop bx    ;AL=VOIX
mov ah,bl
;al=voix
;ah=63 volume
call volume_dune_voix
;-----------------------

gpas_de_noteee:

;.......... les effets sont nos amis.
lodsw
;call num
;dans al:numero effet
;dans ah:commande effet
;on a dans bp=la voix*2
;

call effets1_GUS     ;detection de tous les effets.

;mov al,3
;mov ah,63
;call volume_dune_voix


add bp,2
xor ax,ax
mov al,es:[nombre_de_voix]
add ax,ax
cmp bp,AX
jne gencore_une_voix

ret
lit_pattern_gus endp
STOP_SONG_GUS PROC NEAR
;.................retablis le timer...........................................

cli
mov dx,043h
mov al,036h
out dx,al
xor ax,ax
mov dx,040h
out dx,al
out dx,al
sti

mov ax,rmd_data
mov es,ax
mov ds,ax
PUSH DS
LDS dx,es:[old_int8]
mov ax,2508h
int 21h
pop ds

call gus_Init
ret
STOP_SONG_GUS ENDP

sortie_directe_GUS proc near
PUSHF
push ds es bp eax ebx ecx edx si di

;call pal2A

;...............lecture du pattern... (une fois de temps en temps...)
mov ax,rmd_data
mov es,ax
cmp es:[mode_music],0
je msdosd

cmp dword ptr es:[speed_compteur],0
jnz grerereretrterty2
mov eax,es:[speed_compteur_save]
mov es:[speed_compteur],eax
;on place ici le nombre dans speed_wait k'on a choisit
                       ;ca reviendra a ca apres etre arrive a 0...

call lit_pattern_GUS



;.................deplacement d'une ligne vers l'avant...
inc dword ptr es:[numero_de_ligne_dans_pattern]
cmp dword ptr es:[numero_de_ligne_dans_pattern],64
jne gon_continue_dans_le_meme_pattern
;....on est arrive la fin d'un pattern...
mov dword ptr es:[numero_de_ligne_dans_pattern],0

inc es:[viseur_dans_arrangement_chanson]
mov ax,es:[nombre_total_de_pattern_chanson]
cmp es:[viseur_dans_arrangement_chanson],ax ;on regarde si on est arrive
                                            ;a la fin de l'arrangement.
jne gcharlyrulz
mov es:[viseur_dans_arrangement_chanson],0   ;on repart au debut...
                                             ;de l'arrangement


gcharlyrulz:

mov bx,es:[viseur_dans_arrangement_chanson]
;xor eax,eax
;mov al,es:[arrangement_de_la_chanson+bx]
movzx eax,es:[arrangement_de_la_chanson+bx]

;nombre_de_voix db ?                 ;nombre de voix dans le mod...
cmp es:[nombre_de_voix],4
je canariwarior
shl eax,11 ;multiplie par 2048... 8 VOIX
           ;on a donc dans ax le viseur_dans_pattern
jmp canariwarior2
canariwarior:
shl eax,10 ;multiplie par 1024... 4 VOIX
           ;on a donc dans ax le viseur_dans_pattern
canariwarior2:

mov es:[viseur_dans_pattern],eax
jmp grerereretrterty
gon_continue_dans_le_meme_pattern:

cmp es:[nombre_de_voix],4
je canariwariorf
add es:[viseur_dans_pattern],32 ;8 VOIX
jmp canariwarior2f
canariwariorf:
add es:[viseur_dans_pattern],16 ;4 VOIX
canariwarior2f:

grerereretrterty:

;mov ax,es:[volume_sample] ;(bx=+numero sample*2)
;shl ax,8
;mov al,0
;call volume_dune_voix
;
;mov ax,es:[volume_sample+2] ;(bx=+numero sample*2)
;shl ax,8
;mov al,1
;call volume_dune_voix
;
;mov ax,es:[volume_voix+4] ;(bx=+numero sample*2)
;shl ax,8
;
;mov ax,es:[volume_sample+6] ;(bx=+numero sample*2)
;shl ax,8
;mov al,3
;call volume_dune_voix
;

call effets2    ;effet ki s'activent lorsqu'on a fini la ligne courante
                ;(detect‚s grace a effet 1)
                ;on le place ici car permet de modififer les modifs naturelles
                ;de deplacement dans les patterns de sorte k'elles nont aucun
                ;effet.
                ;effets valable pour SB et GUS

call synchro ;met a jour les variables public de la synchro

grerereretrterty2:
;....................................
dec dword ptr es:[speed_compteur]
;....................................


;;********** appelle les effets ki marchent entre les lignes **********
;
;mov bp,0
;gdarling:
;call es:[table_de_saut+bp]     ;effets actif pour les 4 voix...
;add bp,2
;cmp bp,8
;jne gdarling

;mov bp,0
xor bp,bp
call es:[table_de_saut]     ;pour 8 voix...
mov bp,2
call es:[table_de_saut+2]
mov bp,4
call es:[table_de_saut+4]
mov bp,6
call es:[table_de_saut+6]
mov bp,8
call es:[table_de_saut+8]
mov bp,10
call es:[table_de_saut+10]
mov bp,12
call es:[table_de_saut+12]
mov bp,14
call es:[table_de_saut+14]

msdosd:
;*********************************************************************
;----------------------- EXTRA SOunD FX ------------------------------

cmp es:[mode_fx],0
je aeroplane2t

;mov bp,0
xor bp,bp
mov bx,8
ice9606A:

cmp es:[blow_what+4+bp],1
jne riendenouveau
mov dx,es:[blow_what+bp]   ;32 ;numero du sample
mov ax,es:[blow_what+2+bp] ;30 ;numero de la note.

shl dx,2

mov es:[blow_what+4+bp],0

push bp bx
;shl bx,1
add bx,bx

mov bp,bx
call PLaY_BONUS_SAMPLE
pop bx bp
riendenouveau:

cmp es:[blow_what+4+bp],2
jne riendenouveau2

mov dx,es:[blow_what+bp]   ;32 ;numero du sample
mov ax,es:[blow_what+2+bp] ;30 ;numero de la note.

shl dx,2

mov es:[blow_what+4+bp],0

push bp bx
;shl bx,1
add bx,bx
mov bp,bx
call PLaY_BONUS_SAMPLE2
pop bx bp


riendenouveau2:


add bp,6
inc bx

cmp bx,12
jne ice9606A

aeroplane2t:
;*********************************************************************


dec es:[old_timer_compteur_GUS]
jnz gdfgfgdghfgttttttttfg
mov es:[old_timer_compteur_GUS],17
pushf ;toutes les  18.2 fois /S ici on le fait 10000 fois /S donc: 10000/18.2
call dword ptr es:[old_int8]
call teste_Joystick
pop  di si edx ecx ebx eax bp es ds
popF
Iret
gdfgfgdghfgttttttttfg:
;....................................

gfggghghyjfyrytyt:

mov al,20h                  ;
out 20h,al                  ;

pop  di si edx ecx ebx eax bp es ds
popF
Iret

sortie_directe_GUS endp

effets1_GUS proc near ;detection de tous les effets.

                  ;on a dans bp=la voix*2
                  ;dans al:commande
                  ;dans ah:=parametre
push di eax si bx

;************** effet 0, Arpeggio...
;effect qui dure entre les lignes...
;pas besoin du convertisseur
cmp al,0
jne trfraiche2c3

cmp ah,0          ;si le parametre est aussi a 0 il n'y a pas d'effet!
je trfraiche2c3    ;

;on a sauvegard‚ SAUVE_VISEUR_DANS_SBFREQ+BP
;ce ki va permettre de recuperer les frequences des deux notes k'on va nous
;demander.

push ax ;(1)
shr ax,8+4
;on a dans ax:le nombre de demi-tons a rajouter.

;call affsigne

push ax
xor ebx,ebx
xor eax,eax
pop ax

mov bx,es:[SAUVE_VISEUR_DANS_SBFREQ+BP]

mov si,offset FREQUENCE_POUR_LES_3_NOTES1 ;en fait pour la GUS  on sauvegarde
add si,bp                                 ;l'adder d'offset (et non la
add si,bp                                 ;frequence) comme pour la SB
mov es:[si],ebx

;call affsigne

push bx ;'4'
;shl ax,2 ;on multiplie par 4 le nombre de demi-ton a rajouter.

sub bx,ax
jnc orsay23  ;cas particulier:depasserait les valeurs possible (trop aigu)
xor bx,bx
orsay23:


mov si,offset FREQUENCE_POUR_LES_3_NOTES2
add si,bp
add si,bp
mov es:[si],ebx

pop bx ;'4'

pop ax ;(1)

shr ax,8
and ax,00001111B
;call affsigne
;shl ax,2

;add ax,bx

sub bx,ax
jnc orsay233  ;cas particulier:depasserait les valeurs possible (trop aigu)
xor bx,bx
orsay233:


mov si,offset FREQUENCE_POUR_LES_3_NOTES3
add si,bp
add si,bp
mov es:[si],ebx

;---------------------------------
mov si,offset compteur_pour_arpegio
add si,bp
add si,bp
mov dword ptr es:[si],0

mov es:[compteur_pour_arpegio3+bp],0

mov si,offset compteur_pour_arpegio2
add si,bp
add si,bp

mov eax,es:[speed_compteur] ;duree d'une ligne
dec eax                     ;pour s'arreter juste avant
mov dword ptr es:[si],eax

mov es:[table_de_saut+bp],offset fx_arpegio_GUS

jmp rfin_proc_effet1
trfraiche2c3:

;************** effet 1,PORTAMENTO UP
;effect qui dure entre les lignes...

cmp al,01
jne jrfraiche2c

shr ax,8

;....dans ax on a le parametre...

;shl ax,1

mov es:[adder_effect_entre_ligne+bp],ax ;completement au PIF.mais ca marche.

mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

mov es:[table_de_saut+bp],offset fx_portamento_updown_GUS

jmp rfin_proc_effet1
jrfraiche2c:

;************** effet 2,PORTAMENTO DOWN
;effect qui dure entre les lignes...

cmp al,02
jne yjrfraiche2c

shr ax,8

;....dans ax on a le parametre...

neg ax ;PORTAMENTO DOWN
mov es:[adder_effect_entre_ligne+bp],ax ;completement au PIF.mais ca marche.

mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

mov es:[table_de_saut+bp],offset fx_portamento_updown_GUS

jmp rfin_proc_effet1
yjrfraiche2c:

;************** 3 TONE PORTAMENTO +5
;effect qui dure entre les lignes...

cmp al,5 ;TONE PORTAMENTO + volume sliming sans nouvelle note
je lsexyremdy1

cmp al,-1 ;TONE PORTAMENTO sans nouvelle note...
je lsexyremdy
;----------------nouvelle note------------
cmp al,20        ;cas particulier pour les effets 3=20+la note
                 ;on a sauvegard‚ la note fantome dans l'effet au lieu de
                 ;la laisser (ce qui aurait pos‚ la probleme que la note
                 ;aurait ete jouee..
jb lrfraiche2cER

push ax
and ax,255
sub ax,20

;call affsigne
;mov eax,es:[gusfreq+BX]
;freq_joue_gus  DW 8 DUP (?)

shl ax,2                  ;on multiplie par 4 (permet de stocker plus petit!)
mov bx,ax
mov eax,es:[gusfreq+bx]

mov si,offset SAVE_NOTE_PORTAMENTO
add si,bp
add si,bp
mov es:[si],eax

pop ax
;call affsigne
mov es:[sauvegarde_de_la_vitesse_du_portamento+bp],ax

;------------------kan on arrive ici on se raproche de l'autre note...
JMP lsexyremdy

;----ZONE POUR LE VOLUME SLIMING EN PLUS
lsexyremdy1:

shr ax,8
;******* s'occupe du volume sliming ******
;push ax

and ax,01111B
;on a dans ax la vitesse du volumesliming down...

mov es:[table_de_saut+bp],offset fx_volumeslimingdown_GUS
mov es:[adder_effect_entre_ligne+bp],ax ;definis la vitesse...
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax
;------------ fini par le portamento

mov ax,es:[sauvegarde_de_la_vitesse_du_portamento+bp]

lsexyremdy:
;_____________________________________________________________________________

or ah,ah ;dans AX on a la vitesse du portamento
jnz les_2
;si ah=0 on utilise la derniere valeur de vitesse de portamento k'on a utilise
mov ax,es:[sauvegarde_de_la_vitesse_du_portamento+bp]
les_2:

movzx edx,ah ; dans EDX on a la vitesse du portamento

mov si,offset SAVE_NOTE_PORTAMENTO ;(c)
add si,bp
add si,bp
mov eax,es:[si]
cmp eax,-1
je lprobleme_fais_rienddd ;si pas de note avant...on fait rien,.
;------- dans eax: frequence finale
;DANS EAX on a la frequence finale du portamento

movzx ebx,es:[freq_joue_gus+bp] ;(a)
push  ecx
movzx ecx,es:[portamento_gus+bp]  ;(b)
add   ebx,ecx
pop   ecx
;DANS EBX on a la frequence joue en GUS

cmp ebx,eax  ; (c)=(a)+(b) ???
je loooooouuuuuuuuuh ;si on est impect bon on arrete !!!
ja lriver

add es:[portamento_gus+bp],dx
add ebx,edx

cmp ebx,eax
jb loooooouuuuuuuuuh

somethingyousaid:
;--------- on arrive ici si on a depass‚ dans l'autre sens
;          la valeur max!!!
sub es:[portamento_gus+bp],dx
;sub ebx,edx
;mov ebx,eax

push ebx eax
mov si,offset SAVE_NOTE_PORTAMENTO ;note finale. ;(c)
add si,bp
add si,bp

mov ebx,es:[si]
xor eax,eax
mov ax,es:[freq_joue_gus+bp]       ; (a)
sub ebx,eax
mov es:[portamento_gus+bp],bx      ;(c)-(a)= (b)
pop eax ebx
;--------
jmp je_dis_mefiance
lriver:

sub es:[portamento_gus+bp],dx
sub ebx,edx

cmp ebx,eax
ja loooooouuuuuuuuuh
righttt:

add es:[portamento_gus+bp],dx

;add ebx,edx
;mov ebx,eax

push ebx eax
mov si,offset SAVE_NOTE_PORTAMENTO ;note finale. ;(c)
add si,bp
add si,bp
mov ebx,es:[si]

xor eax,eax
mov ax,es:[freq_joue_gus+bp]       ; (a)
sub ebx,eax
mov es:[portamento_gus+bp],bx      ;(c)-(a)= (b)
pop eax ebx
;--------
;call num
jmp je_dis_mefiance

loooooouuuuuuuuuh:
mov es:[freq_joue_gus+bp],bx

je_dis_mefiance:

;mov ecx,ebx ;freq

mov bx,bp
shr bx,1
mov bh,byte ptr es:[SAUVE_VISEUR_DANS_SBFREQ+BP]
;entree bl:numero de la voix...
;dans bh: ce kon doit utiliser pour piocher la frequence dans gusfreq
push bx dx
mov cx,es:[portamento_gus+bp]
call FREQ_VOIX
pop dx bx

lprobleme_fais_rienddd:
jmp fin_proc_effet1

lrfraiche2cER:

;************** effet 4, VIBRATO
;effect qui dure entre les lignes...

cmp al,04
jne trfraiche2c2_f

;push ax
;xor eax,eax
;pop ax
and eax,01111111111111111B

push ax
shr ax,8
and ax,01111B     ;ici on a donc Y profondeur
jz hihhiihhihi2   ;si=0 on utilisera le dernier vibrato_fx_prof
mov es:[vibrato_fx_prof+bp],ax
hihhiihhihi2:

;call num
pop ax

;push ax
shr ax,8+4    ;ici on a donc X vitesse
;shl ax,1
add ax,ax  ;*2 ;!!!

jz hihhiihhihi
mov es:[vibrato_fx_speed+bp],ax
hihhiihhihi:      ;si=0 on utilisera le dernier vibrato_fx_speed

;call num
;pop ax

;mov es:[VIBRATO_viseur],0

call calcule_la_duree_dun_tick
;dans ax on a le nombre de vibrato compteur a passer pour faire a un tick.
;on doit diviser ca parla vitesse du truc

xor dx,dx
mov bx,es:[vibrato_fx_speed+bp]
or bx,bx
jz trtrttterertrte
div bx
jmp trerererer
trtrttterertrte:
mov ax,es:[VIBRATO_compteur_save+bp] ;si la vitesse=0 on reprend la derniere
                                     ;vitesse k'on a eu...
trerererer:

;attention:cas particlier:si la zik etait tres rapide...
;il est possible ke la division donne zero (c'est a dire k'il faudrait une
;modif plus souvent ke le le player est appele en hz..on reduira donc a un fois...)
or ax,ax
jnz terreerththrtrt
mov ax,1
terreerththrtrt:

mov es:[VIBRATO_compteur_save+bp],ax
mov es:[VIBRATO_compteur+bp],ax

mov es:[table_de_saut+bp],offset VIBRATO_fx_GUS


mov ax,es:[portamento_gus+bp]
mov es:[SAVE_PORTO_VIBRATO+BP],ax

jmp rfin_proc_effet1
trfraiche2c2_f:

;************** effet 6 VOLUMESLIMING DOWN + VIBRATO...

cmp al,6
jne trfraiche2g
shr ax,8
;******* s'occupe du volume sliming ******
;push ax

and ax,01111B
;on a dans ax la vitesse du volumesliming down...

mov es:[table_de_saut+bp],offset fx_volumeslimingdown_vibrato_GUS
mov es:[adder_effect_entre_ligne+bp],ax ;definis la vitesse...
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

;pop ax
;******** s'occupe du vibrato ************
; NON !! dans FT2 ya pas de changement de vitesse de vibrato possible ici...
;donc on fait rien

jmp rfin_proc_effet1
trfraiche2g:

;************** effet 7, TREMOLO
;effect qui dure entre les lignes...

cmp al,07
jne irfraiche2c2_fg

push ax
xor eax,eax
pop ax

push ax
shr ax,8
and ax,01111B ;ici on a donc Y profondeur
mov es:[TREMOLO_fx_prof+bp],ax
pop ax

shr ax,8+4    ;ici on a donc X vitesse
mov es:[TREMOLO_fx_speed+bp],ax

call calcule_la_duree_dun_tick

;call affsigne
;dans ax on a le nombre de TREMOLO compteur a passer pour faire a un tick.
;on doit diviser ca parla vitesse du truc


xor dx,dx
mov bx,es:[TREMOLO_fx_speed+bp]
or bx,bx
jz irtrttterertrteg
div bx
jmp irererererg
irtrttterertrteg:
mov ax,es:[TREMOLO_compteur_save+bp] ;si la vitesse=0 on reprend la derniere
                                     ;vitesse k'on a eu...
irererererg:

;attention:cas particlier:si la zik etait tres rapide...
;il est possible ke la division donne zero (c'est a dire k'il faudrait une
;modif plus souvent ke le le player est appele en hz..on reduira donc a un fois...)
or ax,ax
jnz erreerththrtr
mov ax,1
erreerththrtr:

mov es:[TREMOLO_compteur_save+bp],ax
mov es:[TREMOLO_compteur+bp],ax

mov es:[table_de_saut+bp],offset TREMOLO_fx_gus

jmp rfin_proc_effet1
irfraiche2c2_fg:


;************** effet 8, SET PANNING POSITION (que ger‚ en GUS!)
;               BALANCe GAUCHE/DROITE
cmp al,08
jne rtrfraiche2ct

and eax,01111111100000000B
shr eax,8+4 ;sur GUS va de 0 a 16...

mov bx,bp
shr bx,1
;bx=voix
;ax=valeur panning...

call balance

jmp rfin_proc_effet1
rtrfraiche2ct:

;************** effet 9,definir offset sample.

cmp al,09
jne trfraiche2ct

;on doit mutliplier par 256 l'operante...
;ca equivaut:
and eax,01111111100000000B

push bp
mov bx,bp
;shl bx,1
add bx,bx

mov bp,bx
mov ebx,es:[gus_adresse_fin_sample_GUS+bp]
sub ebx,es:[gus_adresse_debut_sample_GUS+bp]
pop bp

cmp eax,ebx       ;cas particluier verifie ke l'offset demande est pas hors du sample.
ja tbien_sur      ;si c'est le cas on arrete le sample

tcbononyvamapoule:


push bp

mov bx,bp ;voix*2
;shl bx,1  ;voix*4
add bx,bx  ;voix*4
mov bp,bx ;bp=voix*4
shr bx,2  ;bl=voix*1

;**** ETTEINT D'ABORD LA VOIX
push ax bx
mov al,1 ;mode etteint voix
call BALANcE_VOIX
pop bx ax
;****


add eax,es:[gus_adresse_debut_sample_GUS+bp]
mov edx,es:[gus_adresse_fin_sample_GUS+bp]
mov ecx,es:[gus_adresse_loop_sample_GUS+bp]

push bx
call def_voix
pop bx
;**** REALLUME D'ABORD LA VOIX
mov al,0 ;allume
call BALANcE_VOIX
;****


pop bp

jmp rfin_proc_effet1

tbien_sur:
;il faut arreter le sample...
;etteint voix
mov bx,bp
shr bx,1
mov al,1
call BALANcE_VOIX

;etteint voix

jmp rfin_proc_effet1
trfraiche2ct:

;************** effet A (10),VOLUMESLIMING.
;pas besoin du converisseur de parametre...
;effect qui dure entre les lignes...
;peut etre up ou down...en fonction du parametre (xxxxYYYY)
;(si c'est en xxxx c'est up a la vitesst xxxx)


cmp al,0Ah
jne trfraiche2

shr ax,8 ;

cmp ax,0fh
ja tlaondoitmonterleson
;
;call affsigne

mov es:[table_de_saut+bp],offset fx_volumeslimingdown_GUS
mov es:[adder_effect_entre_ligne+bp],ax ;definis la vitesse...
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

jmp tcestpartis
tlaondoitmonterleson:
shr ax,4
;call affsigne
mov es:[table_de_saut+bp],offset fx_volumeslimingup_GUS
mov es:[adder_effect_entre_ligne+bp],ax ;definis la vitesse...
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

tcestpartis:


;cmp ax,64
;ja rya_un_prob_mieux_vaut_rien_faire
;mov es:[volume_de_la_voix+bp],ax
;rya_un_prob_mieux_vaut_rien_faire:
jmp rfin_proc_effet1
trfraiche2:


;************** effet B (11),position jump
;effet_B dw 0,0  ;premier mot: 0=pas active,1=active
;                ;deuxieme mot: numero le la ligne ou on se place dans la
;                ;pattern suivante...

;a PAS besoin du converisseur de parametre...
cmp al,0Bh
jne trfraicher4
shr ax,8 ;


;call affsigne
mov bx,es:[nombre_total_de_pattern_chanson]
cmp ax,bx

jb tcokcdanslarrangement
;si c'est pas dans l'arrangement on met au 1er pattern de l'arrangement pattern
xor ax,ax
tcokcdanslarrangement:
mov es:[effet_B],1 ; db 0,0  ;premier mot: 0=pas active,1=active
mov es:[effet_B+2],ax ;
jmp rfin_proc_effet1
trfraicher4:

;************** effet C (12),changement du volume d'un voix
;a pas besoin du converisseur de parametre...
cmp al,0Ch
jne trfraiche
shr ax,8 ;
;
;call affsigne

cmp ax,64
ja trya_un_prob_mieux_vaut_rien_faire
mov es:[volume_de_la_voix+bp],ax

push ax
;VOLUME_DUNE_VOIX
mov ax,bp ;VOIX*2
shr ax,1  ;voix
pop bx    ;AL=VOIX
mov ah,bl ;AH=volume...

call volume_dune_voix

trya_un_prob_mieux_vaut_rien_faire:
jmp rfin_proc_effet1
trfraiche:

;************** effet D (13),pattern break.
;egghffgffet_D db 0,0  ;premier octet: 0=pas active,1=active
;      ghf          ;deuxieme octet: numero le la ligne ou on se place dans la
;dffd        fghfgh dw 0    ;mot: viseur_dans_arrangement comme on se placera ensuite...
;    dfdf           ;pattern suivante...
;a besoin du converisseur de parametre...
cmp al,0Dh
jne trfraicher
shr ax,8 ;

;call num
;call affsigne

cmp ax,63
;pour l'effet D,le parametre est dans le fichier comme du decimal pris pour
;de l'hexa!!! bizarre..

ja trya_un_prob_mieux_vaut_rien_fairer
mov es:[effet_D],1 ; db 0,0  ;premier mot: 0=pas active,1=active
mov es:[effet_D+2],aX ;

mov ax,es:[nombre_total_de_pattern_chanson] ;
mov bx,es:[viseur_dans_arrangement_chanson]
inc bx
cmp bx,ax
jb tcokoncointinure
xor bx,bx
tcokoncointinure:
mov es:[effet_D+4],bx ;

trya_un_prob_mieux_vaut_rien_fairer:
jmp rfin_proc_effet1
trfraicher:
;-------------------------------------------------

cmp al,0Eh ;test pour sauter le gros tas de E!!!
je okokokokok2
jmp okokokokok2passetouslesE2
okokokokok2:

;************** effet E (14) E.1 et 2 14.1 et 2 FINESLIDE UP et DOWN****
cmp al,0Eh
jne ttdepressed33t
mov bx,ax   ;sauvegarde ax...
shr ax,8+4
cmp ax,01
je ttdepressed233t
cmp ax,02
je ttdepressed233t2
mov ax,bx
jmp ttdepressed33t
ttdepressed233t:
;.......Up
shr bx,8
and bx,01111B ;parametre..

add es:[portamento_gus+bp],bx ;arbitraire rulz!
add es:[portamento_gus+bp],bx
add es:[portamento_gus+bp],bx

;................ frequence/note
mov bx,bp ;numero de voix*2
shr bx,1
;dans bl numero de voix

mov dx,es:[SAUVE_VISEUR_DANS_SBFREQ+BP]
shl dx,8
or  bx,dx

;*********
;FREQ_VOIX:
;entree bl:numero de la voix...
;dans bh: ce kon doit utiliser pour piocher la frequence dans gusfreq
;         BRUT! tel k'il est dans les pattern format remdy.
;         (on va le multiplier par 4 ensuite...)
;

mov cx,es:[portamento_gus+bp]
call FREQ_VOIX

jmp rfin_proc_effet1
;..............DOWN
ttdepressed233t2:

shr bx,8
and bx,01111B ;parametre..

sub es:[portamento_gus+bp],bx ;arbitraire rulz!
sub es:[portamento_gus+bp],bx
sub es:[portamento_gus+bp],bx

;................ frequence/note
mov bx,bp ;numero de voix*2
shr bx,1
;dans bl numero de voix

mov dx,es:[SAUVE_VISEUR_DANS_SBFREQ+BP]
shl dx,8
or  bx,dx

;*********
;FREQ_VOIX:
;entree bl:numero de la voix...
;dans bh: ce kon doit utiliser pour piocher la frequence dans gusfreq
;         BRUT! tel k'il est dans les pattern format remdy.
;         (on va le multiplier par 4 ensuite...)
;

mov cx,es:[portamento_gus+bp]
call FREQ_VOIX

jmp rfin_proc_effet1

ttdepressed33t:


;************** effet E (14) 14.4 SELECTIONNE LE TYPE DE VIBRATO ****
cmp al,0Eh
jne tfdepressed
mov bx,ax   ;sauvegarde ax...
shr bx,8+4  ;1er parametre doit etre egal a 4.
cmp bx,4
jne tfdepressed

shr ax,8
and ax,0001111B
;call affsigne

cmp ax,0
jne terrererr
mov ax,offset VIBRATO_SIN
mov es:[what_vibrato],ax
terrererr:


cmp ax,1
jne terrerer
mov ax,offset VIBRATO_1
mov es:[what_vibrato],ax
terrerer:

cmp ax,2
jne terrerer2
mov ax,offset VIBRATO_2
mov es:[what_vibrato],ax
terrerer2:


mov es:[VIBRATO_viseur+bp],0
jmp rfin_proc_effet1
tfdepressed:


;************** effet E (14) 14.6 LOOP ****
cmp al,0Eh
jne jdepressed
mov bx,ax   ;sauvegarde ax...
shr ax,8+4  ;1er parametre doit etre egal a 6 sinon c'est pas une LOOP...
cmp ax,6
je jdepressed2
mov ax,bx
jmp jdepressed
jdepressed2:
;------ ON A BIEN une loop,2 possibilites:
;      1ø) marquage du debut d'une loop.
;      2ø) saut dans une loop
shr bx,8           ;
and bx,0001111B    ;2eme parametre:  si =0 ca veut dire ligne a conserver
                   ;                 si <>0 ca veut dire nombre de fois k'on
                   ;                 doit retourner a la ligne conservee.
cmp bx,0
jne jnonon_cpaslapermierepzrtieduloop
;------ 1ø) ICI il faut juste conserver

mov eax,es:[numero_de_ligne_dans_pattern]
mov es:[FXLOOP2],eax

jmp rfin_proc_effet1
jnonon_cpaslapermierepzrtieduloop:
;2ø) dans bx on a le nombre de fois k'il faut sauter...

cmp es:[FXLOOP1],-1 ;on a cette valeur juste au debut...
                    ;une fois k'on a sauvegarde elle n'y est plus...
jne jbreuuuuuuuuuuuuuuu
mov es:[FXLOOP1],bx ;on sauvegarde le nombre de fois k'on doit sauter.
                    ;il ne faut faire cette sauvegarde k'au premier passage.
jbreuuuuuuuuuuuuuuu:

cmp es:[FXLOOP1],0  ;si c'est a la fin de la boucle il faut arreter de sauter.
je jrfrrerererere    ;
mov es:[effet_E6],1 ;indique a la procedure ki va suivre de sauter
dec es:[FXLOOP1]    ;on decremente le nombre de fois k'il faut sauter
jmp rfin_proc_effet1
jrfrrerererere:
mov es:[FXLOOP1],-1 ;permet d'avoir d'autres boucles ensuite.
jmp rfin_proc_effet1
jdepressed:

;************** effet E (14) 14.7 SELECTIONNE LE TYPE DE TREMOLO ****
cmp al,0Eh
jne rfdepressedh
mov bx,ax   ;sauvegarde ax...
shr bx,8+4  ;1er parametre doit etre egal a 4.
cmp bx,7
jne rfdepressedh

shr ax,8
and ax,0001111B
;call affsigne

cmp ax,0
jne rerrererrh
mov ax,offset VIBRATO_SIN
mov es:[what_TREMOLO],ax
rerrererrh:


cmp ax,1
jne rerrererh
mov ax,offset VIBRATO_1
mov es:[what_TREMOLO],ax
rerrererh:

cmp ax,2
jne rerrerer2h
mov ax,offset VIBRATO_2
mov es:[what_TREMOLO],ax
rerrerer2h:

mov es:[TREMOLO_viseur+bp],0
jmp rfin_proc_effet1
rfdepressedh:

;************** effet E (14) E.9 14.9 NOTE RETRIGGERING ****
;retappe la note a partir d'un certain battement.

cmp al,0Eh
jne trkdepressed33
mov bx,ax   ;sauvegarde ax...
shr ax,8+4
cmp ax,9
je trkdepressed233
mov ax,bx
jmp trkdepressed33
trkdepressed233:

shr bx,8
and bx,01111B ;parametre..

;****
cmp bx,es:[speed_song]
jb toutevotreviet
jnz toutevotreviet
;cas aussi un peu particulier... speed_song>ou= a parametre
;on fait rien...
jmp rfin_proc_effet1
toutevotreviet:

;mov ax,bx
;call affsigne

;on va calculer le temps k'il faut attendre...
xor eax,eax
call calcule_la_duree_dun_tick
mul bx

mov ebx,es:[SPEED_COMPTEUR]
sub ebx,eax
;donc on devra attendre juska ce ke speed compteur soit egal a ebx!!

mov si,offset NOTE_RETRIG
add si,bp
add si,bp
mov es:[si],ebx

mov es:[table_de_saut+bp],offset fx_noteRETRIG_GUS

jmp rfin_proc_effet1

trkdepressed33:


;************** effet E (14) E.A/B 14.10/11 FINE VOLUMESLIDING UP+DOWN ****
cmp al,0Eh
jne rtdepressed33
mov bx,ax   ;sauvegarde ax...
shr ax,8+4
cmp ax,010
je rtdepressed233

cmp ax,0bh
je rtdepressed233b

mov ax,bx
jmp rtdepressed33
rtdepressed233:

shr bx,8
and bx,01111B ;parametre..

;call affsigne

add es:[volume_de_la_voix+bp],bx
cmp es:[volume_de_la_voix+bp],64
jna rfinirerere
mov es:[volume_de_la_voix+bp],64
rfinirerere:
jmp rfinirererer

rtdepressed233B:

shr bx,8
and bx,01111B ;parametre..

;call affsigne

sub es:[volume_de_la_voix+bp],bx
cmp es:[volume_de_la_voix+bp],0
jns rfinirererer
mov es:[volume_de_la_voix+bp],0
rfinirererer:

mov ax,bp ;dans ax:numero de voix *2
shr ax,1  ;dans ax:numero de voix
mov bx,es:[volume_de_la_voix+bp]
shl bx,8
or  ax,bx

;VOLUME_DUNE_VOIX PROC NEAr
;
;mov al,0  ;VOIX
;mov ah,63 ;VOLUME
call volume_dune_voix


jmp rfin_proc_effet1

rtdepressed33:

;************** effet E (14) E.C 14.12 NOTE CUT ****
cmp al,0Eh
jne rdepressed33
mov bx,ax   ;sauvegarde ax...
shr ax,8+4
cmp ax,0ch
je rdepressed233
mov ax,bx
jmp rdepressed33
rdepressed233:
;on devra arreter la note a
;(SPEED_COMPTEUR_SAVE)-(duree d'un tick*parametre)

shr bx,8
and bx,01111B ;parametre..

cmp bx,es:[speed_song]
jb toutevotrevie
;cas aussi un peu particulier... speed_song>ou= a parametre
;on fait rien...

jmp rfin_proc_effet1
toutevotrevie:
or bx,bx
jnz noncpaszero
;....cas un peu particluier: si le parametre est egal a 0 on coupe la note de
; suite (pas vraiment particluier mais insdispencable a cause le l'aproximation.
mov ebx,es:[SPEED_COMPTEUR]
dec ebx
mov si,offset SPEED_COMPTEUR_TEST_EFFET12
add si,bp
add si,bp
mov es:[si],ebx

mov es:[table_de_saut+bp],offset fx_notecut_GUS

jmp rfin_proc_effet1
;..........................

noncpaszero:
xor eax,eax
call calcule_la_duree_dun_tick
mul bx
;call num
mov ebx,es:[SPEED_COMPTEUR]
sub ebx,0 ;5 ;car calcule_la_duree_dun_tick approximatif

sub ebx,eax
;donc on devra arreter la note une fois arrive a speed_compteur=ebx

;dec ebx ;de 1 car chiant kan c'etait juste (vitesse et parametre egal-->note
;jouee en entier...)

mov si,offset SPEED_COMPTEUR_TEST_EFFET12
add si,bp
add si,bp
mov es:[si],ebx

mov es:[table_de_saut+bp],offset fx_notecut_GUS

;speed_song   dw  6
;speed_compteur_save dd 1200 ;vitesse 6 par default.

;dans ax:resultat
; SPEED_resultat: a partir dukel
;call num

jmp rfin_proc_effet1

rdepressed33:

;************** effet E (14) E.D 14.13 NOTE DELAY ****
;le parametre Y indique le nombre de ticks pendant lequels il faut
;retarder la voix...

cmp al,0Eh
jne hkdepressed33
mov bx,ax   ;sauvegarde ax...
shr ax,8+4
cmp ax,0dh
je hkdepressed233
mov ax,bx
jmp hkdepressed33
hkdepressed233:

shr bx,8
and bx,01111B ;parametre..
;mov ax,bx
;call affsigne

;on va calculer le temps k'il faut attendre...
xor eax,eax
call calcule_la_duree_dun_tick
mul bx

inc eax
mov ebx,es:[SPEED_COMPTEUR]
sub ebx,eax
;donc on devra attendre juska ce ke speed compteur soit egal a ebx!!

mov si,offset NOTE_DELAY
add si,bp
add si,bp
mov es:[si],ebx

mov es:[table_de_saut+bp],offset fx_notedelay_gus

;**** ETTEINT D'ABORD LA VOIX
mov bx,bp
shr bx,1
mov al,1 ;mode etteint voix
call BALANcE_VOIX
;****

;mov NOTE_DELAY2 dw 4 DUP (0) ;pour sauver sample_joue_en_ce_moment dw 4 dup (0)

;0FFFFh
;NOTE_DELAY dd 4 DUP (0)
;NOTE_DELAY2 dw 4 DUP (0) ;pour sauver sample_joue_en_ce_moment dw 4 dup (0)
;                         ;et on met 0 le temps k'on attend.

jmp rfin_proc_effet1

hkdepressed33:


;************** effet E (14) E.E 14.14 DELAI POUR LE PATTERN ****
;note: on attend pas le nombre de beats (tick) donnes mais plutot le nombre
;de Notes comme le fait FT2. year.

cmp al,0Eh
jne gdepressed3
mov bx,ax   ;sauvegarde ax...
shr ax,8+4  ;1er parametre doit etre egal a 0eh

cmp ax,0Eh
je gdepressed23
mov ax,bx
jmp gdepressed3
gdepressed23:
shr bx,8
and bx,01111B
or bx,bx
jz gdepressed3 ;si c'est 0 on change rien...

mov eax,es:[speed_compteur_save]
cmp word ptr es:[speed_compteur_save+2],0 ;cas particulier non prevu mais
                                 ; n'arrivant
                                 ;jamais:speed_compteur_save > a 0FFFFh
jne gfin_p                        ;

mul bx
mov word ptr es:[speed_compteur],ax
mov word ptr es:[speed_compteur+2],dx

gfin_p:
jmp rfin_proc_effet1
gdepressed3:

okokokokok2passetouslesE2:
;*******************************************************************1
;************** effet F (15),changement de la vitesse d'execution
;a besoin du convertisseur de parametre...
;
;deux action differante celui le parametre:
; <32: nouvelle SPEED_SONG dans parametre (valeurs:0 a 31)
; =>32 :nouvelle BMP_SPEED dans parametre (valeur:32 a 0FFH)

cmp al,0Fh
jne yfraiche
shr ax,8 ;
;call affsigne
cmp ax,31
ja yla_il_faut_carement_changer_le_bmp
mov es:[speed_song],ax
;call affsigne

shl ax,2 ;multiplie par 4...

mov di,offset Speed_wait
add di,ax

mov eax,es:[speed_compteur_save]
mov eax,es:[di]

mov es:[speed_compteur_save],eax
mov es:[speed_compteur],eax

jmp rfin_proc_effet1

yla_il_faut_carement_changer_le_bmp:
mov es:[bmp_speed],al
push ax
and al,011111111B
;call affsigne
pop ax
call calc_new_speed_GUS    ;calcule un nouvelle table de speed.
                       ;il_faut_maintenant_mettre_a_jour_le_speed_compteu
mov ax,es:[speed_song]
shl ax,2 ;multiplie par 4...
mov di,offset Speed_wait
add di,ax
mov eax,es:[di]
;call num
mov es:[speed_compteur_save],eax
mov es:[speed_compteur],eax

call calcule_la_duree_dun_tick
mov es:[compteur_effect_entre_ligne_save],ax
jmp rfin_proc_effet1
yfraiche:
;*****************

rfin_proc_effet1:
pop bx si eax di
ret
effets1_GUS endp

fx_arpegio_GUS proc near
;,mov ax,rmd_data
;mov es,ax
mov si,offset compteur_pour_arpegio2
add si,bp
add si,bp

dec dword ptr es:[si]
jnz tfrtrertr                   ;pour arreter a la fin...
mov dword ptr es:[si],1         ;avant la prochaine ligne il faut
mov eax,0                       ;se retrouver avec l'ancienne bonne valeur.
jmp trtrtrtrt_onŠfait_ca_a_la_fin

tfrtrertr:

mov si,offset compteur_pour_arpegio
add si,bp
add si,bp
mov eax,es:[si]

inc es:[compteur_pour_arpegio3+BP]

mov bx,es:[compteur_effect_entre_ligne_save]

cmp es:[compteur_pour_arpegio3+BP],bx ;DUREE D'un BEAT!
je trreer
ret ;sinon ya rien a changer...
trreer:
inc eax

mov es:[compteur_pour_arpegio3+BP],0


cmp eax,3
jne terreer
mov eax,0
terreer:
mov es:[si],eax
trtrtrtrt_onŠfait_ca_a_la_fin:

cmp eax,1
je taide_memoire2
cmp eax,2
je taide_memoire3
;cmp eax,0
;je taide_memoire1


taide_memoire1:

mov si,offset FREQUENCE_POUR_LES_3_NOTES1
add si,bp
add si,bp
mov eax,es:[si]
;en fait adder...
mov bx,bp
shr bx,1

mov bh,al

;*********
;FREQ_VOIX:
;entree bl:numero de la voix...
;dans bh: ce kon doit utiliser pour piocher la frequence dans gusfreq
;         BRUT! tel k'il est dans les pattern format remdy.
;         (on va le multiplier par 4 ensuite...)

mov cx,es:[portamento_gus+bp]
call FREQ_VOIX


ret

taide_memoire2:

mov si,offset FREQUENCE_POUR_LES_3_NOTES2
add si,bp
add si,bp
mov eax,es:[si]

;en fait adder...
mov bx,bp
shr bx,1

mov bh,al

;*********
;FREQ_VOIX:
;entree bl:numero de la voix...
;dans bh: ce kon doit utiliser pour piocher la frequence dans gusfreq
;         BRUT! tel k'il est dans les pattern format remdy.
;         (on va le multiplier par 4 ensuite...)

mov cx,es:[portamento_gus+bp]
call FREQ_VOIX

ret

taide_memoire3:

mov si,offset FREQUENCE_POUR_LES_3_NOTES3
add si,bp
add si,bp
mov eax,es:[si]

;en fait adder...
mov bx,bp
shr bx,1

mov bh,al

;*********
;FREQ_VOIX:
;entree bl:numero de la voix...
;dans bh: ce kon doit utiliser pour piocher la frequence dans gusfreq
;         BRUT! tel k'il est dans les pattern format remdy.
;         (on va le multiplier par 4 ensuite...)

mov cx,es:[portamento_gus+bp]
call FREQ_VOIX

ret

fx_arpegio_GUS endp

fx_notedelay_GUS proc near

;kan cv'est fini on remet comme avant...

mov ebx,es:[SPEED_COMPTEUR]
mov si,offset NOTE_DELAY
add si,bp
add si,bp
cmp es:[si],ebx
jne gnonono_faut_encore_attendre

;**** REMET LA VOIX
mov bx,bp
shr bx,1
mov ax,es:[NOTE_DELAY2+bp] ;ou on a sauvegarde si la voix est en mode loop ou non
call BALANcE_VOIX
;****

gnonono_faut_encore_attendre:

;NOTE_DELAY dd 4 DUP (0)
;NOTE_DELAY2 dw 4 DUP (0) ;pour sauver sample_joue_en_ce_moment dw 4 dup (0)
;                         ;et on met 0 le temps k'on attend.

ret
fx_notedelay_GUS endp



calc_new_speed_GUS proc near ;pour calculer une nouvelle table de speed.
;lorsque l'on change le BMP du fichier...
push ax di si cx dx bx
;BMP_SPEED    db  125
;
;                    0        1     2      3      4      5      6      7
;SPeed_wait2  dd 0FFFFFFFFh,025000,050000,075000,100000,125000,150000,175000
;                      8      9     10     11     12     13     14     15
;                 dd 200000,225000,250000,275000,300000,325000,350000,375000
;                      16     17    18     19     21     22     23     24
;                 dd 400000,425000,450000,475000,500000,525000,550000,575000
;                      25     26    27     28     29     30     31
;                 dd 600000,625000,650000,675000,700000,725000,750000
mov ax,rmd_data
mov es,ax

mov di,offset speed_wait2+4     ;source
mov si,offset speed_wait+4
mov cx,31 ;31
grand_prixl:
mov eax,es:[di]

;call num

shr eax,3 ;DIVISE PAR 8 CAR c'EST pour la GUS!!!


;push ax
;shr ax,16
;mov dx,ax
;pop ax
;
xor edx,edx
xor ebx,ebx
mov bl,es:[bmp_speed]

div ebx

mov es:[si],ax
;call affsigne
add di,4
add si,4
dec cx
jnz grand_prixl
pop bx dx cx si di ax
ret
calc_new_speed_GUS endp
fx_notecut_GUS proc near

mov si,offset SPEED_COMPTEUR_TEST_EFFET12
add si,bp
add si,bp
mov ebx,es:[SI]
cmp ebx,es:[SPEED_COMPTEUR]
jne rpubrererer

;**** ETTEINT D'ABORD LA VOIX
mov bx,bp
shr bx,1
mov al,1 ;mode etteint voix
call BALANcE_VOIX
;****

rpubrererer:
ret
fx_notecut_GUS endp

fx_noteretrig_GUS proc near

mov ebx,es:[SPEED_COMPTEUR]
mov si,offset NOTE_RETRIG
add si,bp
add si,bp
cmp es:[si],ebx
jne rnonono_faut_encore_attendrer

;MOV es:[OFFSET_SAMPLE+bp],0

mov bx,bp ;dans bl=numero de VOIX
shr bx,1
;*********
;DEF_VOIX:
;entree bl:numero de la voix...
;eax: adresse du debut du sample dans la gus k'on veut jouer...
;edx: adresse de la fin du sample dans la gus k'on veut jouer...
;ecx: adresse de la boucle dans le sample dans la gus k'on veut jouer...


;;**** ETTEINT D'ABORD LA VOIX
;push ax
;mov al,1 ;mode etteint voix
;call BALANcE_VOIX
;pop ax
;****
push bp
;dans bp on doit mettre le numero du sample joue..*4

push ax
mov ax,es:[sample_joue_en_ce_moment+bp]  ;+numero voix*2
shl ax,2
mov bp,ax
pop ax

mov eax,es:[adresse_debut_sample_GUS+bp]
mov edx,es:[adresse_fin_sample_GUS+bp]
mov ecx,es:[adresse_loop_sample_GUS+bp]

call def_voix
pop bp
rnonono_faut_encore_attendrer:

ret
fx_noteretrig_GUS endp

volumesliming_gus proc near
;mov ah,63 ;valeur d'arrivee
;al=voix

movzx bx,ah

mov dx,es:[gus_voice] ;choisis la voix
out dx,al
;definit facteur de ramping
mov dx,es:[gus_command]
mov al,6
out dx,al
mov dx,es:[gus_datahi]

mov al,000111111B ;facteur ;!!!
out dx,al

;------------- modif volume actuel ---
mov dx,es:[gus_command]
mov al,9
out dx,al
mov dx,es:[gus_datahi]

;mov ax,63
;mov di,offset TABLE_Volumes_GUS
;shl ax,1
;add di,ax
;mov al,es:[di]
mov al,010010B ;es:[volume_de_la_voix+bp]
out dx,al
;-------------


mov dx,es:[gus_command]
mov al,7
out dx,al
mov dx,es:[gus_datahi]

;mov ax,010010B ;es:[volume_de_la_voix+bp]

;mov ax,0
;mov di,offset TABLE_Volumes_GUS
;shl ax,1
;add di,ax
;mov al,es:[di]
mov ax,010010B ;es:[volume_de_la_voix+bp]

Out dx,al

mov dx,es:[gus_command]
mov al,8
out dx,al
mov dx,es:[gus_datahi]

mov ax,bx         ;volume arrive
mov di,offset TABLE_Volumes_GUS
;shl ax,1
add ax,ax

add di,ax
mov ax,es:[di]
shr ax,8
out dx,al

mov dx,es:[gus_command]
mov al,0dh
out dx,al
mov dx,es:[gus_datahi]
mov al,00000000B ;sens ramping
out dx,al
call delay

mov dx,es:[gus_command]
mov al,0dh
out dx,al
mov dx,es:[gus_datahi]
mov al,00000000B ;sens ramping
out dx,al
ret
volumesliming_gus endp

fx_volumeslimingup_GUS proc near

mov ax,es:[compteur_effect_entre_ligne+bp]
sub ax,es:[adder_effect_entre_ligne+bp]
jns tnon_pas_deffet
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

cmp es:[volume_de_la_voix+bp],63
ja tnon_le_volume_est_deja_a_fond
inc es:[volume_de_la_voix+bp]

mov bx,es:[volume_de_la_voix+bp]
shl bx,8
mov ax,bp
shr ax,1
or  ax,bx

call VOLUME_DUNE_VOIX
;mov al,0  ;VOIX
;mov ah,63 ;VOLUME


tnon_le_volume_est_deja_a_fond:
ret

tnon_pas_deffet:
mov es:[compteur_effect_entre_ligne+bp],ax
ret
fx_volumeslimingup_GUS endp

fx_volumeslimingdown_GUS proc near

mov ax,es:[compteur_effect_entre_ligne+bp]
sub ax,es:[adder_effect_entre_ligne+bp]
jns tnon_pas_deffet2
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax


cmp es:[volume_de_la_voix+bp],0
je tnon_le_volume_est_deja_a_zero
dec es:[volume_de_la_voix+bp]

mov bx,es:[volume_de_la_voix+bp]
shl bx,8
mov ax,bp
shr ax,1
or  ax,bx

call VOLUME_DUNE_VOIX

tnon_le_volume_est_deja_a_zero:

ret
tnon_pas_deffet2:
mov es:[compteur_effect_entre_ligne+bp],ax
ret

fx_volumeslimingdown_GUS endp

;bx=voix
;ax=valeur panning...
balance proc near

push ax bx dx
push ax

mov dx,es:[gus_voice] ;choisis vOIX!
mov al,bl
out dx,al
mov dx,es:[gus_command]
mov al,0ch
out dx,al
mov dx,es:[gus_datahi]
pop ax
out dx,al
pop dx bx ax

ret
balance ENDP

TREMOLO_fx_gus proc near

dec es:[TREMOLO_compteur+bp]
jz ierereerret
ret
ierereerret:
mov ax,es:[TREMOLO_compteur_save+bp]
mov es:[TREMOLO_compteur+bp],ax

xor eax,eax
add es:[TREMOLO_viseur+bp],2
cmp es:[TREMOLO_viseur+bp],64*2
jne imariat
mov es:[TREMOLO_viseur+bp],0
imariat:
mov bx,es:[TREMOLO_viseur+bp]

mov si,es:[WHAT_TREMOLO]

mov ax,es:[si+bx]
or ax,ax
jns irrereererer
neg ax
mov bx,es:[TREMOLO_fx_prof+bp]

mul bx
shr ax,7  ;normallement ca devrait etre 8
          ;mais peut etre ke le parametre de vitesse doit pas etre deplace
neg ax
add ax,es:[volume_de_la_voix+bp]

cmp ax,64
jb ie1234e
mov ax,0;63
ie1234e:
mov es:[volume_de_la_voix+bp],ax
shl ax,8
mov bx,bp
shr bx,1
mov al,bl
;mov al,0  ;VOIX
;mov ah,63 ;VOLUME
call VOLUME_DUNE_VOIX

ret

irrereererer: ;pas de signe

mov bx,es:[TREMOLO_fx_prof+bp]

mul bx
shr ax,7  ;normallement ca devrait etre 8
         ;mais peut etre ke le parametre de vitesse doit pas etre deplace

add ax,es:[volume_de_la_voix+bp]
cmp ax,64
jb ie1234er
mov ax,64
ie1234er:
mov es:[volume_de_la_voix+bp],ax
shl ax,8
mov bx,bp
shr bx,1
mov al,bl
;mov al,0  ;VOIX
;mov ah,63 ;VOLUME
call VOLUME_DUNE_VOIX

ret

TREMOLO_fx_gus endp

fx_portamento_updown_GUS proc near

dec es:[compteur_effect_entre_ligne+bp]
jz famet
ret
famet:
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

mov bx,es:[adder_effect_entre_ligne+bp]
add bx,es:[adder_effect_entre_ligne+bp]
add bx,es:[adder_effect_entre_ligne+bp]

or bx,bx   ;pour obtenir un facteur de 1,5... (ave ce k'il y a au dessus)
js hiiiiu
shr bx,1
jmp iiiihhy
hiiiiu:
neg bx
shr bx,1
neg bx
iiiihhy:


or bx,bx
js yeaaaaar ;il faut sauter le test ki suit si c'est negatif
cmp es:[portamento_gus+bp],10000 ;arbitraire rulz!
ja k_choice
yeaaaaar:
add es:[portamento_gus+bp],bx ;arbitraire rulz!
;add es:[portamento_gus+bp],bx ;arbitraire rulz!
;add es:[portamento_gus+bp],bx ;arbitraire rulz!
k_choice:


mov bx,bp
shr bx,1

mov ax,es:[SAUVE_VISEUR_DANS_SBFREQ+BP]
shl ax,8
or bx,ax

mov cx,es:[portamento_gus+bp]

call FREQ_VOIX

ret
fx_portamento_updown_GUS endp

vibrato_fx_GUS proc near

;VIBRATO_viseur          dw 4 DUP (0) ;viseur dans tablos.
;vibrato_fx_prof         dw 4 DUP (0) ;pour sauvegarde des info sur
;vibrato_fx_speed        dw 4 DUP (0) ;le vibrato en cours!

cmp es:[speed_compteur],0
jne lzezeezrzzeezze

mov ax,es:[SAVE_PORTO_VIBRATO+BP]
mov es:[vibrato_gus+bp],ax

mov bx,bp
shr bx,1
mov ax,es:[SAUVE_VISEUR_DANS_SBFREQ+BP]
shl ax,8
or bx,ax
mov cx,es:[portamento_gus+bp]
add cx,es:[vibrato_gus+bp]
call FREQ_VOIX
;call num

ret
lzezeezrzzeezze:

dec es:[VIBRATO_compteur+bp]
jz lerereerre
ret
lerereerre:
mov ax,es:[VIBRATO_compteur_save+bp]
mov es:[VIBRATO_compteur+bp],ax

add es:[VIBRATO_viseur+bp],2
cmp es:[VIBRATO_viseur+bp],128*2
jne lmaria
mov es:[VIBRATO_viseur+bp],0
lmaria:
mov bx,es:[VIBRATO_viseur+bp]

mov si,es:[WHAT_VIBRATO]
xor eax,eax
mov ax,es:[si+bx]

or ax,ax
jns lpas_de_signe
mov bx,es:[vibrato_fx_prof+bp]
neg ax
mul bx
;on a dans ax la frequence en HZ a rajouter...
;convertion en HZ remdy
shl eax,8-4
xor edx,edx
mov ebx,10000
div ebx
;call num
neg eax   ;mais peut etre ke le parametre de vitesse doit pas etre deplace
          ;a droite
JMP lLA_FIN
;-*-*-*-*-*-*-*-*-*-*
lpas_de_signe:
mov bx,es:[vibrato_fx_prof+bp]
mul bx
;on a dans ax la frequence en HZ a rajouter...
;convertion en HZ remdy
shl eax,8-4
xor edx,edx
mov ebx,10000
div ebx
;-*-*-*-*-*-*-*-*-*-*
lLA_FIN:
;mov si,offset note_joue_par_sample
;add si,bp
;add si,bp
;add dword ptr es:[si],eax
;jNS lrrereretr22
;sub dword ptr es:[si],eax
;lrrereretr22:

mov es:[vibrato_gus+bp],ax ;arbitraire rulz!
add es:[vibrato_gus+bp],ax ;arbitraire rulz!
shl ax,3
add es:[vibrato_gus+bp],ax ;arbitraire rulz!

mov bx,bp
shr bx,1

mov ax,es:[SAUVE_VISEUR_DANS_SBFREQ+BP]
shl ax,8
or bx,ax

mov cx,es:[portamento_gus+bp]
add cx,es:[vibrato_gus+bp]

call FREQ_VOIX

ret
vibrato_fx_GUS endp

fx_volumeslimingdown_vibrato_GUS proc near

call vibrato_fx_GUS

cmp es:[VIBRATO_compteur_save+bp],0FFFFh ;cas particulier il n'y a pas eu
je rttrrtrtr                             ;de vibrato avant:on fait rien
call fx_volumeslimingdown_GUS
rttrrtrtr:
ret
fx_volumeslimingdown_vibrato_GUS endp

PLAY_BONUS_SAMPLE PROC NEAR

cmp es:[gus_or_sb],2
je onaunesb

cmp es:[gus_or_sb],1
je onaunegus

ret

onaunegus:

push dx ;(1)

;................ frequence/note
mov bx,bp ;numero de voix*2
shr bx,1
;dans bX (bl) numero de voix


push bx ax
mov al,es:[panning_GUS+Bx]
call balance
pop ax bx

mov bh,al

;DAns bh on a le numero de la nouvelle note a jouer...


push ax bx ;.........;met le volume a 0-------
push ax
;VOLUME_DUNE_VOIX
mov ax,bp ;VOIX*2
shr ax,1  ;voix
pop bx    ;AL=VOIX
mov ah,0 ;AH=volume... ;on met
;al=voix
;ah=63 volume
call volume_dune_voix
pop bx ax

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

mov eax,es:[adresse_debut_sample_GUS+bp]
mov edx,es:[adresse_fin_sample_GUS+bp]
mov ecx,es:[adresse_loop_sample_GUS+bp]

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

cmp word ptr es:[longueur_loop_sample+bp],0
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
;******************************* pareil pour la SB.... *****************

onaunesb:

;dans ax:sample k'on va jouer...
;dans bp: numero de la voix * 2 (de 8*2 a 11*2)
;dans bx:numero de la note

;----- Quand on change un sample: cv'est ici k'on change le volume.
;      pas ailleur...on change donc juste:le volume et le prochain sample
;      qui sera joue...


mov es:[sample_joue_en_ce_moment+bp],ax ;+numero voix*2
                                     ;note: si on met 0 il n'y a pas
                                     ;de sample joue du tout.
                                     ;...
                                     ;or si le numero du sample  est a 0
                                     ;ici on se contente de joue du dernier
                                     ;instrument.
or ax,ax ;si c'est l'intrument 0 rien a faire!!! ca veut dire fait rien
jz cdfun

mov dx,ax

;;;shl bx,1
;;;dans bx: numero du sample joue *2 ;!
;;;mov ax,es:[volume_sample+bx] ;(bx=+numero sample*2)

mov es:[volume_de_la_voix+bp],63 ;+numero voix*2

;................ frequence/note
;dans bx on a le numero de la note.

shl bx,2 ;on multiplie par 4 (permet de stocker plus petit!)
mov eax,es:[sbfreq+bx]

mov di,offset note_joue_par_sample    ;+numero voix*4
add di,bp
add di,bp
mov es:[di],eax

;...joue le bon sample...................................
mov bx,dx ;sample joue en ce moment
;shl bx,1
add bx,bx

;dans bx: numero du sample joue *2 ;!

mov ax,es:[longueur_sample+bx] ;(bx=+numero sample*2)
mov es:[longueur_sample_joue+bp],ax ;+numero voix*2

mov ax,es:[depart_loop_sample+bx] ;(bx=+numero sample*2)
mov es:[depart_loop_sample_joue+bp],ax ;+numero voix*2

mov ax,es:[longueur_loop_sample+bx] ;(bx=+numero sample*2)
mov es:[longueur_loop_sample_joue+bp],ax ;+numero voix*2

mov es:[OFFSET_SAMPLE+bp],0             ;+numero voix*2

mov es:[OFFSET_COMPTEUR_SAMPLE+BP],0    ;+numero voix*4

cdfun:
ret

PLAY_BONUS_SAMPLE ENDP


PLAY_BONUS_SAMPLE2 PROC NEAR

cmp es:[gus_or_sb],2
je tonaunesb

cmp es:[gus_or_sb],1
je tonaunegus

ret

tonaunegus:

;................ frequence/note
mov bx,bp ;numero de voix*2
shr bx,1

push bx ax
mov al,es:[panning_GUS+Bx]
call balance
pop ax bx

mov bh,al

push bx dx
xor cx,cx
call FREQ_VOIX
pop dx bx


ret
;******************************* pareil pour la SB.... *****************

tonaunesb:

;dans ax:sample k'on va jouer...
;dans bp: numero de la voix * 2 (de 8*2 a 11*2)
;dans bx:numero de la note

;................ frequence/note
;dans bx on a le numero de la note.

shl bx,2 ;on multiplie par 4 (permet de stocker plus petit!)
mov eax,es:[sbfreq+bx]

mov di,offset note_joue_par_sample    ;+numero voix*4
add di,bp
add di,bp
mov es:[di],eax

ret

PLAY_BONUS_SAMPLE2 ENDP


SYNCHRO PROC NEAR
;line_in_current_played_pattern         dw  0
;number_played_in_pattern_playlist      dw  0
;pattern_number                         dw  0
mov eax,es:[numero_de_ligne_dans_pattern]
mov es:[line_in_current_played_pattern],ax
;call num
;
mov bx,es:[viseur_dans_arrangement_chanson]
xor ax,ax
mov al,es:[arrangement_de_la_chanson+bx]
mov es:[pattern_number],ax
mov es:[number_played_in_pattern_playlist],bx
;call affsigne
;mov ax,bx
;call affsigne
ret
SYNCHRO ENDP
RE_INIT_VARIABLES PROC NEAR
mov ax,rmd_data
mov es,ax
mov ds,ax
mov es:[old_timer_compteur],548
mov es:[old_timer_compteur_GUS],17

mov cx,64
mov di,offset longueur_sample
mov ax,0
rep stosw

mov cx,32
mov di,offset volume_sample
mov ax,0
rep stosw

mov cx,64
mov di,offset longueur_loop_sample
mov ax,0
rep stosw

mov cx,64
mov di,offset segment_sample
mov ax,0
rep stosw

mov cx,12
mov di,offset offset_sample
mov ax,0
rep stosw

mov cx,12
mov di,offset offset_compteur_sample
mov ax,0
rep stosw

mov cx,12
mov di,offset mixage
mov ax,0
rep stosw


mov cx,12
mov di,offset sample_joue_en_ce_moment
mov ax,0
rep stosw

mov cx,12
mov di,offset longueur_sample_joue
mov ax,0
rep stosw

mov cx,12
mov di,offset note_joue_par_sample
mov eax,-1
rep stosd

mov cx,12
mov di,offset volume_de_la_voix
mov ax,0
rep stosw

mov cx,8
mov di,offset sauve_viseur_dans_sbfreq
mov ax,0
rep stosw

mov es:[bmp_speed],125
mov word ptr es:[speed_song],6

mov es:[numero_de_ligne_dans_pattern],0
mov es:[viseur_dans_arrangement_chanson],0

mov cx,3
mov di,offset effet_d
mov ax,0
rep stosw

mov cx,2
mov di,offset effet_b
mov ax,0
rep stosw

mov cx,1
mov di,offset effet_e6
mov ax,0
rep stosw

mov cx,8
mov di,offset table_de_saut
mov ax,offset nopper
rep stosw

mov cx,8
mov di,offset speed_compteur_test_effet12
mov eax,0
rep stosd

mov es:[fxloop1],-1
mov es:[fxloop2],0

mov cx,8
mov di,offset note_delay
mov eax,0
rep stosd

mov cx,8
mov di,offset note_delay2
mov ax,0
rep stosw


mov cx,8
mov di,offset note_retrig
mov eax,0
rep stosd

mov es:[what_vibrato],OFFSET  vibrato_sin

mov cx,8
mov di,offset vibrato_viseur
mov ax,0
rep stosw


mov cx,8
mov di,offset vibrato_fx_prof
mov ax,0
rep stosw

mov cx,8
mov di,offset vibrato_fx_speed
mov ax,0
rep stosw

mov cx,8
mov di,offset vibrato_compteur_save
mov ax,0FFFFh
rep stosw

mov cx,8
mov di,offset vibrato_compteur
mov ax,0
rep stosw


mov cx,8
mov di,offset save_note_vibrato
mov eax,0
rep stosd

mov cx,8
mov di,offset SAVE_NOTE_PORTAMENTO
mov eax,-1
rep stosd

mov cx,8
mov di,offset sauvegarde_de_la_vitesse_du_portamento
mov ax,0
rep stosw

mov es:[what_tremolo],OFFSET  vibrato_sin

mov cx,8
mov di,offset tremolo_viseur
mov ax,0
rep stosw

mov cx,8
mov di,offset tremolo_fx_prof
mov ax,0
rep stosw

mov cx,8
mov di,offset tremolo_fx_speed
mov ax,0
rep stosw

mov cx,8
mov di,offset tremolo_compteur_save
mov ax,0ffffh
rep stosw

mov cx,8
mov di,offset tremolo_compteur
mov ax,0
rep stosw

mov cx,8
mov di,offset save_volume_tremolo
mov ax,0
rep stosw

mov cx,8
mov di,offset portamento_gus
mov ax,0
rep stosw

mov cx,8
mov di,offset vibrato_gus
mov ax,0
rep stosw

mov cx,64
mov di,offset adresse_debut_sample_gus
mov eax,0
rep stosd

mov cx,64
mov di,offset adresse_fin_sample_gus
mov eax,0
rep stosd

mov cx,64
mov di,offset adresse_loop_sample_gus
mov eax,0
rep stosd

mov cx,8
mov di,offset gus_adresse_debut_sample_gus
mov eax,0
rep stosd

mov cx,8
mov di,offset gus_adresse_fin_sample_gus
mov eax,0
rep stosd

mov cx,8
mov di,offset gus_adresse_loop_sample_gus
mov eax,0
rep stosd

mov di,offset BLOW_WHAT
mov cx,3*4
xor ax,ax
rep movsw


ret
RE_INIT_VARIABLES ENDP

