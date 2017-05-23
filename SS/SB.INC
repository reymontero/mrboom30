
db 'Û remdy soundsystem v0.6 gama Û'

;****************************************** POUR LA SB !!!!!!!!!!!!!!!! ****

WR_DSP PROC NEAR ;envois une commande a la SB (vers 0ch)
;Entree:      al=commande a envoyer.

push ds es
pusha

push ax  ;(1)
mov ax,rmd_data
mov es,ax
mov dx,es:[dsp_adr]
add dx,0ch
sb_sexual:   ; attend ke le bit numero 7 soit a 0...
in al,dx     ;
cmp al,128   ;
jnb sb_sexual

pop ax   ;(1)
out dx,al    ;puis envoye la commande.

popa
pop es ds
ret
WR_DSP ENDP

SBREADBYTE PROC NEAR
;lis le port de donne de la SB (vers 0ah)
;sortie: AL octet lu !!!

push ds es
push dx

mov ax,rmd_data
mov es,ax
mov dx,es:[dsp_adr]
add dx,0ah
sb_sexual2:   ; attend ke le port de donnnee ne renvois plus 0aah
in al,dx     ;
cmp al,0aah   ;
je sb_sexual2
;ON A dans AL l'octet lu !!!

pop dx
pop es ds
ret
SBREADBYTE ENDP
littlenoping proc near
push cx
mov cx,1000 ;pour bloquer le test si  ca repond toujours pas...
sblittlenoping:
dec cx
jnz sblittlenoping
pop cx
ret
littlenoping endp

mettre_haut_parleur_en_marche proc near
push ds es
pusha

mov al,0d1h
call WR_DSP           ;envois une commande a la SB (vers 0ch)
                      ;Entree:      al=commande a envoyer.

popa
pop es ds
ret
mettre_haut_parleur_en_marche endp


mettre_haut_parleur_hs proc near
push ds es
pusha

mov al,0d3h
call WR_DSP           ;envois une commande a la SB (vers 0ch)
                      ;Entree:      al=commande a envoyer.

popa
pop es ds
ret
mettre_haut_parleur_hs endp

sortie_directe proc near
PUSHF
push ds es bp eax ebx ecx edx si di

;...............lecture du pattern... (une fois de temps en temps...)
mov ax,rmd_data
mov es,ax
cmp es:[mode_music],0
je msdosdtr

cmp dword ptr es:[speed_compteur],0
jnz rerereretrterty2
mov eax,es:[speed_compteur_save]
mov es:[speed_compteur],eax

;on place ici le nombre dans speed_wait k'on a choisit
;ca reviendra a ca apres etre arrive a 0...
call lit_pattern

;.................deplacement d'une ligne vers l'avant...
inc dword ptr es:[numero_de_ligne_dans_pattern]
cmp dword ptr es:[numero_de_ligne_dans_pattern],64
jne on_continue_dans_le_meme_pattern

;....on est arrive la fin d'un pattern...
mov dword ptr es:[numero_de_ligne_dans_pattern],0

inc es:[viseur_dans_arrangement_chanson]
mov ax,es:[nombre_total_de_pattern_chanson] ;
cmp es:[viseur_dans_arrangement_chanson],ax ;on regarde si on est arrive
                                            ;a la fin de l'arrangement.
jne charlyrulz
mov es:[viseur_dans_arrangement_chanson],0   ;on repart au debut...
                                             ;de l'arrangement
charlyrulz:

mov bx,es:[viseur_dans_arrangement_chanson]
;xor eax,eax
;mov al,es:[arrangement_de_la_chanson+bx]
movzx eax,es:[arrangement_de_la_chanson+bx]

;nombre_de_voix db ?                 ;nombre de voix dans le mod...
cmp es:[nombre_de_voix],4
je tcanariwarior
shl eax,11 ;multiplie par 2048... 8 VOIX
           ;on a donc dans ax le viseur_dans_pattern
jmp tcanariwarior2
tcanariwarior:
shl eax,10 ;multiplie par 1024... 4 VOIX
           ;on a donc dans ax le viseur_dans_pattern
tcanariwarior2:

mov es:[viseur_dans_pattern],eax
jmp rerereretrterty
on_continue_dans_le_meme_pattern:

cmp es:[nombre_de_voix],4
je tcanariwariorf
add es:[viseur_dans_pattern],32 ;8 VOIX
jmp tcanariwarior2f
tcanariwariorf:
add es:[viseur_dans_pattern],16 ;4 VOIX
tcanariwarior2f:

rerereretrterty:
call effets2    ;effet ki s'activent lorsqu'on a fini la ligne courante
                ;(detect‚s grace a effet 1)
                ;on le place ici car permet de modififer les modifs naturelles
                ;de deplacement dans les patterns de sorte k'elles nont aucun
                ;effet.
call synchro    ;met a jour les variables pour la syncrho
rerereretrterty2:

;....................................
dec dword ptr es:[speed_compteur]
;....................................

;********** appelle les effets ki marchent entre les lignes **********

xor bp,bp
call es:[table_de_saut]     ;pour 8 voix...

mov bp,2
call es:[table_de_saut+2]
;
mov bp,4
call es:[table_de_saut+4]
;
mov bp,6
call es:[table_de_saut+6]

cmp es:[nombre_de_voix_multiplie_par_2],4
je surtoiioooooooo

mov bp,8
call es:[table_de_saut+8]
mov bp,10
call es:[table_de_saut+10]
mov bp,12
call es:[table_de_saut+12]
mov bp,14
call es:[table_de_saut+14]
surtoiioooooooo:


;*********************************************************************

;mov al,010h

msdosdtr:

cmp es:[GUS_OR_SB],3
je ea__mode_silenceretrterte


;******* REMPLACE call WR_DSP           ;envois une commande a la SB (vers 0ch)
                                ;Entree:      al=commande a envoyer.

mov dx,es:[dsp_adr]
add dx,0ch
tsb_sexual:   ; attend ke le bit numero 7 soit a 0...
in al,dx     ;
cmp al,128   ;
jnb tsb_sexual
mov al,010h
out dx,al    ;puis envoye la commande.

;******************************************************************

cmp es:[mode_music],0
je ermsdosdtrdfrt


;mov ax,rmd_data
;mov es,ax

;-*-*-*-*-*-*-*-*-* call calc_voix -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

;
;calc_voix proc near
;...........pour les differents voix...


 ;numero de la voix*2
xor bp,bp
encore_une_voix2:


;-----dans dx:on va mettre bp*2
mov dx,bp
;shl dx,1
add dx,dx

;-----

mov bx,es:[sample_joue_en_ce_moment+bp]
or bx,bx ;cmp bx,0 ;cas particulier:ce code signifie ke aucun sample est joue...
jnz aeroplane
mov ax,128
jmp cas_special_si_aucun_sample_est_joue
aeroplane:
;....

;shl bx,1
add bx,bx

mov di,offset note_joue_par_sample
;add di,bp
;add di,bp
add di,dx

mov eax,es:[di]
cmp ax,-1  ;equivaut a "cmp eax,-1"
jne zergrerrtrterert
mov ax,128
jmp cas_special_si_aucun_sample_est_joue
zergrerrtrterert:

add es:[OFFSET_COMPTEUR_SAMPLE+BP],ax ;!!!

on_doit_encore_monter_peut_etre:

;push ecx
mov cx,es:[OFFSET_COMPTEUR_SAMPLE+BP] ;
shr cx,8
add es:[OFFSET_SAMPLE+bp],cx
shl cx,8

sub es:[OFFSET_COMPTEUR_SAMPLE+BP],cx
;pop ecx

mov ax,es:[longueur_loop_sample_joue+bp] ;si en mode loop...
add ax,es:[depart_loop_sample_joue+bp]
;or ax,ax ;cmp ax,0
jnz  cestunsampleloopeur

mov ax,es:[longueur_sample_joue+bp]      ;si pas en mode loop...

cestunsampleloopeur: ;comme c'est un sample loopeur onne prend pas compte
                     ;de la longueur reele du sample, on s'arrete a la fin du
                     ;loop (et les fois suivante on recommencera au debut du loop)

cmp es:[OFFSET_SAMPLE+bp],ax
jb reerertrterteert

;....arrive ici en fin de sample...et on le fait passer en loop ou non...
;....attention: s'il y a un loop dans le sample, le premier passage doit
;s'arreter a la fin du loop!!! (et non a la fin normalle du passage)

;mov es:[sample_est_il_en_train_de_louper],1
mov ax,es:[depart_loop_sample_joue+bp] ;on met de tout maniere mais ca peut etre
                                    ;annule juste apres
mov es:[OFFSET_SAMPLE+bp],ax

;.........si la longueur du loop est =0 pas de loop on eteint la voix.
cmp es:[longueur_loop_sample_joue+bp],0
jne ertrertertertert
mov es:[sample_joue_en_ce_moment+bp],0 ;si=0 pas de nouveau sample joue...
ertrertertertert:
;..............................

reerertrterteert:

non_on_avance_pas_dans_le_sample:
mov di,es:[OFFSET_SAMPLE+bp] ;en fonction de la voix...

;.............on arrive ici avec [di] pointeur du sample...
mov ax,es:[SEGMENT_SAMPLE+bx] ;1ere sample
mov ds,ax
mov byte ptr al,ds:[di]
;add al,128
;......... le volume !!!

mov bx,es:[volume_de_la_voix+bp]
mov dx,es:[music_volume]

imul bl ;mul al par bl...resultat dans ax...
sar ax,6

imul dl ;mul al par bl...resultat dans ax...
sar ax,6

add ax,128

;..........
cas_special_si_aucun_sample_est_joue:
mov es:[mixage+bp],ax

add bp,2
cmp bp,es:[nombre_de_voix_multiplie_par_2] ;tiens compte des voix sample
jne encore_une_voix2

;ret
;calc_voix endp
;
;
;
;-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

;******* REMPLACE call WR_DSP           ;envois une commande a la SB (vers 0ch)
                                ;Entree:      al=commande a envoyer.

ermsdosdtrdfrt:


mov dx,es:[dsp_adr]
add dx,0ch
rtsb_sexual:   ; attend ke le bit numero 7 soit a 0...
in al,dx     ;
cmp al,128   ;
jnb rtsb_sexual

;----------------

cmp es:[mode_music],0
je ermsdosdtrdfrtrterr

;-------------------- MIXAGE
cmp es:[nombre_de_voix_multiplie_par_2],8
je surtoi ;****** 8 VOIX !!! ******
mov ax,es:[mixage]
add ax,es:[mixage+2]
add ax,es:[mixage+4]
add ax,es:[mixage+6]
add ax,es:[mixage+8]
add ax,es:[mixage+10]
add ax,es:[mixage+12]
add ax,es:[mixage+14]
shr ax,3
jmp surtoi3

surtoi:  ;****** 4 VOIX !!! ******
mov ax,es:[mixage]
add ax,es:[mixage+2]
add ax,es:[mixage+4]
add ax,es:[mixage+6]

shr ax,2
surtoi3:
;--------------------

jmp tertrte
msdosdt: ;saute si si on est dans le mode SANS music support
ermsdosdtrdfrtrterr:
xor ax,ax
tertrte:
;*************************** rajoute les FX si besoin *****
cmp es:[mode_fx],0
je aeroplane2
push ax dx
;*************************** REGARDE SI NOUVEAU TRUC A BALANCER

;dans ax:sample k'on va jouer...
;dans bp: numero de la voix * 2 (de 8 a 11)
;dans bx:numero de la note

 ;9*2 ;!!! 1 !!!
xor bp,bp
mov dx,8*2 ;commence a la 8eme voix...
pcteam:
cmp es:[blow_what+4+bp],1
jne riendenouveau3
mov ax,es:[blow_what+bp]   ;32 ;numero du sample
mov bx,es:[blow_what+2+bp] ;30 ;numero de la note.
mov es:[blow_what+4+bp],0

push bp dx
mov bp,dx

call PLaY_BONUS_SAMPLE

pop dx bp
riendenouveau3:

cmp es:[blow_what+4+bp],2
jne riendenouveau3e
mov ax,es:[blow_what+bp]   ;32 ;numero du sample
mov bx,es:[blow_what+2+bp] ;30 ;numero de la note.
mov es:[blow_what+4+bp],0

push bp dx
mov bp,dx

call PLaY_BONUS_SAMPLE2

pop dx bp
riendenouveau3e:


add dx,2 ;voix ;!!!

add bp,6
cmp bp,6*4 ;pour les 4 voix du fx !
jne pcteam


;******************* CALCUL LES VALEUR MIXAGE SPECIAL FX
;*-*-*-**-*-*-**-*-*-*call calc_voix_bonus *-*-*-**-*-*-**-*-*-**-*-*-**-*-*-*
;...........pour les differents voix...

mov bp,8*2  ;numero de la voix*2
tencore_une_voix2:

;-----dans dx:on va mettre bp*2
mov dx,bp
;shl dx,1
add dx,dx
;-----


mov bx,es:[sample_joue_en_ce_moment+bp]
or bx,bx ;cmp bx,0 ;cas particulier:ce code signifie ke aucun sample est joue...
jnz taeroplane
mov ax,128
jmp tcas_special_si_aucun_sample_est_joue
taeroplane:
;....

;shl bx,1
add bx,bx

mov di,offset note_joue_par_sample
;add di,bp
;add di,bp
add di,dx

mov eax,es:[di]

add es:[OFFSET_COMPTEUR_SAMPLE+bp],ax ;!!!

ton_doit_encore_monter_peut_etre:


mov cx,es:[OFFSET_COMPTEUR_SAMPLE+bp]
shr cx,8
add es:[OFFSET_SAMPLE+bp],cx
shl cx,8


sub es:[OFFSET_COMPTEUR_SAMPLE+bp],cx

mov ax,es:[longueur_loop_sample_joue+bp] ;si en mode loop...
add ax,es:[depart_loop_sample_joue+bp]
;or ax,ax ;cmp ax,0
jnz  tcestunsampleloopeur

mov ax,es:[longueur_sample_joue+bp]      ;si pas en mode loop...

tcestunsampleloopeur: ;comme c'est un sample loopeur on attend ne prend pas compte
                     ;de la longueur reele du sample, on s'arrete a la fin du
                     ;loop (et les fois suivante on recommencera au debut du loop)

