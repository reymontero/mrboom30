;
;
; format RMD
;Header:
; offset 951:  on met le nombre de voix (a la place de la Vitesse CIA)
;              '4' ou '8' ;pour RMD V1.0
;
; offset 1080-1083: taille du .RMD
;
;
;
;




.386

frequence EQU 10000

TAILLE_DU_FICHIER_EXE EQU 200 ;kb

PILE      SEGMENT STACK USE16
  DW      512 DUP (0)
PILE      ENDS

SB_SEG SEGMENT USE16

TXTOUPAS DB 1 ;0=avec 1=sans


numero_du_pattern dw -1

SUPER_SIGNE2 DB 0
SUPER_SIGNE3 DB 0 ;pour aller moins vite..

CommandLine db 128 dup (' ')
	    db '$'
mod_file db  '        .MOD',0,'$' ;'CHIPJAZZ.mod',0,'c:\music\divers\magnetic.MOD',0
MOD_FILE2 db '        .RMD',0,'$'

NOt_FOUND db 'not found...',10,13,'$'
nombre_de_voix db ?                 ;nombre de voix dans le mod...
				    ;remplis par load_file
old_int8     dd ? ;pour sauvegarde timer...
old_timer_compteur dw 0 ;compteur pour savoir kan blancer l'ancienne interruption

dsp_adr   dw 220h   ;port du dsp.

please_wait db 'Please wait while converting: $'
suckme db 'PROBLEME DANS GESTION FICHIER',10,13,'$'
syntax db 'MOD2RMD V0.5 .MOD to .RMD files convertor.',10,13
       db 'important: re-save the .MOD in Fast Tracker before converting.',10,13
       db '(to prevent bugs in replay routine...)',10,13
       db '',10,13
       db 'syntax: MOD2RMD MODNAME.MOD',10,13,'$'

syntax2 db 'MOD2RMD V0.5 .MOD to .RMD files convertor.',10,13
        db 'IMPORTANT: re-save the .MOD in Fast Tracker before converting.',10,13
        db '(to prevent bugs in replay routine...)',10,13
        db 'There may be some problems running this program under Windows:Run it under DOS.',10,13
        db '$'

sbmess1 db 'Pas de sb trouve la...',10,13,'$'
sbmess2 db 'SB trouv‚e !!!! a cette adresse:$'
sbmess3 db 'XXXXh !!','210h !!$','220h !!$','230h !!$','240h !!$','250h !!$','260h !!$','270h !!$','280h !!$'
sbmess4 db 'Version de la soundblaster:$'
sbmess5 db '-Taille du mod:$'
sbmess6 db '-taille du segment pattern:$'

erreur_file_mess db 'Erreur dans la gestion de fichier:procedure load_file',10,13,'$'
erreur_memory_mess db 'Pas assez de memoire pour charger un sample',10,13,'$'
erreur_memory_mess_pattern db 'Pas assez de memoire pour charger le segment pattern.',10,13,'$'
probleme_conversion_effet db 'PCE','$'

pas_de_note db 'NC$'
pas_bon_mod db 10,13,'ABORDED: not a 4 or 8 voices module.',10,13,'$'
NOMBre_DE_VOIX_mess db 10,13, '-nombre de voix dans le .MOD:$'
pas_bon_finetune db 'ton finetune est different de 0',10,13,'$'

sbvermaj db ?   ;pour la version de la SB...
sbvermin db ?

handle_mod_file dw  ?   ;handler du fichier mod!
handle_mod_file2 dw  ?   ;handler du fichier mod2!
mod_file_size   dd  ?   ;taille du fichier mod!

header_mod DB 1084 DUP (?) ;on charge ici le header du mod!!

;important: l'intrument 0 est l'intrument nul.
;il n'existe pas vraiment. toutes ses valeurs sont a 0

longueur_sample      DW 32 DUP (0)   ;longueur des 32 instruments.
volume_sample        DW 32 DUP (0)   ;volume par defalut des 32 instruments
depart_loop_sample   DW 32 DUP (0)   ;depart loop des 32 instruments
longueur_loop_sample DW 32 DUP (0)   ;longueur loop des 32 instruments
SEGMENT_SAMPLE       DW 32 DUP (0)   ;addresse du segment de chaque sample.

;*1.059463094 ou 0.943874312 ou monter/descendre d'un ton.
;Middle C freq: C4=8363
;               C5=16726
; La table des frequences ! Pour chaque note et en HZ.
;*1.059463094 ou 0.943874312 ou monter/descendre d'un ton.
;Middle C freq: C4=8363
;               C5=16726
; La table des frequences ! Pour chaque note et en HZ.

       ;   -  B7 - A#7  - A7    - G#7  - G7  - F#7 - F7  - E7  - D#7 - D7  - C#7 - C7  -
sbfreq dd  126297,119209,112518,106203,100242,94616,89306,84293,79562,75097,70882,66903
      ;   -  B6 - A#6 - A6  - G#6 - G6  - F#6 - F6  - E6  - D#6 - D6  - C#6 - C6  -
      dd   63148,59604,56259,53101,50121,47308,44653,42146,39781,37548,35441,33451
      ;   -  B5 - A#5 - A5  - G#5 - G5  - F#5 - F5  - E5  - D#5 - D5  - C#5 - C5  -
      dd   31574,29802,28129,26550,25060,23654,22326,21073,19890,18774,17720,16726
      ;   -  B4 - A#4 - A4  - G#4 - G4  - F#4 - F4  - E4  - D#4 - D4  - C#4 - C4  -
      dd   15787,14901,14064,13275,12530,11827,11163,10536,09945,09387,08860,08363
      ;   -  B3 - A#3 - A3  - G#3 - G3  - F#3 - F3  - E3  - D#3 - D3  - C#3 - C3  -
      dd   07893,07450,07032,06637,06265,05913,05581,05268,04972,04693,04430,04181
      ;   -  B2 - A#2 - A2  - G#2 - G2  - F#2 - F2  - E2  - D#2 - D2  - C#2 - C2  -
      dd   03946,03725,03516,03318,03132,02956,02790,02634,02486,02346,02215,02090
      ;   -  B1 - A#1 - A1  - G#1 - G1  - F#1 - F1  - E1  - D#1 - D1  - C#1 - C1  -
      dd   01973,01862,01758,01659,01566,01478,01395,01317,01243,01173,01107,01045
      ;   -  B0 - A#0 - A0  - G#0 - G0  - F#0 - F0  - E0  - D#0 - D0  - C#0 - C0  -
      dd   00986,00931,00879,00829,00783,00739,00697,00658,00621,00586,00553,00522

	;   -  B7 - A#7 - A7  - G#7 - G7  - F#7 - F7  - E7  - D#7 - D7  - C#7 - C7  -
