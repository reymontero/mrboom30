; - faire ke lexe finisse par 1664
; ?pas de contamination kan on est sur unlapin et kon saute.
; ? tapis roulants nivo 1
; ? fleches sur le sol pour les bombes kon pousse
; ? ralentir le clignotement du gillet par balles a la fin

duree_saut EQU 64
duree_mort EQU 32
ttp  EQU 4000 ;emps avant le mode demo (touches pressees ...)
ttp2 EQU 60*3  ;temps avant le mode demo (pas de touches pressees)
TRICHE=0

;faire des apocalypse differentes
version_du_jeu EQU 00110000B ;10110000B
nombre_de_vbl_avant_le_droit_de_poser_bombe2 EQU 60*2
invisibilite_totale EQU 100 ;nombre de r‚sistance apres un choc.
invinsibilite_bonus equ 750 ;nombre vbl de m‚gaforce apres manger bonus...

duree_match EQU 001000000000B  ;2 minutes
;duree_match EQU 111000000000B  ;2 minutes
duree_match2 EQU 000000110000B ;30 secondes
duree_match4 EQU 001000000000B ;2 minutes

duree_match3 EQU 000100000000B ;1 minutes
duree_match5 EQU 000100110000B ;1 minutes 30

;duree_match4 EQU 000100000000B ;1 minutes

;010011B  ;001100000000B
time_bouboule equ 5 ;temps pour rotation boules menu
pic_max equ 500 ;dur‚e attente sur gfx de zaac
taille_exe_gonfle EQU 0255442
duree_conta EQU 0800 ;nombre de vbl pour une contamination.


duree_draw2 EQU 500 ;dur‚e du draw game
duree_med2 EQU  1200 ;dur‚e du med cere ;10 secondes...
duree_vic2 EQU  1200 ;dur‚e du vic cere
attente_avant_draw2 equ 100
attente_avant_med2 equ 100
temps_re_menu equ 10
r‚sistance_au_debut_pour_un_dyna equ   0
;----- pour les joueurs...
info1 equ 1
info2 equ 1
info3 equ 210
info4 equ 3
;1,2,3 (normal),4:double...

;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; PMODE/W Assembly Example File #1
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
.386p

;includelib c:\tasm\lib\import32.lib
include ss\proc-pm.inc ;SOUNDSYSTEM.
;
;extrn     ExitProcess     : PROC     ;procedure to shut down a process
;
;extrn     ShowWindow      : PROC
;extrn     GetModuleHandleA: PROC
;extrn     GetForegroundWindow : PROC

;extrn     ExitProcess     : PROC     ;procedure to shut down a process
;extrn     GetForegroundWindow : PROC
;extrn     SendMessageA    : PROC
;extrn     IsZoomed        : PROC
;extrn     ShowWindow      : PROC

_TEXT   segment use32 dword public 'CODE'
        assume  cs:_TEXT,ds:_DATA

start:

        jmp _main

        db '  Monsieur Boom  '   ; The "WATCOM" string is needed in
                                        ; order to run under DOS/4G and WD.

;E db 'envois !!!',10,13,'$'
;a db 'attend... !!!',10,13,'$'

sagouin MACRO aT
PUSH EDX EAX
mov edx,offset aT
mov ah,9
INT 21h
POP EAX EDX
ENDM

        include ipxmacro.inc
        include divers\aff-pm.inc
        include divers\couleur.inc
        include bomb.inc
        include ipx.inc


;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; CODE
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±

;°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
; Entry To ASM Code (_main)
; In:
;   CS - Code Selector    Base: 00000000h - Limit: 4G
;   DS - Data Selector    Base: 00000000h - Limit: 4G
;   ES - PSP Selector     Base: PSP Seg   - Limit: 100h   ;segment video: selector: ES
;   FS - ?
;   GS - ? ;sauvegarde de DS..
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

        PUSHALL

pushall
mov ah,02ch
int 21h

xor eax,eax
mov al,dh
and eax,11100B
mov differentesply2,eax

;and dh,01
;mov kel_pic_intro,dh

popall

        mov ax,3h
        int 10h

        call decrypt
        lea edx,intro_txt
        mov ah,9
        int 21h
        POPALL
        call ewindows
        call ligne_de_commande

        ;----- inst clavier -
        pushall
        xor eax,eax
        mov ax,ds
        mov ss:[merdo],eax
        call inst_clavier
        popall
        ;---

 ;       push    0h
 ;       call    GetModuleHandleA
 ;       mov     [AppHWnd],eax
 ;       call    GetForegroundWindow
 ;       push    3
 ;
; this can be any of the following values :
;SW_HIDE                         equ      0
;SW_SHOWNORMAL                   equ      1
;SW_NORMAL                       equ      1
;SW_SHOWMINIMIZED                equ      2
;SW_SHOWMAXIMIZED                equ      3
;SW_MAXIMIZE                     equ      3
;SW_SHOWNOACTIVATE               equ      4
;SW_SHOW                         equ      5
;SW_MINIMIZE                     equ      6
;SW_SHOWMINNOACTIVE              equ      7
;SW_SHOWNA                       equ      8
;SW_RESTORE                      equ      9
;SW_SHOWDEFAULT                  equ     10
;SW_MAX                          equ     10

;        push    eax
;        call    ShowWindow

;          CALL    ExitProcess     ;End (exit) program
;        call get_pal_ansi
        call setup

        cmp sortie_config,1
        jne reteeeeeeeytyrrtyyt

        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h
        reteeeeeeeytyrrtyyt:

        PUSHALL
;        mov bp,240h

;setup_viseur dd 0
;setup_viseur2 dd 8
;setup_viseur2_offset dw 210h,220h,230h,240h,250h,260h,270h,280h,0

cmp economode,1
jne trreljljrjkltjhtehljtehljte
mov setup_viseur2,8
trreljljrjkltjhtehljtehljte:

mov ebx,setup_viseur2
add ebx,ebx
xor ebp,ebp
mov bp,[setup_viseur2_offset+ebx]
;mov bp,260h
;mov ax,bp
;call affsigne
;setup_viseur2_offset dw 210h,220h,230h,240h,250h,260h,270h,280h,0

        call detect ;es:PSP
        POPALL

        ;mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        ;int 21h                         ; DOS INT 21h

include memoire.inc ;reserve la memoire pour les donn‚es --> selector: FS
                    ;segment video: selector: ES

;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h


;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h


call init_packed_liste


call init_ipx

cmp modeinfo,1            ;cas ou on scan le reso.
jne ertrerertrtrer
call zget_information
ertrerertrtrer:

;----- si pas ipx + pas asserz de memoire: on kill
pushall
        cmp [assez_de_memoire],1
        jne eretterertrteertterrteertterrtertytyerrtyrty
        cmp ipx_,0
        jne eretterertrteertterrteertterrtertytyerrtyrty
        lea edx,NULOSPRODUCTION
        mov ah,9
        int 21h
        mov bl,4 ;bleu ciel
        mov bh,10000000B ;indique clignotement
        call last_color
        call de_init_ipx
        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h
        eretterertrteertterrteertterrtertytyerrtyrty:
popall


pushall
        cmp [assez_de_memoire],1
        jne teretterertrteertterrteertterrtertytyerrtyrty
        cmp special_on_a_loadee_nivo,1
        je erttrtrtrtrettrtettr
        cmp willrecord,1
        jne teretterertrteertterrteertterrtertytyerrtyrty
        erttrtrtrtrettrtettr:

        lea edx,message_mem_rp
        mov ah,9
        int 21h
        mov bl,4 ;bleu ciel
        mov bh,10000000B ;indique clignotement
        call last_color
        call de_init_ipx
        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h
        teretterertrteertterrteertterrtertytyerrtyrty:
popall


;-*-*-*-*-*===================_____X____)\_,--------------------------
        pushall
        cmp [master],0
        jne trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrtyererzreeertrtetertyeryu
        lea edx,information
        mov ah,9
        int 21h
        mov bl,11 ;bleu ciel
        mov bh,00000000B ;indique clignotement
        call last_color
        trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrtyererzreeertrtetertyeryu:

        cmp [assez_de_memoire],1
        jne eretterertrteertterrteertterrte
        lea edx,terminalor
        mov ah,9
        int 21h
        mov bl,5 ;bleu ciel
        mov bh,10000000B ;indique clignotement
        call last_color
        eretterertrteertterrteertterrte:
        popall

;*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

call load_data ;serra fait que si y'a assez de memoire.

cmp [assez_de_memoire],1
        je eretterert
        mov ax,13h
        int 10h
        call affpal

;lea esi,pal_pic2
;pushall
;push ds
;pop es
;
;lea esi,pal_pic2 ;;;rene
;lea edi,pal_affich‚e
;mov ecx,768
;rep movsb
;pal          db  768 dup (?)  ;pal  de l'‚mulateur.
;pal_affich‚e db 768 dup (0)   ;pal k'on affiche...
;popall
;mov esi,1966080+64000*21
;call copie_page
;call aff_page2

eretterert:

call dyna_net ;serra fait si ipx found

;cmp [assez_de_memoire],1
;
;        je eretterertd
;        call affpal
;eretterertd:



cmp dword ptr [kezax],2 ;special.. en cas de brebie ‚gar‚e.
je nouvelle_manche3

hoooooooop:
call init_menu
reterrterterte:
call menu
call pal_visage
call play_fx
call controle

;gestion temps de demo/repousse le compte a rebours
;cmp temps_avant_demo,1
;je ljljrtjhrljhrryr
touche_presse temps_avant_demo ttp
;ljljrtjhrljhrryr:
;==================== SPECIAL DEMO,pour kitter avec nimporte kelle touche...
cmp action_replay,2
jne erterertrtertetertyutyuyuttyuuty
cmp nombre_de_vbl_avant_le_droit_de_poser_bombe,0 ;pas des le debut...
jne erterertrtertetertyutyuyuttyuuty
touche_presse sortie 1
erterertrtertetertyutyuyuttyuuty:
;=================================================================


;kb_packets_jeu_envoyes dd 0
cmp [master],0
jne trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrtyererzreer
call gooroo
return_presse demande_partie_slave 1
call menu_intelligence
call menu_action ;pour action replay
get_all_infos3         ; r‚cupere les touches pour chaque joueur et pour
                       ; tous les diff‚rents ordinateurs.

mov on_les_dans_le_menu,1
call master_net

;--- esc du master ---------------------------------

cmp sors_du_menu_aussitot,1
jne y_special_mrb
mov byte ptr [sortie],1 ;eSC.
y_special_mrb:

cmp byte ptr [sortie],1 ;eSC.
jne erertrterteertrteertertrtertertyeertrteertterertertterertterert

;mov [previentlmesenfants],1
cmp byte ptr [ordre],'B' ;pour bye... (du master)
je rtertertyeertrteertterertertterertterert
mov byte ptr [ordre],'B' ;pour bye...
jmp reterrterterte
erertrterteertrteertertrtertertyeertrteertterertertterertterert:
;----------------------------------------------------------------------

jmp trrtyrtyyrtyrttyrrtyyrtyrtrty
trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrtyererzreer:
call slavemenu
;--- sortie si on a dit kon se cassait
cmp sortie_slave,1
je rtertertyeertrteertterertertterertterert
;-----------

trrtyrtyyrtyrttyrrtyyrtyrtrty:

;cmp changement,300
;jne poiy
;mov byte ptr [sortie],1 ;eSC. ;!!!!!!!!
;poiy:

cmp byte ptr [ordre],'B' ;pour bye... (du slave)
jne rtertertyeertrteertterertertterertterert2RT
mov previentlmesenfants,1 ;pour slave: affiche messgae fin
jmp rtertertyeertrteertterertertterertterert
rtertertyeertrteertterertertterertterert2RT:

cmp [attente_nouveau_esc],0
jne ook

cmp [master],0
jne oook2
cmp byte ptr [sortie],1 ;eSC.
je rtertertyeertrteertterertertterertterert
jmp oook2
ook:
dec [attente_nouveau_esc]
oook2:

cmp byte ptr [ordre],''
jne reterrterterte
;--------------------------------------------------------------------
nouvelle_partie345:

call nouvelle_partie

nouvelle_manche3:

call nouvelle_manche

;**************************************************************************
retertdgrfgd:

call pal_visage

call play_fx

;----- gestion des joeurs locaux.

call controle    ;pr‚pare le packet qu'on va transmettre en informant
                 ;les touches ke l'on presse actuellement

;*************************** MASTER *******************************
cmp [master],0
jne trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty
call gooroo
mov on_les_dans_le_menu,0
call master_net
call master1
call triche_master
trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty:

;*************************** SLAVE ********************************
cmp [master],1
jne trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2
call slave1
trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2:
;-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

;--------------- lecture des ordre ------------------------------
cmp byte ptr [ordre2],'M'  ;pour slave...
je hoooooooop              ;saute au menu si ordre...
;--------------------------------------------------
cmp byte ptr [ordre2],'%' ;indique nouvelle manche
je nouvelle_manche3
;-*-------------------------------

;-- sortie forcee..
cmp [master],0
je ertyerttyrrtyyrtretertdgrfgd
cmp sortie_slave,0 ;cmp sortie,0 ;
jne rtertertyeertrteertterertertterertterert
jmp retertdgrfgd
ertyerttyrrtyyrtretertdgrfgd:


cmp [master],0
jne retertdgrfgd

cmp byte ptr [sortie],1 ;eSC.
jne retertdgrfgd
;on est master.. et echap est appuy‚...
;****************** SORTIE... uniquement pour le master *********************

mov byte ptr [ordre2],'M'  ;donne ordre de sortie
jmp retertdgrfgd

; r‚cupere les touches pour chaque joueur et pour
                           ; tous les diff‚rents ordinateurs.
;call master1               ; comme ca... les autres vont recup ordre2..
;jmp hoooooooop


;****************************************************************************
rtertertyeertrteertterertertterertterert:
        mov ax,3h
        int 10h
;----
cmp previentlmesenfants,1 ;pour slave: affiche messgae fin
jne ertertterrtertyutyutyutyutyutyuutytyu
lea edx,gameover
mov ah,09h
int 21h
ertertterrtertyutyutyutyutyutyuutytyu:
;---


rtertertyeertrteertterertertterertterert2:
busy_ou: ;fin koi

;--effacage de fin ... ---
;cmp [mechant],1
;je mechant3
mechant5:

;pushall
;mov ax,02fh
;mov ax,1684h
;mov bx,07fe0h
;int 2Fh
;mov ax,es
;call affsigne
;
;popall

        call de_init_ipx

;               mov eax,[adresse_des_fonds] ; dd 0h ;,100000h,200000h,100000h
;        mov eax,[differents_offset_possible+8*4*4]
;        call num
;        sagouin texte_fin

        call gus_init


;cmp [jesus_mode],0
;jne reteretrertert5445870t
;packets_jeu_envoyes dw 0
;packets_jeu_recus   dw 0
call affichage_stats
;call affichage_rec
;control_joueur dd 8 dup (?) ;-1,6,32,32+6,-1,-1,-1,-1
;mov eax,control_joueur
;call num

;mov ecx,9
;mov esi,offset victoires
;money_train:
;lodsd
;call affsigne
;loop money_train

;lea edx,last_name
;mov ah,9
;int 21h

;mov ah,02ah
;int 21h
;cmp cx,1998
;jb tranquilleee
;ja rtertertyeertrteertterertertterertterertertrtetyrtyuyuuie
;cmp dh,3
;ja rtertertyeertrteertterertertterertterertertrtetyrtyuyuuie
;tranquilleee:
;
;        lea edx,information2
;        mov ah,9
;        int 21h
;        mov bh,00000000B ;indique clignotement
;        mov bl,11 ;5 ;rouge
;        call last_color
;rtertertyeertrteertterertertterertterertertrtetyrtyuyuuie:
;mov cl,[last_sucker]
;nonoiutryyrtryt:
;cmp [last_sucker],cl
;je nonoiutryyrtryt


;;------------ dky -
;push ds
;pop  es
;
;xor al,al
;lea edi,pal_affich‚e
;mov cx,768
;rep stosb
;call affpal
;
;mov esi,offset darky
;mov edi,0b8000h
;mov ecx,1000
;rep movsd
;mov dl,79
;mov dh,23
;mov al,0
;mov bh,0
;mov ah,2
;int 10h
;
;;lea esi,pal_txt_debut
;
;;rep movsb
;
;;------------
;
;mov cx,63
;rereerter:
;call affpal
;call vbl
;
;;lea esi,pal_txt_debut
;mov bx,768
;xor al,al
;lea esi,pal_txt_debut
;lea edi,pal_affich‚e
;oohiu:
;;lodsb
;cmp al,[edi]
;cmpsb
;je ertterrtyrtrtyrty
;inc byte ptr [edi-1]
;ertterrtyrtrtyrty:
;;inc edi
;
;dec bx
;jnz oohiu
;;rep stosb
;
;
;dec cx
;jnz rereerter


;cmp windows,1
;je oregreteiiooi
;
;        lea edx,information3
;        mov ah,9
;        int 21h
;        mov bh,00000000B ;indique clignotement
;        mov bl,15
;        call last_color
;oregreteiiooi:

;master      db 0 ; 0 = OUI

cmp byte ptr [lost_conney],1 ;eSC.
je r4564654eertrterereetr

cmp [master],0
jne r4564654eertrterereetr
cmp on_a_bien_fait_une_partie,0
jne r4564654eertrterereetr
        lea edx,information5
        mov ah,9
        int 21h
r4564654eertrterereetr:


;lea edx,nick_t
;mov ah,9
;int 21h
        mov al,[lost_conney]
        mov ah,4ch                      ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h
;mov ax,bidouille
;push ax
;pop cs
;xchg ax,cs
;;push cs
;pop cs
;int 20h

quitte_baby: ;cas de connection lost... pour slave...
POPALL
        mov ax,3h
        int 10h
mov [lost_conney],1

mov edx,offset ohohohohoh
mov ah,9
int 21h

        mov bl,0100B ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color

mov dl,''
mov ah,2
int 21h

;mov trygain,1
;jmp tryagain
;
;mov esi,0b8000h
;mov [esi],651516

jmp rtertertyeertrteertterertertterertterert2

;mechant3:
;
;        mov ax,3h
;        int 10h
;
;;load_pcx proc near ; ecx: offset dans le fichier.
;;                   ; edx: offset nom du fichier
;;                   ; edi: viseur dans donn‚es ou ca serra copi‚ (ax:)
;;                   ; ebx: nombre de pixels dans le pcx
;;
;;pushad
;;push es ds
;;
;;mov [load_pcx_interne],ebx
;;
;;
;; mov es,ax
; mov edx,offset iff_file_name
;; mov ah,09h
;; int 21h
; xor eax,eax
; mov al,01h ;ecriture;
; mov ah,03dh
; int 21h
;
;;xor ebx,ebx
;mov ebx,eax
;mov ah,040h
;mov ecx,250000 ;juste le code
;push ds
;
;push fs
;pop  ds
;xor edx,edx
;int 21h
;;  AH     = 40h
;;  BX     = file handle
;;  ECX    = number of bytes to write
;;  DS:EDX -> buffer to write from
;
;pop ds
;jmp mechant5