cmp es:[OFFSET_SAMPLE+bp],ax
jb treerertrterteert

;....arrive ici en fin de sample...et on le fait passer en loop ou non...
;....attention: s'il y a un loop dans le sample, le premier passage doit
;s'arreter a la fin du loop!!! (et non a la fin normalle du passage)

;mov es:[sample_est_il_en_train_de_louper],1
mov ax,es:[depart_loop_sample_joue+bp] ;on met de tout maniere mais ca peut etre
                                    ;annule juste apres
mov es:[OFFSET_SAMPLE+bp],ax

;.........si la longueur du loop est =0 pas de loop on eteint la voix.
cmp es:[longueur_loop_sample_joue+bp],0
jne tertrertertertert
mov es:[sample_joue_en_ce_moment+bp],0 ;si=0 pas de nouveau sample joue...
tertrertertertert:
;..............................

treerertrterteert:

tnon_on_avance_pas_dans_le_sample:
mov di,es:[OFFSET_SAMPLE+bp] ;en fonction de la voix...

;.............on arrive ici avec [di] pointeur du sample...
mov ax,es:[SEGMENT_SAMPLE+bx] ;1ere sample
mov ds,ax
mov byte ptr al,ds:[di]
;add al,128
;......... le volume !!!

;mov bx,es:[volume_de_la_voix+bp]
;


mov bx,es:[volume_de_la_voix+bp]
mov dx,es:[fx_volume]

;sub dx,64
;add bx,dx
;jz kiii
;jns material_girl3
;
;kiii:
;
;
;;si le volume est egal a 0...
;mov ax,128
;jmp cas_special_si_aucun_sample_est_joue
;material_girl3:
;

imul bl ;mul al par bl...resultat dans ax...
sar ax,6

imul dl ;mul al par bl...resultat dans ax...
sar ax,6

add ax,128

tcas_special_si_aucun_sample_est_joue:
mov es:[mixage+bp],ax

add bp,2
cmp bp,8*2+4*2
jne tencore_une_voix2

;ret
;calc_voix_bonus endp
;
;
;*-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-*
pop dx ax
;...............divise par 2 en fonction du mod.
mov bx,es:[mixage+16]
add bx,es:[mixage+18]
add bx,es:[mixage+20]
add bx,es:[mixage+22]
shr bx,2
add ax,bx
;-------- si on est en sans music on divise ke par 4----
cmp es:[mode_music],0
je aeroplane2
;---------
shr ax,1
aeroplane2:
;**********************************************************

;call WR_DSP

;------------
out dx,al    ;puis envoye la commande.

;.........balance l'ancien vecteur...

ea__mode_silenceretrterte:

;call pal2B

dec es:[old_timer_compteur]
jnz dfgfgdghfgttttttttfg
mov es:[old_timer_compteur],548
pushf  ;toutes les  18.2 fois /S ici on le fait 10000 fois /S donc: 10000/18.2
call dword ptr es:[old_int8]
call teste_joystick ;en fait s'active un fois sur 5 donc 4 fois  /secondes
pop  di si edx ecx ebx eax bp es ds
popF
Iret
dfgfgdghfgttttttttfg:
;....................................

fggghghyjfyrytyt:

VERTIGEr:


mov al,20h ;                ;
out 20h,al                  ;
pop  di si edx ecx ebx eax bp es ds
popF
Iret

sortie_directe endp


RESET_SBCARD PROC NEAR
;SORTIE:      ax=0  --> pas reussit a effectuer le RESET.
;             ax=1  --> reussit a effectuer le RESET !!!

push ds es
pusha

mov ax,rmd_data
mov es,ax
mov dx,es:[dsp_adr]
add dx,06h
mov al,1
out dx,al

;mov cx,100             ;attend...
;neslet:
;nop
;loop neslet

          in      al,dx         ;attend...
          in      al,dx
          in      al,dx
          in      al,dx


mov al,0
out dx,al

mov cx,1000 ;pour bloquer le test si  ca repond toujours pas...
karmaenjirerere:
dec cx
jz karmadffffffffffff


mov dx,es:[dsp_adr]
add dx,0ah
in al,dx
cmp al,0aah
jne karmaenjirerere

popa
pop es ds
mov ax,1 ;RESET effectue.

ret

karmadffffffffffff:  ;pas de sb trouve la...

popa
pop es ds

mov ax,0 ;pas reussit a effectuer le RESET.

ret
RESET_SBCARD ENDP

DETECT_SBREG PROC NEAR
;mov ax,13h
;int 10h
;
;ret

mov ax,rmd_data
mov es,ax
mov ds,ax

mov es:[dsp_adr],210h
mov bx,0
mov dx,210 ;adresse en decimal
next_try:

call RESET_SBCARD
;SORTIE:      ax=0  --> pas reussit a effectuer le RESET.
;             ax=1  --> reussit a effectuer le RESET !!!
cmp ax,1
je ok_sb_trouve

add es:[dsp_adr],10h
add dx,10
inc bx
cmp bx,8 ;va juska 280h
je ok_sb_NON_trouve
jmp next_try
ok_sb_NON_trouve:

;sbmess1 db 'Pas de sb trouve la...',10,13,'$'
;sbmess2 db 'SB trouv‚e !!!!',10,13,'$'

;mov ax,rmd_data
;mov es,ax
;mov ds,ax

;cmp bp,1
;je no_banner3
;
;mov dx,offset sbMESS1
;mov  ah,09h
;int 21h
;
;no_banner3:

ret
ok_sb_trouve:

;mov ax,rmd_data
;mov es,ax
;mov ds,ax
;
;                                ;2=SB
mov es:[gus_or_sb],2

cmp bp,1
je no_banner3
mov ax,dx
mov dx,offset sbMESS2
call aff_port
no_banner3:

;shl bx,4 ;bidouille pour afficher le port de la SB...
;
;;sbmess3 db 'XXXXh !!','210h !!$','220h !!$','230h !!$','240h !!$','250h !!$','260h !!$','270h !!$','280h !!$'
;
;mov dx,offset sbMESS3
;add dx,bx
;int 21h

ret
DETECT_SBREG ENDP

;sbgetdspversion proc near
;;trouve le numero de la version de la dsp et le depose dans les variables
;;globales SBVERMAJ et SBVERMIN et dans SBVERSSTR
;
;push ds es
;pusha
;
;mov al,0e1h
;call wr_dsp
;
;mov ax,rmd_data
;mov es,ax
;mov ds,ax
;
;call sbreadbyte
;mov byte ptr es:[sbvermaj],al
;
;call littlenoping
;
;call sbreadbyte                    ;
;
;mov byte ptr es:[sbvermin],al
;
;;................affichage.......
;mov ax,rmd_data
;mov es,ax
;mov ds,ax
;
;mov dx,offset sbMESS4
;mov  ah,09h
;int 21h
;
;xor ax,ax
;mov al,es:[sbvermaj]
;call affsigne
;
;xor ax,ax
;mov al,es:[sbvermin]
;call affsigne
;
;popa
;pop es ds
;ret
;sbgetdspversion endp
;----------------------------
load_file proc near ;debut pareil GUS/SB puis se separe en fonction
                    ;de GUS_OR_SB
                    ;entree ECX: OFFSET DANS FICHIER DAT

push es ds di si edx ecx ebx eax

mov ax,rmd_data
mov es,ax
mov ds,ax

cmp es:[gus_or_sb],0
je pas_de_carte_detectee_avant
cmp es:[mode_music],0 ;mode special sans musique du TOUT
je viens_faire_du_fromage_de_chevre

;...ouverture fichier....

;mov dx,offset mod_file ;affiche le nom du fichier.
;mov ah,09h
;int 21h

mov dx,offset rmd_file_name
mov ah,03dh ;ouverture du fichier avec handle.
mov al,00h  ;ouverture du fichier pour lecture.
int 21h
jc erreur_file;saute si carry=1
;dans ax:handle fichier
;push ax
;mov ax,rmd_data
;mov es,ax
;mov ds,ax
;pop ax
mov word ptr es:[handle_mod_file],ax

;;... deplacement a l'interieur du fichier rmd ...
mov word ptr bx,es:[handle_mod_file]
mov ah,042h
mov al,00h ;debut du fichier
mov dx,cx
shr ecx,16

;dans cx:dx deplacement a l'interieur du fichier

int 21h
jc erreur_file;saute si carry=1

;...lecture du fichier...

mov word ptr bx,es:[handle_mod_file]
mov ah,03fh
mov cx,1084 ;pour charger header mod...
mov dx,offset header_mod
int 21h
jc erreur_file;saute si carry=1

;Recupere la taille du mod.
mov  si,offset header_mod
mov  eax,es:[si+1080]
mov  es:[mod_file_size],eax
sub  eax,1084          ;on retire juste le header
mov  es:[byte_load_left],eax ;