ptable0 dd   00448,00480,00496,00528,00560,00592,00640,00672,00720,00752,00800,0848
      ;   -  B6 - A#6 - A6  - G#6 - G6  - F#6 - F6  - E6  - D#6 - D6  - C#6 - C6  -
      dd   00896,00960,01008,01072,01136,01200,01280,01360,01440,01520,01616,1712
      ;   -  B5 - A#5 - A5  - G#5 - G5  - F#5 - F5  - E5  - D#5 - D5  - C#5 - C5  -
      dd   01808,01920,02032,02160,02288,02416,02560,02720,02880,03040,03232,3424
      ;   -  B4 - A#4 - A4  - G#4 - G4  - F#4 - F4  - E4  - D#4 - D4  - C#4 - C4  -
      dd   03616,03840,04064,00209,00465,00737,01025,01329,01665,02001,02369,02753
      ;   -  B3 - A#3 - A3  - G#3 - G3  - F#3 - F3  - E3  - D#3 - D3  - C#3 - C3  -
      dd   03153,03585,04033,00418,00930,01474,02050,02658,03330,04002,00643,01411
      ;   -  B2 - A#2 - A2  - G#2 - G2  - F#2 - F2  - E2  - D#2 - D2  - C#2 - C2  -
      dd   02211,03075,03971,00836,01860,02948,00005,01221,02565,03909,01286,02822
      ;   -  B1 - A#1 - A1  - G#1 - G1  - F#1 - F1  - E1  - D#1 - D1  - C#1 - C1  -
      dd   00327,02055,03847,01672,03720,01801,00010,02442,01035,03723,02572,01549
      ;   -  B0 - A#0 - A0  - G#0 - G0  - F#0 - F0  - E0  - D#0 - D0  - C#0 - C0  -
      dd   00654,00015,03599,03328,03329,03586,00004,00773,02054,03335,01033,03082

;...............variables pour les 4 voix...

OFFSET_SAMPLE dw 4 dup (0)          ;ou on est dans le sample de chaque voix.
OFFSET_COMPTEUR_SAMPLE dd 4 dup (0) ;COMPTEUR POUR LE CALCUL DE LA PROGRESSION
				    ;que l'on doit donner a l'offset du
				    ;sample de chaque voix en fonction de la
				    ;frequence a laquelle il est joue.

mixage                   dw 4 dup (0) ;octets calcules pour les 4 voix.

sample_joue_en_ce_moment dw 4 dup (0) ;numero du sample joue sur les 4 voix
				      ;de 1 a 31 (et non 0 a 31)
				      ;cas particulier si=0 pas de sample joue...
				      ;donc on met 0 a la fin d'un sample non
				      ;loupeur...

longueur_sample_joue      DW 4 dup (0)   ;
depart_loop_sample_joue   DW 4 DUP (?)   ;
longueur_loop_sample_joue DW 4 DUP (?)   ;
note_joue_par_sample      DD 4 DUP (?)   ;place la vitesse en HZ direct!

volume_de_la_voix         DW 4 DUP (63)  ;volume pour chaque voix...


SAUVE_VISEUR_DANS_SBFREQ  DW 4 dup (0)   ;sauvegarde du viseur lorsque l'on
					 ;pioche la frequence
					 ;utile pour les effets pour cacule
					 ;la frequence d'une note au dessus.

;pour balancer un sample il faut:
;dans sa voix.
;mettre son numero dans [sample_joue_en_ce_moment]
;mettre sa longueur dans [longueur_sample_joue]
;mettre ses infos de loop dans [depart_loop_sample_joue]
;et [longueur_loop_sample_joue]
;mettre 0 dans
;              [OFFSET_SAMPLE]
;              [OFFSET_COMPTEUR_SAMPLE]
;placer coef note dans
;              [note_joue_par_sample]
; aussi regler le volume par rapport a la valeur par default du volume du sample
;
;..........................................
;............ variables pour la vitesse d'execution du sample.
;
; Speed/50 = nombre de secondes par ligne...
;
; vitesses possibles 1,2,3,...,31
;
;Speed 1: Speed/50=0.02 soit 0.02 secondes par ligne!
;le player est a 10000 fois par seconde...
;il faut donc changer de lignes toutes les 10000*0.02=200 fois ke le player
;est appel‚.
;
; stop:le bmp peut changer...
; on a donc:
; BMP * 2/5= 50 HZ.
;
;donc chaque valeur du speed wait doi etre calcule par:
; (SPeed*10000)/(BMP * 2/5)
; donc comme ya 32 valeur de speed possible on va faire un tablo
; de base.ou il ne restera plus k'a diviser par le bmp et a placer dans speed
; wait si on change la valeur de la vitesse bmp...
;
;Speed=nombre de ticks par ligne.
;
BMP_SPEED    db  125
speed_song   dw  6

;                    0        1     2      3      4      5      6      7
SPeed_wait2  dd 0FFFFFFFFh,025000,050000,075000,100000,125000,150000,175000
;                      8      9     10     11     12     13     14     15
		 dd 200000,225000,250000,275000,300000,325000,350000,375000
;                      16     17    18     19     20     21     22     23
		 dd 400000,425000,450000,475000,500000,525000,550000,575000
;                      24     25    26     27     28     29     30     31
		 dd 600000,625000,650000,675000,700000,725000,750000,775000

; par default on prend la table: BMP=125
;
;                 0       1    2    3    4    5    6    7    8    9    10
Speed_wait dd 0FFFFFFFFh,0200,0400,0600,0800,1000,1200,1400,1600,1800,2000
;              11   12   13   14   15   16   17   18   19   20
	   dd 2200,2400,2600,2800,3000,3200,3400,3600,3800,4000
;              21   22   23   24   25   26   27   28   29   30
	   dd 4200,4400,4600,4800,5000,5200,5400,5600,5800,6000
;              31
	   dd 6200


speed_compteur_save dd 1200 ;vitesse 6 par default.
		       ;on place ici le nombre dans speed_wait k'on a choisit
		       ;ca reviendra a ca apres etre arrive a 0...
speed_compteur dd 1200 ;
		       ;
