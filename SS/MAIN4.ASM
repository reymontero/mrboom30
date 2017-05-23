o0 equ 0
;ษออออออออออออออออออออออออออออออออออออออออออออป
;บ Remdy soundsystem V0.                      บ
;ศออออออออออออออออออออออออออออออออออออออออออออผ

size_of_exe_file EQU 30+64 ;in kb VERY important!

code segment public use16
ASSUME CS:CODE,dS:rmd_data,SS:PILE

.386

extrn detect:near
extrn load_file:near
extrn play_song:near
extrn stop_song:near
extrn LOAD_BONUS_SAMPLE:near

;****** put your procedures here ... *****
affsigne proc near
push ax
pushf

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

push ax
push dx
add al,48
mov dl,al
mov ah,2
int 21h
pop ax
pop dx

dec cx
JNZ affichage
pop cx
pop bx

push ax
mov al,' '

push ax
push dx
mov dl,al
mov ah,2
int 21h
pop dx
pop ax

pop ax

popf
pop ax
ret
affsigne endp

affchiffre proc near
push ax dx
pushf
add al,48
mov dl,al
mov ah,2
int 21h
mov dl,' '
mov ah,2
int 21h

popf
pop dx ax
ret
affchiffre endp


;**** PLEASE LET THIS THE BEGINNING *****
start:

MOV AH,04Ah
MOV BX,size_of_exe_file*64      ;important: if the program crash that
INT 21h                         ;may come from here.
                                ;make sure you give a superior size
                                ;of the EXE file.



mov bp,o0
call detect

cmp es:[joystick_detected],2 ;no joystick
je alexandrie

mov ax,bp
;call affsigne
call affchiffre

;***** LOAD FILE ******************************
; INPUT: ECX: OFFSET in the file. (useful for big DATA files with many .RMD
;                                  files in them for example)
; OUTPUT: BP=0 no problemo
;         BP=1 not a 4 or 8 channels .RMD file
;         BP=2 error loading file (file not found...)
;         BP=3 not enough base memory (can only happen with SB)
;         BP=4 not enough memory in GUS
;         BP=5 no Soundcard detected before

mov  ecx,0 ;323878

CALL load_file

mov  ax,bp
call affchiffre ;signe

cmp bp,0
jne cachiecassetoi

;;***** LOAD BONUS SAMPLE **********************
; INPUT:  AX=NUMBER YOU GIVE TO THE SAMPLE (between 31 to 63 for the normal
;            extra sample, between 1 to 31 will replace a normal .RMD sample.)
;         ECX=OFFSET in the file. (useful for big DATA files with many .IFF
;                                  files in them)
;
; OUTPUT: BP=0 no problemo
;         BP=2 error loading file (file not found...?)
;         BP=3 not enough base memory (can only happen with SB)
;         BP=4 not enough memory in GUS
;         BP=5 no Soundcard detected before
;
; IMPORTANT: 'mode_fx db' must be set to 1 or no bonus sample will be played.
;            (in case you don't need bonus samples don't forget to set
;            'mode_fx db' to 0 or that would waste some time machine...)

mov ax,32
mov ecx,0

call LOAD_BONUS_SAMPLE

;mov ax,33
;mov ecx,0
;
;call LOAD_BONUS_SAMPLE
;
;mov ax,bp
;call affsigne