mov  si,offset header_mod
ADD SI,42
mov di,offset longueur_sample     ;longueur des 31 instruments.
add di,2  ;on saute le premier sample: sample vide...
mov cx,31 ;31 samples maximum.
encore_un_sample:
lodsw
rol ax,8 ;transforme format pc!
;shl ax,1 ;on multiplie par 2 (c'etait la taille en nombre de mots!)
add ax,ax
stosw
;call num
;call affsigne
add si,30-2
dec cx
jnz encore_un_sample

mov  si,offset header_mod
ADD  SI,45
xor ax,ax
mov  di,offset volume_sample     ;longueur des 31 instruments.
add  di,2  ;on saute le premier sample: sample vide...
mov cx,31 ;31 samples maximum.
encore_un_sample2:
lodsb
stosw
add si,30-1
dec cx
jnz encore_un_sample2

mov  si,offset header_mod
ADD SI,46
mov di,offset depart_loop_sample     ;longueur des 31 instruments.
add di,2  ;on saute le premier sample: sample vide...
mov cx,31 ;31 samples maximum.
encore_un_sample3:
lodsw
rol ax,8 ;transforme format pc!
;shl ax,1 ;on multiplie par 2 (c'etait la taille en nombre de mots!)
add ax,ax
stosw
;call affsigne
add si,30-2
dec cx
jnz encore_un_sample3

mov  si,offset header_mod
ADD SI,48
mov di,offset longueur_loop_sample     ;longueur des 31 instruments.
add di,2  ;on saute le premier sample: sample vide...
mov cx,31 ;31 samples maximum.
encore_un_sample4:
lodsw
rol ax,8 ;transforme format pc!
;shl ax,1 ;on multiplie par 2 (c'etait la taille en nombre de mots!)
add ax,ax
stosw
;call affsigne
add si,30-2
dec cx
jnz encore_un_sample4

mov  si,offset header_mod
ADD SI,950
mov  di,offset nombre_total_de_pattern_chanson
movsb

mov  si,offset header_mod
ADD SI,952
mov di,offset arrangement_de_la_chanson
mov cx,128
rep movsb

;... teste si c'est un mod 4 voix...
mov  si,offset header_mod
add  si,951


cmp byte ptr es:[si],'4'
jne frtretertertert
mov es:[nombre_de_voix],4
mov es:[nombre_de_voix_multiplie_par_2],4*2

jmp rttrtrtrtrrttrrtyrttyrrt
frtretertertert:
cmp byte ptr es:[si],'8'
jne frtretertertert4
mov es:[nombre_de_voix_multiplie_par_2],8*2
mov es:[nombre_de_voix],8
jmp rttrtrtrtrrttrrtyrttyrrt
frtretertertert4:

;mov dx,offset pas_bon_mod
;mov  ah,09h
;int 21h
mov bp,1 ;pas bon mod...
pop  eax ebx ecx edx si di ds es

ret
rttrtrtrtrrttrrtyrttyrrt:

;****************************** les patterns... ******************************
;calcul du nombre de patterns du mod (pas de la chanson)

;mov ax,rmd_data
;mov es,ax
;mov ds,ax
mov eax,es:[mod_file_size]

sub eax,1084 ;soustrait le header

mov di,offset longueur_sample ;calcule la taille de l'ensemble des samples.
add di,2

xor ebx,ebx
mov cx,31
la_sept:
mov bx,es:[di]
sub eax,ebx
add di,2
dec cx
jnz la_sept

mov es:[taille_segment_pattern],eax

cmp es:[nombre_de_voix],4
jne antineuralgic
shr   eax,10 ;on divise par 1024 pour 4 voix
jmp antineuralgic2
antineuralgic:
shr   eax,11 ;on divise par 2048 pour 8 voix
antineuralgic2:

mov es:[nombre_total_de_pattern_mod],al ;car le nombre max c'est 164!
;............se place au debut de la chanson...
mov bx,es:[viseur_dans_arrangement_chanson]
xor eax,eax
mov al,es:[arrangement_de_la_chanson+bx]
cmp es:[nombre_de_voix],4
jne antineuralgicr
shl   eax,10 ;on multiplie par 1024 pour 4 voix
jmp antineuralgic2r
antineuralgicr:
shl   eax,11 ;on multiplie par 2048 pour 8 voix
antineuralgic2r:
mov es:[viseur_dans_pattern],eax
;..............................................
;GUS_OR_SB db 1                  ;1=GUS
;                                ;2=SB

;si dans le mode affichage du pourcentage...
cmp es:[mode_percent],1
jne rtertertrteererterrte
push ds ax dx
mov ah,02h ;retour a la ligne
mov dl,13
int 21h
;note la ligne ou l'on est :::
mov ah,3h
xor bx,bx
int 10h
;dh:ligne du curseur!!!
mov dl,14 ;colonne
mov es:[ligne_percent],dx

mov ax,rmd_data
mov ds,ax
mov ah,9
mov dx,offset loading
int 21h
pop dx ax ds
rtertertrteererterrte:
;-------------------

viens_faire_du_fromage_de_chevre:

cmp byte ptr es:[GUS_OR_SB],1
je SAUTE_LOAD_GUS

;........................ partie SB ..........................................
;.............................................................................
;.........................................

cmp es:[mode_music],0 ;mode special sans musique du TOUT
je viens_faire_du_fromage_de_chevre_a_la_maison

;************************************************* ici pour la SB
;...reserve la memoire pour le segment pattern.
mov  eax,es:[taille_segment_pattern]

shr  eax,4 ;divise par 16.
mov  ebx,eax
inc ebx
mov  ah,48h
int  21h

jnc dfgfgfghfghhjfghjg2 ;saute si carry n'est pas a 1...

;----pas assez de memoire pour charger le segment pattern---
mov bp,3    ;
pop  eax ebx ecx edx si di ds es
ret
dfgfgfghfghhjfghjg2:
;-----------------------------------------------------------
mov es:[SEGMENT_PATTERN],ax
mov ds,ax
mov ecx,es:[taille_segment_pattern] ;nombre d'octets a charger...
mov word ptr bx,es:[handle_mod_file]

;****** chargement du fichier en plusieur fois si plus long !!! ****
party5:
cmp ecx,01024 ;FFFFh
jna rrrrrrre
push ecx bx

sub es:[byte_load_left],1024
jns ttreertertertertertyrtrtyr
mov es:[byte_load_left],0
ttreertertertertertyrtrtyr:
call aff_percent

mov cx,01024 ;FFFFh
mov ah,03fh
xor dx,dx
int 21h
pop bx ecx
sub ecx,01024 ;FFFFh
mov ax,ds
add ax,64 ;4096 ;un segement en plus
mov ds,ax
xor dx,dx
jmp party5
rrrrrrre:
;---

push ecx
and ecx,0FFFFh
sub es:[byte_load_left],ecx
jns yttreertertertertertyrtrtyr
mov es:[byte_load_left],0
yttreertertertertertyrtrtyr:
call aff_percent
pop ecx

mov word ptr bx,es:[handle_mod_file]
xor dx,dx
mov ah,03fh
mov dx,0
int 21h

;********** place le pointeur ou il faut ***
;jmp rtytyryrt
;mov ax,rmd_data
;mov es,ax
;
;mov di,offset longueur_sample ;calcule la taille de l'ensemble des samples.
;add di,2
;
;xor ebx,ebx
;xor eax,eax
;mov cx,31
;la_septe:
;mov bx,es:[di]
;add eax,ebx
;add di,2
;dec cx
;jnz la_septe
;neg eax
;mov word ptr bx,es:[handle_mod_file]
;mov dx,ax
;shr eax,16
;mov cx,ax
;mov ah,42h
;mov al,02h
;int 21h
;rtytyryrt:


cmp byte ptr es:[GUS_OR_SB],3
je fini_si_c_mode_silence


;************************** chargement des samples ***************************
;--- alloue la memoire ---
mov ax,rmd_data
mov es,ax
mov ds,ax
mov si,offset longueur_sample
add si,2  ;on saute le premier sample: sample vide...
mov di,offset SEGMENT_SAMPLE
add di,2  ;on saute le premier sample: sample vide...

mov ecx,31
fuckzerze:
push ecx
mov ax,rmd_data
mov es,ax
mov ds,ax


mov bx,es:[si]
or bx,bx ;si pas de sample...on fait rien...
jz pas_de_sample_a_loader

push di ;on valide k'il y a un sample...
sub di,offset SEGMENT_SAMPLE
add di,offset SEGMENT_SAMPLE_verif
mov word ptr es:[di],1
pop di


shr bx,4

inc bx
jnz rerrere
dec bx
rerrere:

mov ah,48h
int 21h

jnc dfgfgfghfghhjfghjg ;saute si carry n'est pas a 1...
;----pas assez de memoire pour charger sample---
;mov dx,offset erreur_memory_mess
;mov  ah,09h
;int 21h
pop ecx

mov bp,3 ;

;mov ax,bx ;taille de memoire dispo
;call affsigne
;
;mov ah,08h ;attend la frappe d'un caractere
;int 21h    ;
;mov ah,08h ;attend la frappe d'un caractere
;int 21h    ;
pop  eax ebx ecx edx si di ds es

ret

dfgfgfghfghhjfghjg:
;---------------

;on arrive ici avec dans le segment reserve en AX:0
;donc on sauvergarde ax...

mov es:[di],ax

mov cx,es:[si] ;nombre d'octets a charger...

push ecx
and ecx,0FFFFh
sub es:[byte_load_left],ecx
jns ttreertertertertertyrtrtyrtt
mov es:[byte_load_left],0
ttreertertertertertyrtrtyrtt:
call aff_percent
pop ecx

mov word ptr bx,es:[handle_mod_file]
mov ax,es:[di]
mov ds,ax

push cx ds
xor dx,dx ;offset 0
mov ah,03fh
mov dx,0
int 21h
pop ds cx

;;****** addtionne 128 a chaque sample pour le convertir en sample SB
;push si
;xor si,si
;fidele:
;add byte ptr ds:[si],128
;inc si
;dec cx
;jnz fidele
;pop si
;*****************
pas_de_sample_a_loader:
pop ecx
add di,2
add si,2

dec ecx
jnz fuckzerze
;****************************************************************************

fini_si_c_mode_silence:

;...fermeture fichier...
mov ax,rmd_data
mov es,ax
mov ds,ax
mov word ptr bx,es:[handle_mod_file]
mov ah,03eh
int 21h
jc erreur_file;saute si carry=1


cmp es:[mode_percent],1 ;pour si on affiche le pourcentage a loader...
jne irtertertrteererterrtett
mov ah,02h ;retour a la ligne
mov dl,13
int 21h
mov ah,02h ;debut de ligne
mov dl,10
int 21h
irtertertrteererterrtett:


viens_faire_du_fromage_de_chevre_a_la_maison: ;cas partioculier mode_music
;mov bp,0 ;succeded...
xor bp,bp
pop  eax ebx ecx edx si di ds es

ret
erreur_file:
;mov ax,rmd_data
;mov es,ax
;mov ds,ax
;
;mov dx,offset erreur_file_mess
;mov  ah,09h
;int 21h
mov bp,2 ;error loading file (not good file name...)
pop  eax ebx ecx edx si di ds es

ret
;................................partie GUS....
SAUTE_LOAD_GUS:

mov bp,0
call gus_Init

cmp es:[mode_music],0 ;mode special sans musique du TOUT
je vive_les_vacances_a_la_montagne

;BUFFER_LOAD_GUS DB 5000 DUP (?)
;

;...................... charge pattern + sample

mov ecx,es:[mod_file_size] ;nombre d'octet a recopier dans la GUS...


mov es:[MEMOIRE_GUS_UTILISEE],ecx
cmp ecx,es:[MEMOIRE_GUS]
jna okyaassezdeplace
mov bp,4  ;pas assez de memoire dans la GUS
pop  eax ebx ecx edx si di ds es

ret
okyaassezdeplace:

xor ebx,ebx                ;adresse dans la GUS
                           ;dans ecx taille du sample

cmp ecx,taille_buffer_load ;1024 ;5000
jb fini_juste

singer_cest:
;.... remplis le buffer .........
push ecx
push ebx
mov ecx,taille_buffer_load ;1024 ;5000

mov word ptr bx,es:[handle_mod_file]
mov ax,rmd_data
mov ds,ax
mov dx,offset header_mod; BUFFER_LOAD_GUS
mov ah,03fh
int 21h
pop ebx
mov ecx,taille_buffer_load ;1024 ;5000

;entree EBx: adresse dans la gravis (EBX est modifie par BUFFER_2GUS)
;       ecx: longueur du sample...

call BUFFER_2GUS
sub es:[byte_load_left],taille_buffer_load
jns reertertertertertyrtrtyr
mov es:[byte_load_left],0
reertertertertertyrtrtyr:
call aff_percent

add ebx,taille_buffer_load ;1024 ;5000

pop  ecx
sub  ecx,taille_buffer_load ;1024 ;5000
cmp ecx,taille_buffer_load ;1024 ;5000
jnb singer_cest
;.........fini precisement...
fini_juste:
;.... remplis le buffer ......... ;dans ecx: ce k'il reste a remplir
cmp ecx,0
je cfini
push ecx
push ebx
;mov ecx,5000
mov word ptr bx,es:[handle_mod_file]
mov ax,rmd_data
mov ds,ax
mov dx,offset header_mod ;BUFFER_LOAD_GUS
mov ah,03fh
int 21h
pop ebx
pop ecx

;entree EBx: adresse dans la gravis (EBX est modifie par BUFFER_2GUS)
;       ecx: longueur du sample...

call BUFFER_2GUS
sub es:[byte_load_left],taille_buffer_load
jns reertertertertertyrtrty
mov es:[byte_load_left],0
reertertertertertyrtrty:
call aff_percent

cfini:
;........................................... maintenant il faut
;transferer toutes ces informations:
;longueur_sample      DW 32 DUP (0)   ;longueur des 32 instruments.
;volume_sample        DW 32 DUP (0)   ;volume par defalut des 32 instruments
;depart_loop_sample   DW 32 DUP (0)   ;depart loop des 32 instruments
;longueur_loop_sample DW 32 DUP (0)   ;longueur loop des 32 instruments

;dans les variables plus adaptee a la GUS...

;adresse_debut_sample_GUS  DD 32 DUP (0)
;adresse_fin_sample_GUS    DD 32 DUP (0)
;adresse_loop_sample_GUS   DD 32 DUP (0)
mov ax,rmd_data
mov es,ax
mov ds,ax

mov ebx,es:[taille_segment_pattern]

mov si,offset longueur_sample
mov di,offset adresse_debut_sample_GUS

mov cx,32
rejouit:
xor eax,eax
lodsw
push eax
mov eax,ebx
;call num
stosd
pop eax
add ebx,eax
dec cx
jnz rejouit

;adresse_debut_sample_GUS  DD 32 DUP (0)
;adresse_fin_sample_GUS    DD 32 DUP (0)

;important: s'il y a un loop... ca change l'adresse de fin.
;adresse de fin= debut loop + longueur loop
mov di,offset longueur_sample
mov bx,0

mov cx,32
erreerreerrere:
mov si,offset depart_loop_sample
mov ax,es:[si+bx]
mov si,offset longueur_loop_sample
add ax,es:[si+bx]
add bx,2
or ax,ax
jz ererreer     ;on ne change ke s'il y a un loop...
mov es:[di],ax
ererreer:
add di,2
dec cx
jnz erreerreerrere

k:
;depart_loop_sample   DW 32 DUP (0)   ;depart loop des 32 instruments
;longueur_loop_sample DW 32 DUP (0)   ;longueur loop des 32 instruments

mov si,offset adresse_debut_sample_GUS
mov di,offset adresse_fin_sample_GUS
mov cx,32
rep movsd

mov si,offset longueur_sample
mov di,offset adresse_fin_sample_GUS

mov cx,32
rereererrere:
xor eax,eax
lodsw
add dword ptr es:[di],eax
add di,4
dec cx
jnz rereererrere

;adresse_debut_sample_GUS  DD 32 DUP (0)
;adresse_loop_sample_GUS    DD 32 DUP (0)

mov si,offset adresse_debut_sample_GUS
mov di,offset adresse_loop_sample_GUS
mov cx,32
rep movsd

mov si,offset depart_loop_sample
mov di,offset adresse_loop_sample_GUS

mov cx,32
rrereererrere:
xor eax,eax
lodsw
add dword ptr es:[di],eax
add di,4
dec cx
jnz rrereererrere


;...fermeture fichier..
;mov ax,rmd_data
;mov es,ax
;mov ds,ax
mov word ptr bx,es:[handle_mod_file]
mov ah,03eh
int 21h
jc erreur_file;saute si carry=1

cmp es:[mode_percent],1 ;pour si on affiche le pourcentage a loader...
jne irtertertrteererterrte
mov ah,02h ;retour a la ligne
mov dl,13
int 21h
mov ah,02h ;debut de ligne
mov dl,10
int 21h
irtertertrteererterrte:


;mov bp,0 ;succeded
vive_les_vacances_a_la_montagne:
xor bp,bp
pop  eax ebx ecx edx si di ds es
ret
;---------------- Cas ou pas de carte detectee avant
pas_de_carte_detectee_avant:
mov bp,5
pop  eax ebx ecx edx si di ds es
ret
load_file endp


aff_texte proc near ;entree es:[si] debut de la chaine. cx:longueur chaine.
push ax dx si cx
mov ah,02h
dfrteeeeeeeeeeeeey:
mov dl,es:[si]
inc si
int 21h
dec cx
jnz dfrteeeeeeeeeeeeey

mov dl,10
int 21h
mov dl,13
int 21h

pop cx si dx ax
ret
aff_texte endp

num proc near ;entree eax:juska 9999999999
push dx si
push ebx eax ecx

;mov eax,0543212345

mov ebx,eax

mov si,offset liste_de_machin
mov ecx,cs:[si]
errrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr:
mov ax,0
rrtetrertertretertterert:
cmp ebx,ecx ;10000
jb reerrereerret
sub ebx,ecx ;10000
inc ax
jmp rrtetrertertretertterert
reerrereerret:
;affchiffre
push ax
push dx
add al,48
mov dl,al
mov ah,2
int 21h
pop ax
pop dx


add si,4
mov ecx,cs:[si]
or ecx,ecx
jz reererreer
jmp errrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
reererreer:

mov dl,' '
mov ah,2
int 21h

pop ecx eax ebx
pop si dx
ret

liste_de_machin dd 1000000000,100000000,10000000,1000000,100000,10000,1000,100,10,1,0

num endp

calc_freq_sb proc near ;calcul les rapports entre la frequence de chaque note et
                    ;la frequence du timer.
mov ax,rmd_data
mov es,ax
mov ds,ax
;on multiplie...par 8^2
;donc on aura une virgule apres les 24 premiers bits.
mov si,offset sbfreq
mov cx,12*8
fool_me:
shl dword ptr es:[si],8
add si,4
dec cx
jnz fool_me
;maintenant on va diviser par 10000 (la frequence...)
;apres on obtiendra un nombre...a chaque passe de la routine ca rajoutera
;cette valeur au nombre et s'il est superieur a 0ffh on avancera dans le
;mod...

mov si,offset sbfreq
mov cx,12*5
fool_mee:
mov eax,es:[si]

xor edx,edx
mov ebx,10000
div ebx

mov es:[si],eax
add si,4
dec cx
jnz fool_mee

ret
calc_freq_sb endp


lit_pattern proc near

;              mov eax,es:[viseur_dans_pattern] ;vise sur la note jouee...
;              call affsigne ;num
;              on anule les effect ki durent entre les ligneS...
;              pour les 8 voix.

mov es:[table_de_saut],offset nopper
mov es:[table_de_saut+2],offset nopper
mov es:[table_de_saut+4],offset nopper
mov es:[table_de_saut+6],offset nopper
mov es:[table_de_saut+8],offset nopper
mov es:[table_de_saut+10],offset nopper
mov es:[table_de_saut+12],offset nopper
mov es:[table_de_saut+14],offset nopper

xor bp,bp ;num‚ro de voix*2
encore_une_voix:

mov ax,es:[SEGMENT_PATTERN]
mov esi,es:[viseur_dans_pattern] ;vise sur la note jouee...

;----- on va modifier DS en fonction de ESI
push edi
mov edi,esi
shr edi,4                                                   ;64
add ax,di
pop  edi
and esi,0001111B
;--------
mov ds,ax

xor eax,eax
mov ax,bp  ;note:...on incremente de 4...car on lit pas le meme octet!!
add esi,eax
add esi,eax
                                ;
                                ;valeur k'on additionne pour
                                ;piocher dans le segment pattern
xor ax,ax
lodsb

or al,al ;important si c'est le sample 0; aucune modification a faire
jz pas_de_modif_sample

;----- Quand on change un sample: cv'est ici k'on change le volume.
;      pas ailleur...on change donc juste:le volume et le prochain sample
;      qui sera joue...

mov bx,ax

mov es:[sample_joue_en_ce_moment+bp],bx ;+numero voix*2
                                     ;note: si on met 0 il n'y a pas
                                     ;de sample joue du tout.
                                     ;...
                                     ;or si le numero du sample  est a 0
                                     ;ici on se contente de joue du dernier
                                     ;instrument.
;shl bx,1
add bx,bx

;dans bx: numero du sample joue *2 ;!
mov ax,es:[volume_sample+bx] ;(bx=+numero sample*2)
mov es:[volume_de_la_voix+bp],ax ;+numero voix*2


pas_de_modif_sample:
;................ frequence/note
xor bx,bx
xor ax,ax
lodsb ;charge deuxieme octet format remdy
cmp al,-1 ;code special indique k'il n'y a pas de note...
je  pas_de_noteee ;pas de nouvelle note
shl ax,2 ;on multiplie par 4 (permet de stocker plus petit!)
mov bx,ax
mov eax,es:[sbfreq+bx]

;on sauvegarde bx (utile pour les effets...)
mov es:[SAUVE_VISEUR_DANS_SBFREQ+BP],BX

;note_joue_par_sample DD 4 DUP (?)   ;place la vitesse en HZ direct!

mov di,offset note_joue_par_sample    ;+numero voix*4
add di,bp
add di,bp
mov es:[di],eax

;...joue le bon sample...................................
mov bx,es:[sample_joue_en_ce_moment+bp]
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

mov es:[OFFSET_COMPTEUR_SAMPLE+bp],0    ;+numero voix*4

pas_de_noteee:
;.......... les effets sont nos amis.
lodsw
;call num
;dans al:numero effet
;dans ah:commande effet
;on a dans bp=la voix*2

call effets1     ;detection de tous les effets.

add bp,2
cmp bp,es:[nombre_de_voix_multiplie_par_2]

jne encore_une_voix

ret
lit_pattern endp

;****************************************************************************
;****************************************************************************
;****************************************************************************
;****************************************************************************
effets1 proc near ;detection de tous les effets.
                  ;on a dans bp=la voix*2
                  ;dans al:commande
                  ;dans ah:=parametre
push di eax si bx

;************** effet 0, Arpeggio...
;effect qui dure entre les lignes...
;pas besoin du convertisseur
cmp al,0
jne rfraiche2c3

cmp ah,0          ;si le parametre est aussi a 0 il n'y a pas d'effet!
je rfraiche2c3    ;
;on a sauvegard‚ SAUVE_VISEUR_DANS_SBFREQ+BP
;ce ki va permettre de recuperer les frequences des deux notes k'on va nous
;demander.

push ax ;(1)
shr ax,8+4
;on a dans ax:le nombre de demi-tons a rajouter.
mov bx,es:[SAUVE_VISEUR_DANS_SBFREQ+BP]
push ax
mov eax,es:[sbfreq+bx]
;call num
mov si,offset FREQUENCE_POUR_LES_3_NOTES1
add si,bp
add si,bp
mov es:[si],eax
pop ax

shl ax,2 ;on multiplie par 4 le nombre de demi-ton a rajouter.

push ax  bx
sub bx,ax
jnc orsay4  ;cas particulier:depasserait les valeurs possible (trop aigu)
xor bx,bx
orsay4:

mov eax,es:[sbfreq+bx]
mov si,offset FREQUENCE_POUR_LES_3_NOTES2
add si,bp
add si,bp
mov es:[si],eax
;call num
pop bx ax

pop ax ;(1)

shr ax,8
and ax,00001111B
shl ax,2
;call affsigne

push ax bx
sub bx,ax
jnc orsay2  ;cas particulier:depasserait les valeurs possible (trop aigu)
xor bx,bx
orsay2:
mov eax,es:[sbfreq+bx]
mov si,offset FREQUENCE_POUR_LES_3_NOTES3
add si,bp
add si,bp
mov es:[si],eax
;call num
pop bx ax

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

mov es:[table_de_saut+bp],offset fx_arpegio

jmp fin_proc_effet1

rfraiche2c3:

;************** effet 1 et 2 PORTAMENTO UP/DOWN
;effect qui dure entre les lignes...


cmp al,01
je rfraiche2cE

cmp al,02
jne rfraiche2c

shr ax,8

shl ax,3 ;get the fuck

jmp dooooown
rfraiche2cE:

shr ax,8

shl ax,3

;....dans ax on a le parametre...

rtrttyrrtyyrt:

mov di,offset note_joue_par_sample
add di,bp
add di,bp

movzx eax,ax

add dword ptr es:[di],eax
;add dword ptr es:[di],eax
;add dword ptr es:[di],eax

cmp dword ptr es:[di],0FFFFH
jb uhuhuh

cmp dword ptr es:[di],01FFFFH
ja uhuhuh2

mov dword ptr es:[di],0FFFFH ;parre fou!!!

jmp fin_proc_effet1

uhuhuh2:
sub dword ptr es:[di],eax
;sub dword ptr es:[di],eax
;sub dword ptr es:[di],eax
uhuhuh:

jmp fin_proc_effet1
;----------down
dooooown:

mov di,offset note_joue_par_sample
add di,bp
add di,bp

movzx eax,ax

sub dword ptr es:[di],eax
jc uuuuuuuuuh
;sub dword ptr es:[di],eax
;jc uuuuuuuuuh
;sub dword ptr es:[di],eax
;jc uuuuuuuuuh

jmp fin_proc_effet1
uuuuuuuuuh:
mov dword ptr es:[di],80
jmp fin_proc_effet1
rfraiche2c:

;************** 3 TONE PORTAMENTO
;effect qui dure entre les lignes...

cmp al,5 ;TONE PORTAMENTO+ VOLUME SLIMING sans nouvelle note...
je sexyremdy1

cmp al,-1 ;TONE PORTAMENTO sans nouvelle note...
je sexyremdy
;----------------nouvelle note------------
cmp al,20
jb rfraiche2cER

push ax
and ax,255
sub ax,20
;call affsigne
shl ax,2 ;on multiplie par 4 (permet de stocker plus petit!)
mov bx,ax
mov eax,es:[sbfreq+bx]
mov si,offset SAVE_NOTE_PORTAMENTO
add si,bp
add si,bp
mov es:[si],eax
pop ax
;------------------kan on arrive ici on se raproche de l'autre note...

mov es:[sauvegarde_de_la_vitesse_du_portamento+bp],ax
;------------------kan on arrive ici on se raproche de l'autre note...
JMP sexyremdy
;----ZONE POUR LE VOLUME SLIMING EN PLUS
sexyremdy1:


;******* s'occupe du volume slim

shr ax,8 ;

mov es:[table_de_saut+bp],offset fx_volumeslimingdown
mov es:[adder_effect_entre_ligne+bp],ax ;definis la vitesse...
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

;------------ fini par le portamento

mov ax,es:[sauvegarde_de_la_vitesse_du_portamento+bp]

sexyremdy:

or ah,ah
jnz gles_2
;si ah=0 on utilise la derniere valeur de vitesse de portamento k'on a utilise
mov ax,es:[sauvegarde_de_la_vitesse_du_portamento+bp]
gles_2:

movzx edx,ah

;shl edx,4 ;on multiplie le facteur ; arbitraire.

mov ebx,edx
add edx,ebx ;*2
add edx,ebx ;*3
add edx,ebx ;*4
add edx,ebx ;*5
add edx,ebx ;*6
add edx,ebx ;*7
add edx,ebx ;*8
add edx,ebx ;*9

mov si,offset SAVE_NOTE_PORTAMENTO
add si,bp
add si,bp
mov eax,es:[si]
cmp eax,-1
je probleme_fais_rienddd ;si pas de note avant...on fait rien,.

mov si,offset note_joue_par_sample ;sauvegarde la note pour la remettre a la fin
add si,bp
add si,bp

cmp dword ptr es:[si],-1
je probleme_fais_rienddd ;si on a pas joue de vrai notes avant on ne fait rien

mov ebx,es:[si]

cmp ebx,eax
je oooooouuuuuuuuuh
ja river
add ebx,edx
jc omethingyousaid
cmp ebx,eax
jb oooooouuuuuuuuuh
omethingyousaid:
mov ebx,eax
jmp oooooouuuuuuuuuh
river:
sub ebx,edx
jc ighttt
cmp ebx,eax
ja oooooouuuuuuuuuh
ighttt:
mov ebx,eax

oooooouuuuuuuuuh:

mov es:[si],ebx

probleme_fais_rienddd: ;si pbs carry!
jmp fin_proc_effet1

rfraiche2cER:
;************** effet 4, VIBRATO
;effect qui dure entre les lignes...

cmp al,04
jne rfraiche2c2_f

;push ax
;xor eax,eax
;pop ax

and eax,01111111111111111B

push ax
shr ax,8
and ax,01111B ;ici on a donc Y profondeur
jz hihhiihhihi3
mov es:[vibrato_fx_prof+bp],ax
hihhiihhihi3:
;call num
pop ax

;push ax

shr ax,8+4    ;ici on a donc X vitesse
;shl ax,1      ;multiplie par 2 arbitrairement
add ax,ax

jz hihhiihhihi4
mov es:[vibrato_fx_speed+bp],ax
hihhiihhihi4:

;call num
;pop ax

;mov es:[VIBRATO_viseur],0

call calcule_la_duree_dun_tick
;dans ax on a le nombre de vibrato compteur a passer pour faire a un tick.
;on doit diviser ca parla vitesse du truc

xor dx,dx
mov bx,es:[vibrato_fx_speed+bp]
or bx,bx
jz rtrttterertrte
div bx
jmp rerererer
rtrttterertrte:
mov ax,es:[VIBRATO_compteur_save+bp] ;si la vitesse=0 on reprend la derniere
                                     ;vitesse k'on a eu...
rerererer:

;attention:cas particlier:si la zik etait tres rapide...
;il est possible ke la division donne zero (c'est a dire k'il faudrait une
;modif plus souvent ke le le player est appele en hz..on reduira donc a un fois...)
or ax,ax
jnz erreerththrtrt
mov ax,1
erreerththrtrt:

mov es:[VIBRATO_compteur_save+bp],ax
mov es:[VIBRATO_compteur+bp],ax

mov es:[table_de_saut+bp],offset VIBRATO_fx

mov si,offset note_joue_par_sample ;sauvegarde de la frequence actuelle
                                   ;de la note pour la remettre a la fin
add si,bp
add si,bp
mov eax,es:[si]
mov si,offset SAVE_NOTE_VIBRATO
add si,bp
add si,bp
mov es:[si],eax


jmp fin_proc_effet1
rfraiche2c2_f:

;************** effet 6 VOLUMESLIMING DOWN + VIBRATO...

cmp al,6
jne rfraiche2g
shr ax,8
;******* s'occupe du volume sliming ******
;push ax

and ax,01111B
;on a dans ax la vitesse du volumesliming down...

mov es:[table_de_saut+bp],offset fx_volumeslimingdown_vibrato
mov es:[adder_effect_entre_ligne+bp],ax ;definis la vitesse...
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

;pop ax
;******** s'occupe du vibrato ************
; NON !! dans FT2 ya pas de changement de vitesse de vibrato possible ici...
;donc on fait rien

jmp fin_proc_effet1
rfraiche2g:

;************** effet 7, TREMOLO
;effect qui dure entre les lignes...

cmp al,07
jne rfraiche2c2_fg

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
;dans ax on a le nombre de TREMOLO compteur a passer pour faire a un tick.
;on doit diviser ca parla vitesse du truc

xor dx,dx
mov bx,es:[TREMOLO_fx_speed+bp]
or bx,bx
jz rtrttterertrteg
div bx
jmp rererererg
rtrttterertrteg:
mov ax,es:[TREMOLO_compteur_save+bp] ;si la vitesse=0 on reprend la derniere
                                     ;vitesse k'on a eu...
rererererg:

;attention:cas particlier:si la zik etait tres rapide...
;il est possible ke la division donne zero (c'est a dire k'il faudrait une
;modif plus souvent ke le le player est appele en hz..on reduira donc a un fois...)
or ax,ax
jnz rerreerththrtr
mov ax,1
rerreerththrtr:

mov es:[TREMOLO_compteur_save+bp],ax
mov es:[TREMOLO_compteur+bp],ax

mov es:[table_de_saut+bp],offset TREMOLO_fx

;mov ax,es:[volume_de_la_voix+bp]
;mov es:[SAVE_VOLUME_TREMOLO+BP],ax

;mov es:[STOP_TREMOLO+bp],0
;
;*******************
;cmp es:[STOP_TREMOLO+bp],1
;jne erreererer
;mov ax,es:[SAVE_VOLUME_TREMOLO+BP]
;mov es:[volume_de_la_voix+bp],ax
;mov es:[STOP_TREMOLO+bp],0
;erreererer:


jmp fin_proc_effet1
rfraiche2c2_fg:

;************** effet 9,definir offset sample.

cmp al,09
jne rfraiche2ct


;on doit mutliplier par 256 l'operante...
;ca equivaut:
and  ax,01111111100000000B
;call affsigne
mov bx,es:[longueur_sample_joue+bp]



cmp ax,bx ;cas particluier verifie ke l'offset demande est pas hors du sample.
ja bien_sur      ;si c'est le cas on arrete le sample

;il reste un deuxieme cas particulier, si c'est un sample a boucle.
;et que l'on voudrait sauter a une position apres la zone de boucle (la fin
;du sample en fait) ben faut jouer rien.

cmp es:[longueur_loop_sample_joue+bp],0
je cbononyvamapoule
mov bx,es:[depart_loop_sample_joue+bp]
add bx,es:[longueur_loop_sample_joue+bp]
cmp ax,bx
ja bien_sur

cbononyvamapoule:

mov es:[offset_sample+bp],ax

jmp fin_proc_effet1
bien_sur:
mov es:[sample_joue_en_ce_moment+bp],0
;cas particulier:ce code signifie ke aucun sample est joue...
jmp fin_proc_effet1
rfraiche2ct:


;************** effet A (10),VOLUMESLIMING.
;pas besoin du converisseur de parametre...
;effect qui dure entre les lignes...
;peut etre up ou down...en fonction du parametre (xxxxYYYY)
;(si c'est en xxxx c'est up a la vitesst xxxx)


cmp al,0Ah
jne rfraiche2
shr ax,8 ;

cmp ax,0fh
ja laondoitmonterleson
;
;call affsigne

mov es:[table_de_saut+bp],offset fx_volumeslimingdown
mov es:[adder_effect_entre_ligne+bp],ax ;definis la vitesse...
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

jmp cestpartis
laondoitmonterleson:
shr ax,4
;call affsigne
mov es:[table_de_saut+bp],offset fx_volumeslimingup
mov es:[adder_effect_entre_ligne+bp],ax ;definis la vitesse...
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

cestpartis:


;cmp ax,64
;ja rya_un_prob_mieux_vaut_rien_faire
;mov es:[volume_de_la_voix+bp],ax
;rya_un_prob_mieux_vaut_rien_faire:
jmp fin_proc_effet1
rfraiche2:

;************** effet B (11),position jump
;effet_B dw 0,0  ;premier mot: 0=pas active,1=active
;                ;deuxieme mot: numero le la ligne ou on se place dans la
;                ;pattern suivante...

;a PAS besoin du converisseur de parametre...
cmp al,0Bh
jne rfraicher4
shr ax,8 ;


;call affsigne
mov bx,es:[nombre_total_de_pattern_chanson]
cmp ax,bx

jb cokcdanslarrangement
;si c'est pas dans l'arrangement on met au 1er pattern de l'arrangement pattern
xor ax,ax
cokcdanslarrangement:
mov es:[effet_B],1 ; db 0,0  ;premier mot: 0=pas active,1=active
mov es:[effet_B+2],ax ;
jmp rfin_proc_effet1
rfraicher4:
;************** effet C (12),changement du volume d'un voix
;a pas besoin du converisseur de parametre...
cmp al,0Ch
jne rfraiche
shr ax,8 ;
;
;call affsigne

cmp ax,64
ja rya_un_prob_mieux_vaut_rien_faire
mov es:[volume_de_la_voix+bp],ax
rya_un_prob_mieux_vaut_rien_faire:
jmp fin_proc_effet1
rfraiche:
;************** effet D (13),pattern break.
;egghffgffet_D db 0,0  ;premier octet: 0=pas active,1=active
;      ghf          ;deuxieme octet: numero le la ligne ou on se place dans la
;dffd        fghfgh dw 0    ;mot: viseur_dans_arrangement comme on se placera ensuite...
;    dfdf           ;pattern suivante...
;a besoin du converisseur de parametre...
cmp al,0Dh
jne rfraicher
shr ax,8 ;

;call num
;call affsigne

cmp ax,63
;pour l'effet D,le parametre est dans le fichier comme du decimal pris pour
;de l'hexa!!! bizarre..

ja rya_un_prob_mieux_vaut_rien_fairer
mov es:[effet_D],1 ; db 0,0  ;premier mot: 0=pas active,1=active
mov es:[effet_D+2],aX ;

mov ax,es:[nombre_total_de_pattern_chanson] ;donne nombre
mov bx,es:[viseur_dans_arrangement_chanson] ;nombre mais commence a 0
inc bx
cmp bx,ax
jb cokoncointinure ;
xor bx,bx
cokoncointinure:
mov es:[effet_D+4],bx ;

rya_un_prob_mieux_vaut_rien_fairer:
jmp fin_proc_effet1
rfraicher:


cmp al,0Eh ;test pour sauter le gros tas de E!!!
je okokokokok
jmp okokokokok2passetouslesE
okokokokok:

;;************** effet E (14) E.1 et 2 14.1 et 2 FINESLIDE UP et DOWN****
;cmp al,0Eh
;jne tdepressed33t
;xor ebx,ebx
;mov bx,ax   ;sauvegarde ax...
;shr ax,8+4
;cmp ax,01
;je tdepressed233t
;cmp ax,02
;je tdepressed233t2
;mov ax,bx
;jmp tdepressed33t
;tdepressed233t:
;;.......Up
;shr bx,8
;and bx,01111B ;parametre..
;
;and ebx,0FFFFh
;shl ebx,2 ;!on multiplie pour ke ca aille plus vite... ;** AU PIF !!
;mov di,offset note_joue_par_sample
;add di,bp
;add di,bp
;erttttt:
;add dword ptr es:[di],ebx
;jc erttttt2
;jmp fin_proc_effet1
;;..............DOWN
;tdepressed233t2:
;
;shr bx,8
;and bx,01111B ;parametre..
;
;shl ebx,2 ;!on multiplie pour ke ca aille plus vite... ;** AU PIF !!
;mov di,offset note_joue_par_sample
;add di,bp
;add di,bp
;erttttt2:
;sub dword ptr es:[di],ebx
;jc erttttt
;jmp fin_proc_effet1
;
;tdepressed33t:
;
;;************** effet E (14) 14.4 SELECTIONNE LE TYPE DE VIBRATO ****
cmp al,0Eh
jne fdepressed
mov bx,ax   ;sauvegarde ax...
shr bx,8+4  ;1er parametre doit etre egal a 4.
cmp bx,4
jne fdepressed

shr ax,8
and ax,0001111B
;call affsigne

cmp ax,0
jne errererr
mov ax,offset VIBRATO_SIN
mov es:[what_vibrato],ax
errererr:


cmp ax,1
jne errerer
mov ax,offset VIBRATO_1
mov es:[what_vibrato],ax
errerer:

cmp ax,2
jne errerer2
mov ax,offset VIBRATO_2
mov es:[what_vibrato],ax
errerer2:


mov es:[VIBRATO_viseur+bp],0
jmp fin_proc_effet1
fdepressed:

;************** effet E (14) 14.6 LOOP ****
cmp al,0Eh
jne depressed
mov bx,ax   ;sauvegarde ax...
shr ax,8+4  ;1er parametre doit etre egal a 6 sinon c'est pas une LOOP...
cmp ax,6
je depressed2
mov ax,bx
jmp depressed
depressed2:
;------ ON A BIEN une loop,2 possibilites:
;      1ø) marquage du debut d'une loop.
;      2ø) saut dans une loop
shr bx,8           ;
and bx,0001111B    ;2eme parametre:  si =0 ca veut dire ligne a conserver
                   ;                 si <>0 ca veut dire nombre de fois k'on
                   ;                 doit retourner a la ligne conservee.