;pour l'effet D,le parametre est dans le fichier comme du decimal pris pour
;de l'hexa!!! bizarre..enfin avec ce tableau on peut convertir
conv_list  db 00,01,02,03,04,05,06,07,08,09,10h,11h,12h,13h,14h,15h,16h,17h,18h,19h,20h
  db 21h,22h,23h,24h,25h,26h,27h,28h,29h,30h,31h,32h,33h,34h,35h,36h,37h,38h
  db 39h,40h,41h,42h,43h,44h,45h,46h,47h,48h,49h,50h,51h,52h,53h,54h,55h,56h
  db 57h,58h,59h,60h,61h,62h,63h

;................position dans le mod/tout sur les patterns...
numero_de_ligne_dans_pattern    dd 0 ;dans le pattern courant.
viseur_dans_arrangement_chanson dw 0 ;


nombre_total_de_pattern_chanson dw ? ;nombre total dans l'arrangemement de
				     ;la chanson.
nombre_total_de_pattern_mod     db ? ;nombre total de pattern dans le mod.
arrangement_de_la_chanson db 128 dup (?)    ;ordre des patterns a executer.

taille_segment_pattern dd ?          ;en octets.
SEGMENT_pattern        dw ?          ;addresse du segment des patterns...
viseur_dans_pattern    dd 0          ;vise sur la note jouee...
				     ;valeur k'on additionne pour
				     ;piocher dans le segment pattern


;..................variables pour les effets...................


effet_D dw 0,0,0  ;premier mot: 0=pas active,1=active
		 ;deuxieme mot: numero le la ligne ou on se place dans la
		 ;pattern suivante...
		 ;troisieme mot: prochain viseur_dans_arrangement k'on mettra...

effet_B dw 0,0  ;premier mot  : 0=pas active,1=active
		;deuxieme mot  : numero du pattern
		;dans l'arrangement ou on se place

effet_E6 dw 0   ;premier mot  : 0=pas active,1=active

;table_de_saut dw offset nopper,offset nopper,offset nopper,offset nopper

SPEED_COMPTEUR_TEST_EFFET12 dd 4 dup (0)


;............. effect entre lignes. (pour les 4 voix)

;utilises de maniere differente suivant les effets...

compteur_effect_entre_ligne dw 4 dup (?)
adder_effect_entre_ligne    dw 4 dup (?)
compteur_effect_entre_ligne_save dw  (200) ;200 par default
					   ;change si on change la vitesse
					   ;definis la rapidite...
					   ;cacule par proc def_vitesse_tick                                                                                               ;calcule par proc
;arpegio:
FREQUENCE_POUR_LES_3_NOTES1 DD 4 DUP (?)
FREQUENCE_POUR_LES_3_NOTES2 DD 4 DUP (?)
FREQUENCE_POUR_LES_3_NOTES3 DD 4 DUP (?)
compteur_pour_arpegio  dd 4 DUP (0)
compteur_pour_arpegio2 dd 4 DUP (0)
compteur_pour_arpegio3 dw 4 DUP (0)
;loop
FXLOOP1                dw (-1) ;nombre de fois k'on doit faire la loop
			       ;1 indique k'on peut faire une nouvelle loop
FXLOOP2                dd (0) ;sauvegarde de la ligne ou on doit
			      ;retourner
;note cut
NOTE_DELAY  dd 4 DUP (0)
NOTE_DELAY2 dw 4 DUP (0) ;pour sauver sample_joue_en_ce_moment dw 4 dup (0)
			 ;et on met 0 le temps k'on attend.

;note retrig
NOTE_RETRIG  dd 4 DUP (0)

;vibrato
WHAT_VIBRATO            DW offSET  VIBRATO_SIN ;vise sur kel tablo on choisit

VIBRATO_SIN             Dw   0, 24, 49, 74, 97,120,141,161
			Dw 180,197,212,224,235,244,250,253
			Dw 255,253,250,244,235,224,212,197
			Dw 180,161,141,120, 97, 74, 49, 24
			Dw   0,-24,-49, -74, -97,-120,-141,-161
			Dw -180,-197,-212,-224,-235,-244,-250,-253
			Dw -255,-253,-250,-244,-235,-224,-212,-197
			Dw -180,-161,-141,-120, -97, -74, -49, -24

VIBRATO_1               Dw  0, 16,32,48,64,80,96,112,128
			Dw  144,160,176,192,208,224,240
			Dw 256,240,224,208,192,176,160,144
			Dw 128,112,096,080,064,048,032,16
			Dw  0,-16,-32,-48,-64,-80,-96,-112
			dw -128,-144,-160,-176,-192,-208,-224,-240
			dw -256,-240,-224,-208,-192,-176,-160,-144
			Dw -128,-112,-096,-080,-064,-048,-032,-16

VIBRATO_2               dw  256,256,256,256,256,256,256,256
			dw  256,256,256,256,256,256,256,256
			dw  256,256,256,256,256,256,256,256
			dw  256,256,256,256,256,256,256,256
			dw -256,-256,-256,-256,-256,-256,-256
			dw -256,-256,-256,-256,-256,-256,-256
			dw -256,-256,-256,-256,-256,-256,-256
			dw -256,-256,-256,-256,-256,-256,-256


;VIBRATO_1               Dw 256,240,224,208,192,176,160,144
;                        Dw 128,112,096,080,064,048,032,16
;                        Dw  0, -16,-32,-48,-64,-80,-96,-112,-128
;                        Dw -144,-160,-176,-192,-208,-224,-240,-256
;                        Dw 256,240,224,208,192,176,160,144
;                        Dw 128,112,096,080,064,048,032,16
;                        Dw  0, -16,-32,-48,-64,-80,-96,-112,-128
;                        Dw -144,-160,-176,-192,-208,-224,-240,-256


VIBRATO_viseur          dw 4 DUP (0) ;viseur dans tablos.

vibrato_fx_prof         dw 4 DUP (0) ;pour sauvegarde des info sur
vibrato_fx_speed        dw 4 DUP (0) ;le vibrato en cours!

VIBRATO_compteur_save   dw 4 DUP (0FFFFh)
VIBRATO_compteur        dw 4 DUP (0)
SAVE_NOTE_VIBRATO       DD 4 DUP (0) ;pour sauvegarder la note de base pour
;.......tremolo (utilise les tables de vibrato...)
WHAT_TREMOLO            DW offSET  VIBRATO_SIN ;vise sur kel tablo on choisit

TREMOLO_viseur          dw 4 DUP (0) ;viseur dans tablos.

TREMOLO_fx_prof         dw 4 DUP (0) ;pour sauvegarde des info sur
TREMOLO_fx_speed        dw 4 DUP (0) ;le vibrato en cours!

TREMOLO_compteur_save   dw 4 DUP (0FFFFh)
TREMOLO_compteur        dw 4 DUP (0)
SAVE_VOLUME_TREMOLO     Dw 4 DUP (0) ;pour sauvegarder la note de base pour

