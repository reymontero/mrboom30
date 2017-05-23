;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; PMODE/W Assembly Example File #1
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
.386p

include proc-pm.inc

_TEXT   segment use32 dword public 'CODE'
	assume  cs:_TEXT,ds:_DATA

start:
	jmp short _main

	db 'WATCOM... What me worry?'   ; The "WATCOM" string is needed in
					; order to run under DOS/4G and WD.

;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; CODE
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±

;°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
; Entry To ASM Code (_main)
; In:
;   CS - Code Selector    Base: 00000000h - Limit: 4G
;   DS - Data Selector    Base: 00000000h - Limit: 4G
;   ES - PSP Selector     Base: PSP Seg   - Limit: 100h
;   FS - ?
;   GS - ?
;   SS - Data Selector    Base: 00000000h - Limit: 4G
;   ESP -> STACK segment
;   Direction Flag - ?
;   Interrupt Flag - ?
;
;   All Other Registers Are Undefined!
;°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
_main:
	sti                             ; Set The Interrupt Flag
	cld                             ; Clear The Direction Flag

;include memoire.inc ;resserve la memoire pour les donn‚es --> selector: FS
;                    ;segment video: selector: ES

;load_pcx proc near ; ecx: offset dans le fichier.
;                   ; edx: offset nom du fichier
;
;mov ecx,0
;mov edx,offset fichier2
;mov edi,0
;call load_pcx
;;
;mov ecx,0
;mov edx,offset fichier2
;mov edi,307200
;call load_pcx
;
;
;        mov bx,101h
;        mov ah,04fh ;numero fonction
;        mov al,2    ;sous fonction
;        int 10h
;
;        call affpal
;
;
;retertdgrfgd:
;
;call vbl
;
;mov esi,0
;;===== affiche en ram video ce k'il y a a : FS:ESI
;;      ENTREE : ESI
;call aff_page
;;=================================================
;
;
;;call vbl
;;
;;mov esi,307200
;;;===== affiche en ram video ce k'il y a a : FS:ESI
;;;      ENTREE : ESI
;;call aff_page
;;;=================================================
;
;

;retertdgrfgdr:
;in al,60h
;cmp al,1
;jne retertdgrfgdr
;
;        mov ax,3h
;        int 10h
	mov bp,0
	call detect ;es:PSP

	mov ecx,0
	mov eax,32
	call LOAD_BONUS_SAMPLE

	mov ecx,0
	mov eax,9*4
	call LOAD_BONUS_SAMPLE

;ECX: OFFSET
;! dans EaX NUMERO DU SAMPLE *4 !
;MOV BP,32*4




;BLOW_WHAT    dw   0,0,0  ; 1st FX channel
;              dw   0,0,0  ; 2nd FX channel
;              dw   0,0,0  ; 3rd FX channel
;              dw   0,0,0  ; 4th FX channel

mov byte ptr [BLOW_WHAT],0F8h ;4 bits:panning, 4 bits: sample
mov byte ptr [BLOW_WHAT+1],40  ;0 droite. ici. F left
;mov byte ptr [BLOW_WHAT+12],8 ;8*4
;mov byte ptr [BLOW_WHAT+13],30

;mov byte ptr [BLOW_WHAT+4],8 ;8*4
;mov byte ptr [BLOW_WHAT+5],50
;mov byte ptr [BLOW_WHAT+6],8 ;8*4
;mov byte ptr [BLOW_WHAT+7],35
;mov byte ptr [BLOW_WHAT+8],8 ;8*4
;mov byte ptr [BLOW_WHAT+9],25



; first byte... num‚ro du sample (PAS x4.. normal...)

;        * normal use:
;        first word:  Number of sample. (1 to 63 advailable)
;        second word: Note number.      (0 to 95 advailable)