cmp bx,0
jne nonon_cpaslapermierepzrtieduloop
;------ 1ø) ICI il faut juste conserver

mov eax,es:[numero_de_ligne_dans_pattern]
mov es:[FXLOOP2],eax

jmp fin_proc_effet1
nonon_cpaslapermierepzrtieduloop:
;2ø) dans bx on a le nombre de fois k'il faut sauter...

cmp es:[FXLOOP1],-1 ;on a cette valeur juste au debut...
                    ;une fois k'on a sauvegarde elle n'y est plus...
jne breuuuuuuuuuuuuuuu
mov es:[FXLOOP1],bx ;on sauvegarde le nombre de fois k'on doit sauter.
                    ;il ne faut faire cette sauvegarde k'au premier passage.
breuuuuuuuuuuuuuuu:

cmp es:[FXLOOP1],0  ;si c'est a la fin de la boucle il faut arreter de sauter.
je rfrrerererere    ;
mov es:[effet_E6],1 ;indique a la procedure ki va suivre de sauter
dec es:[FXLOOP1]    ;on decremente le nombre de fois k'il faut sauter
jmp fin_proc_effet1
rfrrerererere:
mov es:[FXLOOP1],-1 ;permet d'avoir d'autres boucles ensuite.
jmp fin_proc_effet1
depressed:

;************** effet E (14) 14.7 SELECTIONNE LE TYPE DE TREMOLO ****
cmp al,0Eh
jne fdepressedh
mov bx,ax   ;sauvegarde ax...
shr bx,8+4  ;1er parametre doit etre egal a 4.
cmp bx,7
jne fdepressedh

shr ax,8
and ax,0001111B
;call affsigne

cmp ax,0
jne errererrh
mov ax,offset VIBRATO_SIN
mov es:[what_TREMOLO],ax
errererrh:


cmp ax,1
jne errererh
mov ax,offset VIBRATO_1
mov es:[what_TREMOLO],ax
errererh:

cmp ax,2
jne errerer2h
mov ax,offset VIBRATO_2
mov es:[what_TREMOLO],ax
errerer2h:

mov es:[TREMOLO_viseur+bp],0
jmp fin_proc_effet1
fdepressedh:

;************** effet E (14) E.9 14.9 NOTE RETRIGGERING ****
;retappe la note a partir d'un certain battement.

cmp al,0Eh
jne rkdepressed33
mov bx,ax   ;sauvegarde ax...
shr ax,8+4
cmp ax,9
je rkdepressed233
mov ax,bx
jmp rkdepressed33
rkdepressed233:

shr bx,8
and bx,01111B ;parametre..

;****
cmp bx,es:[speed_song]
jb rtoutevotreviet
jnz rtoutevotreviet
;cas aussi un peu particulier... speed_song>ou= a parametre
;on fait rien...
jmp fin_proc_effet1
rtoutevotreviet:


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

mov es:[table_de_saut+bp],offset fx_noteRETRIG

jmp fin_proc_effet1

rkdepressed33:

;************** effet E (14) E.A/B 14.10/11 FINE VOLUMESLIDING UP+DOWN ****
cmp al,0Eh
jne tdepressed33
mov bx,ax   ;sauvegarde ax...
shr ax,8+4
cmp ax,010
je tdepressed233

cmp ax,0bh
je tdepressed233b

mov ax,bx
jmp tdepressed33
tdepressed233:

shr bx,8
and bx,01111B ;parametre..

;call affsigne

add es:[volume_de_la_voix+bp],bx
cmp es:[volume_de_la_voix+bp],64
jna finirerere
mov es:[volume_de_la_voix+bp],64
finirerere:
jmp fin_proc_effet1

tdepressed233B:

shr bx,8
and bx,01111B ;parametre..

;call affsigne

sub es:[volume_de_la_voix+bp],bx
cmp es:[volume_de_la_voix+bp],0
jns finirererer
mov es:[volume_de_la_voix+bp],0
finirererer:
jmp fin_proc_effet1

tdepressed33:


;************** effet E (14) E.C 14.12 NOTE CUT ****
cmp al,0Eh
jne depressed33
mov bx,ax   ;sauvegarde ax...
shr ax,8+4
cmp ax,0ch
je depressed233
mov ax,bx
jmp depressed33
depressed233:
;on devra arreter la note a
;(SPEED_COMPTEUR_SAVE)-(duree d'un tick*parametre)

shr bx,8
and bx,01111B ;parametre..

;............
cmp bx,es:[speed_song]
jb toutevotrevier
;cas aussi un peu particulier... speed_song>ou= a parametre
;on fait rien...

jmp fin_proc_effet1
toutevotrevier:
or bx,bx
jnz noncpaszeror
;....cas un peu particluier: si le parametre est egal a 0 on coupe la note de
; suite (pas vraiment particluier mais insdispencable a cause le l'aproximation.
mov ebx,es:[SPEED_COMPTEUR]
dec ebx
mov si,offset SPEED_COMPTEUR_TEST_EFFET12
add si,bp
add si,bp
mov es:[si],ebx

mov es:[table_de_saut+bp],offset fx_notecut

jmp fin_proc_effet1
;..........................

noncpaszeror:

xor eax,eax

call calcule_la_duree_dun_tick
mul bx
;call num
mov ebx,es:[SPEED_COMPTEUR]
;sub ebx,5 ;car calcule_la_duree_dun_tick approximatif
sub ebx,eax
;donc on devra arreter la note une fois arrive a speed_compteur=ebx

;dec ebx ;de 1 car chiant kan c'etait juste (vitesse et parametre egal-->note
;jouee en entier...)

mov si,offset SPEED_COMPTEUR_TEST_EFFET12
add si,bp
add si,bp
mov es:[si],ebx

mov es:[table_de_saut+bp],offset fx_notecut

;speed_song   dw  6
;speed_compteur_save dd 1200 ;vitesse 6 par default.

;dans ax:resultat
; SPEED_resultat: a partir dukel
;call num

jmp fin_proc_effet1

depressed33:

;************** effet E (14) E.D 14.13 NOTE DELAY ****
;le parametre Y indique le nombre de ticks pendant lequels il faut
;retarder la voix...

cmp al,0Eh
jne kdepressed33
mov bx,ax   ;sauvegarde ax...
shr ax,8+4
cmp ax,0dh
je kdepressed233
mov ax,bx
jmp kdepressed33
kdepressed233:

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

mov es:[table_de_saut+bp],offset fx_notedelay

mov ax,es:[sample_joue_en_ce_moment+bp] ;sauvegarde pour bloquer note...
mov es:[NOTE_DELAY2+BP],ax

mov es:[sample_joue_en_ce_moment+bp],0 ;arrete le sample...

;0FFFFh
;NOTE_DELAY dd 4 DUP (0)
;NOTE_DELAY2 dw 4 DUP (0) ;pour sauver sample_joue_en_ce_moment dw 4 dup (0)
;                         ;et on met 0 le temps k'on attend.

jmp fin_proc_effet1

kdepressed33:

;************** effet E (14) E.E 14.14 DELAI POUR LE PATTERN ****
;note: on attend pas le nombre de beats (tick) donnes mais plutot le nombre
;de Notes comme le fait FT2. year.

cmp al,0Eh
jne depressed3
mov bx,ax   ;sauvegarde ax...
shr ax,8+4  ;1er parametre doit etre egal a 6 sinon c'est pas une LOOP...

;call affsigne

cmp ax,0Eh
je depressed23
mov ax,bx
jmp depressed3
depressed23:
shr bx,8
and bx,01111B
or bx,bx
jz depressed3 ;si c'est 0 on change rien...

mov eax,es:[speed_compteur_save]

cmp word ptr es:[speed_compteur_save+2],0 ;cas particulier non prevu mais
                                 ; n'arrivant
                                 ;jamais:speed_compteur_save > a 0FFFFh
jne fin_p                        ;

mul bx
mov word ptr es:[speed_compteur],ax
mov word ptr es:[speed_compteur+2],dx

fin_p:
jmp fin_proc_effet1
depressed3:

okokokokok2passetouslesE:

;************** effet F (15),changement de la vitesse d'execution
;a besoin du convertisseur de parametre...
;
;deux action differante celui le parametre:
; <32: nouvelle SPEED_SONG dans parametre (valeurs:0 a 31)
; =>32 :nouvelle BMP_SPEED dans parametre (valeur:32 a 0FFH)

cmp al,0Fh
jne fraiche
shr ax,8 ;

cmp ax,31
ja la_il_faut_carement_changer_le_bmp
mov es:[speed_song],ax
;call affsigne
shl ax,2 ;multiplie par 4...
mov di,offset Speed_wait
add di,ax
mov eax,es:[di]
mov es:[speed_compteur_save],eax
mov es:[speed_compteur],eax

jmp fraiche

la_il_faut_carement_changer_le_bmp:
mov es:[bmp_speed],al

call calc_new_speed    ;calcule un nouvelle table de speed.
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

fraiche:
;*****************
fin_proc_effet1:
pop bx si eax di
ret
effets1 endp

;****************************************************************************
;****************************************************************************
;****************************************************************************
;****************************************************************************

effets2 proc near ;effets valable pour SB et GUS
                ;effet ki s'activent lorsqu'on a fini la ligne courante
                ;(detect‚s grace a effet 1)
push eax

;************** mise en place de l'effet B (11),position jump
cmp es:[effet_B],1
jne blur_house2
xor eax,eax
mov bx,es:[effet_B+2]

mov dword ptr es:[numero_de_ligne_dans_pattern],0 ;on doit recommencer au
                                                  ;debut du pattern annonc‚
mov es:[viseur_dans_arrangement_chanson],bx

xor eax,eax
mov al,es:[arrangement_de_la_chanson+bx]
shl eax,10 ;multiplie par 1024...
           ;on a donc dans ax le viseur_dans_pattern

mov es:[viseur_dans_pattern],eax

mov word ptr es:[effet_B],0  ;on arrete l'effet...
;jmp fin_proc_effet2
blur_house2:
;**********************************

;************** mise en place de l'effet D (15),pattern break.
cmp es:[effet_D],1
jne blur_house
xor eax,eax
mov ax,es:[effet_D+2]

mov dword ptr es:[numero_de_ligne_dans_pattern],eax
;call num
;
;jmp neofuck
mov bx,es:[effet_D+4]
mov es:[viseur_dans_arrangement_chanson],bx
;
;
;mov ax,es:[nombre_total_de_pattern_chanson] ;
;cmp es:[viseur_dans_arrangement_chanson],ax ;on regarde si on est arrive
;jne charlyrulzz
;mov es:[viseur_dans_arrangement_chanson],0   ;on repart au debut...
;                                             ;de l'arrangement
;charlyrulzz:
;mov bx,ax ;es:[viseur_dans_arrangement_chanson]
;xor eax,eax
xor eax,eax
mov al,es:[arrangement_de_la_chanson+bx]
shl eax,10 ;multiplie par 1024...
         ;on a donc dans ax le viseur_dans_pattern

mov ebx,es:[numero_de_ligne_dans_pattern]
shl ebx,4   ;*16 (4 voix pas lignes*4 octets.)
add eax,ebx

mov es:[viseur_dans_pattern],eax
;call num
neofuck:
mov word ptr es:[effet_D],0  ;on arrete l'effet...

;jmp fin_proc_effet2
blur_house:

;************** EFFET E6:LOOP
;
cmp es:[effet_E6],1
jne blur_house23

mov eax,es:[FXLOOP2]
mov es:[numero_de_ligne_dans_pattern],eax

xor ebx,ebx
mov bx,es:[viseur_dans_arrangement_chanson]

xor eax,eax
mov al,es:[arrangement_de_la_chanson+bx]

cmp es:[nombre_de_voix],4
jne pourkoiestiltellementmechant
shl eax,10 ;multiplie par 1024... ;4 VOIX...
           ;on a donc dans ax le viseur_dans_pattern
pourkoiestiltellementmechant:

cmp es:[nombre_de_voix],8
jne pourkoiestiltellementmechante
shl eax,11 ;multiplie par 2048... ;8 VOIX...
           ;on a donc dans ax le viseur_dans_pattern
pourkoiestiltellementmechante:

mov ebx,es:[numero_de_ligne_dans_pattern]

cmp es:[nombre_de_voix],4
jne rpourkoiestiltellementmechant
shl ebx,4 ;*16
rpourkoiestiltellementmechant:

cmp es:[nombre_de_voix],8
jne rpourkoiestiltellementmechant2
shl ebx,5 ;*32
rpourkoiestiltellementmechant2:

add eax,ebx

mov es:[viseur_dans_pattern],eax

mov es:[effet_E6],0
blur_house23:

fin_proc_effet2:
pop eax
ret
effets2 endp


calc_new_speed proc near ;pour calculer une nouvelle table de speed.
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
mov di,offset speed_wait2+4
mov si,offset speed_wait+4
mov cx,31
grand_prix:
mov ax,es:[di]
mov dx,es:[di+2]
xor bx,bx
mov bl,es:[bmp_speed]
div bx
;call affsigne
mov es:[si],ax
add di,4
add si,4
dec cx
jnz grand_prix
pop bx dx cx si di ax
ret
calc_new_speed endp

;***************** effets ki durent entre les lignes ***********************
;entr‚ee BP) numero de voix *2

fx_volumeslimingup proc near

mov ax,es:[compteur_effect_entre_ligne+bp]
sub ax,es:[adder_effect_entre_ligne+bp]
jns non_pas_deffet
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax

cmp es:[volume_de_la_voix+bp],63
ja non_le_volume_est_deja_a_fond
inc es:[volume_de_la_voix+bp]
non_le_volume_est_deja_a_fond:
ret

non_pas_deffet:
mov es:[compteur_effect_entre_ligne+bp],ax
ret
fx_volumeslimingup endp

fx_volumeslimingdown proc near

mov ax,es:[compteur_effect_entre_ligne+bp]
sub ax,es:[adder_effect_entre_ligne+bp]
jns non_pas_deffet2
mov ax,es:[compteur_effect_entre_ligne_save]
mov es:[compteur_effect_entre_ligne+bp],ax


cmp es:[volume_de_la_voix+bp],0
je non_le_volume_est_deja_a_zero
dec es:[volume_de_la_voix+bp]
non_le_volume_est_deja_a_zero:

ret
non_pas_deffet2:
mov es:[compteur_effect_entre_ligne+bp],ax
ret

fx_volumeslimingdown endp

;fx_portamento_updown proc near
;
;dec es:[compteur_effect_entre_ligne+bp]
;jz fame
;ret
;fame:
;
;mov ax,es:[compteur_effect_entre_ligne_save]
;mov es:[compteur_effect_entre_ligne+bp],ax
;
;mov di,offset note_joue_par_sample
;add di,bp
;add di,bp
;
;movsx eax,es:[adder_effect_entre_ligne+bp]
;call num
;
;add dword ptr es:[di],eax
;
;cmp dword ptr es:[di],0FFFFH
;jb uhuhuh
;
;cmp dword ptr es:[di],01FFFFH
;ja uhuhuh2
;
;
;mov dword ptr es:[di],0FFFFH ;parre fou!!!
;
;ret
;uhuhuh2:
;sub dword ptr es:[di],eax
;uhuhuh:
;ret
;fx_portamento_updown endp

fx_arpegio proc near

mov si,offset compteur_pour_arpegio2
add si,bp
add si,bp
dec dword ptr es:[si]
jnz frtrertr                    ;pour arreter a la fin...
mov dword ptr es:[si],1         ;avant la prochaine ligne il faut
mov eax,0                       ;se retrouver avec l'ancienne bonne valeur.
jmp rtrtrtrt_onŠfait_ca_a_la_fin

frtrertr:


mov si,offset compteur_pour_arpegio
add si,bp
add si,bp
mov eax,es:[si]

inc es:[compteur_pour_arpegio3+BP]
mov bx,es:[compteur_effect_entre_ligne_save]
cmp es:[compteur_pour_arpegio3+BP],bx ;200
je rreer
ret ;sinon ya rien a changer...
rreer:
inc eax
mov es:[compteur_pour_arpegio3+BP],0


cmp eax,3
jne erreer
mov eax,0
erreer:
mov es:[si],eax
rtrtrtrt_onŠfait_ca_a_la_fin:

cmp eax,1
je aide_memoire2
cmp eax,2
je aide_memoire3
;cmp eax,0
;je aide_memoire1

aide_memoire1:

mov si,offset FREQUENCE_POUR_LES_3_NOTES1
add si,bp
add si,bp
mov eax,es:[si]
mov si,offset note_joue_par_sample
add si,bp
add si,bp
mov es:[si],eax

ret

aide_memoire2:

mov si,offset FREQUENCE_POUR_LES_3_NOTES2
add si,bp
add si,bp
mov eax,es:[si]

mov si,offset note_joue_par_sample
add si,bp
add si,bp
mov es:[si],eax
ret

aide_memoire3:

mov si,offset FREQUENCE_POUR_LES_3_NOTES3
add si,bp
add si,bp
mov eax,es:[si]

mov si,offset note_joue_par_sample
add si,bp
add si,bp
mov es:[si],eax

ret

fx_arpegio endp

nopper proc near

ret
nopper endp

calcule_la_duree_dun_tick proc near ;entree: es=rmd_data
                          ;sortie: ax=nombre d'unite dans speed_compteur
                          ;        qui equivaut a un tick
                          ;utilise par SB et GUS...

push dx bx
mov bx,es:[speed_song]
cmp bx,0
jne rereerreer
inc bx
rereerreer:
mov eax,es:[SPEED_COMPTEUR_SAVE]
xor dx,dx
div bx
pop bx dx
ret
calcule_la_duree_dun_tick endp

vibrato_fx proc near

;VIBRATO_viseur          dw 4 DUP (0) ;viseur dans tablos.
;vibrato_fx_prof         dw 4 DUP (0) ;pour sauvegarde des info sur
;vibrato_fx_speed        dw 4 DUP (0) ;le vibrato en cours!

cmp es:[speed_compteur],1
ja zezeezrzzeezze
mov si,offset SAVE_NOTE_VIBRATO ;....pour tout remettre dans l'ordre a la fin
add si,bp
add si,bp
mov eax,es:[si]

mov si,offset note_joue_par_sample
add si,bp
add si,bp
mov es:[si],eax

ret
zezeezrzzeezze:

dec es:[VIBRATO_compteur+bp]
jz erereerre
ret
erereerre:
mov ax,es:[VIBRATO_compteur_save+bp]
mov es:[VIBRATO_compteur+bp],ax

add es:[VIBRATO_viseur+bp],2
cmp es:[VIBRATO_viseur+bp],128*2
jne maria
mov es:[VIBRATO_viseur+bp],0
maria:
mov bx,es:[VIBRATO_viseur+bp]

mov si,es:[WHAT_VIBRATO]
xor eax,eax
mov ax,es:[si+bx]

or ax,ax
jns pas_de_signe
mov bx,es:[vibrato_fx_prof+bp]
neg ax
mul bx



;on a dans ax la frequence en HZ a rajouter...
;convertion en HZ remdy
shl eax,8-4+1 ;le plus 1 c'est pour ke ca fasse plus d'effet...
xor edx,edx
mov ebx,10000
div ebx
;call num
neg eax   ;mais peut etre ke le parametre de vitesse doit pas etre deplace
          ;a droite
JMP LA_FIN
;-*-*-*-*-*-*-*-*-*-*
pas_de_signe:
mov bx,es:[vibrato_fx_prof+bp]
mul bx
;on a dans ax la frequence en HZ a rajouter...
;convertion en HZ remdy
shl eax,8-4
xor edx,edx
mov ebx,10000
div ebx
;-*-*-*-*-*-*-*-*-*-*
LA_FIN:
mov si,offset note_joue_par_sample
add si,bp
add si,bp
add dword ptr es:[si],eax
jNS rrereretr22
sub dword ptr es:[si],eax
rrereretr22:

ret
vibrato_fx endp

TREMOLO_fx proc near

;cmp es:[speed_compteur],0
;ja zezeezrzzeezzet
;
;mov ax,es:[SAVE_VOLUME_TREMOLO+BP]
;mov es:[volume_de_la_voix+bp],ax
;;mov es:[STOP_TREMOLO+bp],1
;
;ret
;zezeezrzzeezzet:

dec es:[TREMOLO_compteur+bp]
jz erereerret
ret
erereerret:
mov ax,es:[TREMOLO_compteur_save+bp]
mov es:[TREMOLO_compteur+bp],ax

xor eax,eax
add es:[TREMOLO_viseur+bp],2
cmp es:[TREMOLO_viseur+bp],64*2
jne mariat
mov es:[TREMOLO_viseur+bp],0
mariat:
mov bx,es:[TREMOLO_viseur+bp]

mov si,es:[WHAT_TREMOLO]

mov ax,es:[si+bx]
or ax,ax
jns rrereererer
neg ax
mov bx,es:[TREMOLO_fx_prof+bp]

mul bx
shr ax,7  ;normallement ca devrait etre 8
          ;mais peut etre ke le parametre de vitesse doit pas etre deplace
neg ax
add ax,es:[volume_de_la_voix+bp]

cmp ax,64
jb e1234e
mov ax,0;63
e1234e:
mov es:[volume_de_la_voix+bp],ax
ret

rrereererer: ;pas de signe