;STOP_TREMOLO            DW 4 DUP (0) ;0=NON
;.............................................................



;****************** GUS !!! *************************************************

  gus_base     dw 260h
  gus_status   dw gus_base+006h
  gus_voice    dw gus_base+102h
  gus_command  dw gus_base+103h
  gus_Datalo   dw gus_base+104h
  gus_Datahi   dw gus_base+105h
  gus_DramIO   dw gus_base+107h

TABLE_Volumes_GUS  DW 1500h
		   DW 40004,42600,44752,45648,46544,47624,48448,49232
		   DW 50048,50584,51112,51656,52184,52584,52976,53376
		   DW 53752,54016,54280,54520,54768,55024,55280,55544
		   DW 55776,56048,56288,56536,56784,56992,57184,57384
		   DW 57616,57752,57888,58000,58112,58248,58368,58480
		   DW 58600,58720,58840,58960,59088,59208,59336,59464
		   DW 59584,59720,59816,59944,60072,60176,60312,60408
		   DW 60544,60648,60784,60888,60992,61064,61176,61248


       ;   -  B7 - A#7  - A7    - G#7  - G7  - F#7 - F7  - E7  - D#7 - D7  - C#7 - C7  -
voix_gus EQU 43 ;=14minimum
gusfreq dd  126297/voix_gus,119209/voix_gus,112518/voix_gus,106203/voix_gus,100242/voix_gus,94616/voix_gus,89306/voix_gus,84293/voix_gus,79562/voix_gus,75097/voix_gus,70882/voix_gus,66903/voix_gus
      ;   -  B6 - A#6 - A6  - G#6 - G6  - F#6 - F6  - E6  - D#6 - D6  - C#6 - C6  -
      dd   63148/voix_gus,59604/voix_gus,56259/voix_gus,53101/voix_gus,50121/voix_gus,47308/voix_gus,44653/voix_gus,42146/voix_gus,39781/voix_gus,37548/voix_gus,35441/voix_gus,33451/voix_gus
      ;   -  B5 - A#5 - A5  - G#5 - G5  - F#5 - F5  - E5  - D#5 - D5  - C#5 - C5  -
      dd   31574/voix_gus,29802/voix_gus,28129/voix_gus,26550/voix_gus,25060/voix_gus,23654/voix_gus,22326/voix_gus,21073/voix_gus,19890/voix_gus,18774/voix_gus,17720/voix_gus,16726/voix_gus
      ;   -  B4 - A#4 - A4  - G#4 - G4  - F#4 - F4  - E4  - D#4 - D4  - C#4 - C4  -
      dd   15787/voix_gus,14901/voix_gus,14064/voix_gus,13275/voix_gus,12530/voix_gus,11827/voix_gus,11163/voix_gus,10536/voix_gus,09945/voix_gus,09387/voix_gus,08860/voix_gus,08363/voix_gus

      ;   -  B3 - A#3 - A3  - G#3 - G3  - F#3 - F3  - E3  - D#3 - D3  - C#3 - C3  -
      dd   07893/voix_gus,07450/voix_gus,07032/voix_gus,06637/voix_gus,06265/voix_gus,05913/voix_gus,05581/voix_gus,05268/voix_gus,04972/voix_gus,04693/voix_gus,04430/voix_gus,04181/voix_gus
      ;   -  B2 - A#2 - A2  - G#2 - G2  - F#2 - F2  - E2  - D#2 - D2  - C#2 - C2  -
      dd   03946/voix_gus,03725/voix_gus,03516/voix_gus,03318/voix_gus,03132/voix_gus,02956/voix_gus,02790/voix_gus,02634/voix_gus,02486/voix_gus,02346/voix_gus,02215/voix_gus,02090/voix_gus
      ;   -  B1 - A#1 - A1  - G#1 - G1  - F#1 - F1  - E1  - D#1 - D1  - C#1 - C1  -
      dd   01973/voix_gus,01862/voix_gus,01758/voix_gus,01659/voix_gus,01566/voix_gus,01478/voix_gus,01395/voix_gus,01317/voix_gus,01243/voix_gus,01173/voix_gus,01107/voix_gus,01045/voix_gus
      ;   -  B0 - A#0 - A0  - G#0 - G0  - F#0 - F0  - E0  - D#0 - D0  - C#0 - C0  -
      dd   00986/voix_gus,00931/voix_gus,00879/voix_gus,00829/voix_gus,00783/voix_gus,00739/voix_gus,00697/voix_gus,00658/voix_gus,00621/voix_gus,00586/voix_gus,00553/voix_gus,00522/voix_gus

SB_SEG ENDS

BIBERMAN SEGMENT USE16
BIBERMAN2 DB 0ffffh DUP (?)
BIBERMAN ENDS

;VIDEO_SEG SEGMENT USE16
;VIDEO DB 64000 DUP ('!')
;VIDEO_SEG ENDS

;-----------------------------------------
CODE      SEGMENT USE16
	  ASSUME CS:CODE,DS:CODE,SS:PILE

;----------------------------------------------------------------------------
ecris proc near ;entree:cx
mov ax,sb_seg
mov es,ax

mov ax,BIBERMAN
mov ds,ax
xor dx,dx

mov word ptr bx,es:[handle_mod_file2]

mov ax,04000h

int 21h

jnc zesddddsdsdsq
jmp erreur_file2
zesddddsdsdsq:
ret
ecris endp

ecris2 proc near ;entree:cx

mov ax,sb_seg
mov es,ax

;       taille_segment_pattern dd ?          ;en octets.
;       SEGMENT_pattern        dw ?          ;addresse du segment des patterns...
;       viseur_dans_pattern    dd 0          ;vise sur la note jouee...

mov ax,es:[SEGMENT_pattern]
mov ds,ax
xor dx,dx

mov ecx,es:[taille_segment_pattern]   ; dd ? en octets.
push eax
mov eax,ecx
call num
pop eax

mov word ptr bx,es:[handle_mod_file2]

xor dx,dx

delire3:

errererererereer:
push ecx
mov ecx,1024
mov ax,04000h
int 21h
pop ecx

call SUPER_SIGNE2b

sub ecx,1024

;mov eax,ecx
;call num

mov ax,ds
add ax,64
mov ds,ax
cmp ecx,0
jne errererererereer
;
;;jnc zesddddsdsdsq23
;jmp erreur_file2
;zesddddsdsdsq23:
ret
ecris2 endp

lis proc near ;entree:cx
mov ax,sb_seg
mov es,ax