master1 proc near

;cmp [speed_raster],1
;je no_fucking_vbl
call vbl
;jmp ouiouirt
;no_fucking_vbl:
;inc dword ptr [changement]
;ouiouirt:

;--- intelligence draw game ------------------------------------------------
cmp byte ptr [ordre2],'D'
jne trtyrtyrtyrtyrtyterterertrteert

;*** affichage draw game
cmp byte ptr [assez_de_memoire],1
je retetrterterertertrteertertertertre
cmp [duree_draw],duree_draw2
jne erertertteryr
mov [affiche_pal],1
erertertteryr:
call copie_le_fond_draw
call aff_page2
jmp rtyrtyrtytyrrtyyttyutyutyutyutyutyutyutyutyuyuttyu
retetrterterertertrteertertertertre:
;;;- pas asssez memoire -
;mov ah,02h
;mov dh,24
;mov dl,0
;mov bh,0
;int 10h
;call affiche_en_mode_texte
rtyrtyrtytyrrtyyttyutyutyutyutyutyutyutyutyuyuttyu:
;**************************************************************************
dec [duree_draw]
jnz reterertertert
mov [ordre2],'%' ;indique nouvelle manche
reterertertert:

;,return_presseque_master  ordre2 '%'

;--- pour pas ke le master kitte de suite kan on sort d'un draw game forc‚

cmp [duree_draw],450 ;pas tout de suite kan meme...
ja ertetrtrkjjklmkjlmetkjlmdikgrhrfhgrrethghkgh
cmp word ptr bdraw666,'99'
je ertetrtrkjjklmkjlmetkjlmdikgrhrfhgrrethghkgh
touche_presseque_master  ordre2 '%'
ertetrtrkjjklmkjlmetkjlmdikgrhrfhgrrethghkgh:

cmp [duree_draw],400 ;pas tout de suite kan meme...
ja rerteertertertert3r0
touche_presse ordre2 '%' ;saute au menu...
rerteertertertert3r0:

call compact
get_all_infos2         ; r‚cupere les touches pour chaque joueur et pour
;                       ; tous les diff‚rents ordinateurs.
ret
trtyrtyrtyrtyrtyterterertrteert:
;---------------------------------------------------------------------------

;--------------- intelligence jeu ------------------------------
cmp byte ptr [ordre2],'' ;uniqUEMENT si on est dans le jeu.
jne terterertrteert
call gestion_jeu
;----affichage jeu -------------------

cmp byte ptr [ordre2],'Z' ;uniqUEMENT si on a quitt‚ le jeu en fait...
je  meeeeeed

call compact
get_all_infos2         ; r‚cupere les touches pour chaque joueur et pour
                       ; tous les diff‚rents ordinateurs.
                       ; si ca n'a pas chang‚...
                       ; l'ordre peut avoir chang‚ mais seulement a la fin...

call rec_play_touches  ;enregistre/joue les touches (pour le REPLAY...)

cmp byte ptr [ordre2],'' ;uniqUEMENT si on a pas quitt‚ le jeu en fait...
jne yttyutyutyutyutyutyutyutyutyuyuttyu

;*************** affichage *************************************************
cmp byte ptr [assez_de_memoire],1
je retetrterterertertrteertertertert
;master db 0 ; 0 = OUI
;            ; 1 = NON
;----- affichage de l'‚cran local. l'ancien ecran...
call copie_le_fond
call affiche_sprites
call aff_page2
jmp yttyutyutyutyutyutyutyutyutyuyuttyu
retetrterterertertrteertertertert:
;mov ah,02h
;mov dh,24
;mov dl,0
;mov bh,0
;int 10h
;mov ax,word ptr [donnee4+6]
;and ax,255
;call affsigne
;mov ax,word ptr [donnee+8*2]
;call affsigne
;mov ax,word ptr [donnee+8*2*2]
;call affsigne
call affiche_en_mode_texte
yttyutyutyutyutyutyutyutyutyuyuttyu:
;*****************************************************************************
ret
terterertrteert:
;--------------------------------------------------


;---- victoire supreme -------------------------------------------------------
cmp byte ptr [ordre2],'V'
jne etrertertrtertertyerterttrtyrtyrtyrtyrtyterterertrteert
victoire_sup:
cmp byte ptr [assez_de_memoire],1
je kiretetrterterertertrteertertertertre
cmp [duree_vic],duree_vic2 ;pour kitter...
jne kierertertteryr
mov [affiche_pal],1
kierertertteryr:
call copie_le_fond_vic
call aff_page2
;jmp kirtyrtyrtytyrrtyyttyutyutyutyutyutyutyutyutyuyuttyu
kiretetrterterertertrteertertertertre:
;--- intelligence  vic ---
dec [duree_vic]
jnz ireterertertertu
mov [ordre2],'M' ;indique saute au menu...
ireterertertertu:

cmp [duree_vic],duree_vic2-60 ;pas tout de suite kan meme...
ja rerteertertertert



cmp [duree_vic],duree_vic2-60 ;pas tout de suite kan meme.
ja rerteertertertertPOPOP
touche_presseque_master  ordre2 'M'
rerteertertertertPOPOP:

cmp [duree_vic],duree_vic2/2 ;pas tout de suite kan meme...
ja rerteertertertert
touche_presse ordre2 'M' ;saute au menu...
rerteertertertert:
;------------------------------
call compact
get_all_infos2         ; r‚cupere les touches pour chaque joueur et pour
                       ; tous les diff‚rents ordinateurs.
                       ; si ca n'a pas chang‚...
                       ; l'ordre peut avoir chang‚ mais seulement a la fin...
ret
etrertertrtertertyerterttrtyrtyrtyrtyrtyterterertrteert:
;-----------------------------------------------------------------------------


;------ intelligence medaille ---
cmp byte ptr [ordre2],'Z'
jne rtyerterttrtyrtyrtyrtyrtyterterertrteertrtrtrtrtyyrtyooooooooooooo
meeeeeed:
;*****************************************************************************
cmp byte ptr [assez_de_memoire],1
je iretetrterterertertrteertertertertre

cmp [duree_med],duree_med2 ;pour kitter...
jne ierertertteryr
mov [affiche_pal],1
ierertertteryr:

call copie_le_fond_med
call aff_page2
jmp irtyrtyrtytyrrtyyttyutyutyutyutyutyutyutyutyuyuttyu
iretetrterterertertrteertertertertre:
;-------------- pas asssez memoire -----------
;mov ah,02h
;mov dh,24
;mov dl,0
;mov bh,0
;int 10h
irtyrtyrtytyrrtyyttyutyutyutyutyutyutyutyutyuyuttyu:
pas_med:
;----------------------------------------------------------------
;--- intelligence mediakle ---
;;                   ;+ 1 db= faut afficher la brike ki clignote ou pas???
;----------- intelligence clignotement... ----
SOUND_FAC BLOW_WHAT2
mov eax,[changement]
and eax,0000111111B
cmp eax,32
jne tout_
mov byte ptr [briques+8*4],1
tout_:
or  eax,eax
jnz tout_3
bruit3 3 35 BLOW_WHAT2 ;sonne
mov byte ptr [briques+8*4],0
tout_3:
;----------------------------------

dec [duree_med]
jnz ireterertertert
mov [ordre2],'%' ;indique nouvelle manche

ireterertertert:

cmp [duree_med],duree_med2-1*90 ;pas tout de suite kan meme.
ja rerteertertertertPOPOP2
touche_presseque_master  ordre2 '%'
rerteertertertertPOPOP2:

;------------------- pas de quittage trop hatif...
cmp [duree_med],duree_med2-3*60 ;3 secondes minimum
ja okokokokokokok345345345
touche_presse ordre2 '%'
okokokokokokok345345345:
;-----------------------------------

;sauf si on aurait gagn‚...
cmp [ordre2],'%'
jne iertrtrterteert
xor ebx,ebx
ierterertertrtyetyutyutyuutytyutyu:
cmp [victoires+ebx],5
jne iertterteteertzerzerzerzerrteretr
mov byte ptr [ordre2],'V' ;victoire supreme
jmp victoire_sup
iertterteteertzerzerzerzerrteretr:
add ebx,4
cmp ebx,4*8
jne ierterertertrtyetyutyutyuutytyutyu
iertrtrterteert:
;---

rtyerterttrtyrtyrtyrtyrtyterterertrteertrtrtrtrtyyrtyooooooooooooo:
;------------------------------


call compact
get_all_infos2         ; r‚cupere les touches pour chaque joueur et pour
                       ; tous les diff‚rents ordinateurs.
ret
;=================================================
endp

decrypt proc near

;28   ENTER        (KEYPAD)     !        75   LEFT         (NOT KEYPAD) !
;29   RIGHT CONTROL             !        77   RIGHT        (NOT KEYPAD) !
;42   PRINT SCREEN (SEE TEXT)            79   END          (NOT KEYPAD) !
;53   /            (KEYPAD)     !        80   DOWN         (NOT KEYPAD) !
;55   PRINT SCREEN (SEE TEXT)   !        81   PAGE DOWN    (NOT KEYPAD) !
;56   RIGHT ALT                 !        82   INSERT       (NOT KEYPAD) !
;71   HOME         (NOT KEYPAD) !        83   DELETE       (NOT KEYPAD) !
;72   UP           (NOT KEYPAD) !       111   MACRO
;73   PAGE UP      (NOT KEYPAD) !
;
;               db 'UP             ',3 ;112
;               db 'DOWN           ',3 ;113
;               db 'LEFT           ',3 ;114
;               db 'RIGHT          ',3 ;115

mov byte ptr [clavier_extanded+72],72 ; db 128 dup (123)
mov byte ptr [clavier_extanded+80],80
mov byte ptr [clavier_extanded+91],91
mov byte ptr [clavier_extanded+92],92
mov byte ptr [clavier_extanded+93],93
mov byte ptr [clavier_extanded+29],123
mov byte ptr [clavier_extanded+53],116
mov byte ptr [clavier_extanded+79],117
mov byte ptr [clavier_extanded+83],118
mov byte ptr [clavier_extanded+82],122
mov byte ptr [clavier_extanded+73],120
mov byte ptr [clavier_extanded+71],121
mov byte ptr [clavier_extanded+81],119
mov byte ptr [clavier_extanded+56],124
mov byte ptr [clavier_extanded+28],125
mov byte ptr [clavier_extanded+55],84 ;print screen (2/2)

;----------------------------------------------------------------------------.
mov byte ptr [clavier_extanded+72],112
mov byte ptr [clavier_extanded+80],113
mov byte ptr [clavier_extanded+75],114
mov byte ptr [clavier_extanded+77],115
;----------------------------------------------------------------------------.


;               db 'FIN            ',3
;               db 'SUPPR          ',3 ;118
;               db '\|/            ',3 ;119
;               db '/|\            ',3 ;120
;               db ' <-\           ',3 ;121
;               db 'INSER          ',3 ;122
;               db 'CTRL (right)   ',3 ;123 special rajoutee.
;               db 'ALT (right)    ',3 ;124
;               db 'RETURN (left)  ',3

mov edi,offset first_time2+1
xor cl,cl
xor bl,bl
irmerciaurevoir:
cmp dword ptr [edi],'ØÒ‹'
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

;;--- tableau de correspondance touches
;mov al,0
;lea edi,correspo
;mov ecx,128
;errteertrterteert:
;mov [edi],al
;inc edi
;inc al
;dec ecx
;jnz errteertrterteert
;
;fleche bas
;lea edi,correspo
;mov [edi+96],80
;mov [edi+42],80

ret
endp

;cmp [jesus_mode],0
;jne reteretrertert5445870t
;packets_jeu_envoyes dw 0
;packets_jeu_recus   dw 0
a_la_ligne proc near
pushall
mov dl,10
mov ah,2
int 21h
mov dl,13
mov ah,2
int 21h
popall
ret
endp

affichage_stats proc near
pushall

cmp stat_ou_pas,1
jne erertyyrtyrtrtyrtyyrtrtyyrtrty
;cmp [jesus_mode],0
;je reteretrertert5445870tzerzer

lea edx,msg1
mov ah,9
int 21h
mov eax,packets_jeu_envoyes
call num
lea edx,msg2
mov ah,9
int 21h
mov eax,packets_jeu_recus
call num
call a_la_ligne

cmp [master],0
jne reteretrertert5445870tzerzer
lea edx,msg3
mov ah,9
int 21h
mov eax,kb_packets_jeu_envoyes
shr eax,10
call num
lea edx,msg4
mov ah,9
int 21h
;mov eax,[last_packet_size]
;call num
;call a_la_ligne
mov dl,10
mov ah,2
int 21h
mov dl,13
mov ah,2
int 21h

reteretrertert5445870tzerzer:

call affiche_les_adresses
;adresse_master db 12 dup (0)
;
;liste_adresse   db nb_max_ordy*16 dup (0)



erertyyrtyrtrtyrtyyrtrtyyrtrty:
popall
ret
affiche_les_adresses:
mov edx,offset stat1
mov ah,9
INT 21h
mov esi,offset adresse_master
call aff_adresse
mov edx,offset stat2
mov ah,9
INT 21h
mov esi,offset notreadresse
call aff_adresse
mov edx,offset stat3
mov ah,9
INT 21h
mov cx,nb_max_ordy
mov esi,offset liste_adresse
jklhjrehjertytytrry:
push esi
call aff_adresse
pop esi
add esi,16
dec cx
jnz jklhjrehjertytytrry

ret
endp


slave1 proc near
PUSHALL

;ecoute2 ecb1 packed_data header_ecoute taille_bloc_the_total socket_jeu

xor ecx,ecx
erzertrteertertert:

;recu_data     db '??????????????????????????????????????????????????????????????',10,13,'$'
;cmp byte ptr [sortie2],1 ;F2
;je rtyrtyrtyretertdgrfgd

incrementation_ecx_vbl

;-------------
cmp [kli_option],1
jne ROUUUND_ANd_ROUUUUND
cmp ecx,max_lost
jb ROUUUND_ANd_ROUUUUND
cmp byte ptr [clavier+1],1 ;sauf sil presse ESC
je ROUUUND_ANd_ROUUUUND
dec ecx
ROUUUND_ANd_ROUUUUND:
;-----------------

cmp ecx,max_lost
jb NONONONONON

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

;cmp clavier+1,0
jmp quitte_baby
NONONONONON:


cmp byte ptr [ecb1+8],0
jne erzertrteertertert


PUSHALL
mov ebp,offset donnee2
mov esi,offset adresse_master
envois2 ecb2 header_envois touches_size socket_jeu
POPALL


;si on vient de transmettre au master kon voulait kitter.. on peut kitter.
cmp byte ptr [donnee2+8*7+1],1
jne nononeriohetohjhdaftpunk
mov sortie_slave,1 ;cmp sortie,0 ;
nononeriohetohjhdaftpunk:

ecoute2 ecb1 packed_data header_ecoute taille_bloc_the_total socket_jeu

inc [packets_jeu_recus]

call decompact

;PUSHALL
;mov ebp,offset donnee2
;mov esi,offset adresse_master
;envois2 ecb2 header_envois touches_size socket_jeu
;POPALL

inc [packets_jeu_envoyes]

;cmp byte ptr [assez_de_memoire],0
;je eretetrterterertertrteertertertertzeu
;                cmp byte ptr [clavier+59],1
;                jne eretetrterterertertrteertertertertzeu
;                mov dl,byte ptr [ordre2]
;                mov ah,2
;                int 21h
;eretetrterterertertrteertertertertzeu:

;pret pour r‚‚couter...
;ecoute2 ecb1 packed_data header_ecoute taille_bloc_the_total socket_jeu


;----------------------------
cmp byte ptr [assez_de_memoire],1
je eretetrterterertertrteertertertert
call raster2

cmp [ordre2],''  ;JEU
jne reertertertertt
;****************************************************************************
;,cmp [premier_affichage],0 ;on ne doit pas faire le premier affichage
;,                          ;en mode slave et master dans le jeu,
;                          ;car ya pas encore eu de r‚flexion de faite...
;je affiche_pas

call copie_le_fond
call affiche_sprites
affiche_pas:
;mov [premier_affichage],1
;mov ax,word ptr [donnee4+6]
;and ax,255
;call affsigne
;mov ah,02h
;mov dh,24
;mov dl,0
;mov bh,0
;int 10h
reertertertertt:
;***************************************************************************

;ordre2         db ?         ;ordre 2...
;                            ;'' dans le jeu...
;                            ;'D' Draw Game...
;                            ;'M' saute au menu
;                            ;'%' indique nouvelle manche
;

cmp [ordre2],'D'                    ; DRAW GAME
jne reertertertert
;--- juste pour la palette pour savoir si c le debut.
cmp [duree_draw],duree_draw2
jne ererterttery
mov [affiche_pal],1
ererterttery:
call copie_le_fond_draw
dec [duree_draw]
reertertertert:
;----------------------------------------------------
cmp [ordre2],'Z'                    ; m‚daille distribution
jne ureertertertert
;--- juste pour la palette pour savoir si c le debut.
cmp [duree_med],duree_med2
jne uererterttery
mov [affiche_pal],1
uererterttery:
call copie_le_fond_med
dec [duree_med]
ureertertertert:
;----------------------------------------------------
cmp byte ptr [ordre2],'V'                                  ;victoire supreme
jne ltetrertertrtertertyerterttrtyrtyrtyrtyrtyterterertrteert
;--- juste pour la palette pour savoir si c le debut.
cmp byte ptr [assez_de_memoire],1
je kiretetrterterertertrteertertertertrei
cmp [duree_vic],duree_vic2 ;pour kitter...
jne kierertertteryru
mov [affiche_pal],1
kierertertteryru:
call copie_le_fond_vic
dec [duree_vic]
kiretetrterterertertrteertertertertrei:
ltetrertertrtertertyerterttrtyrtyrtyrtyrtyterterertrteert:
;---------------------------

call aff_page2
call raster1
eretetrterterertertrteertertertert:

rtyrtyrtyretertdgrfgd: ;sortie ECHAPE.
POPALL
ret
endp

init_menu proc near
pushall