mov bx,es:[TREMOLO_fx_prof+bp]

mul bx
shr ax,7  ;normallement ca devrait etre 8
         ;mais peut etre ke le parametre de vitesse doit pas etre deplace

add ax,es:[volume_de_la_voix+bp]
cmp ax,64
jb e1234er
mov ax,64
e1234er:
mov es:[volume_de_la_voix+bp],ax
ret

TREMOLO_fx endp


fx_notecut proc near

mov si,offset SPEED_COMPTEUR_TEST_EFFET12
add si,bp
add si,bp
mov ebx,es:[SI]
cmp ebx,es:[SPEED_COMPTEUR]
jne pubrererer
mov es:[volume_de_la_voix+bp],0


pubrererer:
ret
fx_notecut endp

fx_notedelay proc near


;kan cv'est fini on remet comme avant...

mov ebx,es:[SPEED_COMPTEUR]
mov si,offset NOTE_DELAY
add si,bp
add si,bp
cmp es:[si],ebx
jne nonono_faut_encore_attendre

mov ax,es:[NOTE_DELAY2+BP]
mov es:[sample_joue_en_ce_moment+bp],ax

nonono_faut_encore_attendre:

;NOTE_DELAY dd 4 DUP (0)
;NOTE_DELAY2 dw 4 DUP (0) ;pour sauver sample_joue_en_ce_moment dw 4 dup (0)
;                         ;et on met 0 le temps k'on attend.

ret
fx_notedelay endp
;*****************

fx_noteretrig proc near

mov ebx,es:[SPEED_COMPTEUR]
mov si,offset NOTE_RETRIG
add si,bp
add si,bp
cmp es:[si],ebx
jne nonono_faut_encore_attendrer

MOV es:[OFFSET_SAMPLE+bp],0

nonono_faut_encore_attendrer:

ret
fx_noteretrig endp
play_song_sb proc near
mov ax,rmd_data
mov es,ax

cmp es:[first_time],0
jne retertert
call calc_freq_sb
mov es:[first_time],1
retertert:
;.............................. pour la vitesse..............................
call calc_new_speed    ;calcule un nouvelle table de speed.
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


cmp es:[GUS_OR_SB],3
je ea__mode_silence


;call DETECT_SBREG
;call sbgetdspversion
cmp bp,1
je ertertterert
call mettre_haut_parleur_en_marche
ertertterert:

ea__mode_silence:
;.............................

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
mov dx,offset sortie_directe
mov ax,2508h
int 21h
pop ds
POP ES DS
POPA

cli
mov ax,120 ;(1193180/10000)=120
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
play_song_sb endp
stop_song_sb proc near

mov ax,rmd_data
mov es,ax
mov ds,ax


cmp es:[GUS_OR_SB],3
je rea__mode_silenceretrterte

cmp bp,1
je pas_besoiiin
call mettre_haut_parleur_hs
pas_besoiiin:

rea__mode_silenceretrterte:

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
ret
stop_song_sb endp

fx_volumeslimingdown_vibrato proc near

call vibrato_fx

cmp es:[VIBRATO_compteur_save+bp],0FFFFh ;cas particulier il n'y a pas eu
je rttrrtrt                             ;de vibrato avant:on fait rien
call fx_volumeslimingdown
rttrrtrt:
ret
fx_volumeslimingdown_vibrato endp

stop_song proc near ;entree bp=0 mode normal, bp=1 mode sans 'sttttrach'

push es ds di si edx ecx ebx eax


mov ax,rmd_data
mov es,ax

cmp es:[gus_or_sb],3
je rertterertteryrtyuererettter2


cmp es:[gus_or_sb],2
jne rererettter2
rertterertteryrtyuererettter2:
call stop_song_sb
call de_init_mem
call RE_INIT_VARIABLES

pop  eax ebx ecx edx si di ds es
ret
rererettter2:

cmp es:[gus_or_sb],1
jne rererettter2r
call stop_song_GUS
call RE_INIT_VARIABLES

pop  eax ebx ecx edx si di ds es
ret
rererettter2r:
call RE_INIT_VARIABLES
pop  eax ebx ecx edx si di ds es
ret
stop_song endp

play_song proc near ;bp=1 --> sans scraaaatch

push es ds di si edx ecx ebx eax

mov ax,rmd_data
mov es,ax


;--------arrete tous les samples balance ki proviennent des derniers
; sample balanc‚s en fait.
; enfin ki n'ont pas ete trait‚s.

mov di,offset BLOW_WHAT
xor ax,ax
mov cx,3*4
rep stosw
;-

cmp es:[GUS_OR_SB],3
je a__mode_silence


cmp es:[gus_or_sb],2
jne rererettter2t
a__mode_silence:
call play_song_sb
jmp ret_delire_total
rererettter2t:

cmp es:[gus_or_sb],1
jne rererettter2rt
call play_song_GUS
jmp ret_delire_total
rererettter2rt:

ret_delire_total:
pop  eax ebx ecx edx si di ds es
ret
play_song endp


detect proc near
push es ds di si edx ecx ebx eax

;ENTREE:
; BP=0 ;Normal mode
; BP=1 ;No banner mode
;        BP=2 will not use GUS, even if a GUS is found.
;        BP=3 will not use SB, even if a SB is found.

;gus_or_sb DB 0                  ;0=PAS ENCORE DETECTEE
;                                ;1=GUS
;                                ;2=SB

;silence_mode=0 -> no silence mode if no cards found
;silence_mode=1 -> silence mode if no cards found


;------------decryptage du texte + detection joystick
push ax es bx di
mov ax,rmd_data
mov es,ax
cmp es:[first_time2],1 ;seulement une fois au debut
je edeja_fait
mov es:[first_time2],1
xor bl,bl
mov di,offset first_time2+1

xor cl,cl
xor bl,bl
rmerciaurevoir:
cmp dword ptr es:[di],'ØÒ‹'
;db '‹ÒØ'
je edeja_fait

;;-------------------------------------------------------------------
;push bx
;mov bl,al
;add al,cs:[tata3]
;mov cs:[tata3],bl
;pop bx
;;-------------------------------------------------------------------

;push bx
;mov bl,al
;add al,cs:[tata3]
;add cs:[tata3],bl
;pop bx


;add al,cs:[tata2]
;add cs:[tata2],78 ;1



;----------
mov al,es:[di] ;2
sub al,cl ;1
add cl,15 ;1

sub al,bl      ;2
mov bl,al      ;2
;-----------

;
;sub al,bl
;add bl,al

mov es:[di],al
inc di
jmp rmerciaurevoir
edeja_fait:
pop  di bx es ax

call detect_joystick

;------ cas particulier on n'a rien demande en fait !!! ----------------
cmp bp,4
jne always_be3
mov ax,rmd_data
mov ds,ax
mov es,ax

cmp es:[silence_mode],0
je no_silence_mode

mov es:[gus_or_sb],3 ;passe pas en mode silence...

cmp bp,1
je  pas_de_banner_54
mov dx,offset RIEN_DU_TOUT_silence_mode
mov ah,09h
int 21h
pas_de_banner_54:

mov bp,3
jmp exit_sortie

no_silence_mode:


mov es:[gus_or_sb],0 ;passe pas en mode silence...

cmp bp,1
je  pas_de_banner_54r
mov dx,offset RIEN_DU_TOUT_NO_silence_mode
mov ah,09h
int 21h
pas_de_banner_54r:

mov bp,4 ;no silence mode et no cards
jmp exit_sortie


always_be3:
;-----------------------------------------------------------------------

call config_detect

mov ax,rmd_data
mov es,ax
cmp es:[gus_or_sb],0
jne antiphony
cmp bp,2 ;2 si on a dit pas de gus
je  antiphony

call detect_gusreg

;mov es:[gus_or_sb],1
antiphony:

mov ax,rmd_data
mov es,ax
cmp es:[gus_or_sb],0
jne antiphony2
cmp bp,3 ;si on a dit pas de SB
je  antiphony2

call detect_sbREG

antiphony2:

;------ cas particulier on n'a rien TROUVE! en fait !!! ----------------

cmp es:[gus_or_sb],0
jne ertteertertterterrteter
cmp es:[silence_mode],0
je rerterterteert

cmp bp,1
je  pas_de_banner_54reretrert
mov dx,offset RIEN_DU_TOUT_silence_mode
mov ah,09h
int 21h
pas_de_banner_54reretrert:

mov bp,3 ;silence mode activated
mov es:[gus_or_sb],3
jmp exit_sortie
rerterterteert:

cmp bp,1
je  pas_de_banner_54reretrertrtrte
mov dx,offset RIEN_DU_TOUT_NO_silence_mode
mov ah,09h
int 21h
pas_de_banner_54reretrertrtrte:

mov bp,4 ;no silence mode et no cards
mov es:[gus_or_sb],0

jmp exit_sortie
ertteertertterterrteter:
;-----------------------------------------------------------------------

movzx bp,es:[gus_or_sb]

exit_sortie:


cmp bp,1 ;si on a trouve une gus on regarde combien elle a en RAM...
jne retertertr
cmp es:[first_time],0
jne retertertr
call GET_GUs_MEMORY
mov es:[first_time],1

call light_show ;init speciale light show

push bp
xor bp,bp
call gus_Init
pop bp

retertertr:

pop  eax ebx ecx edx si di ds es
ret
detect endp

;             SET BLASTER = A220 I7 D1 T1
;                             ³   ³  ³  ÀÄÄ> 1 = Sound Blaster
;                             ³   ³  ³       2 = Sound Blaster Pro
;                             ³   ³  ³       3 = Sound Blaster 2.0
;                             ³   ³  ³       4 = Sound Blaster 16
;                             ³   ³  ÀÄÄÄÄÄ> DMA
;                             ³   ÀÄÄÄÄÄÄÄÄ> Irq
;                             ÀÄÄÄÄÄÄÄÄÄÄÄÄ> Port
;     þ Gravis UltraSound :
;
;             SET ULTRASND=220,1,1,7,7
;                             ³  ³   ÀÄÄÄÄÄ> Irq
;                             ³  ÀÄÄÄÄÄÄÄÄÄ> DMA
;

config_detect proc near

mov di,02ch
mov ax,es:[di]
call affsigne
mov ds,ax
mov si,0
mov ax,rmd_data
mov es,ax
mov di,offset header_mod ;ENVIRONMENT
;important: on efface les ' '
mov cx,256
packkkk:
lodsb
cmp al,' '
je erttertt
stosb
erttertt:
loop packkkk
;------- transforme les minuscules en majuscules.
mov di,offset header_mod ;ENVIRONMENT
mov cx,256
packkkkEreff:
mov al,byte ptr es:[di]
cmp al,97
jb nonezezer
cmp al,122
ja nonezezer
sub al,32 ;met majuscules...
mov byte ptr es:[di],al
nonezezer:
inc di
loop packkkkEreff
;---------------

;mov di,offset header_mod ;ENVIRONMENT
;mov cx,256
;ererertrte:
;mov dl,es:[di]
;mov ah,2
;int 21h
;inc di
;loop ererertrte
;--------------

;        BP=2 will not use GUS, even if a GUS is found.
;        BP=3 will not use SB, even if a SB is found.
cmp bp,2
je appalachian

;------------test la GUS
mov ax,rmd_data
mov ds,ax

mov di,offset header_mod ;ENVIRONMENT

mov cx,256

equilibre:
cmp byte ptr es:[di],'U'
jne pas_cette_fois_mon_petit
cmp byte ptr es:[di+1],'L'
jne pas_cette_fois_mon_petit
cmp byte ptr es:[di+2],'T'
jne pas_cette_fois_mon_petit
cmp byte ptr es:[di+3],'R'
jne pas_cette_fois_mon_petit
cmp byte ptr es:[di+4],'A'
jne pas_cette_fois_mon_petit
cmp byte ptr es:[di+5],'S'
jne pas_cette_fois_mon_petit
cmp byte ptr es:[di+6],'N'
jne pas_cette_fois_mon_petit
cmp byte ptr es:[di+7],'D'
jne pas_cette_fois_mon_petit
cmp byte ptr es:[di+8],'='
jne pas_cette_fois_mon_petit
cmp byte ptr es:[di+9],'2'
jne pas_cette_fois_mon_petit

;............................regarde le port...

cmp byte ptr es:[di+10],'1'
jne aphonia
mov es:[gus_base],210h
mov ax,210
mov dx,offset gusmess3
call aff_port
jmp apiary
aphonia:
cmp byte ptr es:[di+10],'2'
jne aphonia2
mov es:[gus_base],220h
mov ax,220
mov dx,offset gusmess3
call aff_port
jmp apiary
aphonia2:
cmp byte ptr es:[di+10],'3'
jne aphonia3
mov es:[gus_base],230h
mov ax,230
mov dx,offset gusmess3
call aff_port
jmp apiary
aphonia3:
cmp byte ptr es:[di+10],'4'
jne aphonia4
mov ax,240
mov dx,offset gusmess3
call aff_port
mov es:[gus_base],240h
jmp apiary
aphonia4:
cmp byte ptr es:[di+10],'5'
jne aphonia5
mov ax,250
mov dx,offset gusmess3
call aff_port
mov es:[gus_base],250h
jmp apiary
aphonia5:
cmp byte ptr es:[di+10],'6'
jne aphonia6
mov ax,260
mov dx,offset gusmess3
call aff_port
mov es:[gus_base],260h
jmp apiary
aphonia6:
cmp byte ptr es:[di+10],'7'
jne aphonia7
mov ax,270
mov dx,offset gusmess3
call aff_port
mov es:[gus_base],270h
jmp apiary
aphonia7:
cmp byte ptr es:[di+10],'8'
jne aphonia8

mov ax,280
mov dx,offset gusmess3
call aff_port
mov es:[gus_base],280h
jmp apiary
aphonia8:
JMP pas_cette_fois_mon_petit
apiary:

; BP=1 ;No banner mode
;cmp bp,1
;je no_banner
;mov dx,offset gusmess3
;mov ah,09
;int 21h
;no_banner:

  mov di,es:[gus_base]
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

ret

pas_cette_fois_mon_petit:
inc di
dec cx
jnz equilibre

appalachian:
;................................test pour la sb now...

;        BP=2 will not use GUS, even if a GUS is found.
;        BP=3 will not use SB, even if a SB is found.
cmp bp,3
je  kosta

