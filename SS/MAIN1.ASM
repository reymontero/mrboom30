;ษออออออออออออออออออออออออออออออออออออออออออออป
;บ Remdy soundsystem V0.                    . บ
;ศออออออออออออออออออออออออออออออออออออออออออออผ
;
; simple example, just play a .RMD and then exit.

size_of_exe_file EQU 30 ;in kb VERY important!

code segment public use16
ASSUME CS:CODE,DS:rmd_data,SS:PILE

.386

extrn detect:near
extrn load_file:near
extrn play_song:near
extrn stop_song:near
extrn LOAD_BONUS_SAMPLE:near

;****** put your procedures here ... *****

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
;****************************************



;***** DETECT *********************************
; NOTE: 'detect' need to check PSP to detect environnement
;       so it need ES the way it was at the beginning of the program.
;
; INPUT: BP=0 normal mode
;        BP=1 will NOT display banners (no more 'gus environment found...')
;        BP=2 will not use GUS, even if a GUS is found.
;        BP=3 will not use SB, even if a SB is found.
;        BP=4 do NOT detect any cards.
;             (But this is NOT a silence mode, in V0.5 there's no synchro
;              whithout cards...)
;
; OUTPUT: enable you to use play_song and stop_song (if detection) succeded
;        BP=1 found a GUS
;        BP=2 found a SB
;        BP=3 no sound card detected (silence mode will be activated)
;        BP=4 no sound card detected (BUT no silence mode activated)
;             Only happens if INPUT=4 too... (-> gus_or_sb=0)
; DATA OUTPUT:
;        Will modify theses datas: MEMOIRE_GUS DD 0 (if gus found)
;                                  GUS_OR_SB   DB 0 (infos where declared!)

mov bp,0
call detect

mov ax,bp            ;display output...
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

mov  ecx,0 

CALL load_file

mov ax,bp            ;display output...
call affchiffre

;..............................................
;;***** PLAY_SONG **********************
;
; INPUT: BP=0 normal mode
;        BP=1 whithout "scraatch" on speakers, only use AFTER you already
;             used this procedure with a normal BP=0 input.$
;             if you want to play another song after this (you MUST use
;             stop_song in normal at the end of your program...
;
; OUTPUT: NONE
;
mov bp,0
CALL play_song
;..............................................

mov ax,rmd_data  ;display message...
mov ds,ax
mov dx,offset message
mov ah,9
int 21h

FSDFGDFGDFGDFGSGDFSe:

     IN  AL,60h
     CMP AL,1
     JNE FSDFGDFGDFGDFGSGDFSe


;***** STOP_SONG **********************
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

;--------- NORMAL .RMD PLAYING ----------------------------

rmd_file_name db  'tripto13.RMD',0

;--------- SPECIAL BONUS SAMPLE (SOUND FX) VARIABLES ------

IFF_file_name db  'FUK.IFF',0  ;not used in this example.

;>> NO BONUS SAMPLES USED HERE, SO BETTER PUT MODE_FX TO 0 !!!

mode_fx       db  0         ;0= no bonus sample used (FASTER)
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

;-----------------------------------------------------------

message db  'MAIN0.ASM ,the simplest example, just play a .RMD and then exit. (press ESC)',13,10,'$'

rmd_data     ends


pile         SEGMENT STACK USE16
              DW 512 DUP (0)
pile         ENDS

end start