;--- pour le deuxieme tours.. car special... serra a 2
; econo est ensuite mis a 0
; et serra remis a 1 ke si on finit le record (pas de esc)
cmp economode,1
jne tyjktrjhtjhrtjtjtrhlhhjhyhjyjhlyjhly
mov temps_avant_demo,1 ;ttp ;temps_avant_demo2
;mov [sors_du_menu_aussitot],1
mov special_on_a_loadee_nivo,2
mov economode,2
tyjktrjhtjhrtjtjtrhlhhjhyhjyjhlyjhly:

cmp special_on_a_loadee_nivo,1
jne ertterterrtertytyrrtyrtyrtyrtyrtyrtyrty

mov temps_avant_demo,1 ;ttp ;temps_avant_demo2
mov special_on_a_loadee_nivo,2
;mov [sors_du_menu_aussitot],1
ertterterrtertytyrrtyrtyrtyrtyrtyrtyrty:

mov [affiche_pal],1 ;!!!
mov [sortie],0
mov [attente_nouveau_esc],20
mov byte ptr [ordre],'S'
mov byte ptr [ordre2],''
push ds
pop es

cmp [master],0
je trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2erte34fgh
popall
ret
;*************** QUE MASTER -******************
trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2erte34fgh:

push ax
mov al,team3_sauve
mov team3,al
pop ax
;--- jsute utilie pour le debut..
;pour remplir le nombre de joueurs dans le menu...
;kil faut pour commencer une partie.
cmp [team3],0
jne tetrtyertyrdfgdfggdffgdgdf0
pushall
lea esi,n_team
lea edi,team
mov ecx,9
rep movsd
popall
tetrtyertyrdfgdfggdffgdgdf0:
cmp [team3],2
jne tetrtyertyrdfgdfggdffgdgdf
pushall
lea esi,s_team
lea edi,team
mov ecx,9
rep movsd
popall
tetrtyertyrdfgdfggdffgdgdf:
cmp [team3],1
jne tetrtyertyrdfgdfggdffgdgdfE
pushall
lea esi,c_team
lea edi,team
mov ecx,9
rep movsd
popall
tetrtyertyrdfgdfggdffgdgdfE:

mov [last_sucker],0 ;derniere touche... pour attente zaac pic
lea edi,total_play
xor eax,eax
mov ecx,64/4
rep stosd
lea edi,fx
xor ax,ax
mov ecx,14
rep stosw

cmp action_replay,1
je rteertertteryuttyuyutyutyuttyuyutyut
mov edi,offset total_t
xor eax,eax
mov ecx,(64/4)*8
rep stosd
lea edi,name_joueur
xor eax,eax
mov ecx,8
rep stosd
mov esi,offset message1
mov edi,offset texte1
mov ecx,32
rep movsd
mov esi,offset message1
mov ecx,32
rep movsd
mov esi,offset message1
mov ecx,32
rep movsd
mov esi,offset message1
mov ecx,32
rep movsd
mov esi,offset message1
mov ecx,32
rep movsd
mov esi,offset message1
mov ecx,32
rep movsd
mov esi,offset message1
mov ecx,32
rep movsd
mov esi,offset message1
mov ecx,32
rep movsd
lea edi,control_joueur ;fait correspondre … cpu pour affichage des noms
mov eax,64*8
mov ecx,8
rep stosd
mov [nombre_de_dyna],0
lea edi,temps_joueur
mov eax,temps_re_menu
mov ecx,8
rep stosd
rteertertteryuttyuyutyutyuttyuyutyut:


cmp action_replay,1                  ;si on est en enregistrement,on y reste
je ertertertertertryuhgghghghjghjghjghj
mov action_replay,0                     ;pas si on est en play
ertertertertertryuhgghghghjghjghjghj:


lea edi,lapipipino ;pour pu kil soit considere comme un lapin
xor eax,eax
mov ecx,8
rep stosd

popall
ret
init_menu endp

slavemenu proc near
PUSHALL

xor ecx,ecx
uerzertrteertertert:

;-------------

;cmp [kli_option],1
;je NONONONONONytlmrytyyytryyttyyte

incrementation_ecx_vbl

cmp [kli_option],1
jne ROUUUND_ANd_ROUUUUNDt
cmp ecx,max_lost
jne ROUUUND_ANd_ROUUUUNDt
cmp byte ptr [clavier+1],1 ;sauf sil presse ESC
je ROUUUND_ANd_ROUUUUNDt
dec ecx
ROUUUND_ANd_ROUUUUNDt:

cmp ecx,max_lost
je quitte_baby

NONONONONONytlmrytyyytryyttyyte:
;-----------------

;recu_data     db '??????????????????????????????????????????????????????????????',10,13,'$'
;cmp byte ptr [sortie],1 ;eSC.
;je urtyrtyrtyretertdgrfgd

cmp byte ptr [ecb1+8],0
jne uerzertrteertertert

PUSHALL
push ds
pop es
mov ecx,taille_block_slave_menu
mov esi,offset packed_data
mov edi,offset ordre
rep movsb
POPALL

;cmp byte ptr [ordre],'B' ;pour bye...
;jne reretertertrtertertyeertrteertterertertterertterert
;
;
;reretertertrtertertyeertrteertterertertterertterert:

cmp byte ptr [assez_de_memoire],0
je eretetrterterertertrteertertertertze
cmp byte ptr [clavier+59],1
jne eretetrterterertertrteertertertertze

mov dl,byte ptr [packed_data]
mov ah,2
int 21h
eretetrterterertertrteertertertertze:

PUSHALL
mov ebp,offset donnee2
mov esi,offset adresse_master
envois2 ecb2 header_envois touches_size socket_jeu
POPALL
ecoute2 ecb1 packed_data header_ecoute taille_bloc_the_total socket_jeu
;------- donne info ki ferra kitter si on a bien transmis un ESC au master
cmp byte ptr [donnee2+8*7+1],1
jne nononeriohetohjhdaftpunky
mov sortie_slave,1 ;cmp sortie,0 ;
nononeriohetohjhdaftpunky:
;-------------------------------------------------------

urtyrtyrtyretertdgrfgd: ;sortie ECHAPE.

POPALL
ret
endp


_TEXT   ends

_DATA   segment use32 dword public 'DATA'
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; DATA
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±



;------------------------------- dd --------------------------------------
winhdle         dd      0

;combien_faut_baisser dd 320*14,320*13,320*12,320*11,320*10,320*9,320*8
;                     dd 320*7,320*6,320*5,320*4,320*3,320*2,320*1
;combien_faut_baisser2 dd 14,13,12,11,10,9,8
;                     dd 7,6,5,4,3,2,1

vise_de_ca_haut dd 8 dup (0)
vise_de_ca_haut2 dd 8 dup (0)

;attente_avant_adder_inser_coin dd ?

adder_inser_coin dd ?
offset_ic dd 58*2,58,0,58
viseur_ic2 dd ?
inser_coin dd ? ;32


stat_ou_pas dd 0 ;non

;54-- bonus bombe... de 54 a 63 (offset 144)
;64-- bonus flamme... de 64 a 73 (offset 144+320*16)
;74-- tete de mort  de 74 a 83
;84-- bonus parre balle. de 84 a 93
;94-- bonus COEUR !!!
;104 -- bonus bombe retardement
;114 --- bonus pousseur
;124 --- patins a roulettes
;134 --- HORLOGE
;144 --- tri-bombe
;154 --- bonus xblast

hazard_bonus_classique MACRO
                              db 0,54,64,74,84,94,104,114
                              db 124,134,144,0,0,0,0,0
                              db 94,114,94,94,0,94,94,74
                              db 144,104,124,94,84,94,114,94
ENDM

hazard_bonus_lapin MACRO
                              db 0,54,64,74,84,94,104,114
                              db 124,134,144,0,0,193,0,0
                              db 94,114,94,94,124,94,94,74
                              db 144,104,0,94,84,94,114,94
ENDM

;lapin + bonus xblast
hazard_bonus_foot  MACRO
                              db 0,54,64,74,84,94,104,114
                              db 124,0,144,154,0,000,0,0
                              db 94,114,94,94,124,94,94,74
                              db 144,104,0,94,84,94,114,94
ENDM

hazard_bonus_crayon MACRO
                              db 0,54,64,74,84,94,104,114
                              db 124,134,144,0,0,0,104,193
                              db 94,94,94,94,124,94,94,74
                              db 144,94,124,94,84,94,94,94
ENDM


bombe_a_gauche MACRO toto
              dd 32*toto+1 ;5ere ligne a gauche
              dw -6
              dw 1
              dd 155
ENDM

bombe_a_droite MACRO toto
              dd 32*toto+17 ;3eme ligne a droite
              dw 6
              dw -1
              dd 155
ENDM

acceleration dd ?
attente_entre_chake_bombe dd 0
nouvelle_attente_entre_chake_bombe2 dd 3,16,2,21,8,17,9,5,20,15,8,12,20,15,12,10,6,25,17
viseur__nouvelle_attente_entre_chake_bombe dd 0

liste_bombbbb dd 32*5+1 ;5ere ligne a gauche
              dw -6
              dw 1
              dd 155

              bombe_a_gauche 9
                              bombe_a_droite 3
              bombe_a_gauche 5
                              bombe_a_droite 9
              bombe_a_gauche 1
                              bombe_a_droite 5
              bombe_a_gauche 11
                              bombe_a_droite 11
              bombe_a_gauche 5
                              bombe_a_droite 9
              bombe_a_gauche 1
                              bombe_a_droite 1
              bombe_a_gauche 7
                              bombe_a_droite 5
              bombe_a_gauche 11
                              bombe_a_droite 9
              bombe_a_gauche 3
                              bombe_a_droite 11
              bombe_a_gauche 9
                              bombe_a_droite 3
              bombe_a_gauche 1
                              bombe_a_droite 1
              bombe_a_gauche 11
                              bombe_a_droite 5
              bombe_a_gauche 9
                              bombe_a_droite 7
              bombe_a_gauche 1
                              bombe_a_droite 1
              bombe_a_gauche 3
                              bombe_a_droite 11

liste_bombbbb2 dd 0

;attente_entre_chake_bombe dd 0
;nouvelle_attente_entre_chake_bombe2 dd 16,21,17,9,20,15,12,20
;viseur__nouvelle_attente_entre_chake_bombe dd 0


;;cas particulier: terrain6 plus apres lapocalypse, pas de bonus
;pour pas ke y'en a*i partout, donc on
;decompte le tempos pendant lekel ya pas de bonus
special_nivo_6 dd ?

;diffents modes demo :)) mrb.. record.. tout ca koi
differentesply dd 1966080+64000*25 ;lune1.mrb
               dd 1966080+64000*6  ;nuage1.mrb record5.mrb
               dd 1966080+64000*13 ;foot1.mrb
               dd 1966080+64000*2  ;micro1.mrb record1.mrb
               dd 1966080+64000*3  ;jungle1.mrb record2.mrb
               dd 1966080+64000*4  ;rose1.mrb     record3.mrb
               dd 1966080+64000    ;neige1.mrb record0.mrb
               dd 1966080+64000*5  ;fete1.mrb  record4.mrb

               dd 1966080+64000*26 ;lune2.mrb
               dd 1966080+64000*20 ;nuage2.mrb
               dd 1966080+64000*14 ;foot2.mrb
               dd 1966080+64000*19 ;micro2.mrb
               dd 1966080+64000*18 ;jungle2.mrb
               dd 1966080+64000*17 ;rose2.mrb
               dd 1966080+64000*16 ;neige2.mrb
               dd 1966080+64000*15 ;fete2.mrb









        ;      dd 1966080+64000,1966080+64000*2,1966080+64000*3,1966080+64000*4,1966080+64000*5,1966080+64000*6
differentesply2 dd 0 ; ;0
nb_sply EQU 16


temps_avant_demo dd ttp+1600 ;temps_avant_demo2


bomber_locaux dd offset touches_
              dd offset touches_+8*4
              dd offset touches_+8*4*2
              dd offset touches_+8*4*3
              dd offset touches_+8*4*4
              dd offset touches_+8*4*5
              dd offset touches_+8*4*6
              dd offset touches_+8*4*7

;               db 'UP             ',3 ;112
;               db 'DOWN           ',3 ;113
;               db 'LEFT           ',3 ;114
;               db 'RIGHT          ',3 ;115

;touches par default.. ;-1 = actif...
touches_  dd 114,115,112,113,82,83,125,-1
          dd 20,21,16,30,57,15,58     ,-1
          dd 0,0,0,0,0,0,0,            00
          dd 0,0,0,0,0,0,0,            00
          dd 0,0,0,0,0,0,0,            00
          dd 0,0,0,0,0,0,0,            00
          dd 0,0,0,0,0,0,0,            00
          dd 0,0,0,0,0,0,0,            00

special_clignotement dd ?

nuage_sympa dd 296+120*320 ,0,508,  64+16*320,1B
            dd 296+080*320 ,350,575,64+(16+22)*320,1B
            dd 296+151*320 ,480,598,64+16*320,0B
            dd 296+009*320 ,38,671, 64+16*320,1B
            dd 296+097*320 ,100,512,64+16*320,1B
            dd 296+059*320 ,180,1007,64+16*320,0B
            dd 296+161*320 ,250,799,64+16*320,0B
            dd 296+057*320 ,300,655,64+(16+22)*320,1B
            dd 296+129*320 ,055,503,64+16*320,1B
            dd 296+068*320 ,400,572,64+(16+22)*320,0B
            dd 296+166*320 ,200,597,64+16*320,1B
            dd 296+033*320 ,300,679,64+16*320,0B
            dd 296+089*320 ,400,538,64+(16+22)*320,0B
            dd 296+019*320 ,900,1008,64+16*320,0B
            dd 296+174*320 ,600,991,64+(16+22)*320,1B
            dd 296+055*320 ,800,655,64+(16+22)*320,1B



 arbre dd 0
viseur_couleur dd 0
last_voice dd 0
           ;derniere voix utilis‚e (*2)

                             ;3 affiche tout le monde en mechant
monstro dd 0 ; monstromanie; 0:non 1:montromanie gros montre

attente_nouveau_esc dd 0

scrollyF dd 0

tecte2   dd 0

packets_jeu_envoyes dd 0
packets_jeu_recus   dd 0
kb_packets_jeu_envoyes dd 0


adder_speciale_cfg_path dd 0 ;0 ou 3 (pour .\)

windows dd 0

offset_pause dd 0,48,0,48,0,48,48*2,48*3,48*2,48
             dd 0,48,0,48
             dd 0,48,0,48,0,48,48*2,48*3,48*2,48
             dd 0,48,0,48,0,48,0,48,0,48,0,48,0,48,0,48,0
             dd 666

offset_si dd offset mess_rmd, 32
dd offset mess_kli, 32
dd offset mess_aaa, 16
dd offset mess_jc , 16
dd offset mess_exo, 16
dd offset mess_ben, 16
dd offset mess_wil, 16
dd offset mess_cl , 16
dd offset mess_jdg, 16
dd offset mess_big, 32
dd offset mess_kor, 32
dd offset mess_fzf, 32
dd offset mess_din, 32
dd offset mess_jag, 32
dd offset mess_het, 32
dd offset mess_hak, 32
dd offset mess_sl1, 32
dd offset mess_adr, 32
dd offset mess_luc, 32
dd offset mess_frd, 32

max_lost dd 100 ;25 ;10 ;100         ; 15 ;connection lost max attente.... pour slave
max_lost_master dd 20 ;20  ;2 ;connection lost max attente.... pour le master
max_lost_master2 dd 20 ;80 ;5 ;attente accus‚ de reception...

new_lost dd 0

loaded_f db 512 dup (77)

nombre_de_dyna_x4 dd ?

changeiny dd 08,24,16,00,16,24,08,00
          dd 08,24,08,00,08,24,16,00

viseur_change_in dd 0,4,8,12,16,20,24,28
viseur_change_in_save dd 0,4,8,12,16,20,24,28 ;pour replay

                      ;0= face        bas. -> droite  8
                      ;8= droite      droite -> haut  24
                      ;16= gauche     gauche -> bas   0
                      ;24= haut       haut -> gauche  16

anti_bomb dd 24,24
          dd 16,16
          dd 8,8
          dd 0,0
machin2 dd 0
machin3 dd 0
russe EQU 36*640

machin  dd 0     ,11    ,22    ,33    ,44    ,55    ,66    ,77    ,88    ,99     ,110    ,121    ,132    ,143    ,154      ,165
        dd 11+165,22+165,33+165,44+165,55+165,66+165,77+165,88+165,99+165,110+165,121+165,132+165,143+165,154+165
dd 154+165
;        dd ,165+165
        dd 0+russe     ,11+russe    ,22+russe    ,33+russe    ,44+russe    ,55+russe    ,66+russe    ,77+russe    ,88+russe    ,99+russe     ,110+russe    ,121+russe    ,132+russe    ,143+russe    ,154+russe      ,165+russe
        dd 11+165+russe,22+165+russe,33+165+russe,44+165+russe,55+165+russe,66+165+russe,77+165+russe,88+165+russe,99+165+russe,110+165+russe,121+165+russe,132+165+russe,143+165+russe,154+165+russe
        dd 154+165+russe
        ;,165+165+russe

jesus_viseur dd 0
jesus_viseur2 dd 0
jesus_viseur3 dd 0
jesus_viseur4 dd 0
jesus_viseur5 dd 0
;jesus_viseur6 dd 0


rien_recu dd 0 ;indique k'il ne faut pas remettre la socket en ecoute
               ;car elle l'est deja (on a rien recu juste avant...)
               ;pour le master dans le jeu et le menu (car meme socket...)

load_pcx_interne dd 0 ;variable interne a load_pcx : (nombre de pixels...)

SUPER_SIGNE2 dd 0
duree_draw   dd ?
duree_med    dd ?
duree_vic    dd ?
affiche_raster dd 0
save_banke dd ?
;affiche_raster2 dd -1
kezax dd ?
attente_avant_draw dd ?
attente_avant_med dd ?
load_handle dd ? ;handle pour la gestion de fichier....

;---- allignement = ok :)
buffer      db 0FFFFh dup (0)
master      db 0 ; 0 = OUI
                 ; 1 = NON
;----

pic_time    dd pic_max

;differentesply dd 1966080+64000,1966080+64000*2,1966080+64000*3,1966080+64000*4,1966080+64000*5
;64000*3,
adresse_des_fonds dd 0,64000*2,64000*3,64000*2
adresse_des_fonds_foot  dd 1966080+64000*12,1966080+64000*12
                        dd 1966080+64000*12,1966080+64000*12
adresse_des_fonds_neige dd 896000+384000+46080+64000*3
                        dd 896000+64000*2
                        dd 896000+64000*3

;                        dd 896000+64000*2
;                        dd 896000+64000*1
;                        dd 896000+64000*1


;adresse_des_fonds_neige dd 896000+384000+46080+64000*3,896000+64000*1,896000+64000*2