mov ax,rmd_data
mov ds,ax

mov di,offset header_mod ;ENVIRONMENT

mov cx,256

tequilibre:
;BLASTER = A220

cmp byte ptr es:[di],'B'
jne tpas_cette_fois_mon_petit
cmp byte ptr es:[di+1],'L'
jne tpas_cette_fois_mon_petit
cmp byte ptr es:[di+2],'A'
jne tpas_cette_fois_mon_petit
cmp byte ptr es:[di+3],'S'
jne tpas_cette_fois_mon_petit
cmp byte ptr es:[di+4],'T'
jne tpas_cette_fois_mon_petit
cmp byte ptr es:[di+5],'E'
jne tpas_cette_fois_mon_petit
cmp byte ptr es:[di+6],'R'
jne tpas_cette_fois_mon_petit
cmp byte ptr es:[di+7],'='
jne tpas_cette_fois_mon_petit
cmp byte ptr es:[di+8],'A'
jne tpas_cette_fois_mon_petit
cmp byte ptr es:[di+9],'2'
jne tpas_cette_fois_mon_petit

;............................regarde le port...

cmp byte ptr es:[di+10],'1'
jne taphonia
mov es:[dsp_adr],210h
mov dx,offset sbmess3
mov ax,210
call aff_port
jmp tapiary
taphonia:
cmp byte ptr es:[di+10],'2'
jne taphonia2
mov es:[dsp_adr],220h
mov dx,offset sbmess3
mov ax,220
call aff_port

jmp tapiary
taphonia2:
cmp byte ptr es:[di+10],'3'
jne taphonia3
mov es:[dsp_adr],230h
mov dx,offset sbmess3
mov ax,230
call aff_port

jmp tapiary
taphonia3:
cmp byte ptr es:[di+10],'4'
jne taphonia4
mov es:[dsp_adr],240h
mov dx,offset sbmess3
mov ax,240
call aff_port

jmp tapiary
taphonia4:
cmp byte ptr es:[di+10],'5'
jne taphonia5
mov es:[dsp_adr],250h
mov dx,offset sbmess3
mov ax,250
call aff_port

jmp tapiary
taphonia5:
cmp byte ptr es:[di+10],'6'
jne taphonia6
mov es:[dsp_adr],260h
mov dx,offset sbmess3
mov ax,260
call aff_port

jmp tapiary
taphonia6:
cmp byte ptr es:[di+10],'7'
jne taphonia7
mov es:[dsp_adr],270h
mov dx,offset sbmess3
mov ax,270
call aff_port

jmp tapiary
taphonia7:
cmp byte ptr es:[di+10],'8'
jne taphonia8
mov es:[dsp_adr],280h
mov dx,offset sbmess3
mov ax,280
call aff_port

jmp tapiary
taphonia8:
JMP tpas_cette_fois_mon_petit
tapiary:

  mov es:[gus_or_sb],2

;cmp bp,1
;je no_banner2
;
;mov dx,offset sbmess3
;mov ah,09
;int 21h
;
;no_banner2:

ret

tpas_cette_fois_mon_petit:

inc di
dec cx
jnz tequilibre

kosta:

ret
config_detect endp

LOAD_BONUS_SAMPLE PROC NEAR
;ECX: OFFSET
;! dans aX NUMERO DU SAMPLE *4 !
;MOV BP,32*4

push es ds di si edx ecx ebx eax

push ax
mov ax,rmd_data
mov es,ax
pop ax

cmp es:[gus_or_sb],1
je cuneguskona

cmp es:[gus_or_sb],2
je cunesbkona

mov bp,5 ;no soundcard detected before
jmp kinderdelice
cuneguskona:

shl ax,2
mov bp,ax ;!!!!

;header_IFF DB 78   DUP (?) ;on charge ici le header de l'IFF en cours de

;...ouverture fichier....
mov ax,rmd_data
mov es,ax
mov ds,ax

mov dx,offset iff_file_name
mov ah,03dh ;ouverture du fichier avec handle.
mov al,00h  ;ouverture du fichier pour lecture.
int 21h
jc erreur_file_macarena ;saute si carry=1
;dans ax:handle fichier

mov word ptr es:[handle_IFF_file],ax

;... deplacement a l'interieur du fichier IFF
mov word ptr bx,es:[handle_IFF_file]
mov ah,042h
mov al,00h              ;debut du fichier

mov dx,cx
shr ecx,16

;dans cx:dx deplacement a l'interieur du fichier

int 21h
jc erreur_file_macarena ;saute si carry=1

;...lecture du fichier...
mov word ptr bx,es:[handle_IFF_file]
mov ah,03fh
mov cx,78               ;pour charger header IFF
mov dx,offset header_IFF
int 21h
jc erreur_file_macarena ;saute si carry=1

mov  ebx,es:[MEMOIRE_GUS_UTILISEE]

mov es:[adresse_debut_sample_gus+bp],ebx
mov es:[adresse_loop_sample_gus+bp],ebx

mov si,offset header_IFF
movzx eax,word ptr es:[si+52] ;longueur du sample
ROL AX,8

push eax ;taille du sample (1)
add  eax,ebx
mov es:[adresse_fin_sample_gus+bp],eax

mov es:[MEMOIRE_GUS_UTILISEE],eax
cmp eax,es:[MEMOIRE_GUS];----------------------------test si assez de mem
jb okyaassezdeplaceE
mov bp,4  ;pas assez de memoire dans la GUS
pop eax
jmp kinderdelice
okyaassezdeplaceE:
;---------------------------------------------------------------

;..............par default on met sample non loopeur...

mov di,bp
shr di,1 ;numero du sample *2

mov word ptr es:[longueur_loop_sample+di],0

;mov ax,rmd_data
;mov es,ax

movzx eax,word ptr es:[si+60] ;REPEAT LENGHT
ROL AX,8

;call affsigne ;longueur loop
cmp ax,0
je pas_loopeur_encore

mov word ptr es:[longueur_loop_sample+di],ax

;dans ax on a la longueur de la loop

movzx ecx,ax

movzx eax,word ptr es:[si+56] ;REPEAT
ROL AX,8
;call num

add es:[adresse_loop_sample_gus+bp],eax

mov eax,es:[adresse_loop_sample_gus+bp]

add eax,ecx   ;debut loop+longueur loop

mov es:[adresse_fin_sample_gus+bp],eax

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
mov word ptr bx,es:[handle_IFF_file]
mov ax,rmd_data
mov ds,ax
mov dx,offset header_mod ;BUFFER_LOAD_GUS
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
mov word ptr bx,es:[handle_IFF_file]
mov ax,rmd_data
mov ds,ax
mov dx,offset header_mod ;BUFFER_LOAD_GUS
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
mov word ptr bx,es:[handle_IFF_file]
mov ah,03eh
int 21h
jc erreur_file_macarena ;saute si carry=1

;mov bp,0 ;succeded
xor bp,bp
jmp kinderdelice
erreur_file_macarena:
mov bp,2 ;error loading file.
jmp kinderdelice
;************ pour la SB ****************************************
cunesbkona:

;shl ax,1
add ax,ax

mov bp,ax ;!!!! dans bp numero du sample * 2

;header_IFF DB 78   DUP (?) ;on charge ici le header de l'IFF en cours de

;...ouverture fichier....
mov ax,rmd_data
mov es,ax
mov ds,ax

mov dx,offset iff_file_name
mov ah,03dh ;ouverture du fichier avec handle.
mov al,00h  ;ouverture du fichier pour lecture.
int 21h
jc erreur_file_macarena ;saute si carry=1
;dans ax:handle fichier

mov word ptr es:[handle_IFF_file],ax

;... deplacement a l'interieur du fichier IFF
mov word ptr bx,es:[handle_IFF_file]
mov ah,042h
mov al,00h              ;debut du fichier

mov dx,cx
shr ecx,16

;dans cx:dx deplacement a l'interieur du fichier

int 21h
jc erreur_file_macarena ;saute si carry=1

;...lecture du fichier...
mov word ptr bx,es:[handle_IFF_file]
mov ah,03fh
mov cx,78               ;pour charger header IFF
mov dx,offset header_IFF
int 21h
jc erreur_file_macarena ;saute si carry=1

;mov  ebx,es:[MEMOIRE_GUS_UTILISEE]
;
;mov es:[adresse_debut_sample_gus+bp],ebx
;mov es:[adresse_loop_sample_gus+bp],ebx

mov si,offset header_IFF
movzx eax,word ptr es:[si+52] ;longueur du sample
ROL AX,8

;longueur_sample      DW 32+32 DUP (0)   ;longueur des 32 instruments.
;                                        ;+32 bonus
;volume_sample        DW 32 DUP (0)      ;volume par defalut des 32 instruments
;depart_loop_sample   DW 32+32 DUP (0)   ;depart loop des 32 instruments
;                                        ;+32 bonus
;longueur_loop_sample DW 32+32 DUP (0)   ;longueur loop des 32 instruments
;                                        ;+32 bonus
;segment_sample       DW 32+32 DUP (0)   ;addresse du segment de chaque sample.

mov es:[longueur_sample+bp],ax

push eax ;taille du sample (1)

;..............par default on met sample non loopeur...

mov word ptr es:[longueur_loop_sample+bp],0

;mov ax,rmd_data
;mov es,ax

movzx eax,word ptr es:[si+60] ;REPEAT LENGHT
ROL AX,8

;call affsigne ;longueur loop
or ax,ax ;si = 0
je dpas_loopeur_encore

mov word ptr es:[longueur_loop_sample+bp],ax

;dans ax on a la longueur de la loop

mov ax,word ptr es:[si+56] ;REPEAT depart du loop
ROL AX,8
;call num

mov es:[depart_loop_sample+bp],ax

dpas_loopeur_encore:

pop ecx ;taille du sample (1)
;.............load le sample pour  SB

;************************** chargement des samples ***************************
;--- alloue la memoire ---
mov ax,rmd_data
mov es,ax
mov ds,ax
mov si,offset longueur_sample
add si,bp
mov di,offset SEGMENT_SAMPLE
add di,bp

mov ax,rmd_data
mov es,ax
mov ds,ax

mov bx,es:[si]
or bx,bx ;si pas de sample...on fait rien...
jz tpas_de_sample_a_loader

push di ;on valide k'il y a un sample...
mov di,offset SEGMENT_SAMPLE_verif
add di,bp
mov word ptr es:[di],1
pop di

shr bx,4

inc bx
jnz trerrere
dec bx
trerrere:

mov ah,48h
int 21h

jnc tdfgfgfghfghhjfghjg ;saute si carry n'est pas a 1...
;----pas assez de memoire pour charger sample---

mov bp,3 ;

jmp kinderdelice

tdfgfgfghfghhjfghjg:
;---------------

;on arrive ici avec dans le segment reserve en AX:0
;donc on sauvergarde ax...

mov es:[di],ax

mov cx,es:[si] ;nombre d'octets a charger...

mov word ptr bx,es:[handle_iff_file]
mov ax,es:[di]
mov ds,ax

push cx ds
xor dx,dx ;offset 0
mov ah,03fh
mov dx,0
int 21h
pop ds cx

;;****** addtionne 128 a chaque sample pour le convertir en sample SB
;push si
;xor si,si
;fideleu:
;add byte ptr ds:[si],128
;inc si
;dec cx
;jnz fideleu
;pop si
;*****************
tpas_de_sample_a_loader:

;****************************************************************************
;...fermeture fichier..
mov word ptr bx,es:[handle_IFF_file]
mov ah,03eh
int 21h
jc erreur_file_macarena ;saute si carry=1

;mov bp,0 ;succeded
xor bp,bp
jmp kinderdelice

;---------
kinderdelice:
pop eax ebx ecx edx si di ds es
ret
LOAD_BONUS_SAMPLE ENDP

de_init_mem proc near
mov ax,rmd_data
mov es,ax
;segment_sample       DW 32+32 DUP (0)   ;addresse du segment de chaque sample.

cmp es:[mode_music],0
je le_voyage_fabuleux_du_professeur_remdy

mov ax,es:[segment_pattern]
push es
mov es,ax
mov ah,49h
int 21h
pop es

cmp es:[GUS_OR_SB],3
je teertertterertertterrteterertertertertert

le_voyage_fabuleux_du_professeur_remdy: ;mode music_fx

xor bx,bx
mov di,offset segment_sample
mov si,offset segment_sample_verif     ;0 mean no sample
                                       ;1 mean one SAMPLE
ergrreerer:
mov ax,es:[di+bx]
cmp word ptr es:[si+bx],0
je  ooohh_wear
mov word ptr es:[si+bx],0
;cmp ax,0
;je ergerertert  ;euh.whai. si le mec a de la memoire reserve es 0: ben tnat pis
push es di bx
mov es,ax
mov ah,49h
int 21h
pop bx di es
;ergerertert:
ooohh_wear:

add bx,2
cmp bx,32*2*2
jne ergrreerer
teertertterertertterrteterertertertertert:
ret
de_init_mem ENDP

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


; affichage du port de la GUS.
;entree:
;mov dx,offset gusmess3
;et le part en decimal dans ax
aff_port proc near

cmp bp,1 ;no banner mode !!!
je zererertt
push ax
mov ah,09
int 21h
pop ax
call affsigne

mov dl,'h'
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
zererertt:
ret
aff_port endp

aff_percent proc near
pusha
push ds es
mov ax,rmd_data
mov es,ax
mov ds,ax

cmp es:[mode_percent],1
jne rtertertrteererterrtef

mov dx,es:[ligne_percent]
xor bx,bx
mov ah,02h
int 10h

mov eax,es:[byte_load_left] ;  dw  ? ;nombre d'octets qu'il reste a charger...
shr eax,8+2

call affsigne

mov ah,02h ;retour a la ligne
mov dl,'K'
int 21h
mov ah,02h ;retour a la ligne
mov dl,'B'
int 21h
mov ah,02h ;retour a la ligne
mov dl,' '
int 21h

;push ds ax dx
;mov ah,02h ;retour a la ligne
;mov dl,13
;int 21h
;mov ax,rmd_data
;mov ds,ax
;mov ah,9
;mov dx,offset loading
;int 21h
;pop dx ax ds
;rtertertrteererterrte:
rtertertrteererterrtef:

pop es ds
popa
ret
aff_percent endp


db 'oOo!!'