mov ax,BIBERMAN
mov ds,ax
xor dx,dx

mov word ptr bx,es:[handle_mod_file]

mov ax,03F00h

int 21h

jnc rzesddddsdsdsq
jmp erreur_file2
rzesddddsdsdsq:
ret
lis endp

load_file proc near

;...ouverture fichier....
mov ax,sb_seg
mov ds,ax

mov dx,offset please_wait
mov ah,09h
int 21h

mov dx,offset mod_file ;affiche le nom du fichier.
mov ah,09h
int 21h


;mov dx,offset mod_file
;mov ah,03dh ;ouverture du fichier avec handle.
;mov al,00h  ;ouverture du fichier pour lecture.
;int 21h
;jc erreur_file;saute si carry=1
;dans ax:handle fichier
;push ax
;mov ax,sb_seg
;mov es,ax
;mov ds,ax
;pop ax
;mov word ptr ax,es:[handle_mod_file],ax

;... calcul de la taille du fichier mod ...
mov ax,sb_seg
mov es,ax
mov ds,ax
mov word ptr bx,es:[handle_mod_file]
mov ah,042h
mov al,02h
xor cx,cx
xor dx,dx
int 21h
jc erreur_file;saute si carry=1
;sortir:dx:ax taille du fichier
mov word ptr es:[mod_file_size],ax
mov word ptr es:[mod_file_size+2],dx
;on va mettre ca a la place de la caracterisation !!!

;mov eax,es:[mod_file_size]..affiche taille du mod...

cmp es:[TXTOUPAS],0
jne rreertrtyurtyuyututuyuty
mov ah,09h
mov dx,offset sbmess5
int 21h
mov eax,es:[mod_file_size]
call num
rreertrtyurtyuyututuyuty:
;.......


mov word ptr bx,es:[handle_mod_file] ;replace le pointeur de fichie au debut..
mov ah,042h
mov al,0
xor cx,cx
xor dx,dx
int 21h
jc erreur_file;saute si carry=1

;...lecture du fichier...
mov ax,sb_seg
mov es,ax
mov ds,ax
mov word ptr bx,es:[handle_mod_file]
mov ah,03fh
mov cx,1084 ;pour charger header mod...
mov dx,offset header_mod
int 21h
jc erreur_file;saute si carry=1