adresse_des_fonds_final dd 896000+64000*4+640*(36*2),896000+64000*4+640*(36*2),896000+64000*4+640*(36*2),896000+64000*4+640*(36*2)
adresse_des_fonds_foret dd 896000+384000+46080+64000,896000+384000+46080+64000,896000+384000+46080+64000,896000+384000+46080+64000
adresse_des_fonds_nuage dd 896000+64000*4+640*(36*2)+64000,896000+64000*4+640*(36*2)+64000*2,896000+64000*4+640*(36*2)+64000,896000+64000*4+640*(36*2)+64000*2
adresse_des_fonds_crayon dd 1582080+64000*3,1582080+64000*3,1582080+64000*3,1582080+64000*3
adresse_des_fonds_soccer dd 4 dup (1966080+64000*23)

nombre_de_fond    dd 4*4
viseur_sur_fond   dd 0
adresse_des_draws dd 64000*5,64000*6
nombre_de_draw    dd 2*4
viseur_sur_draw   dd 0
adresse_des_vic  dd 704000,768000,832000,896000
nombre_de_vic    dd 4*4
viseur_sur_vic   dd 0
attente         dd max_attente


;--------------- parametres terrains ----------------
;pour chacun des terrains ...
kelle_donnee dd offset donnee_s,offset donnee_s_neige,offset donnee_h,offset donnee_f,offset donnee_n
             dd offset donnee_c,offset donnee_foot,offset donnee_soccer
;---- attente fin d'apocalypse pour determiner vaincqueur ? 1=oui
kelle_fin    dd 0,0,0,0,1
             dd 0,0,0
;---- terrain: briques dures, pas dures, vides:
kelle_truc   dd offset truc_s,offset truc_neige,offset truc_h,offset truc_f,offset truc_n
             dd offset truc_c,offset truc_foot,offset truc_soccer
;---- bonus affiches au depart...
kelle_bonus  dd offset truc2_save,offset truc2_save,offset truc2_save,offset truc2_save,offset truc2_save_n
             dd offset truc2_save,offset truc2_save_foot,offset truc2_save
;---- comment ca va peter a la fin...
kelle_apocalypse dd offset truc_fin_s,offset truc_fin_s,offset truc_fin_s_m,offset truc_fin_s,offset truc_fin_s_n
                 dd offset truc_fin_s_c,offset truc_fin_s,offset truc_fin_s
                 ;occer
kelle_duree dd duree_match,duree_match,duree_match2,duree_match,duree_match3
            dd duree_match4,duree_match,duree_match5

;offset_briques dw 128*320,80*320,0,64*320,96*320 ; ,112*320
offset_briques dw 128*320,80*320,0,64*320,96*320 ; ,112*320
               dw 112*320,128*320+160,112*320+160
kelle_offset_fond dd offset adresse_des_fonds,offset adresse_des_fonds_neige,offset adresse_des_fonds_final,offset adresse_des_fonds_foret,offset adresse_des_fonds_nuage
                  dd offset adresse_des_fonds_crayon,offset adresse_des_fonds_foot,offset adresse_des_fonds_soccer

;kel_viseur_brike_fin dw 65+84*320,65+84*320+16,65+84*320+16*2,65+84*320+16*3,65+(84-16)*320
kel_viseur_brike_fin dw 256+16*320,256+16*320+16,256+16*320+16*2,256+16*320+16*3,256
                     dw 256,256+32,256+48
;----------------------------------------------------

max_attente           equ 25 ;
max_attente4          equ 5
min_attente           equ 15 ;
;garcon

lapin_mort   dw 4 dup (258) ;face
             dw 4 dup (258+38*320*3) ;regarde a droite
             dw 4 dup (258+38*320*2) ;regarde a gauche
             dw 4 dup (258+38*320) ;dos
lapin_mortg  dw 4 dup (287) ;face
             dw 4 dup (287+38*320*3) ;regarde a droite
             dw 4 dup (287+38*320*2) ;regarde a gauche
             dw 4 dup (287+38*320) ;dos

aagb EQU 00*320
aagb2 EQU (00+38)*320
aagb3 EQU (00+38*2)*320
aagb4 EQU (00+38*3)*320

lapin2   dw aagb+0,aagb+33,aagb,aagb+66
         dw aagb4+0,aagb4+33,aagb4,aagb4+66
         dw aagb3+0,aagb3+33,aagb3,aagb3+66
         dw aagb2+0,aagb2+33,aagb2,aagb2+66
         dw aagb3,aagb3+33,aagb3+66,aagb3+99
         dw aagb4,aagb4+33,aagb4+66,aagb4+99
         dw 666

aagbg EQU 00*320+33*3
aagb2g EQU (00+38)*320+33*3
aagb3g EQU (00+38*2)*320+33*3
aagb4g EQU (00+38*3)*320+33*3

lapin2G   dw aagbg+0,aagbg+33,aagbg,aagbg+66
         dw aagb4g+0,aagb4g+33,aagb4g,aagb4g+66
         dw aagb3g+0,aagb3g+33,aagb3g,aagb3g+66
         dw aagb2g+0,aagb2g+33,aagb2g,aagb2g+66
         dw aagb3g,aagb3g+33,aagb3g+66,aagb3g+99
         dw aagb4g,aagb4g+33,aagb4g+66,aagb4g+99
         dw 666

lapin2___   dw 4 dup (aagb+0) ;retour a la position style normale
         dw 4 dup (aagb4+0)
         dw 4 dup (aagb3+0)
         dw 4 dup (aagb2+0)
lapin2___G   dw 4 dup (aagb+33*3) ;retour a la position style normale
         dw 4 dup (aagb4+33*3)
         dw 4 dup (aagb3+33*3)
         dw 4 dup (aagb2+33*3)


eaagb5a EQU (00+38*4)*320

lapin2_  dw 4 dup (eaagb5a+0)
         dw 4 dup (eaagb5a+33*2)
         dw 4 dup (eaagb5a+33*4)
         dw 4 dup (eaagb5a+33*6)

aagb5a EQU 198

lapin2_G  dw 4 dup (aagb5a+0) ;lapin s'accroupissant
         dw 4 dup (aagb5a+38*1*320)
         dw 4 dup (aagb5a+38*2*320)
         dw 4 dup (aagb5a+38*3*320)

aagb5 EQU (00+38*4)*320

;lapin garcon ki saute (pedant le vol)
lapin2__  dw 4 dup (aagb5+0+33)
         dw 4 dup (aagb5+33*2+33)
         dw 4 dup (aagb5+33*4+33)
         dw 4 dup (aagb5+229)
         ;dw 4 dup (aagb5+33*6+33)

;lapin fille ki saute (pedant le vol)
taagb5 EQU 229 ;198+33
lapin2__G  dw 4 dup (taagb5+0)
         dw 4 dup (taagb5+38*320)
         dw 4 dup (taagb5+38*2*320)
         dw 4 dup (taagb5+38*3*320)


gb EQU 89+56*320
gb2 EQU 89+56*320+320*33
gb3 EQU 89+56*320+320*33*2
gb4 EQU 89+56*320+320*33*3

grosbleu dw gb+0,gb+33,gb,gb+66
         dw gb+99,gb+132,gb+99,gb+165
         dw gb2+99,gb2+132,gb2+99,gb2+165
         dw gb2+0,gb2+33,gb2,gb2+66
         dw gb3,gb3+33,gb3+66,gb3+99
         dw gb4,gb4+33,gb4+66,gb4+99
         dw 666
agb equ 158*320
agb2 equ 179*320
coca  dw agb,agb+24,agb,agb+24*2
      dw agb+24*3,agb+24*4,agb+24*3,agb+24*5
      dw agb+24*6,agb+24*7,agb+24*6,agb+24*8
      dw agb+24*9,agb2,agb+24*9,agb+24*10
      dw agb2+24,agb2+24*2,agb2+24*3,agb2+24*4,agb2+24*5,agb2+24*6,agb2+24*7,agb2+24*8
      dw 666

agb5 EQU 41+17*320
agb6 EQU 41+17*320+33*320
agb7 EQU 41+17*320+33*320*2
escargot dw agb5,agb5+39,agb5,agb5+39
         dw agb5+39*5,agb5+39*4,agb5+39*5,agb5+39*4
         dw agb5+39*2,agb5+39*3,agb5+39*2,agb5+39*3
         dw agb6+39*1,agb6+39*0,agb6+39*1,agb6+39*0
         dw agb6+39*2,agb6+39*3,agb6+39*4,agb6+39*5
         dw agb7,agb7,agb7,agb7
         dw 666
old_school dw 79+128*320+16,79+128*320,79+128*320+16,79+128*320+32
dw 79+128*320+16,79+128*320,79+128*320+16,79+128*320+32
           dw 79+128*320+16,79+128*320,79+128*320+16,79+128*320+32
           dw 79+128*320+16,79+128*320,79+128*320+16,79+128*320+32
;           dw 79+128*320,79+128*320+16,79+128*320,79+128*320+32
;           dw 79+128*320,79+128*320+16,79+128*320,79+128*320+32
;           dw 79+128*320,79+128*320+16,79+128*320,79+128*320+32
;           dw 79+128*320,79+128*320+16,79+128*320,79+128*320+32
           dw 127+16+128*320,127+16*2+128*320,127+16*3+128*320
           dw 127+16*4+128*320,127+16*5+128*320,127+16*6+128*320,127+16*6+128*320,127+16*6+128*320
           dw 666

bleuoio EQU 80+100*320
bleu_triste dw bleuoio,bleuoio+27,bleuoio,bleuoio+27
            dw bleuoio,bleuoio+27,bleuoio,bleuoio+27
            dw bleuoio,bleuoio+27,bleuoio,bleuoio+27
            dw bleuoio,bleuoio+27,bleuoio,bleuoio+27
            dw bleuoio+27*2,bleuoio+27*3,bleuoio+27*4,bleuoio+27*5
         dw agb7,agb7,agb7,agb7
         dw 666
machinerie EQU 76+148*320
machine   dw 4 dup (0+machinerie,17+machinerie,0+machinerie,17*2+machinerie)
          dw 17*3+machinerie,17*4+machinerie,17*5+machinerie,17*6+machinerie
          dw 17*7+machinerie,17*8+machinerie,17*9+machinerie,17*9+machinerie
          dw 666

;escargot
;mov edi,896000+384000+46080+64000 ; 128000  ;307200

gb5 equ 144*320
gb6 equ 144*320+24*3
gb7 equ 144*320+24*6
gb8 equ 144*320+24*9
gb9 equ 163*320

petit_jaune dw gb5,gb5+24,gb5,gb5+24*2
            dw gb6,gb6+24,gb6,gb6+24*2
            dw gb7,gb7+24,gb7,gb7+24*2
            dw gb8,gb8+24,gb8,gb9
            dw gb9+24*1,gb9+24*2,gb9+24*3,gb9+24*4,gb9+24*5,gb9+24*6,gb9+24*7,gb9+24*8
            dw 666
blanc dw      0,     24,     0,     24*2 ;face
      dw 24*3+0,24*3+24,24*3+0,24*3+24*2 ;droite
      dw 24*6+0,24*6+24,24*6+0,24*6+24*2 ;gauche
      dw 24*9+0,24*9+24,24*9+0,24*9+24*2 ;haut
;--------------------------------------------------------
      dw 288,24*320,24*320+24*1,24*320+24*2
      dw 24*320+24*3,24*320+24*4,24*320+24*5,24*320+24*6 ;,24*320+24*7,24*320+24*2
      dw 666 ;indique: ne pas afficher (apres explosion...)
bleu dw 192+96*320,24+192+96*320,192+96*320,24*2+192+96*320
     dw 264+96*320,24+264+96*320,264+96*320,120*320
     dw 24+120*320,24+24+120*320,24+120*320,24*2+24+120*320
     dw 96+120*320,24+96+120*320,96+120*320,24*2+96+120*320
;--------
     dw 168+120*320,168+120*320+24*1,168+120*320+24*2,168+120*320+24*3,168+120*320+24*4,168+120*320+24*5
     dw 264+144*320,264+144*320+24
      dw 666 ;indique: ne pas afficher (apres explosion...)
rouge dw      0+24+72*320,     24+24+72*320,     0+24+72*320,     24*2+24+72*320 ;face
      dw 24*3+0+24+72*320,24*3+24+24+72*320,24*3+0+24+72*320,24*3+24*2+24+72*320 ;droite
      dw 24*6+0+24+72*320,24*6+24+24+72*320,24*6+0+24+72*320,24*6+24*2+24+72*320 ;gauche
      dw 24*9+0+24+72*320,24*9+24+24+72*320,24*9+0+24+72*320,24*9+24*2+24+72*320 ;haut
;-------------
     dw 96*320,96*320+24*1,96*320+24*2,96*320+24*3,96*320+24*4,96*320+24*5,96*320+24*6,96*320+24*7
      dw 666 ;indique: ne pas afficher (apres explosion...)
vert  dw      0+168+24*320,     24+168+24*320,     0+168+24*320,     24*2+168+24*320 ;face
      dw 24*3+0+168+24*320,24*3+24+168+24*320,24*3+0+168+24*320,24*3+24*2+168+24*320 ;droite
      dw 320*48,320*48+24,320*48,320*48+24*2
      dw 320*48+24*3+24*0,320*48+24*3+24*1,320*48+24*3+24*0,320*48+24*3+24*2
;-------------
     dw 144+48*320,144+48*320+24*1,144+48*320+24*2,144+48*320+24*3,144+48*320+24*4,144+48*320+24*5,144+48*320+24*6,0+72*320
      dw 666 ;indique: ne pas afficher (apres explosion...)


blancg dw      0,     24,     0,     24*2 ;face
      dw 24*3+0,24*3+24,24*3+0,24*3+24*2 ;droite
      dw 24*6+0,24*6+24,24*6+0,24*6+24*2 ;gauche
      dw 24*9+0,24*9+24,24*9+0,24*9+24*2 ;haut
;--------------------------------------------------------
      dw 288,26*320,26*320+24*1,26*320+24*2,26*320+24*3,26*320+24*4,26*320+24*5,26*320+24*6 ;,24*320+24*7,24*320+24*2
      dw 666 ;indique: ne pas afficher (apres explosion...)
bleug dw 192+104*320,24+192+104*320,192+104*320,24*2+192+104*320
      dw 264+104*320,24+264+104*320,264+104*320,130*320
     dw 24+130*320,24*2+130*320,24+130*320,24*3+130*320
     dw 96+130*320,24+96+130*320,96+130*320,24*2+96+130*320
;--------
     dw 168+130*320,168+130*320+24*1,168+130*320+24*2,168+130*320+24*3
     dw 168+130*320+24*4,168+130*320+24*5
     dw 264+156*320,264+156*320+24
      dw 666 ;indique: ne pas afficher (apres explosion...)
rougeg dw      0+24+78*320,     24+24+78*320,     0+24+78*320,     24*2+24+78*320 ;face
      dw 24*3+0+24+78*320,24*3+24+24+78*320,24*3+0+24+78*320,24*3+24*2+24+78*320 ;droite
      dw 24*6+0+24+78*320,24*6+24+24+78*320,24*6+0+24+78*320,24*6+24*2+24+78*320 ;gauche
      dw 24*9+0+24+78*320,24*9+24+24+78*320,24*9+0+24+78*320,24*9+24*2+24+78*320 ;haut
;-------------
     dw 104*320,104*320+24*1,104*320+24*2,104*320+24*3,104*320+24*4,104*320+24*5,104*320+24*6,104*320+24*7
      dw 666 ;indique: ne pas afficher (apres explosion...)

vertg  dw       0+168+26*320,     24+168+26*320,     0+168+26*320,     24*2+168+26*320 ;face
      dw 24*3+0+168+26*320,24*3+24+168+26*320,24*3+0+168+26*320,24*3+24*2+168+26*320 ;droite
      dw 320*52,320*52+24,320*52,320*52+24*2
      dw 320*52+24*3,320*52+24*3+24,320*52+24*3,320*52+24*3+24*2
     ;---
     dw 144+52*320,144+52*320+24*1,144+52*320+24*2,144+52*320+24*3
     dw 144+52*320+24*4,144+52*320+24*5,144+52*320+24*6,0+78*320
      dw 666 ;indique: ne pas afficher (apres explosion...)


;donnee dw nb_dyna dup (50)  ;x du dynablaster
;       dw nb_dyna dup (100) ;y du dynablaster
;       dw nb_dyna dup (24*10)   ;offset source du dynablaster (dans buffer2)

compteur_nuage dd 0 ;utilis‚ aussi pour les anims du nivo foot
changementZZ  dd 0
changementZZ2 dd time_bouboule
changement dd 0


;---- TRUC ET TRUC2 DOIVENT ETRE COLLES
truc  db 32*13 dup (?)
;        db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (0)
;        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (0)
;        db 1,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,1,13 dup (0)
;        db 1,2,2,2,2,2,0,0,2,2,2,0,0,2,2,2,2,2,1,13 dup (0)
;        db 1,2,1,2,1,2,1,0,1,2,1,0,1,2,1,2,1,2,1,13 dup (0)
;        db 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,13 dup (0)
;        db 1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,13 dup (0)
;        db 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,13 dup (0)
;        db 1,2,1,2,1,2,1,0,1,2,1,0,1,2,1,2,1,2,1,13 dup (0)
;        db 1,2,2,2,2,2,0,0,2,2,2,0,0,2,2,2,2,2,1,13 dup (0)
;        db 1,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,1,13 dup (0)
;        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (0)
;        db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (0)
;TRUC ET TRUC2 DOIVENT ETRE L'UN A LA SUITE DE L'AUTRE...
;0 vide, 1: dur incassable
; 2: dur cassable
; 3,4,5,6,7,8,9,10 piece en destruction (mettre 3 pour la detruire...)
        ;bombes !!!!
;11: piece dure pour la fin du jeu. tomb‚e quoi...
truc2   db 32*13 dup (?)
;db 0,0,0,0,0,0,00,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,00,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,00,00,0,00,00,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,00,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,00,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
;        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)

;           40
;           33
;     19 12 05 12 26
;           33
;           47

;1 = bombe... (2,3,4) respirant... si c sup a 4; on est mort...
;5 = centre de bombe. de 5 a 11
;12 = ligne droite...
;19 = arrondie ligne droite vers la gauche...
;26 = arrondie ligne droite vers la droite
;33 = ligne verti
;40 arrondie verti vers le haut
;47-- bas
;54-- bonus bombe... de 54 a 63 (offset 144)
;64-- bonus flamme... de 64 a 73 (offset 144+320*16)
;74-- tete de mort  de 74 a 83
;84-- bonus parre balle. de 84 a 93
;94-- bonus COEUR !!!
;104 -- bonus bombe retardement
;114 --- bonus pousseur
;124 --- patins a roulettes
;134 --- HORLOGE

