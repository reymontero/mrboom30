touches_pavnum MACRO a,b
local ettetnonononononezrzer
cmp [last_sucker],a
jne ettetnonononononezrzer

xor ax,ax
mov al,b
jmp directos_allegro
ettetnonononononezrzer:
ENDM

;sortie: ebx entree ebp...
direction_du_joueur MACRO a
local trrtertyrtytyrtyrrtyRz
local trrtertyrtytyrtyrrtyRzt
local ytrrtertyrtytyrtyrrtyy
local ytrrtertyrtytyrtyrrtyRy
push eax
  xor ebx,ebx
  mov eax,[touches+ebp]
  and eax,127
  cmp eax,16
  jne trrtertyrtytyrtyrrtyRz
  mov ebx,-1*a
  trrtertyrtytyrtyrrtyRz:
  cmp eax,8
  jne trrtertyrtytyrtyrrtyRzt
  mov ebx,1*a
  trrtertyrtytyrtyrrtyRzt:
  cmp eax,00
  jne ytrrtertyrtytyrtyrrtyy
  mov ebx,32*a
  ytrrtertyrtytyrtyrrtyy:
  cmp eax,24
  jne ytrrtertyrtytyrtyrrtyRy
  mov ebx,-32*a
  ytrrtertyrtytyrtyrrtyRy:
pop eax
ENDM


;esi: endroit ou on pose la bombe...
;edi: infojoueur du dyna

pose_une_bombe MACRO
local vania
local ttyrrtyrtyrtyrtytyrrtyrtyyrtrty
local erertertrteterert
local nononono_onest_en_recordplay
mov byte ptr [esi],1

;utilise Esi par rapport a truc2 pour gauche/droite.
bruit2 11 34 BLOW_WHAT2 ;bruit de kan on pose une bombe

;"hazard" pour ke les bombes soit pas toutes pareille lors du tri bombe
push eax
mov eax,dword ptr [edi] ;nombre de bombes k'on peut encore poser...
and eax,011B
add byte ptr [esi],al
pop eax
;---------------

dec dword ptr [edi] ;nombre de bombes k'on peut encore poser...

;donnee dw 20,20,277,277,150,200,250,280  ;x du dynablaster
;       dw 9,170,9,170,78,98,98,10 ;y du dynablaster

;liste_bombe dd 0 ; nombre de bombes...
;            dd 247 dup (0,0,0,0)
;1er: offset de l'infojoeur
;2eme: nombre de tours avant que ca PETE !!!
;3eme:distance par rapport au debut de truc2
;4eme puissance de la bombe. + retardee ou non

;mov ebx,[liste_bombe]
;shl ebx,4 ;*16

;recherche la premiere place de libre !!!
xor ebx,ebx
ttyrrtyrtyrtyrtytyrrtyrtyyrtrty:
cmp dword ptr [liste_bombe+ebx+4+1*4],0 ;indique emplacement non remplis !!!
je erertertrteterert
add ebx,taille_dune_info_bombe
jmp ttyrrtyrtyrtyrtytyrrtyrtyyrtrty
erertertrteterert:

mov edx,dword ptr [edi+4]        ;r‚cupere la puissance de la bombe dans
                                 ;l'info du joueur...
mov ecx,dword ptr [edi+8]        ;r‚cupere la taille de la meiche de la
                                 ;bombe dans l'info du joueur...

;mov [nomonster],1
  cmp action_replay,0
  jne nononono_onest_en_recordplay
cmp twice,1
jne nononono_onest_en_recordplay
shr ecx,1
nononono_onest_en_recordplay:

mov [liste_bombe+ebx+4+2*4],eax  ;distance par rapport au debut de truc2
mov word ptr [liste_bombe+ebx+4+3*4],dx  ;puissance de la bombe.
;------------------------------------ mouvement de la bombe
;truc_X   db 32*13 dup (0) ;+ ou -...
;truc_Y   db 32*13 dup (0)

mov byte ptr [truc_X+eax],0
mov byte ptr [truc_Y+eax],0

mov word ptr [liste_bombe+ebx+4+4*4],0 ;!!!!!!!!!1 ;adder X automatique.
mov word ptr [liste_bombe+ebx+4+4*4+2],0
mov word ptr [liste_bombe+ebx+4+5*4],0   ;adder X
mov word ptr [liste_bombe+ebx+4+5*4+2],0 ;adder Y

;-------------------------------------------------


push ebx
mov ebx,[infojoueur+ebp] ;uniquement s'il y a droit...
mov edx,dword ptr [ebx+4*4]
pop ebx

;---- maladie de la bonbinette ???
cmp word ptr [maladie+ebp],6 ;malade ??? (en general)
jne vania
mov word ptr [liste_bombe+ebx+4+3*4],1  ;puissance de la bombe.
vania:
;------

mov word ptr [liste_bombe+ebx+4+3*4+2],dx  ;bombe a retardement ou pas ???

mov [liste_bombe+ebx+4+1*4],ecx  ;nombre de tours avant que ca PETE !!!
mov [liste_bombe+ebx+4+0*4],edi  ;offset de l'infojoeur
inc dword ptr [liste_bombe]
mov [tribombe2+ebp],0


ENDM

lapinomb MACRO a
local nooooiii
local nooooiii2
local nan_prend_pas_lombre

cmp word ptr [donnee4+4+ebx],-1
je nooooiii2

push ecx ebx
mov ecx,edi
add ecx,ecx
mov ebx,[kel_ombre]
shr ebx,cl
and ebx,1111B
jz nan_prend_pas_lombre
cmp ebx,3
ja nan_prend_pas_lombre
pop ebx ecx
;ombres      dw 8 dup (0)
;mov ax,[ombres+edi]
;push ecx ebx
;sub ecx
mov a,[ombres+edi]
add a,8*320
jmp nooooiii
nan_prend_pas_lombre:
pop ebx ecx
nooooiii:
;ca c pour lordre daffichage, pour pas ke 2 dyna se croisent de maniere bizarre
add a,bx
add a,bx
add a,bx
nooooiii2:
ENDM


multiple_eax_par_320 MACRO
push edi
push eax
shl   eax,6 ; x 64
mov   edi,eax
pop eax
shl   eax,8 ; x 256
add   edi,eax
mov eax,edi
pop edi
ENDM

multiple_edx_par_320 MACRO
push edi
push edx
shl   edx,6 ; x 64
mov   edi,edx
pop edx
shl   edx,8 ; x 256
add   edi,edx
mov edx,edi
pop edi
ENDM

poussage MACRO ou,xy_adder,xy_x32
local pas_changement_case
local pas_ca___
local stooppppes
local continue_lme_train_train
local stooppppes_pas
local ya_une_bombe_stope_ou_explose
local ttyrrtyrtyrtyrtytyrrtyrtyyrtrty
local nan_pas_de_bombe_ayant_squatte_entre_temps
local erertertrteterert
local fait_pas_peter
local tantpis
local nanana
local reterertertertertterertert
push ebx eax
xor eax,eax
cmp word ptr [liste_bombe+ebp+4+4*4+xy_adder],ou ;adder X automatique.
jne pas_ca___
;************* _il ya a donc une force ki nous pousser a pousser *********

mov ebx,[liste_bombe+ebp+4+2*4] ;offset dans truc

cmp word ptr [liste_bombe+ebp+4+5*4+xy_adder],0 ; on est au milieu ???
                                                ; changement possible
jne continue_lme_train_train                    ;

cmp byte ptr [truc+ebx+ou*xy_x32],66 ;ya du dur rebondissant a cote ?
jne reterertertertertterertert
neg word ptr [liste_bombe+ebp+4+4*4+xy_adder]
bruit2b 3 45
jmp continue_lme_train_train
reterertertertertterertert:

cmp byte ptr [truc+ebx+ou*xy_x32],0 ;ya du dur a cote ?
jne stooppppes

cmp byte ptr [truc_monstre+ebx],'' ;stoppe si on est sur un dyna/monstre..
je stooppppes
cmp byte ptr [truc2+ebx+ou*xy_x32],0 ;ya du dur a cote ?
je stooppppes_pas
cmp byte ptr [truc2+ebx+ou*xy_x32],5 ;ya du dur a cote ?
jb ya_une_bombe_stope_ou_explose
cmp byte ptr [truc2+ebx+ou*xy_x32],54 ;ya du dur a cote ?
ja stooppppes
stooppppes_pas:

jmp continue_lme_train_train
ya_une_bombe_stope_ou_explose:
;***************** CHOC EVENTUEL AVEC UNE BOMBE 50% ******************************
;---------- recherche la bombe... pour la faire eventuellement peter.
;fait un diiiing (chok entre deux bombes)
;bruit3 6 30 BLOW_WHAT2
push esi ebx
mov esi,ebx
add esi,ou*xy_x32
xor ebx,ebx
ttyrrtyrtyrtyrtytyrrtyrtyyrtrty:
cmp dword ptr [liste_bombe+ebx+4+2*4],esi ;regarde si ya une bombe a cet endroit
je erertertrteterert
add ebx,taille_dune_info_bombe
jmp ttyrrtyrtyrtyrtytyrrtyrtyyrtrty
erertertrteterert:
;fait peter ke si elle bouge...
cmp word ptr [liste_bombe+ebx+4+4*4],0
jne tantpis
cmp word ptr [liste_bombe+ebx+4+4*4+2],0
je fait_pas_peter
tantpis:
mov dword ptr [liste_bombe+ebx+4+1*4],1   ;fait peter la bombe...
mov word ptr  [liste_bombe+ebx+4+4*3+2],0   ;(la rend la bombe normalle. au cas ou)
pop  ebx esi
jmp stooppppes
fait_pas_peter:
;----------------------------------------------------------
pop  ebx esi
;jmp continue_lme_train_train
;-------------------------------
stooppppes:
mov word ptr [liste_bombe+ebp+4+4*4+xy_adder],0 ;adder X automatique.
;bruit2b 2 40
jmp pas_ca___

continue_lme_train_train:
;------------ rien ne peu nous arreter: on pousse.

add word ptr [liste_bombe+ebp+4+5*4+xy_adder],ou ;ax   ;adder X
cmp word ptr [liste_bombe+ebp+4+5*4+xy_adder],8*ou ;on a change de case !!!
jne pas_changement_case

;--- cas particulier des 50% de bombes restantexs non detectees.
; (forcement en deplacement celles la.)
; (peut aussi etre un bonus, une flamme; un espoir. euh non, pas despoir)

cmp [truc2+ebx+ou*xy_x32],0
je nan_pas_de_bombe_ayant_squatte_entre_temps
sub word ptr [liste_bombe+ebp+4+5*4+xy_adder],ou
mov dword ptr [liste_bombe+ebp+4+1*4],1   ;fait peter la bombe...
mov word ptr  [liste_bombe+ebp+4+4*3+2],0   ;(la rend la bombe normalle. au cas ou)
jmp stooppppes ;remonte...
nan_pas_de_bombe_ayant_squatte_entre_temps:

;-------------------------------------------

mov word ptr [liste_bombe+ebp+4+5*4+xy_adder],-8*ou
mov al,byte ptr [truc2+ebx]
mov byte ptr [truc2+ebx],0

add ebx,ou*xy_x32

add dword ptr [liste_bombe+ebp+4+2*4],ou*xy_x32
mov byte ptr [truc2+ebx],al
pas_changement_case:

;validation du nouveau X/Y....
mov ax,word ptr [liste_bombe+ebp+4+5*4+xy_adder]
mov ebx,[liste_bombe+ebp+4+2*4]
mov byte ptr [truc_X+ebx],0
mov byte ptr [truc_Y+ebx],0
mov byte ptr [truc_X+ebx+(13*16*xy_adder)],al
pas_ca___:
pop eax ebx
ENDM

hautbas MACRO setup_viseur,max_s
local rteeeeeeeeeeeeeeeee
local ertttttttttttttttttt
local ertttttttttttttttttt2
local errrrrrrrrrrrrrtyutty
local erttttttttttttttttttr2
local erttttttttttttttttttr
local ertertterertertttttttttttttttttt
local ertertterertertttttttttttttttttt2
;**************** wait pour la fleche vers lehaut
cmp setup_wait3,0
jz rteeeeeeeeeeeeeeeee
dec setup_wait3
jnz ertttttttttttttttttt
rteeeeeeeeeeeeeeeee:

;xor ebx,ebx
;mov bl,[last_sucker]
;mov ax,bx
;call affsigne ;!!

cmp byte ptr [clavier+72],1 ;haut
je ertertterertertttttttttttttttttt
cmp byte ptr [clavier+112],1 ;haut
jne ertttttttttttttttttt
ertertterertertttttttttttttttttt:
inc ebp
mov setup_wait3,setup_wait
cmp setup_viseur,0
je ertttttttttttttttttt2
dec setup_viseur
jmp ertttttttttttttttttt
ertttttttttttttttttt2:
mov setup_viseur,max_s
ertttttttttttttttttt:
;******************** wait pour la fleche vers le bas
cmp setup_wait2,0
je errrrrrrrrrrrrrtyutty
dec setup_wait2
jnz erttttttttttttttttttr2
errrrrrrrrrrrrrtyutty:

cmp byte ptr [clavier+80],1 ;bqs
je ertertterertertttttttttttttttttt2
cmp byte ptr [clavier+113],1 ;bas
jne erttttttttttttttttttr2
ertertterertertttttttttttttttttt2:
inc ebp
mov setup_wait2,setup_wait
cmp setup_viseur,max_s
je erttttttttttttttttttr
inc setup_viseur
jmp erttttttttttttttttttr2
erttttttttttttttttttr:
mov setup_viseur,0
erttttttttttttttttttr2:
ENDM


;viseur esi-1 sur TRUC.
colle_un_bonus MACRO viseur_hazard_bonus,hazard_bonus,correspondance_bonus
local uihuiuihhuiouiohuihuiorteerrty
local pas_recyuiyuiyuioiouuioyuioyuiouioy
local reertertert
local pas_rec
local pas_rect
local drtytyrrtyrteterertert
local drtytyrrtyrteterertert2
;------------- ne pose pas de bonus sur une bombe non explosee
cmp byte ptr [esi-1+32*13],0
je drtytyrrtyrteterertert2
cmp byte ptr [esi-1+32*13],5
jb drtytyrrtyrteterertert
drtytyrrtyrteterertert2:
;--------------------------------------------------

;local rteterertert
;-------------- met ou du vide ou un bonus...
;hazard_bonus db 54,0,54,0,54,0,54,0,0,0,54,0
;viseur_hazard_bonus dd 0
push eax

push esi
inc [viseur_hazard_bonus]
mov esi,offset hazard_bonus
mov eax,[changement] ;renegade
and eax,000000011B
add esi,eax
add esi,[viseur_hazard_bonus]
cmp esi,offset viseur_hazard_bonus
jb reertertert
mov [viseur_hazard_bonus],0
mov esi,offset hazard_bonus
mov eax,[changement]
and eax,000000011B
add esi,eax
reertertert:
mov al,[esi]
pop esi

;or al,al
;jz rteterertert

push ebx
xor ebx,ebx
mov bl,al
mov al,[correspondance_bonus+ebx]

;********************** TRAFFIC POUR PLAY !!! *********
cmp action_replay,2 ;play
jne pas_rect
push ebx
;STRUTURE DE REC:
xor ebx,ebx
mov bl,byte ptr fs:[1966080+TAILLE_HEADER_REC]
mov byte ptr al,fs:[1966080+TAILLE_HEADER_REC+ebx]
inc byte ptr fs:[1966080+TAILLE_HEADER_REC]
pop ebx
pas_rect:
;**************************************************

;******* INTERDICTION DE BONUS TEMPS POUR LE MODE REC *********
cmp action_replay,1 ;rec
jne pas_recyuiyuiyuioiouuioyuioyuiouioy
cmp al,134
jne pas_recyuiyuiyuioiouuioyuioyuiouioy
xor al,al
pas_recyuiyuiyuioiouuioyuioyuiouioy:
;---------------------------------------------------------------

;;cas particulier: terrain6 plus apres lapocalypse, pas de bonus
cmp special_nivo_6,0
jz uihuiuihhuiouiohuihuiorteerrty
xor al,al
uihuiuihhuiouiohuihuiorteerrty:
;---------------

mov byte ptr [esi-1+32*13],al ;54
pop ebx

;********************** SAUVEGARDE BONUS POUR REC *********
cmp action_replay,1 ;rec
jne pas_rec
push ebx
;STRUTURE DE REC:
xor ebx,ebx
mov bl,byte ptr fs:[1966080+64000+TAILLE_HEADER_REC]
mov byte ptr fs:[1966080+64000+TAILLE_HEADER_REC+ebx],al
inc byte ptr fs:[1966080+64000+TAILLE_HEADER_REC]
pop ebx
pas_rec:
;**************************************************

pop eax
drtytyrrtyrteterertert:
ENDM


cheat MACRO coco,jesus,speed_raster,valeur
local yureertrteertert
local yureertrteertert2
;-- pour le spoeed mode ---
mov ebx,[coco]
cmp al,byte ptr [jesus+ebx]
jne yureertrteertert
inc ebx
inc coco
cmp byte ptr [jesus+ebx],'Û'
jne yureertrteertert2
mov [speed_raster],valeur
;jmp yureertrteertert2
yureertrteertert:
mov [coco],0
yureertrteertert2:
;---
ENDM




resistance MACRO saut,monstre_ou_pas
local finito_baby
local erterdynanormalito
local passaut2
cmp [invinsible+ebp],0 ;flamme ? sauf si on est en invinsible apres un coups...
jne saut                  ;‚vite la mort de justesse...

cmp [lapipipino+ebp],0 ;lapin ?
je erterdynanormalito
cmp [lapipipino2+ebp],0 ;lapin qui saute ?
je passaut2
cmp [lapipipino5+ebp],0 ;hauteur du saut
jne saut
passaut2:


;tue le lapin...
bruit3 12 34 BLOW_WHAT2 ;bruit de kan on pose une bombe

mov [lapipipino2+ebp],3 ;mort du lapin
mov [lapipipino3+ebp],duree_mort
erterdynanormalito:

;--- rend normalles toutes ses bombes
;--- qui etaient a retardement. et retire son pouvoir..
push ebx
mov ebx,[infojoueur+ebp]
mov dword ptr [ebx+4*4],0 ;retire pouvoir
call nike_toutes_ses_bombes
pop ebx
;---------------------

;**d‚cr‚mente le nombre de coups k'on peut prendre ***
cmp [nombre_de_coups+ebp],0
je finito_baby
dec dword ptr  [nombre_de_coups+ebp]
mov [invinsible+ebp],invisibilite_totale
;---- retire le pouvoir de pousser (and car on le retire pas pour les monstres)
and dword ptr [pousseur+ebp],monstre_ou_pas
;retire les patins a roulette
mov dword ptr [patineur+ebp],0
;retire le tribombe
mov dword ptr [tribombe+ebp],0

jmp saut
finito_baby:
ENDM


aff_spt666 MACRO lignes,colonnes
local yuertertertrteerti
local yuconcerti
local yuertertertrtei
mov ecx,lignes
yuertertertrteerti:
mov ebx,colonnes
yuconcerti:
movsb
dec ebx
jnz yuconcerti
add edi,320-colonnes
add esi,320-colonnes
dec ecx
jnz yuertertertrteerti
ENDM


aff_spt MACRO lignes,colonnes
local yuertertertrteerti
local yuconcerti
local yuertertertrtei
mov ecx,lignes
yuertertertrteerti:
mov ebx,colonnes
yuconcerti:
lodsb
or al,al
jz yuertertertrtei
mov byte ptr es:[edi],al
yuertertertrtei:
inc edi
dec ebx
jnz yuconcerti
add edi,320-colonnes
add esi,320-colonnes
dec ecx
jnz yuertertertrteerti
ENDM

aff_spt2 MACRO lignes,colonnes,a
local yuertertertrteerti
local yuconcerti
local yuertertertrteiE
local yuertertertrtei
local rtrtyrtyrtyrtyrtyrtyrty
mov ecx,lignes
yuertertertrteerti:
mov ebx,colonnes
yuconcerti:
lodsb
or al,al
jz rtrtyrtyrtyrtyrtyrtyrty
cmp al,1
je yuertertertrtei
cmp al,156
je yuertertertrteiE

mov byte ptr es:[edi],al
jmp rtrtyrtyrtyrtyrtyrtyrty
yuertertertrteiE:
push ebx
xor ebx,ebx
mov bl,es:[edi]
mov al,es:[couleurssss+ebx]
add al,93 ;!
mov byte ptr es:[edi],al
pop ebx
jmp rtrtyrtyrtyrtyrtyrtyrty
yuertertertrtei:
push ebx
xor ebx,ebx
mov bl,es:[edi]
mov al,es:[couleurssss+ebx]
add al,a
mov byte ptr es:[edi],al
pop ebx
rtrtyrtyrtyrtyrtyrtyrty:
inc edi
dec ebx
jnz yuconcerti
add edi,320-colonnes
add esi,320-colonnes
dec ecx
jnz yuertertertrteerti
ENDM

return_presse MACRO e,machin
local retertertertertetrtrertertert
local erterertertert
PUSHALL
mov ecx,[nb_ordy_connected]
inc ecx
;nombre d'ordy en tout...
mov esi,offset total_t
;control_joueur dd 8 dup (?) ;-1,6,32,32+6,-1,-1,-1,-1

retertertertertetrtrertertert:
cmp byte ptr [esi+7*8],1
jne erterertertert
cmp [nombre_de_dyna],2 ;uniquement s'il y a au moins 2 dyna...
jb erterertertert
mov byte ptr [e],machin
erterertertert:

add esi,64
dec ecx
jnz retertertertertetrtrertertert
POPALL
ENDM

touche_presse MACRO e,machin
local retertertertertetrtrertertert
local erterertertert
PUSHALL
mov ecx,[nb_ordy_connected]
inc ecx
;nombre d'ordy en tout...
mov esi,offset total_t
;control_joueur dd 8 dup (?) ;-1,6,32,32+6,-1,-1,-1,-1

retertertertertetrtrertertert:
cmp byte ptr [esi+7*8+2],1
jne erterertertert
mov [e],machin
erterertertert:
add esi,64
dec ecx
jnz retertertertertetrtrertertert
POPALL
ENDM


touche_presseque_master MACRO e,machin
local erterertertert
PUSHALL

cmp [master],0
jne erterertertert
cmp byte ptr [total_t+7*8+2],1
jne erterertertert
mov byte ptr [e],machin
erterertertert:

POPALL
ENDM


bonus_tete MACRO a ;active un bonus... quand on marche dessus
local yertterertertertert
push eax
cmp byte ptr [esi],a
jb yertterertertertert
cmp byte ptr [esi],a+10 ;54+10
jnb yertterertertertert
bruit2 1 40
;bruit 1 40
mov byte ptr [esi],0

mov eax,[changement]
and eax,01111B
mov al,[hazard_maladie+eax]
and ax,255
mov word ptr [maladie+ebp],ax ;ax ;4: touches invers‚e...
                             ;3 : la chiasse...
                             ;2 : maladie de la lenteur...
                             ;1 : maladie du speeD.
                             ;5 : maladie de la constipation
                             ;6 : maladie de la bonbinette

mov word ptr [maladie+ebp+2],duree_conta ;500 ; dd 8 dup (?)
;mov esi,[infojoueur+ebp]
;cmp byte ptr [esi+c],b ;bombe_max
;je yertterertertertert
;inc byte ptr [esi+c]
yertterertertertert:
pop eax
ENDM

bruit MACRO a,b,t
local op
;a:panning 0 droite
;
;last_voice dd 0
;           ;derniere voix utilis‚e (*2)
;
;
;0.1.2.3.4.5.6 7
;8.9.0.1.2.3.4.5

;a: sample, b:note

push ebp eax
mov al,a
or  al,01110000B
mov ebp,[last_voice]
add [last_voice],2
cmp [last_voice],14*2
jne op
mov [last_voice],0
op:


mov byte ptr [t+ebp],al   ;al ;073h ;4 bits:panning, 4 bits: sample
                               ;0 droite. ici. F left

mov eax,[changement]
and eax,011B
add eax,b
mov byte ptr [t+ebp+1],al ;note
pop eax ebp
ENDM

bruit3 MACRO a,b,t ; au milieu
local op
;a:panning 0 droite
;
;last_voice dd 0
;           ;derniere voix utilis‚e (*2)
;
;
;0.1.2.3.4.5.6 7
;8.9.0.1.2.3.4.5

;a: sample, b:note

push ebp eax
mov al,a
or  al,01110000B
mov ebp,[last_voice]
add [last_voice],2
cmp [last_voice],14*2
jne op
mov [last_voice],0
op:


mov byte ptr [t+ebp],al   ;al ;073h ;4 bits:panning, 4 bits: sample
                               ;0 droite. ici. F left

;,mov eax,[changement]
;and eax,011B
mov eax,b
mov byte ptr [t+ebp+1],al ;note
pop eax ebp
ENDM

bruit3b MACRO a,b,t ; au milieu
local op
;a:panning 0 droite
;
;last_voice dd 0
;           ;derniere voix utilis‚e (*2)
;
;
;0.1.2.3.4.5.6 7
;8.9.0.1.2.3.4.5

;a: sample, b:note

push ebp eax
mov al,a
or  al,01110000B
mov ebp,[last_voice]
add [last_voice],2
cmp [last_voice],14*2
jne op
mov [last_voice],0
op:


mov byte ptr [t+ebp],al   ;al ;073h ;4 bits:panning, 4 bits: sample
                               ;0 droite. ici. F left

mov eax,[changement]
and eax,011B
add eax,b
mov byte ptr [t+ebp+1],al ;note
pop eax ebp
ENDM



bruit2 MACRO a,b
local op

;a: sample, b:note

push ebp eax esi  ebx
mov al,a
;

;---------------
sub esi,offset truc2
and esi,011111B
;0 a 32.
mov bl,byte ptr [panning2+esi]
shl ebx,4
;------------ fait exploser la bombe -------------------------------------
or  al,bl ;apnning

mov ebp,[last_voice]
add [last_voice],2
cmp [last_voice],14*2
jne op
mov [last_voice],0
op:

mov byte ptr [BLOW_WHAT2+ebp],al   ;al ;073h ;4 bits:panning, 4 bits: sample
                               ;0 droite. ici. F left
mov eax,[changement]
and eax,010B
add eax,b
;mov eax,b ;!!
mov byte ptr [BLOW_WHAT2+ebp+1],al ;note
pop ebx esi eax ebp
ENDM

bruit2b MACRO a,b
local op

;a: sample, b:note

push ebp eax esi  ebx

;
;on recup le panning sur ebx
and ebx,011111B
mov bl,byte ptr [panning2+ebx]

mov al,a
shl ebx,4
;------------ fait exploser la bombe -------------------------------------
or  al,bl ;apnning

mov ebp,[last_voice]
add [last_voice],2
cmp [last_voice],14*2
jne op
mov [last_voice],0
op:

mov byte ptr [BLOW_WHAT2+ebp],al   ;al ;073h ;4 bits:panning, 4 bits: sample
                               ;0 droite. ici. F left
mov eax,[changement]
and eax,010B
add eax,b
;mov eax,b ;!!
mov byte ptr [BLOW_WHAT2+ebp+1],al ;note
pop ebx esi eax ebp
ENDM


SOUND_FAC MACRO a
PUSHALL
mov ax,ds
mov es,ax
lea edi,a
mov ecx,14
xor ax,ax
rep stosw
POPALL
ENDM

SOUND MACRO
PUSHALL
mov ax,ds
mov es,ax
lea edi,BLOW_WHAT
lea esi,BLOW_WHAT2
mov ecx,14
rep movsw
POPALL
ENDM

SOUND_menu MACRO
PUSHALL
mov ax,ds
mov es,ax
lea edi,BLOW_WHAT
lea esi,fx
mov ecx,14
rep movsw
POPALL
ENDM

crocro macro
local eretretrertertert
lodsb
or al,al
jz eretretrertertert
mov es:[edi],bl
eretretrertertert:
inc edi
ENDM

copie macro a
PUSHALL
mov ax,ds
mov es,ax
mov ax,fs
mov ds,ax
mov ecx,a
rep movsd
POPALL
ENDM


aff_bombe MACRO
local ertertrteertrterte
local zerertertter
local retertterert
mov dx,16
ertertrteertrterte:
mov bx,16
zerertertter:
lodsb
or al,al
jz retertterert
mov es:[edi],al
retertterert:
inc edi
dec bx
jnz zerertertter
add edi,320-16
add esi,320-16
dec dx
jnz ertertrteertrterte
ENDM



;aff_omb  MACRO lignes,colonnes
;local yuertertertrteerti
;local yuconcerti
;local yuertertertrteiE
;local rtrtyrtyrtyrtyrtyrtyrty
;local trrttytyrtyrrtyyrtrtytyryrt2
;local trrttytyrtyrrtyyrtrtytyryrt
;;local yuertertertrtei
;pushall
;mov ecx,8
;yuertertertrteerti:
;mov ebx,16
;yuconcerti:
;lodsb
;or al,al
;jz rtrtyrtyrtyrtyrtyrtyrty
;cmp al,36
;je yuertertertrteiE
;;cmp al,156
;;je yuertertertrteiE
;
;mov byte ptr es:[edi],al
;jmp rtrtyrtyrtyrtyrtyrtyrty
;yuertertertrteiE:
;mov al,es:[edi]
;cmp al,32
;jb trrttytyrtyrrtyyrtrtytyryrt
;sub al,32
;trrttytyrtyrrtyyrtrtytyryrt:
;cmp al,64
;jb trrttytyrtyrrtyyrtrtytyryrt2
;sub al,32
;trrttytyrtyrrtyyrtrtytyryrt2:
;
;mov byte ptr es:[edi],al
;rtrtyrtyrtyrtyrtyrtyrty:
;inc edi
;dec ebx
;jnz yuconcerti
;add edi,320-16
;add esi,320-16
;dec ecx
;jnz yuertertertrteerti
;popall
;ENDM

aff_omb  MACRO
local ertertrteertrterte
local zerertertter
local retertterert
mov dx,8
ertertrteertrterte:
mov bx,16
zerertertter:
lodsb
or al,al
jz retertterert
mov es:[edi],al
retertterert:
inc edi
dec bx
jnz zerertertter
add edi,320-16
add esi,320-16
dec dx
jnz ertertrteertrterte
ENDM

aff_mortlapin  MACRO
local ertertrteertrterte
local zerertertter
local retertterert
mov dx,32
ertertrteertrterte:
mov bx,32
zerertertter:
lodsb
or al,al
jz retertterert
mov es:[edi],al
retertterert:
inc edi
dec bx
jnz zerertertter
add edi,320-32
add esi,320-32
dec dx
jnz ertertrteertrterte
ENDM

aff_bombe2 MACRO
local ertertrteertrterte
local zerertertter
local retertterert
sub edi,11*320+6
mov dx,27
ertertrteertrterte:
mov bx,31
zerertertter:
lodsb
or al,al
jz retertterert
mov es:[edi],al
retertterert:
inc edi
dec bx
jnz zerertertter
add edi,320-31
add esi,320-31
dec dx
jnz ertertrteertrterte
ENDM

aff_oeuf MACRO
local ertertrteertrterte
local zerertertter
local retertterert
sub edi,3
mov dx,16
ertertrteertrterte:
mov bx,22
zerertertter:
lodsb
or al,al
jz retertterert
mov es:[edi],al
retertterert:
inc edi
dec bx
jnz zerertertter
add edi,320-22
add esi,320-22
dec dx
jnz ertertrteertrterte
ENDM



;b: max...
bonus_ MACRO a,b,c ;active un bonus... quand on marche dessus
local yertterertertertert
local FIREUERTKjertjertkljertertertertter2
local FIREUERTKjertjertkljertertertertter

push esi
cmp byte ptr [esi],a
jb yertterertertertert
cmp byte ptr [esi],a+10 ;54+10
jnb yertterertertertert

mov byte ptr [esi],0
bruit2 1 40
mov esi,[infojoueur+ebp]
cmp byte ptr [esi+c],b ;bombe_max
je FIREUERTKjertjertkljertertertertter2
 ;yertterertertertert
inc byte ptr [esi+c]

;------------ tricheur notoire
cmp byte ptr [esi+c],b ;bombe_max
je yertterertertertert
push esi
mov esi,offset nick_t
add esi,[control_joueur+ebp]
cmp byte ptr [esi+4],''
pop esi
jne yertterertertertert
inc byte ptr [esi+c]
;--------------------------------------------------
yertterertertertert:
pop esi
jmp FIREUERTKjertjertkljertertertertter
FIREUERTKjertjertkljertertertertter2:
pop esi
mov byte ptr [esi],194  ;degage le bonus
bruit2 4 40
FIREUERTKjertjertkljertertertertter:

ENDM

bonus_2 MACRO a,b,c  ;active un bonus... quand on marche dessus
local yertterertertertert

cmp byte ptr [esi],a
jb yertterertertertert
cmp byte ptr [esi],a+10 ;54+10
jnb yertterertertertert
bruit2 1 40
;mov byte ptr [esi],0
;mov esi,[infojoueur+ebp]
;cmp byte ptr [esi+c],b ;bombe_max
;je yertterertertertert
;inc byte ptr [esi+c]
mov byte ptr [esi],0
add [c+ebp],b

;------------ tricheur notoire
push esi
mov esi,offset nick_t
add esi,[control_joueur+ebp]
cmp byte ptr [esi+4],''
pop esi
jne yertterertertertert
add [c+ebp],b
;--------------------------------------------------

yertterertertertert:
ENDM

bonus_3 MACRO a,b,c  ;active un bonus... quand on marche dessus
local yertterertertertert
local rteelmkklmertklmertklmertertterter
                        ;cas particulier,bon kon peut deja avoir
cmp byte ptr [esi],a
jb yertterertertertert
cmp byte ptr [esi],a+10 ;54+10
jnb yertterertertertert
cmp [c+ebp],b
jne rteelmkklmertklmertklmertertterter
mov byte ptr [esi],194  ;degage le bonus
bruit2 4 40
jmp yertterertertertert
rteelmkklmertklmertklmertertterter:
bruit2 1 40
mov byte ptr [esi],0
mov [c+ebp],b
yertterertertertert:
ENDM

bonus_5 MACRO a  ;active un bonus... quand on marche dessus
local yertterertertertert
local rteelmkklmertklmertklmertertterter
                        ;cas particulier,bon kon peut deja avoir
cmp byte ptr [esi],a
jne yertterertertertert
cmp [lapipipino+ebp],1
jne rteelmkklmertklmertklmertertterter
mov byte ptr [esi],194  ;degage le bonus
bruit2 4 40
jmp yertterertertertert
rteelmkklmertklmertklmertertterter:
;ke kan on est au milieu
au_milieu_x_et_y yertterertertertert
;---------
bruit2 1 40
mov byte ptr [esi],0
;mov byte ptr [esi],194  ;degage le bonus
;mov [lapipipino3+ebp],duree_saut
;mov [lapipipino2+ebp],1
mov [lapipipino6+ebp],1
inc [nombre_de_coups+ebp]

;saut de lapin le lapin...
bruit3 10 30 BLOW_WHAT2 ;bruit kan 1 lapin saute

;nombre_de_coups dd 8 dup (?) ;avant la mort...
;clignotement    dd 8 dup (?) ;varie entre 1 et 0  quand invinsible <>0
;                             ;mis a jour par la proc "blanchiment"
;pousseur        dd 8 dup (0)
;patineur        dd 8 dup (?)
;invinsible      dd 8 dup (?) ;invincibilit‚. nombre de vbl restant ... d‚cr‚ment‚e... 0= none...

yertterertertertert:
ENDM


bonus_4 MACRO a         ;pour horloge
local yertterertertertert
local pas_zeroerrterteert
cmp byte ptr [esi],a
jb yertterertertertert
cmp byte ptr [esi],a+10
jnb yertterertertertert
bruit2 1 40
mov byte ptr [esi],0  ;degage le bonus

;cas particulier si le temps = 0
;alors on fait exploser le bonus :)
test temps,000111111111111B
jnz pas_zeroerrterteert
mov byte ptr [esi],194  ;degage le bonus
bruit2 4 40
jmp yertterertertertert
pas_zeroerrterteert:

push ax bx
mov ax,temps ;duree_match ;001100000000B  ;time
mov bx,ax
and bx,0111100000000B
cmp bx,9*256
je non_fait_rien
mov special_clignotement,2
add ax,256 ;ajoute une minute
non_fait_rien:
mov temps,ax
pop bx ax

yertterertertertert:
ENDM

;pour xblast
bonus_6 MACRO a
local yertterertertertert
local pas_zeroerrterteert
cmp byte ptr [esi],a
jb yertterertertertert
cmp byte ptr [esi],a+10
jnb yertterertertertert
bruit2 1 40
mov byte ptr [esi],0  ;degage le bonus
call nike_toutes_les_bombes
yertterertertertert:
ENDM

au_milieu_x_et_y MACRO a
local pas_milieu
local boooh
push ebp eax
shr ebp,1
xor eax,eax
mov ax,word ptr [donnee+nb_dyna*2+ebp] ;recup Y
add ax,14
and ax,00000000000001111B
cmp ax,7
jne pas_milieu
mov ax,word ptr [donnee+ebp] ;recup X
add ax,3
and ax,01111B
cmp ax,7
jne pas_milieu
pop eax ebp
jmp boooh
pas_milieu:
pop eax ebp
jmp a
boooh:
ENDM
au_milieu_y2 MACRO a
local ertzerterta
push ebp eax
shr ebp,1
xor eax,eax
mov ax,word ptr [donnee+nb_dyna*2+ebp] ;recup Y
add ax,14
and ax,00000000000001111B
cmp ax,7
je ertzerterta
pop eax ebp
jmp a
ertzerterta:
pop eax ebp
ENDM

au_milieu_X2 MACRO a
local ertzerterta
push ebp eax
shr ebp,1
xor eax,eax
mov ax,word ptr [donnee+ebp] ;recup X
add ax,3
and ax,01111B
cmp ax,7
je ertzerterta
pop eax ebp
jmp a
ertzerterta:
pop eax ebp
ENDM

au_milieu_y MACRO
local ertzerterta
local erterererererertertYUTYUyutyuu
local retreterertertterertertert
push ebp
shr ebp,1
xor eax,eax
mov ax,word ptr [donnee+nb_dyna*2+ebp] ;recup Y
add ax,14
and ax,00000000000001111B
cmp ax,7
jne ertzerterta
pop ebp
jmp erterererererertertYUTYUyutyuu
ertzerterta:
pop ebp
;---- pas au milieu 2 cas de figure:
;la place est libre en face
cmp ax,7
jb retreterertertterertertert
cmp byte ptr [esi+ebx+32],0
jne erterererererertert2
jmp erterererererertertYUTYUyutyuu
retreterertertterertertert:
cmp byte ptr [esi+ebx-32],0
jne erterererererertert2 ;ne fait pas le saut, transforme en saut vertical
erterererererertertYUTYUyutyuu:
mov [lapipipino2+ebp],2 ;saut directionel
mov [lapipipino7+ebp],17 ;endroit a partir dukel on arrete de bouger
;------------------------------
ENDM

au_milieu_x MACRO
local ertzerterta
local erterererererertertYUTYUyutyuuty222
local retreterertertterertertertty222
push ebp
shr ebp,1
xor eax,eax
mov ax,word ptr [donnee+ebp] ;recup X
add ax,3
and ax,01111B

cmp ax,7
jne ertzerterta
pop ebp
jmp erterererererertertYUTYUyutyuuty222
ertzerterta:
pop ebp
;---- pas au milieu 2 cas de figure:
;la place est libre en face
cmp ax,7
jb retreterertertterertertertty222
cmp byte ptr [esi+ebx+1],0
jne erterererererertert2
jmp erterererererertertYUTYUyutyuuty222
retreterertertterertertertty222:
cmp byte ptr [esi+ebx-1],0
jne erterererererertert2
erterererererertertYUTYUyutyuuty222:
mov [lapipipino2+ebp],2 ;saut directionel
mov [lapipipino7+ebp],17 ;endroit a partir dukel on arrete de bouger
;------------------------------

ENDM


xy_to_offset MACRO
xor eax,eax
shr ebp,1
mov ax,word ptr [donnee+nb_dyna*2+ebp] ;recup Y
add ax,14
;shr ax,4
mov bx,word ptr [donnee+ebp] ;X
and ax,01111111111110000B
add bx,3
shl ax,1 ;*32
;mov esi,offset truc2
shr bx,4
add ax,bx
;add esi,eax
ENDM

explosion MACRO a,b,c
local nononononono_rien_pas_de_bonus
local nononononono_rien_pas_de_bombe
local trrtyyrtrytrtyrytrytrtyyrtyrt
local reerertterertteretr
local ferretertrterteetrrteertrterteretrteretertertrteert
local retertertert
local ttyrrtyrtyrtyrtytyrrtyrtyyrtrty
local erertertrteterert
local erterertrteert
local erterertrteertre
local ytyutyuiityuityu
pushall
;puissance bombe
xor ecx,ecx
mov cx,word ptr [liste_bombe+ebp+4+3*4]
;[eax+4]
;mov eax,[liste_bombe+ebp+4+0*4] ;offset de l'infojoeur

trrtyyrtrytrtyrytrytrtyyrtyrt:
add esi,a ;-32
cmp byte ptr [esi-32*13],0
je reerertterertteretr
cmp byte ptr [esi-32*13],2
jne ferretertrterteetrrteertrterteretrteretertertrteert ;on arrete tout
                                                        ;si ce n'est pas une
                                                        ;Pierre cassable.
mov byte ptr [esi-32*13],3 ;casse la brique...
jmp ferretertrterteetrrteertrterteretrteretertertrteert

reerertterertteretr:
;donc il n'y a rien dans truc... c'est vide...
;3 possibilit‚: vide.. ou une bombe,ou un bonus... visible dans truc 2.
cmp byte ptr [esi],1
jb  nononononono_rien_pas_de_bombe
;1 = bombe... (2,3,4) respirant...
cmp byte ptr [esi],4
ja  nononononono_rien_pas_de_bombe
;---- il y a une bombe il faut la faire exploser...
pushall
sub esi,offset truc2 ;dans esi: distance par rapport a truc2
;liste_bombe dd 0 ; nombre de bombes...
;            dd 247 dup (0,0,0,0)
;1er: offset de l'infojoeur
;2eme: nombre de tours avant que ca PETE !!! ; si = 0 ca veut dire
;                                            ;emplacement libre...
;3eme:distance par rapport au debut de truc2
;4eme puissance de la bombe.

;recherche la bombe a niker...
xor ebx,ebx
ttyrrtyrtyrtyrtytyrrtyrtyyrtrty:
cmp dword ptr [liste_bombe+ebx+4+2*4],esi ;regarde si ya une bombe a cet endroit
je erertertrteterert
add ebx,taille_dune_info_bombe
jmp ttyrrtyrtyrtyrtytyrrtyrtyyrtrty
erertertrteterert:
mov dword ptr [liste_bombe+ebx+4+1*4],1   ;fait peter la bombe...
mov word ptr  [liste_bombe+ebx+4+4*3+2],0 ;(la rend la bombe normalle. au cas ou)
popall
jmp ferretertrterteetrrteertrterteretrteretertertrteert
;----------------------------------------
nononononono_rien_pas_de_bombe:

;----- ya t'il un bonus ??? -----
;54-- bonus bombe... de 54 a 63 (offset 144)
;64-- bonus flamme... de 64 a 73 (offset 144+320*16)
;
;
;194-- explosion d'un bonus... de 194 a 200 (offset 0.172 31x27 +32)

cmp byte ptr [esi],54
jb  nononononono_rien_pas_de_bonus
;1 = bombe... (2,3,4) respirant...
cmp byte ptr [esi],194
ja  nononononono_rien_pas_de_bonus
;-- ya un bonus.. il faut le faire exploseR. --
;194
bruit2 4 40
mov byte ptr [esi],194

jmp ferretertrterteetrrteertrterteretrteretertertrteert
nononononono_rien_pas_de_bonus:
;---------------------------------

cmp byte ptr [esi],0 ;uniquement si ya aucune autre bombe en train d'exploser
                     ; a cet endroit. en ce moment ...
je erterertrteertre

;--- on choisit quelle bombe il faut proviligier...
; si c'est un coeur de bombe.. on le laissE...
;
;5 = centre de bombe. de 5 a 11
cmp byte ptr [esi],5
jb ytyutyuiityuityu
cmp byte ptr [esi],12
;b erterertrteert ;c un coeur.. on arrete...
jb ferretertrterteetrrteertrterteretrteretertertrteert
ytyutyuiityuityu:


erterertrteertre:

mov al,b ;33 ;truc verti...
cmp ecx,1
jne retertertert
mov al,c ;40
retertertert:
mov byte ptr [esi],al
erterertrteert:
dec ecx
jnz trrtyyrtrytrtyrytrytrtyyrtyrt
ferretertrterteetrrteertrterteretrteretertertrteert:
popall
ENDM

bombe MACRO baba
local tetererterertrteerterrteertertrteertrteertertterooi
local terertrteerterto

cmp ax,baba
jnb tetererterertrteerterrteertertrteertrteertertterooi

test dword ptr [changement],0000000000011B
jnz terertrteerterto
inc byte ptr [esi-1]

cmp byte ptr [esi-1],baba
jne terertrteerterto
mov byte ptr [esi-1],0 ;renegade
terertrteerterto:

and eax,011111111B
sub ax,5
shl eax,1
mov ax,word ptr [central_b+eax]
stosw
mov ax,bx
stosw
inc cx
jmp tzererrte

tetererterertrteerterrteertertrteertrteertertterooi:
ENDM


bonus MACRO baba,toto
local tetererterertrteerterrteertertrteertrteertertterooit
local terertrteertertot

cmp ax,baba
jnb tetererterertrteerterrteertertrteertrteertertterooit

test dword ptr [changement],0000000000111B
jnz terertrteertertot
inc byte ptr [esi-1]

cmp byte ptr [esi-1],baba
jne terertrteertertot
mov byte ptr [esi-1],baba-10
terertrteertertot:

and eax,011111111B
sub ax,baba-10
shl eax,4 ;*16
add eax,toto
stosw
mov ax,bx
stosw
inc cx
jmp tzererrte

tetererterertrteerterrteertertrteertrteertertterooit:
ENDM

explo_bonus MACRO baba,toto
local tetererterertrteerterrteertertrteertrteertertterooit
local terertrteertertot

cmp ax,baba
jnb tetererterertrteerterrteertertrteertrteertertterooit

test dword ptr [changement],0000000000111B
jnz terertrteertertot
inc byte ptr [esi-1]

cmp byte ptr [esi-1],baba
jne terertrteertertot
mov byte ptr [esi-1],0 ;baba-8
terertrteertertot:

and eax,011111111B
sub ax,baba-7
shl eax,5 ;*32
add eax,toto
stosw
mov ax,bx
stosw
inc cx
jmp tzererrte

tetererterertrteerterrteertertrteertrteertertterooit:
ENDM

oeuf_bonus MACRO baba,toto
local tetererterertrteerterrteertertrteertrteertertterooit

cmp ax,baba
jne tetererterertrteerterrteertertrteertrteertertterooit

;and eax,011111111B
;sub ax,baba-7
;shl eax,5 ;*32
mov ax,toto
stosw
mov ax,bx
stosw
inc cx
jmp tzererrte

tetererterertrteerterrteertertrteertrteertertterooit:
ENDM

affiche_sprites proc near
pushall
mov ax,ds
mov es,ax

SOUND

;-----------------------------------------------------
cmp terrain,5
jne pas_nuages
cmp [detail],1
je pas_nuages
call gestion_nuage
pas_nuages:
;----- mignon petit oiseau: ceux ki sont derriere nos dynas
cmp [terrain],2
jne retrterterte5rtrze
cmp [detail],1
je retrterterte5rtrze
call noel2
retrterterte5rtrze:
;foot
cmp [terrain],8
jne retrterterte5ertertertreteer
cmp [detail],1
je retrterterte5ertertertreteer
call animfoot_haut
retrterterte5ertertertreteer:
;----------------------------------------------------------



;-------------------- briques ....
;briques dw 3,0,0,0,32,0,64
xor ecx,ecx
mov esi,offset briques
lodsw
or ax,ax
jz reertertertertertterrterte
mov cx,ax
xor ebx,ebx
libere:
xor eax,eax
lodsw
mov bx,ax
lodsw
push esi
push ds
push fs
pop ds

mov esi,1582080

;mov esi,offset buffer3
add esi,ebx


mov edi,offset buffer
add edi,eax

cmp es:[terrain],2 ;pas ce cas particulier avec la neige...
je retterterertertertertertertertertertert
cmp es:[terrain],4 ;pas ce cas particulier avec la foret
je retterterertertertertertertertertertert

or bx,bx
jnz retterterertertertertertertertertertert ;cas particulier:brique en
                                            ;destruction.
retrterterte:
call aff_brique
retterterertertertertertertertertertert2:
pop ds
pop esi
dec cx
jnz libere

reertertertertertterrterte:                             ;


;-------------------- bombes, explosions & bonus

;briques dw 3,0,0,0,32,0,64
xor ecx,ecx
mov esi,offset bombes
lodsw
or ax,ax
jz reertertertertertterrtertet
mov cx,ax

xor ebx,ebx
liberet:
xor eax,eax
lodsw
mov bx,ax
lodsw
push esi
mov esi,1582080+64000*5 ;offset buffer3
add esi,ebx
push ds
  push fs
  pop ds

;---
mov edi,offset buffer
add edi,eax

cmp bx,320*172 ;cas particulier : bonus en explosion... (ne fait rien)
jnb reetrertertert2tyrtyryrtrtyrtyrty
cmp bx,320*16+112 ;cas particulier : oeuf (ne fait rien)
je reetrertertert2tyrtyryrtrtyrtyrty
aff_bombe
reetrertertert2tyrtyryrtrtyrtyrty:
pop ds
pop esi
dec cx
jnz liberet
reertertertertertterrtertet:

;.... bonus oeuf et explosion de bonus (par dessus)
    xor ecx,ecx
    mov esi,offset bombes
    lodsw
    or ax,ax
    jz treertertertertertterrtertet
    mov cx,ax

    xor ebx,ebx
    tliberet:
    xor eax,eax
    lodsw
    mov bx,ax
    lodsw
    push esi
    mov esi,1582080+64000*5 ;offset buffer3
    add esi,ebx
    push ds
    push fs
    pop ds

    ;---
    mov edi,offset buffer
    add edi,eax

    cmp bx,320*172 ;cas particulier : bonus en explosion...
    jnb reetrertertert2
    cmp bx,320*16+112 ;cas particulier : oeuf
    je reetrertertert3
    ;aff_bombe
    reetrertertert:
    pop ds
    pop esi
    dec cx
    jnz tliberet
    treertertertertertterrtertet:

;--- ombres
call aff_ombres
;----- dynablaster

call expere ;affiche le...


;---- arbre de noel
cmp [terrain],2 ;NEIGE !!!
jne retrterterte5ertertert
call noel
retrterterte5ertertert:

;mov edi,896000+384000+46080+64000+64000 ; 128000  ;307200

;1966080+64000*22;foot 7

;---- faux foot (soucoupes volantes)
cmp [terrain],7
jne retrterterte5ertertertrete
;cmp [detail],1
;je retrterterte5ertertertrete
call soucoupe
retrterterte5ertertertrete:

;---- vrai soccer
cmp [terrain],8
jne retrterterte5ertertertretee
call animfoot_oblige
cmp [detail],1
je retrterterte5ertertertretee
call animfoot
retrterterte5ertertertretee:


;mov edi,1966080+64000*24

;---- feuilles de la foret.
cmp [terrain],4 ;foret.
jne retrterterte5ertertertret
cmp [detail],1
je retrterterte5ertertertret
call feuillage
retrterterte5ertertertret:

;---- puzzles sur les crayons
cmp [terrain],6 ;crayon
jne retrterterte5ertertertrett
cmp [detail],1
je retrterterte5ertertertrett
call puzzle2
retrterterte5ertertertrett:

call tv

;cmp action_replay,2
;je retrterterte5ertertertretterrettereererettrr
cmp [detail],1
je retrterterte5ertertertretterrettereererettrr
call bdraw
retrterterte5ertertertretterrettereererettrr:

call horloge

call pauseur

;mov edi,1582080

popall
ret
tv:
;cmp adder_inser_coin,320*67
;je rerteerterterterttrertertertertetrertertert


;AFFICHAGE DU INSER COIN POUR LE MODE DEMO
cmp [detail],1
je rerteerterterterttrertertertertetrertertert
cmp special_on_a_loadee_nivo,2 ;si on load un .mrb pas de truc a droite !!
je rerteerterterterttrertertertertetrertertert
cmp action_replay,2
je ertrteertretterertrteertrte
rerteerterterterttrertertertertetrertertert:
ret
ertrteertretterertrteertrte:
pushall
;
;pause db 0 ;0=nan inverse = oui

;pas de pause en action replay

;cmp action_replay,2
;je pas_en_a
xor ebx,ebx
;mov bl,pauseur2
;mov esi,[offset_pause+ebx]

;offset_ic dd 0,74*2,74
;viseur_ic2 dd 0
;inser_coin dd 256
dec inser_coin
jnz rerteertertyrt
mov inser_coin,32
add viseur_ic2,4
cmp viseur_ic2,4*4
jne rerteertertyrt
mov viseur_ic2,0
rerteertertyrt:

mov ebx,viseur_ic2
mov esi,[offset_ic+ebx]
add esi,adder_inser_coin

;cmp attente_avant_adder_inser_coin,0
;je ertrteertertertertetrertertert
;dec attente_avant_adder_inser_coin
;jmp ertertertertetrertertert
;ertrteertertertertetrertertert:
cmp adder_inser_coin,0 ;320*67
je ertertertertetrertertert
sub adder_inser_coin,320
ertertertertetrertertert:

add esi,1582080+64000*4+74+22*320

push ds
pop es
push fs
pop  ds
;add esi,1582080
mov edi,offset buffer+(0*320+256)
aff_spt2 67 58 0
pas_en_a:
popall
ret
bdraw:
cmp adder_bdraw,50*320
jne reterreer233
;test temps,000111111111111B
;jz zerooo
;
;mov in_the_apocalypse,0
;
;cmp nombre_de_vbl_avant_le_droit_de_poser_bombe,0
;je reterreer233
ret
reterreer233:

;mov esi,1966080+64000*22+32  ;foot 7896000+384000+46080+64000+64000+11

pushall


;bdraw666 db '30'

;--- affichage des chiffres ---
xor eax,eax
mov al,bdraw666
sub al,'0'
shl eax,3
mov esi,eax
pushall
push fs
pop es
push fs
pop  ds
add esi,1966080+64000*22+173+320*33
mov edi,1966080+64000*22+137+320*64
aff_spt666 5 8
popall
xor eax,eax
mov al,bdraw666+1
sub al,'0'
shl eax,3
mov esi,eax
pushall
push fs
pop es
push fs
pop  ds
add esi,1966080+64000*22+173+320*33
mov edi,1966080+64000*22+137+8+320*64
aff_spt666 5 8
popall
;-----------------------

xor esi,esi
mov si,adder_bdraw
add esi,1966080+64000*22+96+41*320

;
;add esi,adder_bdraw

push ds
pop es
push fs
pop  ds
;add esi,1582080
mov edi,offset buffer+8
aff_spt2 43 78 11-31 ;

popall
ret

pauseur:
pushall
;
;pause db 0 ;0=nan inverse = oui

;pas de pause en action replay

cmp pauseur2,0
je pas_en_pause
xor ebx,ebx
mov bl,pauseur2
mov esi,[offset_pause+ebx]

push ds
pop es
push fs
pop  ds
add esi,1582080
mov edi,offset buffer+(136+(100-32)*320)
aff_spt 64 46
pas_en_pause:
popall
ret

animfoot:

;mov edi,1966080+64000*24
pushall

inc dword ptr [compteur_nuage]

push ds
pop es
push fs
pop  ds

;supporter..
;
;ov ebx,es:[compteur_nuage]
;nd ebx,0000000000110000B ; 011111110000B
;hr ebx,4
;ov esi,1966080+64000*24+24+28*320
;or ecx,ecx
;ov cl,es:[offset_supporter+ebx]
;dd esi,ecx
;ov edi,offset buffer+320*2+2
;ff_spt 19 23

;camera 2

mov ebx,es:[compteur_nuage]
and ebx,0000000111110000B ; 011111110000B
shr ebx,4
mov esi,1966080+64000*24
xor ecx,ecx
mov cl,es:[offset_cameraman+ebx]
add esi,ecx
mov edi,offset buffer+140*320
aff_spt 23 21

;camera

mov ebx,es:[compteur_nuage]
add ebx,8+16
and ebx,0000000111110000B ; 011111110000B
shr ebx,4
mov esi,1966080+64000*24
xor ecx,ecx
mov cl,es:[offset_cameraman+ebx]
add esi,ecx
add esi,5*24
mov edi,offset buffer+25*320+299
aff_spt 23 21

; girl

mov ebx,es:[compteur_nuage]
and ebx,00011110000B
shr ebx,3
mov esi,1966080+64000*24
xor ecx,ecx
mov cx,es:[offset_fille+ebx]
add esi,ecx
mov edi,offset buffer+170*320+140+32
aff_spt 30 48

mov ebx,es:[compteur_nuage]
and ebx,00011110000B
shr ebx,3
mov esi,1966080+64000*24
xor ecx,ecx
mov cx,es:[offset_fille+ebx]
add esi,ecx
mov edi,offset buffer+170*320+140+33+32
aff_spt 30 48

mov ebx,es:[compteur_nuage]
and ebx,00011110000B
shr ebx,3
mov esi,1966080+64000*24
xor ecx,ecx
mov cx,es:[offset_fille+ebx]
add esi,ecx
mov edi,offset buffer+170*320+140+66+32
aff_spt 30 48

mov ebx,es:[compteur_nuage]
and ebx,00011110000B
shr ebx,3
mov esi,1966080+64000*24
xor ecx,ecx
mov cx,es:[offset_fille+ebx]
add esi,ecx
mov edi,offset buffer+170*320+10
aff_spt 30 48

mov ebx,es:[compteur_nuage]
and ebx,00011110000B
shr ebx,3
mov esi,1966080+64000*24
xor ecx,ecx
mov cx,es:[offset_fille+ebx]
add esi,ecx
mov edi,offset buffer+170*320+42
aff_spt 30 48


;----
;mov edi,1966080+64000*22

popall
ret

animfoot_haut:

pushall
push ds
pop es
push fs
pop  ds

;supporter..

mov ebx,es:[compteur_nuage]
and ebx,0000000000110000B ; 011111110000B
shr ebx,4
mov esi,1966080+64000*24+24+28*320
xor ecx,ecx
mov cl,es:[offset_supporter+ebx]
add esi,ecx
mov edi,offset buffer+320*2+2
aff_spt 19 23

;supporter..2

mov ebx,es:[compteur_nuage]
add ebx,7
and ebx,0000000000110000B ; 011111110000B
shr ebx,4
mov esi,1966080+64000*24+144+28*320
xor ecx,ecx
mov cl,es:[offset_supporter+ebx]
add esi,ecx
mov edi,offset buffer+320*3+295
aff_spt 19 23


popall
ret


animfoot_oblige:

;mov edi,1966080+64000*24
pushall
push ds
pop es
push fs
pop  ds

mov esi,1966080+64000*22+11+52*320
mov edi,offset buffer+11+52*320
aff_spt 77 12

mov esi,1966080+64000*22+297+52*320
mov edi,offset buffer+297+52*320
aff_spt 77 12

popall
ret


soucoupe:

pushall

inc dword ptr [compteur_nuage]
mov ebx,[compteur_nuage]
xor esi,esi
and ebx,0000000000010000B
jnz mlkjmljktrjklmrejklmtrjklmjklmteerrtrtrrttrrttre
mov esi,232
mlkjmljktrjklmrejklmtrjklmjklmteerrtrtrrttrrttre:

push ds
pop es
push fs
pop  ds
add esi,1966080+64000*22+133*320  ;foot 7896000+384000+46080+64000+64000+11
mov edi,offset buffer+232
aff_spt 36 88

;ov esi,1966080+64000*22+10*320     ;foot 7896000+384000+46080+64000+64000+11
;mov edi,offset buffer+266
;aff_spt 24 54

popall
ret

feuillage:
pushall
push ds
pop es
push fs
pop  ds

mov esi,896000+384000+46080+64000+64000+11
mov edi,offset buffer+11
aff_spt 192 21

mov esi,896000+384000+46080+64000+64000+288
mov edi,offset buffer+288
aff_spt 192 21

mov esi,896000+384000+46080+64000+64000+36-6
mov edi,offset buffer+30
aff_spt 16 263

mov esi,896000+384000+46080+64000+64000+69+166*320
mov edi,offset buffer+69+166*320 ;166
aff_spt 26 206


popall
ret

puzzle2:
pushall
push ds
pop es
push fs
pop  ds


mov esi,1582080+64000*4+51 ;le haut
mov edi,offset buffer+51
aff_spt 16 187


;ov esi,1582080+64000*4+155+6*320
;ov edi,offset buffer+155+6*320
;ff_spt 10 10
;ov esi,1582080+64000*7+217+6*320
;ov edi,offset buffer+217+6*320
;ff_spt 10 10


mov esi,1582080+64000*4+16 ;a gauche
mov edi,offset buffer+16
aff_spt 191 16

;a droite
mov esi,1582080+64000*4+288
mov edi,offset buffer+288
aff_spt 92 17
mov esi,1582080+64000*4+288+107*320
mov edi,offset buffer+288+107*320
aff_spt 85 17



popall

ret


gestion_nuage:
pushall

inc dword ptr [compteur_nuage]

;nuage_sympa dd 72+296*320,0

mov ecx,16
lea esi,nuage_sympa
;-------
teryrtyrtyuuiyuyu:

;add eax,160

mov eax,dword ptr [esi+16]
test dword ptr [compteur_nuage],eax
jnz pas_Šcette_fois
inc dword ptr [esi+4]
pas_Šcette_fois:

mov eax,[esi]

mov ebx,[esi+8]
cmp dword ptr [esi+4],ebx
jb ertrteterertert
mov dword ptr [esi+4],0
ertrteterertert:

cmp dword ptr [esi+4],319
ja ertertrteterertert

sub eax,[esi+4]
mov edx,dword ptr [esi+12]
call un_nuage
ertertrteterertert:


add esi,4*5
dec ecx
jnz teryrtyrtyuuiyuyu

popall
ret
un_nuage:
pushall
;mov esi,offset buffer3
mov esi,1582080+64000*5 ;offset buffer3

add esi,edx
mov edi,offset buffer
add edi,eax
push ds
pop  es
push fs
pop  ds
mov cx,22
tab_oo:
mov bx,48
ma_rtrty:
lodsb
cmp byte ptr es:[edi],103
jne nanananaert
cmp al,131
je nananana
sub al,4
mov byte ptr es:[edi],al
jmp nananana
nanananaert:
cmp byte ptr es:[edi],131
jne nananana
mov byte ptr es:[edi],al
nananana:
inc edi
dec bx
jnz ma_rtrty
add edi,320-48
add esi,320-48
dec cx
jnz tab_oo
popall
ret
noel:
pushall
push ds
pop  es
push fs
pop  ds

mov esi,64000*8+136*320

inc es:[arbre]
test es:[arbre],0000100000B
jz retterertertert
add esi,33
retterertertert:

mov edi,offset buffer+112+31*320

mov ecx,48 ;64
uertertertrteert:
mov ebx,33
uconcert:
lodsb
or al,al
jz uertertertrte
mov byte ptr es:[edi],al
uertertertrte:
inc edi
dec ebx
jnz uconcert
add edi,320-33
add esi,320-33
dec ecx
jnz uertertertrteert

mov esi,64000*8+077*320
mov edi,offset buffer+232+56*320

mov ecx,42
yuertertertrteert:
mov ebx,48
yuconcert:
lodsb
or al,al
jz yuertertertrte
mov byte ptr es:[edi],al
yuertertertrte:
inc edi
dec ebx
jnz yuconcert
add edi,320-48
add esi,320-48
dec ecx
jnz yuertertertrteert

;--- oiseaux

cmp es:[detail],1
je retrterterte5

mov esi,64000*8+040*320+69+16*4
mov ebx,es:[arbre]
and ebx,0000010000B
jz ertertreterterter
add esi,16
ertertreterterter:
mov edi,offset buffer+320*184+50
call oiseau
mov edi,offset buffer+320*184+50+17*1
call oiseau
mov edi,offset buffer+320*184+50+17*4
call oiseau
mov edi,offset buffer+320*184+50+17*9
call oiseau

mov esi,64000*8+040*320+69+16*0
mov ebx,es:[arbre]
and ebx,0000010000B
jz iertertreterterter
add esi,16
iertertreterterter:
mov edi,offset buffer+320*164+1
call oiseau
mov edi,offset buffer+320*148+1
call oiseau
mov edi,offset buffer+320*101+1
call oiseau
mov edi,offset buffer+320*30+1
call oiseau
mov edi,offset buffer+320*47+1
call oiseau

retrterterte5:

popall
ret
noel2:

pushall
push ds
pop  es
push fs
pop  ds

mov esi,64000*8+023*320+69
;mov edi,offset buffer+112+86*320
mov edi,offset buffer+1+320+9

mov ebx,es:[arbre]
add ebx,18*16
and ebx,0111110000B
shr ebx,2
add esi,es:[offset_oiseau+ebx]
call oiseau
mov edi,offset buffer+1+320+16+1+9
call oiseau
mov edi,offset buffer+1+320+16+1+16+1+9
call oiseau

mov esi,64000*8+023*320+69
mov ebx,es:[arbre]
add ebx,20*16
and ebx,0111100000B
shr ebx,3
add esi,es:[offset_oiseau+ebx]
mov edi,offset buffer+1+320+16+1+16+1+16*8
call oiseau
mov edi,offset buffer+1+320+16+1+16+1+16*10
call oiseau

mov esi,64000*8+023*320+69
mov ebx,es:[arbre]
add ebx,20*16
and ebx,0011110000B
shr ebx,2
add esi,es:[offset_oiseau+ebx]
mov edi,offset buffer+1+320+16+1+16+1+16*5
call oiseau
mov edi,offset buffer+1+320+16+1+6+1+16*14
call oiseau

;---- devant l'arbre
mov esi,64000*8+023*320+69
mov edi,offset buffer+112+89*320
mov ebx,es:[arbre]
and ebx,0111110000B
shr ebx,2
add esi,es:[offset_oiseau+ebx]
call oiseau
mov edi,offset buffer+112+89*320+16+1
call oiseau


retrterterte5rt:
popall

ret
oiseau:
pushall
mov ecx,16
iyuertertertrteert:
mov ebx,16
iyuconcert:
lodsb
or al,al
jz iyuertertertrte
mov byte ptr es:[edi],al
iyuertertertrte:
inc edi
dec ebx
jnz iyuconcert
add edi,320-16
add esi,320-16
dec ecx
jnz iyuertertertrteert
popall
ret


;rterterteertrteertert:
;xor ebx,ebx
;mov ecx,[nombre_de_dyna]

expere:
pushall
;POPALL
;push ecx
;xor eax,eax
;mov ax,word ptr [donnee+nb_dyna*2+ebx] ;y
;
;push eax
;shl   eax,6 ; x 64
;mov   edi,eax
;pop eax
;shl   eax,8 ; x 256
;add   edi,eax
;
;xor eax,eax
;xor esi,esi
;mov ax,word ptr [donnee+ebx]
;mov si,word ptr [donnee+nb_dyna*2*2+ebx]
;cmp si,666 ;code speical indique affiche rien...
;je nanananana_il_est_mort

;;------- source en fonction de si c'est un boy ou une girl...
;add esi,576000 ; 128000  ;307200
;cmp ebx,2*4
;jb reterterertrte45 ;c'est une girl...
;add esi,64000
;reterterertrte45:
;;-------------------------------

;mov ebx,320*200 ;307200
;mov ax,fs

; (serra tri‚ … l'affichage par chaque machine.mettra dest a 0ffffh)




mov ecx,8 ;[nombre_de_dyna]
oooooooo:

push ecx

;----- recherche le dyna le plus haut !!!
xor ebx,ebx
xor edi,edi

xor eax,eax
mov al,byte ptr [donnee4+6+ebx]
multiple_eax_par_320
add ax,word ptr [donnee4+4+ebx]
;--- cas particulier: on a une ombre: donc on prend l'ombre a la place
lapinomb ax
;----------------------------------------
;----

mov ebp,ebx

push ecx
mov ecx,8 ;[nombre_de_dyna]
gogotingo:
add ebx,nb_unite_donnee4 ;8
add edi,2 ;pour avoir un viseur x2 sur le numero du dyna kon a choisit
dec ecx
jz mwai

xor edx,edx
mov dl,byte ptr [donnee4+6+ebx]
multiple_edx_par_320
add dx,word ptr [donnee4+4+ebx]
;--- cas particulier: on a une ombre: donc on prend l'ombre a la place
lapinomb dx
;----------------------------------------


;cmp word ptr [donnee4+4+ebx],ax
cmp dx,ax
jnb fraiche

xor eax,eax
mov al,byte ptr [donnee4+6+ebx]
multiple_eax_par_320
add ax,word ptr [donnee4+4+ebx]
;add ax,319 ;pour ke ka on se croie gauche droite ca change pas bizarre
;           ;rement au milieu
;--- cas particulier: on a une ombre: donc on prend l'ombre a la place
lapinomb ax
;----------------------------------------

mov ebp,ebx
fraiche:
jmp gogotingo
mwai:
pop ecx


mov esi,dword ptr [donnee4+ebp]
cmp esi,666
je  nanananana_il_est_mort
push edi
xor edi,edi
mov di,word ptr [donnee4+4+ebp] ;offset "bloc"

  push ds

xor bx,bx
mov bl,byte ptr [donnee4+6+ebp] ;nombre des lignes.
xor cx,cx
mov cl,byte ptr [donnee4+7+ebp] ;nombre de colonnes.
mov dl,byte ptr [donnee4+8+ebp] ;1er bit: clignotement ???
and dl,01B

  push fs
  pop ds

  call  affiche_bomby
  pop ds
pop edi
  nanananana_il_est_mort:

mov word ptr [donnee4+4+ebp],-1
mov byte ptr [donnee4+6+ebp],0

pop ecx
dec ecx
jnz oooooooo

POPALL
ret

;cas particulier. brique en destruction...
retterterertertertertertertertertertert:
PUSHALL
aff_bombe
POPALL
jmp retterterertertertertertertertertertert2

affiche_bomby:
;mov dl,byte ptr [donnee4+8+ebp] ;1er bit: clignotement ???
;and dl,01B

cmp dl,1
je blancheur_supreme

affiche_bomby2: ;sans blancheur
;-----
add edi,offset buffer
;add esi,offset buffer2
;mov bx,23 ;dans bx: nombre de lignes
ertrterterte:
;mov cx,23
push edi esi cx
retertrtert:
lodsb
or al,al
jz reertert
mov es:[edi],al
reertert:
inc edi
dec cx
jnz retertrtert
pop cx esi edi
add esi,320
add edi,320
dec bx
jnz ertrterterte
ret
;affiche sprite mais en blanc.
blancheur_supreme:
add edi,offset buffer
;add esi,offset buffer2
;mov bx,23 ;dans bx: nombre de lignes
ertrtertertei:
;mov cx,23
push edi esi cx
retertrterti:
lodsb
or al,al
jz reerterti
mov byte ptr es:[edi],255
reerterti:
inc edi
dec cx
jnz retertrterti
pop cx esi edi
add esi,320
add edi,320
dec bx
jnz ertrtertertei
ret

aff_brique:

mov eax,[esi]
mov [edi],eax
mov eax,[esi+4]
mov [edi+4],eax
mov eax,[esi+8]
mov [edi+8],eax
mov eax,[esi+12]
mov [edi+12],eax

mov eax,[esi+320]
mov [edi+320],eax
mov eax,[esi+320+4]
mov [edi+320+4],eax
mov eax,[esi+320+8]
mov [edi+320+8],eax
mov eax,[esi+320+12]
mov [edi+12+320],eax

mov eax,[esi+320*2]
mov [edi+320*2],eax
mov eax,[esi+320*2+4]
mov [edi+320*2+4],eax
mov eax,[esi+320*2+8]
mov [edi+320*2+8],eax
mov eax,[esi+320*2+12]
mov [edi+12+320*2],eax

mov eax,[esi+320*3]
mov [edi+320*3],eax
mov eax,[esi+320*3+4]
mov [edi+320*3+4],eax
mov eax,[esi+320*3+8]
mov [edi+320*3+8],eax
mov eax,[esi+320*3+12]
mov [edi+12+320*3],eax


mov eax,[esi+320*4]
mov [edi+320*4],eax
mov eax,[esi+320*4+4]
mov [edi+320*4+4],eax
mov eax,[esi+320*4+8]
mov [edi+320*4+8],eax
mov eax,[esi+320*4+12]
mov [edi+12+320*4],eax

mov eax,[esi+320*5]
mov [edi+320*5],eax
mov eax,[esi+320*5+4]
mov [edi+320*5+4],eax
mov eax,[esi+320*5+8]
mov [edi+320*5+8],eax
mov eax,[esi+320*5+12]
mov [edi+12+320*5],eax

mov eax,[esi+320*6]
mov [edi+320*6],eax
mov eax,[esi+320*6+4]
mov [edi+320*6+4],eax
mov eax,[esi+320*6+8]
mov [edi+320*6+8],eax
mov eax,[esi+320*6+12]
mov [edi+12+320*6],eax

mov eax,[esi+320*7]
mov [edi+320*7],eax
mov eax,[esi+320*7+4]
mov [edi+320*7+4],eax
mov eax,[esi+320*7+8]
mov [edi+320*7+8],eax
mov eax,[esi+320*7+12]
mov [edi+12+320*7],eax


mov eax,[esi+320*8]
mov [edi+320*8],eax
mov eax,[esi+320*8+4]
mov [edi+320*8+4],eax
mov eax,[esi+320*8+8]
mov [edi+320*8+8],eax
mov eax,[esi+320*8+12]
mov [edi+12+320*8],eax


mov eax,[esi+320*9]
mov [edi+320*9],eax
mov eax,[esi+320*9+4]
mov [edi+320*9+4],eax
mov eax,[esi+320*9+8]
mov [edi+320*9+8],eax
mov eax,[esi+320*9+12]
mov [edi+12+320*9],eax


mov eax,[esi+320*10]
mov [edi+320*10],eax
mov eax,[esi+320*10+4]
mov [edi+320*10+4],eax
mov eax,[esi+320*10+8]
mov [edi+320*10+8],eax
mov eax,[esi+320*10+12]
mov [edi+12+320*10],eax


mov eax,[esi+320*11]
mov [edi+320*11],eax
mov eax,[esi+320*11+4]
mov [edi+320*11+4],eax
mov eax,[esi+320*11+8]
mov [edi+320*11+8],eax
mov eax,[esi+320*11+12]
mov [edi+12+320*11],eax


mov eax,[esi+320*12]
mov [edi+320*12],eax
mov eax,[esi+320*12+4]
mov [edi+320*12+4],eax
mov eax,[esi+320*12+8]
mov [edi+320*12+8],eax
mov eax,[esi+320*12+12]
mov [edi+12+320*12],eax


mov eax,[esi+320*13]
mov [edi+320*13],eax
mov eax,[esi+320*13+4]
mov [edi+320*13+4],eax
mov eax,[esi+320*13+8]
mov [edi+320*13+8],eax
mov eax,[esi+320*13+12]
mov [edi+12+320*13],eax


mov eax,[esi+320*14]
mov [edi+320*14],eax
mov eax,[esi+320*14+4]
mov [edi+320*14+4],eax
mov eax,[esi+320*14+8]
mov [edi+320*14+8],eax
mov eax,[esi+320*14+12]
mov [edi+12+320*14],eax


mov eax,[esi+320*15]
mov [edi+320*15],eax
mov eax,[esi+320*15+4]
mov [edi+320*15+4],eax
mov eax,[esi+320*15+8]
mov [edi+320*15+8],eax
mov eax,[esi+320*15+12]
mov [edi+12+320*15],eax

ret
reetrertertert3: ;affichage d'un oeuf

aff_oeuf

jmp reetrertertert

reetrertertert2: ;affichage d'une explosion de bonus...

aff_bombe2

jmp reetrertertert
affiche_sprites endp

;    mov     dx,3dah
;vbl1:           in      al,dx
;    test    al,8
;    jne     vbl1
;vbl2:           in      al,dx
;    test    al,8
;    je      vbl2



incrementation_ecx_vbl MACRO
local evbl13
local evbl13ertertrte
push dx ax
                 mov     dx,3dah
                 in      al,dx
                 test    al,8
                 jne     evbl13
                 in      al,dx
                 test    al,8
                 je      evbl13
inc ecx

                 mov     dx,3dah
evbl13ertertrte:
                 in      al,dx
                 test    al,8
                 je     evbl13ertertrte

evbl13:
pop ax dx
ENDM


;differentesply2 dd 0
;nb_sply EQU 6

vbl proc near

push dx ax

inc dword ptr [changement]

cmp [speed_raster],1
je no_fucking_vbl

;call vbl
;jmp ouiouirt
;no_fucking_vbl:
;inc dword ptr [changement]
;ouiouirt:


call raster1

		mov     dx,3dah
avbl1:           in      al,dx
		test    al,8
    jne     avbl1
avbl2:           in      al,dx
		test    al,8
    je      avbl2

call raster2

no_fucking_vbl:

pop ax dx
ret
vbl endp


vbl2 proc near

push dx ax

inc dword ptr [changement]

call raster1

		mov     dx,3dah
uvbl1:           in      al,dx
		test    al,8
    jne     uvbl1
uvbl2:           in      al,dx
		test    al,8
    je      uvbl2

call raster2

pop ax dx
ret
vbl2 endp

vbl3 proc near

push dx ax cx

xor cx,cx

		mov     dx,3dah
ruvbl1:           in      al,dx
		test    al,8
    jne     ruvbl1


ruvbl2:

;and cx,0011B
;jnz rtyryytytytryryrytryyrr
;push dx
;   mov   dx,3c8h
;   mov   al,0
;   out   dx,al
;   mov   dx,3c9h
;   mov   al,cl
;   out   dx,al
;   mov   al,0
;   out   dx,al
;   mov   al,0 ;63 ;15
;   out   dx,al
;and cx,63
;inc cx
;pop dx
;rtyryytytytryryrytryyrr:

           in      al,dx
    test    al,8
    je      ruvbl2

pop cx ax dx
ret
vbl3 endp


raster1 proc near
push dx ax

   mov   dx,3c8h
	 mov   al,0
	 out   dx,al
	 mov   dx,3c9h
   mov   al,0 ;15
	 out   dx,al
	 mov   al,0
	 out   dx,al
	 mov   al,0 ;63 ;15
	 out   dx,al
pop ax dx
ret
raster1 endp


raster2 proc near

cmp [mechant],2
jne ertrtyrtyrtyrtyryrtyyrttyr

;cmp [jesus_mode],0
;je ertrtyrtyrtyrtyryrtyyrttyr

;cmp [affiche_raster2],0
;je ertrtyrtyrtyrtyryrtyyrttyr
foooooooooo:

push dx ax
   mov   dx,3c8h
	 mov   al,0
	 out   dx,al
	 mov   dx,3c9h
   mov   al,60 ;15
	 out   dx,al
	 mov   al,0
	 out   dx,al
	 mov   al,0 ;63 ;15
	 out   dx,al
pop ax dx
 ertrtyrtyrtyrtyryrtyyrttyr:
ret
raster2 endp


;load proc near
; xor eax,eax
; mov al,00h  ;ouverture du fichier pour lecture.
; mov ah,03dh
; mov edx,offset fichier
; int 21h
; jc erreur_filec;saute si carry=1
;
; mov ebx,eax
; mov ah,03fh
; mov ecx,064000
; mov edx,offset buffer
; int 21h
;
; mov ah,03eh
; int 21h
;ret
erreur_filec:
        mov ax,3h
        int 10h
        lea edx,loaderror
        mov ah,9
        int 21h
        mov bl,0100B ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color

        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h

call affsigne
ret
;load endp

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

;copie_page2 proc near ;copie dans buffer2 ce k'il y a a : FS:ESI
;PUSHALL
;
;mov ax,ds
;mov es,ax
;mov ax,fs
;mov ds,ax
;mov edi,offset buffer2
;mov ecx,64000/4
;rep movsd
;
;POPALL
;ret
;copie_page2 endp

copie_page proc near ;copie dans buffer ce k'il y a a : FS:ESI
PUSHALL

mov ax,ds
mov es,ax
mov ax,fs
mov ds,ax
mov edi,offset buffer
mov ecx,64000/4
rep movsd

POPALL
ret
copie_page endp

aff_page2 proc near ;affiche en ram video ce k'il y a a dans le buffer
PUSHALL

cmp [affiche_pal],1 ;!!! sauf si on eteint la pal...
jne erertrte
popall
ret
erertrte:

xor edi,edi

;mov ax,fs  ;SOURCE...
;mov ds,ax  ;

mov esi,offset buffer

mov ecx,320*200/4
rep movsd

POPALL
ret
aff_page2 endp


load_pcx proc near ; ecx: offset dans le fichier.
                   ; edx: offset nom du fichier
                   ; edi: viseur dans donn‚es ou ca serra copi‚ (ax:)
                   ; ebx: nombre de pixels dans le pcx

pushad
push es ds

mov [load_pcx_interne],ebx


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

cmp ebx,[load_pcx_interne]
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

load_raw proc near ; ecx: offset dans le fichier.
                   ; edx: offset nom du fichier
                   ; edi: viseur dans donn‚es ou ca serra copi‚ (ax:)
                   ; ebx: nombre de pixels dans le pcx

pushad
push es ds

 xor eax,eax
 mov al,00h  ;ouverture du fichier pour lecture.
 mov ah,03dh
 int 21h
jnc retyryurttyutyutyuutyyuiiyuuiyuiy
mov dl,13
mov ah,2
int 21h
lea edx,suite2
mov ah,09h
int 21h
        mov bl,4 ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color
        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h
retyryurttyutyutyuutyyuiiyuuiyuiy:

mov [load_handle],eax

mov ebx,[load_handle]
mov ah,042h
mov al,00h ;debut du fichier
mov dx,cx
shr ecx,16
int 21h

 mov ebx,[load_handle]
 mov ah,03fh
 mov ecx,064000
                   ; edi: viseur dans donn‚es ou ca serra copi‚ (ax:)
push ds
push fs
pop  ds
 mov edx,edi
 int 21h
pop ds

mov ebx,[load_handle]
mov ah,03eh
int 21h

pop ds es
popad
ret
load_raw endp


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

;pal          db  768 dup (?)  ;pal  de l'‚mulateur.
;pal_affich‚e db 768 dup (0)   ;pal k'on affiche...

;affiche_pal  db 0             ; 1: vas de la palette au noir (ne plus afficher
;                              ;                               d'‚cran !!!)
;                              ;
;                              ; 2: va du noir a la palette
;                              ; 0: ne fait rien...


pal_visage proc near
pushall
;call noping
;call noping
;call noping
;call noping
;call noping
;call noping
;call noping
;call noping
;call noping
;call noping
;call noping
;call noping
cmp byte ptr [assez_de_memoire],1
je rty

cmp [affiche_pal],0
jne histoire
rty:
popall
ret
histoire:

push ds
pop  es

cmp [affiche_pal],1
jne zorrro

;affiche_pal  db 0             ; 1: vas de la palette au noir (ne plus afficher
;                              ;                               d'‚cran !!!)

;------------
xor bp,bp
mov dx,4
reeeeee:
;mov esi,offset pal
mov esi,offset pal_affich‚e
mov cx,768
rchanger:
cmp byte ptr [esi],0
je pareil
dec byte ptr [esi]
jmp pas_pareil
pareil:
inc bp
pas_pareil:
inc esi
dec cx
jnz rchanger
dec dx
jnz reeeeee

cmp bp,768*4
jne erterterterrterte
mov [affiche_pal],2
erterterterrterte:

call affpal
popall
ret

zorrro:

xor bp,bp
mov dx,4
yreeeeee:

mov edi,offset pal

;cmp byte ptr [ordre2],'' ;uniqUEMENT si on est dans le jeu.
;jne terterertrteertyerertrteterter

cmp byte ptr [ordre],'S'
jne rezterterertrteertyerertrteterter
cmp [master],0
jne opiopiioiouuiiuiuiuooo
cmp [pic_time],0
je opiopiioiouuiiuiuiuooo
lea edi,pal_pic
;cmp kel_pic_intro,1
;jne opiopiioiouuiiuiuiuooo
;lea edi,pal_pic2
opiopiioiouuiiuiuiuooo:
rezterterertrteertyerertrteterter:

; si on est pas dans le menu
cmp byte ptr [ordre],'S'
je terterertrteertyerertrteterter
cmp byte ptr [ordre2],''
jne terrteterertterterertrteertyerertrtetertererer
lea edi,pal_jeu
terrteterertterterertrteertyerertrtetertererer:
cmp byte ptr [ordre2],'V'
jne terrteterertterterertrteertyerertrteterterererr
lea edi,pal_jeu
terrteterertterterertrteertyerertrteterterererr:


cmp byte ptr [ordre2],'V'
jne terrteterertterterertrteertyerertrtetertererereErr
lea edi,pal_vic
terrteterertterterertrteertyerertrtetertererereErr:


cmp byte ptr [ordre2],'Z'
jne terrteterertterterertrteertyerertrtetertererereE
lea edi,pal_med
terrteterertterterertrteertyerertrtetertererereE:
cmp byte ptr [ordre2],'D'
jne tyr2trtyrtyrtyrtyrtyterterertrteert
lea edi,pal_draw
tyr2trtyrtyrtyrtyrtyterterertrteert:
terterertrteertyerertrteterter:


cmp pic_de_tout_debut,1
jne ereetrtrtrtrteeete
lea edi,pal_pic2
ereetrtrtrtrteeete:

mov esi,offset pal_affich‚e
mov cx,768
yrchanger:
mov al,byte ptr [edi]
cmp byte ptr [esi],al
je ypareil
inc byte ptr [esi]
jmp ypas_pareil
ypareil:
inc bp
ypas_pareil:
inc edi
inc esi
dec cx
jnz yrchanger
dec dx
jnz yreeeeee

cmp bp,768*4
jne yerterterterrterte
mov [affiche_pal],0
yerterterterrterte:

call affpal

popall
ret
endp

;get_pal_ansi proc near
;pushall
;   mov   dx,3c7h
;   XOR   al,al
;   out   dx,al
;   mov   dx,3c9h
;push ds
;pop es
;lea edi,pal_txt_debut
;         mov cx,256*3
;         u@@saaccvaaaax:
; in al,dx
;stosb
;   dec cx
;         JNZ  u@@saaccvaaaax
;popall
;ret
;get_pal_ansi endp

affpal      proc near
    pushad

         mov   esi,offset pal_affich‚e
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

affpal2      proc near
    pushad

;         mov   esi,offset pal_affich‚e
	 mov   dx,3c8h
	 XOR   al,al
	 out   dx,al
	 mov   dx,3c9h
         mov cx,256*3
         a@@saaccvaaaax:
	 LODSB
	 out   dx,al
	 dec cx
         JNZ  a@@saaccvaaaax
   popad
   ret
affpal2      endp

copie_le_fond proc near
PUSHALL

dec [attente]

cmp [attente],0
jne erteteteerre

add [viseur_sur_fond],4
mov [attente],max_attente

cmp [terrain],2     ; eau...
jne yertertertertertutyoooooortyyrt
mov [attente],min_attente    ;
yertertertertertutyoooooortyyrt:


erteteteerre:
mov eax,4*4

cmp [terrain],2 ;       db 2        ; 1:fete, 2: neige...
jne yertertertertertutyoooooo
mov eax,3*4
yertertertertertutyoooooo:

mov ebx,[viseur_sur_fond]
cmp  ebx,eax ;4 [nombre_de_fond]
jb erterertyurttyu
mov [viseur_sur_fond],0
xor ebx,ebx
erterertyurttyu:

push ebx
mov bl,terrain
dec bl
shl ebx,2
mov esi,[ebx+kelle_offset_fond]
pop ebx

mov esi,[esi+ebx]

;cmp [terrain],2 ;       db 2        ; 1:fete, 2: neige...
;jne yertertertertert
;mov esi,[adresse_des_fonds_neige+ebx]
;yertertertertert:
;
;cmp [terrain],3 ;       db 2        ; 1:fete, 2: neige...
;jne yertertertertert1
;mov esi,[adresse_des_fonds_hell+ebx]
;yertertertertert1:
;
;cmp [terrain],4 ;       db 2        ; 1:fete, 2: neige...
;jne yertertertertert2
;mov esi,[adresse_des_fonds_foret+ebx]
;yertertertertert2:
;
;cmp [terrain],5 ;       db 2        ; 1:fete, 2: neige...
;jne yertertertertert2r
;mov esi,[adresse_des_fonds_nuage+ebx]
;yertertertertert2r:
;
;
;
;cmp [terrain],1 ;       db 2        ; 1:fete, 2: neige...
;jne rertertertertert
;mov esi,[adresse_des_fonds+ebx]
;rertertertertert:



;===== affiche en ram video ce k'il y a a : FS:ESI
;      ENTREE : ESI
call copie_page

POPALL
ret
copie_le_fond endp


copie_le_fond_draw proc near
PUSHALL

;adresse_des_fonds dd 0,64000,128000
;nombre_de_fond    dd 3*2
;viseur_sur_fond   dd 0
;attente               db 0
;max_attente           db 0

dec [attente]

cmp [attente],0
jne yerteteteerre

add [viseur_sur_draw],4
mov [attente],max_attente

yerteteteerre:

mov ebx,[viseur_sur_draw]
cmp  ebx,[nombre_de_draw]
jne yerterertyurttyu
mov [viseur_sur_draw],0
xor ebx,ebx
yerterertyurttyu:

mov esi,[adresse_des_draws+ebx]

;===== affiche en ram video ce k'il y a a : FS:ESI
;      ENTREE : ESI
call copie_page

POPALL
ret
copie_le_fond_draw endp


copie_le_fond_vic  proc near
PUSHALL

dec [attente]

cmp [attente],0
jne iyyerteteteerre

;mov edi,704000 ; 128000  ;307200
add [viseur_sur_vic],4
mov [attente],max_attente4

iyyerteteteerre:

mov ebx,[viseur_sur_vic]
cmp  ebx,[nombre_de_vic]
jne iyerterertyurttyu
mov [viseur_sur_vic],0
xor ebx,ebx
iyerterertyurttyu:

mov esi,[adresse_des_vic+ebx]

;===== affiche en ram video ce k'il y a a : FS:ESI
;      ENTREE : ESI
call copie_page
POPALL
PUSHALL
push ds
pop   es
;mov esi,offset donnee4+9*4
;mov ecx,9
;rep movsd

;mov esi,dword ptr [donnee4+9*4]
;
;mov esi,640000 ; 128000  ;307200

inc dword ptr [changementZZ]
mov ebx,[changementZZ]
and ebx,000110000B
shr ebx,2
mov esi,dword ptr [donnee4+9*4+ebx]
mov edi,152+57*320-2-1
xor cx,cx
mov cl,byte ptr [donnee4+9*4+4*4+1] ;nombre de colonnes.
xor bx,bx
mov bl,byte ptr [donnee4+9*4+4*4] ;nb lignes

mov dl,byte ptr [donnee4+8+ebp] ;1er bit: clignotement ???
and dl,01B

push ds
push fs
pop  ds
call affiche_bomby2
pop  ds

POPALL
ret
copie_le_fond_vic endp


copie_le_fond_med proc near

PUSHALL

SOUND

;adresse_des_fonds dd 0,64000,128000
;nombre_de_fond    dd 3*2
;viseur_sur_fond   dd 0
;attente               db 0
;max_attente           db 0

mov esi,64000*7                  ;[adresse_des_draws+ebx]
cmp [team3],1
jne pas_color
mov esi,1582080+64000
pas_color:
cmp [team3],2
jne pas_g
mov esi,1582080+64000*2
pas_g:

;===== affiche en ram video ce k'il y a a : FS:ESI
;      ENTREE : ESI
call copie_page

;---- copie les noms des joueurs
pushall
push ds
pop es

mov ebx,offset briques
mov [viseur_couleur],0
mov edi,offset buffer
mov ecx,8
xor edx,edx
pppppppgoeger:
push edi
;viseur_namec dd 10+(69)*320,10+(69+9)*320,10+(43+42*2)*320,10+(43+42*3)*320
cmp [team3],1
jne pas_c3
add edi,[viseur_namec+edx]
jmp ihjhuihui
pas_c3:
cmp [team3],2
jne pas_g3
add edi,[viseur_nameg+edx]
jmp ihjhuihui
pas_g3:
add edi,[viseur_name+edx]
ihjhuihui:
;------------- affiche un nom de joueur...--
pushall
call affiche_un_caractere
popall
add edi,8
inc ebx
pushall
call affiche_un_caractere
popall
add edi,8
inc ebx
pushall
call affiche_un_caractere
popall
inc [viseur_couleur]
add ebx,2 ;affichae pas l'espace
;-------------------------------------------
pop edi
add edx,4
;add ebx,4
dec ecx
jnz pppppppgoeger

popall
;-------------------

popall

pushall

;------- copie les m‚dailles ---

;victoires dd 8 dup (?)
;viseur pour on place la premiere m‚daille pour chacun des 8 joueurs.
;
;viseur_victory dd 44+44*320,44+86*320,44+128*320,44+170*320
;               dd 205+45*320,205+86*320,205+128*320,205+170*320
;latest_victory dd ?
;offset_medaille dw 23*0,23*1,23*2,23*3,23*4,23*5,23*6,23*7,23*8,23*9,23*10,23*11,23*12
;                dw 23*320+23*0,23*320+23*1,23*320+23*2
push ds
pop  es

;mov edi,offset buffer
;mov ecx,320
;mov eax,54501015
;rep stosd

mov esi,64000*8

xor ebx,ebx

mov ax,fs
;;dans ax: source
mov ds,ax

;add viseur sur la piece !!!
mov ebx,es:[changementZZ]
and ebx,0111100B
shr ebx,1

inc dword ptr es:[changementZZ]

xor ebp,ebp
mov edi,offset buffer
ertrterteterter:
push edi

mov ecx,dword ptr es:[donnee4+ebp] ;victoires
or ecx,ecx
jz ertertertertertertert

cmp ecx,5
jb rerterteertrte
mov ecx,5
rerterteertrte:


;-----
erertererrteert:
push edi esi
xor eax,eax

;mov ebx,es:[changement]
;and ebx,0111100B
;shr ebx,1

;add ebx,ebx
mov ax,word ptr es:[offset_medaille+ebx]
add esi,eax

cmp es:[team3],1
jne pas_c32
add edi,es:[viseur_victoryc+ebp]
jmp ihjhuihui2
pas_c32:
cmp es:[team3],2
jne pas_c32r
add edi,es:[viseur_victoryg+ebp]
jmp ihjhuihui2
pas_c32r:
add edi,es:[viseur_victory+ebp]
ihjhuihui2:

;--- clignotement ---
cmp ecx,1
jne eertterrtrteterert
cmp dword ptr es:[donnee4+4*8],ebp
jne eertterrtrteterert

mov esi,64000*8 ;de face uniquement

;briques dw 1+19*13*2 dup (?)  ;nombre de brique, source de la brique, destination
;                              ;dans buffer video
;                              ;si on est dans 'Z' m‚daille c‚remony
;                              ;les noms de chaque joueur. 8x4 octets.
;
;                   ;+ 1 db= faut afficher la brike ki clignote ou pas???
cmp byte ptr es:[briques+8*4],1
je ertterrtrteterert
;test dword ptr es:[changementZZ],0000110000B
;jnz  eertterrtrteterert
;jmp ertterrtrteterert
eertterrtrteterert:
call aff_sprite
ertterrtrteterert:
;--- clignotement ---

pop  esi edi

add edi,23

add ebx,2*2
and ebx,31

dec ecx
jnz erertererrteert
;-----
ertertertertertertert:


pop edi
add ebp,4
cmp ebp,4*8
jne ertrterteterter

POPALL
ret
aff_sprite:
PUSH ecx ebx esi
mov ecx,22
ertertertrteert:
mov ebx,22
concert:
lodsb
or al,al
jz ertertertrte
mov byte ptr es:[edi],al
ertertertrte:
inc edi
dec ebx
jnz concert
add edi,320-22
add esi,320-22
dec ecx
jnz ertertertrteert
pop  esi ebx ecx
ret
copie_le_fond_med endp


inst_clavier proc near
PUSHALL

;2.14 - Function 0200h - Get Real Mode Interrupt Vector:
;-------------------------------------------------------
;  Returns the real mode segment:offset for the specified interrupt vector.
;In:
;  AX     = 0200h
;  BL     = interrupt number
;Out:
;  always successful:
;    carry flag clear
;    CX:DX  = segment:offset of real mode interrupt handler
;Notes:
;) The value returned in CX is a real mode segment address, not a protected
;  mode selector.

;mov ax,0200h
;mov bl,9
;int 31h
;
;mov word ptr [clavier_old_int],dx
;mov word ptr [clavier_old_int+2],cx

;2.15 - Function 0201h - Set Real Mode Interrupt Vector:
;-------------------------------------------------------
;  Sets the real mode segment:offset for the specified interrupt vector.
;In:
; AX     = 0201h
;  BL     = interrupt number
;  CX:DX  = segment:offset of real mode interrupt handler

;offset_2_adresse_physique proc near ;source ds:esi
;                                    ;adresse physique (dx:ax)

;mov esi,offset HANDLER9
;call offset_2_adresse_physique
;mov cx,dx
;mov dx,ax
;mov ax,201h
;int 31h

;2.18 - Function 0204h - Get Protected Mode Interrupt Vector:
;------------------------------------------------------------
;
;  Returns the address of the current protected mode interrupt handler for the
;specified interrupt.
;
;In:
;  AX     = 0204h
;  BL     = interrupt number
;
;Out:
;  always successful:
;    carry flag clear
;    CX:EDX = selector:offset of protected mode interrupt handler

;  AX     = 0204h
;  BL     = interrupt number
;
;Out:
;  always successful:
;    carry flag clear
;    CX:EDX = selector:offset of protected mode interrupt handler

mov cx,cs
mov edx,offset handler10
mov ax,0205h
mov bl,9
int 31h

POPALL
ret
inst_clavier endp

;de_inst_clavier proc near
;PUSHALL
;
;mov dx,word ptr [clavier_old_int]
;mov cx,word ptr [clavier_old_int+2]
;
;mov ax,201h
;int 31h
;
;
;POPALL
;ret
;
;de_inst_clavier endp

;db 0b8h
;sisisis dw ?




HANDLER10 PROC NEAR ;detourtenement int 9h (procedure k'on rajoute devant l'int.)
PUSHF
pushall

mov ecx,132456h
mov edx,132456h
db 0b8h
merdo dd ? ;2144
mov ds,ax

;mov temps_avant_demo,ttp



xor eax,eax
in al,60h
;call affsigne
;mov [last_sucker],al
;mov [last_sucker],al
test al,128
jnz ureertrteertert2

cheat jesus_viseur,jesus,jesus_mode,1
cheat jesus_viseur2,jesus2,speed_raster,1
cheat jesus_viseur3,jesus3,speed_raster,0
cheat jesus_viseur4,jesus4,speed_raster,0
cheat jesus_viseur5,jesus5,jesus_mode,0
;cheat jesus_viseur6,jesus6,record_user,1

ureertrteertert2:

mov edi,offset clavier

cmp al,225         ;
jne retertert_specialye
mov [clavier_stuff2],2

cmp action_replay,0
jne retertert_specialye

mov [pause],1
jmp tttttttttoooooi
retertert_specialye:

cmp al,224         ;
jne retertert_special
mov [clavier_stuff],1
jmp tttttttttoooooi
retertert_special:

;------------- special pause -----------
cmp [clavier_stuff2],0
je reterrteertertter
dec [clavier_stuff2]
;;;;;;;;jnz tttttttttoooooi
;;;;;;;;;;;mov [last_sucker],110 ;code pause...
jmp tttttttttoooooi
reterrteertertter:
;---------------------

cmp [clavier_stuff],1
jne pas_extanded
mov [clavier_stuff],0
;;-+----------------
;cmp al,42 ;cas particulier.. les 224,42 on s'en tappe !!!
;je tttttttttoooooi
;;-+------------

;---c as particulier pause !!!!
cmp al,70
jne pas_poauser
mov [pause],1
 pas_poauser:
;--------


xor ebx,ebx
CMP AL,128
JB uTOU
and al,127
mov bl,al
mov al,[clavier_extanded+ebx]
or al,al           ;si non prevu... fait rien...
je tttttttttoooooi

or al,128
jmp pas_extanded
uTOU:
mov bl,al
mov al,[clavier_extanded+ebx]
;cmp al,42 ;cas particulier.. les 224,42 on s'en tappe !!!
or al,al           ;si non prevu... fait rien...
je tttttttttoooooi

pas_extanded:

CMP AL,128
JB uTOUCHE_APPUYEE
AND AL,01111111B
ADD eDI,eAX
MOV byte ptr [eDI],0
jMP uBE_ALL
uTOUCHE_APPUYEE:
add edi,eax
;;-----------------------***--------------**
;;touches_  dd 114,115,112,113,82,83,0, -1
;;          dd 20,21,16,30,57,15,0,     -1
;push ebx edi
;xor ebx,ebx
;encpoooe:
;cmp [touches_+ebx+7*4],-1
;;jne pas_active
;cmp [touches_+ebx],eax
;je cceluila
;cmp [touches_+ebx+4],eax
;je cceluila
;cmp [touches_+ebx+8],eax
;je cceluila
;cmp [touches+ebx+12],eax
;je cceluila
;
;jmp pas_active
;cceluila:
;mov edi,offset clavier
;add edi,[touches_+ebx]
;MOV byte ptr [eDI],0
;
;mov edi,offset clavier
;add edi,[touches_+ebx+4]
;;MOV byte ptr [eDI],0
;
;mov edi,offset clavier
;add edi,[touches_+ebx+8]
;MOV byte ptr [eDI],0
;
;mov edi,offset clavier
;add edi,[touches_+ebx+12]
;MOV byte ptr [eDI],0
;
;pas_active:
;add ebx,8*4
;cmp ebx,(8*4)*8
;jne encpoooe
;pop edi ebx
;;------------********---------************-
MOV byte ptr [eDI],1
mov [last_sucker],al
uBE_ALL:

tttttttttoooooi:

cmp eax,1
jne uertterertert
cmp [attente_nouveau_esc],0
jne uertterertert
mov [sortie],1
uertterertert:


uoitreterrtyrty:

mov byte ptr [une_touche_a_telle_ete_pressee],1 ;et oui...
mov al,20h
out 20h,al

popall
POPF
iret

handleR10 ENdP


;donnee2 dd 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
;        dd 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
;        dd 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
;        dd 0,0,0,0     ,0,0   ;4eme joeur d'un ordy

;mov esi,offset donnee2 ;si joeur 1


controle proc near ;utilise par les slavers et les masters
PUSHALL
                 ;pr‚pare le packet qu'on va transmettre en informant
                 ;les touches ke l'on presse actuellement
                 ;

;nbe_bomber_locaux dd 2 ;nombre de bombers locaux
;
;bomber_locaux dd 0,1,0,0 ;mode de controle pour les bombermans locaux.
;;0 key droit
;;1 keyb gauche

;--------- efface le packet...
push ds
pop  es
xor eax,eax
mov edi,offset donnee2
mov ecx,touches_size
rep stosb
;----------------------------

mov ecx,8 ;[nbe_bomber_locaux] ;ceci ne correspond pas a l'ordre des dyna
                               ; juste les 8 dyna possilbe sur 1 becane
mov esi,offset donnee2
mov edi,offset bomber_locaux  ;mode de control
;xor ebp,ebp
;
;mov ah,02h ;SUPER_SIGNE2 DB 0
;mov dl,13
;int 21h

ertyertyjyuiyuiyuiiyu:
push ecx

push esi
mov dword ptr [esi],0 ;on efface le dernier packet
mov word ptr [esi+4],0
push edi
mov edi,[edi]
cmp dword ptr [edi+7*4],-1 ;ke si joueur en action (via setup)
jne retertertrtertetyyrtuui

call controle_joueur_fleche
retertertrtertetyyrtuui:
pop edi
pop esi

add esi,7 ;6 ;7

add edi,4 ;mode de control
;add ebp,4
pop ecx
dec ecx
jnz ertyertyjyuiyuiyuiiyu


;mov dword ptr [esi+20],0 ;return
cmp byte ptr [clavier+28],1
jne erertertertp
mov byte ptr [donnee2+8*7],1
erertertertp:


cmp byte ptr [clavier+1],1
jne erertertertpt
mov byte ptr [donnee2+8*7+1],1
erertertertpt:

cmp byte ptr [une_touche_a_telle_ete_pressee],1
jne erertertertptEE
mov byte ptr [donnee2+8*7+2],1
erertertertptEE:
mov byte ptr [une_touche_a_telle_ete_pressee],0

POPALL
ret
controle endp

menu_intelligence proc near

pushall

call vbl

SOUND_FAC fx

;n al,60h
;cmp al,57
;jne reterrterterte2
;mov byte ptr [ordre],''
;reterrterterte2:
;cmp byte ptr [clavier+1],1
;jne erertertertpt
;cmp byte ptr [total_t+6*4+1],1


;------------- ordre du master --------------------------

;******************************************************

cmp action_replay,1 ;si on est en mode rec; on decremente pas ca.
je rtbrtyjkrtklrtyrtyrtyrty
dec temps_avant_demo
jnz rtbrtyjkrtklrtyrtyrtyrty
mov temps_avant_demo,ttp2 ;temps_avant_demo2/10
jmp rtrtytyutyutyutyuyuttyuyuttyuyutyuyuttyuyuttyuyut
rtbrtyjkrtklrtyrtyrtyrty:

;cmp byte ptr [clavier+88],1 ;F12
;jne retyeyutyuutyyutyutyuioodfgdfgdfggdf
;
cmp action_replay,2
je rtrtytyutyutyutyuyuttyuyuttyuyutyuyuttyuyuttyuyut

jmp retyeyutyuutyyutyutyuioodfgdfgdfggdf

rtrtytyutyutyutyuyuttyuyuttyuyutyuyuttyuyuttyuyut:

        ;on ne passe pas en mode demo si on est sur le 386...
        cmp [assez_de_memoire],1
        je retyeyutyuutyyutyutyuioodfgdfgdfggdf



;=========== restauration/sauvegarde replay ===========
;******** ACTION REPLAY--------------------
; si play
;cmp action_replay,2 ; play,recup...
;jne pashjktrkhjerterttyrr
;mov edx,dword ptr fs:[1966080+TAILLE_HEADER_REC-5] ;rotation, offet 1 dans le header !
pushall

; on joue une partie


;differentesply dd 1966080+64000,1966080+64000*2,1966080+64000*3,1966080+64000*4,1966080+64000*5

mov ebx,differentesply2

add differentesply2,4
cmp differentesply2,4*nb_sply
jne ertyertyuityu
mov differentesply2,0
ertyertyuityu:

mov esi,[differentesply+ebx]

mov ax,fs
mov ds,ax
mov es,ax

;mov eax,fs:[1966080+TAILLE_HEADER_REC-9] ;variable changement

mov edi,1966080
;mov esi,1966080+64000
mov ecx,16000
rep movsd
popall
;pashjktrkhjerterttyrr:
;=======

;initialisation des pointeurs..
mov byte ptr fs:[1966080+TAILLE_HEADER_REC],1 ;(viseur bonus ?)
mov dword ptr fs:[1966080+TAILLE_HEADER_REC+TAILLE_BONUS_REC],4 ; (taille octet suite a BONUS_REC)

mov action_replay,2 ;play
push eax
mov eax,dword ptr fs:[1966080+TAILLE_HEADER_REC-17] ;nombre de dyna
mov [nombre_de_dyna],eax
mov byte ptr [ordre],''
pop eax
popall
ret
retyeyutyuutyyutyutyuioodfgdfgdfggdf:
;****************************************************

mov eax,[nombre_minimum_de_dyna]

cmp [nombre_de_dyna],eax ;uniquement s'il y a au moins 2 dyna...
jb erertertertpert

cmp demande_partie_slave2,0
je jkrltjhetjhejhjhtejhhjthjehjehjerjherlhjetlhljter2
cmp demande_partie_slave,1
je jkrltjhetjhejhjhtejhhjthjehjehjerjherlhjetlhljter
jkrltjhetjhejhjhtejhhjthjehjehjerjherlhjetlhljter2:

cmp byte ptr [clavier+28],1
jne erertertertpert
jkrltjhetjhejhjhtejhhjthjehjehjerjherlhjetlhljter:
mov demande_partie_slave,0
mov [on_a_bien_fait_une_partie],1
mov byte ptr [ordre],''
erertertertpert:
cmp byte ptr [clavier+2],1
jne erertertertperterre
mov [viseur_liste_terrain],0
erertertertperterre:
cmp byte ptr [clavier+3],1
jne erertertertperterrert
mov [viseur_liste_terrain],1
erertertertperterrert:
cmp byte ptr [clavier+4],1
jne erertertertperterrert4t
mov [viseur_liste_terrain],2
erertertertperterrert4t:
cmp byte ptr [clavier+5],1
jne erertertertperterrert4t54
mov [viseur_liste_terrain],3
erertertertperterrert4t54:
cmp byte ptr [clavier+6],1
jne erertertertperterrert4t54r
mov [viseur_liste_terrain],4
erertertertperterrert4t54r:
cmp byte ptr [clavier+7],1
jne erertertertperterrert4t54rt5
mov [viseur_liste_terrain],5
erertertertperterrert4t54rt5:
cmp byte ptr [clavier+8],1
jne erertertertperterrert4t54rt5y
mov [viseur_liste_terrain],6
erertertertperterrert4t54rt5y:
cmp byte ptr [clavier+9],1
jne erertertertperterrert4t54rt5yd
mov [viseur_liste_terrain],7
erertertertperterrert4t54rt5yd:


;cmp byte ptr [clavier+5],1
;jne erertertertperterrert4t3
;mov [viseur_liste_terrain],3
;erertertertperterrert4t3:

;----------------------------------------------------------------

;--------- r‚cupere touches pour personnes d‚ja inscrites...

push ds
pop es

mov ebp,[nombre_de_dyna]
or  ebp,ebp
jz yen_a_pas
xor ebx,ebx
xor edx,edx

ooooooooh:

cmp [name_joueur+ebx],4 ;finito
je ms_dos

;---- copie le nom du joueur

mov esi,offset nick_t
add esi,[control_joueur+ebx]
lodsd
mov dword ptr [texte1+6*1+1+32*0+edx],eax
mov dword ptr [texte1+6*1+1+32*1+edx],eax
mov dword ptr [texte1+6*1+1+32*2+edx],eax
mov dword ptr [texte1+6*1+1+32*3+edx],eax

;---- affiche le curseur.
cmp [name_joueur+ebx],1
jb  retrterteoooshow
cmp [name_joueur+ebx],3
ja  retrterteoooshow
push edx
mov dword ptr [texte1+6*2+32*0+edx],'    '
mov dword ptr [texte1+6*2+32*1+edx],'    '
mov dword ptr [texte1+6*2+32*2+edx],'    '
mov dword ptr [texte1+6*2+32*3+edx],'    '

add edx,[name_joueur+ebx]
mov byte ptr [texte1+6*2+32*0+edx],'-'
mov byte ptr [texte1+6*2+32*1+edx],'-'
mov byte ptr [texte1+6*2+32*2+edx],'-'
mov byte ptr [texte1+6*2+32*3+edx],'-'
pop edx
retrterteoooshow:
;-------------------
;regarde si on a press‚...
dec [temps_joueur+ebx]
cmp [temps_joueur+ebx],0
jne ertterrtytyrrtyrtyrtyrtytuoooooooooo

;les fleches... changement d'un caratere...
mov esi,offset total_t
add esi,[control_joueur+ebx]
cmp byte ptr [esi+3],0
je pas_flechedu
;mov temps_avant_demo,ttp
push esi
mov esi,offset nick_t
add esi,[control_joueur+ebx]
add esi,[name_joueur+ebx]
dec byte ptr [esi-1]
cmp byte ptr [esi-1],'a'-1
jne ertrteertterrterterte
mov byte ptr [esi-1],'z'+13 ;,'a'
ertrteertterrterterte:
pop esi
mov [temps_joueur+ebx],temps_re_menu
jmp finito_touches
pas_flechedu:

;les fleches... changement d'un caratere...
mov esi,offset total_t
add esi,[control_joueur+ebx]
cmp byte ptr [esi+0],0
je upas_flechedu
;mov temps_avant_demo,ttp
push esi
mov esi,offset nick_t
add esi,[control_joueur+ebx]
add esi,[name_joueur+ebx]
inc byte ptr [esi-1]
cmp byte ptr [esi-1],'z'+14
jne uertrteertterrterterte
mov byte ptr [esi-1],'a' ;'z'+13
uertrteertterrterterte:
pop esi
mov [temps_joueur+ebx],temps_re_menu
jmp finito_touches
upas_flechedu:



;les fleches...

mov esi,offset total_t
add esi,[control_joueur+ebx]
cmp byte ptr [esi+1],0
je pas_fleched
;mov temps_avant_demo,ttp
inc [name_joueur+ebx]
cmp [name_joueur+ebx],4
jne pertertras_flechedertertertret
mov [name_joueur+ebx],3
jmp ooooiio
pertertras_flechedertertertret:
bruit 5 40 fx
ooooiio:
mov [temps_joueur+ebx],temps_re_menu
jmp finito_touches
pas_fleched:

cmp byte ptr [esi+2],0
je pas_flechedm
;mov temps_avant_demo,ttp
dec [name_joueur+ebx]
cmp [name_joueur+ebx],0
jne pertertras_flechedertertertretm
mov [name_joueur+ebx],1
jmp ootoi
pertertras_flechedertertertretm:
bruit 5 40 fx
ootoi:
mov [temps_joueur+ebx],temps_re_menu
jmp finito_touches
pas_flechedm:

;--- sort...
cmp byte ptr [esi+4],0
je pas_flechedmy
;mov temps_avant_demo,ttp
;---- que si sur le 3eme caractere. sinon decalle...

cmp [name_joueur+ebx],3
je pertertras_flechedertertertrety

bruit 5 40 fx

inc [name_joueur+ebx]
mov [temps_joueur+ebx],temps_re_menu
jmp finito_touches
pertertras_flechedertertertrety:
;;====================--------- cas particulier de gruge !!! rmc:
;pushall
;mov esi,offset nick_t
;add esi,[control_joueur+ebx]
;;------ pourle retour ici dans longtemps --
;cmp byte ptr [esi+4],''      ;pour ke ca soit retire ensuite...
;jne etreyytyyyuuuuuuuuuu
;mov byte ptr [esi+4],' '
;etreyytyyyuuuuuuuuuu:
;;-------------
;;--- pour la 2eme fois ou on passe la !! (juste apres :))
;cmp byte ptr [esi+4],'t'      ;pour ke ca soit retire ensuite...
;jne treyytyyyuuuuuuuuuu
;mov byte ptr [esi+4],''
;treyytyyyuuuuuuuuuu:
;;-----------------------------
;mov eax,dword ptr [nomdetriche]
;cmp dword ptr [esi],eax
;jne iiuiuiuoooooooooooooooooo
;mov eax,dword ptr [nomdetriche2]
;mov dword ptr [esi],eax
;mov byte ptr [esi+4],'t'
;popall
;mov [temps_joueur+ebx],temps_re_menu
;jmp finito_touches
;iiuiuiuoooooooooooooooooo:
;popall
;======================----------------------------------------------------------

bruit 3 40 fx

;on est sur le 3eme caracte !! finito !!

mov [name_joueur+ebx],4

mov eax,[control_joueur+ebx]

shr eax,6 ;/64
inc eax
add al,'0'

mov esi,offset nick_t
add esi,[control_joueur+ebx]
push eax
mov eax,[esi]

mov esi,offset message2
mov [esi],eax
mov [esi+32],eax
mov last_name,eax
pop eax
mov byte ptr [esi+16+32*2],al
mov byte ptr [esi+16+32*3],al
mov edi,offset texte1
add edi,edx
mov ecx,32
rep movsd


;dans ebx... nom— du mec... cas particulier...
;cmp ebx,'rmd '

pushall
xor ebx,ebx
xor ebp,ebp

enojjojortyrtyrtytyr:
mov eax,dword ptr [love_si+ebx]
cmp last_name,eax
jne nonon_
mov esi,[offset_si+ebp]
mov edi,offset texte1
add edi,edx
mov ecx,[offset_si+ebp+4]
rep movsd
mov eax,'FFFF' ;pour sortir
nonon_:
add ebp,8
add ebx,4
cmp eax,'FFFF'
jne enojjojortyrtyrtytyr
popall

jmp finito_touches
pas_flechedmy:

mov [temps_joueur+ebx],1
finito_touches:

ertterrtytyrrtyrtyrtyrtytuoooooooooo:
;-------------------

ms_dos:
add ebx,4
add edx,32*4
dec ebp
jnz ooooooooh
;name_joueur     dd 8 dup (?) ;pour dans le menu...

;name_joueur     dd 8 dup (?) ;pour dans le menu...
;0: pas encore inscrit.
;1: r‚cupere la premiere lettre
;2: r‚cupere la premiere lettre
;3: r‚cupere la troisieme lettre
;4: finis... attend de jouer
;temps_joueur   dd 8 dup (temps_re_menu) ;temps d'attente avant validation
                                        ;d'une nouvelle frappe de touche.
                                        ;dans menu...
yen_a_pas:
;--------------------------------------------------------

mov ebp,[nombre_de_dyna]
cmp ebp,8
je finito_trop_de_dyna

shl ebp,2 ;nombre de joueurs x4

mov esi,offset differents_offset_possible ;dans la table des offset du tas
                                          ; de touches.
eetterrterterterteertterertert:

mov ebx,[esi]
cmp ebx,666 ;fin...
je ok_on_en_a_trouve_un

cmp byte ptr [total_t+ebx+4],1
jne touche_non_appuyee

;---regarde si ce EBX n'est pas deja dans le control_joeur...
;   cmp byte ptr [esi+ebx+4],1

;jmp plusieur ;renegade ***********************

push ebp
or ebp,ebp
jz ca_roule_mon_coco
tretrrtrtrtrtrttr:
sub ebp,4
cmp [control_joueur+ebp],eBx
jne reetretrert
;et non on l'avait deja pris...
pop ebp
jmp touche_non_appuyee
reetretrert:
or ebp,ebp
jnz tretrrtrtrtrtrttr
ca_roule_mon_coco:
pop ebp
;--
plusieur:

mov dword ptr [control_joueur+ebp],ebx
inc [nombre_de_dyna]
push ds
pop es

;--- sonne

;a: sample, b:note

bruit 3 40 fx

; on va marquer le numero de l'ordy connect‚...

;mov eax,esi
;sub eax,offset differents_offset_possible
;shr eax,4
;inc eax
;add al,'0'
;mov ah,byte ptr [nombre_de_dyna]
;add ah,'0'

mov esi,offset message3 ;2

;mov byte ptr [esi+5],ah
;mov byte ptr [esi+5+32],ah
;mov byte ptr [esi+16+32*2],al
;mov byte ptr [esi+16+32*3],al

mov [name_joueur+ebp],1
mov edi,offset texte1
shl ebp,5 ;*32 (deja x4)
add edi,ebp
mov ecx,32
rep movsd
jmp ok_on_en_a_trouve_un

touche_non_appuyee:
add esi,4
jmp eetterrterterterteertterertert

finito_trop_de_dyna:
ok_on_en_a_trouve_un:
;----

popall
ret
menu_intelligence endp
controle_joueur_fleche proc near ;touches fleches
pushall
;75,77,80,72
mov ebx,[edi]
cmp byte ptr [clavier+ebx],1
jne erertertert
mov byte ptr [esi+2],1
erertertert:

mov ebx,[edi+4]
cmp byte ptr [clavier+ebx],1
jne erertertert2
mov byte  ptr  [esi+1],1
erertertert2:

mov ebx,[edi+8]
cmp byte ptr [clavier+ebx],1
jne erertertert3
mov byte  ptr  [esi],1
erertertert3:

mov ebx,[edi+12]
cmp byte ptr [clavier+ebx],1
jne erertertert4
mov byte  ptr  [esi+03],1
erertertert4:

mov ebx,[edi+16]
cmp byte ptr [clavier+ebx],1
jne erertertert45
mov  byte ptr  [esi+04],1
erertertert45:

mov ebx,[edi+20]
cmp byte ptr [clavier+ebx],1
jne ererterter45
mov byte ptr  [esi+05],1
ererterter45:

mov ebx,[edi+24]
cmp byte ptr [clavier+ebx],1
jne ererterter455
mov byte ptr  [esi+06],1
ererterter455:


;offset 0         =1 si la fleche bas est press‚/               j1
;       1         =1 si la fleche droite est press‚             j1
;       2         =1 si la fleche gauche est press‚             j1
;       3         =1 si la fleche haut est press‚2              j1
;       4         =1 bouton 1                                   j1
;       5         =1 bouton 2                                   j1


popall
ret
endp



gestion_jeu proc near ;uniquement appel‚ par le master.
pushall

;;cas particulier: terrain6 plus apres lapocalypse, pas de bonus
;decompte le tempos pendant lekel ya pas de bonus
;---
cmp special_nivo_6,0
je iophrehuiophuioeterterrte
dec special_nivo_6
iophrehuiophuioeterterrte:
;---

;************************************* refuse une pause tout de suite !!!

cmp action_replay,0
jne ytnononono_onest_en_recordplaye
cmp twice,1
jne ytnononono_onest_en_recordplaye
cmp nombre_de_vbl_avant_le_droit_de_poser_bombe,(nombre_de_vbl_avant_le_droit_de_poser_bombe2-10)/2
ja erteetetretrerterterter
jmp klhlkjljkjkljlkjkljkljklkljkljkljkljklj
ytnononono_onest_en_recordplaye:
cmp nombre_de_vbl_avant_le_droit_de_poser_bombe,nombre_de_vbl_avant_le_droit_de_poser_bombe2-10
ja erteetetretrerterterter
klhlkjljkjkljlkjkljkljklkljkljkljkljklj:

;mov byte ptr [esi],0
;mov [lapipipino3+ebp],duree_saut
;mov [lapipipino2+ebp],1
;mov [lapipipino6+ebp],1
;transformation homme -> lapin doit se faire uniqment ici. car ca serrait
;un demi-lapin dans le process sinon. clair ?
pushall
xor ebp,ebp
ertyrtyutyutyutyuioooppp:
cmp [lapipipino6+ebp],1
jne ertytyuyututyuyyuiyui
mov [lapipipino6+ebp],0
mov [lapipipino+ebp],1
mov [lapipipino3+ebp],duree_saut
mov [lapipipino2+ebp],1
ertytyuyututyuyyuiyui:

cmp [lapipipino6+ebp],2
jne ertytyuyututyuyyuiyuir
mov [lapipipino6+ebp],0
mov [lapipipino+ebp],0
mov [lapipipino3+ebp],0
mov [lapipipino2+ebp],0
ertytyuyututyuyyuiyuir:


add ebp,4
cmp ebp,4*8
jne ertyrtyutyutyutyuioooppp
popall
;
call gestion_pause
cmp pauseur2,0
je erteetetretrerterterter
call donnee_to_donnee4 ;passe de donne a donnee4
popall
ret
erteetetretrerterterter:
;******************

call transmet_central  ; transmet au CENTRAL les infos k'on vient de pomper.

SOUND_FAC BLOW_WHAT2

call dec_temps
call gestion_bdraw

cmp action_replay,0
jne nononono_onest_en_recordplaye
cmp twice,1
jne nononono_onest_en_recordplaye
cmp twice2,1
je nononono_onest_en_recordplaye
call dec_temps
call gestion_bdraw
nononono_onest_en_recordplaye:

call fabrique_monstro_truc
call gestion_blanchiment

call contamination ;contamination de dyna ?.

mov ecx,[nombre_de_dyna]
xor ebp,ebp ;--- bp: joeur en ce moment *4
brouter:
push ecx

mov esi,[liste_couleur+ebp] ;offset blanc ;esi: couleur du joeur...

call gestion_lapin

;------ patineur ----------------------------
cmp [patineur+ebp],0
je OooooOooooooOooooooooooOooooooooooOoooooo
call gestion_lapin
OooooOooooooOooooooooooOooooooooooOoooooo:
;--- maladie de la speed ---
cmp word ptr [maladie+ebp],01B
jne OooooOooooooOooooooooooOooooooooooOooooooe
call gestion_lapin
OooooOooooooOooooooooooOooooooooooOooooooe:

cmp action_replay,0
jne tnononono_onest_en_recordplaye
cmp twice,1
jne tnononono_onest_en_recordplaye
call gestion_lapin
tnononono_onest_en_recordplaye:



;-malade ???
cmp word ptr [maladie+ebp],0 ;malade ??? (en general)
je ertterterrterterte
cmp [lapipipino+ebp],0 ;lapin ?
jne ertterterrterterte ;si oui, on doit pas gerer le changement de couleur
                       ;ici...
test dword ptr [changement],0000000010000B
jnz ertterterrterterte
mov esi,[liste_couleur_malade+ebp]
ertterterrterterte:
;-----

call anim_un_joeur

cmp [vie+ebp],1
jne erertert
Call touches_action
call la_mort ;regarde si elle a frapp‚e. OU si on a mang‚ un BONUS...
erertert:

add ebp,4
pop ecx
dec ecx
jnz brouter
;dans ebp: viseur sur num‚ro du joeur. enfin du premier monstre
;------ il reste les m‚chants … g‚rer ---
cmp [nombre_de_monstres],0
je y_en_a_pas

mov ecx,[nombre_de_monstres]
;--- bp: joeur en ce moment *4
tbrouter:
push ecx

cmp [vie+ebp],1
jne  next_monstre

cmp [blocage+ebp],0
jne ertreteretterter
call intelligence_monstre
ertreteretterter:
call la_mort_monstre ;regarde si elle a frapp‚e.
next_monstre:
mov esi,[liste_couleur+ebp] ;offset blanc ;esi: couleur du joeur...
pushall
call anim_un_joeur
popall

cmp [vie+ebp],1
jne next_monstre2
cmp [blocage+ebp],0
jne next_monstre2

;---- si le monstre est mont‚ sur la flamme.. on lui dit pas bonne id‚e..
jmp anti_bomb_monstre
nonononononononon: ;retours anti_bomb pas sur une bombe...
;;si pas reussit a bouger. remet anciennes touches ...
cmp [avance+ebp],1 ;=0 si PAS reussit a bouger
je retererttZERer     ;=1 si reussit a bouger...
mov eax,[touches_save+ebp]
or  eax,128 ;fige...
mov [touches+ebp],eax
ouiuouiouiuoi: ;retours anti_bomb aletre rouge changement de CAP....
mov esi,[liste_couleur+ebp] ;offset blanc ;esi: couleur du joeur...
pushall
call anim_un_joeur
popall
retererttZERer:
next_monstre2:

add ebp,4
pop ecx
dec ecx
jnz tbrouter
y_en_a_pas:
;------------------------------------------

call minuteur ;pour les bombes... fauit le tic tic tic :)

call monsieur_bombe ;cr‚e l'affichage les bombes
call monsieur_brik
call calc_ombres
call phase ;draw game ??? fin machin ???

cmp byte ptr [ordre2],'' ;on ne fait pas ca si on a quitt‚ le jeu...
jne reertertertertert
call donnee_to_donnee4 ;passe de donne a donnee4
reertertertertert:

popall
ret
gestion_lapin:
  ;====== SPECIAL LE LASCAR EST UN MOTHAFUCKAAAA DE LAPINA (3lit3)
  cmp [lapipipino+ebp],1
  jne ertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuioe
  ;c'est un lapin

mov esi,[lapin_mania1+ebp] ; pointeur sur la bloc de position
                             ; du lapin normal
  ;c'est un lapin qui fait un saut vertical de lapin



;  cmp [lapipipino2+ebp],2 ;saut direction
;  je ertrterterteertzerzererzzer

  cmp [lapipipino2+ebp],0  ;lapin ki fait rien
  je ertrterterteert

;  cmp [lapipipino2+ebp],1 ;saut vertical ou mort du lapin
;  jne ertrterterteert ;lapin ki fait rien
  ertrterterteertzerzererzzer:

;..................... LAPIN QUI SAUTE ......................................

  mov [lapipipino4+ebp],0 ;hauteur du lapin (Y)
  mov [lapipipino5+ebp],0 ;hauteur du lapin (Y)

  ;decrementation du compteur saut
;  dec [lapipipino3+ebp]
;  jz ohohohohohohh
  dec [lapipipino3+ebp]
  jnz erterterterterertrterterteert
;ohohohohohohh:

;--- cas particulier lapin mort
  cmp [lapipipino2+ebp],3 ;mort
  jne rttyuooooooo
  mov [lapipipino6+ebp],2
  jmp ertrterterteert ;c pu un lapin ki saute (ou lapin mort..)
  rttyuooooooo:
;-------------
  mov [lapipipino2+ebp],0 ;arrete le saut
  jmp ertrterterteert ;c pu un lapin ki saute (ou lapin mort..)
  erterterterterertrterterteert:

  ;******************* lapin ki saute phase 1 ***********************
  cmp [lapipipino3+ebp],duree_saut-15 ;compteur dans le saut du lapin
  ja trtyrtyrtyrtyrtyrty
  cmp [lapipipino3+ebp],15            ;compteur dans le saut du lapin
  jb trtyrtyrtyrtyrtyrty

  cmp [lapipipino2+ebp],3    ;mort (cas particulier, esi, tjs le meme)
  je ertertertrterterteertzerzererzzerrtyrtrtyyrtrty
  mov esi,[lapin_mania3+ebp] ; milieu de saut
ertertertrterterteertzerzererzzerrtyrtrtyyrtrty:
  push eax ebx
  mov ebx,[lapipipino3+ebp] ;compteur dans le saut du lapin
  sub ebx,15
  add ebx,ebx
  xor eax,eax
  mov ax,[saut_de_lapin+ebx]
  cmp [lapipipino2+ebp],1 ;saut vertical
  jne ertrterterteertererer
  mov ax,[saut_de_lapin2+ebx]
  ertrterterteertererer:
  mov [lapipipino5+ebp],eax ;hauteur du lapin x1
  multiple_eax_par_320
  mov [lapipipino4+ebp],eax ;hauteur du lapin x320
  pop ebx eax

;********************************** lapin qui saute directionnellement
  ;---- deplace le lapin ---
  cmp [lapipipino3+ebp],duree_saut-15 ;compteur dans le saut du lapin
  je ertrterterteert
  cmp [lapipipino2+ebp],2 ;que lapin sautant dans une direction
  jne  ertrterterteert

  ;compteur a partir dukel on ne fait plus avancer le lapin 17 normallement
push eax
  mov eax,[lapipipino7+ebp]
  cmp [lapipipino3+ebp],eax
  jnb ertrterterteert_oooo
pop eax
jmp ertrterterteert
ertrterterteert_oooo:
pop eax

  push eax ebx
  mov ebx,ebp
  shr ebx,1
  ;mov ah,02h ;SUPER_SIGNE2 DB 0
  ;mov dl,13
  ;int 21h

;8: gauche
  mov eax,[touches+ebp]
  and eax,127
  cmp eax,8
  jne trrtertyrtytyrtyrrty
;donnee       dw 8 dup (?) ;x du dynablaster
;             dw 8 dup (?) ;y du dynablaster
  inc [donnee+ebx]
  trrtertyrtytyrtyrrty:
  cmp eax,16
  jne trrtertyrtytyrtyrrtyR
  dec [donnee+ebx]
  trrtertyrtytyrtyrrtyR:
  cmp eax,00
  jne trrtertyrtytyrtyrrtyy
;donnee       dw 8 dup (?) ;x du dynablaster
;             dw 8 dup (?) ;y du dynablaster
  inc [donnee+8*2+ebx]
  trrtertyrtytyrtyrrtyy:
  cmp eax,24
  jne trrtertyrtytyrtyrrtyRy
  dec [donnee+8*2+ebx]
  trrtertyrtytyrtyrrtyRy:
  pop ebx eax

pushall
push ebp
xy_to_offset
pop ebp
lea esi,[truc+eax]
mov [last_bomb+ebp],esi
popall
  jmp ertrterterteert
  ;-------------------------
  trtyrtyrtyrtyrtyrty:

;******************* LAPIN FASE SE COURBE (?) *

  cmp [lapipipino3+ebp],duree_saut-7
  ja trtyrtyrtyrtyrtyrtyu
  cmp [lapipipino3+ebp],7
  jb trtyrtyrtyrtyrtyrtyu
  mov esi,[lapin_mania4+ebp] ; preske normal
  jmp ertrterterteert
  trtyrtyrtyrtyrtyrtyu:
  mov esi,[lapin_mania2+ebp] ; se courbe
  ertrterterteert:

;----- lapin mort !!! ----
  cmp [lapipipino2+ebp],3    ;mort (cas particulier, esi, tjs le meme)
  jne  kertrterterteert

  push eax ebx
  mov ebx,[lapipipino3+ebp] ;compteur dans le saut du lapin
  add ebx,ebx
  xor eax,eax
  mov ax,[mort_de_lapin+ebx]
  mov [lapipipino5+ebp],eax ;hauteur du lapin x1
  multiple_eax_par_320
  mov [lapipipino4+ebp],eax ;hauteur du lapin x320
  mov esi,[lapin_mania5+ebp] ; pointeur sur la bloc de position
                             ; du lapin mort
  pop ebx eax
  kertrterterteert:
;---------------

  ertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuioe:
  ;====================================================

ret
gestion_pause:


;*******************************
;gestion, sprite

;pas de pause en action replay

cmp pauseur2,0
je pas_en_pauseer
test dword ptr [changement],0000000001111B
jnz pas_en_pauseer

xor ebx,ebx
mov bl,pauseur2
add ebx,4
cmp [offset_pause+ebx],666
jne ihhihiertteretr
mov ebx,4
ihhihiertteretr:
mov pauseur2,bl

pas_en_pauseer:


;*******************************

cmp pause2,0
je uerertertert
dec pause2
uerertertert:

cmp pause,1 ;touche vient d'etre touchee/relachee ?
jne raison_detat

;;------------- gestion sprite
;xor ebx,ebx
;mov bl,pause
;dec bl
;shl ebx,2
;
;add ebx,4
;cmp [offset_pause+ebx],666
;jne uiyuighguirrtrt
;xor ebx,ebx
;uiyuighguirrtrt:
;inc bl
;mov pause,bl
;;------------------------------

mov pause,0
cmp pause2,0
jne dejapresseyapaslongtemps
mov pause2,15
;pauseur2
;NOT pauseur2
cmp pauseur2,0
jne reeertertterert
mov pauseur2,4
jmp raison_detat
reeertertterert:
mov pauseur2,0
raison_detat:
dejapresseyapaslongtemps:
ret

anti_bomb_monstre:

cmp [invinsible+ebp],0
jne nonononononononon ;si il s'est prit dans la bombe il faut k'il se tretourne.
                     ;ou alors il resiste donc on s'en fou.
pushall
;cmp [avance+ebp],1 ;=0 si PAS reussit a bouger
;je reterertter     ;=1 si reussit a bouger...

push ebp
xy_to_offset
lea esi,[truc2+eax]
pop ebp

cmp byte ptr [esi],5
jb ertterertertertertt
cmp byte ptr [esi],54
jnb ertterertertertertt
mov [avance+ebp],0 ;=0 si PAS reussit a bouger. vaut mieu pas babe..
;+ mouvement inverse...
mov ebx,[touches+ebp]
and ebx,127 ;d‚fige...
mov eax,[anti_bomb+ebx]
mov [touches+ebp],eax
popall
jmp ouiuouiouiuoi
ertterertertertertt:
popall
jmp nonononononononon ;retours anti_bomb
intelligence_monstre:

mov esi,[infojoueur+ebp]
mov ecx,dword ptr [esi+12]
cmp ecx,1
jne pas_1i
test dword ptr [changement],00000000111B
jnz non_bouge_pasttryrtytyr
jmp ok_il_bougert
pas_1i:
cmp ecx,2
jne ok_il_bougert
test dword ptr [changement],00000000011B
jnz non_bouge_pasttryrtytyr
jmp ok_il_bougert
non_bouge_pasttryrtytyr:
ret
ok_il_bougert:
;1,2,3 (normal),4:double...

;--- intelligence ----

mov eax,[changement]
add eax,[avance2+ebp]          ;hazard
add eax,[viseur_change_in+ebp] ;hazard total...
add eax,[maladie+ebp]          ;hazard..
;add eax,dword ptr [donnee+ebp] ;hazard..
add eax,ebp ;nouveau hazard.. violent
and eax,01111111B
jnz alllagrishna

cmp [avance2+ebp],3 ;compte a rebourd avant nouvelle action...
jb arrete__
mov [avance2+ebp],3 ;compte a rebourd avant nouvelle action...
jmp arrete__
alllagrishna:

cmp [avance+ebp],1 ;=0 si PAS reussit a bouger
je reterertter     ;=1 si reussit a bouger...

;si reussit continue...
;pas reussit

arrete__:

dec [avance2+ebp] ;compte a rebourd avant nouvelle action...
jnz mendier
hier2:

mov [avance2+ebp],15

pushall
mov ebx,[viseur_change_in+ebp]
mov eax,[changeiny+ebx]
mov [touches+ebp],eax
add [viseur_change_in+ebp],4
cmp [viseur_change_in+ebp],16*4
jne retkortykokoptrkopkop
mov [viseur_change_in+ebp],0
retkortykokoptrkopkop:
popall
                      ;0= face        bas.
                      ;8= droite      droite
                      ;16= gauche     gauche
                      ;24= haut       haut

jmp mendier
reterertter:
mov eax,[touches+ebp] ;sauvegarde du dernier success d'un monstre...
mov [touches_save+ebp],eax
;------------------
mendier:
ret

donnee_to_donnee4:
PUSHALL
;POPALL
;push ecx


xor ecx,ecx ;0,nb_unite_donnee4,...
xor ebx,ebx ;0,2,4,
xor ebp,ebp ;0,4,8,12,...
;***
hooooooop:
;----- calcule dans edi le Y en le multipliant par 320

;;multiple_eax_par_320
;;mov [vise_de_ca_haut2+ebp],eax

xor eax,eax
mov ax,word ptr [donnee+nb_dyna*2+ebx] ;y
push eax
shl   eax,6 ; x 64
mov   edi,eax
pop eax
shl   eax,8 ; x 256
add   edi,eax
;-------------- rajoute le X
xor eax,eax
mov ax,word ptr [donnee+ebx]
add edi,eax
;---------------

  mov [vise_de_ca_haut+ebp],0
  mov [vise_de_ca_haut2+ebp],0
  ;====== SPECIAL LE LASCAR EST UN MOTHAFUCKAAAA DE LAPINA (3lit3)
  cmp [lapipipino+ebp],1
  jne ertrtyyuttyutyurtyutyutyuyutyut
  ;=== cas particulier: trop haut./ deborderait de l'ecran
  push eax
  xor eax,eax
  mov ax,word ptr [donnee+nb_dyna*2+ebx] ;y
  mov edx,[lapipipino5+ebp]
  add edx,13
  cmp ax,dx
  ja erertzertertertertertert

;combien_faut_baisser dd 320*14,320*13,320*12,320*11,320*10,320*9,320*8
;                    dd 320*7,320*6,320*5,320*4,320*3,320*2,320*1
;combien_faut_baisser2 dd 14,13,12,11,10,9,8
;                     dd 7,6,5,4,3,2,1

;push ebx

;push eax
neg eax
add eax,edx
inc eax
mov [vise_de_ca_haut2+ebp],eax
;pop eax

;mov [vise_de_ca_haut2+ebp],eax

;xor ebx,ebx
;shl ax,2
;mov bx,ax

;mov eax,[combien_faut_baisser2+ebx]
;mov [vise_de_ca_haut2+ebp],eax
;mov eax,[combien_faut_baisser+ebx]
multiple_eax_par_320
;mov [vise_de_ca_haut2+ebp],eax
;pop ebx
  add edi,eax ;320*14
  mov [vise_de_ca_haut+ebp],eax ;320*14
  erertzertertertertertert:
  pop eax
  ;=== attention au adder, faut pas kon le mette trop haut ================
  add edi,-14*320-4
  sub edi,[lapipipino4+ebp] ;saut du lapin (y)
  or edi,edi                                   ;!
  jns rterteerertertterteryuyyuuuuu            ;!
  add edi,[lapipipino4+ebp] ;saut du lapin (y) ;!
                                               ;!
  ;bon on bidouille !!
  push eax
  mov eax,[lapipipino4+ebp]
;  add [lapin_mania+ebp],eax ;pointeur sur la source memoire
;  add [vise_de_ca_haut+ebp],eax
  pop eax
  rterteerertertterteryuyyuuuuu:

  jmp tryrtyyrttyutyuyuttyutyutyutyutyutyutyu
  ertrtyyuttyutyurtyutyutyuyutyut: ;pas un lapin
  add edi,dword ptr [donnee+112+ebp] ;adder y.. (car girl plus gaut!!!)
  tryrtyyrttyutyuyuttyutyutyutyutyutyutyu:
  ;============
mov word ptr [donnee4+ecx+4],di
;---------------

;----- OFFSET EN MEMOIRE -------------
xor eax,eax
mov ax,word ptr [donnee+nb_dyna*4+ebx]

cmp ax,666 ;mort... et on affiche plus...
je reertertertrte
  ;====== SPECIAL LE LASCAR EST UN MOTHAFUCKAAAA DE LAPINA (3lit3)
  cmp [lapipipino+ebp],1
  jne ertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuio
  add eax,[vise_de_ca_haut+ebp] ;decalleur spoecial y

;--- glignotement des lapins malades ---
cmp word ptr [maladie+ebp],0 ;malade ??? (en general)
je ertterterrtertertertt
test dword ptr [changement],0000000010000B
jnz ertterterrtertertertt
  add eax,[lapin_mania_malade+ebp] ;pointeur sur la source memoire
  jmp reertertertrte
ertterterrtertertertt:
;------------------------------------------
  add eax,[lapin_mania+ebp] ;pointeur sur la source memoire
  jmp reertertertrte
  ertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuio:
  ;====================================================
add eax,dword ptr [donnee+8*2*3+ebp] ;ou en m‚moire!!!
reertertertrte:
mov dword ptr [donnee4+ecx],eax ;source... 666 indique: ne rien afficher

;---
mov ax,word ptr [donnee+8*5*2+ebx]
mov byte ptr [donnee4+6+ecx],al ;nombre de lignes...

mov ax,word ptr [donnee+8*6*2+ebx]
mov byte ptr [donnee4+7+ecx],al ;nombre de colonnes....
;---

  ;====== SPECIAL LE LASCAR EST UN MOTHAFUCKAAAA DE LAPINA (3lit3)
  cmp [lapipipino+ebp],1
  jne rertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuio
  push ax
  mov ax,37
  sub ax,word ptr [vise_de_ca_haut2+ebp]
  mov byte ptr [donnee4+6+ecx],al ;nombre de lignes...
  pop ax
  mov byte ptr [donnee4+7+ecx],32 ;nombre de colonnes....
  rertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuio:
  ;====================================================


;dw 23,23,23,23,25,25,25,25 ;nombre de lignes pour un dyna...
;mov si,word ptr [donnee+nb_dyna*2*2+ebx]
;xor ecx,ecx ;0,7,...
;xor ebx,ebx ;0,2,4,
;xor ebp,ebp ;0,4,8,12,...

mov eax,[clignotement+ebp] ;
and byte ptr [donnee4+8+ecx],011111110B
or byte ptr [donnee4+8+ecx],al

add ecx,nb_unite_donnee4
add ebx,2
add ebp,4
cmp ebp,4*8
jne hooooooop
POPALL
ret
;*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
la_mort: ;regarde si elle a frapp‚e. ou si on a mang‚ un bonus.
pushall
push ebp
xy_to_offset
lea esi,[truc2+eax]
pop ebp


;==== mort par brike sur la gueule ===
cmp [lapipipino+ebp],0 ;lapin ?
je nan_comme_dab
cmp [lapipipino2+ebp],0 ;lapin qui saute pas?
jne nan_laisse_tourner
cmp byte ptr [esi-32*13],11 ;regarde si c a la fin... brique sur la gueulle..
jne nan_laisse_tourner
mov [lapipipino2+ebp],3
mov [lapipipino3+ebp],duree_mort
jmp nan_laisse_tourner
nan_comme_dab:
cmp byte ptr [esi-32*13],11 ;regarde si c a la fin... brique sur la gueulle..
je microsoft
nan_laisse_tourner:
;==================================




cmp byte ptr [esi],5
jb ertterertertertert
cmp byte ptr [esi],54
jnb ertterertertertert

;invinsible    dd 8 dup (?) ;invincibilit‚. nombre de vbl restant ... d‚cr‚ment‚e... 0= none...
;nombre_de_coups dd 8 dup (3) ;avant la mort...

;r‚sistance aux coups/calcul...

resistance ertterertertertert 0

microsoft: ;LA c'est la mort.

;mort d'un dyna par flamme. ou brike sur la gueulle (de dayna)

;-- on lui ote le pouvoir d'explosion retarde ... (ca a deja du etre fait,
; sauf s'il est mort par apocalypse. donc on en remet une couche!)
push ebx ;et sinon ses bombes elles resteraient.
mov ebx,[infojoueur+ebp]
mov dword ptr [ebx+4*4],0
call nike_toutes_ses_bombes
pop ebx
;--------

bruit3 7 35 BLOW_WHAT2
mov [vie+ebp],0

ertterertertertert:

;regarde si on a mang‚ un bonus

;si on est un lapin en train de sauter on mange pas le bonus
cmp [lapipipino+ebp],0 ;lapin ?
je on_est_pas_un_lapin_on_mange_les_bonus
cmp [lapipipino5+ebp],0 ;en hauteur ?
jne baaaaaaaaaaaaaaaaaaaaaaaah_paas_de_bonus
on_est_pas_un_lapin_on_mange_les_bonus:

bonus_ 54 bombe_max 0
bonus_ 64 bombe_max2 4
bonus_tete 74
bonus_2 84 invinsibilite_bonus invinsible
bonus_2 94 1 nombre_de_coups
bonus_ 104 1 4*4
bonus_3 114 1 pousseur
bonus_3 124 1 patineur
;horloge
bonus_4 134
bonus_3 144 1 tribombe
bonus_6 154
;oeuf
bonus_5 193
baaaaaaaaaaaaaaaaaaaaaaaah_paas_de_bonus:

;--- regarde si un mechant nous a mang‚...
mov eax,[last_bomb+ebp]
cmp [nombre_de_monstres],0
je y_en_a_pas2
mov ebx,[nombre_de_dyna]
shl ebx,2

reetrertetert:
cmp [vie+ebx],1 ;si le mechant il est mort. ben il peut pas nous tuer...
jne pas_tue
cmp eax,[last_bomb+ebx]
jne pas_tue

;r‚sistance aux coups/calcul...
resistance pas_tue 0

;mort d'un dyna
bruit3 7 35 BLOW_WHAT2
mov [vie+ebp],0
pas_tue:
add ebx,4
cmp ebx,32
jne reetrertetert

y_en_a_pas2:

popall
ret

la_mort_monstre: ;regarde si elle a frapp‚e.
pushall
push ebp
xy_to_offset
lea esi,[truc2+eax]
pop ebp

cmp byte ptr [esi-32*13],11 ;regarde si c a la fin... brique sur la gueulle..
je microsoft2

cmp byte ptr [esi],5
jb uertterertertertert
cmp byte ptr [esi],54
jnb uertterertertertert

;r‚sistance aux coups/calcul...
resistance uertterertertertert -1

pushall
sub esi,32*13-1
;inc esi
colle_un_bonus viseur_hazard_bonus2 hazard_bonus2 correspondance_bonus2
popall


microsoft2:

;mort d'un monstre courageux.

bruit3 8 35 BLOW_WHAT2
mov [vie+ebp],0
uertterertertertert:
popall
ret


;----------------
anim_un_joeur:

cmp [vie+ebp],1
jne rtertterterrterte


                      ;0= face
                      ;8= droite
                      ;16= gauche
                      ;24= haut

  ;cas du lapin ki saute... ne bouge pas comme ca
 ; cmp [lapipipino+ebp],1
 ; jne ertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuioeertertert
 ; cmp [lapipipino2+ebp],1 ;saut vertical
 ; je rtrtyyrtrtytrytyrrty
 ; ertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuioeertertert:


cmp dword ptr [touches+ebp],128 ;on met le bit 7 a 1 si bouge pas.
jb  okbouge_pas
;on a un monstre/dyna ki ne se deplace pas..
;donc on ne le je fait pas gigoter.
; sauf cas particulier: monstre du nivo 7, et nivo micro !!
; ki gigottent tout le temps
and dword ptr [touches+ebp],127
add esi,[touches+ebp] ;variable en central ou ya une valeur pour chaque type
                      ;de deplacement pour un joeur et ceci pour TOUS les
                      ;joeurs...
                      ;les touches.
or  dword ptr [touches+ebp],128 ;remet le bit a 1

;----  cas particulier gigotage
cmp [nombre_de_dyna_x4],ebp ; uniquement si on est pas un humain...
ja non_c_pas_un_monstre2
cmp terrain,7
jne special_monstres_gigoteurs4
;*** c un cas particulier dans le cas particulier.. BIDOUILLE ATTENTION
;il faut ke ca soit des sprites ou les pieds bougent pas !!!
push ebx
xor eax,eax

;mov eax,[changement]
;and eax,0011000B
;shr eax,2

mov ebx,[changement]
;and ebx,0110000B
;shr ebx,3
and ebx,011000B
shr ebx,2

cmp bx,2
jne trhjllhjkrtlhjrhjkltyrlhjkrty
mov ax,-17*2
trhjllhjkrtlhjrhjkltyrlhjkrty:
cmp bx,6
jne trhjllhjkrtlhjrhjkltyrlhjkrty2
mov ax,-17
trhjllhjkrtlhjrhjkltyrlhjkrty2:
add ax,[esi]  ;;ATTENTION JE SUIS HARD CORE LA :))
pop ebx
jmp rtrtyyrtrtytrytyrrtyZERZERZERZER
;****
special_monstres_gigoteurs4:

cmp terrain,3
je special_monstres_gigoteurs
non_c_pas_un_monstre2:
jmp rtrtyyrtrtytrytyrrty
;--------
okbouge_pas:

;------------------------- TOUCHES INVERSEES -------------------------------
cmp [nombre_de_dyna_x4],ebp ; uniquement si on est un humain...
jna ui
cmp word ptr [maladie+ebp],4 ;touches invers‚e...
jne ui
cmp [touches+ebp],8
jne tyuo
mov [touches+ebp],16
jmp ui
tyuo:
cmp [touches+ebp],16
jne tyuu
mov [touches+ebp],8
jmp ui
tyuu:
cmp [touches+ebp],0
jne tyuo2
mov [touches+ebp],24
jmp ui
tyuo2:
cmp [touches+ebp],24
jne tyuu1
mov [touches+ebp],0
jmp ui
tyuu1:
ui:
;---------------------------------------------------------------------------

;---- lapin ... annule tous les direction si on est en train de sauter ---
;  cmp [lapipipino+ebp],1
;  jne rertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuioeertertert
;  cmp [lapipipino2+ebp],1 ;saut vertical
;  jne rertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuioeertertert
;  or  dword ptr [touches+ebp],128 ;remet le bit a 1
;  rertyrttyrrtytyuutyyuiyuiiyuyuityuioouiioyuuioyyuioeertertert:
;------


add esi,[touches+ebp] ;variable en central ou ya une valeur pour chaque type
                      ;de deplacement pour un joeur et ceci pour TOUS les
                      ;joeurs...
                      ;les touches.

;pour le deplacement...

;-------------- variation du sprite si il bouge... (gauche/droite.. )
special_monstres_gigoteurs:
;cmp [nombre_de_dyna_x4],ebp ; uniquement si on est un humain...
;ja non_c_pas_un_monstre

mov eax,[changement]

;--- c un monstre ??? -----
cmp [nombre_de_dyna_x4],ebp ; uniquement si on est pas un humain...
ja non_c_pas_un_monstre
push ecx ebx
mov ecx,[vitesse_monstre+ebp]
;----
cmp action_replay,0
jne eanononono_onest_en_recordplaye
cmp twice,1
jne eanononono_onest_en_recordplaye
inc ecx
eanononono_onest_en_recordplaye:
;-----

mov ebx,011B
shl ebx,cl
and eax,ebx
dec cl
shr eax,cl
pop ebx ecx
jmp eanononono_onest_en_recordplay
non_c_pas_un_monstre:
;----------------------
and eax,0110000B
shr eax,3
cmp [patineur+ebp],0 ;patineur cour 2 fois plus vite
je tryyyyyyyyyyytyuiouiiuoouiuiooui
mov eax,[changement]
and eax,0011000B
shr eax,2
tryyyyyyyyyyytyuiouiiuoouiuiooui:
;mode twice...--------------------
cmp action_replay,0
jne eanononono_onest_en_recordplay
cmp twice,1
jne eanononono_onest_en_recordplay
;cours 2 fois plus vite
mov eax,[changement]
and eax,0011000B
shr eax,2
eanononono_onest_en_recordplay:
;---------------------------------
add esi,eax
;----------------
rtrtyyrtrtytrytyrrty:

mov ax,[esi]

rtrtyyrtrtytrytyrrtyZERZERZERZER:
push ebp
shr ebp,1
mov [donnee+nb_dyna*4+ebp],ax ;variables en central contenant les infos completes
                          ;nivo affichage pour chaque joueur
                          ;X,Y,offset
pop ebp
;------------ regarde si le sprite se deplace... (X/Y)
cmp [touches+ebp],128 ;variable en central ou ya une valeur pour chaque type
jNB non_bouge_pas


;----- vitesse = normal.. + = + !!!

;infojoueur dd offset j1,offset j2,offset j3,offset j4,offset j5,offset j6,offset j7,offset j8
;premier dd: nombre de bombes que le joeur peut encore mettre.
;deuxieme dd:  puissance de ces bombes... minimum = 1 ...
;troisieme dd: nombre de tous avant que ca pete.
;quatrieme dd: vitesse du joeur... 1:normal...

mov esi,[infojoueur+ebp]
mov ecx,dword ptr [esi+12]

;1,2,3 (normal),4:double...

;-*-*-*-*-*-*-* GESTION vitesse -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
;---- modif..
cmp ecx,1
jne pas_1
test dword ptr [changement],00000000111B
jnz non_bouge_pas
;mov ecx,1
jmp finto_gestion_vitesse
pas_1:
cmp ecx,2
jne pas_2
test dword ptr [changement],00000000011B
jnz non_bouge_pas
mov ecx,1
jmp finto_gestion_vitesse
pas_2:
cmp ecx,3
jne pas_3
mov ecx,1
jmp finto_gestion_vitesse
pas_3:
cmp ecx,4
jne pas_4
mov ecx,2
jmp finto_gestion_vitesse
pas_4:
finto_gestion_vitesse:
;-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

;--- mode twice ------------
  cmp action_replay,0
  jne anononono_onest_en_recordplay
cmp twice,1
jne anononono_onest_en_recordplay
inc ecx
anononono_onest_en_recordplay:
;-------------------

;--- patins a roulettes ?
add ecx,[patineur+ebp]

;--- maladie de la speed ---
cmp word ptr [maladie+ebp],01B ;255 ; dd 8 dup (?)
jne ertertrterteterrteert2
add ecx,3
ertertrterteterrteert2:
;----------------------------


;;--- maladie de la lenteur ne marche pas sur le lapin !!!
;cmp [lapipipino+ebp],1
;je ertertrterteterrteert3
;--- maladie de la lenteur --
cmp word ptr [maladie+ebp],02 ;255 ; dd 8 dup (?)
jne ertertrterteterrteert3
test dword ptr [changement],00000000011B
jnz non_bouge_pas
ertertrterteterrteert3:
;----------------------------

;----------------------------
cmp [blocage+ebp],0
je  next_monstre2r2
dec [blocage+ebp]
jmp non_bouge_pas
next_monstre2r2:

;--------------------------------

mov [avance+ebp],1 ;reussit a bouger par d‚fault. (pour monstre)

ertertrterteterrteert:
push ECX


cmp [touches+ebp],8 ;*********** droite
jne ererterertert4
push ebp
shr ebp,1
;------ remet au milieu ----- Y-------------------------------
mov si,16
call remet_milieu_y
jz errteterertertrte3 ;on l'a remis au milieu...
;-------------------------------------------------------------
;dx add x, cx: add y
mov dx,8+1
mov cx,0
call possible_ou_pas
jnz errteterertertrte2 ;impossible
inc [donnee+ebp]
;add ebp,ebp
jmp errteterertertrte3
errteterertertrte2:
;---------------------------
push ebp
add ebp,ebp
mov [avance+ebp],0 ;PAS reussit a bouger apres avoir ‚t‚ replac‚. (pour monstre)
pop ebp
errteterertertrte3:
;-----------------------------
pop ebp
ererterertert4:



cmp [touches+ebp],16 ;*********** gauche
jne ererterertert4e
push ebp
shr ebp,1
;------ remet au milieu ----- Y-------------------------------
mov si,-16
call remet_milieu_y
jz errteterertertrte3e
;-------------------------------------------------------------
;dx add x, cx: add y
mov dx,-8
mov cx,0
call possible_ou_pas
jnz errteterertertrte2e ;impossible
dec [donnee+ebp]
;add ebp,ebp
jmp errteterertertrte3e
errteterertertrte2e:
;---------------------------
push ebp
add ebp,ebp
mov [avance+ebp],0 ;PAS reussit a bouger apres avoir ‚t‚ replac‚. (pour monstre)
pop ebp
errteterertertrte3e:
;-----------------------------


pop ebp
ererterertert4e:


cmp [touches+ebp],24 ;*********** haut
jne ererterertert4ey
push ebp
shr ebp,1
;------ remet au milieu ----- Y-------------------------------
mov si,-16 ; ;16 ;8
call remet_milieu_x
jz errteterertertrte3ey
;-------------------------------------------------------------
;dx add x, cx: add y
mov dx,0
mov cx,-8
call possible_ou_pas
jnz errteterertertrte2ey ;impossible
dec [donnee+nb_dyna*2+ebp]
;add ebp,ebp
;errteterertertrte2ey:
jmp errteterertertrte3ey
errteterertertrte2ey:
;---------------------------
push ebp
add ebp,ebp
mov [avance+ebp],0 ;PAS reussit a bouger apres avoir ‚t‚ replac‚. (pour monstre)
pop ebp
errteterertertrte3ey:
;-----------------------------


pop ebp
ererterertert4ey:

cmp [touches+ebp],0 ;*********** bas
jne ererterertert4eyt
push ebp
shr ebp,1
;------ remet au milieu ----- Y-------------------------------
mov si,16
call remet_milieu_x
jz errteterertertrte3eyt
;-------------------------------------------------------------
;dx add x, cx: add y
mov dx,0
mov cx,8+1
call possible_ou_pas
jnz errteterertertrte2eyt ;impossible
inc [donnee+nb_dyna*2+ebp]
;add ebp,ebp
jmp errteterertertrte3eyt
errteterertertrte2eyt:
;---------------------------
push ebp
add ebp,ebp
mov [avance+ebp],0 ;PAS reussit a bouger apres avoir ‚t‚ replac‚. (pour monstre)
pop ebp
errteterertertrte3eyt:
;-----------------------------
pop ebp
ererterertert4eyt:


;----- vitesse/. 1 = normal.. + = + !!!
pop  ECX
dec ecx
jnz ertertrterteterrteert

;
pushall
push ebp
xy_to_offset
pop ebp
lea esi,[truc+eax]
mov [last_bomb+ebp],esi
popall

non_bouge_pas:

ret

;dead dyna.
rtertterterrterte:
;add esi,32 ;[vie+ebp]
;add esi,[vie+ebp]
;add esi,0 ;32
add esi,[vie+ebp]
mov ax,[esi+32]
push ebp
shr ebp,1
mov [donnee+nb_dyna*4+ebp],ax
pop ebp

mov eax,[changement]
and eax,000000111B
jnz ertterrteertrterteertrte
cmp dword ptr [vie+ebp],16 ;8*2
je ertterrteertrterteertrte
add dword ptr [vie+ebp],2
ertterrteertrterteertrte:
ret


monsieur_brik:

;--------------- gestion des briques ---------------------------------
;briques dw 3,0,0,0,32,0,64
mov ax,ds
mov es,ax

mov esi,offset truc
mov edi,offset briques+2

xor cx,cx
xor eax,eax

mov bx,8 ;offset dans buffer destionation auquel la case correspond...

mov dx,13
rettertyutyuuityyuityuityuiyuiyuiyui:

push dx

mov dx,19
reertertertertertreerertert:
xor ax,ax
lodsb
or al,al
jz zererrte
cmp al,1
je zererrte
cmp al,66
je zererrte

cmp al,2
je ertrtyrtytyytutyutyuuty
;--- rajout de brique dure pour la fin...
cmp al,11
jne nonononono

xor ax,ax

push ebx
xor ebx,ebx
mov bl,terrain
dec bl
add ebx,ebx
mov ax,[kel_viseur_brike_fin+ebx]
pop ebx

jmp brique_dure_rajout‚e
nonononono:
;----------------
;cmp [terrain],2 ;pas ce cas particulier avec la neige...
;jne retterterertertertertertertertertertertertret
test dword ptr [changement],00000000011B
jnz erertrteertert
;j,z rteterterrterterterte
;retterterertertertertertertertertertertertret:
;
;cmp [terrain],4 ;pas ce cas particulier avec la foret
;jne retterterertertertertertertertertertertertret5
;test dword ptr [changement],00000000011B
;jz rteterterrterterterte
;retterterertertertertertertertertertertertret5:
;
;test dword ptr [changement],00000000111B
;jnz erertrteertert
;rteterterrterterterte: ;cas particulier neige  + foret

inc byte ptr [esi-1]

cmp byte ptr [esi-1],11
jne erertrteertert
mov byte ptr [esi-1],0

colle_un_bonus viseur_hazard_bonus hazard_bonus correspondance_bonus

erertrteertert:

ertrtyrtytyytutyutyuuty:


sub ax,2
shl ax,4

;------ affiche brique diff‚rentes en fonction du terrain...
push ebx
xor ebx,ebx
mov bl,[terrain] ;offset_briques dw 0,0,65+116*320
dec bl
add bx,bx
add ax,word ptr [offset_briques+ebx]
pop ebx
;-----------------

brique_dure_rajout‚e:
inc cx
;add ax,320*16*2
stosw
;--------------------
mov ax,bx
stosw
ertteretretrertrte:

zererrte:
add bx,16
rettertertertert:
;*************************************************************************
dec dx
jnz reertertertertertreerertert
pop dx
add esi,13
add bx,320*16-16*19
dec dx
jnz rettertyutyuuityyuityuityuiyuiyuiyui

mov [briques],cx

;truc    db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,1,2,1,2,1,0,1,0,1,0,1,0,1,0,1,0,1,13 dup (0)
;        db 1,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,1,2,1,2,1,0,1,0,1,0,1,0,1,0,1,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,13 dup (0)
;        db 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,13 dup (0)
;        db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (0)



ret


monsieur_bombe:

;briques dw 3,0,0,0,32,0,64
mov ax,ds
mov es,ax

mov esi,offset truc2
mov edi,offset bombes+2

xor cx,cx
xor eax,eax

mov bx,8 ;offset dans buffer destionation auquel la case correspond...

mov dx,13
trettertyutyuuityyuityuityuiyuiyuiyui:

push dx

mov dx,19
treertertertertertreerertert:
xor ax,ax
lodsb
or al,al
jz tzererrte


cmp al,5
jnb ftttrrtrtyyrtyrtrtyrtytyrrtyrtyrtyrtyrty
;******************************************** bombe qui respire...
test dword ptr [changement],00000001111B
jnz terertrteertert
inc byte ptr [esi-1]
cmp byte ptr [esi-1],5
jne terertrteertert
mov byte ptr [esi-1],1
terertrteertert:
inc cx
dec ax
shl ax,4
add ax,320*16
stosw

;add ax,
;add byte ptr [esi-1],5
;mov

;--- special bombes... adder X/Y
push cx
xor ax,ax
movsx ax,byte ptr [esi-1+32*13] ;trux_X
add   ax,bx

movsx cx,byte ptr [esi-1+32*13*2] ;trux_Y
push ax
mov ax,cx
shl ax,6 ;*64
shl cx,8 ;*256
add cx,ax
pop ax
add ax,cx
stosw
pop cx
jmp tzererrte
tertteretretrertrte:
;*************************************************
ftttrrtrtyyrtyrtrtyrtytyrrtyrtyrtyrtyrty:

;***************************************************************************

bombe 12
bombe 12+7
bombe 12+7+7
bombe 12+7+7+7
bombe 12+7+7+7+7
bombe 12+7+7+7+7+7
bombe 12+7+7+7+7+7+7

;----- bonus

bonus 64 160
bonus 74 160+320*16
bonus 84 160+320*32
bonus 94 160+320*48
bonus 104 160+320*16*4
bonus 114 160+320*16*5
bonus 124 160+320*16*6
bonus 134 160+320*16*7
bonus 144 160+320*16*8
bonus 154 160+320*16*9
bonus 164 0
;----- bonus qui explose...
oeuf_bonus  193 112+16*320
explo_bonus 194+7 0+172*320

tzererrte:

;***************************************************************************

add bx,16
trettertertertert:
;*************************************************************************
dec dx
jnz treertertertertertreerertert
pop dx
add esi,13
add bx,320*16-16*19
dec dx
jnz trettertyutyuuityyuityuityuiyuiyuiyui

mov [bombes],cx
ret

touches_action: ;--- bp: joeur en ce moment *4
PUSHALL

;-pour par k'on pose une bombe au d‚but tout de suite kan meme...
cmp nombre_de_vbl_avant_le_droit_de_poser_bombe,0
je okokokok_pas_debut
dec nombre_de_vbl_avant_le_droit_de_poser_bombe
jmp treteterrterteterertter
okokokok_pas_debut:
;--------------
cmp [attente_avant_med],attente_avant_med2   ;uniquement si le processus
jb treteterrterteterertter                   ;de medaille est pas sur le point
                                             ;d'avoir lieu... plus de
                                             ; bombes

;--- maladie de la chiasse...
cmp word ptr [maladie+ebp],03 ;255 ; dd 8 dup (?)
je ertertrterteterrteert2rttyrrty
;---------------------------

inc [tribombe2+ebp]
;--- maladie de la constipation
cmp word ptr [maladie+ebp],05
je  treteterrterteterertter
;---------------------------

;----- touche action 1 ---
cmp byte ptr [ACTION+ebp],1
jne treteterrterteterertter
;------------------------
ertertrterteterrteert2rttyrrty:


;regarde si on peut poser une bombe...
mov edi,[infojoueur+ebp] ;dans edi: viseur sur l'info d'un joueur.
cmp dword ptr [edi],0  ;nombre de bombes qu'il peut encore poser.
je  treteterrterteterertter
push ebp
xy_to_offset
pop ebp
lea esi,[truc2+eax]

cmp byte ptr [esi],0 ;regarde si ya rien ou l'on veut placer la bombe
jne ya_une_bombeici
    pushall
    pose_une_bombe
    popall
jmp treteterrterteterertter
ya_une_bombeici:
cmp [tribombe+ebp],0 ;que si on a le bonus
je treteterrterteterertter
cmp [tribombe2+ebp],20
ja treteterrterteterertter
cmp [tribombe2+ebp],2
ja ttrrttreteterrterteterertter
mov [tribombe2+ebp],0 ;remet a zero si on presse tjs
jmp treteterrterteterertter
ttrrttreteterrterteterertter:

;utilise Esi par rapport a truc2 pour gauche/droite.
bruit2 9 34 BLOW_WHAT2 ;bruit du bonus tri bombe.

;2eme generation
;sortie: ebx entree ebp...
direction_du_joueur 1

  pushall ;(1)

encore_une_toto:

cmp dword ptr [edi],0  ;nombre de bombes qu'il peut encore poser.
jne nan_c_bon_on_peut_encore_poser
  popall  ;(1)
jmp treteterrterteterertter
nan_c_bon_on_peut_encore_poser:

   add esi,ebx
   add eax,ebx
    cmp byte ptr [esi],0 ;regarde si ya rien ou l'on veut placer la bombe
    je ici_toto
  popall  ;(1)
jmp treteterrterteterertter
    ici_toto:
    cmp byte ptr [esi-32*13],0 ;regarde si ya rien ou l'on veut placer la bombe
    je ici_toto2
  popall  ;(1)
jmp treteterrterteterertter
    ici_toto2:

       pushall
        pose_une_bombe
       popall
jmp encore_une_toto
treteterrterteterertter:


;---------- touche action 2 -----------
;***
;pushall
;mov ah,02h ;SUPER_SIGNE2 DB 0
;mov dl,13
;int 21h
;xor eax,eax
;shr ebp,1
;mov ax,word ptr [donnee+nb_dyna*2+ebp] ;recup Y
;add ax,14
;and ax,00000000000001111B
;call affsigne
;popall
;***


pushall
cmp byte ptr [ACTION+2+ebp],1
jne treteterrterteterertteruiotyterertertterert
;2 possibilites vertical ou pas vertical


  cmp [lapipipino+ebp],0
  je treteterrterteterertteruiotyterertertterert
  cmp [lapipipino2+ebp],0
  jne treteterrterteterertteruiotyterertertterert

;saut de lapin le lapin...
bruit3 10 32 BLOW_WHAT2 ;bruit kan 1 lapin saute

;sortie: ebx entree ebp...
direction_du_joueur 2

push ebp ebx
xy_to_offset
lea esi,[truc+eax]
pop ebx ebp

mov [lapipipino3+ebp],duree_saut
mov [lapipipino2+ebp],1 ;saut vertical


;cas particulier: le lapin est ;en bas
cmp ebx,32*2
jne ertytyyuttyuyuiyuiiyyuiiyuiyu2
cmp eax,32*10
ja erterererererertert
ertytyyuttyuyuiyuiiyyuiiyuiyu2:

;cas particulier: le lapin est en haut:
cmp ebx,-32*2
jne ertytyyuttyuyuiyuiiyyuiiyuiyuo
cmp eax,32*2
jb erterererererertert
ertytyyuttyuyuiyuiiyyuiiyuiyuo:

;========== cas pqrticulier: on veut sauter une brike ==========
;il ne faut pas ke lon soit pas au milieu d'une brike
cmp ebx,-32*2
jne biooooiiii
cmp byte ptr [esi+ebx+32],0 ;une brike ?
je biooooiiii
au_milieu_y2 erterererererertert2
biooooiiii:
cmp ebx,32*2
jne biooooiiiiE2
cmp byte ptr [esi+ebx-32],0 ;une brike ?
je biooooiiiiE2
au_milieu_y2 erterererererertert2
biooooiiiiE2:
cmp ebx,2
jne biooooiiiiE24
cmp byte ptr [esi+ebx-1],0 ;une brike ?
je biooooiiiiE24
au_milieu_X2 erterererererertert2
biooooiiiiE24:
cmp ebx,-2
jne biooooiiiiE24y
cmp byte ptr [esi+ebx+1],0 ;une brike ?
je biooooiiiiE24y
au_milieu_X2 erterererererertert2
biooooiiiiE24y:
;)===================================================================


;---------------------------------------


cmp byte ptr [esi+ebx],0 ;si ya rien a l'endroit ou on va sauter
jne erterererererertert

;-- 3 cases a gauche
cmp ebx,-2
jne iuertytyyuttyuyuiyuiiyyuiiyuiyu

;--- si on est pas au milieu de la case en Y il faut verif ke on peut sauter
au_milieu_y

;la place est pas libre en face
;cmp [touches+ebp],128 ;si on avance pas
;jb  herterererererertert ;on saute a la verticale
;mov [lapipipino2+ebp],1 ;saut vertical
;jmp erterererererertert
;herterererererertert:
;mov [lapipipino3+ebp],0
;mov [lapipipino2+ebp],0 ;pƒs de saut
;jmp treteterrterteterertteruiotyterertertterert
;
;erterererererertertYUTYUyutyuu:

; pour etre sur kon va pas avancer sur cette case
;-- si elle est dur en effet on pourrait deborder
push eax
push ebp
shr ebp,1
xor eax,eax
mov ax,word ptr [donnee+ebp] ;recup X
add ax,3
and ax,1111B
pop ebp
cmp byte ptr [esi+ebx-1],0 ;pas vide a 3 cases a gauche
je iuokeeey
cmp ax,7
ja iuokeeey
push eax
sub eax,7
sub [lapipipino7+ebp],eax
pop eax
iuokeeey:
pop eax
iuertytyyuttyuyuiyuiiyyuiiyuiyu:
;------

;-- 3 cases a droite
; pour etre sur kon va pas avancer sur cette case
;-- si elle est dur en effet on pourrait deborder
cmp ebx,+2
jne iiuertytyyuttyuyuiyuiiyyuiiyuiyu

;--- si on est pas au milieu de la case en Y il faut verif ke on peut sauter
au_milieu_y
;------------------------------

push eax
push ebp
shr ebp,1
xor eax,eax
mov ax,word ptr [donnee+ebp] ;recup X
add ax,3
and ax,1111B
pop ebp
cmp byte ptr [esi+ebx+1],0 ;pas vide a 3 cases a gauche
je iiuokeeey
cmp ax,8
jb iiuokeeey
push eax
sub eax,7
add [lapipipino7+ebp],eax
pop eax
iiuokeeey:
pop eax
iiuertytyyuttyuyuiyuiiyyuiiyuiyu:
;------

;en bas ???
; pour etre sur kon va pas avancer sur cette case
;-- si elle est dur en effet on pourrait deborder
cmp ebx,32*2
jne nooooooooooooooooooooi
;saut vers le bas, avec truc dur a 3 cases dessous

;--- si on est pas au milieu de la case en X il faut verif ke on peut sauter
au_milieu_x



;;---- donc on regarde si ya du dur juste en dessous de lendroit ========
;;     ou on va atterir, car on pourrait deborder...
;; ou on va arriver
push eax
push ebp
shr ebp,1
xor eax,eax
mov ax,word ptr [donnee+nb_dyna*2+ebp] ;recup Y
add ax,14
and ax,00000000000001111B
pop ebp
cmp byte ptr [esi+ebx+32],0 ;pas vide a 3 cases en dessous ?
je uokeeey
cmp ax,8
jb uokeeey
push eax
sub eax,7
add [lapipipino7+ebp],eax
pop eax
uokeeey:
pop eax
nooooooooooooooooooooi:

;en haut
; pour etre sur kon va pas avancer sur cette case
;-- si elle est dur en effet on pourrait deborder
cmp ebx,-32*2 ;en haut
jne knooooooooooooooooooooi

;--- si on est pas au milieu de la case en X il faut verif ke on peut sauter
au_milieu_x

;saut vers le bas, avec truc dur a 3 cases dessous
;;---- donc on regarde si ya du dur juste en dessous de lendroit ========
;;     ou on va atterir, car on pourrait deborder...
;; ou on va arriver
push eax
push ebp
shr ebp,1
xor eax,eax
mov ax,word ptr [donnee+nb_dyna*2+ebp] ;recup Y
add ax,14
and ax,00000000000001111B
pop ebp
cmp byte ptr [esi+ebx-32],0 ;pas vide a 3 cases au dessus
je kuokeeey                 ;pour cas particulier, on est avance vers le
cmp ax,7                    ;bas... donc on serra avance sur une case dure
ja kuokeeey
  push eax
  sub eax,7
  neg eax
  add [lapipipino7+ebp],eax
  pop eax
kuokeeey:
pop eax
knooooooooooooooooooooi:
;;---===================================================================

erterererererertert:
jmp baaaaaaaaaaa
erterererererertert2:   ;pour pas sauter a la verticale,dans tous les cas
cmp [touches+ebp],127   ;si on avance pas
ja baaaaaaaaaaa         ;on saute a la verticale
mov [lapipipino3+ebp],0
mov [lapipipino2+ebp],0
baaaaaaaaaaa:
;--------

treteterrterteterertteruiotyterertertterert:
popall

mov ebx,[infojoueur+ebp] ;uniquement s'il y a droit...
cmp dword ptr [ebx+4*4],1
jne treteterrterteterertteruioty

cmp byte ptr [ACTION+1+ebp],1
jne treteterrterteterertteruioty
;liste_bombe dd ? ; nombre de bombes...
;            dd 247 dup (?,?,?,?)
mov ecx,[liste_bombe]
or ecx,ecx
jz pasdutout
lea esi,liste_bombe+4-taille_dune_info_bombe
next_bomby:
add esi,taille_dune_info_bombe
cmp dword ptr [esi+4],0
jne ya_bombe_ici
jmp next_bomby
ya_bombe_ici:
;------- unqieuemnt si c'est notre propre bombe...
mov ebx,[infojoueur+ebp]
cmp dword ptr [esi],ebx
jne non_dejar
;--------- uniquement si cette bombe est a retardement...
cmp word ptr [esi+4*3+2],0
je non_dejar
mov word ptr [esi+4*3+2],0 ;la transforme en bombe normalle
mov dword ptr [esi+4],1    ;la fait exploser
non_dejar:
dec ecx
jnz next_bomby
pasdutout:
;1er: offset de l'infojoeur
;2eme: nombre de tours avant que ca PETE !!! ; si = 0 ca veut dire
;                                            ;emplacement libre...
;3eme:distance par rapport au debut de truc2
;4eme puissance de la bombe.
treteterrterteterertteruioty:
;-----------------------------------------

POPALL
ret

minuteur: ;le tic tic tic des bombes...+ deplacement
PUSHALL

mov ecx,[liste_bombe]
or ecx,ecx
jz ertrteertertrterteertertertrteertertert
xor ebp,ebp

tetrrtyrtyrtyrtyrtyrtytyrtyr:
cmp dword ptr [liste_bombe+ebp+4+1*4],0 ;indique emplacement non remplis !!!
jne rtytyrrtytyrtyuutyiyuuiouiopuiouiopioppiopiopp2
inc ecx
jmp rtytyrrtytyrtyuutyiyuuiouiopuiouiopioppiopiopp
rtytyrrtytyrtyuutyiyuuiouiopuiouiopioppiopiopp2:

;*****-*-*-------********----------POUSSER DEPLACEMENT *-*-*********------

;add esi,[liste_bombe+ebp+4+2*4]  ;distance par rapport au debut de truc2
;mov word ptr [liste_bombe+ebx+4+4*4],1 ;adder X automatique.
;mov word ptr [liste_bombe+ebx+4+4*4+2],0
;mov word ptr [liste_bombe+ebx+4+5*4],0   ;adder X
;mov word ptr [liste_bombe+ebx+4+5*4+2],0 ;adder Y
;movsx eax,word ptr [liste_bombe+ebp+4+4*4] ;force d'addage.. (+1 ou -1)
;or  eax,eax
;je non_zero ;pas de force de deplacement X/Y
;add ebx,1 ;eax                     ;offset dans truc+addage
;--- r‚flechis au deplacement uniquement si on est a 0 en adder...
;cmp word ptr [liste_bombe+ebp+4+5*4],0
;jne depeplacement_kan_mee
;cmp byte ptr [truc+ebx],0
;jne non_ya_un_mur_ote ;mur a cote...
;depeplacement_kan_mee:
;on deplace....
;jne nan_nan_normale

;xy_adder 0 ou 2
;xy_x32   1 ou 32

;truc_monstre db 32*13 dup (?)

call deplacement_bombes


cmp action_replay,0
jne nononono_onest_en_recordplayzrezerzeezr
cmp twice,1
jne nononono_onest_en_recordplayzrezerzeezr
call deplacement_bombes
nononono_onest_en_recordplayzrezerzeezr:

;mov word ptr [liste_bombe+ebp+4+5*4],-7
;-----------
;mov ax,word ptr [liste_bombe+ebp+4+5*4]
;mov ebx,[liste_bombe+ebp+4+2*4]
;mov byte ptr [truc_X+ebx],al
;jmp okey_abe
;mov word ptr [liste_bombe+ebp+4+4*4],0
;okey_abe:
;non_zero:

;------------------ sauf si on a les bombes a retardement
;liste_bombe dd ? ; nombre de bombes...
;            dd 247 dup (?,?,?,?)
;1er: offset de l'infojoeur
;2eme: nombre de tours avant que ca PETE !!! ; si = 0 ca veut dire
;3eme:distance par rapport au debut de truc2
;4eme:DD= 1 DW: puissance de la bombe + 1 DW: bombe a retardement ??? (=1)

;mov ebx,[liste_bombe+ebp+4]
;cmp dword ptr [ebx+4*4],1

mov esi,offset truc2
add esi,[liste_bombe+ebp+4+2*4]  ;distance par rapport au debut de truc2

;---- cas particulier.. on est une bombe, est on vient de se prendre
;une brike sur la gueule... donc on explose...
cmp byte ptr [esi-32*13],11 ;cas particulier... apres apocalypse...
jne kklmjjkjklmklmjmjklmjklmjklmjkl
;on la fait exploser de suite...
mov dword ptr [liste_bombe+ebp+4+1*4],1 ;pour ke ca pete :))
mov word ptr [liste_bombe+ebp+4+3*4+2],0 ;elle est plus retarde (enfin
                                         ;plus.. maintenant. si elle l'etait)
jmp finis_la
kklmjjkjklmklmjmjklmjklmjklmjkl:
;----

cmp word ptr [liste_bombe+ebp+4+3*4+2],1 ;si bombe retardee...
je rertertertert                         ;ne decremente pas

finis_la:
dec dword ptr [liste_bombe+ebp+4+1*4]
jnz rertertertert

dec dword ptr [liste_bombe]
;------------ fait exploser la bombe -------------------------------------
;bruit 1 40 BLOW_WHAT2

cmp byte ptr [esi-32*13],11 ;cas particulier... apres apocalypse...
je nononononiioiouuio
mov byte ptr [esi],05 ;centre.
bruit2 2 40
nononononiioiouuio:

mov eax,[liste_bombe+ebp+4+0*4] ;offset de l'infojoeur
inc dword ptr [eax] ;augmente le nombre de bombe k'il a le droit de poser...
;,explosion ; -32 33 40

cmp byte ptr [esi-32*13],11 ;cas particulier... apres apocalypse... (pice dure)
je nononononiioiouuiorytrty
explosion -32 33 40
explosion 32 33 47
explosion 1 12 26
explosion -1 12 19
nononononiioiouuiorytrty:

;mov dword ptr [liste_bombe+ebp+4+3*4]
mov dword ptr [liste_bombe+ebp+4+0*4],0
mov dword ptr [liste_bombe+ebp+4+1*4],0
mov dword ptr [liste_bombe+ebp+4+2*4],0
mov dword ptr [liste_bombe+ebp+4+3*4],0
mov dword ptr [liste_bombe+ebp+4+4*4],0
mov dword ptr [liste_bombe+ebp+4+5*4],0

;----------------------------------------------------------------------
rertertertert:

rtytyrrtytyrtyuutyiyuuiouiopuiouiopioppiopiopp:
add ebp,taille_dune_info_bombe
dec ecx
jnz tetrrtyrtyrtyrtyrtyrtytyrtyr

ertrteertertrterteertertertrteertertert:

POPALL
ret
;ya un draw game ??? ou une victoire ???
;mov ecx,8
;mov edi,offset victoires
;xor eax,eax
;rep stosd

phase:
pushad

;-- special... draw forc‚ ---
cmp word ptr bdraw666,'99'
je dikgrhrfhgrrethghkgh

mov edi,offset vie
mov ecx,[nombre_de_dyna]
yretrteertertert:
cmp dword ptr [edi],1
je et_non_pas_de_draw
add edi,4
dec ecx
jnz yretrteertertert

;-------- si on est au temps = 0 on compte moins vite !!!!
;car c le bordel faut k'on ai le temps de voir...

;;cmp in_the_apocalypse,1
;;je pas_encore
;;----------------------
dec [attente_avant_draw]
jnz pas_encore
dikgrhrfhgrrethghkgh:
mov byte ptr [ordre2],'D'
pas_encore:
et_non_pas_de_draw:
;----------------------------- ya une victoire ???? ----------------------

xor ebx,ebx
xor edx,edx
xor edi,edi
mov eax,-1 ;equipe du dernier a avoir gagne..
mov ecx,[nombre_de_dyna]
uyretrteertertert:
cmp dword ptr [vie+edi],1
jne uil_est_mort

;team      dd 0,1,2,3,4,5,6,7
cmp eax,[team+edi] ;si deja un gagnant de cette ‚quipe. on le compte pas.
je deja_dernier_un_gagnant_comme_ca
inc edx ;------- nombre de gagnants
mov eax,[team+edi] ;recup dans eax la team du gagnant...
mov ebx,edi ;sauvegarde du gagnant.
deja_dernier_un_gagnant_comme_ca:
uil_est_mort:
add edi,4
dec ecx
jnz uyretrteertertert

cmp edx,1
jne terertyrtytyrrtyrty
; plus k'1 EQUIPE vivante... !!! !
; regarde si ya plus de bombes....

;dans eax on a l'equipe du gagnat
push eax
;-- transforme les bombes en semi-retardee
push ebx
xor ebx,ebx
ertterertuuuuu:
push ebx
mov ebx,[infojoueur+ebx]
;mov dword ptr [ebx+4*4],0
call nike_toutes_ses_bombes
pop ebx
add ebx,4
cmp ebx,16
jne ertterertuuuuu
pop ebx
;--------
pop eax

; juste pour la premiere fois... pour k'on ne pose plus de bombes.
cmp [attente_avant_med],attente_avant_med2
jne reterertertertr89
mov [attente_avant_med],attente_avant_med2-1
reterertertertr89:


;cmp word ptr [bombes],0
;jne terertyrtytyrrtyrty
mov esi,offset truc2
mov ecx,32*13
zertertrtertetyrtyutyuiuiy:
cmp byte ptr [esi],0
je terertyrtytyrrtyrtyert
cmp byte ptr [esi],54
jb terertyrtytyrrtyrty ;bombe trouv‚e...
terertyrtytyrrtyrtyert:
inc esi
dec ecx
jnz zertertrtertetyrtyutyuiuiy
;truc2   db 32*13 dup (?)
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

;---------- regarde si on est dans un terrain ou il faut attendre ke l'apocalypse
;           soit terminee pour determiner un gagnant.
push ebx
mov bl,terrain
dec bl
shl ebx,2
cmp [ebx+kelle_fin],0
je pas_attente_fin_apocalypse
pop ebx
cmp in_the_apocalypse,1 ;c'est encore l'apo. decompte pas encore.
je terertyrtytyrrtyrty
push ebx
pas_attente_fin_apocalypse:
pop ebx

;;----------------------

dec [attente_avant_med]
jnz terertyrtytyrrtyrty
;fabriquation du packet/victoires&m‚dailles
mov [ordre2],'Z'

;-------- on donne la victoire au tout premier de cette equipe
xor ebx,ebx
pas_celui_la:
cmp [team+ebx],eax
je reertertertertert90
add ebx,4
jmp pas_celui_la
reertertertertert90:

inc dword ptr [victoires+ebx]

mov [latest_victory],ebx
push ds
pop  es
mov esi,offset victoires
mov edi,offset donnee4
mov ecx,9
rep movsd
;--- puis on copie:
;les  4 dd: des sources du dyna de face ki a gagn‚...
;puis 1 db: le nombre de lignes k'il fait...
;liste_couleur dd offset blanc,

mov esi,[liste_couleur+ebx]
xor eax,eax
mov ax,word ptr [esi]
add eax,dword ptr [donnee+8*3*2+ebx] ;--- adresse page
stosd
xor eax,eax
mov ax,word ptr [esi+2]
add eax,dword ptr [donnee+8*3*2+ebx] ;--- adresse page
stosd
xor eax,eax
mov ax,word ptr [esi+4]
add eax,dword ptr [donnee+8*3*2+ebx] ;--- adresse page
stosd
xor eax,eax
mov ax,word ptr [esi+6]
add eax,dword ptr [donnee+8*3*2+ebx] ;--- adresse page
stosd
shr ebx,1
mov ax,word ptr [donnee+8*5*2+ebx]   ;--- nombre de lignes
stosb
mov ax,word ptr [donnee+8*6*2+ebx]   ;--- nombre de colones.
stosb

;--- puis copie les noms des diff‚rents joueurs...
mov edi,offset briques
xor ebx,ebx
erertcharmant:
mov esi,offset nick_t
add esi,[control_joueur+ebx]
;lodsd
movsd
add ebx,4
cmp ebx,4*8
jne erertcharmant
;-------------------------------------------------------

;mov dword ptr [texte1+6*1+1+32*0+edx],eax
;mov dword ptr [texte1+6*1+1+32*1+edx],eax
;mov dword ptr [texte1+6*1+1+32*2+edx],eax
;mov dword ptr [texte1+6*1+1+32*3+edx],eax


;donnee       dw 8 dup (?) ;x du dynablaster
;             dw 8 dup (?) ;y du dynablaster
;             dw 8 dup (?) ;source du dyna dans bloque
;             dd 8 dup (?) ;source bloque memoire
;             dw 8 dup (?) ;nombre de lignes pour un dyna...
;             dw 8 dup (?) ;nombre de colonnes.
;             dd 8 dup (?) ;adder di (pour la girl + grande...)
;liste_couleur dd 8 dup (?)

;donnee4+9*4+4*4

;mov ecx,4
;lodsw
;rep movsd ;des sources du dyna de face ki a gagn‚...
;stosd

;;donnee  dw 8*3 dup (?)
;;       dw 20,20,277,277,116,116,180,180  ;x du dynablaster
;;       dw 9,170,9,170,41,137,41,137 ;y du dynablaster
;;       dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna dans bloque
;;dd 576000,576000,576000,576000,640000,640000,640000,640000 ;source bloque memoire
;;dw 23,23,23,23,25,25,25,25 ;nombre de lignes pour un dyna...
;;dd 0,0,0,0,-3*320,-3*320,-3*320,-3*320 ;adder di (pour la girl + grande...)


;si ordre2='Z'
;       copie de "victoires dd 8 dup (?)"
;       et 1 dd avec le offset du dernier ki a eu une victoire...
;          (latest_victory)

terertyrtytyrrtyrty:


;============================== sortie STYLE ESC en fin de record kan
;ya victoire d'un joueur ou autre...

cmp action_replay,1   ;rec
jne rtyrtyrtyertertyrtyrtytyutyutyutyuyut
cmp byte ptr [ordre2],'' ;LORSQUE LON EST SORTIS DU JEU
je  rtyrtyrtyertertyrtyrtytyutyutyutyuyut
mov [sortie],1 ;on sort !
call enregistre
rtyrtyrtyertertyrtyrtytyutyutyutyuyut:

;===========================================

popad
ret
gestion_jeu endp




;touches dd nb_dyna dup (0)

                      ;0= face        bas.
                      ;8= droite      droite
                      ;16= gauche     gauche
                      ;24= haut       haut

load_data proc near
pushall

cmp gus_or_sb,1
jne pas_de_guuuuus
call load_gus
pas_de_guuuuus:

cmp [assez_de_memoire],1
je eretterertrerzet

;------------------- charge le fichier avec les sprites ---------------

;mov ecx,[packed_liste+4*6]
;mov edx,offset iff_file_name
;mov edi,offset buffer4 ; 128000  ;307200
;mov ebx,320*200 ;307200
;mov ax,ds
;call load_pcx

;mov esi,0
;call copie_page2
;-----------------------------------------------------------------------

;mov ecx,0
;mov edx,offset fichier1
mov ecx,[packed_liste+4*0]
mov edx,offset iff_file_name
;adresse_des_fonds dd 640000,64000,328000
mov edi,0
mov ebx,320*200 ;307200 ;nombre de pixels.

mov ax,fs
call load_pcx
call loader

;mov ecx,0
;mov edx,offset fichier2
mov ecx,[packed_liste+4*1]
mov edx,offset iff_file_name

mov edi,64000*2
mov ebx,320*200 ;307200

 mov ax,fs
call load_pcx
call loader

;mov ecx,0
;mov edx,offset fichier3

;---- game
mov ecx,[packed_liste+4*2]
mov edx,offset iff_file_name
mov edi,64000*3 ; 128000  ;307200
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- draw 1  ----
mov ecx,[packed_liste+4*7]
mov edx,offset iff_file_name
mov edi,64000*5
mov ebx,320*200
mov ax,fs
call load_pcx
call loader
;----------------

;--- draw2   ----
mov ecx,[packed_liste+4*8]
mov edx,offset iff_file_name
mov edi,64000*6
mov ebx,320*200
mov ax,fs
call load_pcx
call loader
;----------------

;--- med 1   ----
mov ecx,[packed_liste+4*9]
mov edx,offset iff_file_name
mov edi,64000*7
mov ebx,320*200
mov ax,fs
call load_pcx
call loader
;----------------

;--- med 3   ----
mov ecx,[packed_liste+4*10]
mov edx,offset iff_file_name
mov edi,64000*8
mov ebx,320*200
mov ax,fs
call load_pcx
call loader
;----------------

;--- sprites bomberman masculins ---
mov ecx,[packed_liste+4*3]
mov edx,offset iff_file_name
mov edi,576000 ; 128000  ;307200
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- sprites bomberman feminin ---
mov ecx,[packed_liste+4*6]
mov edx,offset iff_file_name
mov edi,640000 ; 128000  ;307200
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- vic 1 ---
mov ecx,[packed_liste+4*11]
mov edx,offset iff_file_name
mov edi,704000 ; 128000  ;307200
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- vic 2 ---
mov ecx,[packed_liste+4*12]
mov edx,offset iff_file_name
mov edi,768000 ; 128000  ;307200
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- vic 3 ---
mov ecx,[packed_liste+4*13]
mov edx,offset iff_file_name
mov edi,832000 ; 128000  ;307200
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- vic 4 ---
mov ecx,[packed_liste+4*14]
mov edx,offset iff_file_name
mov edi,896000 ; 128000  ;307200
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- neige1 ---
mov ecx,[packed_liste+4*15]
mov edx,offset iff_file_name
mov edi,896000+64000*3 ; 128000  ;307200
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- neige2 ---
mov ecx,[packed_liste+4*16]
mov edx,offset iff_file_name
mov edi,896000+64000*2 ; 128000  ;307200
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- pic.pcx ---
mov ecx,[packed_liste+4*18]
mov edx,offset iff_file_name
mov edi,896000+64000*1 ;896000+64000*3 ; 128000  ;307200
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;;--- mrfond.pcx ---
;mov ecx,[packed_liste+4*19]
;mov edx,offset iff_file_name
;;cmp kel_pic_intro,1
;;jne opiopiioiouuiiuiuiuooo
;;
;mov edi,896000+64000*4 ; 128000  ;307200
;mov ebx,640*(36*2) ;307200
;mov ax,fs
;call load_pcx
;call loader

;;--- mrfond.pcx ---
mov ecx,[packed_liste+4*19]
mov edx,offset iff_file_name
;;cmp kel_pic_intro,1
;;jne opiopiioiouuiiuiuiuooo
;;
mov edi,1966080+64000*21
mov ebx,320*200
mov ax,fs
call load_pcx
call loader




;--- final.pcx ---
mov ecx,[packed_liste+4*20]
mov edx,offset iff_file_name
mov edi,896000+64000*4+640*(36*2) ; 128000  ;307200
mov ebx,320*200
mov ax,fs
call load_pcx
call loader
;;--nuage1.pcx--
mov ecx,[packed_liste+4*21]
mov edx,offset iff_file_name
mov edi,896000+64000*4+640*(36*2)+64000 ; 128000  ;307200
mov ebx,320*200
mov ax,fs
call load_pcx
call loader
;--nuage2.pcx--
mov ecx,[packed_liste+4*22]
mov edx,offset iff_file_name
mov edi,896000+64000*4+640*(36*2)+64000*2 ; 128000  ;307200
mov ebx,320*200
mov ax,fs
call load_pcx
call loader


;--- foret.pcx ---
mov ecx,[packed_liste+4*23]
mov edx,offset iff_file_name
mov edi,896000+384000+46080+64000 ; 128000  ;307200
mov ebx,320*200
mov ax,fs
call load_pcx
call loader

;--- feuille.pcx ---
mov ecx,[packed_liste+4*24]
mov edx,offset iff_file_name
mov edi,896000+384000+46080+64000+64000 ; 128000  ;307200
mov ebx,320*200
mov ax,fs
call load_pcx
call loader

;--- neige3 ---
mov ecx,[packed_liste+4*17]
mov edx,offset iff_file_name
mov edi, 896000+384000+46080+64000*3
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;1582080

;--- pause.pcx ---
mov ecx,[packed_liste+4*25]
mov edx,offset iff_file_name
mov edi,1582080
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- mdec.pcx ---
mov ecx,[packed_liste+4*26]
mov edx,offset iff_file_name
mov edi,1582080+64000
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;--- mdeg.pcx ---
mov ecx,[packed_liste+4*27]
mov edx,offset iff_file_name
mov edi,1582080+64000*2
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;;--- exo1.pcx ---
;mov ecx,[packed_liste+4*28]
;mov edx,offset iff_file_name
;mov edi,1582080+64000*3
;mov ebx,320*200
;mov ax,fs
;call load_pcx
;call loader
;;--- puzzle.pcx ---
;mov ecx,[packed_liste+4*29]
;mov edx,offset iff_file_name
;mov edi,1582080+64000*4
;mov ebx,320*200
;mov ax,fs
;call load_pcx
;call loader

;---- record0.mbr ---
;cmp special_on_a_loadee_nivo,1
;je naoinoirzeniozerrzeerzzererz
mov ecx,[packed_liste+4*30]
mov edx,offset iff_file_name

cmp economode,1
je ertertterterrtertytyrrtyrtyrtyrtyrtyrtyrty

cmp special_on_a_loadee_nivo,1
jne ertertterterrtertytyrrtyrtyrtyrtyrtyrtyrty
lea edx,reccord2
xor ecx,ecx
ertertterterrtertytyrrtyrtyrtyrtyrtyrtyrty:
mov edi,1966080+64000
call load_raw
call loader
naoinoirzeniozerrzeerzzererz:
;---- record1.mbr ---
mov ecx,[packed_liste+4*31]
mov edx,offset iff_file_name
mov edi,1966080+64000*2
call load_raw
call loader
;---- record2.mbr ---
mov ecx,[packed_liste+4*32]
mov edx,offset iff_file_name
mov edi,1966080+64000*3
call load_raw
call loader
;---- record3.mbr ---
mov ecx,[packed_liste+4*33]
mov edx,offset iff_file_name
mov edi,1966080+64000*4
call load_raw
call loader
;---- fete1.mbr ---
mov ecx,[packed_liste+4*34]
mov edx,offset iff_file_name
mov edi,1966080+64000*5
call load_raw
call loader
;---- record5.mbr ---
mov ecx,[packed_liste+4*37]
mov edx,offset iff_file_name
mov edi,1966080+64000*6
call load_raw
call loader

;---- crayon.pcx ---
mov ecx,[packed_liste+4*35]
mov edx,offset iff_file_name
mov edi,1582080+64000*3 ;1582080+64000*6
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader
;---- crayon2.pcx ---
mov ecx,[packed_liste+4*36]
mov edx,offset iff_file_name
mov edi,1582080+64000*4 ;1582080+64000*7
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader
;---- lapin1.pcx ---
mov ecx,[packed_liste+4*38]
mov edx,offset iff_file_name
mov edi,1966080+64000*7
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader

;---- mort.pcx ---
mov ecx,[packed_liste+4*39]
mov edx,offset iff_file_name
mov edi,1966080+64000*8
mov ebx,320*200
mov ax,fs
call load_pcx
call loader

;---- lapin2.pcx ---
mov ecx,[packed_liste+4*40]
mov edx,offset iff_file_name
mov edi,1966080+64000*9
mov ebx,320*200
mov ax,fs
call load_pcx
call loader

;---- lapin3.pcx ---
mov ecx,[packed_liste+4*41]
mov edx,offset iff_file_name
mov edi,1966080+64000*10
mov ebx,320*200
mov ax,fs
call load_pcx
call loader

;---- lapin4.pcx ---
mov ecx,[packed_liste+4*42]
mov edx,offset iff_file_name
mov edi,1966080+64000*11
mov ebx,320*200
mov ax,fs
call load_pcx
call loader

;---- foot.pcx ---
mov ecx,[packed_liste+4*43]
mov edx,offset iff_file_name
mov edi,1966080+64000*12
mov ebx,320*200
mov ax,fs
call load_pcx
call loader

;---- foot1.mbr ---
mov ecx,[packed_liste+4*44]
mov edx,offset iff_file_name
mov edi,1966080+64000*13
call load_raw
call loader

;---- foot2.mbr ---
mov ecx,[packed_liste+4*45]
mov edx,offset iff_file_name
mov edi,1966080+64000*14
call load_raw
call loader

;---- fete2.mbr ---
mov ecx,[packed_liste+4*46]
mov edx,offset iff_file_name
mov edi,1966080+64000*15
call load_raw
call loader

;---- neige2.mbr ---
mov ecx,[packed_liste+4*47]
mov edx,offset iff_file_name
mov edi,1966080+64000*16
call load_raw
call loader
;---- rose2.mbr ---
mov ecx,[packed_liste+4*48]
mov edx,offset iff_file_name
mov edi,1966080+64000*17
call load_raw
call loader
;---- jungle2.mbr ---
mov ecx,[packed_liste+4*49]
mov edx,offset iff_file_name
mov edi,1966080+64000*18
call load_raw
call loader
;---- micro2.mbr ---
mov ecx,[packed_liste+4*50]
mov edx,offset iff_file_name
mov edi,1966080+64000*19
call load_raw
call loader
;---- nuage2.mbr ---
mov ecx,[packed_liste+4*51]
mov edx,offset iff_file_name
mov edi,1966080+64000*20
call load_raw
call loader

;--- soucoupe.pcx ---
mov ecx,[packed_liste+4*52]
mov edx,offset iff_file_name
mov edi,1966080+64000*22
mov ebx,320*200
mov ax,fs
call load_pcx
call loader

;--- soccer.pcx ---
mov ecx,[packed_liste+4*53]
mov edx,offset iff_file_name
mov edi,1966080+64000*23
mov ebx,320*200
mov ax,fs
call load_pcx
call loader

;--- footanim.pcx ---
mov ecx,[packed_liste+4*54]
mov edx,offset iff_file_name
mov edi,1966080+64000*24
mov ebx,320*200
mov ax,fs
call load_pcx
call loader


;---- lune1.mbr ---
mov ecx,[packed_liste+4*55]
mov edx,offset iff_file_name
mov edi,1966080+64000*25
call load_raw
call loader
;---- lune2.mbr ---
mov ecx,[packed_liste+4*56]
mov edx,offset iff_file_name
mov edi,1966080+64000*26
call load_raw
call loader


;---- bombes.+ sprites bonus (sprite2.pcx)
mov ecx,[packed_liste+4*4]
mov edx,offset iff_file_name
mov edi,1582080+64000*5
mov ebx,320*200 ;307200
mov ax,fs
call load_pcx
call loader
;------------------------
;(1582080+64000*6) 64000K r‚serv‚ pour sauvegarde
;
;
;------------------------

;--- menu... ----
mov ecx,[packed_liste+4*5]
mov edx,offset iff_file_name
mov edi,64000*4
mov ebx,320*200
mov ax,fs
call load_pcx
call loader
;----------------


eretterertrerzet:
popall
ret
endp


transmet_central proc near ; … partir du GROS packet de touches qu'on a
                           ; r‚cup‚r‚ pour tous les ordinateur.
                           ; on regarde … kel dyna correspond chaque partie
                           ; packet
                           ; et on modifie les variables CENTRAL "touches"
                           ; et "action"
                           ; qui informent dans kel direction le dyna va
                           ; s'il est en mouvement  et s'il veut poser une
                           ; bombes. grace a ces variables l'intelligence du
                           ; master d‚terminera les packets finaux a envoyer
                           ; ou diff‚rents slaves... (enfin … l'affichage koi)
pushall
;*************** transmet au central...

mov ecx,[nombre_de_dyna] ;   dd 2 ;en tout.. pour le master
xor ebp,ebp
rterteterrterteertert:
mov ebx,[control_joueur+ebp] ;r‚cupere l'offet du packet en question.

;controle joueur special play
cmp action_replay,2
jne pas_recertterteretrreertyutyyut
mov ebx,[control_joueur2+ebp] ;r‚cupere l'offet du packet en question.
;mov ebx,-64
pas_recertterteretrreertyutyyut:
;=================

lea esi,[total_t+ebx]



;entr‚e. ebp ;num‚ro CENTRAL d'un joeur.

;mov esi,offset total_t ;packet

;call packet_to_central ;modifie les valeurs du central a partir des
;                       ;deplacement d'un dyna.
;packet_to_central proc near ;num‚ro du dyna * 4

PUSHALL

;model des packets recus par le master.. (envoy‚ par slave.)
;donnee2 dd 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
;        dd 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
;        dd 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
;        dd 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
;
;;offset 0         =1 si la fleche bas est press‚/               j1
;;       4         =1 si la fleche droite est press‚             j1
;;       8         =1 si la fleche gauche est press‚             j1
;;       12        =1 si la fleche haut est press‚2              j1
;;       16        =1 bouton 1                                   j1
;;       20        =1 bouton 2                                   j1

xor ax,ax ;indique k'on a trouv‚ aucune touche...

mov dword ptr [ACTION+ebp],0 ;touches action a 0

cmp [lapipipino+ebp],0 ;lapin ? tient pas compte de ses trucs
je dynanormalito
cmp [lapipipino2+ebp],0 ;en train de sauter ? tient pas compte de ses trucs
jne errereerreerretertertrtertetyyrtuui
dynanormalito:

cmp byte ptr [esi+3],1
jne erterertertertert
mov [touches+ebp],0
mov ax,1
 erterertertertert:

cmp byte ptr [esi+1],1
jne erterertertertert2
mov [touches+ebp],8
mov ax,2
 erterertertertert2:

cmp byte ptr [esi+2],1
jne erterertertertert3
mov [touches+ebp],16
mov ax,3
 erterertertertert3:

cmp byte ptr [esi],1
jne erterertertertert4
mov [touches+ebp],24
mov ax,4
 erterertertertert4:


;**************** touches d'action

;------------- touches d'action
;       4         =1 bouton 1                                   j1
;      5          =1 bouton 2                                   j1




cmp byte ptr [esi+4],1
jne ertertertertrte
mov byte ptr [ACTION+ebp],1
ertertertertrte:

cmp byte ptr [esi+6],1
jne ertertertertrte3
mov byte ptr [ACTION+ebp+2],1
; si lapin ki a la maladie de la lenteur... on lui permet pas de sauter ...
cmp word ptr [maladie+ebp],02 ;255 ; dd 8 dup (?)
jne ertertertertrte3
mov byte ptr [ACTION+ebp+2],0
;------------
ertertertertrte3:

;special lapin en train de sauter,on arrive directement la
errereerreerretertertrtertetyyrtuui:

cmp byte ptr [esi+5],1
jne tertertertertrte
mov byte ptr [ACTION+ebp+1],1
tertertertertrte:

;*******************************

;-------------
;touches dd nb_dyna dup (0)
;                      ;0= face        bas.
;                      ;8= droite      droite
;                      ;16= gauche     gauche
;                      ;24= haut       haut

;+128 si ne bouge pas..
or ax,ax
jnz reerrteertyut
or dword ptr [touches+ebp],128
reerrteertyut:
POPALL

add ebp,4
dec ecx
jnz rterteterrterteertert

popall
ret
endp

;get_all_infos proc near
;pushall
;
;;1er mot 0=existe pas: 1 existe !!!
;;2eme mot: num‚ro de l'ordinateur !!!
;;        0= local.
;;3eme mot: num‚ro interne (0 a 3) pour chaque ordinateur.
;;liste_des_joeurs dd 1,0,0
;;                 dd 0,0,0
;
;xor ebp,ebp
;
;mov esi,offset liste_des_joeurs
;mov ecx,[nombre_de_dyna] ;   dd 2 ;en tout.. pour le master
;sauver_de_moi_meme:
;or ecx,ecx
;jz fini
;dec ecx
;;cmp dword ptr [esi],0
;;je fini
;
;
;cmp dword ptr [esi+4],0 ;regarde si le joueur en question est en local. sinon il faut
;              ;r‚cup‚rer l'info par communication avec l'ordinateur.
;je cest_en_local
;
;cmp dword ptr [esi+8],0 ;regarde si on aurait pas deja r‚cup‚r‚ le packet..
;                        ;(vrai si offset dans le packet <> 0...)
;jne cest_en_local ;deja fait...
;
;;communication. (si le packet n'est pas deja charg‚...)
;;**************************************************************************
;ytytytytttttttttttttttttttttt:
;PUSHALL
;mov esi,[esi+4] ;offset liste_adresse ;r‚cupere l'adresse de l'ordy ou on envois... ;offset adresse
;mov ebp,offset packed_data ;donnee
;;call envois
;;envois special bloc total...
;envois3 ecb2 header_envois socket_jeu
;POPALL
;;call ecoute
;ecoute2 ecb1 recu_data header_ecoute touches_size socket_jeu
;
;xor ax,ax
;erzertrteertertert1:
;
;     /********************************************************\
;cmp byte ptr [clavier+59],1 ;F1... donne la periode d'attente pour la comm
;                            ;avec un ordy...
;jne reertertertertertert
;;- raster vert -
;inc ax
;push dx ax
;   mov   dx,3c8h
;push ax
; xor ax,ax
;   out   dx,al
;   mov   dx,3c9h
;   out   dx,al
;pop ax
;   out   dx,al
;xor ax,ax
;   out   dx,al
;pop ax dx
;;- raster vert -
;reertertertertertert:
;;     \********************************************************/
;cmp byte ptr [sortie],1 ;eSC.
;je rtyrtyrtyretertdgrfgdtrdfgdfgdfg
;cmp byte ptr [ecb1+8],0
;jne erzertrteertertert1
;;
;call raster2
;rtyrtyrtyretertdgrfgdtrdfgdfgdfg:
;;-------
;pushall
;mov ax,gs
;mov es,ax
;;recu_data     db '??????????????????????????????????????????????????????????????',10,13,'$'
;mov esi,offset recu_data
;mov edi,offset donnee2
;mov ecx,6*4*4
;rep movsb
;popall
;
;;**************************************************************************
;cest_en_local:
;
;push esi
;mov esi,[esi+8] ;r‚cupere l'offet du packet en question.
;add esi,offset donnee2 ;packet
;
;;entr‚e. ebp ;num‚ro CENTRAL d'un joeur.
;
;call packet_to_central ;modifie les valeurs du central a partir des
;                       ;deplacement d'un dyna.
;pop esi
;;------------------------------------------
;add ebp,4
;add esi,32
;jmp sauver_de_moi_meme
;fini:
;popall
;ret
;endp


possible_ou_pas proc near ;dx add x, cx: add y
pushall

;add [donnee+nb_dyna*2+ebp],1 Y

;xy_to_offset
;lea esi,[truc+eax]

xor eax,eax
mov ax,[donnee+ebp] ;x !!!!
add ax,dx
add ax,3
shr ax,4

xor ebx,ebx
mov bx,[donnee+nb_dyna*2+ebp] ;Y !!!!
add bx,14
add bx,cx
;shr bx,4
and bx,01111111111110000B
shl bx,1 ;*32
mov esi,offset truc
add esi,ebx
add esi,eax

cmp byte ptr [esi],0
jne zerrzerzeerzer

;;1 = bombe... (2,3,4) respirant... si c sup a 4; on est mort...
cmp byte ptr [esi+32*13],1
jb efrerrereterter
cmp byte ptr [esi+32*13],4
ja efrerrereterter

add ebp,ebp
cmp [last_bomb+ebp],esi
je efrerrereterter

;--- ya une bombe+c'est pas la derniere case !!! essaye de la pousser ---

cmp [pousseur+ebp],1
jne zerrzerzeerzer
pushall
cmp dx,0
je pas_eee
jns tjyuyu6754oooi
mov ax,-1
tjyuyu6754oooi:

cmp dx,0
js tjyuyu6754oooir
mov ax,1
tjyuyu6754oooir:

mov ecx,0
call pousse_la_bombe
jmp okeeeeeyiui
pas_eee:

cmp cx,0
je pas_eeerty
jns tjyuyu6754oooirr
mov ax,-1
tjyuyu6754oooirr:

cmp cx,0
js tjyuyu6754oooirt
mov ax,1
tjyuyu6754oooirt:

mov ecx,2
call pousse_la_bombe
pas_eeerty:

okeeeeeyiui:
popall

jmp zerrzerzeerzer
efrerrereterter:


xor cx,cx ;retourne jz=vrai
popall
ret

zerrzerzeerzer:

mov cx,1
or cx,cx ;retourne jz=faux

popall
ret
endp


;mov si,-16 ; ;16 ;8 haut.
;call remet_milieu_x

remet_milieu_x proc near ;replace le sprite au milieu d'un case.
pushall
xor ebx,ebx
mov bx,[donnee+ebp] ;x !!!!
add bx,3
;------------------
and bx,01111B
cmp bx,7
je iookokokokok_deja_milieux
;dx add x, cx: add y
mov dx,0            ;X
mov cx,si           ;Y
call possible_ou_pas
jnz ertertirtyrtyyrtrtyrtyxer ;impossible.

;il n'y a rien juste au dessus/sous. remet vers le milieu...

eheheh_mur:

cmp bx,7
ja zererzerrteertrterteert
inc word ptr [donnee+ebp] ;x !!!!
xor cx,cx ;retourne jz=vrai
popall
ret
zererzerrteertrterteert:
dec word ptr [donnee+ebp] ;x !!!!
xor cx,cx ;retourne jz=vrai
popall
ret
;---------- ya kekchoz en dessous/sus
ertertirtyrtyyrtrtyrtyxer:

push ebp
add ebp,ebp
mov [avance+ebp],0 ;=0 PAS reussit a bouger
pop ebp


cmp bx,7
ja uzererzerrteertrterteert

;dx add x, cx: add y
mov dx,-16                     ;X
mov cx,si                      ;Y
call possible_ou_pas
jnz eheheh_mur
;dx add x, cx: add y
mov dx,-16                     ;X
mov cx,0                       ;Y
call possible_ou_pas
jnz eheheh_mur

dec word ptr [donnee+ebp] ;x !!!!
xor cx,cx ;retourne jz=vrai
popall
ret
uzererzerrteertrterteert:

mov dx,16
mov cx,si ;16 ;8
call possible_ou_pas
jnz eheheh_mur
mov dx,16 ;0
mov cx,0 ;si ;16 ;8
call possible_ou_pas
jnz eheheh_mur

inc word ptr [donnee+ebp] ;x !!!!
xor cx,cx ;retourne jz=vrai
popall
ret

iookokokokok_deja_milieux:
mov cx,1
or cx,cx ;retourne jz=faux
popall
ret
endp

remet_milieu_y proc near ;replace le sprite au milieu d'un case.
pushall
xor ebx,ebx
mov bx,[donnee+nb_dyna*2+ebp] ;y !!!!
add bx,14 ;!
;------------------


and bx,01111B
cmp bx,7
je yiookokokokok_deja_milieux
;dx add x, cx: add y
mov dx,si
mov cx,0 ;16 ;8
call possible_ou_pas
jnz yertertirtyrtyyrtrtyrtyxer ;impossible.

impossible_2_fois:

;push ebp
;add ebp,ebp
;mov [avance+ebp],0 ;=0 PAS reussit a bouger
;pop ebp

cmp bx,7
ja yzererzerrteertrterteert
inc word ptr [donnee+nb_dyna*2+ebp] ;y !!!!
xor cx,cx ;retourne jz=vrai
popall
ret
yzererzerrteertrterteert:
dec word ptr [donnee+nb_dyna*2+ebp] ;y !!!!
xor cx,cx ;retourne jz=vrai
popall
ret
;---------- ya kekchoz en dessous
yertertirtyrtyyrtrtyrtyxer:

push ebp
add ebp,ebp
mov [avance+ebp],0 ;=0 PAS reussit a bouger
pop ebp



cmp bx,7
ja yuzererzerrteertrterteert

mov dx,si
mov cx,-16
call possible_ou_pas
jnz impossible_2_fois
mov dx,0
mov cx,-16
call possible_ou_pas
jnz impossible_2_fois


dec word ptr [donnee+nb_dyna*2+ebp] ;y !!!!
xor cx,cx ;retourne jz=vrai
popall
ret
yuzererzerrteertrterteert:

mov dx,si
mov cx,16
call possible_ou_pas
jnz impossible_2_fois
mov dx,0
mov cx,16
call possible_ou_pas
jnz impossible_2_fois


inc word ptr [donnee+nb_dyna*2+ebp] ;y !!!!
xor cx,cx ;retourne jz=vrai
popall
ret

yiookokokokok_deja_milieux:
mov cx,1
or cx,cx ;retourne jz=faux
popall
ret
endp

nouvelle_partie proc near
pushall

push ds
pop  es

mov pauseur2,0
mov pause,0
mov pause2,50 ;interdiction de pause !!!


mov eax,[nombre_de_dyna]

push eax
shl eax,2
mov [nombre_de_dyna_x4],eax
pop eax

sub eax,8
neg eax
mov [nombre_de_monstres],eax
mov [nombre_de_monstres],eax

cmp [master],0
je trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2erte

popall
ret
;*************** QUE MASTER -******************
trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2erte:

mov ecx,8
mov edi,offset victoires
xor eax,eax
rep stosd

popall
ret
endp


nouvelle_manche proc near
pushall

push ds
pop  es

;mov attente_avant_adder_inser_coin,60*20

;bdraw666 db '  '
;bdraw1  dd ? ;32
mov inser_coin,120
mov viseur_ic2,4
mov adder_inser_coin,320*(67+50)

mov [viseur_sur_fond],0
mov [duree_vic],duree_vic2

mov [attente_avant_draw],attente_avant_draw2
mov [attente_avant_med],attente_avant_med2
mov [duree_draw],duree_draw2
mov [duree_med],duree_med2

mov [attente_nouveau_esc],0

mov [affiche_pal],1
mov [ordre2],''
mov [sortie],0

cmp [master],0
je trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2ert

popall
ret
;*************** QUE MASTER -******************
trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2ert:

mov word ptr bdraw666,'03'
mov bdraw1,60
mov adder_bdraw,50*320
mov balance_le_bdrawn,0
mov temps2,59

mov special_nivo_6,0

mov acceleration,0

mov in_the_apocalypse,0

mov nombre_de_vbl_avant_le_droit_de_poser_bombe,nombre_de_vbl_avant_le_droit_de_poser_bombe2

push ax
mov al,team3_sauve
mov team3,al
pop ax

;---- terrain ---
mov ebx,[viseur_liste_terrain] ;dd 0
mov al,[liste_terrain+ebx]
mov [terrain],al
inc [viseur_liste_terrain]
cmp [liste_terrain+1+ebx],66
jne coolio
mov [viseur_liste_terrain],0
coolio:
;------------------


;;SI PLAY, terrain dans le header !!! + variable "changement" -------
cmp action_replay,2
jne ertrtertertyetyuyutyut

;cmp nombre_de_vbl_avant_le_droit_de_poser_bombe,0
;jne erterertrtertetertyutyuyuttyuuty
mov team3,0
push eax
mov eax,fs:[1966080+TAILLE_HEADER_REC-9] ;variable changement
mov [changement],eax
mov byte ptr al,fs:[1966080+TAILLE_HEADER_REC-1] ;1er octet: le numero du terrain
mov [terrain],al
pop eax
ertrtertertyetyuyutyut:
;-------------------
;ENREGISTREMENT ***
cmp action_replay,1
jne pas_rec345
push eax
mov eax,[changement]
mov fs:[1966080+64000+TAILLE_HEADER_REC-9],eax ;variable changement
mov al,[terrain]
mov byte ptr fs:[1966080+64000+TAILLE_HEADER_REC-1],al ;1er octet: le numero du terrain],al ;1er octet: le numero du terrain
pop eax
pas_rec345:
;*******************

;mov temps,duree_match

;push ax
;mov al,team3_sauve
;mov team3,al
;pop ax

cmp [team3],0
jne etrtyertyrdfgdfggdffgdgdfgy
pushall
lea esi,n_team
lea edi,team
mov ecx,9
rep movsd
popall
etrtyertyrdfgdfggdffgdgdfgy:

cmp [team3],2
jne etrtyertyrdfgdfggdffgdgdf
pushall
lea esi,s_team
lea edi,team
mov ecx,9
rep movsd
popall
etrtyertyrdfgdfggdffgdgdf:
cmp [team3],1
jne etrtyertyrdfgdfggdffgdgdfE
pushall
lea esi,c_team
lea edi,team
mov ecx,9
rep movsd
popall
etrtyertyrdfgdfggdffgdgdfE:

;--- recup la duree du match en fonction du terrain
xor ebx,ebx
mov bl,terrain
dec bl
shl ebx,2
mov eax,[ebx+kelle_duree]
mov temps,ax
;----------------------------------------------------------
mov edi,offset total_t
xor eax,eax
mov ecx,(64/4)*8
rep stosd
lea edi,total_play
xor eax,eax
mov ecx,64/4
rep stosd

xor eax,eax
mov ecx,8 ;nb_dyna
lea edi,touches_save
rep stosd

;-------------------------------------------- donn‚es ...
mov edi,offset donnee

xor ebx,ebx
mov bl,terrain
dec bl
shl ebx,2
mov esi,[ebx+kelle_donnee]

;donnee_s_neige dw 20,20,277,277-32,116-16-16,116,180+16+16,180  ;x du dynablaster
;                dw 9,170,9,170,41,137,41,137-16-16 ;y du dynablaster

;--- X/Y avec rotation pour changer la place des dyna..
  xor edx,edx
  mov edx,[changement]
  and edx,01111B ;
  shl edx,5 ;*32

  ;******** ACTION REPLAY--------------------
  ; si play
  cmp action_replay,2
  jne pashjktrkhjerterttyr
  mov edx,dword ptr fs:[1966080+TAILLE_HEADER_REC-5] ;rotation, offet 1 dans le header !
  pashjktrkhjerterttyr:
  ; si rec
  cmp action_replay,1
  jne upashjktrkhjerterttyrr
  mov dword ptr fs:[1966080+64000+TAILLE_HEADER_REC-5],edx ;rotation, offet 1 dans le header !
  upashjktrkhjerterttyrr:
  ;--------------------------------

  mov ecx,8
  oooiiooiioio:
  mov ebx,[random_place+edx]
  mov ax,word ptr [esi+ebx]
  mov word ptr [edi],ax
  mov ax,word ptr [esi+ebx+8*2]
  mov word ptr [edi+8*2],ax
  add edi,2
  add edx,4
  dec ecx
  jnz oooiiooiioio
  add esi,8*4
  add edi,8*2
;------
mov ecx,8*14
rep movsb
mov edi,offset liste_couleur
mov ecx,8
rep movsd
lea edi,nombre_de_coups
mov ecx,8
rep movsd

mov edi,offset infos_j_n
mov ecx,5
rep movsd
lea edi,infos_m_n
mov ecx,5*8
rep movsd
lea edi,invinsible
mov ecx,8
rep movsd
lea edi,blocage
mov ecx,8
rep movsd

mov ecx,[nombre_de_dyna]
lodsd
lea edi,invinsible
rep stosd

mov ecx,[nombre_de_dyna]
lodsd
lea edi,blocage
rep stosd

lea edi,pousseur
mov ecx,8
rep movsd

lea edi,vitesse_monstre
mov ecx,8
rep movsd

mov ecx,[nombre_de_dyna]
lodsd
lea edi,pousseur
rep stosd

mov ecx,[nombre_de_dyna]
lodsd
lea edi,patineur
rep stosd

lea edi,correspondance_bonus
mov ecx,32/4
rep movsd


;info j.
mov edi,offset j1
mov ecx,[nombre_de_dyna]
;--- 1
push ecx
koaiouiouiouiououiuio:
mov eax,[infos_j_n]
stosd
mov eax,[infos_j_n+4]
stosd
mov eax,[infos_j_n+8]
stosd
mov eax,[infos_j_n+12]
stosd
mov eax,[infos_j_n+16]
stosd
dec ecx
jnz  koaiouiouiouiououiuio
pop ecx
mov eax,ecx
sub ecx,8
neg ecx
or ecx,ecx
jz centralol
;--- 8 POUR LES MONSTRES !!!
lea esi,infos_m_n
;on doit ajouter (4*5)*nombre joueurs en offset
erterertertert:
add esi,4*5
dec eax
jnz erterertertert

monstro4:
;mov eax,[infos_m_n]
;stosd
push ecx
mov ecx,5
rep movsd
pop ecx
;mov eax,[infos_m_n+4]
;stosd
;movsd
;mov eax,[infos_m_n+8]
;stosd
;movsd
;mov eax,[infos_m_n+12]
;stosd
;movsd
;xor eax,eax
;stosd
;movsd
;---
dec ecx
jnz monstro4
centralol:

;-- transforme les monstres par d‚faux en dynas ...
mov esi,offset s_normal
lea edi,donnee+8*6
mov ecx,[nombre_de_dyna]
rep movsd
lea esi,liste_couleur_normal
lea edi,liste_couleur ;(= donnee+8*18)
mov ecx,[nombre_de_dyna]
rep movsd
mov esi,offset l_normal
lea edi,donnee+8*10
mov ecx,[nombre_de_dyna]
rep movsw
mov esi,offset c_normal
lea edi,donnee+8*12
mov ecx,[nombre_de_dyna]
rep movsw
mov esi,offset a_normal
lea edi,donnee+8*14
mov ecx,[nombre_de_dyna]
rep movsd
lea esi,r_normal
lea edi,nombre_de_coups
mov ecx,[nombre_de_dyna]
rep movsd
i:

;donnee_s_neige dw 20,20,277,277-32,116-16-16,116,180+16+16,180  ;x du dynablaster
;       2        dw 9,170,9,170,41,137,41,137-16-16 ;y du dynablaster
;       4        dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna
;       6        dd 512000,512000,512000,512000,512000,512000,512000,512000 ;source bloque memoire
;       10       dw 32,32,32,32,32,32,32,32 ;nombre de lignes pour un dyna...
;       12       dw 32,32,32,32,32,32,32,32 ;nombre de colonnes.
;       14       dd -9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4 ;adder di
;       18       dd offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu
;
;;avec un dyna...
;liste_couleur_normal dd blanc,offset bleu,offset vert,offset rouge,offset blancg,offset bleug,offset vertg,offset rougeg
;
;;       dw 20,20,277,277,116,116,180,180  ;x du dynablaster
;;       dw 9,170,9,170,41,137,41,137 ;y du dynablaster
;;       dw 24*0,777,24*2,24*3,24*4,24*5,24*6,24*7 ;source du dyna dans bloque
;;       64000*8
;s_normal dd 512000,576000,576000,576000,640000,640000,640000,640000 ;source bloque memoire
;l_normal dw 23,23,23,23,25,25,25,25 ;nombre de lignes pour un dyna...
;c_normal dw 32,23,23,23,23,23,23,23 ;nombre de colonnes.
;a_normal dd 0,0,0,0,-3*320,-3*320,-3*320,-3*320 ;adder di (pour la girl + grande...)

;-----------------------------------

;briques dw 1+19*13*2 dup (?)  ;nombre de brique, source de la brique, destination
;                              ;dans buffer video
;bombes  dw 1+19*13*2 dup (?)  ; pareil pour les bombes & explosion & bonus
xor eax,eax
mov edi,offset briques
mov ecx,1+19*13*2
rep stosw
mov edi,offset bombes
mov ecx,1+19*13*2
rep stosw

mov edi,offset maladie
mov ecx,8
rep stosd

lea edi,clignotement
mov ecx,8
rep stosd

lea edi,tribombe
mov ecx,8
rep stosd
lea edi,tribombe2
mov ecx,8
rep stosd

lea edi,lapipipino ;pour pu kil soit considere comme un lapin
mov ecx,8
rep stosd
lea edi,lapipipino2 ;pour pu kil soit considere comme un lapin
mov ecx,8
rep stosd
lea edi,lapipipino3 ;pour pu kil soit considere comme un lapin
mov ecx,8
rep stosd
lea edi,lapipipino4 ;pour pu kil soit considere comme un lapin
mov ecx,8
rep stosd
lea edi,lapipipino5 ;pour pu kil soit considere comme un lapin
mov ecx,8
rep stosd
lea edi,lapipipino6 ;pour pu kil soit considere comme un lapin
mov ecx,8
rep stosd

xor ebx,ebx
mov bl,terrain
dec bl
shl ebx,2
mov esi,[ebx+kelle_truc]

mov edi,offset truc
mov ecx,32*13
rep movsb

;--
xor ebx,ebx
mov bl,terrain
dec bl
shl ebx,2
mov esi,[ebx+kelle_bonus]
mov edi,offset truc2
mov ecx,32*13
rep movsb
;---
;liste_bombe dd ? ; nombre de bombes...
;            dd 247 dup (?,?,?,?)
mov edi,offset liste_bombe
mov ecx,1+247*(taille_dune_info_bombe/4)
rep stosd

;touches dd nb_dyna dup (0)
;action, touches d'action appuy‚s pour chacun des joeurs...
;
;ACTION dw nb_dyna dup (0,0)

lea edi,avance2
mov eax,1
mov ecx,8
rep stosd

mov edi,offset touches

xor eax,eax
mov ecx,8
rep stosd
xor eax,eax

mov edi,offset action
mov ecx,8
rep stosd

;-------- choisit une apocalypse en fonction du terrain...
;lea esi,truc_fin_s
push ebx
mov bl,terrain
dec bl
shl ebx,2
mov esi,[ebx+kelle_apocalypse]
pop ebx
lea edi,truc_fin
mov ecx,13*32+4
rep movsb

;------------------------------- eax: -1
mov edi,offset vie
mov ecx,8
mov eax,1
rep stosd


;fabrique un last_bomb pour chaque dyna...(par rapport a la position de debut)

xor ebp,ebp
a6ans:
pushall
  push ebp
  xy_to_offset
  pop ebp
  lea esi,[truc+eax]
  mov [last_bomb+ebp],esi
popall
add ebp,4
cmp ebp,4*8
jne a6ans

;mov [nomonster],1

cmp action_replay,0
jne nonononpasmode
cmp nomonster,1
jne nonononpasmode

;  jne nononono_onest_en_recordplay
;cmp twice,1
;jne nononono_onest_en_recordplay
;shr ecx,1
;nononono_onest_en_recordplay:

;----- tue tout le monde-
;cmp byte ptr [clavier+88],1 ;F12
;jne ertretetertertrte
mov edi,offset vie
xor ebp,ebp
mov ecx,[nombre_de_dyna]
retrteertertert:
or ecx,ecx
jz ljkljkmjkljklmljk
dec ecx
jmp trttyyrryrrryryryryr
ljkljkmjkljklmljk:
mov dword ptr [edi+ebp],14
trttyyrryrrryryryryr:

add ebp,4
cmp ebp,8*4
jnz retrteertertert
;ertretetertertrte:

nonononpasmode:


cmp action_replay,0 ;1
je pas_action

mov liste_bombbbb2,0
mov attente_entre_chake_bombe,0
mov viseur__nouvelle_attente_entre_chake_bombe,0

;viseur_change_in dd 0,4,8,12,16,20,24,28

pushall
lea edi,avance
xor eax,eax
mov ecx,8
rep stosd

;viseur_change_in dd 0,4,8,12,16,20,24,28
;viseur_change_in_save dd 0,4,8,12,16,20,24,28 ;pour replay
lea esi,viseur_change_in_save
lea edi,viseur_change_in
xor eax,eax
mov ecx,8
rep movsd

popall

;STRUTURE DE REC:
TAILLE_HEADER_REC EQU 32
TAILLE_BONUS_REC EQU 256

;---------- REC ou  -------------
;pushall ;hazard indesirable :) kan on enregistre :)
;push ds
;pop es
;lea edi,avance2
;mov eax,1
;mov ecx,8
;rep stosd
;popall


;si on rec, on initialise la veriable ki contiendra a la fin le nombre
; total de "tours"

;mov byte ptr fs:[1966080+TAILLE_HEADER_REC],1
;mov dword ptr fs:[1966080+TAILLE_HEADER_REC+TAILLE_BONUS_REC],4


cmp action_replay,1 ;rec
jne pas_rec

mov byte ptr fs:[1966080+64000+TAILLE_HEADER_REC],1
mov dword ptr fs:[1966080+64000+TAILLE_HEADER_REC+TAILLE_BONUS_REC],4

mov dword ptr fs:[1966080+64000+TAILLE_HEADER_REC-13],0 ;variable nb de tours total
push eax
mov eax,[nombre_de_dyna]
mov dword ptr  fs:[1966080+64000+TAILLE_HEADER_REC-17],eax ;nombre de dyna
pop eax
pas_rec:

pas_action:
;------------------------------
;(1582080+64000*6) 64000K r‚serv‚ pour sauvegarde

popall
ret
endp

rec_play_touches proc near
pushall

;rec
cmp action_replay,1
jne pas_rec3

mov ebp,dword ptr fs:[1966080+64000+TAILLE_HEADER_REC+TAILLE_BONUS_REC]

xor ebx,ebx
lea esi,total_t

mov ecx,dword ptr  fs:[1966080+64000+TAILLE_HEADER_REC-17] ;nb dyna
encoermnjklrtrtytyuyuisdfgrht345:
push esi
add esi,[control_joueur+ebx]

xor ah,ah
mov al,byte ptr [esi+6]
shl al,6
or ah,al
mov al,byte ptr [esi+5]
shl al,5
or ah,al
mov al,byte ptr [esi+4]
shl al,4
or ah,al
mov al,byte ptr [esi+3]
shl al,3
or ah,al
mov al,byte ptr [esi+2]
shl al,2
or ah,al
mov al,byte ptr [esi+1]
shl al,1
or ah,al
mov al,byte ptr [esi]
or ah,al
mov byte ptr fs:[1966080+64000+TAILLE_HEADER_REC+TAILLE_BONUS_REC+ebp],ah ;sauvegarde de la position du dyna
inc ebp

pop esi
add ebx,4
dec ecx
jnz encoermnjklrtrtytyuyuisdfgrht345

;cmp ebx,4*8
;jne encoermnjklrtrtytyuyuisdfgrht345

inc dword ptr fs:[1966080+64000+TAILLE_HEADER_REC-13] ;variable nb de tours total

mov dword ptr fs:[1966080+64000+TAILLE_HEADER_REC+TAILLE_BONUS_REC],ebp

;;--- arrete l'enregistrement kan pu de place
cmp ebp,64000-TAILLE_HEADER_REC-TAILLE_BONUS_REC-50 ;50 euh :)) whai koi
jb encore_de_la_place
mov [sortie],1 ;on sort !
call enregistre
encore_de_la_place:
;;-----------------------------------------------

;control_joueur dd 8 dup (0) ;-1,6,32,32+6,-1,-1,-1,-1
;

;total_t db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
;        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
;        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
;        db 0,0

pas_rec3:



;***********************************************
;         PLAY !!!  Û>
;***** ...
cmp action_replay,2
jne pas_rec4


;******
;cmp economode,1
;je rertterterrtertytyrrtyrtyrtyrtyrtyrtyrty
;cmp economode,1
;je erererjhrejhreerlhehelej
cmp special_on_a_loadee_nivo,2 ;bizarrerie pour sortir a la fin du play
                               ;car on a fin un load mrb
jne rertterterrtertytyrrtyrtyrtyrtyrtyrtyrty
erererjhrejhreerlhehelej:
mov [sors_du_menu_aussitot],1
rertterterrtertytyrrtyrtyrtyrtyrtyrtyrty:
;*********

;total_play db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
;        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
;        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
;        db 0,0,0,00     ,0,0   ;8eme joeur d'un ordy
;        db 0,0


mov ebp,dword ptr fs:[1966080+TAILLE_HEADER_REC+TAILLE_BONUS_REC]

xor ebx,ebx
lea esi,total_play

;mov ecx,dword ptr  fs:[1966080+64000+TAILLE_HEADER_REC-17]

mov ecx,dword ptr  fs:[1966080+TAILLE_HEADER_REC-17]

iencoermnjklrtrtytyuyuisdfgrht345:

mov al,byte ptr fs:[1966080+TAILLE_HEADER_REC+TAILLE_BONUS_REC+ebp]

mov byte ptr [esi+ebx],0
test al,0000001B
jz bhrebherterteeeeee
mov byte ptr [esi+ebx],1
bhrebherterteeeeee:
mov byte ptr [esi+ebx+1],0
test al,0000010B
jz bhrebherterteeeeeei
mov byte ptr [esi+ebx+1],1
bhrebherterteeeeeei:
mov byte ptr [esi+ebx+2],0
test al,0000100B
jz bhrebherterteeeeeeii
mov byte ptr [esi+ebx+2],1
bhrebherterteeeeeeii:
mov byte ptr [esi+ebx+3],0
test al,0001000B
jz bhrebherterteeeeeeiii
mov byte ptr [esi+ebx+3],1
bhrebherterteeeeeeiii:
mov byte ptr [esi+ebx+4],0
test al,0010000B
jz bhrebherterteeeeeeooo
mov byte ptr [esi+ebx+4],1
bhrebherterteeeeeeooo:
mov byte ptr [esi+ebx+5],0
test al,0100000B
jz bhrebherterteeeeeep
mov byte ptr [esi+ebx+5],1
bhrebherterteeeeeep:
mov byte ptr [esi+ebx+6],0
test al,01000000B
jz bhrebherterteeeeeept
mov byte ptr [esi+ebx+6],1
bhrebherterteeeeeept:

;xor ah,ah
;mov al,byte ptr [esi+5]
;shl al,5
;or ah,al
;mov al,byte ptr [esi+4]
;shl al,4
;or ah,al
;mov al,byte ptr [esi+3]
;shl al,3
;or ah,al
;mov al,byte ptr [esi+2]
;shl al,2
;or ah,al
;mov al,byte ptr [esi+1]
;shl al,1
;or ah,al
;mov al,byte ptr [esi]
;or ah,al
;mov byte ptr fs:[1966080+TAILLE_HEADER_REC+TAILLE_BONUS_REC+ebp],ah

inc ebp
add ebx,7

;cmp ebx,6*8
;
dec ecx
jnz iencoermnjklrtrtytyuyuisdfgrht345

mov dword ptr fs:[1966080+TAILLE_HEADER_REC+TAILLE_BONUS_REC],ebp

;----------- ;pour sortir si un slave press return... (euh en fait sil presse

;cmp temps_avant_demo,1
;je rertttttttttttttttttttttt345

touche_presse sortie 1
cmp sortie,1
jne rertttttttttttttttttttttt345
mov temps_avant_demo,ttp
rertttttttttttttttttttttt345:
;-------

dec dword ptr fs:[1966080+TAILLE_HEADER_REC-13] ;variable nb de tours total
jnz continueeeee
;--
cmp economode,2
jne non_non_pas_en_mode_truc
mov [sors_du_menu_aussitot],0
mov economode,1
non_non_pas_en_mode_truc:
;--


mov [sortie],1 ;on sort !
continueeeee:


;mov temps_avant_demo,ttp2
;----------


;control_joueur dd 8 dup (0) ;-1,6,32,32+6,-1,-1,-1,-1
;

;total_t db 0,0,0,0     ,0,0   ;1er joeur d'un ordy.
;        db 0,0,0,0     ,0,0   ;2eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;3eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;4eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;5emejoeur d'un ordy.
;        db 0,0,0,0     ,0,0   ;6eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;7eme joeur d'un ordy
;        db 0,0,0,0     ,0,0   ;8eme joeur d'un ordy
;        db 0,0

pas_rec4:

popall
ret
endp

;affichage_rec proc near
;pushall
;xor ax,ax
;mov al,byte ptr fs:[1966080+TAILLE_HEADER_REC]
;call affsigne
;mov al,byte ptr fs:[1966080+TAILLE_HEADER_REC+1]
;call affsigne
;mov al,byte ptr fs:[1966080+TAILLE_HEADER_REC+2]
;call affsigne
;mov eax,dword ptr fs:[1966080+TAILLE_HEADER_REC+TAILLE_BONUS_REC]
;call num
;xor eax,eax
;mov al,byte ptr fs:[1966080+TAILLE_HEADER_REC-1] ;1er octet: le numero du terrain
;call affsigne
;popall
;ret
;endp

load_gus proc near
pushall

;BOOM     IFF        10,783  08-06-97  4:36a
;BANG     IFF         8,046  08-06-97 10:26a
;KLANNG   IFF         9,373  08-06-97 10:27a
;
;del iff.dat
;copy /B BOOM.IFF+BANG.IFF+KLANNG.IFF iff.Dat

mov edi,offset iff_liste
mov eax,[total_liste]
uencoremasuperdeliredemaker:
cmp dword ptr [edi],-1
je ufinitobabyr
add dword ptr eax,[edi]
mov dword ptr [edi],eax
add edi,4
jmp uencoremasuperdeliredemaker
ufinitobabyr:


       xor ebp,ebp
       mov eax,4

tyu:
        mov ecx,[iff_liste+ebp]
        cmp ecx,-1
        je ooo
        PUSHALL
        call LOAD_BONUS_SAMPLE
        POPALL
        call loader

        add ebp,4
        add eax,4
        jmp tyu
ooo:

;ECX: OFFSET
;! dans EaX NUMERO DU SAMPLE *4 !
;MOV BP,32*4

;mov byte ptr [BLOW_WHAT],8 ;8*4
;mov byte ptr [BLOW_WHAT+1],40

;mov byte ptr [BLOW_WHAT+12],2    ;8*4
;mov byte ptr [BLOW_WHAT+13],30

;mov byte ptr [BLOW_WHAT],073h ;4 bits:panning, 4 bits: sample
;mov byte ptr [BLOW_WHAT+1],40  ;0 droite. ici. F left


popall
ret
endp

init_packed_liste proc near
pushall
mov edi,offset packed_liste
mov eax,taille_exe_gonfle
encoremasuperdeliredemaker:
cmp dword ptr [edi],-1
je finitobabyr
add dword ptr eax,[edi]
mov dword ptr [edi],eax
add edi,4
jmp encoremasuperdeliredemaker
finitobabyr:

mov [total_liste],eax

popall
 ret
init_packed_liste endp


menu proc near

pushall

;regarde si le dernier packet est un packet de menu.. ou non...
; si c'est on est pas master...

cmp [master],1
jne erttrtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2r

cmp dword ptr [packed_data+1],'unem'
je retttttttttttt
popall
ret
retttttttttttt:

erttrtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2r:

;       db 'menu' ;pout reconnaitre ou on est... enfin si c'est un packet


sound_menu

;mov edi,896000+64000*3 ; 128000  ;307200


cmp [assez_de_memoire],1
je erettererttrtyrtyyrtrty

;---- affiche le PIC.PCX -----------------------------------------------
cmp [master],0
jne reerttrtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2R
cmp [pic_time],0
jz  reerttrtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2R

dec [pic_time]
cmp [pic_time],16
jne erterertyyuuutyutyutyutyutyutyutyuty
mov [affiche_pal],1
erterertyyuuutyutyutyutyutyutyutyuty:
cmp [pic_time],17         ;RE quitte pas pendant k'on efface la palette
jb erttertertertertert
cmp [pic_time],pic_max-34 ;quitte pas avant k'on ait la pallette affich‚
ja erttertertertertert    ;
;cmp [last_sucker],0 ;derniere touche...
;je erttertertertertert
touche_presse pic_time 17
;mov [pic_time],17    ;acc‚lere le processus...
erttertertertertert:

;cmp [assez_de_memoire],1
;je affiche_pas_


mov esi,896000+64000*1 ;896000+64000*3

;cmp kel_pic_intro,1
;jne opiopiioiouuiiuiuiuooorytyyryrtt
;mov esi,1966080+64000*21
;opiopiioiouuiiuiuiuooorytyyryrtt:

;===== affiche en ram video ce k'il y a a : FS:ESI
;      ENTREE : ESI
call copie_page
call aff_page2 ;affiche en ram video ce k'il y a a dans le buffer
;affiche_pas_:
popall
ret
reerttrtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2R:
;---------------------------------------------------------------------------

;cmp [assez_de_memoire],1
;je erettererttrtyrtyyrtrty

push es

mov esi,896000+64000*3
;===== affiche en ram video ce k'il y a a : FS:ESI
;      ENTREE : ESI
mov esi,64000*4
call copie_page


mov ax,ds
mov es,ax

;call copie_bande

;mov edi,offset buffer
;xor eax,eax
;mov ecx,16000
;rep stosD

call scroll

mov [viseur_couleur],0

;------ premiere barre.
;mov esi,64000*4+58*320
;mov edi,offset buffer
;push edi
;copie 80*71
;pop edi

;lea edi,buffer+(30*320+36*320+14+320*3+2)

lea edi,buffer+(30*320+36*320+14+320*3+2-06+2+320*08+1)
mov ebx,offset texte1
  mov ecx,4
  rrteertertrteert:
  pushall
  ;---- edi: viseur sur ou ecrire
  ; ebx:texte
  ;------
  mov eax,[scrollyf]
  and eax,001100000B
  add ebx,eax
  call aff_texte
  popall
  add ebx,32*4

inc [viseur_couleur]

  add edi,80
  dec ecx
  jnz rrteertertrteert

;------ deuxieme barre.
;mov esi,64000*4+129*320
;mov edi,offset buffer+100*320
;push edi
;copie 80*71
;pop edi
;lea edi,buffer+(101*320+36*320+14+320*3+2)
lea edi,buffer+(101*320+36*320+14+320*3+2-06+2+320*08+1)
mov ebx,offset texte1+32*4*4

  mov ecx,4
  oorrteertertrteert:
  pushall
  ;---- edi: viseur sur ou ecrire
  ; ebx:texte
  ;------
  mov eax,[scrollyf]
  and eax,001100000B
  add ebx,eax
  call aff_texte
  popall
  add ebx,32*4
inc [viseur_couleur]
  add edi,80
  dec ecx
  jnz oorrteertertrteert
;.............................................................................
pop es
call aff_page2 ;affiche en ram video ce k'il y a a dans le buffer
popall
ret
erettererttrtyrtyyrtrty:
;pas assez de m‚moire...
popall
ret

aff_lettre:
push ecx
mov ecx,6
oertterertertertert:
push ebx

;couleur db 62,3,224,28,65,160,28,3
mov ebx,es:[viseur_couleur] ;db 0
cmp es:[ordre2],'Z'                    ; m‚daille distribution
jne rertetyutyuyuttuyyuttyu
mov bl,es:[couleur+ebx]
jmp rtyutyuyuttyutyuyutyutyut
rertetyutyuyuttuyyuttyu:
mov bl,es:[couleur_menu+ebx]
rtyutyuyuttyutyuyutyutyut:

crocro
crocro
crocro
crocro
crocro
crocro
crocro
crocro
pop ebx
add edi,320-8
add esi,320-8
dec ecx
jnz oertterertertertert
pop ecx
ret
aff_texte:

mov edx,3
reretertertrte:
mov ecx,6
ererrteertertertertert:
call affiche_un_caractere
add edi,8
dec ecx
jnz ererrteertertertertert
add edi,320*10-8*6
dec edx
jnz reretertertrte
ret
rerteertertertertertrteertertretrerertertert:
inc ebx
jmp rtrtytyryrtrtysepcialespace
affiche_un_caractere:
push edi ds
;mov esi,offset buffer3+165*320
mov esi,1582080+64000*5+165*320 ;offset buffer3
push fs
pop ds
;-- selectionne lettre
xor eax,eax
mov al,byte ptr es:[ebx]
cmp al,' '
je rerteertertertertertrteertertretrerertertert

cmp al,'z'+13 ;special pour le menu... espace dans nom d'un joueur...
je rerteertertertertertrteertertretrerertertert

cmp al,'?'
jne erttrerteertertertertertrteertertretrerertertertyyfr
;mov esi,223+171*320
mov esi,1582080+64000*5+232+8*3+172*320 ;[buffer3+232+8*3+172*320]
jmp reerertrteertertrteertrtertertrteert
erttrerteertertertertertrteertertretrerertertertyyfr:

;cmp al,'-'-'a'
;jne tderterterertZtr
;mov ax,304/8
;jmp rtrtyrtyrty
;tderterterertZtr:

cmp al,'-' ;curseur...
jne erttrerteertertertertertrteertertretrerertertertyyfrt
;mov esi,223+171*320
mov esi,1582080+64000*5+167*320+304 ;[buffer3+167*320+304]
sub edi,320*3
jmp reerertrteertertrteertrtertertrteert
erttrerteertertertertertrteertertretrerertertertyyfrt:

sub al,'a'
cmp al,'!'-'a'
jne erterterert
mov ax,288/8
jmp rtrtyrtyrty
erterterert:
cmp al,'.'-'a'
jne erterterertZ
mov ax,296/8
jmp rtrtyrtyrty
erterterertZ:

cmp al,':'-'a'
jne derterterertZ
mov ax,312/8
jmp rtrtyrtyrty
derterterertZ:

cmp al,'0'-'a'
jb rderterterertZ
add al,26-('0'-'a')
rderterterertZ:

rtrtyrtyrty:
shl ax,3

add esi,eax
reerertrteertertrteertrtertertrteert:
inc ebx
;----
call aff_lettre
rtrtytyryrtrtysepcialespace:
pop ds edi
ret
menu endp


scroll proc near

;---

inc [scrollyF]

;-- selectionne lettre
test dword ptr [scrollyF],0000000000111B
jnz trerteertertertertertrteertertretrerertertert
;223,171
xor eax,eax
mov ebx,offset tected

cmp [master],1
jne trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2R
mov ebx,offset tecte_sl
trtyrtrtyrtyrtyrtyrtytyrrtyrtytyryrtrty2R:

add ebx,[tecte2]
inc [tecte2]
;tecte    db 'abcedfghijklmnopq remdy is back Û'
;tecte2   dd 0


mov al,byte ptr [ebx]
cmp al,'*'
jne dtrerteertertertertertrteertertretrererterterte
lea edx,tected
sub edx,offset tecte
neg edx
mov [tecte2],edx
;lea esi,[buffer3+223+171*320]
mov esi,1582080+64000*5+223+171*320 ;64000*5+165*320 ;offset buffer3

jmp reerertrteertertrteert
dtrerteertertertertertrteertertretrererterterte:


mov al,byte ptr [ebx]
cmp al,'Û'
jne dtrerteertertertertertrteertertretrerertertert
;mov [tecte2],0
lea edx,tected
sub edx,offset tecte
neg edx
mov [tecte2],edx
mov esi,1582080+64000*5+223+171*320 ;[buffer3++223+171*320]

cmp [master],1
jne reerertrteertertrteert
mov [tecte2],0
jmp reerertrteertertrteert
dtrerteertertertertertrteertertretrerertertert:

cmp al,' '
jne erttrerteertertertertertrteertertretrerertertert
;mov esi,223+171*320
mov esi,1582080+64000*5+223+171*320 ;[buffer3+223+171*320]
jmp reerertrteertertrteert
erttrerteertertertertertrteertertretrerertertert:

cmp al,'/'
jne erttrerteertertertertertrteertertretrererterterty
;mov esi,223+171*320
;,ea esi,[buffer3+232+172*320]
mov esi,1582080+64000*5+223+172*320-8+16
jmp reerertrteertertrteert
erttrerteertertertertertrteertertretrererterterty:

cmp al,'('
jne erttrerteertertertertertrteertertretrerertertertyr
;mov esi,223+171*320
;,lea esi,[buffer3+232+8+172*320]
mov esi,1582080+64000*5+223+8+172*320-8+16
jmp reerertrteertertrteert
erttrerteertertertertertrteertertretrerertertertyr:

cmp al,')'
jne erttrerteertertertertertrteertertretrerertertertyy
;mov esi,223+171*320
;lea esi,[buffer3+232+8*2+172*320]
mov esi,1582080+64000*5+223+8*2+172*320-8+16
jmp reerertrteertertrteert
erttrerteertertertertertrteertertretrerertertertyy:

cmp al,'?'
jne erttrerteertertertertertrteertertretrerertertertyyf
;mov esi,223+171*320
;lea esi,[buffer3+232+8*3+172*320]
mov esi,1582080+64000*5+223+8*3+172*320-8+16
jmp reerertrteertertrteert
erttrerteertertertertertrteertertretrerertertertyyf:






sub al,'a'
cmp al,'!'-'a'
jne terterterert
mov ax,288/8
jmp trtrtyrtyrty
terterterert:
cmp al,'.'-'a'
jne terterterertZ
mov ax,296/8
jmp trtrtyrtyrty
terterterertZ:

cmp al,':'-'a'
jne tderterterertZ
mov ax,312/8
jmp trtrtyrtyrty
tderterterertZ:

cmp al,'-'-'a'
jne tderterterertZt
mov ax,304/8
jmp trtrtyrtyrty
tderterterertZt:


cmp al,'0'-'a'
jb trderterterertZ
add al,26-('0'-'a')
trderterterertZ:

trtrtyrtyrty:
shl ax,3

;inc ebx
;lea esi,[buffer3+165*320+eax]
mov esi,1582080+64000*5+165*320
add esi,eax
reerertrteertertrteert:
;----
;call aff_lettre

;:,:test [changement],0000111B
push ds
push fs
pop ds
mov edi,offset scrolly+320
mov ecx,6
frrr:
movsd
movsd
add edi,320
add esi,320-8
dec ecx
jnz frrr
pop ds

;---
trerteertertertertertrteertertretrerertertert:

lea esi,scrolly+1 ;   db 6*328 dup (01011101B)
lea edi,scrolly

mov ecx,328*6
rep movsb

lea esi,scrolly
mov edi,offset buffer+320*192
;4,5,6,7,8,9
mov edx,6
ddd:
mov ecx,320
;rep movsd
oooooooooi:
lodsb
or al,al
jz retertetyooo
mov es:[edi],al
retertetyooo:
inc edi
dec ecx
jnz oooooooooi

add esi,8

dec edx
jnz ddd
ret
endp


foo MACRO speed_bonus,i
local o2
cmp [last_bomb+i],eax
jne o2
cmp [vie+i],1 ;que les dyna vivants !!!!
jne  o2
cmp word ptr [speed_bonus+i],0 ;pas si deja une maladie..
jne o2
mov word ptr [speed_bonus+i],bx ;maladie..
mov word ptr [speed_bonus+i+2],duree_conta
o2:
ENDM

conta MACRO speed_bonus,ebp
local reterterrtertert
local o2
;last_bomb dd 8 dup (?)
;speed_bonus dd 8 dup (?)
cmp word ptr [speed_bonus+ebp],0 ;regarde si on a une maladie a donner.
je reterterrtertert
cmp [vie+ebp],1 ;que les dyna vivants !!!!
jne reterterrtertert

mov eax,[last_bomb+ebp]
;--- regarde pour les autres si
mov bx,word ptr [speed_bonus+ebp] ;dans bx on a la maladie...
foo maladie 0
foo maladie 4
foo maladie 8
foo maladie 12
foo maladie 0+16
foo maladie 4+16
foo maladie 8+16
foo maladie 12+16

reterterrtertert:
ENDM

decrem MACRO speed_bonus,o
local ertertrterteterrteert
local ooo
cmp word ptr [speed_bonus+o+2],0 ;255 ; dd 8 dup (?)
je ertertrterteterrteert
dec word ptr [speed_bonus+o+2]
jmp ooo
ertertrterteterrteert:
mov [speed_bonus+o],0 ;annule la maladie..
ooo:
ENDM

contamination proc near
pushall

decrem  maladie 0
decrem  maladie 4
decrem  maladie 8
decrem  maladie 12
decrem  maladie 0+16
decrem  maladie 4+16
decrem  maladie 8+16
decrem  maladie 12+16

conta  maladie 0
conta  maladie 4
conta  maladie 8
conta  maladie 12
conta  maladie 0+16
conta  maladie 4+16
conta  maladie 8+16
conta  maladie 12+16

popall
ret
endp




loader proc near
PUSHALL
mov ah,03
mov bh,0
int 10h
dec dl
jc erreer
mov dl,0
erreer:
mov ah,02h
int 10h


mov ah,02h ;SUPER_SIGNE2 DB 0
cmp [SUPER_SIGNE2],0
jne reertter
mov dl,'|'
int 21h
jmp er
reertter:
cmp [SUPER_SIGNE2],1
jne reerttertr
mov dl,'\'
int 21h
jmp er
reerttertr:
cmp [SUPER_SIGNE2],2
jne reerttertt
mov dl,'-'
int 21h
jmp er
reerttertt:
cmp [SUPER_SIGNE2],3
jne reertterttt
mov dl,'/'
int 21h
jmp er
reertterttt:
er:
inc [SUPER_SIGNE2]
cmp [SUPER_SIGNE2],4
jne oerR
mov [SUPER_SIGNE2],0
oerR:
POPALL
ret
endp

;
;action_replay dd 0 ; 0 = RIEN
;                   ; 1 = REC
;                   ; 2 = PLAY

menu_action proc near ;pour action replay
pushall

cmp record_user,0
je  azreertterertrtetrertrteertertretr
cmp byte ptr [clavier+88],1 ;F12
jne azreertterertrtetrertrteertertretr
cmp action_replay,1
je azreertterertrtetrertrteertertretr
mov temps_avant_demo,1
     mov   dx,3c8h
     xor ax,ax
     out   dx,al
     mov   dx,3c9h
     out   dx,al
     mov al,63
     out   dx,al
     xor ax,ax
     out   dx,al

azreertterertrtetrertrteertertretr:
;cmp record_user,0
;je azreertterertrtetrertrteertertretru
;cmp byte ptr [clavier+087],1 ;F11
;jne azreertterertrtetrertrteertertretru

cmp special_on_a_loadee_nivo,0
jne azreertterertrtetrertrteertertretru
cmp willrecord,1
jne azreertterertrtetrertrteertertretru
mov willrecord,0

mov action_replay,1

pushall
mov ax,fs
mov es,ax
mov edi,1966080+64000
mov ecx,16000
rep stosd
popall

     mov   dx,3c8h
     xor ax,ax
     out   dx,al
     mov   dx,3c9h
     out   dx,al
     out   dx,al
     mov al,63
     out   dx,al

azreertterertrtetrertrteertertretru:

popall
ret
endp

triche_master proc near
pushall

cmp [jesus_mode],0
jne reteretrertert5445870
popall
ret
reteretrertert5445870:

;jesus db 32,18,31,22,31
;jesus_viseur db 0
;jesus_mode db 0

push ds
pop es


;----- temps=1 !!!!!
;cmp byte ptr [clavier+84],1 ;pri,nt screen
;jne ertretetertertrtereertert
;mov temps,1
;ertretetertertrtereertert:

;--------------------- donne a tout le monde la maladie inversee
cmp byte ptr [clavier+70],1 ;scroll lock
jne reertterertrtetrertrteertertretr
xor ebx,ebx
ertttttttttttttttuyyut:
mov word ptr [maladie+ebx],2  ;2: lenteur
mov word ptr [maladie+2+ebx],duree_conta ;500 ; dd 8 dup (?)
add ebx,4
cmp ebx,4*8
jne ertttttttttttttttuyyut
reertterertrtetrertrteertertretr:

;--------------------- donne a tout le monde la power bombes.
cmp byte ptr [clavier+084],1 ;print screen
jne reertterertrtetrertrteertertretru
xor ebp,ebp
ertttttttttttttttuyyutu:
mov ebx,[infojoueur+ebp]
mov dword ptr [ebx+4*4],1
add ebp,4
cmp ebp,4*8
jne ertttttttttttttttuyyutu
reertterertrtetrertrteertertretru:

;mov [nomonster],1
;  cmp action_replay,0
;  jne nononono_onest_en_recordplay
;cmp twice,1
;jne nononono_onest_en_recordplay
;shr ecx,1
;nononono_onest_en_recordplay:

;----- tue tout le monde-
;cmp byte ptr [clavier+88],1 ;F12
;jne ertretetertertrte
;mov edi,offset vie
;mov ecx,[nombre_de_dyna]
;retrteertertert:
;cmp dword ptr [edi],1
;jne errteter
;mov dword ptr [edi],0
;errteter:
;add edi,4
;dec ecx
;jnz retrteertertert
;ertretetertertrte:
;--- victoire supreme du blanc--
cmp byte ptr [clavier+87],1     ;F11
jne reertterrterterteertter

mov dword ptr [victoires],4
mov dword ptr [victoires+4],4
mov dword ptr [victoires+8],4
mov dword ptr [victoires+12],4
mov dword ptr [victoires+16],4
mov dword ptr [victoires+20],4
mov dword ptr [victoires+24],4
mov dword ptr [victoires+28],4

reertterrterterteertter:


popall
ret
endp

gooroo proc near
pushall

cmp [jesus_mode],0
jne reteretrertert5445870t
popall
ret
reteretrertert5445870t:

;-------- raster vert
  cmp byte ptr [clavier+117],1 ;F1... donne la periode d'attente pour la comm
  jne ierreertterrterterteertter

  mov dword ptr [affiche_raster],0 ;raster vert off
  ierreertterrterterteertter:
  cmp byte ptr [clavier+121],1 ;F1... donne la periode d'attente pour la comm
  jne eierreertterrterterteertter
                            ;avec un ordy...
  mov dword ptr [affiche_raster],1 ;raster vert on
  eierreertterrterterteertter:
;-------

;-------

;-------- raster tout court
  cmp byte ptr [clavier+119],1 ; raster rouge off
  jne uierreertterrterterteertter
                            ;avec un ordy...
  ;NOT dword ptr [affiche_raster2]
mov [mechant],0
  uierreertterrterterteertter:
;-------

;--------
  cmp byte ptr [clavier+120],1 ; raster rouge on
  jne uierreertterrterterteertterz
                            ;avec un ordy...
  ;NOT dword ptr [affiche_raster2]
mov [mechant],2
  uierreertterrterterteertterz:
;-------



;---- KICKAGE:
;xor ebx,ebx
;rtertyrtyyrtrtytyryrtyrtyrt:
;cmp byte ptr [clavier+59+ebx],1
;jne ertretetertertrteerzertter
;push ebx
;shl ebx,4
;cmp dword ptr [liste_adresse+12+ebx],'koko'
;jne rteertertertrteertterertert
;mov dword ptr [liste_adresse+12+ebx],'daed'
;dec [nb_ordy_connected]  ;dd 0 ;*16 en fait.
;rteertertertrteertterertert:
;pop  ebx
;ertretetertertrteerzertter:
;inc ebx
;cmp ebx,7
;jne rtertyrtyyrtrtytyryrtyrtyrt

;--diminue le temps
;cmp byte ptr [clavier+68],1
;jne ertretetertertrteerzerttertrrtpo
;mov [temps],000000000001B ;little 2
;ertretetertertrteerzerttertrrtpo:

;----- active en monstre ------- ;-----------
cmp byte ptr [clavier+68],1 ;f10
jne reertterertrtetrertrteertert
pushall
push ds
pop  es
;lea esi,ooo34
mov lapipipino,1
mov [lapipipino+4],1
mov [nombre_de_coups],1
mov [nombre_de_coups+4],1
;lea esi,lapin_mania
;lea edi,ooo546
;mov ecx,16*8
;rep movsb
;
;mov dword ptr [liste_couleur],offset grosbleu
;mov dword ptr [donnee+8*2*3],512000
;mov word ptr [donnee+8*2*5],32
;mov word ptr [donnee+8*2*6],32
;mov dword ptr [donnee+8*2*7],-9*320-4
popall
reertterertrtetrertrteertert:
;---------------------------------------------------------------------------


;----- monstromanie --------------------------------------------------------
;mov esi,offset grosbleu
;si ordre2=''
;cmp [ordre2],''
;jne ememertkerty
;cmp [monstro],1
;jne ememertkerty
;mov esi,offset grosbleu
;si ordre2=''
; 8x source DD, destination dw pour chaque dyna..., db: nombre de ligne du dyna
; (serra tri‚ … l'affichage par chaque machine.mettra dest a ffffh)
;
;       dd 512000,512000,512000,512000,512000,512000,512000,512000 ;source bloque memoire
;       dw 32,32,32,32,32,32,32,32 ;nombre de lignes pour un dyna...
;       dw 32,32,32,32,32,32,32,32 ;nombre de colonnes.
;       dd -9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4,-9*320-4 ;adder di
;       dd offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu,offset grosbleu

;sub dword ptr [donnee4+ecx],
;ememertkerty:
;;---------------------------------------------------------------------------
;
;
;mov [monstro],1
;jmp reertterertrtetrertrteertert
;ertertter:
;mov [monstro],0
reertterertrtetrertrteertert:
;--------------------------------

popall
ret
endp
;copie_bande proc near
;PUSHALL
;mov ebx,[machin2]
;
;dec dword ptr [changementZZ2] ;000011000B
;jnz retterertrte
;mov dword ptr [changementZZ2],time_bouboule ;011000B
;add [machin2],4
;cmp [machin2],4*29*2-4
;jne retterertrte
;mov [machin2],0
;retterertrte:
;
;mov esi,[machin+ebx]
;add esi,[machin3]
;
;push ds
;pop  es
;push fs
;pop ds
;add esi,896000+64000*4 ; 128000  ;307200
;lea edi,buffer
;mov edx,29
;ano:
;mov ecx,320/4
;rep movsd
;add esi,320
;dec edx
;jnz ano
;POPALL
;
;PUSHALL
;mov ebx,[machin2]
;sub ebx,4*29*2
;neg ebx
;dec dword ptr [changementZZ2] ;000011000B
;jnz retterertrtey
;;mov dword ptr [changementZZ2],time_bouboule ;011000B
;;add [machin2],4
;;cmp [machin2],4*29*2
;;jne retterertrtey
;;mov [machin2],0
;;retterertrtey:
;
;
;mov esi,[machin+ebx]
;add esi,[machin3]
;add esi,640*1
;push ds
;pop  es
;push fs
;pop ds
;add esi,896000+64000*4 ; 128000  ;307200
;lea edi,buffer+173*320
;mov edx,27
;anoy:
;mov ecx,320/4
;rep movsd
;add esi,320
;dec edx
;jnz anoy
;POPALL
;
;ret
;copie_bande endp

horloge proc near
pushall

;inc es:[changementzz]
;

test [temps],01000000000000000B
jz clignote
;test dword ptr es:[changementzz],00000100000B
;jnz affiche_pas_deuxpointR
popall
ret
clignote:

;temps        dw 000200030000B  ;time
mov bp,temps

                ;1 bit, 3 bit,4 bits
;temps        db 10010001B  ;time

push ds
pop es
push fs
pop  ds
lea edi,buffer+320*183+277


push edi

xor eax,eax
mov ax,bp
shr ax,8
and ax,01111B
mov esi,896000+384000+46080+128000+83*320+80
shl eax,4
add esi,eax
aff_spt 16 11

mov esi,896000+384000+46080+128000+83*320+80+10*16
;lea edi,buffer+320*170+200+12

pop edi

push edi
add edi,12
test es:[temps],00100000000000000B
jnz affiche_pas_deuxpoint
aff_spt 16 5
affiche_pas_deuxpoint:

pop edi

;lea edi,buffer+320*170+200+12+6
push edi

add edi,12+6
xor eax,eax
mov ax,bp
shr ax,4
and ax,001111B
mov esi,896000+384000+46080+128000+83*320+80
shl eax,4
add esi,eax
aff_spt 16 11

pop edi
;,push edi
add edi,24+6
;lea edi,buffer+320*170+200+24+6
xor eax,eax
mov ax,bp
and ax,01111B
mov esi,896000+384000+46080+128000+83*320+80
shl eax,4
add esi,eax
aff_spt 16 11

popall
ret
endp
gestion_bdraw proc near

;test temps,000111111111111B
;jnz zerrezrezezrerrteerzerooo
;cmp in_the_apocalypse,0
;jne zerrezrezezrerrteerzerooo
;mov balance_le_bdrawn,1
;zerrezrezezrerrteerzerooo:

cmp balance_le_bdrawn,0
jne ereretereterreer233
ret
ereretereterreer233:

pushall
;mov bdraw666,'03'
;mov bdraw1,60

;cas particulier... on est entr‚ en phase 1 seul dyna vivant...
;on doit donc arreter le compte a rebourd...

cmp [attente_avant_med],attente_avant_med2
jne ertertertertetrertertertzet
;--

cmp word ptr bdraw666,'99'
je kjmlkjjkmlkjlmjklmjmkl
dec bdraw1
jnz kjmlkjjkmlkjlmjklmjmkl
mov bdraw1,60
dec bdraw666+1
cmp bdraw666+1,'0'-1
jne kjmlkjjkmlkjlmjklmjmkl
mov bdraw666+1,'9'
dec bdraw666
cmp bdraw666,'0'-1
jne kjmlkjjkmlkjlmjklmjmkl
mov bdraw666,'9'
kjmlkjjkmlkjlmjklmjmkl:

cmp adder_bdraw,0
je ertertertertetrertertertzet
sub adder_bdraw,320
ertertertertetrertertertzet:
;--------------
popall
ret
endp

dec_temps proc near
pushall

test temps,000111111111111B
jz zerooo
;mov balance_le_bdrawn,0
cmp temps2,15
jne nonononoiuioiohjrr

;--- deuxieme cas particulier-
cmp special_clignotement,0
je dommage_pp
dec special_clignotement
jmp special_fete
dommage_pp:
;-----------------------------
or  temps,00100000000000000B
mov ax,temps
and ax,0011111111111111B
cmp ax,000010001B
ja nonononoiuioiohjrr
special_fete:
or  temps,01000000000000000B ;clinotement g‚n‚ral.
nonononoiuioiohjrr:

cmp temps2,1
jne nonononoiuioiohjrrt
and  temps,01011111111111111B
test temps,01000000000000000B
jz nonononoiuioiohjrrt
bruit3 6 40 BLOW_WHAT2
and  temps,00111111111111111B ;glonotement global..
nonononoiuioiohjrrt:

dec temps2
jz ertterrtyrtyrtyyrt
popall
ret
zerooo:
;-*-*-*-*-*-*-*-*-*-*- apocalypse

cmp terrain,6
jne ertrtytyuyuiiyuughfdfgdfgfgdrtyrtyrtyerertertert
call pose_une_bombe_bonus
ertrtytyuyuiiyuughfdfgdfgfgdrtyrtyrtyerertertert:
;--------


;test dword ptr [changement],0000000000001B
;jnz finto_pasŠ_cetelmk

;133: virrer la brique. pour le milieu...

;test temps,000111111111111B
;jz zerooo
;
mov in_the_apocalypse,0

push ds
pop  es
lea esi,truc_fin
lea edi,truc
mov ecx,32*13
nextooi:
cmp byte ptr [esi],0
je nextooo

mov in_the_apocalypse,1                 ;indiquate the apocalypse is going on

;test temps,000111111111111B
;jz zerooo
;mov balance_le_bdrawn,0


;------------- vitesse de l'apocalypse... ---
mov eax,dword ptr [truc_fin+32*13] ;recup la vitesse.
test [changement],eax
jnz nextooo
  dec byte ptr [esi]

  ;quand arrive a 133 defonce ce kil y avait en dessous...
  ;mais ne posera pas de brike dure, puisuquon aurra mis byte ptr [esi] a 0
  ;malin...

  ;------ cas particulier... anti-brique... (et au milieu...)
  cmp byte ptr [esi],133
  jne nextooo567888888_
    mov special_nivo_6,60 ;indike de pas filler de bonus :) (cf. nivo 6)

      cmp terrain,6 ;terrain nivo 6
      je ertrtytyuyuiiyuughfdfgdfgfgdrtyrtyrtyertetttrrttrt
      mov balance_le_bdrawn,1 ;indique de balancer es 30 dernieres secondes
      ertrtytyuyuiiyuughfdfgdfgfgdrtyrtyrtyertetttrrttrt:

    cmp byte ptr [edi],2 ;pour brique.
    jne nextoooy
    ;194

      ;----- explosion de la brike ---
      cmp terrain,6 ;terrain nivo 6
      je ertrtytyuyuiiyuughfdfgdfgfgdrtyrtyrty
      mov byte ptr [edi],0         ;+degages la brique
      mov byte ptr [edi+32*13],194 ;+ explosion
      bruit3 4 40 BLOW_WHAT2
      jmp nextoooy
      ;------ cas particulier: nivo 6: brike se decompose
      ertrtytyuyuiiyuughfdfgdfgfgdrtyrtyrty:
      mov byte ptr [edi],3 ;casse la brique... normallement
      nextoooy:
    mov byte ptr [esi],0
    jmp nextooo
  nextooo567888888_:

  ;---------- endroit normal.. bombardement de piece dure.
  cmp byte ptr [esi],0
  jne nextooo
  cmp byte ptr [edi],1 ;si y'en a deja une...
  je nextooo
  ;194
  ;bruit2 4 40
  mov byte ptr [edi],11        ;place la brique dure.
  mov byte ptr [edi+32*13],194 ;+ explosion
  bruit2 4 40
nextooo:

inc edi
inc esi
dec ecx
jnz nextooi
finto_pasŠ_cetelmk:
popall
ret
;*--*-*-*-*-*-*-*-* d‚cr‚mentation du compte  rebour.
ertterrtyrtyrtyyrt:

mov temps2,59
;--------
mov ax,temps
and ax,01111B
dec ax
cmp ax,-1
jne pas_zeroret
mov ax,9
jmp canal_sux
pas_zeroret:
and temps,01111111111110000B
or temps,ax
popall
ret
canal_sux:
and temps,01111111111110000B
or temps,ax

mov ax,temps
shr ax,4
and ax,01111B
;mov bl,al
dec ax
cmp ax,-1
jne pas_zeroret7
mov ax,5
jmp stade
pas_zeroret7:
shl ax,4
and temps,01111111100001111B
or temps,ax
popall
ret
stade:
shl ax,4
and temps,01111111100001111B
or temps,ax

mov ax,temps
shr ax,8
;and ax,01111B
;mov bl,al
dec ax
cmp ax,-1
jne pas_zeroret72
mov ax,9
jmp stade
pas_zeroret72:
shl ax,8
and temps,01111000011111111B
or temps,ax

popall
ret
endp

gestion_blanchiment proc near
pushall
xor ebp,ebp
verite:
cmp [invinsible+ebp],0
je bababh
dec dword ptr [invinsible+ebp]
test changement,01000B
jz bababh
mov [clignotement+ebp],1
jmp fiert
bababh:
mov [clignotement+ebp],0 ; ,non...
fiert:
add ebp,4
cmp ebp,4*8
jne verite
popall
ret
endp
nike_toutes_ses_bombes proc near ;entree ebx: viseur infojoueur.
pushall
mov ecx,[liste_bombe]
or ecx,ecx
jz upasdutout
lea esi,liste_bombe+4-taille_dune_info_bombe
unext_bomby:
add esi,taille_dune_info_bombe
cmp dword ptr [esi+4],0
jne uya_bombe_ici
jmp unext_bomby
uya_bombe_ici:
;------- unqieuemnt si c'est notre propre bombe...
cmp dword ptr [esi],ebx
jne unon_dejar
;--------- uniquement si cette bombe etait a retardement...
cmp word ptr [esi+4*3+2],1
jne unon_dejar
mov word ptr [esi+4*3+2],2 ;la rend preske normalle .... ;0 ;le rend normalle
unon_dejar:
dec ecx
jnz unext_bomby
upasdutout:
popall
ret
endp

nike_toutes_les_bombes proc near
pushall
mov ecx,[liste_bombe]
or ecx,ecx
jz upasdutoutu
lea esi,liste_bombe+4-taille_dune_info_bombe
unext_bombyu:
add esi,taille_dune_info_bombe
cmp dword ptr [esi+4],0
jne uya_bombe_iciu
jmp unext_bombyu
uya_bombe_iciu:
;--------- uniquement si cette bombe etait a retardement...
mov word ptr [esi+4*3+2],0 ;le rend normalle
mov dword ptr [esi+1*4],1
dec ecx
jnz unext_bombyu
upasdutoutu:
popall
ret
endp


ligne_de_commande proc near
pushall

;push es
;mov ax,c
;mov es,ax
;mov di,offset score ;CommandLine
;pop es

  mov     ebx,82h
  xor eax,eax
  mov     al,es:[ebx-2]
  or      al,al
  jz      TestNext
mov ebp,eax
add ebp,82h
rettttttttttttttttttt:
  cmp     ebx,ebp
  je      mwaiwmai
  cmp     ebx,80+82h
  je      mwaiwmai
  cmp     byte ptr es:[ebx],0
  je      mwaiwmai

;cmp [assez_de_memoire],1  ; db 0  ; 0 OUI suffisament



;cmp [adder_speciale_cfg_path],3

;mov dl,13
;mov ah,2
;int 21h
;
;lea edx,setup_n_error
;mov ah,09h
;int 21h
;        mov bl,4 ;rouge
;        mov bh,10000000B ;indique clignotement
;        call last_color
;
;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h


;-------------
  cmp word ptr es:[ebx],'H-'
  je     mwaiwmaietrertrezi6
  cmp word ptr es:[ebx],'h-'
  je     mwaiwmaietrertrezi6
  cmp word ptr es:[ebx],'?-'
  jne     mwaiwmaietrerti6
mwaiwmaietrertrezi6:
lea edx,info666
mov ah,09h
int 21h
        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h
mwaiwmaietrerti6:
;----------------


  cmp word ptr es:[ebx],'i-'
  je     mwaiwmaietrertrezi
  cmp word ptr es:[ebx],'I-'
  jne     mwaiwmaietrerti
mwaiwmaietrertrezi:
mov [ipx_],0 ;y'aura pas d'ipx.
lea edx,setup_i
mov ah,09h
int 21h
mwaiwmaietrerti:

;--- pathhh
  cmp word ptr es:[ebx],'P-'
  je     mwaiwmaietrertrezir
  cmp word ptr es:[ebx],'p-'
  jne     mwaiwmaietrertir
mwaiwmaietrertrezir:
mov [adder_speciale_cfg_path],3
lea edx,pathing
mov ah,09h
int 21h
mwaiwmaietrertir:


;speed_raster,1

  cmp word ptr es:[ebx],'3-'
  jne mwaiwmaietrertin

cmp special_on_a_loadee_nivo,1
je mwaiwmaietrertin
cmp willrecord,1
je mwaiwmaietrertin

mov [assez_de_memoire],1
lea edx,setup_3
mov ah,09h
int 21h

mwaiwmaietrertin:


;max_lost dd 10 ;100         ; 15 ;connection lost max attente.... pour slave
;max_lost_master dd 4 ;20  ;2 ;connection lost max attente.... pour le master
;max_lost_master2 dd 8 ;80 ;5 ;attente accus‚ de reception...


  cmp word ptr es:[ebx],'T-'
  je     ymwaiwmaietrertrezin
  cmp word ptr es:[ebx],'t-'
  jne    ymwaiwmaietrertin
ymwaiwmaietrertrezin:
mov [speed_raster],1
lea edx,setup_T
mov ah,09h
int 21h
ymwaiwmaietrertin:

  cmp word ptr es:[ebx],'m-'
  je     ymwaiwmaietrertrezine
  cmp word ptr es:[ebx],'M-'
  jne    ymwaiwmaietrertine
ymwaiwmaietrertrezine:
mov [nomonster],1
lea edx,setup_m
mov ah,09h
int 21h
ymwaiwmaietrertine:

  cmp word ptr es:[ebx],'x-'
  je     ymwaiwmaietrertrezines
  cmp word ptr es:[ebx],'X-'
  jne    ymwaiwmaietrertines

ymwaiwmaietrertrezines:

;!!!!! autorise le reso dans winshit
mov ipx_,1
mov windows,0
mov windowsnetwork,1
;!!

mov modeinfo,1

;lea edx,setup_m
;mov ah,09h
;int 21h
;call zget_information
;
;        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
;        int 21h                         ; DOS INT 21h

ymwaiwmaietrertines:


  cmp word ptr es:[ebx],'F-'
  je     ymwaiwmaietrertreziney
  cmp word ptr es:[ebx],'f-'
  jne    ymwaiwmaietrertiney
ymwaiwmaietrertreziney:

cmp [assez_de_memoire],1
jne tokokokokeeeeeeeeeeur
lea edx,message_mem_rp
mov ah,09h
int 21h
        mov bl,4 ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color
        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h
tokokokokeeeeeeeeeeur:

  cmp word ptr es:[ebx+2],'46'
  jne zrezreezrzerymwaiwmaietrertreziney
mov save64,1
zrezreezrzerymwaiwmaietrertreziney:

mov willrecord,1
lea edx,setup_f
mov ah,09h
int 21h
ymwaiwmaietrertiney:


  cmp word ptr es:[ebx],'L-'
  je     rymwaiwmaietrertrezin
  cmp word ptr es:[ebx],'l-'
  jne    rymwaiwmaietrertin
rymwaiwmaietrertrezin:
mov max_lost,130
mov max_lost_master,100
mov max_lost_master2,100
lea edx,setup_l
mov ah,09h
int 21h
rymwaiwmaietrertin:

  cmp word ptr es:[ebx],'1-'
  jne  rymwaiwmaietrertrezin2reterttrtrtre
cmp [assez_de_memoire],1
je rymwaiwmaietrertrezin2reterttrtrtre
;  AH     = 3Bh
;  DS:EDX -> ASCIIZ path name
mov ah,03bh
lea edx,winsux
int 21h

mov economode,1
mov ipx_,0
mov special_on_a_loadee_nivo,1
mov on_a_bien_fait_une_partie,1
rymwaiwmaietrertrezin2reterttrtrtre:

;*************************************

  cmp word ptr es:[ebx],'R-'
  je     rymwaiwmaietrertrezin2
  cmp word ptr es:[ebx],'r-'
  jne    rymwaiwmaietrertin2
rymwaiwmaietrertrezin2:
;mov willrecord,0 ;disable si on avait mis un -F pour faire un record en meme
;mov differentesply2,0 ;retire le hazard
;mov differentesply,1966080+64000
; temps !!
mov on_a_bien_fait_une_partie,1
cmp [assez_de_memoire],1
jne okokokokeeeeeeeeeeur
lea edx,message_mem_rp
mov ah,09h
int 21h
        mov bl,4 ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color
        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h
okokokokeeeeeeeeeeur:


cmp dword ptr es:[ebx+2+1+8],'brm.'
je zerzertertyrrtyrtyrtytyryrttyrrtyrty
cmp dword ptr es:[ebx+2+1+8],'BRM.'
je zerzertertyrrtyrtyrtytyryrttyrrtyrty

;mov dl,byte ptr es:[ebx+2]
;cmp dl,'0'
;jb yerrroro
;cmp dl,'9'
;ja yerrroro
;mov dl,byte ptr es:[ebx+3]
;cmp dl,'0'
;jb yerrroro
;cmp dl,'9'
;ja yerrroro
;
;jmp zerzertertyrrtyrtyrtytyryrttyrrtyrty
;yerrroro:

mov dl,13
mov ah,2
int 21h

lea edx,suite3
mov ah,09h
int 21h
        mov bl,4 ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color

        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h

zerzertertyrrtyrtyrtytyryrttyrrtyrty:
mov eax,es:[ebx+3]
mov dword ptr [reccord2],eax
mov eax,es:[ebx+7]
mov dword ptr [reccord2+4],eax

lea edx,reccord3
mov ah,09h
int 21h
mov differentesply2,0 ;4*4
mov differentesply,1966080+64000
mov special_on_a_loadee_nivo,1
mov ipx_,0

rymwaiwmaietrertin2:
;*************************************

  cmp word ptr es:[ebx],'d-'
  je     yrymwaiwmaietrertrezin
  cmp word ptr es:[ebx],'D-'
  jne    yrymwaiwmaietrertin
yrymwaiwmaietrertrezin:
mov detail,1
lea edx,setup_d
mov ah,09h
int 21h
yrymwaiwmaietrertin:


;GIRL power
  cmp word ptr es:[ebx],'g-'
  je     mwaiwmaietrertrezi3
  cmp word ptr es:[ebx],'G-'
  jne     mwaiwmaietrerti3
mwaiwmaietrertrezi3:
mov [team3_sauve],2
lea edx,setup_s
mov ah,09h
int 21h
mwaiwmaietrerti3:

  cmp word ptr es:[ebx],'B-'
  je     mwaiwmaietrertrezi3b
  cmp word ptr es:[ebx],'b-'
  jne     mwaiwmaietrerti3b
mwaiwmaietrertrezi3b:
mov [twice],1
lea edx,setup_b
mov ah,09h
int 21h
mwaiwmaietrerti3b:

  cmp word ptr es:[ebx],'2-'
  jne erertertrmwaiwmaietrertrezi3b
mov [twice],1
mov [twice2],1
lea edx,setup_2
mov ah,09h
int 21h
erertertrmwaiwmaietrertrezi3b:



  cmp word ptr es:[ebx],'%-'
  jne     tmwaiwmaietrerti33
mov stat_ou_pas,1
lea edx,setup_%
mov ah,09h
int 21h
tmwaiwmaietrerti33:


;mov ipx_,0
;lea edx,tected
;sub edx,offset tectew
;neg edx
;mov [tecte2],edx
;
;mov windows,1


  cmp word ptr es:[ebx],'W-'
  je     mwaiwmaietrertrezi33t
  cmp word ptr es:[ebx],'w-'
  jne     mwaiwmaietrerti33t
mwaiwmaietrertrezi33t:
lea edx,setup_w
mov ah,09h
int 21h

;!!!!! autorise le reso dans winshit
mov ipx_,1
mov windows,0
mov windowsnetwork,1
;!!

mwaiwmaietrerti33t:


;color
  cmp word ptr es:[ebx],'c-'
  je     mwaiwmaietrertrezi33
  cmp word ptr es:[ebx],'C-'
  jne     mwaiwmaietrerti33
mwaiwmaietrertrezi33:
mov [team3_sauve],1
lea edx,setup_c
mov ah,09h
int 21h
mwaiwmaietrerti33:

;-k option
  cmp word ptr es:[ebx],'k-'
  je     mwaiwmaietrertrezi33k
  cmp word ptr es:[ebx],'K-'
  jne     mwaiwmaietrerti33k
mwaiwmaietrertrezi33k:
mov [kli_option],1
lea edx,setup_k
mov ah,09h
int 21h
mwaiwmaietrerti33k:

  cmp word ptr es:[ebx],'E-'
  je     mwaiwmaietrertrezi33kE
  cmp word ptr es:[ebx],'e-'
  jne     mwaiwmaietrerti33kE
mwaiwmaietrertrezi33kE:
mov demande_partie_slave2,1
lea edx,setup_E
mov ah,09h
int 21h
mwaiwmaietrerti33kE:


;nombre_minimum_de_dyna dd 2
;team    dd 0,1,2,3,4,5,6,7 ;par default
;c_team  dd 0,0,1,1,2,2,3,3 ;par couleur
;        dd 3 ;minimum joueurs
;s_team  dd 0,1,0,1,0,1,0,1 ;par sexe
;        dd 2

  cmp word ptr es:[ebx],'n-'
  je     mwaiwmaietrertrezint
  cmp word ptr es:[ebx],'N-'
  jne     mwaiwmaietrertint
mwaiwmaietrertrezint:
lea edx,setup_n
mov ah,09h
int 21h

;!!!!! autorise le reso dans winshit
mov ipx_,1
mov windows,0
mov windowsnetwork,1
;!!


mov dl,byte ptr es:[ebx+2]
cmp dl,'0'
jb errroro
cmp dl,'9'
ja errroro

push cx
xor cx,cx
mov cl,dl
sub cl,'0'
shl cx,2
shl cx,8
mov [grosse_sochette],cx
pop cx


;----
mov ah,2
int 21h
mov dl,'.'
mov ah,2
int 21h
mov dl,10
mov ah,2
int 21h
mov dl,13
mov ah,2
int 21h
jmp mwaiwmaietrertint
;----------- retours au dos si mauvais parametre ici... ------
errroro:

mov dl,13
mov ah,2
int 21h

lea edx,setup_n_error
mov ah,09h
int 21h
        mov bl,4 ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color

        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h
popall
ret
;-------------------------------------------------------------
mwaiwmaietrertint:



  cmp word ptr es:[ebx],'S-'
  je     mwaiwmaietrertrez
  cmp word ptr es:[ebx],'s-'
  jne     mwaiwmaietrert
mwaiwmaietrertrez:
lea edx,setup_
mov ah,09h
int 21h


mov _setup_,1
mwaiwmaietrert:

;cmp [ipx_],1 ; dd 1 ;1:oui_ par default... (indique teste serra fait...)
;             ;0:non...
;jne onenveutpas

;  mov byte ptr es:[ebx],0

  inc ebx
  jmp rettttttttttttttttttt
mwaiwmai:

;  jmp     NoCmdLine
;push es
;mov ax,c
;mov es,ax
;mov di,offset score ;CommandLine
;pop es
;  mov     bx,82h
;  mov     al,es:[bx-2]
;  cmp     al,0
;  jne     TestNext
;  jmp     NoCmdLine

popall
ret

TestNext:
lea edx,pas_ligne
mov ah,09h
int 21h
mov bx,13 ;rose
      ;  mov bh,10000000B ;indique clignotement
        call last_color

popall
ret
endp


setup proc near
pushall

push ds
pop  es

;3.14 - Function 3Dh - Open File:
;--------------------------------
;
;In:
;  AH   = 3Dh
;  AL   = open code
;  DS:EDX -> ASCIIZ path name
;
;Out:
;  if successful:
;    carry flag clear
;    EAX = handle
;
;  if failed:
;    carry flag set
;    EAX = error code
mov ah,03dh
mov al,0
mov cfgfile2,0
lea edx,cfgfile
add edx,[adder_speciale_cfg_path]
int 21h
jc eooooooooookyu

;3.15 - Function 3Fh - Read From File:
;-------------------------------------
;
;In:
;  AH   = 3Fh
;  BX   = file handle
;  ECX  = number of bytes to read
;  DS:EDX -> buffer to read to
mov bx,ax
mov ah,3fh
mov ecx,512
lea edx,loaded_f
int 21h
jc eooooooooookyu
;---------- v‚rifie l'int‚grit‚ du fichier config ---
lea esi,loaded_f
mov cx,511
xor bl,bl
ererrteerertty:
lodsb
add bl,al
dec cx
jne ererrteerertty
cmp [esi],bl
jne eooooooooookyu
;---------- utilise la config pour les touches
lea esi,loaded_f
lea edi,touches_
mov ecx,256/4
rep movsd
lodsd
mov setup_viseur2,eax ;et pour le choix de force de la carte son

;---------- affiche le fichier ki a ‚t‚ utilis‚.
lea edx,okcfg
cmp [adder_speciale_cfg_path],3
jne tyutyutyutyutyu
lea edx,okcfg3
tyutyutyutyutyu:
mov ah,9
int 21h

jmp heypiiiiiiiiiiiiiiiiiiiiiiiiiiii
eooooooooookyu:;pas trouv‚ de fichier cfg (ou erreur dedans)
cmp _setup_,1 ;affiche pas de message d'erreur si on a lanc‚ l'option :)
je heypiiiiiiiiiiiiiiiiiiiiiiiiiiii

lea edx,cfgerror
mov ah,09h
int 21h
;mov windows,1
        mov bl,11 ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color
heypiiiiiiiiiiiiiiiiiiiiiiiiiiii:

cmp _setup_,1
jne errteretertert ;sortie

;        call    GetForegroundWindow
;        mov     [winhdle],eax
;        push    3
;        push    [winhdle]
;        call    ShowWindow
;        push    [winhdle]
;        call    IsZoomed
;        or      eax,eax
;        je      OKDOSINFULLSCREEN
;        push    0
;        push    0
;        push    0407h
;        push    [winhdle]
;        call    SendMessageA
;OKDOSINFULLSCREEN:


;***************************** AFFICHE LE MENU DE SETUP *********************
;,cmp windows,1
;jne eertyertertterertertertertert
        lea edx,wsetup
        mov ah,09h
        int 21h
        mov bl,00 ;000B ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color

        lea edx,wsetup2
        mov ah,09h
        int 21h
        call last_color
        lea edx,wsetup3
        mov ah,09h
        int 21h
        call last_color
        lea edx,wsetup4
        mov ah,09h
        int 21h
        call last_color
        lea edx,wsetup5
        mov ah,09h
        int 21h
        call last_color

eertyertertterertertertertert:

lea edx,setup1
mov ah,9
int 21h
call affiche_setup1
;call affiche_rouge
erertertertprerezezeryyyyyyooooooo:
call vbl
xor ebp,ebp

;********** fleches radicalles *******
cmp byte ptr [clavier+120],1 ;shaut
jne ertttttttttttttttttter
mov setup_viseur,0
inc ebp
ertttttttttttttttttter:

cmp byte ptr [clavier+119],1 ;sbas
jne erttttttttttttttttttert
mov setup_viseur,max_s
inc ebp
erttttttttttttttttttert:
;-*****************************

hautbas setup_viseur max_s

;*********************************** RETURN PRESSE ?? ************

cmp setup_wait4,0
jz reeeeeeetertrtrteertertyuuttrrtytyrtry
dec setup_wait4
jmp reeeeeeetertrtrteertertyuu
reeeeeeetertrtrteertertyuuttrrtytyrtry:

cmp byte ptr [clavier+28],1
jne reeeeeeetertrtrteertertyuu

mov setup_wait4,setup_wait*2

;---- retours au dos
cmp setup_viseur,max_s-1
jne errrrrrrrtyyuii
mov ou_ca_setup,3
call affiche_setup1
mov sortie_config,1
popall
ret
errrrrrrrtyyuii:
;---- sauvegarde...
cmp setup_viseur,max_s
jne errrrrrrrtyyuiit
mov ou_ca_setup,3
call affiche_setup1

lea edi,loaded_f
lea esi,touches_
mov ecx,256/4
rep movsd
mov eax,setup_viseur2
stosd

lea esi,loaded_f
mov cx,511
xor bl,bl
ererrteererttyr:
lodsb
add bl,al
dec cx
jne ererrteererttyr
mov [esi],bl

;  AH     = 3Ch
;  CX   = attribute
;  DS:EDX -> ASCIIZ path name
;
;Out:
;  if successful:
;    carry flag clear
;    EAX = handle
mov ah,03ch
mov cx,0
lea edx,cfgfile
add edx,[adder_speciale_cfg_path]
int 21h
jc erreurf
;  AH     = 40h
;  BX   = file handle
;  ECX  = number of bytes to write
;  DS:EDX -> buffer to write from
mov bx,ax
mov ah,040h
mov ecx,512
lea edx,loaded_f
int 21h

jmp errteretertert
erreurf:
lea edx,errorcfg
mov ah,9
int 21h
        mov bl,4  ;rouge
        mov bh,10000000B ;indique clignotement
        call last_color

jmp errteretertert
errrrrrrrtyyuiit:

;----- changement sound card
cmp setup_viseur,0
jne noooooooooooi0
call change_card
noooooooooooi0:

;----- changement touche joueur 1
cmp setup_viseur,1
jne noooooooooooi
mov al,1 ;numero du joueur...
call change_touches
noooooooooooi:
;----- changement touche joueur 2
cmp setup_viseur,2
jne noooooooooooi2
mov al,2 ;numero du joueur...
call change_touches
noooooooooooi2:

;----- changement ON/OFF joueur 3
cmp setup_viseur,3
jne noooooooooooi3r
inc ebp ;!!
NOT dword ptr [touches_+8*4*2+7*4]
noooooooooooi3r:
;----- changement ON/OFF joueur 4
cmp setup_viseur,5
jne noooooooooooi4r
inc ebp ;!!
NOT dword ptr [touches_+8*4*3+7*4]
noooooooooooi4r:
;----- changement ON/OFF joueur 5
cmp setup_viseur,7
jne noooooooooooi5r
inc ebp ;!!
NOT dword ptr [touches_+8*4*4+7*4]
noooooooooooi5r:
;----- changement ON/OFF joueur 6
cmp setup_viseur,9
jne noooooooooooi6r
inc ebp ;!!
NOT dword ptr [touches_+8*4*5+7*4]
noooooooooooi6r:
;----- changement ON/OFF joueur 7
cmp setup_viseur,11
jne noooooooooooi7r
inc ebp ;!!
NOT dword ptr [touches_+8*4*6+7*4]
noooooooooooi7r:
;----- changement ON/OFF joueur 8
cmp setup_viseur,13
jne noooooooooooi8r
inc ebp ;!!
NOT dword ptr [touches_+8*4*7+7*4]
noooooooooooi8r:

;----- changement touche joueur 3
cmp setup_viseur,4
jne noooooooooooi3
mov al,3 ;numero du joueur...
call change_touches
noooooooooooi3:

;----- changement touche joueur 4
cmp setup_viseur,6
jne noooooooooooi4
mov al,4 ;numero du joueur...
call change_touches
noooooooooooi4:
;----- changement touche joueur 5
cmp setup_viseur,8
jne noooooooooooi5
mov al,5 ;numero du joueur...
call change_touches
noooooooooooi5:
;----- changement touche joueur 6
cmp setup_viseur,10
jne noooooooooooi6
mov al,6 ;numero du joueur...
call change_touches
noooooooooooi6:
;----- changement touche joueur 7
cmp setup_viseur,12
jne noooooooooooi7
mov al,7 ;numero du joueur...
call change_touches
noooooooooooi7:
;----- changement touche joueur 8
cmp setup_viseur,14
jne noooooooooooi8
mov al,8 ;numero du joueur...
call change_touches
noooooooooooi8:

;********************************************************
reeeeeeetertrtrteertertyuu:


;---------- modification de l'ecran...
or ebp,ebp
jz erttttttttttttttttttttttt
;call affsigne
;;-------- affichage des touches correspondant a la personne sur la kelle on est
;;------------------

call affiche_setup1
call affiche_touches_totales

;**************** pas d'affichage *************
erttttttttttttttttttttttt:

jmp erertertertprerezezeryyyyyyooooooo ;retour boucle.

;cmp byte ptr [clavier+1],1
;jne erertertertprerezezeryyyyyyooooooo

errteretertert:
popall
ret
affiche_rouge:
pushall
mov ebx,setup_viseur
shl ebx,3
;mviseur_rouge dd 0b8000h+80*2*06+1+2,35

mov edi,[viseur_rouge+ebx] ;0b8000h+80*2*06+1+2
mov esi,edi
mov ecx,[viseur_rouge+ebx+4]
reerererte:
lodsb
;or al,bh
;and al,00000100B
;or  al,00110000B
mov al,01001111B
cmp ou_ca_setup,0
jne erertrtee2
mov al,11001111B
erertrtee2:

stosb
inc edi
inc esi
dec cx
jnz reerererte
popall

pushall
mov ebx,setup_viseur2
shl ebx,3
;mviseur_rouge dd 0b8000h+80*2*06+1+2,35

mov edi,[viseur_rouge3+ebx] ;0b8000h+80*2*06+1+2
mov esi,edi
mov ecx,[viseur_rouge3+ebx+4]
reerererte23:
lodsb
;or al,bh
;and al,00000100B
;or  al,00110000B
mov al,01011111B
cmp ou_ca_setup,1
jne erertrtee
mov al,11011111B
erertrtee:
stosb
inc edi
inc esi
dec cx
jnz reerererte23
popall

ret
;viseur_rouge dd 80*2+10

affiche_rouge2:
pushall
shl ebx,3
;mviseur_rouge dd 0b8000h+80*2*06+1+2,35

mov edi,[viseur_rouge2+ebx] ;0b8000h+80*2*06+1+2
mov esi,edi
mov ecx,[viseur_rouge2+ebx+4]
reerererte2:
lodsb
;or al,bh
;and al,00000100B
;or  al,00110000B
mov al,10011111B
stosb
inc edi
inc esi
dec cx
jnz reerererte2
popall
ret
;viseur_rouge dd 80*2+10


affiche_setup1:

pushall
mov edi,0b8000h+80*2*05+1
push edi
mov ecx,80*19
xor eax,eax
ireerererte:
mov al,15
stosb
inc edi
dec ecx
jnz ireerererte
pop edi

;touches_  dd 114,115,113,112,82,83,0, 1
;          dd 20,21,30,16,57,15,0,     1
;          dd 0,0,0,0,0,0,0,           1
;          dd 0,0,0,0,0,0,0,           1
;          dd 0,0,0,0,0,0,0,           0
;          dd 0,0,0,0,0,0,0,           0
;          dd 0,0,0,0,0,0,0,           1
;          dd 0,0,0,0,0,0,0,           0


mov ebx,8*4*2+7*4
mov cx,6
zerzerzerzer:
mov byte ptr [edi+80*4*2+27],'O'
mov byte ptr [edi+80*4*2+27+1],12
mov byte ptr [edi+80*4*2+27+2],'F'
mov byte ptr [edi+80*4*2+27+2+1],12
mov byte ptr [edi+80*4*2+27+4],'F'
mov byte ptr [edi+80*4*2+27+4+1],12
cmp [touches_+ebx],0
je rteterterrteter
mov byte ptr [edi+80*4*2+27],'O'
mov byte ptr [edi+80*4*2+27+1],15
mov byte ptr [edi+80*4*2+27+2],'N'
mov byte ptr [edi+80*4*2+27+2+1],15
mov byte ptr [edi+80*4*2+27+4],' '
mov byte ptr [edi+80*4*2+27+4+1],15
rteterterrteter:

add edi,80*2*2
add ebx,8*4
dec cx
jnz zerzerzerzer

popall
call affiche_rouge
ret

endp

change_card proc near
pushall

mov ou_ca_setup,1
call affiche_setup1

reeeeeeetertrtrteertertyuueerre:
cmp byte ptr [clavier+28],0
jne reeeeeeetertrtrteertertyuueerre

reeeeeeetertrtrteertertyuueerr:

call vbl
xor ebp,ebp

hautbas setup_viseur2 max_s2

;********** fleches radicalles *******
cmp byte ptr [clavier+120],1 ;shaut
jne ertttttttttttttttttterr
mov setup_viseur2,0
inc ebp
ertttttttttttttttttterr:

cmp byte ptr [clavier+119],1 ;sbas
jne erttttttttttttttttttertr
mov setup_viseur2,max_s2
inc ebp
erttttttttttttttttttertr:
;-*****************************
or ebp,ebp
jz pas_ffertrterte
call affiche_setup1
pas_ffertrterte:

cmp byte ptr [clavier+28],1
jne reeeeeeetertrtrteertertyuueerr

mov ou_ca_setup,0
call affiche_setup1

popall
ret
endp

change_touches proc near ;dans al: numero du joueur (1 a 8)
pushall

mov ou_ca_setup,2
call affiche_setup1

ereeeeeeetertrtrteertertyuueerree:
cmp byte ptr [clavier+28],0
jne ereeeeeeetertrtrteertertyuueerree
mov [last_sucker],0

lea edi,touches_
push eax
dec eax
and eax,127
shl eax,5
add edi,eax
pop eax

mov ebx,0b8000h+80*2*06+85+8*2+1
add al,'0'
mov [ebx],al
;-------

mov bl,[last_sucker]
;call transforme_bl
;viseur_rouge2

mov ecx,7 ;6
reteetrertertrteert:
push ebx ecx
dec ecx
mov ebx,ecx
call affiche_rouge2
pop ecx ebx

;viseur_rouge2 dd 0b8000h+80*2*06+1+2+2+40,18
cmp bl,[last_sucker]
je reteetrertertrteert ;deja presse juste avant...


xor ebx,ebx
mov bl,[last_sucker]
;--
mov ax,bx
;call affsigne ;!!
call affiche_touche_choisit

push ebx
shl ebx,4
lea esi,[touches_prises+ebx]
pop ebx
cmp [esi],' A/N'
jne erttyerrtyrtyrtyyrt
jmp reteetrertertrteert
erttyerrtyrtyrtyyrt:

;validation de la touche
mov [edi],ebx
add edi,4
;---

call affiche_setup1

dec ecx
jnz reteetrertertrteert

mov dword ptr [edi],-1

mov ou_ca_setup,0
call affiche_setup1

popall
ret

affiche_touches_totales: ;affiche les touches ki correspondent a l'endroit
                         ;on on est
pushall

xor eax,eax
mov ebx,setup_viseur
mov al,[what_t+ebx]
or al,al
jnz nanana_pasici ;sauf si on est a un endroit ou c'est pas la peine.
popall
ret
nanana_pasici:

lea esi,touches_
push eax
dec eax
and eax,127
shl eax,5
add esi,eax
pop eax

mov ebx,0b8000h+80*2*06+85+8*2+1
add al,'0'
mov [ebx],al
;-------

;mov bl,[last_sucker]
;call transforme_bl
;viseur_rouge2

mov ecx,7 ;6
reteetrertertrteertu:
;push ebx ecx
;dec ecx
;mov ebx,ecx
;;call affiche_rouge2
;pop ecx ebx
;
;;viseur_rouge2 dd 0b8000h+80*2*06+1+2+2+40,18
;cmp bl,[last_sucker]
;je reteetrertertrteert ;deja presse juste avant...


xor ebx,ebx

;mov bl,[last_sucker]

;mov ax,bx
;call affsigne ;!!
;mov ebx,0
mov ebx,[esi]
call affiche_touche_choisit

;push ebx
;shl ebx,4
;lea esi,[touches_prises+ebx]
;pop ebx
;cmp [esi],' A/N'
;jne erttyerrtyrtyrtyyrt
;jmp reteetrertertrteert
;erttyerrtyrtyrtyyrt:
;
;;validation de la touche
;mov [edi],ebx
add esi,4
;;---

;call affiche_setup1

dec ecx
jnz reteetrertertrteertu

;call affiche_setup1
popall
ret

affiche_touche_choisit:
pushall
dec ecx
shl ecx,3
;mviseur_rouge dd 0b8000h+80*2*06+1+2,35

mov edi,[viseur_rouge2+ecx] ;0b8000h+80*2*06+1+2
dec edi

shl ebx,4 ;*16

lea esi,[touches_prises+ebx]
lodsb
mov [edi+17*2],al
lodsb
mov [edi+18*2],al
lodsb
mov [edi+19*2],al
lodsb
mov [edi+20*2],al
lodsb
mov [edi+21*2],al
lodsb
mov [edi+22*2],al
lodsb
mov [edi+23*2],al
lodsb
mov [edi+24*2],al
lodsb
mov [edi+25*2],al
lodsb
mov [edi+26*2],al
lodsb
mov [edi+27*2],al
lodsb
mov [edi+28*2],al
lodsb
mov [edi+29*2],al

popall
ret
endp

;;transforme_bl proc near ;fait passer dans le tableau de correspondance.
;push esi
;mov esi,ebx
;and esi,127
;mov bl,[correspo+esi]
;pop esi
;ret
;endp

ewindows proc near
pushall
        mov     ax,1600h
        int     2Fh
        or      al,al
        jz      @@nowin
        cmp     al,80h
        jz      @@nowin
mov ah,9
lea edx,win
int 21h

;------------------------

;pushall
;mov ax,02fh
;mov ax,1684h
;mov bx,07fe0h
;int 2Fh
;mov ax,di
;
;call affsigne

;
;call clear_call_int
;mov [call_int+10h],0

;mov [call_int+1Ch],01684h
;mov [call_int+10h],07fe0h

;mov word ptr [call_int+14h],dx

;mov [call_int+14h],edx

;call_int dd 0 ;           00h     4       EDI
;dd 0 ;           04h     4       ESI
;dd 0 ;           08h     4       EBP
;dd 0 ;           0ch     4       reserved, ignored
;dd 0 ;           10h     4       EBX
;dd 0 ;           14h     4       EDX
;dd 0 ;           18h     4       ECX
;dd 0 ;           1ch     4       EAX
;dw 0 ;           20h     2       CPU status flags
;dw 0 ;           22h     2       ES
;dw 0 ;           24h     2       DS
;dw 0 ;           26h     2       FS
;dw 0 ;           28h     2       GS
;dw 0 ;           2ah     2       IP
;dw 0 ;           2ch     2       CS
;dw 0 ;           2eh     2       SP
;dw 0 ;           30h     2       SS

;  AX     = 0300h
;  BL     = interrupt number
;  BH     = must be 0
;  CX     = number of words to copy from the protected mode stack to the real
;           mode stack
;  ES:EDI = selector:offset of real mode register data structure in the
;;           following format:
;push es
;mov ax,ds
;mov es,ax
;mov edi,offset call_int
;mov cx,0
;mov bh,0
;mov bl,02Fh
;mov ax,300h
;int 31h
;pop es
;
;mov ax,word ptr [call_int+022h] ;es ;
;mov ebx,[call_int+00h] ;edi
;
;;call affsigne
;push ax ebx
;call clear_call_int
;pop ebx ax

;dw 0 ;           2ah     2       IP
;dw 0 ;           2ch     2       CS

;mov word ptr [call_int+02ah],bx ;edi ;
;mov word ptr [call_int+02ch],ax ;es ;
;
;push es
;mov ax,ds
;mov es,ax
;mov edi,offset call_int
;mov cx,0
;mov bh,0
;mov bl,02Fh
;mov ax,301h
;int 31h
;pop es
;
;popall
;
;------------------------

mov ipx_,0

lea edx,tected
sub edx,offset tectew
neg edx
mov [tecte2],edx

mov windows,1
popall
ret
@@nowin:
mov ah,9
lea edx,nowin
int 21h
popall
ret
endp

pousse_la_bombe proc near
pushall
;cmp byte ptr [esi+32*13],1
;jb efrerrereterter
;cmp byte ptr [esi+32*13],4
;ja efrerrereterter
;--- ya une bombe !!! essaye de la pousser ---
;
;call pouse_la_bombe
sub esi,offset truc

;recherche cette bombe.
xor ebx,ebx
ttyrrtyrtyrtyrtytyrrtyrtyyrtrtye:
cmp dword ptr [liste_bombe+ebx+4+1*4],0 ;indique emplacement non remplis !!!
je cherche_encore
cmp dword ptr [liste_bombe+ebx+4+2*4],esi ;regarde si ya une bombe a cet endroit
jne cherche_encore
jmp okey_on_puse
cherche_encore:
add ebx,taille_dune_info_bombe
jmp ttyrrtyrtyrtyrtytyrrtyrtyyrtrtye
okey_on_puse:

;mov dword ptr [liste_bombe+ebx+4+1*4],1
;
;on peut pousser ke si elle est au milieu
cmp word ptr [liste_bombe+ebx+4+5*4],0    ; adder X
jne peu_pas_pousser                       ;
cmp word ptr [liste_bombe+ebx+4+5*4+2],0  ;adder Y
jne peu_pas_pousser

;---- cas particulier -- on ne pousse pas vers le bas en bas ----
;cas particulier speical cote rebondissant pour eviter kon fasse rebondir
;contre un mur alors ke la bombe y est colle.
;bas
cmp esi,32*11
jb pas_ce_cas_larrr
cmp ecx,2
je peu_pas_pousser
pas_ce_cas_larrr:
;haut
cmp esi,32*2
jnb pas_ce_cas_larrr2
cmp ecx,2
je peu_pas_pousser
pas_ce_cas_larrr2:

and esi,31
;gauche
cmp esi,1
jne pas_ce_cas3
or ecx,ecx
jz peu_pas_pousser
pas_ce_cas3:

;droite
cmp esi,17
jne pas_ce_cas5
or ecx,ecx
jz peu_pas_pousser
pas_ce_cas5:
;----------------------------------------------------

mov dword ptr [liste_bombe+ebx+4+4*4],0    ;pour degager l'ancien mouvement
                                           ;si elle bougait
                                           ;deja...
add ebx,ecx ;!!!!!!!!!!!!                  ;oU y automatique cA dEPENT dE eCX
mov word ptr [liste_bombe+ebx+4+4*4],ax ;0 ;!!!!!!!!!1 ;adder X automatique.

peu_pas_pousser:
;mov word ptr [liste_bombe+ebx+4+4*4+2],0
;mov word ptr [liste_bombe+ebx+4+5*4],15   ;adder X
;mov word ptr [liste_bombe+ebx+4+5*4+2],0 ;adder Y
popall
ret
endp

affiche_en_mode_texte proc near
pushall

push ds
pop es

mov edi,0b8000h+((80-19)*2)
lea esi,truc


;truc  db 32*13 dup (?)
; db 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13 dup (0)
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
mov dx,13
ijhrere:
mov cx,19
nooonr:
xor eax,eax
lodsb
add eax,eax
mov ebx,eax
mov ax,word ptr [correspondance_mode_texte+ebx]

;or al,bh
;and al,11110000B
;or  al,bl
stosw

dec cx
jne nooonr
add edi,(80-19)*2
add esi,13
dec dx
jnz ijhrere

;------------ monstres

mov edi,0b8000h+((80-19)*2)
lea esi,truc_monstre

mov dx,13
tijhrere:
mov cx,19
tnooonr:
xor eax,eax
lodsb
cmp al,''
jne rerteterrterte
stosb
jmp mklhjrtyyrt
rerteterrterte:
inc edi
mklhjrtyyrt:
inc edi
dec cx
jne tnooonr
add edi,(80-19)*2
add esi,13
dec dx
jnz tijhrere

popall
ret
endp

;truc_monstre db 32*13 dup (?)
fabrique_monstro_truc proc near
pushall
push ds
pop es
lea edi,truc_monstre
xor eax,eax
mov ecx,32*13/4
rep stosd

xor ebp,ebp
zecompetion:
cmp [vie+ebp],1
jne  fdggrtetyrklmjyurtmkljrtymjklyut

push ebp
xy_to_offset
mov [truc_monstre+eax],''
pop ebp
fdggrtetyrklmjyurtmkljrtymjklyut:
add ebp,4
cmp ebp,8*4
jne zecompetion

popall
ret
endp


pose_une_bombe_bonus proc near
pushall
;call noping
;liste_bombbbb dd 32+1
;              dd 32*3+1
;              dd 32*5+1
;              dd 32*7+1
;              dd 32*9+1
;
cmp [attente_avant_med],attente_avant_med2
jne errteerterttyjtyutyuutytyuyutyutyututy

;test dword ptr [changement],0000000000111B
;jnz errteerterttyjtyutyuutytyuyutyutyututy
;

cmp attente_entre_chake_bombe,0
je okokokokok_cette_fois
dec attente_entre_chake_bombe
jmp errteerterttyjtyutyuutytyuyutyutyututy
okokokokok_cette_fois:

add viseur__nouvelle_attente_entre_chake_bombe,4

;nouvelle_attente_entre_chake_bombe2 dd 16,21,17,9,20,15,12,20
lea esi,nouvelle_attente_entre_chake_bombe2
add esi,viseur__nouvelle_attente_entre_chake_bombe
cmp esi,offset viseur__nouvelle_attente_entre_chake_bombe
jne ertteertertertertter
cmp [acceleration],20
je retteterrterteterertert
inc [acceleration]
retteterrterteterertert:
mov viseur__nouvelle_attente_entre_chake_bombe,0
lea esi,nouvelle_attente_entre_chake_bombe2
ertteertertertertter:

mov ebx,[esi]
sub ebx,[acceleration]
js loupe
jz loupe
jmp rrtyertyrtyrtyrtyertyrtytyr
loupe:
mov ebx,1
rrtyertyrtyrtyrtyertyrtytyr:
mov attente_entre_chake_bombe,ebx


mov ebx,liste_bombbbb2
add ebx,12
lea esi,liste_bombbbb+ebx
cmp esi,offset liste_bombbbb2
;
;cmp ebx,4*6
jne e6rtertertert
xor ebx,ebx
e6rtertertert:
mov liste_bombbbb2,ebx
mov eax,[liste_bombbbb+ebx]
mov dx,word ptr [liste_bombbbb+4+ebx]
mov cx,word ptr [liste_bombbbb+6+ebx]
mov ebp,dword ptr [liste_bombbbb+8+ebx]
lea esi,truc2
;mov eax,32*1+1
add esi,eax

cmp byte ptr [esi-32*13],0 ;regarde si ya rien ou l'on veut placer la bombe
jne  ytreteterrterteterertter
cmp byte ptr [esi],0 ;regarde si ya rien ou l'on veut placer la bombe
jne  ytreteterrterteterertter

;cmp cx,-1
;jne retterertertertter
;sub esi,2
;retterertertertter:
;inc esi
;cmp byte ptr [esi-32*13],0 ;regarde si ya rien ou l'on veut placer la bombe
;jne  ytreteterrterteterertter
;cmp byte ptr [esi-32*13],0 ;regarde si ya rien ou l'on veut placer la bombe
;jne  ytreteterrterteterertter
;cmp byte ptr [esi],0 ;regarde si ya rien ou l'on veut placer la bombe
;jne  ytreteterrterteterertter
;cmp cx,-1
;jne rettererterterttere
;add esi,2
;rettererterterttere:
;dec esi

mov byte ptr [esi],1

;dec dword ptr [edi] ;nombre de bombes k'on peut encore poser...

;donnee dw 20,20,277,277,150,200,250,280  ;x du dynablaster
;       dw 9,170,9,170,78,98,98,10 ;y du dynablaster

;liste_bombe dd 0 ; nombre de bombes...
;            dd 247 dup (0,0,0,0)
;1er: offset de l'infojoeur
;2eme: nombre de tours avant que ca PETE !!! ; si = 0 ca veut dire
;                                            ;emplacement libre...
;3eme:distance par rapport au debut de truc2
;4eme:DD= 1 DW: puissance de la bombe + 1 DW: bombe a retardement ??? (=1)
;5eme: VITESSE:1 db:X (+1/-1/0) ,1 db:Y (+1/-1/0);+ 2 db VIDE
;6eme: ADDER_X/Y: 1 dw:X,1 dW:Y


;mov ebx,[liste_bombe]
;shl ebx,4 ;*16

;recherche la premiere place de libre !!!
xor ebx,ebx
yttyrrtyrtyrtyrtytyrrtyrtyyrtrty:
cmp dword ptr [liste_bombe+ebx+4+1*4],0 ;indique emplacement non remplis !!!
je yerertertrteterert
add ebx,taille_dune_info_bombe
jmp yttyrrtyrtyrtyrtytyrrtyrtyyrtrty
yerertertrteterert:

;mov edx,3 ;dword ptr [edi+4]        ;r‚cupere la puissance de la bombe dans
                                 ;l'info du joueur...
;mov ecx,256 ;dword ptr [edi+8]        ;r‚cupere la taille de la meiche de la
                                 ;bombe dans l'info du joueur...

;------------------------------------ mouvement de la bombe
;truc_X   db 32*13 dup (0) ;+ ou -...
;truc_Y   db 32*13 dup (0)

;push dx
;  cmp dx,-7
;  jne zerertrterteterert
;  mov dl,-7
;  zerertrterteterert:
  mov byte ptr [truc_X+eax],dl  ;;;;;;;;;;;;;;;;;;;;;;;;;;dl ;0
;pop dx

mov byte ptr [truc_Y+eax],0

mov [liste_bombe+ebx+4+0*4],offset infojoueur2
mov [liste_bombe+ebx+4+1*4],ebp ;ecx  ;nombre de tours avant que ca PETE !!!
mov [liste_bombe+ebx+4+2*4],eax  ;distance par rapport au debut de truc2
mov word ptr [liste_bombe+ebx+4+3*4],3 ;dx  ;puissance de la bombe.
mov word ptr [liste_bombe+ebx+4+3*4+2],0 ;dx  ;bombe a retardement ou pas ???
mov word ptr [liste_bombe+ebx+4+4*4],cx ;adder X automatique.
mov word ptr [liste_bombe+ebx+4+4*4+2],0
mov word ptr [liste_bombe+ebx+4+5*4],dx ;-7 ;0   ;adder X
mov word ptr [liste_bombe+ebx+4+5*4+2],0 ;adder Y

;5eme: VITESSE:1 db:X (+1/-1/0) ,1 db:Y (+1/-1/0);+ 2 db VIDE
;6eme: ADDER_X/Y: 1 dw:X,1 dW:Y


;edi  ;offset de l'infojoeur
inc dword ptr [liste_bombe]
ytreteterrterteterertter:
errteerterttyjtyutyuutytyuyutyutyututy:
popall
ret
endp
enregistre proc near
pushall

xor ebx,ebx
mov bl,terrain
dec bl
shl ebx,3
mov eax,dword ptr [nom_terrain+ebx]
mov dword ptr [reccord],eax
mov eax,dword ptr [nom_terrain+ebx+4]
mov word ptr [reccord+4],ax
xor eax,eax

mov ah,03ch
mov cx,0
xor ebx,ebx
lea edx,reccord
int 21h
inc byte ptr [reccord+7]
cmp byte ptr [reccord+7],'9'+1
jne ertrteertertyrtyrtrtyrtyyrtrtyrtyrtytr
mov byte ptr [reccord+7],'0'
inc byte ptr [reccord+6]
ertrteertertyrtyrtrtyrtyyrtrtyrtyrtytr:




;  AH     = 40h
;  BX   = file handle
;  ECX  = number of bytes to write
;  DS:EDX -> buffer to write from
mov bx,ax
push ebx
mov ah,040h
;mov bl,byte ptr fs:[1966080+64000+TAILLE_HEADER_REC]

mov ecx,64000
cmp save64,0
jne uioiupiuopuiopiopuuipoiupopuio
;mov dword ptr fs:[1966080+64000+TAILLE_HEADER_REC+TAILLE_BONUS_REC],ebp

mov ecx,TAILLE_HEADER_REC+TAILLE_BONUS_REC+4
add ecx,fs:[1966080+64000+TAILLE_HEADER_REC+TAILLE_BONUS_REC]

uioiupiuopuiopiopuuipoiupopuio:

push fs
pop  ds


mov edx,1966080+64000
int 21h

pop ebx
mov ah,03eh
int 21h

popall
ret
endp

calc_ombres proc near
pushall
;
;call noping
;call noping
;call noping
;donnee       dw 8 dup (?) ;x du dynablaster
;             dw 8 dup (?) ;y du dynablaster
xor ebx,ebx
xor ebp,ebp
mov kel_ombre,0
mertrymrtejklertyjklmtyer:

cmp [lapipipino+ebp],0
je pas_un_lapin_345
;cmp [lapipipino5+ebp],0
;je pas_un_lapin_345 ;ki saute pas
mov eax,1
cmp [lapipipino5+ebp],6
jb aaaaaa
mov eax,2
aaaaaa:
cmp [lapipipino5+ebp],12
jb aaaaaa2
mov eax,3
aaaaaa2:

;mort de lapin
cmp [lapipipino2+ebp],3 ;mort du lapin
jne veuoooooooooooi
mov eax,4
cmp [lapipipino3+ebp],27
ja reeeeeeeeeet
inc eax
cmp [lapipipino3+ebp],24
ja reeeeeeeeeet
inc eax
cmp [lapipipino3+ebp],21
ja reeeeeeeeeet
inc eax
cmp [lapipipino3+ebp],18
ja reeeeeeeeeet
inc eax
cmp [lapipipino3+ebp],16
ja reeeeeeeeeet
inc eax
cmp [lapipipino3+ebp],14
ja reeeeeeeeeet
inc eax
cmp [lapipipino3+ebp],11
ja reeeeeeeeeet
inc eax
cmp [lapipipino3+ebp],08
ja reeeeeeeeeet
inc eax
cmp [lapipipino3+ebp],05
ja reeeeeeeeeet
inc eax
reeeeeeeeeet:

mov ecx,ebp
shl eax,cl
or [kel_ombre],eax
xor eax,eax
mov ax,[donnee+8*2+ebx]
add ax,15
multiple_eax_par_320
add ax,[donnee+ebx]
add ax,4
sub ax,8
sub ax,320*19
mov [ombres+ebx],ax


jmp pas_un_lapin_345
veuoooooooooooi:
;-----

mov ecx,ebp
shl eax,cl
or [kel_ombre],eax
xor eax,eax
mov ax,[donnee+8*2+ebx]
add ax,15
multiple_eax_par_320
add ax,[donnee+ebx]
add ax,4
mov [ombres+ebx],ax

pas_un_lapin_345:
add ebp,4
add ebx,2
cmp ebx,2*8
jne mertrymrtejklertyjklmtyer


popall
ret
endp

aff_ombres proc near
pushall

;--- pour ombres ---
;kel_ombre   dd 0
;ombres      dw 8 dup (?)
;-------------------
mov esi,1582080+64000*5 ;offset buffer3
;add esi,ebx
;push ds
xor ebp,ebp
mov edi,offset buffer

push fs
pop ds

xor ebp,ebp
xor ebx,ebx
rtmklmrtyjklrtymjkrtyjklmrtyrty:

mov eax,1111B
mov ecx,ebp
shl eax,cl
mov edx,es:[kel_ombre]
and edx,eax
shr edx,cl

or  edx,edx
jz nananan_pas_dombre_ici

push esi edi ebx
cmp edx,2
jne oooooorytrtyrtyp
add esi,24
oooooorytrtyrtyp:
cmp edx,3
jne oooooorytrtyrtyp4
add esi,24*2
oooooorytrtyrtyp4:

;mort phase 1 (carcasse de lapin mort. hey oui c une ombre)
cmp edx,4
jb caaaaaaaaaaaaaaaaa
mov esi,1966080+64000*8+1+1*320
;---- couleur rose ou bleu
test ebp,0100B
jnz c_une_fille
add esi,320*(33+33)
c_une_fille:
;-----

sub edx,4
shl edx,5                 ;*32
add esi,edx
xor eax,eax
mov ax,es:[ombres+ebx]
add edi,eax
aff_mortlapin
pop ebx edi esi
jmp nananan_pas_dombre_ici
caaaaaaaaaaaaaaaaa:

xor eax,eax
mov ax,es:[ombres+ebx]
add edi,eax
add esi,71+150*320
aff_omb
pop ebx edi esi

nananan_pas_dombre_ici:

add ebx,2
add ebp,4
cmp ebx,8*2
jne rtmklmrtyjklrtymjkrtyjklmrtyrty

popall
ret
endp

deplacement_bombes proc near

poussage 1 0 1
poussage -1 0 1
poussage 1 2 32
poussage -1 2 32
poussage 1 0 1
poussage -1 0 1
poussage 1 2 32
poussage -1 2 32

ret
endp
