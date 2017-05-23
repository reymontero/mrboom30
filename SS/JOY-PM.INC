
JSPort                   EQU     201h      ;iosticos portos (e aramis ?)
JSCounterTimeOutVal      EQU     08888h    ;timehoutos countero valeo

detect_joystick proc far
pushad

cmp [joystick_detected],3
je il_en_veut_pas_le_monsieur

                push    ecx
                push    edx
                pushf
                clc                             ;bavoui


                xor     ecx,ecx                 ;resetos loopas countera
                mov     dx,JSPort
                mov     al,1
                out     dx,al                   ;setos offos timeros
                mov     cx,JSCounterTimeOutVal  ;timaout counto
@jdloop:                                        ;las loopas
                in      al,dx                   ;octos ina al = Statuos
                and     al,00000001b            ;e el iosticos XY valeos
                jz      YAUNJOY
                dec cx
                jnz    @jdloop

;-------- PAS DE PUTAIN DE JOYSTICK
mov [joystick_detected],2
mov edx,offset no_joystick
mov ah,09
int 21h
jmp beuuuuuuuuuuuuuurk
YAUNJOY:

;-------------- regarde si on est chez moi ou chez jc !!!!

mov [joystick_jc],1 ;par default si c chez JC.

                mov     dx,JSPort
                mov     al,1
                out     dx,al
                mov     dx,JSPort
                in      al,dx
                shr     al,4
                not al
                clc
                shr     al,1
                jnc nonononot
mov [joystick_jc],0 ;si le bouton est deja appuye (faux !!!)
                       ;on dit ke c chez moi!
                nonononot:

;------------- BON ALORS on a trouv‚ un joytick. on regarde si y'en a deux

                mov     dx,JSPort
                xor     al,al                   ;clearos al
                out     dx,al                   ;offos el timeros (NOSOUND! hahahahahahahahahahaahhahhaaaaahhahahahahahhaahhahahaaaaaaaaaaaaaaahahahahahahahhhhhaaaaahahahahahahahahahhahahahahhahhahaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahahahahahahahahahahahhaahhaahaahoohoohohhohohoaoahaohaooahoahohoahaohaohaohaohaohahaahahahhahahaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahooohohahhaohoaohoahhoaohaohaohoahaohohaohaohaohoaohahooooooooooooooooooooaaaaaaaaaaaaaaaaahahoahoahohaohoahaihiihihihihiihhiihihuuuuhuhuhhhuhuhuhuhuhehehehehhehehhohoohaohhaoahaahahaa   HA.
mov cx,JSCounterTimeOutVal
b@jsloop:
                in      al,dx                   ;octetos ina al = Statuos
;                mov     ah,al                   ;besoine toa testa si no valeos
                and     al,00001111b            ;e el iosticos XY valeos
                jz      wha_putain_yen_a_deux             ;finita !
                dec cx
                jnz b@jsloop

;------- 1 SEUL JOYSTICK

mov [joystick_number],1

mov edx,offset joystick_1
mov ah,09
int 21h

mov [joystick_detected],1

jmp beuuuuuuuuuuuuuurk

wha_putain_yen_a_deux:

mov [joystick_number],2

mov edx,offset joystick_2
mov ah,09
int 21h

mov [joystick_detected],1

beuuuuuuuuuuuuuurk:
                popf
                pop     edx
                pop     ecx
il_en_veut_pas_le_monsieur:

popad
ret
detect_joystick endp

teste_Joystick            PROC    far

        pushad                                  ;sobgardazion dela muerte
        pushf

cmp [joystick_detected],1 ;mˆme pas peur
jne terterterertrte

;--- pour le faire pas trop souvent !!!
inc [joystick_compteur]
cmp [joystick_compteur],2
jne terterterertrte
mov [joystick_compteur],0
;------------

               mov     [joystick_a_x],0     ;incos countera si bita HIGH
               mov     [joystick_a_y],0
               mov     [joystick_b_x],0
               mov     [joystick_b_y],0
               mov     [joystick_a_but1],0
               mov     [joystick_a_but2],0
               mov     [joystick_b_but1],0
               mov     [joystick_b_but2],0

mov bl,011B
cmp [joystick_number],2
jne reretrteert
mov bl,01111B
reretrteert:

mov cx,JSCounterTimeOutVal
                mov     dx,JSPort
                xor     al,al                   ;clearos al
                out     dx,al                   ;offos el timeros (NOSOUND! hahahahahahahahahahaahhahhaaaaahhahahahahahhaahhahahaaaaaaaaaaaaaaahahahahahahahhhhhaaaaahahahahahahahahahhahahahahhahhahaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahahahahahahahahahahahhaahhaahaahoohoohohhohohoaoahaohaooahoahohoahaohaohaohaohaohahaahahahhahahaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahooohohahhaohoaohoahhoaohaohaohoahaohohaohaohaohoaohahooooooooooooooooooooaaaaaaaaaaaaaaaaahahoahoahohaohoahaihiihihihihiihhiihihuuuuhuhuhhhuhuhuhuhuhehehehehhehehhohoohaohhaoahaahahaa   HA.
@jsloop:
                in      al,dx                   ;octetos ina al = Statuos
                mov     ah,al
                and     al,bl                   ;e el iosticos XY valeos
                jz      @donejspoll             ;finita !
                clc
                shr     al,1                    ;Sticos A X axis
                adc     [joystick_a_x],0     ;incos countera si bita HIGH
                clc                             ;clearos por nextos bitos
                shr     al,1                    ;Sticos A Y axis
                adc     [joystick_a_y],0     ;incos countera si bita HIGH
                clc                             ;
                shr     al,1                    ;Sticos B X axis
                adc     [joystick_b_x],0     ;incos countera si bita HIGH
                clc                             ;
                shr     al,1                    ;Sticos B Y axis
                adc     [joystick_b_y],0     ;incos countera si bita HIGH
                dec     cx ;:,[JSCounter]
               jnz     @jsloop ;saut si pas superieur
@donejspoll:

;----------------

cmp [joystick_jc],1 ;             db  0   ;0= comme chez moi, 1 =jc
je jct
;---------------- methode des boutons pour chez moi...
mov dx,204h
in al,dx
shr al,4
not al ;-> 1 = bouton appuy‚

                clc                             ;mantenata timere por buttonos..
                shr     al,1                    ;coolos, loada buttona varios
                adc     [joystick_a_but1],0
                clc
                shr     al,1
                adc     [joystick_a_but2],0
                clc
                shr     al,1
                adc     [joystick_b_but1],0
                clc
                shr     al,1
                adc     [joystick_b_but2],0


jmp terterterertrte
;------- methode des boutons pour chez jc
jct:
                mov     dx,JSPort
                mov     al,1
                out     dx,al
                mov     dx,JSPort
                in      al,dx
                shr     al,4
not al
                clc
                shr     al,1
                jnc nononono
                or     [joystick_a_but1],1
                nononono:

                clc
                shr     al,1

                jnc nononono3
                or     [joystick_a_but2],1
                nononono3:

                clc
                shr     al,1

                jnc nononono2
                or     [joystick_b_but1],1
                nononono2:
                clc
                shr     al,1

                jnc nononono4
                or     [joystick_b_but2],1
                nononono4:


terterterertrte:
        popf
        popad

;xor ax,ax
;mov al,[joystick_a_but1]
;call affsigne
;mov al,[joystick_a_but2]
;call affsigne
;mov al,ds:[joystick_b_but1]
;call affsigne
;mov al,[joystick_b_but2]
;call affsigne
;mov ax,[joystick_a_Y]
;call affsigne
;mov ax,ds:[joystick_a_x]
;call affsigne
;mov ax,ds:[joystick_b_Y]
;call affsigne
;mov ax,ds:[joystick_b_x]
;call affsigne

;call affblanc
;call noping

        ret

teste_Joystick            ENDP

;noping proc near
;push cx
;mov cx,300
;changer:
;push cx
;mov cx,0FFFFh
;il:
;nop
;loop il
;pop cx
;loop changer
;pop cx
;ret
;noping endp


;affblanc proc near
;mov cx,15
;okz:
;mov al,' '
;push ax
;push dx
;mov dl,al
;mov ah,2
;int 21h
;pop dx
;pop ax
;loop okz
;ret
;affblanc endp