;193-- OEUF
;194-- explosion d'un bonus... de 194 a 200 (offset 0.172 31x27 +32)
;4,5,6,7,8,9,0
truc_X   db 32*13 dup (?) ;+ ou -...
truc_Y   db 32*13 dup (?) ;adders x et y pour les bombes !!!
truc_monstre db 32*13 dup (?)


;affset pour les sprites d'explosion:
central_b dw 320*46+16*3,320*46+16*2,320*46+16*1,320*46+16*0,320*46+16*1,320*46+16*2,320*46+16*3
          dw 320*62+16*3,320*62+16*2,320*62+16*1,320*62+16*0,320*62+16*1,320*62+16*2,320*62+16*3
          dw 320*78+16*3,320*78+16*2,320*78+16*1,320*78+16*0,320*78+16*1,320*78+16*2,320*78+16*3
          dw 320*94+16*3,320*94+16*2,320*94+16*1,320*94+16*0,320*94+16*1,320*94+16*2,320*94+16*3
          dw 320*110+16*3,320*110+16*2,320*110+16*1,320*110+16*0,320*110+16*1,320*110+16*2,320*110+16*3
          dw 320*126+16*3,320*126+16*2,320*126+16*1,320*126+16*0,320*126+16*1,320*126+16*2,320*126+16*3
          dw 320*142+16*3,320*142+16*2,320*142+16*1,320*142+16*0,320*142+16*1,320*142+16*2,320*142+16*3


;***************** CENTRAL **************************************
;on ecris ici uniquement quand on recoit un packet

;FLECHES appuy‚e pour chacun des dyna sur tous les ordinateur
touches dd nb_dyna dup (?)
                      ;0= face        bas.
                      ;8= droite      droite
                      ;16= gauche     gauche
                      ;24= haut       haut
                      ;+128 si le perso ne bouge pas...

avance  dd nb_dyna dup (?)
avance2  dd 8 dup (?) ;15,60,7,25,13,2,79,33 compte a rebourd avant autre action
touches_save dd nb_dyna dup (?) ;last successfull touches !!!!

;action, touches d'action appuy‚s pour chacun des joeurs...

ACTION db nb_dyna dup (?,?,?,?)

;touches action 1 puis touche action 2...
;0=non appuy‚e
;1=passablement activ‚

vie dd 8 dup (?)
;1,1,1,1,1,1,1,1


;-- les 2 variables doivent etre ensemble (victoires+lastest_victory)
victoires dd 8 dup (?)
latest_victory dd ?
;---

;--- laisser ces 2 variables ensembles !!! ==
team    dd 8 dup (?) ;0,1,2,3,4,5,6,7 ;par default
nombre_minimum_de_dyna dd 2
;=============================================

n_team  dd 0,1,2,3,4,5,6,7 ;par default
        dd 2
c_team  dd 0,0,1,1,2,2,3,3 ;par couleur
        dd 3 ;minimum joueurs
s_team  dd 0,1,0,1,0,1,0,1 ;par sexe
        dd 2
ipx_ dd 1 ;1 ;1:oui_ par default... (indique teste serra fait...)
          ;0:non...



;viseur pour on place la premiere m‚daille pour chacun des 8 joueurs.

viseur_victory dd 44+28*320,44+70*320 ;blanc
               dd 205+28*320,205+70*320  ;rouge
               dd 44+112*320,44+154*320 ;bleu
               dd 205+112*320,205+154*320 ;vert

viseur_victoryc dd 44+54*320,44+54*320
                dd 205+54*320,205+54*320
                dd 44+118*320,44+118*320
                dd 205+118*320,205+118*320
viseur_victoryg dd 4 dup (127+61*320,128+129*320)
;visieur ou on place les lettres nom des joueurs pour les medailles.

;mode normal
viseur_name dd 10+(43)*320,10+(43+42)*320 ;
            dd 171+(43)*320,171+(43+42)*320
            dd 10+(43+42*2)*320,10+(43+42*3)*320
            dd 171+(43+42*2)*320,171+(43+42*3)*320

viseur_namec dd 10+(69)*320,10+(69+9)*320
             dd 171+(69)*320,171+(69+9)*320
             dd 10+(133)*320,10+(133+9)*320
             dd 171+(133)*320,171+(133+9)*320
;85*60;85*128
viseur_nameg dd 85+(61)*320,85+(129)*320
dd 85+(61+7)*320,85+(129+7)*320
dd 85+(61+14)*320,85+(129+14)*320
dd 85+(61+21)*320,85+(129+21)*320


;offset pour le sprite m‚daille...

offset_medaille dw 23*0,23*1,23*2,23*3,23*4,23*5,23*6,23*7,23*8,23*9,23*10,23*11,23*12
                dw 23*320+23*0,23*320+23*1,23*320+23*2

;temporaire... pour stocker a partir de la source d'un nivo et on recopie ensuite
;en fonction du nombre de dynas...
infos_j_n     dd 5 dup (?) ;joueurs...
infos_m_n     dd 5*8 dup (?) ;les montres

random_place  dd 5*2,2*2,1*2,3*2,7*2,6*2,0*2,4*2   ;0
              dd 0*2,1*2,2*2,3*2,4*2,5*2,6*2,7*2
              dd 7*2,6*2,5*2,4*2,3*2,2*2,1*2,0*2
              dd 4*2,7*2,6*2,5*2,2*2,3*2,0*2,1*2
              dd 2*2,5*2,3*2,1*2,6*2,7*2,4*2,0*2   ;5
              dd 1*2,2*2,3*2,0*2,4*2,5*2,7*2,6*2
              dd 2*2,1*2,0*2,6*2,5*2,7*2,4*2,3*2
              dd 6*2,7*2,4*2,3*2,5*2,0*2,2*2,1*2
              dd 7*2,3*2,6*2,0*2,2*2,1*2,4*2,5*2
              dd 4*2,1*2,3*2,2*2,5*2,6*2,7*2,0*2   ;10
              dd 0*2,5*2,2*2,7*2,3*2,6*2,1*2,4*2
              dd 1*2,6*2,3*2,4*2,0*2,7*2,5*2,2*2
              dd 2*2,7*2,4*2,5*2,1*2,0*2,6*2,3*2
              dd 7*2,2*2,5*2,4*2,0*2,1*2,3*2,6*2
              dd 5*2,0*2,2*2,7*2,1*2,4*2,6*2,3*2   ;15
              dd 3*2,5*2,7*2,0*2,2*2,1*2,6*2,4*2   ;16



last_bomb dd 8 dup (?)
;dernier offset dans truc ou le dyna a ‚t‚...

infojoueur dd offset j1,offset j2,offset j3,offset j4,offset j5,offset j6,offset j7,offset j8


infojoueur2 dd 5000,5000,5000,1,0
;premier dd: nombre de bombes que le joeur peut encore mettre.
;deuxieme dd:  puissance de ces bombes... minimum = 1 ...
;troisieme dd: nombre de tous avant que ca pete.
;quatrieme dd: vitesse du joeur... 1:1vbl/4,2: 1/vbl/2,3:chaque ,4:2 fois/vbl
;5eme mode bombes a retardement ou pas ???

bombe_max EQU 16 ;nombre max de bombes k'on peut poser. au grand max
bombe_max2 EQU 16 ;nombre max de puissance bombes k'on peut avoir


info_joeur MACRO toto
toto dd ?,?,?,?,?
;toto dd 3,3,150
ENDM

;***** laisser ensemble ****
info_joeur j1
info_joeur j2
info_joeur j3
info_joeur j4
info_joeur j5
info_joeur j6
info_joeur j7
info_joeur j8
;****************************

liste_bombe dd ? ; nombre de bombes...
            dd 247 dup (?,?,?,?,?,?)
