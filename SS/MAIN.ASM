o0 equ 0
;ษออออออออออออออออออออออออออออออออออออออออออออป
;บ Remdy soundsystem V0.5                     บ
;ศออออออออออออออออออออออออออออออออออออออออออออผ



size_of_exe_file EQU 30 ;in kb VERY important!

code segment public use16
ASSUME CS:CODE,DS:rmd_data,SS:PILE

.386

extrn detect:near
extrn load_file:near
extrn play_song:near
extrn stop_song:near
extrn LOAD_BONUS_SAMPLE:near
extrn teste_Joystick:near

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

;***** DETECT *********************************
; NOTE: 'detect' need to check PSP to detect environnement
;       so it need ES the way it was at the beginning of the program.
;
; INPUT: BP=0 normal mode
;        BP=1 will NOT display banners (no more 'gus environment found...')
;        BP=2 will not use GUS, even if a GUS is found.
;        BP=3 will not use SB, even if a SB is found.
;        BP=4 do NOT detect any cards. (will activate silence mode with
;                                       synchro support ONLY if silence_mode=1
;                                       note that this mode need memory for
;                                       the patterns.)
;
;
; OUTPUT: enable you to use play_song and stop_song (if detection) succeded
;        BP=1 found a GUS
;        BP=2 found a SB
;        BP=3 no sound card detected (silence mode activated)
;        BP=4 no sound card detected (silence mode NOT activated)
; DATA OUTPUT:
;        Will modify theses datas: MEMOIRE_GUS DD 0 (if gus found)
;                                  GUS_OR_SB   DB 0 (infos where declared!)

mov bp,o0
call detect

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
;:!inc cx
;cmp cx,128
;jne foo
;xor cx,cx
mov ah,02h
mov dh,24
mov dl,0
mov bh,0
int 10h
mov ax,rmd_data
mov es,ax
xor ax,ax
mov al,es:[joystick_a_but1]
call affsigne
mov al,es:[joystick_a_but2]
call affsigne
mov al,es:[joystick_b_but1]
call affsigne
mov al,es:[joystick_b_but2]
call affsigne
mov ax,es:[joystick_a_Y]
call affsigne
mov ax,es:[joystick_a_x]
call affsigne
mov ax,es:[joystick_b_Y]
call affsigne
mov ax,es:[joystick_b_x]
call affsigne

;call teste_Joystick
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

cachiecassetoi:

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
public        silence_mode
public        mode_percent

;JOYSTICK AUDIANCE:
public        joystick_detected
public        joystick_a_but1
public        joystick_a_but2
public        joystick_b_but1
public        joystick_b_but2
public        joystick_a_x
public        joystick_b_x
public        joystick_a_y
public        joystick_b_y
public        joystick_number


;--------- NORMAL .RMD PLAYING ----------------------------

;rmd_file_name db  'awake.RMD',0

;--------- SPECIAL BONUS SAMPLE (SOUND FX) VARIABLES ------

IFF_file_name db  'NON.IFF',0

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

mode_percent  db  1         ; if =1 display % of le file that is loaded when
                            ; the music file is loaded. (load_file)
                            ; (better ONLY do that in text mode)
                            ; if =0 don't do anything

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
gus_or_sb DB 0                  ;DO NO WRITE HERE !!! WILL BY MODIFIED BY
                                ;DETECT:
                                ;0=NOT YET DETECTED
                                ; OR NO SOUND AND NO SILENCE MODE.
                                ; (if silence_mode was put to 0)
                                ;1=PLAYING ON GUS
                                ;2=PLAYING ON SB
                                ;3=SILENCE MODE ACTIVATED. (synchro works.
                                ;  but needs memory and takes time machine.
                                ;  silence_mode have to be = 1 )

silence_mode db 1               ;WRITE this before runnning Detect:
                                ;0= NO silence mode if no cards found
                                ;1= Silence mode if no cards found



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
joystick_b_x        dw 0
joystick_a_y        dw 0
joystick_b_y        dw 0

joystick_number     db 0

;-----------------------------------------------------------
rmd_file_name db   'tripto13.RMD',0



rmd_data     ends

pile         SEGMENT STACK USE16
              DW 512 DUP (0)
pile         ENDS

end start
