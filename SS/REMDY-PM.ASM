PUSHALL MACRO     ; Pushes all registers onto stack = 18c
PUSHAD
PUSH DS ES
ENDM

POPALL MACRO      ; Pops all registers from stack = 18c
POP ES DS
POPAD
ENDM

;
;code segment public use16
;assume cs:code,ds:rmd_data

.386p

code   segment use32 dword public 'CODE'
        assume  cs:code,ds:_data


public detect
;public play_song
;public load_file
;public stop_song
PUBLIC LOAD_BONUS_SAMPLE
public teste_Joystick
public gus_init
public play_fx

;.386
;
;INCLUDE sb.inc
;INCLUDE gus.inc
include affsigne.inc
include joy-pm.inc

include play-pm.inc

code ends

;rmd_data segment public use16

_data   segment use32 dword public 'DATA'


extrn  rmd_file_name:byte
extrn  IFF_file_name:byte
extrn  BLOW_WHAT:WOrD
extrn  line_in_current_played_pattern:word
extrn  number_played_in_pattern_playlist:word
extrn  pattern_number:word
extrn  mode_fx:byte
extrn  mode_music:byte
extrn  music_volume:word
extrn  fx_volume:word
extrn  panning_gus:byte
extrn  gus_or_sb:byte
extrn  MEMOIRE_GUS:dword
extrn  joystick_detected:byte
extrn  joystick_a_but1:byte
extrn  joystick_a_but2:byte
extrn  joystick_b_but1:byte
extrn  joystick_b_but2:byte
extrn  joystick_a_x:word
extrn  joystick_a_y:word
extrn  joystick_b_x:word
extrn  joystick_b_y:word
extrn  joystick_number:byte
extrn  silence_mode:byte
extrn  mode_percent:byte

include remdyseg.inc

_data ends

end