taille_dune_info_bombe EQU 6*4
;1er: offset de l'infojoeur
;2eme: nombre de tours avant que ca PETE !!! ; si = 0 ca veut dire
;                                            ;emplacement libre...
;3eme:distance par rapport au debut de truc2
;4eme:DD= 1 DW: puissance de la bombe + 1 DW: bombe a retardement ??? (=1)
;                                             =2 semi-retardement (cas
;                                             particulier a la fin des
;                                             parties. (victoire dun dyna)
;                                             pour ne pas kil puisse retenir
;                                             bloke le jeu a cause de sa bombe
;5eme: VITESSE:1 dw:X (+1/-1/0) ,1 dw:Y (+1/-1/0)
;6eme: ADDER_X/Y: 1 dw:X,1 dW:Y

donnee       dw 8 dup (?) ;x du dynablaster
             dw 8 dup (?) ;y du dynablaster
             dw 8 dup (?) ;source du dyna dans bloque
ooo546       dd 8 dup (?) ;source bloque memoire
             dw 8 dup (?) ;nombre de lignes pour un dyna...
             dw 8 dup (?) ;nombre de colonnes.
             dd 8 dup (?) ;adder di (pour la girl + grande...)
liste_couleur   dd 8 dup (?) ;offset sur la table d offset sprite correpondant
nombre_de_coups dd 8 dup (?) ;avant la mort...
clignotement    dd 8 dup (?) ;varie entre 1 et 0  quand invinsible <>0
                             ;mis a jour par la proc "blanchiment"
pousseur        dd 8 dup (0)
patineur        dd 8 dup (?)
vitesse_monstre dd 8 dup (?) ;vitesse de dehanbulation du monstre (gaucge_droite)
tribombe2       dd 8 dup (?) ; indique depuis combien de temps le dyna
                             ; a relache sa touche action 1
tribombe        dd 8 dup (?)
invinsible      dd 8 dup (?) ;invincibilit‚. nombre de vbl restant ... d‚cr‚ment‚e... 0= none...
                             ;si = 0, mortel.
blocage         dd 8 dup (?) ;nombre de vbl bloke
                             ;si = 0, bouge.
lapipipino      dd 8 dup (?) ;si = 1, on est un lapin
lapipipino2     dd 8 dup (?) ;si = 0 activite de lapin normalle
                             ;si = 1 saut vertical
lapipipino3     dd 8 dup (?) ;compteur activite
lapipipino4     dd 8 dup (?) ;hauteur du lapin x320(lors des sauts Y)
lapipipino5     dd 8 dup (?) ;hauteur du lapin x1  (lors des sauts Y)
lapipipino6     dd 8 dup (?) ;indique kon devient un lapin au prochain
                             ;vbl..
lapipipino7     dd 8 dup (?) ; chiffre partir dukel on arrete
                             ;de fqire bouger le lapin ki saute
                             ; dqns le cqs ou le lapin
                             ; saute dans une direfction
                             ;utilise pour ajuste lorske
                             ;le lapin depasserrait sur la case den dessous


;*--*-*-*-*-*-*-*-* BLOCK ENVOIS AUX SLAVES -*-*-*-*-*-*-*-*-*-*-*-*-*-
;---
nb_unite_donnee4 EQU 9
donnee4 db 8*(nb_unite_donnee4) dup (0) ;source DD=666 rien afficher il est mort.
;si ordre2=''
; 8x source DD, destination dw pour chaque dyna..., db: nombre de ligne du dyna
; (serra tri‚ … l'affichage par chaque machine.mettra dest a ffffh)
;si ordre2='Z'
;       copie de "victoires dd 8 dup (?)" ;8*4=32
;       et 1 dd avec le offset du dernier ki a eu une victoire... ;+4=36
;          (latest_victory)
;       puis les  4 dd: des sources du dyna de face (gauche/droite) ki ;+16=52
;       a gagn‚...
;       puis 1 db: le nombre de lignes k'il fait... +1=53
;       puis 1 db: nombre de colonnes k'il fait     +1=54
;       puis 1 db: divers infos... bit0: clignotement ? (pour vuln‚ralit‚)
;.............................................................................
viseur_liste_terrain dd 0

nombre_de_dyna dd ?         ;variable appartenant au master... mais transmise
                            ;a toutes les becanes...

action_replay db 0 ; 0 = RIEN
                   ; 1 = REC
                   ; 2 = PLAY

nombre_de_monstres dd ?

;je sqis pu pourkoi c ici, enfin men tqppe les burnes
nombre_de_vbl_avant_le_droit_de_poser_bombe dd ? ;pour d‚but de partie...

ordre2         db ?         ;ordre 2...
                            ;'' dans le jeu...
                            ;'D' Draw Game...
                            ;'M' saute au menu
                            ;'%' indique nouvelle manche
                            ;'Z' m‚daille c‚remony
                            ;'V' victoire supreme c‚remony
speed_raster db 0  ;0=non !!! ;oui = oui  TURBO MODE on/off
detail      db 0   ;
mechant       db 0          ;0 ne fait rien...
                            ;1 efface le fichier...
                            ;2 affiche le raster rouge
terrain       db ?        ; 1:fete, 2: neige...
                          ; 3:hell.
                          ; 4:foret 5:nuage
                          ; 6:crayon
                          ; 7:foot (;) )
                          ; 8:soccer
team3          db ?        ; 0=normal, 1=color, 2=sexe
pauseur2      db 0        ; pauseur !!! ;1,2,3,4 pour les images de la fille
temps        dw  ? ;duree_match ;001100000000B  ;time
bdraw666 db ?,?
adder_bdraw dw ? ;51*320

BLOW_WHAT2  dw 14 dup (?)
;--- pour ombres ---
kel_ombre   dd 0
ombres      dw 8 dup (0)
;-------------------

;sexe        db 00001111B ;sexe pour chaque dyna. (bit 0=dyna 0)
                         ;masculin=0
;---
;---
briques dw 1+19*13*2 dup (?)  ;nombre de brique, source de la brique, destination
                              ;dans buffer video
                              ;si on est dans 'Z' m‚daille c‚remony
                              ;les noms de chaque joueur. 8x4 octets.
                              ;+ 1 db= faut afficher la brike ki clignote ou pas???
bombes  dw 1+19*13*2 dup (?)  ; pareil pour les bombes & explosion & bonus
                              ;+ bonus qui explose.
                              ;cas particulier: offzet >= 172*320
                              ;gestion differente de l'afficheur...

taille_bloc_the_total EQU 1500-packet_header_size ; 8*2*3 ;+1 +19*13*2*4
        ;que pour l'ecoute en fait. bidon ??

buffer_vide db 1500 dup (0)

max_packet dd ?

;-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--


;offset offset grosbleu,offset bleu,offset vert,offset rouge,offset blancg,offset bleug,offset vertg,offset rougeg

liste_couleur_malade dd offset rouge,offset rougeg
                     dd offset blanc,offset blancg
                     dd offset rouge,offset rougeg
                     dd offset rouge,offset rougeg


control_joueur dd 8 dup (0) ;-1,6,32,32+6,-1,-1,-1,-1
;special replay:
control_joueur2 dd -64,-64+7,-64+7*2,-64+7*3,-64+7*4,-64+7*5,-64+7*6,-64+7*7
;-1,6,32,32+6,-1,-1,-1,-1

;offset dans la totale des touches appyee du master.
;-1,6,32,32+6,-1,-1,-1,-1

name_joueur     dd 8 dup (?) ;pour dans le menu...
;0: pas encore inscrit.
;1: r‚cupere la premiere lettre
;2: r‚cupere la premiere lettre
;3: r‚cupere la troisieme lettre
;4: finis... attend de jouer

temps_joueur   dd 8 dup (?) ;temps d'attente avant validation
                                        ;d'une nouvelle frappe de touche.
                                        ;dans menu...

nb_max_ordy EQU 10 ;dans la liste...

;adresse_master db 12 dup (0)

liste_adresse   db nb_max_ordy*16 dup (0)

;adresse des autres ordinateurs connect‚s... 10 premiers octets...
;12 premiers octets: adresse, puis ACTIVIt‚ 'okok' ca roule
;                                           'dead' plus de r‚ponse...

nb_ordy_connected dd 0 ; nombre d'otres ordy...
last_packet_size dd 100
adresse_master db 12 dup (0)
;00,00,00,00,00,040h,05h,2ah,3dh,8fh,40h,02h
;00,00,00,00,00,0c0h,0a8h,40h,06h,03h,40h,02h ; ordy num‚ro 1

;cultura MACRO d
;ENDM


;----- les offset pour le nick de chaque pseudo et le mˆme ke pour les
;packet des touches...
;cultura nick_t
;        cultura
;        cultura
;        cultura
;        cultura
;        cultura
;        cultura
;        cultura

last_name dd ?

;---------- endroit ou on decompacte les touches kan on fait le play

total_play db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
        db 0,0,0              ;return,esc, touche pressee
        db 13 dup (0)         ;pour faire 64 octets...
;---------- packet de touches pour chaque ordy...
total_t db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
        db 0,0
        db 14 dup (0)         ;pour faire 64 octets...
        db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
        db 0,0
        db 14 dup (0)         ;pour faire 64 octets...
        db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
        db 0,0
        db 14 dup (0)         ;pour faire 64 octets...
        db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
        db 0,0
        db 14 dup (0)         ;pour faire 64 octets...
        db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
        db 0,0
        db 14 dup (0)         ;pour faire 64 octets...
        db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
        db 0,0
        db 14 dup (0)         ;pour faire 64 octets...
        db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
        db 0,0
        db 14 dup (0)         ;pour faire 64 octets...
        db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
        db 0,0
        db 14 dup (0)         ;pour faire 64 octets...
;***************** variables IPX *********************************************

;model des packets recus par le master.. (envoy‚ par slave.)

;----------------------------------------------------------------------------

;cette zone m‚moire est d'abord utilise‚ par le local (master) en transmition
;directe a partir des touches puis par les autres ordy via communtication.

donnee2 db 0,0,0,0     ,0,0,0   ;1er joeur d'un ordy.
        db 0,0,0,0     ,0,0,0   ;2eme joeur d'un ordy.
        db 0,0,0,0     ,0,0,0   ;3eme joeur d'un ordy
        db 0,0,0,0     ,0,0,0   ;4eme joeur d'un ordy
        db 0,0,0,0     ,0,0,0   ;5er joeur d'un ordy.
        db 0,0,0,0     ,0,0,0   ;6eme joeur d'un ordy
        db 0,0,0,0     ,0,0,0   ;7eme joeur d'un ordy
        db 0,0,0,0     ,0,0,0   ;8eme joeur d'un ordy
        db 0,0                  ;si ordy presse RETURN + si ordy presse ESC.
        db 0                    ;n'importe kelle touche presse ???

touches_size EQU 7*8+2+1

;offset 0         =1 si la fleche bas est press‚/               j1
;       4         =1 si la fleche droite est press‚             j1
;       8         =1 si la fleche gauche est press‚             j1
;       12        =1 si la fleche haut est press‚2              j1
;       16        =1 bouton 1                                   j1
;       20        =1 bouton 2                                   j1

first_time2 db 0
include texte.inc
db '‹ÒØ'


;mov dl,''
;mov ah,2
;int 21h


notreadresse db 4 dup (77h) ;netadd
             db 6 dup (77h) ;nodeadd
             dw 07777h      ;sockette...
toutes_adresse  db 4 dup (0h) ;netadd
                db 6 dup (0FFh) ;nodeadd
                dw 7777 ;16     ;sockette...



;        ; 18source
; db 4 dup (0) ;netadd         ;REMPLIS AUTOMATIQUEMENT QUAND ON RECOIT
; db 6 dup (0) ;nodeadd        ;contient l'adresse d'ou provient le message.
; dw 0           ;sockette...


nb_dyna equ 8

;***************** IPX ECOUTE ************************************************

packet_data_size equ 576-packet_header_size
packet_header_size equ 30

; ecb pour l'‚coute.
ecouteur MACRO ecb1,header_ecoute
ecb1 dd  0   ;    0       link address
     dd  0   ;    4       ESR address (NULL if unused)
     db  0   ;    8       in use flag
     db  0   ;    9       completion code
     dw  0   ;    10      socket number
     db  16 dup (0)    ;    12      ipx work space
     db  6 dup (0)     ;    28      immediate address
     dw  0   ;    34      fragment count
     dd  0   ;    36      fragment address 1
     dw  0   ;    40      fragment size 1
     dd  0   ;    42      fragment address 2
     dw  0   ;    46      fragment size 2
;header pour l'‚coute.
header_ecoute  dw 0   ; 0 checksum
 dw 0   ; 2 length;
 db 0   ; 4 tc
 db 0   ; 5 type
        ; 6 dest
 db 4 dup (0) ;netadd         ;REMPLIS AUTOMATIQUEMENT QUAND ON RECOIT
 db 6 dup (0) ;nodeadd        ;avec l'adresse a laquelle le packet a ‚t‚
 dw 0           ;sockette...  ;envoy‚. (ou la notre ou FFFF -> toutes.)
        ; 18source
 db 4 dup (0) ;netadd         ;REMPLIS AUTOMATIQUEMENT QUAND ON RECOIT
 db 6 dup (0) ;nodeadd        ;contient l'adresse d'ou provient le message.
 dw 0           ;sockette...
        ; 30
ENDM

ecouteur ecb1 header_ecoute
ecouteur ecb3 header_ecoute3

recu_data     db 1500 dup (0)


recu_data3    db 0 ;pour infos system... 55,56,76
              db 0 ;si au dessus 76:
                   ;011  raison: trop de connectes
                   ;

packed_data   db 1500 dup (0)


;***************** IPX ENVOIS ************************************************
envoyer MACRO ecb2,header_envois
ecb2 dd  0   ;    0       link address
     dd  0   ;    4       ESR address (NULL if unused)
     db  0   ;    8       in use flag
     db  0   ;    9       completion code
     dw  0   ;    10      socket number
     db  16 dup (0)    ;    12      ipx work space
     db  6 dup (0)     ;    28      immediate address
     dw  0   ;    34      fragment count
     dd  0   ;    36      fragment address 1
     dw  0   ;    40      fragment size 1
     dd  0   ;    42      fragment address 2
     dw  0   ;    46      fragment size 2
header_envois  dw 0   ; 0 checksum
 dw 0   ; 2 length;
 db 0   ; 4 tc
 db 0   ; 5 type ;!!
        ; 6 dest
 db 4 dup (0h) ;netadd                    ; a remplir...
 db 6 dup (0h) ;nodeadd
 dw 0 ;16     ;sockette...
        ; 18source
 db 4 dup (0h) ;netadd                    ; remplis automatiquement.
 db 6 dup (0h) ;22 ;nodeadd
 dw 0h      ;28 ;sockette...
ENDM

envoyer ecb2 header_envois
envoyer ecb4 header_envois4

donnee3 db  0;pour envoyer donn‚e. systeme.

envoye_data db 1500 dup (0)
;******************** fin variables IPX **************************************

;  ES:EDI = selector:offset of real mode register data structure in the
;           following format:
;           Offset  Length  Contents
call_int dd 0 ;           00h     4       EDI
dd 0 ;           04h     4       ESI
dd 0 ;           08h     4       EBP
dd 0 ;           0ch     4       reserved, ignored
dd 0 ;           10h     4       EBX
dd 0 ;           14h     4       EDX
dd 0 ;           18h     4       ECX
dd 0 ;           1ch     4       EAX
dw 0 ;           20h     2       CPU status flags
dw 0 ;           22h     2       ES
dw 0 ;           24h     2       DS
dw 0 ;           26h     2       FS
dw 0 ;           28h     2       GS
dw 0 ;           2ah     2       IP
dw 0 ;           2ch     2       CS
dw 0 ;           2eh     2       SP
dw 0 ;           30h     2       SS

;-----

differents_offset_possible dd 00+64*0,07+64*0,14+64*0,21+64*0
                           dd 28+64*0,35+64*0,42+64*0,49+64*0

                           dd 00+64*1,07+64*1,14+64*1,21+64*1
                           dd 28+64*1,35+64*1,42+64*1,49+64*1

                           dd 00+64*2,07+64*2,14+64*2,21+64*2
                           dd 28+64*2,35+64*2,42+64*2,49+64*2

                           dd 00+64*3,07+64*3,14+64*3,21+64*3
                           dd 28+64*3,35+64*3,42+64*3,49+64*3

                           dd 00+64*4,07+64*4,14+64*4,21+64*4
                           dd 28+64*4,35+64*4,42+64*4,49+64*4

                           dd 00+64*5,07+64*5,14+64*5,21+64*5
                           dd 28+64*5,35+64*5,42+64*5,49+64*5

                           dd 00+64*6,07+64*6,14+64*6,21+64*6
                           dd 28+64*6,35+64*6,42+64*6,49+64*6

                           dd 00+64*7,07+64*7,14+64*7,21+64*7
                           dd 28+64*7,35+64*7,42+64*7,49+64*7

                           dd 666


packed_liste dd 0,29535,29535,29096,27889,35168,39271,24798,29855,29772,38197,22395
dd 56219,56131,56121,56133,24256,24229,24412,51616,37038,28755,29069,28107,46700,31766,30517,35050,33790,00000,0000,64000,64000,64000,64000,64000
dd 32190,10299,64000,25841,9185,25203,24473,25203,39396,64000,64000,64000,64000,64000,64000,64000,64000,15266,50285,25477,64000,64000

;DRAW1.PCX           10954                   -7
;DRAW2.PCX           10886                   -8

;NEIGE1   PCX        24,256  09-13-97  5:44a
;NEIGE2   PCX        24,229  09-13-97  5:44a
;NEIGE3   PCX        24,412  09-13-97  5:44a

dd -1 ;indique la fin...
total_liste dd ?
iff_liste dd 0,10050,8046,9373,18043,2090,6643,3291,3297,5752,11285,1186,34928
dd -1

;BIP      IFF        10,050  08-06-97  4:36a
;BANG     IFF         8,046  08-06-97 10:26a
;KLANNG   IFF         9,373  08-06-97 10:27a
;SAC.IFF             18043   explosion d'un bonus
;TIC2.IFF             2090
;TIC6                 6643 ;ding sonnerie avant fin...
;ouil.iff            3291  ;mort d'un dyna exceptionnel.
;ail.iff             3297  ;mort d'un monstre courageux.
;tribombe.iff        5752  ;(9) utilisation du bonus tribombe
;SAUT-LAP IFF        11 285  (10)
;POSEBOMB IFF         1 186  (11)
;MORTLAP  IFF        34 928  (12)

;GAME1    PCX        29,535  07-04-97  3:28a -0
;GAME2    PCX        29,535  07-04-97  3:28a -1
;GAME3    PCX        29,096  07-04-97  3:28a -2
;SPRITE   PCX        30269   07-30-97  8:40a -3
;SPRITE2  PCX        45239   07-30-97  5:26a -4
;MENU.PCX            51047                   -5
;SPRITE3.PCX         27709                   -6
;DRAW1.PCX           29855                   -7
;DRAW2.PCX           29772                   -8
;MED.PCX             38197                   -9
;MED3.PCX            22395                   -10
;VIC1     PCX        26 830                  -11
;VIC2     PCX        """"""                  -12
;VIC3     PCX        """"""                  -13
;VIC4     PCX        """"""                  -14

;NEIGE1   PCX        24,256  09-13-97  5:44a
;NEIGE2   PCX        24,229  09-13-97  5:44a
;NEIGE3   PCX        24,412  09-13-97  5:44a

;neige1              24256                   -15
;neige2              24229                   -16
;neige3              24412                   -17
;pic.pcx             51618                   -18
;mrfond.pcx          50396                   -19
;micro.pcx           23593                   -20
;nuage1              29069                    21
;nuage2              28107                    22
;foret.pcx           59615                   -23
;feuille.pcx         40910                   -24
;pause.pcx           30517                   -25
;medc.pcx            35050                   -26
;medg.pcx            33790                   -27
;---------------------------------------     -28
;---------------------------------------     -29
;record0.mrb         64000                    -30 neige
;record1.mrb         64000                    -31 micro (hell)
;record2.mrb         64000                    -32
;record3.mrb         64000                    -33
;fete1.mrb           64000                    -34
;crayon.pcx          25675                    -35
;crayon2.pcx         10299                    -36
;record5.mrb         64000                    -37
;lapin1.pcx          25841                    -38
;mort.pcx            11838                    -39
;lapin2.pcx          25203                    -40
;lapin3.pcx          24473                    -41
;lapin4.pcx          25203                    -42
;foot.pcx            52283                    -43
;foot1.mrb           64000                    -44
;foot2.mrb           64000                    -45
;fete2.mrb           64000                    -46

;neige2.mrb          64000                    -47
;rose2.mrb           64000                    -48
;jungle2.mrb         64000                    -49
;micro2.mrb          64000                    -50
;nuage2.mrb          64000                    -51

;soucoupe.pcx        15266                    -52
;soccer.pcx          62297                    -53
;footanim.pcx        25477                    -54
;lune1.mrb          64000                    -55
;lune2.mrb          64000                    -56

include ss\DATA_RMD.INC ;SOUNDSYSTEM

;*************** save des nivos *****************

;lapin_mania dd 8 dup (1966080+64000*7)
;        dw 8 dup (32)
;       dw 37,37,37,37,37,37,37,37 ;nombre de lignes pour un dyna... ;8*10
;       dw 32,32,32,32,32,32,32,32 ;nombre de colonnes. ;8*12
;        dd 8 dup (-11*320-4)
;       dd -14*320-4,-14*320-4,-14*320-4,-14*320-4,-14*320-4,-14*320-4,-14*320-4,-14*320-4 ;adder di ;8*16
;       dd 8 dup (offset lapin2)

lapin_mania dd 1966080+64000*7,1966080+64000*7
            dd 1966080+64000*11,1966080+64000*11
            dd 1966080+64000*9,1966080+64000*9
            dd 1966080+64000*10,1966080+64000*10

lapin_mania_malade dd 1966080+64000*11,1966080+64000*11
            dd 1966080+64000*7,1966080+64000*7
            dd 1966080+64000*11,1966080+64000*11
            dd 1966080+64000*11,1966080+64000*11

;dd 512000,512000,512000,512000,512000,512000,512000,512000 ;source bloque memoire ;8*6
;            dw 8 dup (37)
;            dw 32,32,32,32,32,32,32,32 ;nombre de colonnes. ;8*12
;            dd 8 dup (-8*320-4)

lapin_mania1 dd offset lapin2,offset lapin2G
             dd offset lapin2,offset lapin2G
             dd offset lapin2,offset lapin2G
             dd offset lapin2,offset lapin2G
lapin_mania2 dd offset lapin2_,offset lapin2_g
             dd offset lapin2_,offset lapin2_g
             dd offset lapin2_,offset lapin2_g
             dd offset lapin2_,offset lapin2_g
lapin_mania3 dd offset lapin2__,offset lapin2__G
             dd offset lapin2__,offset lapin2__G
             dd offset lapin2__,offset lapin2__G
             dd offset lapin2__,offset lapin2__G
lapin_mania4 dd offset lapin2___,offset lapin2___G
             dd offset lapin2___,offset lapin2___G
             dd offset lapin2___,offset lapin2___G
             dd offset lapin2___,offset lapin2___G
lapin_mania5 dd offset lapin_mort,offset lapin_mortg
             dd offset lapin_mort,offset lapin_mortg
             dd offset lapin_mort,offset lapin_mortg
             dd offset lapin_mort,offset lapin_mortg

;--- nivo fete foraine...
donnee_s dw 20,20,277,277,116,116,180,180  ;x du dynablaster ;8*0
       dw 9,169,9,169,41,137,41,137 ;y du dynablaster        ;8*2
       dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna  ;8*4
ooo34  dd 512000,512000,512000,512000,512000,512000,512000,512000 ;source bloque memoire ;8*6
       dw 32,32,32,32,32,32,32,32 ;nombre de lignes pour un dyna... ;8*10
       dw 32,32,32,32,32,32,32,32 ;nombre de colonnes. ;8*12
       dd -9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4 ;adder di ;8*16
       dd offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu
       dd 8 dup (2)   ;r‚sistance aux bobos... (par d‚fault: pour monstre)
;pour les joueurs...
       dd info1,info2,info3,info4,0
;premier dd: nombre de bombes que le joeur peut encore mettre.
;deuxieme dd:  puissance de ces bombes... minimum = 1 ...
;troisieme dd: nombre de tous avant que ca pete.
;quatrieme dd: vitesse du joeur...
;pour les monstres
       dd 8 dup (1,1,220,3,0)
                dd 8 dup (0) ;invinsibilite au debut. (juste monstre)
                dd 8 dup (0) ;blocage au debut. (juste monstre)
                dd 0,0 ;invisibilite/blocage joeur
                dd 8 dup (0) ;pousseurs au debut (pour monstres)
                dd 8 dup (3) ;vitesse de dehambulation (gauche/droite) pour monstre
                dd 0 ;pousseur ou pas pousseur (pour dyna)
                dd 0 ;patineur au debut, ou pas (pour dyna)
                hazard_bonus_lapin

;--- nivo foot
donnee_foot dw 52,52 ,244,244,     116,116,  180,180  ;x du dynablaster ;8*0
            dw  73-32, 137-32,73,137,73,137, 73-32, 137-32
             ;y du dynablaster        ;8*2
            dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna  ;8*4
       dd 1454080,1454080,1454080,1454080,1454080,1454080,1454080,1454080
       dw 8 dup (18) ;nombre de lignes pour un dyna... ;8*10
       dw 8 dup (16) ;nombre de colonnes. ;8*12
       dd 8 dup (4+320*4)
       dd 8 dup (offset machine)
       dd 8 dup (0)   ;r‚sistance aux bobos... (par d‚fault: pour monstre)
;pour les joueurs...
       dd info1,info2,info3,info4,0
;premier dd: nombre de bombes que le joeur peut encore mettre.
;deuxieme dd:  puissance de ces bombes... minimum = 1 ...
;troisieme dd: nombre de tous avant que ca pete.
;quatrieme dd: vitesse du joeur...
;pour les monstres
       dd 8 dup (1,1,220,3,0)
                dd 8 dup (0) ;invinsibilite au debut. (juste monstre)
                dd 8 dup (0) ;blocage au debut. (juste monstre)
                dd 0,0 ;invisibilite/blocage joeur
                dd 8 dup (1) ;pousseurs au debut (pour monstres)
                dd 8 dup (3) ;vitesse de dehambulation (gauche/droite) pour monstre
                dd 0 ;pousseur ou pas pousseur (pour dyna)
                dd 0 ;patineur au debut, ou pas (pour dyna)
                hazard_bonus_foot

;--- nivo soccer
donnee_soccer dw 52,52,244,244,100,100,196,196  ;x du dynablaster ;8*0
              dw 41,137,41,137,73,105,73,105 ;y du dynablaster        ;8*2
            dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna  ;8*4
       dd 4 dup (512000,1454080)
       dw 8 dup (32) ;nombre de lignes pour un dyna... ;8*10
       dw 4 dup (32,38) ;26,26,16,23,26,32,17,38 ;nombre de colonnes. ;8*12
       dd 4 dup (-9*320-4,-9*320-7) ;adder di ;8*16
       dd 4 dup (offset grosbleu,offset escargot)
       dd 2,2,2,2,2,2,2,2   ;r‚sistance aux bobos... (par d‚fault: pour monstre)
       dd info1,info2,info3,info4,0
       dd 1,1,220,3,0,1,1,220,3,0 ;2 premiers montres forcements ecrase!
       ;dd 1,1,220,2,0             ;le oldschool.
       ;dd 1,1,220,3,0             ;le coca
       ;dd 1,1,220,3,0             ;le bleu triste (grandes oreilles)
       dd 3 dup (1,1,220,3,0,1,1,220,2,0)             ;le gros bleu
       ;dd 1,1,220,3,0             ;le gros bleu
       ;dd 1,1,220,3,0             ;le gros bleu
       ;dd 1,1,220,3,0             ;le petit jaune
       ;dd 1,1,220,2,0             ;l'escargot
       ;dd 1,1,220,2,0             ;l'escargot
       ;dd 1,1,220,2,0             ;l'escargot
                dd 8 dup (0) ;invinsibilite au debut. (""")
                dd 8 dup (0) ;blocage au debut. (juste monstre)
                dd 0,0 ;invisibilite/blocage joeur
                dd 0,0,0,0,0,0,0,0 ;pousseurs au debut (pour monstres)
                dd 4 dup (3,4) ;vitesse de dehambulation (gauche/droite) pour monstre
                dd 1 ;pousseur ou pas pousseur (pour dyna)
                dd 0 ;patineur au debut, ou pas (pour dyna)
                hazard_bonus_lapin


;--- (micro.pcx)
donnee_h dw 20,20,276,276,116,116,180,180  ;x du dynablaster ;8*0
       dw 9,169,9,170,41,137,41,137 ;y du dynablaster        ;8*2
       dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna  ;8*4
       dd 1454080,1454080,1454080,1454080,1454080,1454080,1454080,1454080
       dw 27,27,27,27,27,27,27,27 ;nombre de lignes pour un dyna... ;8*10
       dw 26,26,26,26,26,26,26,26 ;nombre de colonnes. ;8*12
       dd -5*320-1,-5*320-1,-5*320-1,-05*320-1,-05*320-1,-05*320-1,-05*320-1,-05*320-1 ;adder di ;8*16
       dd offset bleu_triste,offset bleu_triste,offset bleu_triste,offset bleu_triste,offset bleu_triste,offset bleu_triste,offset bleu_triste,offset bleu_triste
       dd 8 dup (1) ;r‚sistance aux bobos... (par d‚fault: pour monstre)
       dd info1+7,info2+7,info3,info4,0
       dd 8 dup (1,1,220,3,0)
                dd 8 dup (200) ;invinsibilite au debut. (""")
                dd 8 dup (250) ;blocage au debut. (juste monstre)
                dd 0,0 ;invisibilite/blocage joeur
                dd 8 dup (1) ;pousseurs au debut (pour monstres)
                dd 8 dup (3) ;vitesse de dehambulation (gauche/droite) pour monstre
                dd 1 ;pousseur ou pas pousseur (pour dyna)
                dd 0 ;patineur au debut, ou pas (pour dyna)
                hazard_bonus_lapin

;--- nuages
donnee_n dw 84 ,84 ,213,213, 20, 20,277,277  ;x du dynablaster ;8*0
         dw 9  ,169,9  ,170,73,105,73,105 ;y du dynablaster        ;8*2
       dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna  ;8*4
       dd 1454080,1454080,1454080,1582080,1454080,512000,576000,1454080
       dw 27,27,19,21,27,32,18,32 ;nombre de lignes pour un dyna... ;8*10
       dw 26,26,16,23,26,32,17,38 ;nombre de colonnes. ;8*12
       dd -5*320-1,-5*320-1,4+320*3,320*1,-05*320-1,-9*320-4,4*320+3,-9*320-7 ;adder di ;8*16
       dd offset bleu_triste,offset bleu_triste,offset old_school,offset coca,offset bleu_triste,offset grosbleu,offset petit_jaune,offset escargot
       dd 1,1,0,1,1,2,0,2   ;r‚sistance aux bobos... (par d‚fault: pour monstre)
       dd info1,info2,info3,info4,0
       dd 1,1,220,3,0,1,1,220,3,0 ;2 premiers montres forcements ecrase!
       dd 1,1,220,2,0             ;le oldschool.
       dd 1,1,220,3,0             ;le coca
       dd 1,1,220,3,0             ;le bleu triste (grandes oreilles)
       dd 1,1,220,3,0             ;le gros bleu
       dd 1,1,220,3,0             ;le petit jaune
       dd 1,1,220,2,0             ;l'escargot
                dd 8 dup (0) ;invinsibilite au debut. (""")
                dd 8 dup (0) ;blocage au debut. (juste monstre)
                dd 0,0 ;invisibilite/blocage joeur
                dd 0,0,0,0,1,0,0,0 ;pousseurs au debut (pour monstres)
                dd 3,3,3,3,3,3,3,4 ;vitesse de dehambulation (gauche/droite) pour monstre
                dd 0 ;pousseur ou pas pousseur (pour dyna)
                dd 0 ;patineur au debut, ou pas (pour dyna)
                hazard_bonus_lapin
;--- crayon
donnee_c dw 20 ,20 ,277,277, 20, 20,277,277  ;x du dynablaster ;8*0
         dw 9  ,169,9  ,169,73,105,73,105 ;y du dynablaster        ;8*2
       dw 8 dup (24*5) ;source du dyna  ;8*4
       dd 8 dup (1582080)
       dw 21,21,21,21,21,21,21,21 ;nombre de lignes pour un dyna... ;8*10
       dw 23,23,23,23,23,23,23,23 ;nombre de colonnes. ;8*12
       dd 8 dup (320*1)
       dd 8 dup (offset coca)
       dd 8 dup (1)
       dd info1,info2,info3,info4,0
;       dd 1,1,220,3,0,1,1,220,3,0 ;2 premiers montres forcements ecrase!
;       dd 1,1,220,2,0             ;le oldschool.
       dd 8 dup (1,1,220,3,0)      ;le coca
;       dd 1,1,220,3,0             ;le bleu triste (grandes oreilles)
;       dd 1,1,220,3,0             ;le gros bleu
;       dd 1,1,220,3,0             ;le petit jaune
;       dd 1,1,220,2,0             ;l'escargot
                dd 8 dup (0) ;invinsibilite au debut. (""")
                dd 8 dup (0) ;blocage au debut. (juste monstre)
                dd 0,0 ;invisibilite/blocage joeur
                dd 8 dup (0) ;pousseurs au debut (pour monstres)
                dd 8 dup (3) ;vitesse de dehambulation (gauche/droite) pour monstre
                dd 1 ;pousseur ou pas pousseur (pour dyna)
                dd 0 ;patineur au debut, ou pas (pour dyna)
                hazard_bonus_crayon
;--- foret
donnee_f dw 20,20 ,277,277,116,116,180,180  ;x du dynablaster ;8*0
         dw 9 ,169,9  ,169,41 ,105,41 ,137 ;y du dynablaster        ;8*2
       dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna  ;8*4
       dd 1454080,1454080,1454080,1454080,1454080,1454080,1454080,1454080
       ;512000,512000,512000,512000,512000,512000,512000,512000 ;source bloque memoire ;8*6
       dw 32,32,32,32,32,32,32,32 ;nombre de lignes pour un dyna... ;8*10
       dw 38,38,38,38,38,38,38,38 ;nombre de colonnes. ;8*12
       dd -9*320-7,-9*320-7,-9*320-7,-9*320-7,-9*320-7,-9*320-7,-9*320-7,-9*320-7 ;adder di ;8*16
       dd offset escargot,offset escargot,offset escargot,offset escargot,offset escargot,offset escargot,offset escargot,offset escargot
       dd 8 dup (2)   ;r‚sistance aux bobos... (par d‚fault: pour monstre)
       dd info1,info2,info3,info4,0
       dd 8 dup (1,1,220,2,0) ;monstres vitesse lente (escargots...)
                dd 8 dup (0) ;invinsibilite au debut. (""")
                dd 8 dup (0) ;blocage au debut. (juste monstre)
                dd 0,0 ;invisibilite/blocage joeur
                dd 8 dup (0) ;pousseurs au debut (pour monstres)
                dd 8 dup (4) ;vitesse de dehambulation (gauche/droite) pour monstre
                dd 0 ;pousseur ou pas pousseur (pour dyna)
                dd 0 ;patineur au debut, ou pas (pour dyna)
                hazard_bonus_lapin
;escargot
;mov edi,896000+384000+46080+64000 ; 128000  ;307200

;r‚sistance_au_debut_pour_un_dyna equ 0

donnee_s_neige dw 20,20,277,277-32,116-16-16,116,180+16+16,180  ;x du dynablaster
                dw 9,169,9,169,41,137,41,137-16-16 ;y du dynablaster
                dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna
                dd 576000,576000,576000,576000,576000,576000,576000,576000 ;source bloque memoire
                dw 18,18,18,18,18,18,18,18 ;nombre de lignes pour un dyna...
                dw 17,17,17,17,17,17,17,17 ;nombre de colonnes.
                dd 4*320+3,4*320+3,4*320+3,4*320+3,4*320+3,4*320+3,4*320+3,4*320+3;adder di
                dd offset petit_jaune,offset petit_jaune,offset petit_jaune,offset petit_jaune,offset petit_jaune,offset petit_jaune,offset petit_jaune,offset petit_jaune
                dd 8 dup (0)   ;r‚sistance aux bobos... (par d‚fault: pour monstre)
                dd info1,info2,info3,info4,0
                dd 8 dup (1,1,220,3,0)
                dd 8 dup (0) ;invinsibilite au debut. (""")
                dd 8 dup (0) ;blocage au debut. (juste monstre)
                dd 0,0 ;invisibilite/blocage joeur
                dd 8 dup (0) ;pousseurs au debut (pour monstres)
                dd 8 dup (3) ;vitesse de dehambulation (gauche/droite) pour monstre
                dd 0 ;pousseur ou pas pousseur (pour dyna)
                dd 0 ;patineur au debut, ou pas (pour dyna)
                hazard_bonus_classique
;avec un dyna...

liste_couleur_normal dd offset blanc,offset blancg
                     dd offset rouge,offset rougeg
                     dd offset bleu,offset bleug
                     dd offset vert,offset vertg


;       dw 20,20,277,277,116,116,180,180  ;x du dynablaster
;       dw 9,170,9,170,41,137,41,137 ;y du dynablaster
;       dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna dans bloque
;       64000*8
s_normal dd 576000,640000,576000,640000,576000,640000,576000,640000 ;source bloque memoire
l_normal dw 23,25,23,25,23,25,23,25 ;nombre de lignes pour un dyna...
c_normal dw 23,23,23,23,23,23,23,23 ;nombre de colonnes.
a_normal dd 0,-3*320,0,-3*320,0,-3*320,0,-3*320 ;adder di (pour la girl + grande...)
r_normal dd 8 dup (r‚sistance_au_debut_pour_un_dyna)

;             0,0,0,-3*320,-3*320,-3*320,-3*320 ;adder di (pour la girl + grande...)


truc_fin db 13*32 dup (?)   ;endroit ou l'on place le compte … rebourd.
                            ;enfin le nombre de vbl avant le d‚foncage lors
         dd ? ;sa vitesse   ; de L'(a)pocalypse.
;(a)pocalypse de rechange:
truc_fin_s   db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
             db 000,001,002,003,004,005,006,007,008,009,010,011,012,013,014,015,016,017,000,13 dup (0)
             db 000,052,053,054,055,056,057,058,059,060,061,062,063,064,065,066,067,018,000,13 dup (0)
             db 000,051,096,097,098,099,100,101,102,103,104,105,106,107,108,109,068,019,000,13 dup (0)
             db 000,050,095,132,255,255,255,255,255,255,255,255,255,255,255,110,069,020,000,13 dup (0)
             db 000,049,094,131,255,255,255,255,255,255,255,255,255,255,255,111,070,021,000,13 dup (0)
             db 000,048,093,130,255,255,255,255,255,255,255,255,255,255,255,112,071,022,000,13 dup (0)
             db 000,047,092,129,255,255,255,255,255,255,255,255,255,255,255,113,072,023,000,13 dup (0)
             db 000,046,091,128,255,255,255,255,255,255,255,255,255,255,255,114,073,024,000,13 dup (0)
             db 000,045,090,127,126,125,124,123,122,121,120,119,118,117,116,115,074,025,000,13 dup (0)
             db 000,044,089,088,087,086,085,084,083,082,081,080,079,078,077,076,075,026,000,13 dup (0)
             db 000,043,042,041,040,039,038,037,036,035,034,033,032,031,030,029,028,027,000,13 dup (0)
             db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
             dd 000 ;vitesse

truc_fin_soccer   db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
             db 000,001,002,003,004,005,006,007,008,009,010,011,012,013,014,015,016,017,000,13 dup (0)
             db 000,034,033,032,031,030,029,028,027,026,025,024,023,022,021,020,019,018,000,13 dup (0)
             db 000,035,036,037,038,039,040,041,042,043,044,045,046,047,048,049,050,051,000,13 dup (0)
             db 000,050,050,053,053,054,055,056,255,255,255,058,057,056,055,054,053,052,000,13 dup (0)
             db 000,075,074,073,072,071,070,255,255,255,255,255,059,060,061,062,063,064,000,13 dup (0)
             db 000,064,065,066,067,068,069,255,255,255,255,255,070,069,068,067,066,065,000,13 dup (0)
             db 000,063,062,061,060,059,058,255,255,255,255,255,071,072,073,074,075,076,000,13 dup (0)
             db 000,052,053,054,055,055,056,057,255,255,255,083,082,081,080,079,078,077,000,13 dup (0)
             db 000,051,050,049,048,047,046,045,044,043,042,041,040,039,038,037,036,035,000,13 dup (0)
             db 000,018,019,020,021,022,023,024,025,026,027,028,029,030,031,032,033,034,000,13 dup (0)
             db 000,017,016,015,014,013,012,011,010,009,008,007,006,005,004,003,002,001,000,13 dup (0)
             db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
             dd 002;vitesse

truc_fin_s_c db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,000,13 dup (0)
             db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
             dd 000 ;vitesse


;pour le nivo micro...(hell)
truc_fin_s_m db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
             db 000,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,000,13 dup (0)
             db 000,015,015,015,015,015,015,015,015,015,015,015,015,015,015,015,015,015,000,13 dup (0)
             db 000,030,030,030,030,030,030,030,030,030,030,030,030,030,030,030,030,030,000,13 dup (0)
             db 000,045,045,045,045,045,045,045,045,045,045,045,045,045,045,045,045,045,000,13 dup (0)
             db 000,060,060,060,060,060,060,060,060,060,060,060,060,060,060,060,060,060,000,13 dup (0)
             db 000,075,075,075,075,075,075,075,075,075,075,075,075,075,075,075,075,075,000,13 dup (0)
             db 000,090,090,090,090,090,090,090,090,090,090,090,090,090,090,090,090,090,000,13 dup (0)
             db 000,105,105,105,102,105,105,105,105,105,105,105,105,105,105,105,105,105,000,13 dup (0)
             db 000,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,000,13 dup (0)
             db 000,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,000,13 dup (0)
             db 000,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,000,13 dup (0)
             db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
             dd 0111B ;vitesse

;truc_fin_foot db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
;             db 000,001,022,023,044,045,066,067,088,225,078,077,056,055,034,033,012,011,000,13 dup (0)
;             db 000,002,021,024,043,046,065,068,087,225,079,076,057,054,035,032,013,010,000,13 dup (0)
;             db 000,003,020,025,042,047,064,069,086,225,080,075,058,053,036,031,014,009,000,13 dup (0)
;             db 000,004,019,026,041,048,063,070,085,226,081,074,059,052,037,030,015,008,000,13 dup (0)
;             db 000,005,018,027,040,049,062,071,084,226,082,073,060,051,038,029,016,007,000,13 dup (0)
;             db 000,006,017,028,039,050,061,072,083,226,083,072,061,050,039,028,017,006,000,13 dup (0)
;             db 000,007,016,029,038,051,060,073,082,227,084,071,062,049,040,027,018,005,000,13 dup (0)
;             db 000,008,015,030,037,052,059,074,081,227,085,070,063,048,041,026,019,004,000,13 dup (0)
;             db 000,009,014,031,036,053,058,075,080,227,086,069,064,047,042,025,020,003,000,13 dup (0)
;             db 000,010,013,032,035,054,057,076,079,228,087,068,065,046,043,024,021,002,000,13 dup (0)
;             db 000,011,012,033,034,055,056,077,078,228,088,067,066,045,044,023,022,001,000,13 dup (0)
;             db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
;             dd 0111B ;vitesse

truc_fin_s_n db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
             db 000,100,100,100,100,100,255,040,041,042,043,044,255,085,085,085,085,085,000,13 dup (0)
             db 000,100,100,100,100,100,255,047,255,046,255,045,255,085,085,085,085,085,000,13 dup (0)
             db 000,100,100,100,100,100,255,255,255,255,255,255,255,085,085,085,085,085,000,13 dup (0)
             db 000,100,100,100,100,100,255,255,255,255,255,255,255,085,085,085,085,085,000,13 dup (0)
             db 000,100,100,100,100,100,001,255,255,255,255,255,020,085,085,085,085,085,000,13 dup (0)
             db 000,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,000,13 dup (0)
             db 000,070,070,070,070,070,030,255,255,255,255,255,010,110,110,110,110,110,000,13 dup (0)
             db 000,070,070,070,070,070,255,255,255,255,255,255,255,110,110,110,110,110,000,13 dup (0)
             db 000,070,070,070,070,070,255,255,255,255,255,255,255,110,110,110,110,110,000,13 dup (0)
             db 000,070,070,070,070,070,255,056,255,057,255,058,255,110,110,110,110,110,000,13 dup (0)
             db 000,070,070,070,070,070,255,055,054,053,052,051,255,110,110,110,110,110,000,13 dup (0)
             db 000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,13 dup (0)
             dd 0011B ;vitesse


truc_s  db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)
        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
        db 1,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,1,13 dup (1)
        db 1,2,2,2,2,2,0,0,2,2,2,0,0,2,2,2,2,2,1,13 dup (1)
        db 1,2,1,2,1,2,1,0,1,2,1,0,1,2,1,2,1,2,1,13 dup (1)
        db 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,13 dup (1)
        db 1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,13 dup (1)
        db 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,13 dup (1)
        db 1,2,1,2,1,2,1,0,1,2,1,0,1,2,1,2,1,2,1,13 dup (1)
        db 1,2,2,2,2,2,0,0,2,2,2,0,0,2,2,2,2,2,1,13 dup (1)
        db 1,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,1,13 dup (1)
        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
        db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)