;...remplis les variables du player...
mov ax,sb_seg
mov es,ax
mov ds,ax
mov  si,offset header_mod
ADD SI,42
mov di,offset longueur_sample     ;longueur des 31 instruments.
add di,2  ;on saute le premier sample: sample vide...
mov cx,31 ;31 samples maximum.
encore_un_sample:
lodsw
rol ax,8 ;transforme format pc!
shl ax,1 ;on multiplie par 2 (c'etait la taille en nombre de mots!)
stosw

cmp es:[TXTOUPAS],0
jne rreertrtyurtyuyututuyuty2
call num
rreertrtyurtyuyututuyuty2:

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
shl ax,1 ;on multiplie par 2 (c'etait la taille en nombre de mots!)
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
shl ax,1 ;on multiplie par 2 (c'etait la taille en nombre de mots!)
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
add si,1080
cmp byte ptr es:[si],'M'
jne frtretertertert
cmp byte ptr es:[si+1],'.'
jne frtretertertert
cmp byte ptr es:[si+2],'K'
jne frtretertertert
cmp byte ptr es:[si+3],'.'
jne frtretertertert
mov es:[nombre_de_voix],4

mov eax,es:[mod_file_size]

mov es:[si],eax ;on met la taille du mod a la place de l'identification.
push si
mov  si,offset header_mod
mov  byte ptr es:[si+951],'4';on met le nombre de voix a la place de la Vitesse CIA
pop si

jmp rttrtrtrtrrttrrtyrttyrrt
frtretertertert:
cmp byte ptr es:[si],'F'
jne frtretertertert2
cmp byte ptr es:[si+1],'L'
jne frtretertertert2
cmp byte ptr es:[si+2],'T'
jne frtretertertert2
cmp byte ptr es:[si+3],'4'
jne frtretertertert2

mov es:[nombre_de_voix],4

mov eax,es:[mod_file_size]
mov es:[si],eax ;on met la taille du mod a la place de l'identification.
push si
mov  si,offset header_mod
mov  byte ptr es:[si+951],'4';on met le nombre de voix a la place de la Vitesse CIA
pop si


jmp rttrtrtrtrrttrrtyrttyrrt
frtretertertert2:
;cmp byte ptr es:[si],'6'
;jne frtretertertert3
;cmp byte ptr es:[si+1],'C'
;jne frtretertertert3
;cmp byte ptr es:[si+2],'H'
;jne frtretertertert3
;cmp byte ptr es:[si+3],'N'
;jne frtretertertert3
;
;mov byte ptr es:[si],'R'
;mov byte ptr es:[si+1],'M'
;mov byte ptr es:[si+2],'D'
;mov byte ptr es:[si+3],'6'
;
;mov es:[nombre_de_voix],6
;jmp rttrtrtrtrrttrrtyrttyrrt
frtretertertert3:
cmp byte ptr es:[si],'8'
jne frtretertertert4
cmp byte ptr es:[si+1],'C'
jne frtretertertert4
cmp byte ptr es:[si+2],'H'
jne frtretertertert4
cmp byte ptr es:[si+3],'N'
jne frtretertertert4

mov eax,es:[mod_file_size]
mov es:[si],eax ;on met la taille du mod a la place de l'identification.
push si
mov  si,offset header_mod
mov  byte ptr es:[si+951],'8';on met le nombre de voix a la place de la Vitesse CIA
pop si


mov es:[nombre_de_voix],8
jmp rttrtrtrtrrttrrtyrttyrrt
frtretertertert4:

mov dx,offset pas_bon_mod
mov  ah,09h
int 21h

MOV     AX,04C00H
INT     21H


rttrtrtrtrrttrrtyrttyrrt:

cmp es:[TXTOUPAS],0
jne rreertrtyurtyuyututuyuty23

mov dx,offset NOMBre_DE_VOIX_mess
mov  ah,09h
int 21h

xor ax,ax
mov al,es:[nombre_de_voix]
call affsigne
rreertrtyurtyuyututuyuty23:
;  44 *****  Lower four bits are the finetune value, stored as a signed

;... teste si finetune=0
;mov  si,offset header_mod
;add si,44
;cmp byte ptr es:[si],0
;je frtretertertertr
;mov dx,offset pas_bon_finetune
;mov  ah,09h
;int 21h
;frtretertertertr:

;****************************** les patterns... ******************************
;calcul du nombre de patterns du mod (pas de la chanson)

mov ax,sb_seg
mov es,ax
mov ds,ax
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

;....aff taille segment pattern

cmp es:[TXTOUPAS],0
jne rreertrtyurtyuyututuyuty23e

push eax dx
mov dx,offset sbmess6
mov ah,09h
int 21h
pop dx eax
call num
rreertrtyurtyuyututuyuty23e:
;........

;call affsigne ;!
;
cmp es:[nombre_de_voix],4
je tcanariwarior
shr eax,11

jmp tcanariwarior2
tcanariwarior:
shr eax,10

tcanariwarior2:

mov es:[nombre_total_de_pattern_mod],al ;car le nombre max c'est 164!


;...reserve la memoire pour le segment pattern.
mov  eax,es:[taille_segment_pattern]

shr  eax,4 ;divise par 16.
mov  ebx,eax
inc ebx

mov  ah,48h
int  21h

jnc dfgfgfghfghhjfghjg2 ;saute si carry n'est pas a 1...

;----pas assez de memoire pour charger le segment pattern---
mov dx,offset erreur_memory_mess_pattern
mov  ah,09h
int 21h

;mov ax,bx ;taille de memoire dispo
;call affsigne
;
mov ah,08h ;attend la frappe d'un caractere
int 21h    ;
dfgfgfghfghhjfghjg2:
;-----------------------------------------------------------
mov es:[SEGMENT_PATTERN],ax
mov ds,ax
mov ecx,es:[taille_segment_pattern] ;nombre d'octets a charger...
mov word ptr bx,es:[handle_mod_file]

;****** chargement du fichier en plusieur fois si plus long !!! ****

party5:
cmp ecx,1024
jna rrrrrrre
push ecx bx
mov cx,01024
mov ah,03fh
xor dx,dx
int 21h
pop bx ecx
sub ecx,01024
mov ax,ds
add ax,64 ;4096 ;un segment en plus
mov ds,ax
xor dx,dx
jmp party5
rrrrrrre:
mov word ptr bx,es:[handle_mod_file]
xor dx,dx
mov ah,03fh
int 21h

;*******************************************************************

call convert_pattern ;transforme les patterns....
		     ;(les rend moins stupides...)
;call modif_header2

ret
load_file endp
;modif_header2 proc near
;mov ax,sb_seg
;mov es,ax
;mov si,offset header_mod
;add si,20
;;-1er mot:
;mov eax,es:[mod_file_size]
;call num
;
;ret
;modif_header2 endp

convert_pattern proc near

mov dl,10
mov ah,2
int 21h
mov dl,13
mov ah,2
int 21h

;  44      1    Lower four bits are the finetune value, stored as a signed

mov ax,sb_seg
mov es,ax

;mov ecx,es:[taille_segment_pattern] ;nombre d'octets a charger...

mov ax,es:[SEGMENT_PATTERN]
mov ds,ax

;******** reviens ici apres chaque pattern...
inc word ptr es:[numero_du_pattern] ;pour savoir

xor cx,cx

xor si,si ;source...

mov cl,es:[nombre_total_de_pattern_mod]

;--------------------------- didouille pour ke ca en fasse deux fois plus si
;c'est un mode 8 voix
cmp es:[nombre_de_voix],8
jne retrerteyt
shl cx,1
retrerteyt:
;--------------------------------

encore_une_pattern:


push ds cx es si

xor eax,eax
xor ebx,ebx

;............
;format original OCTET1: bits 7-4 ;Bits high du numero d'instrument.
;                             3-0 ;Bits inferieurs indication hauteur du son.
;                OCTET2: bits 7-0 ;Bits superieurs indication hauteur du son.
;                OCTET3:      7-4 ;Bits low du numero d'instrument.
;                        bits 3-0 ;Commande d'effet.
;                OCTET4:      7-0 ;Operante d'effet. BIAZZAROID.
;
;format remdy    OCTET1: numero de l'instrument (de 1 a 32) 0=pas de changement
;                OCTET2: ce k'on doit rajouter l'offset de sbfreq pour obtenir
;                        la bonne frequence (apres l'avoir *4)
;
;                OCTET3:      3-0 ;commande d'effet
;                             7-4 ; '0000'
;                OCTET4:      7-0 ;Operante d'effet.
;le parametre est dans le fichier est pour certain effets
;comme du decimal pris pour
;de l'hexa!!! bizarre..enfin c'est convertis au format remdy.
;

mov cx,64 ;pour chaque ligne... d'un pattern...
captif:
push cx

mov cx,4   ;pour chaque voix d'un pattern...
radio:
push si cx


;******** numero instrument
mov ah,ds:[SI]
shr ah,4
mov al,ds:[SI+2]
shr ax,4
;!!!! call affsigne
;dans ax:on a le numero de l'instrument...on ne le stock pas tout de suite
;pour pas ecraser...
;******** frequence/note
push ax ; (1)
xor ebx,ebx

mov bx,ds:[SI]
and bx,01111111100001111B
shl bl,4
shr bx,4

push eax
mov eax,ebx
;call num
pop eax

push cx di es ax ds

mov al,-1 ;temporaire..si ya pas de note ca restera
cmp ebx,0   ;pas de note
je  reerrrrrrrrrr

xor ax,ax

mov cx,12*8 ;nombre octaves-1
mov di,offset ptable0

compte_tour:
cmp es:[di],ebx
je reerrrrrrrrrr
add di,4
inc ax ; add ax,1 ;calcul de l'offset...on multiplira par 4 ensuite...
dec cx
jnz compte_tour
push es ds ax dx

mov ax,sb_seg
mov ds,ax
mov es,ax


mov ax,es:[numero_du_pattern]
call affsigne

mov ax,si  ;!!!!

call affsigne ;affsigne le viseur dans le pattern
mov ax,sb_seg
mov ds,ax
mov es,ax
mov dx,offset pas_de_note
mov ah,09h
int 21h
pop  dx ax ds es
reerrrrrrrrrr:
;on n'a trouve la note.. ou on en a trouvee une...

mov ds:[si+1],al ;sera a -1 si ya pas de note...
		  ;pour format remdy
pop ds ax es di cx
fuckdfe:

pop ax ;(1)
mov ds:[si],al ;dans al:on a le numero de l'intrument.
	       ;on ne l'a stocke ke maintenant pour rien ecraser...
;** effet *************************

mov al,ds:[SI+2] ;numero de l'effet...
and al,00001111B  ;efface les bits d'intruments k'il y avait dedans.
mov ds:[SI+2],al ;numero de l'effet...
;call num




cmp al,0Dh
je convertion
jmp pas_de_convertion
convertion:

mov ah,ds:[SI+3] ;commande de l'effet...
push bx di        ;convertis du format bizarre ou elle est vers le format
		  ;remdy!
;pour l'effet D,le parametre est dans le fichier comme du decimal pris pour
;de l'hexa!!! bizarre..enfin avec ce tableau on peut convertir


;mov dx,offset conv_list
;mov ah,09h
;int 21h

mov di,offset conv_list
xor bx,bx
pas_ok195:
cmp ah,es:[di]
je okok195
inc di
inc bx
cmp bx,64
je okok1953

jmp pas_ok195
okok1953:
push ds ax
mov ax,sb_seg
mov ds,ax
mov dx,offset probleme_conversion_effet
mov ah,9
int 21h
pop ax ds
okok195:
mov byte ptr ds:[SI+3],bl
pas_ok195e:
pop  di bx
pas_de_convertion:
;-----------convertision speciale pour les effet 3

mov al,ds:[SI+2] ;numero de l'effet...

;and al,00001111B  ;efface les bits d'intruments k'il y avait dedans.
;mov ds:[SI+2],al ;numero de l'effet...

cmp al,03
je convertionF
jmp convertionF2
convertionF:
mov al,20            ;20+note pour effet 3
mov cl,-1
nirvane2:

add al,ds:[SI+1]
cmp byte ptr ds:[si+1],-1
jne pire
mov al,cl ;-1 pas de nouvelle note...!!!
pire:

mov ds:[SI+2],al ;numero de l'effet... 20 + la note... effet 3
                 ;numero de l'effet... -1 effet 3 sans nouvelle note...
mov byte ptr ds:[si+1],-1 ;puis on remet la note a -1 (ya pas de note...)

convertionF2:

;pour prendre:
;mov al,ds:[SI+2] ;on a l'effet la.
;call num
;mov al,ds:[SI+3] ;on a l'operante ici
;call num
;**********************************
pop  cx si
add si,4
dec cx
jnz radio


pop cx

;!!!!mov dl,10
;!!!!mov ah,2
;!!!!int 21h
;!!!!mov dl,13
;!!!!mov ah,2
;!!!!int 21h
dec cx
jnz captif

pop  si es cx ds
mov ax,ds
add ax,64 ;faut additionner: offset/16 -->pattern suivant.
mov ds,ax
dec cx
jnz encore_une_pattern

ret
convert_pattern endp

affsigne proc near
push ax
pushf
add ax,0
jns nonsigne
push ax
mov al,'-'
call affascii
pop ax
neg ax
jmp sdfsdfsdf
nonsigne:
push ax
mov al,'+'
call affascii
pop ax
sdfsdfsdf:
call affdecimal
push ax
mov al,' '
call affascii
pop ax
push ax
mov al,' '
call affascii
pop ax
popf
pop ax
ret
affsigne endp
affascii proc near
push ax
push dx
mov dl,al
mov ah,2
int 21h
pop dx
pop ax
ret
affascii endp

affdecimal proc near
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
call affchiffre
dec cx
JNZ affichage
pop cx
pop bx
ret
affdecimal endp
affchiffre proc near
push ax
push dx
add al,48
mov dl,al
mov ah,2
int 21h
pop ax
pop dx
ret
affchiffre endp

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

;CommandLine db 128 dup (' ')
get_command_line proc near
push es ds
pusha

push es
mov ax,sb_seg
mov es,ax
mov di,offset CommandLine
pop es
	mov     bx,82h
	mov     al,es:[bx-2]
	cmp     al,0
	jne     TestNext
	jmp     NoCmdLine
TestNext:
	mov     al,es:[bx]
	cmp     al,0
	jne     GetIt
	jmp     NoCmdLine

GetIt:
	mov     cl,es:[bx]
cmp cl,97
jb nonezeze
cmp cl,122
ja nonezeze
sub cl,32 ;met majuscules...
nonezeze:

push cx es ax
mov ax,sb_seg
mov es,ax
cmp cl,' ' ;marque pas dans le buffer de commande les espace...
jne reererer
dec di
jmp rttrrt
reererer:
mov es:[di],cl
rttrrt:
pop  ax es cx

;push cx dx
;mov dl,cl
;mov ah,02h
;int 21h
;pop dx cx

inc di
inc bx

	cmp     cl,0Dh
	je      GotIt
	jmp     GetIt
GotIt:
;......................... utilisation de la command line...

mov dl,10
mov ah,02h
int 21h

mov dl,13
mov ah,02h
int 21h



mov ax,sb_seg
mov ds,ax
mov es,ax

;jmp NoCmdLine

mov si,offset CommandLine
mov di,offset mod_file
;push cx dx
;mov cx,8
;zezeezez:

mov bx,-1 ;nombre de caracteres/
mov cx,128
ere:
inc bx

cmp byte ptr es:[si],'.'                                      ;espace=97 arrete a 13...
jne errrre
cmp byte ptr es:[si+1],'M'
jne errrre
cmp byte ptr es:[si+2],'O'
jne errrre
cmp byte ptr es:[si+3],'D'
jne errrre
;....

jmp modtrouve
errrre:
inc si

loop ere
jmp NoCmdLine

modtrouve:
;dans bx nombre de caracteres dans le .MOD (1 a 8)
sub si,bx
mov di,offset mod_file
mov cx,bx
rep movsb

;mov dl,es:[di]
;mov ah,02h
;int 21h

;inc di
;loop zezeezez
;pop dx cx

;mov es:[di],0
;mov es:[di+1],10
;mov es:[di+2],13
;mov es:[di+3],'$'

;.....................
mov si,offset mod_file
mov di,offset mod_file2
mov cx,bx ;nombre de caracteres...
rep movsb

popa
pop  ds es
ret

NoCmdLine:
mov ax,sb_seg
mov ds,ax
mov es,ax

mov dx,offset syntax
mov ah,09h
int 21h

popa
pop  ds es

MOV     AX,04C00H
INT     21H


popa
pop  ds es
ret
get_command_line endp


SUPER_SIGNE PROC NEAR
push es dx ax bx cx

mov ah,03
mov bh,0
int 10h
dec dl
jc erreer
mov dl,0
erreer:
mov ah,02h
int 10h

mov ax,sb_seg
mov es,ax

inc es:[SUPER_SIGNE2]
cmp es:[SUPER_SIGNE2],4
jne reerttert
mov es:[SUPER_SIGNE2],0
reerttert:

mov ah,02h ;SUPER_SIGNE2 DB 0
cmp es:[SUPER_SIGNE2],0
jne reertter
mov dl,'ù'
int 21h
jmp er
reertter:
cmp es:[SUPER_SIGNE2],1
jne reerttertr
mov dl,'+'
int 21h
jmp er
reerttertr:
cmp es:[SUPER_SIGNE2],2
jne reerttertt
mov dl,'*'
int 21h
jmp er
reerttertt:
cmp es:[SUPER_SIGNE2],3
jne reertterttt
mov dl,'+'
int 21h
jmp er
reertterttt:
er:
pop cx bx ax dx es
ret
SUPER_SIGNE ENDP

SUPER_SIGNE2b PROC NEAR
push es dx ax bx cx

mov ax,sb_seg
mov es,ax

inc es:[SUPER_SIGNE3]
cmp es:[SUPER_SIGNE3],4
jne jer
mov es:[SUPER_SIGNE3],0

mov ah,03
mov bh,0
int 10h
dec dl
jc jerreer
mov dl,0
jerreer:
mov ah,02h
int 10h

mov ax,sb_seg
mov es,ax

inc es:[SUPER_SIGNE2]
cmp es:[SUPER_SIGNE2],4
jne jreerttert
mov es:[SUPER_SIGNE2],0
jreerttert:

mov ah,02h ;SUPER_SIGNE2 DB 0
cmp es:[SUPER_SIGNE2],0
jne jreertter
mov dl,'ù'
int 21h
jmp jer
jreertter:
cmp es:[SUPER_SIGNE2],1
jne jreerttertr
mov dl,'+'
int 21h
jmp er
jreerttertr:
cmp es:[SUPER_SIGNE2],2
jne jreerttertt
mov dl,'*'
int 21h
jmp jer
jreerttertt:
cmp es:[SUPER_SIGNE2],3
jne jreertterttt
mov dl,'+'
int 21h
jmp er
jreertterttt:
jer:
pop cx bx ax dx es
ret
SUPER_SIGNE2b ENDP



START:                                  ;DEBUT DU PROGRAMME

;     mov ax,03h
;     int 10h

     call get_command_line

mov ah,04ah
mov bx,TAILLE_DU_FICHIER_EXE*64
int 21h

;copie le fichier...

;BIBERMAN SEGMENT USE16
;BIBERMAN2 DB 0ffffh DUP (?)
;BIBERMAN ENDS

mov ax,sb_seg
mov ds,ax

mov dx,offset mod_file
mov ah,03dh ;ouverture du fichier avec handle.
mov al,00h  ;ouverture du fichier pour lecture.
int 21h
jc erreur_file;saute si carry=1
;dans ax:handle fichier
push ax
mov ax,sb_seg
mov es,ax
mov ds,ax
pop ax
mov word ptr es:[handle_mod_file],ax

;...
mov dx,offset syntax2
mov ah,09h
int 21h
;...

;.............cree le fichier de copie...
;REWRITE PROC NEAR ;cree un fichier
mov ax,sb_seg    ;SEGMENT USE16
mov es,ax
mov ds,ax
mov dx,offset MOD_FILE2
mov ax,03c00h
mov cx,0 ;attribut!
int 21h
jnc sddddsdsds
jmp erreur_file2
ret
sddddsdsds:
mov word ptr es:[handle_mod_file2],ax
;ret
;REWRITE ENDP

call load_file ;................charge la zik en memoire...
	       ; convertis les pattern...

;.....................re-ouvre le fichier de lecture
mov ax,sb_seg
mov ds,ax

mov dx,offset mod_file
mov ah,03dh ;ouverture du fichier avec handle.
mov al,00h  ;ouverture du fichier pour lecture.
int 21h
jc erreur_file;saute si carry=1
;dans ax:handle fichier
push ax
mov ax,sb_seg
mov es,ax
mov ds,ax
pop ax
mov word ptr es:[handle_mod_file],ax

;...............
;entree ds:dx et cx: nombre d'octet a ecrire

mov ecx,es:[mod_file_size]
water:

cmp ecx,0ffffh
jna errereerreerer

push cx
mov cx,0FFFFh
call lis
call SUPER_SIGNE
call ecris
pop cx
sub ecx,0ffffh
jmp water

errereerreerer:
push cx
call lis
call SUPER_SIGNE
call ecris
pop cx
;......................modifie le segment pattern

;place le pointeur dans le fichier de copie sur les patterns.

;.................refabrique nouvo header...

mov ax,sb_seg
mov es,ax
mov ds,ax
mov word ptr bx,es:[handle_mod_file2]

mov ah,42h
mov al,00h

mov cx,0
mov dx,0 ;ecirs aussi le header
int 21h
jc erreur_file2 ;saute si carry=1

mov ax,sb_seg
mov es,ax
mov ds,ax
mov dx,offset header_mod

mov ecx,1084
mov word ptr bx,es:[handle_mod_file2]
mov ax,04000h
int 21h
jc erreur_file2 ;saute si carry=1
;..................

mov ax,sb_seg
mov es,ax
mov ds,ax
mov word ptr bx,es:[handle_mod_file2]

mov ah,42h
mov al,00h

mov cx,0
mov dx,1084 ;ecirs aussi le header
int 21h
jc erreur_file2 ;saute si carry=1

call ecris2 ;nouveaux pattern...

;......................ferme les fichiers...
mov ax,sb_seg
mov es,ax
mov ds,ax
mov word ptr bx,es:[handle_mod_file]
mov ah,03eh
int 21h
jc erreur_file ;saute si carry=1
mov ax,sb_seg
mov es,ax
mov ds,ax
mov word ptr bx,es:[handle_mod_file2]
mov ah,03eh
int 21h
jc erreur_file2 ;saute si carry=1

MOV     AX,04C00H
INT     21H

erreur_file:

mov ax,sb_seg
mov ds,ax
mov es,ax

mov dx,offset mod_file
mov ah,09h
int 21h

mov dx,offset not_found
mov ah,09h
int 21h


;mov es:[di],0
;mov es:[di+1],10
;mov es:[di+2],13
;mov es:[di+3],'$'


MOV     AX,04C00H
INT     21H


erreur_file2:

mov ax,sb_seg
mov ds,ax
mov es,ax

mov dx,offset mod_file2
mov ah,09h
int 21h

mov dx,offset not_found
mov ah,09h
int 21h


;mov es:[di],0
;mov es:[di+1],10
;mov es:[di+2],13
;mov es:[di+3],'$'


MOV     AX,04C00H
INT     21H


CODE      ENDS

END START