;..............................................
;;***** PLAY_SONG **********************
;
; INPUT: BP=0 normal mode
;        BP=1 whithout "scraatch" on speakers, only use if you want to play
;             another song after this (you MUST use stop_song in normal
;             at the end of your program...
; OUTPUT: NONE
;
mov bp,0
CALL play_song
;..............................................

mov ax,13h   ; init mcga 320*200
int 10h
;----- display gfx !!!
mov ax,0a000h
mov es,ax
xor di,di
mov ax,gfx_data
mov ds,ax
xor si,si
mov cx,16000
rep movsd

FSDFGDFGDFGDFGSGDFSe:


     IN  AL,60h
     CMP AL,59
     jne hui
;----------------------------
mov ax,rmd_data
mov es,ax
;mov eax,es:[memoire_gus]
;shr eax,10
;call affsigne
mov es:[blow_what],32  ;numero du sample
mov es:[blow_what+2],30 ;numero de la note.
mov es:[blow_what+4],1  ;BLOW THE SAMPLE! (always fill this WORD AT THE END)
;-------------------------------

;IMPORTANT: 'mode_fx db' must have been set to 1 or no bonus sample will be
;played.

hui:
     IN  AL,60h
     CMP AL,60
     jne hui2

mov ax,rmd_data
mov es,ax

mov es:[blow_what],32   ;numero du sample
mov es:[blow_what+2],40 ;numero de la note.
mov es:[blow_what+4],1  ;BLOW THE SAMPLE! (always fill this WORD AT THE END)

hui2:


     IN  AL,60h
     CMP AL,61
     jne hui2e

mov ax,rmd_data
mov es,ax

mov es:[blow_what],32   ;numero du sample
mov es:[blow_what+2],20 ;numero de la note.
mov es:[blow_what+4],2  ;BLOW THE SAMPLE! (always fill this WORD AT THE END)

hui2e:
;inc cx
;cmp cx,128
;jnz foo
;xor cx,cx

;-------- change the color palette because of the joystick!
mov ax,rmd_data
mov es,ax
mov ax,gfx_data
mov fs,ax


         mov   dx,3c8h
         mov   al,1
         out   dx,al
         mov   dx,3c9h

;------- colors up right down left

xor ax,ax ;defaulf color...

mov bx,fs:[haut_joy] ;to be ok: droite_joy -10 < joystick_a_x < droite_joy +10
sub bx,20
cmp bx,es:[joystick_a_y]
ja not_movedytt
add bx,40
cmp bx,es:[joystick_a_y]
jb not_movedytt

mov al,63

not_movedytt:

         out   dx,al
	 out   dx,al
         out   dx,al

; -------- 1st joystick on the right ??? ------
xor ax,ax ;defaulf color...

mov bx,fs:[droite_joy] ;to be ok: droite_joy -10 < joystick_a_x < droite_joy +10
sub bx,20
cmp bx,es:[joystick_a_x]
ja not_moved
add bx,40
cmp bx,es:[joystick_a_x]
jb not_moved

mov al,63

not_moved:

	 out   dx,al
	 out   dx,al
         out   dx,al

;-- DOWN ??? ----------------------------

xor ax,ax ;defaulf color...

mov bx,fs:[bas_joy] ;to be ok: droite_joy -10 < joystick_a_x < droite_joy +10
sub bx,20
cmp bx,es:[joystick_a_y]
ja not_movedyt
add bx,40
cmp bx,es:[joystick_a_y]
jb not_movedyt

mov al,63

not_movedyt:

         out   dx,al
	 out   dx,al
         out   dx,al


; -------- 1st joystick on the left ??? ------

xor ax,ax ;defaulf color...

mov bx,fs:[gauche_joy] ;to be ok: droite_joy -10 < joystick_a_x < droite_joy +10
sub bx,20
cmp bx,es:[joystick_a_x]
ja not_movedy
add bx,40
cmp bx,es:[joystick_a_x]
jb not_movedy

mov al,63

not_movedy:

         out   dx,al
	 out   dx,al
         out   dx,al

;-----------------------------------------------
;------------------------

         mov   al,es:[joystick_a_but1]
         shl   al,5
         out   dx,al
	 mov   al,0
	 out   dx,al
	 mov   al,0 ;63 ;15
	 out   dx,al

         mov   al,0
         out   dx,al
         mov   al,es:[joystick_a_but2]
         shl   al,5
         out   dx,al
	 mov   al,0 ;63 ;15
	 out   dx,al

;------- colors up left right down
         mov   al,0 ;15
	 out   dx,al
	 mov   al,0
	 out   dx,al
	 mov   al,0 ;63 ;15
         out   dx,al

         mov   al,0
	 out   dx,al
	 mov   al,0 ;63 ;15
         out   dx,al
	 mov   al,0
	 out   dx,al

         mov   al,0 ;63 ;15
	 out   dx,al
	 mov   al,0
	 out   dx,al
         mov   al,0 ;63 ;15
         out   dx,al

         mov   al,0 ;63 ;15
	 out   dx,al
	 mov   al,0
	 out   dx,al
         mov   al,0 ;63 ;15
         out   dx,al


;------------------------

         mov   al,es:[joystick_b_but1]
         shl   al,5
         out   dx,al
	 mov   al,0
	 out   dx,al
	 mov   al,0 ;63 ;15
	 out   dx,al

         mov   al,0
         out   dx,al
         mov   al,es:[joystick_b_but2]
         shl   al,5
         out   dx,al
	 mov   al,0 ;63 ;15
	 out   dx,al


xor ax,ax
mov ax,es:[joystick_a_Y]
;call affsigne

xor ax,ax
mov ax,es:[joystick_a_x]
;call affsigne

xor ax,ax
mov al,es:[joystick_a_but1]
;call affsigne
;
xor ax,ax
mov al,es:[joystick_a_but2]
;call affsigne

xor ax,ax
mov al,es:[joystick_b_but1]
;call affsigne

xor ax,ax
mov al,es:[joystick_b_but2]
;call affsigne


;mov dx,204h
;in al,dx
;shr ax,4
;not ax
;and ax,1111B
;call affsigne

foo:

     IN  AL,60h
     CMP AL,1
     JNE FSDFGDFGDFGDFGSGDFSe

;.............................

;;***** STOP_SONG **********************
; stop music/re-init with GUS and SB (makes a normal "scraatch" on speakers)
; deallocate memory (sb)
;
; INPUT: BP=0 normal mode
;        BP=1 whithout "scraatch" on speakers, only use if you want to play
;             another song after this (you MUST use stop_song in normal
;             at the end of your program...
; OUTPUT: NONE
;
mov bp,0
CALL stop_song

alexandrie:

cachiecassetoi:

        mov    ax,3  ;init text mode
	int    10h   ;

MOV     AX,04C00h
INT     21h

code ends

rmd_data     segment public use16

public        rmd_file_name
public        iff_file_name
public        blow_what
public        line_in_current_played_pattern
public        number_played_in_pattern_playlist
public        pattern_number
public        mode_fx
public        mode_music
public        music_volume
public        fx_volume
public        panning_gus
public        gus_or_sb
public        memoire_gus
;JOYSTICK AUDIANCE:
public        joystick_detected
public        joystick_a_but1
public        joystick_a_but2
public        joystick_b_but1
public        joystick_b_but2
public        joystick_a_x
public        joystick_a_y
public        joystick_b_x
public        joystick_b_y
public        joystick_number

public silence_mode

;--------- NORMAL .RMD PLAYING ----------------------------

;rmd_file_name db  'awake.RMD',0

;--------- SPECIAL BONUS SAMPLE (SOUND FX) VARIABLES ------

IFF_file_name db  'NON.IFF',0


silence_mode db 1               ;WRITE this before runnning Detect:
                                ;0= NO silence mode if no cards found
                                ;1= Silence mode if no cards found

mode_fx       db  1         ;0= no bonus sample used (FASTER)
                            ; but LOAD_BONUS_SAMPLE still work and will need
                            ; memory with SB !!! (this way you can change
                            ; mode_fx ANY time you want in your program)
                            ; if you don't use bonus samples better choose
                            ; this mode, it will sounds better with SB'S.
                            ;1= BONUS SAMPLE MODE ADVAILABLE  (normal mode)
                            ; you MUST put 1 in MODE_FX if you use BONUS
                            ; SAMPLES in your song.

mode_music    db  1         ;0= no music support !!!
                            ;   (won't load/play ANY music)
                            ; you can still use load_file but that won't
                            ; do anything.
                            ; you can still use play_song but that won't
                            ; do anything.
                            ; you can still use stop_song:
                            ; that will deallocate the memory of samples. (SB)
                            ; and that will re-init the GUS/SB
                            ; ONLY select this mode BEFORE a load_song (...)
                            ; or AFTER a stop_song, or better select it at the
                            ; very beginning of your progam if for example you
                            ; don't have enought base memory for music with SB
                            ; but you still want to use sound fx.
                            ; 1= normal mode...

; 4 Differents FX channel played at the same time advailable.

BLOW_WHAT     dw   0,0,0  ; 1st FX channel
              dw   0,0,0  ; 2nd FX channel
              dw   0,0,0  ; 3rd FX channel
              dw   0,0,0  ; 4th FX channel

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


;--------- VOLUME SETTINGS --------------------------------

music_volume dw 64 ;MUST be in 0 to 64 (64=normal volume)
fx_volume    dw 64 ;MUST be in 0 to 64 (64=normal volume)



;--------- PANNING (stereo) for each gus channel ----------

panning_gus db 8,8,8,8,8,8,8,8      ; normal music channels
            db 8,8,8,8              ; SPECIAL BONUS SAMPLE (SOUND FX) channels

;Must be between 0 and 15:
; 0=RIGHT
; 8=MIDDLE (normal)
; 15=LEFT
;
;the 8 first bytes correspond to the eight first channels
;the 4 last to the FX channels


;-READ ONLY VARIABLES---------------------------------------
gus_or_sb DB 0                  ;DO NO WRITE HERE !!!
                                ;0=NOT YET DETECTED (OR NO SOUND CARD)
                                ;1=PLAYING ON GUS
                                ;2=PLAYING ON SB
                                ;3=SILENCE MODE (MARCHE POUR LA SYNCHRO
                                ;                AVEC OU SANS CARTE)
MEMOIRE_GUS DD 0                ;DO NO WRITE HERE !!!
                                ;will be set after detect (if a gus is found)
                                ;answer in bytes...

;-READ ONLY VARIABLES FOR SYNCHRO --------------------------

line_in_current_played_pattern         dw  0 ;DO NO WRITE HERE !!!
number_played_in_pattern_playlist      dw  0 ;DO NO WRITE HERE !!!
pattern_number                         dw  0 ;DO NO WRITE HERE !!!

;-JOYSTICK VARIABLES ---------------------------------------

joystick_detected   db 0  ;  0=not detected yet (will be in detect procedure)
                          ;  1=detected after detect
                          ;  2=no joytick detected after detect
                          ;  3=if you don't want detection use/detect

joystick_a_but1     db 0
joystick_a_but2     db 0
joystick_b_but1     db 0
joystick_b_but2     db 0

joystick_a_x        dw 0
joystick_a_y        dw 0
joystick_b_x        dw 0
joystick_b_y        dw 0

joystick_number     db 0

;-----------------------------------------------------------
rmd_file_name db   'tripto13.RMD',0

rmd_data     ends

;---- segment where the joystick gfx is stored !!!;+variables about the
                                                  ;joystick
gfx_data     segment public use16
 include joygfx.inc

droite_joy       dw 532 ;
gauche_joy       dw 20  ; … mettre au minimum a 10 !!!

haut_joy         dw 20
bas_joy          dw 603


gfx_data     ends
;-------------------------------------------------

pile         SEGMENT STACK USE16
              DW 512 DUP (0)
pile         ENDS

end start