truc_foot  db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)
        db 1,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,1,13 dup (1)
        db 1,2,1,0,1,2,1,2,1,2,1,0,1,2,1,1,0,1,1,13 dup (1)
        db 1,2,0,0,0,2,2,2,2,2,0,0,0,2,2,2,2,2,1,13 dup (1)
        db 1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,13 dup (1)
        db 1,2,2,2,2,2,0,0,0,2,2,2,2,2,0,0,0,2,1,13 dup (1)
        db 1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,13 dup (1)
        db 1,2,0,0,0,2,2,2,2,2,0,0,0,2,2,2,2,2,1,13 dup (1)
        db 1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,0,1,2,1,13 dup (1)
        db 1,2,2,2,2,2,0,0,0,2,2,2,2,2,0,0,0,2,1,13 dup (1)
        db 1,2,1,2,1,2,1,0,1,2,1,2,1,2,1,0,1,2,1,13 dup (1)
        db 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,13 dup (1)
        db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)

truc_soccer       db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)

        db 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,13 dup (1)
        db 1,2,1,0,1,2,1,2,1,2,1,2,1,2,1,0,1,2,1,13 dup (1)
        db 1,2,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,2,1,13 dup (1)
        db 1,1,2,1,2,1,0,1,2,1,2,1,0,1,2,1,2,1,1,13 dup (1)

        db 1,2,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,2,1,13 dup (1)
        db 1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,13 dup (1)
        db 1,2,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,2,1,13 dup (1)
        db 1,1,2,1,2,1,0,1,2,1,2,1,0,1,2,1,2,1,1,13 dup (1)

        db 1,2,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,2,1,13 dup (1)
        db 1,2,1,0,1,2,1,2,1,2,1,2,1,2,1,0,1,2,1,13 dup (1)
        db 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,13 dup (1)

        db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)


;truc_n  db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
 ;       db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (0)

truc_n  db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)
        db 1,2,2,2,0,0,1,2,0,0,0,2,1,0,0,2,2,2,1,13 dup (1)
        db 1,2,1,2,1,0,1,2,1,2,1,2,1,0,1,2,1,2,1,13 dup (1)
        db 1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,13 dup (1)
        db 1,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,1,13 dup (1)
        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
        db 1,1,1,1,1,1,1,2,1,2,1,2,1,1,1,1,1,1,1,13 dup (1)
        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
        db 1,0,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,0,1,13 dup (1)
        db 1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,13 dup (1)
        db 1,2,1,2,1,0,1,2,1,2,1,2,1,0,1,2,1,2,1,13 dup (1)
        db 1,2,2,2,0,0,1,2,0,0,0,2,1,0,0,2,2,2,1,13 dup (1)
        db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)

