
;rmd_data   segment use32 dword public 'rmd_DATA'

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

BLOW_WHAT     dw   14 dup (0)

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

joystick_detected   db 3  ;  0=not detected yet (will be in detect procedure)
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




;rmd_data     ends