; * normal use:
; first word:  Number of sample. (1 to 63 advailable)
; second word: Note number.      (0 to 95 advailable)
;                                (36=B4,35=A#4,...,48=B3...)
; third word:  Blow indication   (0 or 1, put 1 when you start a new sample)
;
; * if you need to stop a FX VOICE:
; first word:  0
; second word: 0
; third word:  1
; (or just blow another FX on this channel)
;
; * if you need to change the 'speed' of a FX VOICE:
; (usefull with LOOPING samples)
;
; first word:  Number of sample.
; second word: Note number.
; third word:  2
; better NOT use this if no sample is currently played...

call play_fx

FSDFGDFGDFGDFGSGDFSe:
;mov ah,02h
;mov dh,24
;mov dl,0
;mov bh,0
;int 10h
;
;xor ax,ax
;mov al,ds:[joystick_a_but1]
;call affsigne
;mov al,ds:[joystick_a_but2]
;call affsigne
;mov al,ds:[joystick_b_but1]
;call affsigne
;mov al,ds:[joystick_b_but2]
;call affsigne
;mov ax,ds:[joystick_a_Y]
;call affsigne
;mov ax,ds:[joystick_a_x]
;call affsigne
;mov ax,ds:[joystick_b_Y]
;call affsigne
;mov ax,ds:[joystick_b_x]
;call affsigne
;
;call teste_Joystick

     IN  AL,60h
     CMP AL,1
     JNE FSDFGDFGDFGDFGSGDFSe


	call gus_init

	mov ax,4c00h                    ; AH=4Ch - Exit To DOS
	int 21h                         ; DOS INT 21h

	; include c:\f\affsigne.inc
	include video.inc

load proc near
 xor eax,eax
 mov al,00h  ;ouverture du fichier pour lecture.
 mov ah,03dh
 mov edx,offset fichier
 int 21h
 jc erreur_filec;saute si carry=1

 mov ebx,eax
 mov ah,03fh
 mov ecx,064000
 mov edx,offset buffer
 int 21h

 mov ah,03eh
 int 21h
ret
erreur_filec:
;call affsigne
ret
load endp

beuh proc near
push ds
mov ax,fs  ;SOURCE...
mov ds,ax  ;
mov es,ax
mov esi,0
mov edi,614400
mov ecx,76800
rep movsd
pop ds
ret
beuh endp

aff_page proc near ;affiche en ram video ce k'il y a a : FS:ESI
		   ;ENTREE : ESI

push ds

xor edi,edi

mov ax,fs  ;SOURCE...
mov ds,ax  ;

xor bx,bx ;pour l'int.
xor dx,dx

call change_page
push edi
mov ecx,016384
rep movsd
pop edi
call change_page
push edi
mov ecx,016384
rep movsd
pop edi
call change_page
push edi
mov ecx,016384
rep movsd
pop edi
call change_page
push edi
mov ecx,016384
rep movsd
pop edi
call change_page
push edi
mov ecx,45056/4
rep movsd
pop edi


pop ds
ret
change_page:
;mov     dx,bp ;numero de la fenetre ;ax
;xor     bx,bx
mov     ax,4f05h
int     10h
inc dx ;bp
ret
aff_page endp

load_pcx proc near ; ecx: offset dans le fichier.
		   ; edx: offset nom du fichier
		   ; edi: viseur dans donn‚es ou ca serra copi‚ (fs:)

pushad
push es ds

 mov ax,fs
 mov es,ax

 xor eax,eax
 mov al,00h  ;ouverture du fichier pour lecture.
 mov ah,03dh
 int 21h
 jc erreur_filec;saute si carry=1

mov [load_handle],eax

;... deplacement a l'interieur du fichier rmd ...

push ecx ;(1)

mov ebx,[load_handle]
mov ah,042h
mov al,00h ;debut du fichier
mov dx,cx
shr ecx,16
;dans cx:dx deplacement a l'interieur du fichier
int 21h
jc erreur_filec ;saute si carry=1

;...lecture du fichier...

 mov ebx,[load_handle]
 mov ah,03fh
 mov ecx,0FFFFh
 mov edx,offset buffer
 int 21h
 jc  erreur_filec ;saute si carry=1

pop eax ;(1)

add eax,dword ptr [buffer]
sub eax,768

push eax ;(1)

;xor edi,edi

xor ebx,ebx ;nombre de pixel k'on a affiche
xor ecx,ecx

mov esi,offset buffer+128

encore_un_pixel:

cmp ebx,640*480
jnb cestfini

lodsb

cmp esi,offset buffer+0ffffh
jne coke
call charge_encore
mov esi,offset buffer
coke:

cmp al,192
jb non_c_un_octet_seul
and al,0111111B

movzx cx,al ;non signe... 8 -> 16 bits

lodsb

cmp esi,offset buffer+0ffffh
jne cok
call charge_encore
mov esi,offset buffer
cok:

viennes:
stosb
inc ebx    ;nombre de pixels k'on a affiches.
dec cx
jnz viennes

jmp encore_un_pixel

non_c_un_octet_seul:
stosb
inc ebx     ;nombre de pixels k'on a affiches.

jmp encore_un_pixel

cestfini:

;.... plus k'a recopier la palette...

;mov ax,c
;mov es,ax
;mov ds,ax
mov ebx,[load_handle]
;;mov eax,0 ;-768 ;259995 ;768

pop eax ;(1) !!
;
mov dx,ax
shr eax,16
mov cx,ax
mov ah,042h
mov al,00h
int 21h
jc erreur_filec ;saute si carry=1
;
;push dx
;mov ax,c
;mov es,ax
;mov ds,ax
mov ebx,[load_handle]
mov ah,03fh
mov cx,0768
mov edx,offset pal
int 21h
;pop dx
;
;;...............convertis la palette...
;
;
;;dans cx:dx deplacement a l'interieur du fichier
;
;mov ax,c
;mov es,ax
;mov ds,ax
	 mov esi,offset pal
;         mov di,offset pal
mov cx,768
xor ax,ax
rtrttr:
mov al,[esi]
shr al,2
mov [esi],al
inc esi
dec cx
jnz rtrttr
;
;...fermeture fichier...
mov ebx,[load_handle]
mov ah,03eh
int 21h
jc erreur_filec ;saute si carry=1

pop ds es
popad
ret
load_pcx endp

charge_encore proc near

push ds ax es ds ebx cx dx
mov ebx,[load_handle]
mov ah,03fh
mov cx,0FFFFh
mov edx,offset buffer
int 21h
pop  dx cx ebx ds es ax ds

ret
charge_encore endp

affpal      proc near
    pushad
	 mov   esi,offset pal
	 mov   dx,3c8h
	 XOR   al,al
	 out   dx,al
	 mov   dx,3c9h
	 mov cx,256*3
	 @@saaccvaaaax:
	 LODSB
	 out   dx,al
	 dec cx
	 JNZ  @@saaccvaaaax
   popad
   ret
affpal      endp


_TEXT   ends

_DATA   segment use32 dword public 'DATA'


;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; DATA
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±

load_handle dd ? ;handle pour la gestion de fichier....
_msg        db 'Hello World From Protected Mode!',10,13,'$'
data_vesa   db 256 dup (?)
buffer      db 0FFFFh dup (0)
pal         db  768 dup (0)
pas_de_vesa db 'NO fucking VESA.',10,13,'$'
pas_de_mem  db 'PAS ASSEZ DE MEMOIRE.',10,13,'$'
pbs1        db 'probleme dans allocation de descriptor..',10,13,'$'
pbs2        db 'probleme dans dans definition de la taille du segment',10,13,'$'
fichier     db 'exit.raw',0,'$'
fichier2    db 'A.pcx',0,'$'
fichier3    db 'B.pcx',0,'$'


include DATA_RMD.INC ;variables pour le player.

rmd_file_name db   'tripto13.RMD',0
IFF_file_name db  'non.iff',0


_DATA   ends


;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; STACK
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
stackseg   segment para stack 'STACK'
	db 1000h dup(?)
stackseg   ends

	end start