truc_c  db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)
        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
        db 1,0,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,1,13 dup (1)
        db 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,13 dup (1)
        db 1,0,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,1,13 dup (1)
        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
        db 1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,13 dup (1)
        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
        db 1,0,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,1,13 dup (1)
        db 1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,13 dup (1)
        db 1,0,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,1,13 dup (1)
        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
        db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)

truc_h  db 1,66,66,66,66,66,66,66,1,1,1,66,66,66,66,66,66,66,1,13 dup (1)
        db 66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,66,13 dup (1)
        db 66,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,66,13 dup (1)
        db 66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,66,13 dup (1)
        db 66,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,66,13 dup (1)
        db 66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,66,13 dup (1)
        db 66,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,66,13 dup (1)
        db 66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,66,13 dup (1)
        db 66,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,66,13 dup (1)
        db 66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,66,13 dup (1)
        db 66,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,66,13 dup (1)
        db 66,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,66,13 dup (1)
        db 66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,13 dup (1)

truc_f  db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)
        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
        db 1,0,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,0,1,13 dup (1)
        db 1,0,2,2,2,0,0,0,1,2,2,0,0,0,2,2,2,0,1,13 dup (1)
        db 1,2,1,1,1,0,1,2,1,1,1,0,1,1,1,2,1,2,1,13 dup (1)
        db 1,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,13 dup (1)
        db 1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,13 dup (1)
        db 1,2,2,2,1,2,0,0,2,2,2,2,2,2,1,2,2,2,1,13 dup (1)
        db 1,2,1,2,1,1,1,0,1,2,1,1,1,2,1,1,1,2,1,13 dup (1)
        db 1,0,2,2,2,2,1,0,2,2,2,0,0,0,2,2,1,0,1,13 dup (1)
        db 1,0,1,1,1,2,1,2,1,1,1,0,1,1,1,2,1,0,1,13 dup (1)
        db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
        db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)


truc_neige  db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)
           db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,1,13 dup (1)
           db 1,0,1,2,1,0,1,2,1,2,1,2,1,2,1,2,1,0,1,13 dup (1)
           db 1,2,2,2,0,0,2,2,2,2,2,2,0,0,2,2,2,2,1,13 dup (1)
           db 1,2,1,2,1,2,1,1,1,2,1,2,1,0,1,0,1,2,1,13 dup (1)
           db 1,2,2,2,2,2,1,1,1,2,2,2,2,2,0,0,0,2,1,13 dup (1)
           db 1,2,1,2,1,2,1,1,1,2,1,2,1,2,1,0,1,2,1,13 dup (1)
           db 1,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,1,13 dup (1)
           db 1,2,1,2,1,2,1,0,1,2,1,0,1,2,1,2,1,2,1,13 dup (1)
           db 1,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,1,13 dup (1)
           db 1,0,1,2,1,2,1,2,1,2,1,2,1,2,1,0,1,1,1,13 dup (1)
           db 1,0,0,2,2,2,2,2,2,2,2,2,2,2,0,0,1,1,1,13 dup (1)
           db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (1)

;--- laisser ensemble
truc2_save_foot db 0,0,0,0,0,0,00,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
             db 0,0,0,0,0,0,00,0,000,00,00,0,0,0,0,0,0,94,0,13 dup (0)
truc2_save   db 32*13 dup (0)
;---
truc2_save_n db 0,0,0,0,0,0,00,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
             db 0,0,0,0,0,0,00,0,114,74,84,0,0,0,0,0,0,0,0,13 dup (0)
             db 0,0,0,0,00,00,0,00,00,0,0,0,0,0,0,0,0,0,0,13 dup (0)
            db 0,0,0,0,0,0,00,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
        db 0,0,0,0,0,0,00,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)
        db 0,0,0,0,0,0,00,0,104,74,94,0,0,0,0,0,0,0,0,13 dup (0)
        db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13 dup (0)



                      ;0= face        bas.
                      ;8= droite      droite
                      ;16= gauche     gauche
                      ;24= haut       haut
;0;8;24;



ia dd 16,0,8,24,0,8,24,16,0,24,16,0,8,16,0,24


;-***********************************************

ordre  db 'M'
       db 'menu' ;pout reconnaitre ou on est... enfin si c'est un packet
                 ;menu ou pas.
fx     dw 14 dup (0)
texte1 db 32*4*8 dup (0) ;texte pour chaque dyna
taille_block_slave_menu equ 32*4*8+1+14*2

;panning2 db 15,14,13,12,11,10,09,08,08,07,07,06,06,05,04,03
;         db 02,01,00

panning2 db 0,1,2,3,4,5,6,6,7,7,8,8,9,10,11,12,13,14,15
;,14,13,12,11,10,09,08,08,07,07,06,06,05,04,03
;         db 02,01,00

maladie dd 8 dup (?)

offset_oiseau  dd 0,16,0,16,0,16,0,16,0,16,0,16,0,16,0,16
               dd 0,16*1,16*0,16*2,16*2,16*0,16*3,16*3,16*0,16*4,16*5,16*6,16*7,16*8,16,0

;---------------------- dw ---------------------------------------
lost_msg dw 0
grosse_sochette dw 0


mort_de_lapin   dw 00,00,01,02,03,04  ;6
                dw 05,06,07,08,09,10 ;12
                dw 11,12,14,15,17,18 ;18
                dw 20,21,23,24,25,24 ;24
                dw 23,21,20,18,17,15 ;30
                dw 14,12             ;32

saut_de_lapin2   dw 02,04,05,07,08,10
                dw 11,13,14,15,16,17
                dw 18,19,20,21,22
                ;50%
                dw 22,21,20
                dw 19,18,17,16,15,14
                dw 13,11,10,08,07,05

                dw 04
                dw 02,00,00,00
                dw 00,00,00,00

saut_de_lapin   dw 01,02,03,04,05,06
                dw 07,08,09,10,11,11
                dw 12,12,13,13,14
                ;50%
                dw 14,13,13
                dw 12,11,10,09,08,07
                dw 06,05,04,03,02,01

                dw 00
                dw 00,00,00,00
                dw 00,00,00,00
                dw 320*00,320*00,320*00,320*00
                dw 320*00,320*00,320*00,320*00
                dw 320*00,320*00,320*00,320*00
                dw 320*00,320*00,320*00,320*00


;---------------------- db ---------------------------------------
save64 db 0
windowsnetwork db 0
economode db 0

demande_partie_slave db 0
demande_partie_slave2 db 0
kli_option db 0

balance_le_bdrawn db ?
bdraw1  db ? ;32
on_a_bien_fait_une_partie db 0
on_les_dans_le_menu db 1
sortie_slave db 0
modeinfo db 0
willrecord db 0
nomonster db 0
twice db 0 ;pour le mode twice faster.
twice2 db 0 ;pour le mode twice faster.

;kel_pic_intro db 1
of_f0 equ 72*320
of_f1 equ 72*320+49
of_f2 equ 72*320+49*2
of_f3 equ 72*320+49*3
of_f4 equ 72*320+49*4
of_f5 equ 72*320+49*5
of_f6 equ 105*320
of_f7 equ 107*320+49
of_f8 equ 107*320+49*2
of_f9 equ 107*320+49*3
of_f10 equ 107*320+49*4
of_f11 equ 107*320+49+5
of_f12 equ 107*320+49+5

;32
offset_fille dw 4 dup (of_f5,of_f4,of_f6,of_f4)

; of_f1,of_f6,of_f1,of_f7
;dw of_f1,of_f6,of_f1,of_f7
;dw of_f1,of_f6,of_f1,of_f7
;dw of_f1,of_f6,of_f1,of_f7

;dw of_f0,of_f1,of_f2,of_f3,of_f4
;             dw 7 dup (of_f5,of_f4,of_f6,of_f4)
;             dw of_f3,of_f2,of_f1,of_f0
;dw 7 dup (of_f3,of_f4,of_f3,of_f5)
;dw of_f2,of_f1
;
;dw of_f3,of_f4,of_f3,of_f5
;dw of_f3,of_f4,of_f3,of_f5
;
;dw of_f3,of_f4,of_f3,of_f5
;dw of_f3,of_f4,of_f3,of_f5
;
;dw of_f1,of_f6,of_f1,of_f7
;dw of_f1,of_f6,of_f1,of_f7
;dw of_f1,of_f6,of_f1,of_f7
;dw of_f1,of_f6,of_f1,of_f7
;dw of_f1,of_f10,of_f11,of_f10,of_f1,of_f12
;
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8
;dw of_f2,of_f8,of_f2,of_f9,of_f2,of_f8

lft equ 24

offset_supporter db 0,24,0,24*2
offset_cameraman db 0*lft,1*lft,2*lft,1*lft ;4
                 db 12 dup (0);

                 db 0*lft,3*lft,4*lft,3*lft
                 db 12 dup (0);

;                 db 0*lft,4*lft,4*lft,4*lft,3*lft,4*lft,4*lft,4*lft
;                 db 8 dup (0);
;
;                 db 16 dup (0);

                 ;--

                 db 0*lft,4*lft,4*lft,4*lft,4*lft,4*lft,4*lft,4*lft
                 db 8 dup (4*lft);

                 db 8 dup (0);

                 db 0*lft,5*lft,6*lft,5*lft
                 db 12 dup (0);

                 db 8 dup (0);

                 db 0*lft,1*lft,2*lft,1*lft ;4
                 db 12 dup (0);

pic_de_tout_debut db 0 ;pour viser la palette de la pic detection reso

une_touche_a_telle_ete_pressee db 0 ;mis a un si on a touche le clavier
                                    ;depuis le dernier packet...

sors_du_menu_aussitot db 0 ;pour kon kitte le jeu aussitot apres avoir
                           ;loade un fichier .mrb
team3_sauve          db 0        ;

special_on_a_loadee_nivo db 0
record_user db 0 ;activ‚ si on a le droit d'enclancher le mode REC/PLAY

previentlmesenfants db 0 ;pour slave: affiche messgae fin

couleurssss db 64 dup (31)
                db 64 dup (31+32)
                db 64 dup (31+32*2)
                db 64 dup (31+32*3)
;;couleurssss2 db 64 dup (124)
;                db 64 dup (124+32)
;                db 64 dup (124+32*2)
;                db 64 dup (124+32*3)



clavier db 128 dup (0)

;-- mettre ensemble... ;0-32
        hazard_bonus db 0,1,0,14,11,2,0,13,1,11,2,14,0,6,15,0,10,0,1,14,11,0,3,0,1,0,15,0,4,0,11,2,0,2,1,0,14,0,0,15,0,0,5,11,0,15
                     db 0,7,2,15,11,0,1,3,0,0,0,14,0,2,0,14,0,11,14,9,0,15,0,11,7,0,13,1,0,14,2,11,0,15,0,1,4,0,2,6,0,11,7,8,2,1,0,1,2,11,14,15,11

                   ;  db 0,54,0,64,0,114,74,0,64,0,0,54,0,74,0,0,64,0,104,54,0,64,0,0,64,0,54,0,0,64,0,0,0,94,0,64,114,0,64,0,74,0,0,84,0,0,0,54,0,64,0,64
                   ;  db 0,54,0,64,0,74,0,64,0,74,54,0,54,0,114,0,0,54,0,64,0,64,0,84,0,0,64,0,54,0,0,54,0,0,114,0,0,64,0,64,0,54,0,0,94,0,0,54,0,104,0,0,74,0,64,0,64,0
        viseur_hazard_bonus dd 0
        hazard_bonus2 db 0,1,2,3,4,5,6,7
                      db 8,9,10,11,12,13,14,15

        ;db 84,94,94,104,94,84,94,104,114,94,94,104,94,84,94,74,94,104,114
        viseur_hazard_bonus2 dd 0

;---- laisser ces deux truc ENSEMBLES !! SOMBRE CRETIN
                                        correspondance_bonus db 16 dup (?)
                                        correspondance_bonus2 db 16 dup (?)
;----------------


;---

;54-- bonus bombe... de 54 a 63 (offset 144) ;1
;64-- bonus flamme... de 64 a 73 (offset 144+320*16) 2
;74-- tete de mort  de 74 a 83                        3
;84-- bonus parre balle. de 84 a 93                    4
;94-- bonus COEUR !!!                                   5
;104 -- bonus bombe retardement                         6
;114 --- bonus pousseur                                 7
;124 --- patins a roulettes                             8
;134 --- HORLOGE                                        9


couleur      db 98,98,42,42,62,62,37,37 ;medailles
couleur_menu db 195,195,224,224,214,214,144,144
;db 62,62,28,28,3,3,96,96
 ;db 62,62,3,3,96,96,28,28

scrolly   db 6*328 dup (0)


last_sucker db 0 ;derniere touche...
pal          db  768 dup (?)  ;pal  de l'‚mulateur.
pal_affich‚e db 768 dup (0)   ;pal k'on affiche...
affiche_pal  db 2             ; 1: vas de la palette au noir (ne plus afficher
                              ;                               d'‚cran !!!)
                              ;
                              ; 2: va du noir a la palette
                              ; 0: ne fait rien...

hazard_maladie db 1,2,3,4 ,5,6,5,4
               db 3,6,5,1 ,2,4,2,4

pause  db 0 ;0=nan inverse = oui
pause2 db 0 ;temps ou on s'en fou

clavier_stuff db 0 ;0 rien
clavier_stuff2 db 0 ;0 rien
clavier_extanded db 128 dup (0)

_setup_  db 0 ;appele ??
setup_wait2 db setup_wait
setup_wait3 db setup_wait
setup_wait4 db setup_wait
setup_wait equ 08
setup_viseur dd 0
setup_viseur2 dd 8
setup_viseur2_offset dw 210h,220h,230h,240h,250h,260h,270h,280h,0

max_s equ 16 ;pour viseur rouge
max_s2 equ 8 ;pour viseur rouge
ou_ca_setup dd 0 ;=1 dans change card
viseur_rouge3 dd 0b8000h+80*2*08+1+2+2+59*2,11
              dd 0b8000h+80*2*09+1+2+2+59*2,11
              dd 0b8000h+80*2*10+1+2+2+59*2,11
              dd 0b8000h+80*2*11+1+2+2+59*2,11
              dd 0b8000h+80*2*12+1+2+2+59*2,11
              dd 0b8000h+80*2*13+1+2+2+59*2,11
              dd 0b8000h+80*2*14+1+2+2+59*2,11
              dd 0b8000h+80*2*15+1+2+2+59*2,11
              dd 0b8000h+80*2*16+1+2+2+59*2,11


viseur_rouge dd 0b8000h+80*2*06+1+2+2,18
             dd 0b8000h+80*2*07+1+2+2,18
             dd 0b8000h+80*2*08+1+2+2,18
             dd 0b8000h+80*2*09+1+2+2,18
             dd 0b8000h+80*2*10+1+2+2,18
             dd 0b8000h+80*2*11+1+2+2,18
             dd 0b8000h+80*2*12+1+2+2,18
             dd 0b8000h+80*2*13+1+2+2,18
             dd 0b8000h+80*2*14+1+2+2,18
             dd 0b8000h+80*2*15+1+2+2,18
             dd 0b8000h+80*2*16+1+2+2,18
             dd 0b8000h+80*2*17+1+2+2,18
             dd 0b8000h+80*2*18+1+2+2,18
             dd 0b8000h+80*2*19+1+2+2,18
             dd 0b8000h+80*2*20+1+2+2,18
             dd 0b8000h+80*2*21+1+2+2,18 ;
             dd 0b8000h+80*2*22+1+2+2,18 ;

viseur_rouge2    dd 0b8000h+80*2*14+1+2+2+48,30 ;----------- pour touches
  dd 0b8000h+80*2*13+1+2+2+48,30 ;----------- pour touches
  dd 0b8000h+80*2*12+1+2+2+48,30 ;----------- pour touches
  dd 0b8000h+80*2*11+1+2+2+48,30 ;----------- pour touches
  dd 0b8000h+80*2*10+1+2+2+48,30 ;----------- pour touches
  dd 0b8000h+80*2*09+1+2+2+48,30 ;----------- pour touches
  dd 0b8000h+80*2*08+1+2+2+48,30 ;----------- pour touches

what_t db 0,1,2,3,3,4,4,5,5,6,6,7,7,8,8,0,0 ;kel touches afficher en fonction
;de la barre rouge dans le menu



_setup_wait  db setup_wait ;appele ??


temps2 db ?

include pal_pic.inc
include pal_pic2.inc
include pal_jeu.inc
include pal_med.inc
include pal_vic.inc
include pal_draw.inc

liste_terrain db 1,2,6,4,3,8,5,7,66
;8:soccer
;7:foot (extra terrestres)
;3
;36 ;J RASTER--->JESUS.
;18 ;19+128  ;E
;31 ;19+128  ;S
;22 ;19+128  ;U

jesus db 31,16,20,16,49,'Û'
jesus_mode db TRICHE ;!!!0
jesus2 db 31,25,18,18,32,'Û'
jesus3 db 31,38,24,44,'Û'
jesus4 db 31,38,24,17,'Û'
jesus5 db 20,24,20,24,'Û'
;jesus6 db 20,24,16,31,20,18,19,'Û'

sortie db 0 ;sortie...




assez_de_memoire db 0  ; 0 OUI suffisament
                       ; 1 non pas assez...


sortie_config db 0

lost_conney db 0

in_the_apocalypse db 0

;correspo db 128 dup (0)

invite_recu db ? ;indique la version du connecte ki s'est manisfete.

;sauveur dw 2144

;ligne_commande 256 db (?)
;                   db '$'

;texte_fin db  'texte integrit‚.',10,13,'$'

;include darkyans.inc

correspondance_mode_texte db ' ',2*16
                          db ' ',7*16
                          db ' ',4*16
                          db '²',2*16+4 ;3 a 10 pice en destruction
                          db '²',2*16+4 ;3 a 10 pice en destruction
                          db '±',2*16+4 ;3 a 10 pice en destruction
                          db '±',2*16+4 ;3 a 10 pice en destruction
                          db '°',2*16+4 ;3 a 10 pice en destruction
                          db '°',2*16+4 ;3 a 10 pice en destruction
                          db ' ',2*16+4 ;3 a 10 pice en destruction
correspondance_mode_texte2 db ' '
                           db 'o'
                           db 'O'
                           db 'O'
                           db 'o'


_DATA   ends

;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; STACK
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
stackseg   segment para stack 'STACK'
        db 1000h dup(?)
stackseg   ends


        end start




