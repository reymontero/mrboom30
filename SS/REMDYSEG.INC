


;important: l'intrument 0 est l'intrument nul.
;il n'existe pas vraiment. toutes ses valeurs sont a 0

longueur_sample      DW 32+32 DUP (0)   ;longueur des 32 instruments.
                                        ;+32 bonus
volume_sample        DW 32 DUP (0)      ;volume par defalut des 32 instruments
depart_loop_sample   DW 32+32 DUP (0)   ;depart loop des 32 instruments
                                        ;+32 bonus
longueur_loop_sample DW 32+32 DUP (0)   ;longueur loop des 32 instruments
                                        ;+32 bonus
segment_sample       DW 32+32 DUP (0)   ;addresse du segment de chaque sample.
                                        ;+32 bonus
segment_sample_verif DW 32+32 DUP (0)   ;0 mean no sample
                                        ;1 mean one SAMPLE


;*1.059463094 ou 0.943874312 ou monter/descendre d'un ton.
;Middle C freq: C4=8363
;               C5=16726
; La table des frequences ! Pour chaque note et en HZ.
;*1.059463094 ou 0.943874312 ou monter/descendre d'un ton.
;Middle C freq: C4=8363
;               C5=16726
; La table des frequences ! Pour chaque note et en HZ.


       ;   -  B7 - A#7  - A7    - G#7  - G7  - F#7 - F7  - E7  - D#7 - D7  - C#7 - C7  -
sbfreq DD  126297,119209,112518,106203,100242,94616,89306,84293,79562,75097,70882,66903
      ;   -  B6 - A#6 - A6  - G#6 - G6  - F#6 - F6  - E6  - D#6 - D6  - C#6 - C6  -
      DD   63148,59604,56259,53101,50121,47308,44653,42146,39781,37548,35441,33451
      ;   -  B5 - A#5 - A5  - G#5 - G5  - F#5 - F5  - E5  - D#5 - D5  - C#5 - C5  -
      DD   31574,29802,28129,26550,25060,23654,22326,21073,19890,18774,17720,16726
      ;   -  B4 - A#4 - A4  - G#4 - G4  - F#4 - F4  - E4  - D#4 - D4  - C#4 - C4  -
      DD   15787,14901,14064,13275,12530,11827,11163,10536,09945,09387,08860,08363
      ;   -  B3 - A#3 - A3  - G#3 - G3  - F#3 - F3  - E3  - D#3 - D3  - C#3 - C3  -
      DD   07893,07450,07032,06637,06265,05913,05581,05268,04972,04693,04430,04181
      ;   -  B2 - A#2 - A2  - G#2 - G2  - F#2 - F2  - E2  - D#2 - D2  - C#2 - C2  -
      DD   03946,03725,03516,03318,03132,02956,02790,02634,02486,02346,02215,02090
      ;   -  B1 - A#1 - A1  - G#1 - G1  - F#1 - F1  - E1  - D#1 - D1  - C#1 - C1  -
      DD   01973,01862,01758,01659,01566,01478,01395,01317,01243,01173,01107,01045
      ;   -  B0 - A#0 - A0  - G#0 - G0  - F#0 - F0  - E0  - D#0 - D0  - C#0 - C0  -
      DD   00986,00931,00879,00829,00783,00739,00697,00658,00621,00586,00553,00522

;...............variables pour les 4 voix...

offset_sample DW 8+4 DUP (0)          ;ou on est dans le sample de chaque voix.
offset_compteur_sample DW 8+4 DUP (0) ;COMPTEUR POUR LE CALCUL DE LA PROGRESSION
                                    ;que l'on doit donner a l'offset du
                                    ;sample de chaque voix en fonction de la
                                    ;frequence a laquelle il est joue.

mixage                   DW 8+4 DUP (0) ;octets calcules pour les 4 voix.

sample_joue_en_ce_moment DW 8+4 DUP (0);numero du sample joue sur les 8  voix
                                      ;de 1 a 31 (et non 0 a 31)
                                      ;cas particulier si=0 pas de sample joue...
                                      ;donc on met 0 a la fin d'un sample non
                                      ;loupeur...

                                      ;+4 = 4 voix de bonus...pour sample FX

longueur_sample_joue      DW 8+4 DUP (0)   ;
depart_loop_sample_joue   DW 8+4 DUP (?)   ;
longueur_loop_sample_joue DW 8+4 DUP (?)   ;
note_joue_par_sample      DD 8+4 DUP (-1)  ;place la vitesse (calculee avec
                                       ;SB freq calc....)
                                       ;+4 = 4 voix de bonus...pour sample FX
                                       ;-1=pas de note encore jouee.

volume_de_la_voix         DW 8+4 DUP (0)  ;volume pour chaque voix...
                                          ;+4 = 4 voix de bonus...pour sample FX
sauve_viseur_dans_sbfreq  DW 8 DUP (0)   ;sauvegarde du viseur lorsque l'on
                                         ;pioche la frequence
                                         ;utile pour les effets pour cacule
                                         ;la frequence d'une note au dessus.
                                         ;utile pour SB et pour GUS !!!

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

;..........................................
;............ variables pour la vitesse d'execution du sample.

; Speed/50 = nombre de secondes par ligne...

; vitesses possibles 1,2,3,...,31

;Speed 1: Speed/50=0.02 soit 0.02 secondes par ligne!
;le player est a 10000 fois par seconde...
;il faut donc changer de lignes toutes les 10000*0.02=200 fois ke le player
;est appel‚.

; stop:le bmp peut changer...
; on a donc:
; BMP * 2/5= 50 HZ.

;donc chaque valeur du speed wait doi etre calcule par:
; (SPeed*10000)/(BMP * 2/5)
; donc comme ya 32 valeur de speed possible on va faire un tablo
; de base.ou il ne restera plus k'a diviser par le bmp et a placer dans speed
; wait si on change la valeur de la vitesse bmp...

;Speed=nombre de ticks par ligne.

speed_song   DW  6
bmp_speed    DB  125
             db  0 ;pour allignement


;                    0        1     2      3      4      5      6      7
speed_wait2  DD 0FFFFFFFFh,025000,050000,075000,100000,125000,150000,175000
;                      8      9     10     11     12     13     14     15
                 DD 200000,225000,250000,275000,300000,325000,350000,375000
;                      16     17    18     19     20     21     22     23
                 DD 400000,425000,450000,475000,500000,525000,550000,575000
;                      24     25    26     27     28     29     30     31
                 DD 600000,625000,650000,675000,700000,725000,750000,775000

; NOTE on utilise SPeed_WAIT2 aussi pour la GUS mais on divise par 16
; avant de calculer pour Speed_Wait
; par default on prend la table: BMP=125

;                 0       1    2    3    4    5    6    7    8    9    10

;Speed_wait dd 0FFFFFFFFh,0200,0400,0600,0800,1000,1200,1400,1600,1800,2000
;;              11   12   13   14   15   16   17   18   19   20
;           dd 2200,2400,2600,2800,3000,3200,3400,3600,3800,4000
;;              21   22   23   24   25   26   27   28   29   30
;           dd 4200,4400,4600,4800,5000,5200,5400,5600,5800,6000
;;              31
;           dd 6200

speed_wait DD 0FFFFFFFFh
           DD 31 DUP (?)  ;calcule au debut du programme...

speed_compteur_save DD ?  ;vitesse 6 par default.
                       ;on place ici le nombre dans speed_wait k'on a choisit
                       ;ca reviendra a ca apres etre arrive a 0...
                       ;calcule au debut du programme...
speed_compteur DD ?    ;calcule au debut du programme...

;;pour l'effet D,le parametre est dans le fichier comme du decimal pris pour
;;de l'hexa!!! bizarre..enfin avec ce tableau on peut convertir
;conv_list  DB 00,01,02,03,04,05,06,07,08,09,10h,11h,12h,13h,14h,15h,16h,17h,18h,19h,20h
;  DB 21h,22h,23h,24h,25h,26h,27h,28h,29h,30h,31h,32h,33h,34h,35h,36h,37h,38h
;  DB 39h,40h,41h,42h,43h,44h,45h,46h,47h,48h,49h,50h,51h,52h,53h,54h,55h,56h
;  DB 57h,58h,59h,60h,61h,62h,63h


;****************** GUS !!! *************************************************

  gus_base     DW ? ;260h
 ; gus_base2    EQU 260h
  gus_status   DW ? ;gus_base2+006h
  gus_voice    DW ? ;gus_base2+102h
  gus_command  DW ? ;gus_base2+103h
  gus_datalo   DW ? ;gus_base2+104h
  gus_datahi   DW ? ;gus_base2+105h
  gus_dramio   DW ? ;gus_base2+107h

table_volumes_gus  DW 64 dup (1500h)
                   DW 1500h
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

;gusfreq DD  126297/voix_gus,119209/voix_gus,112518/voix_gus,106203/voix_gus,100242/voix_gus,94616/voix_gus,89306/voix_gus,84293/voix_gus,79562/voix_gus,75097/voix_gus,70882/voix_gus,66903/voix_gus
;      ;   -  B6 - A#6 - A6  - G#6 - G6  - F#6 - F6  - E6  - D#6 - D6  - C#6 - C6  -
;note ne fonctionne pas en plus de 16 bits cette merde de tasm!!!

;on a rajoute un valeur au debut...!!! car s'etait trop grave.. avant!! uhm!
gusfreq DD  9021,9021,8514,8037,7585,7160,6758,9379,6020,5683,5364,5063,4778
      ;   -  B6 - A#6 - A6  - G#6 - G6  - F#6 - F6  - E6  - D#6 - D6  - C#6 - C6  -
      DD   63148/voix_gus,59604/voix_gus,56259/voix_gus,53101/voix_gus,50121/voix_gus,47308/voix_gus,44653/voix_gus,42146/voix_gus,39781/voix_gus,37548/voix_gus,35441/voix_gus,33451/voix_gus
      ;   -  B5 - A#5 - A5  - G#5 - G5  - F#5 - F5  - E5  - D#5 - D5  - C#5 - C5  -
      DD   31574/voix_gus,29802/voix_gus,28129/voix_gus,26550/voix_gus,25060/voix_gus,23654/voix_gus,22326/voix_gus,21073/voix_gus,19890/voix_gus,18774/voix_gus,17720/voix_gus,16726/voix_gus
      ;   -  B4 - A#4 - A4  - G#4 - G4  - F#4 - F4  - E4  - D#4 - D4  - C#4 - C4  -
      DD   15787/voix_gus,14901/voix_gus,14064/voix_gus,13275/voix_gus,12530/voix_gus,11827/voix_gus,11163/voix_gus,10536/voix_gus,09945/voix_gus,09387/voix_gus,08860/voix_gus,08363/voix_gus

      ;   -  B3 - A#3 - A3  - G#3 - G3  - F#3 - F3  - E3  - D#3 - D3  - C#3 - C3  -
      DD   07893/voix_gus,07450/voix_gus,07032/voix_gus,06637/voix_gus,06265/voix_gus,05913/voix_gus,05581/voix_gus,05268/voix_gus,04972/voix_gus,04693/voix_gus,04430/voix_gus,04181/voix_gus
      ;   -  B2 - A#2 - A2  - G#2 - G2  - F#2 - F2  - E2  - D#2 - D2  - C#2 - C2  -
      DD   03946/voix_gus,03725/voix_gus,03516/voix_gus,03318/voix_gus,03132/voix_gus,02956/voix_gus,02790/voix_gus,02634/voix_gus,02486/voix_gus,02346/voix_gus,02215/voix_gus,02090/voix_gus
      ;   -  B1 - A#1 - A1  - G#1 - G1  - F#1 - F1  - E1  - D#1 - D1  - C#1 - C1  -
      DD   01973/voix_gus,01862/voix_gus,01758/voix_gus,01659/voix_gus,01566/voix_gus,01478/voix_gus,01395/voix_gus,01317/voix_gus,01243/voix_gus,01173/voix_gus,01107/voix_gus,01045/voix_gus
      ;   -  B0 - A#0 - A0  - G#0 - G0  - F#0 - F0  - E0  - D#0 - D0  - C#0 - C0  -
      DD   00986/voix_gus,00931/voix_gus,00879/voix_gus,00829/voix_gus,00783/voix_gus,00739/voix_gus,00697/voix_gus,00658/voix_gus,00621/voix_gus,00586/voix_gus,00553/voix_gus,00522/voix_gus

;SAmple 0=RIEN, sample 01 a 31=sample du .RMD
;               sample 32 a 63=sample BONUS

adresse_debut_sample_gus   DD 32+32 DUP (0)
adresse_fin_sample_gus     DD 32+32 DUP (0)
adresse_loop_sample_gus    DD 32+32 DUP (0)

;des sauvegardes..utile pour l'effet 9 (offset)
gus_adresse_debut_sample_GUS DD 8 DUP (0) ;joue sur chaque voix...
gus_adresse_fin_sample_GUS   DD 8 DUP (0)
gus_adresse_loop_sample_GUS  DD 8 DUP (0)

pattern_load DB 8*4 DUP (?)        ;ou on place la ligne de pattern lu dans
                                   ;la GUS.

;pour la gus on fait du 10000/8 hz=1250 Hz!

;---DB !

header_IFF DB 78 DUP (?)   ;on charge ici le header de l'IFF en cours de
                           ;traitement

frequence EQU 10000


nombre_de_voix DB ?                 ;nombre de voix dans le mod...
                                    ;remplis par load_file
                                    ;Nombre de voix dans le .MOD

nombre_de_voix_multiplie_par_2  dw ?

;!

MEMOIRE_GUS_UTILISEE dd ? ;en octets.calcule d'abord dans LOAD_FILE

old_int8     DD ? ;pour sauvegarde timer...
old_timer_compteur DW 548 ;compteur pour savoir kan blancer l'ancienne interruption
old_timer_compteur_GUS DW 17 ;compteur pour savoir kan blancer l'ancienne interruption
dsp_adr   DW 220h   ;port du dsp.SB - METTRE ? -

first_time      dw  0 ;pour utiliser calc_freq_sb 1 seule fois.

handle_mod_file DW  ?   ;handler du fichier mod!
handle_IFF_file DW  ?   ;handler du fichier IFF!
mod_file_size   DD  ?   ;taille du fichier mod!

;buffer_load_gus DB taille_buffer_load DUP (?)
;ENVIRONMENT DB 256 DUP (?)

taille_buffer_load equ 1084         ;512

header_mod DB 1084 DUP (?) ;on charge ici le header du mod!!
                           ;aussi utilis‚ pour buffer gus...
                           ; et comme environnement buffer

;................position dans le mod/tout sur les patterns...
numero_de_ligne_dans_pattern    DD 0 ;dans le pattern courant.
viseur_dans_arrangement_chanson DW 0 ;

nombre_total_de_pattern_chanson DW ? ;nombre total dans l'arrangemement de
                                     ;la chanson. -1
nombre_total_de_pattern_mod     DB ? ;nombre total de pattern dans le mod.
arrangement_de_la_chanson DB 128 DUP (?)    ;ordre des patterns a executer.

taille_segment_pattern DD ?          ;en octets.
segment_pattern        DW 0          ;addresse du segment des patterns...
viseur_dans_pattern    DD ?          ;vise sur la note jouee...
                                     ;valeur k'on additionne pour
                                     ;piocher dans le segment pattern(pour sb)
                                     ;ou dans la DRAM de la GUS

;..................variables pour les effets...................

effet_d DW 0,0,0  ;premier mot: 0=pas active,1=active
                 ;deuxieme mot: numero le la ligne ou on se place dans la
                 ;pattern suivante...
                 ;troisieme mot: prochain viseur_dans_arrangement k'on mettra...

effet_b DW 0,0  ;premier mot  : 0=pas active,1=active
                ;deuxieme mot  : numero du pattern
                ;dans l'arrangement ou on se place

effet_e6 DW 0   ;premier mot  : 0=pas active,1=active

;POUR 8 VOIX:


;table_de_saut DD OFFSET nopper,OFFSET nopper,OFFSET nopper,OFFSET nopper
;              DD OFFSET nopper,OFFSET nopper,OFFSET nopper,OFFSET nopper

speed_compteur_test_effet12 DD 8 DUP (0)


;............. effect entre lignes. (pour les 8 voix)

freq_joue_gus  DW 8 DUP (?)


;utilises de maniere differente suivant les effets...

compteur_effect_entre_ligne DW 8 DUP (?)
adder_effect_entre_ligne    DW 8 DUP (?)

compteur_effect_entre_ligne_save DW  (?)   ;par default
                                           ;change si on change la vitesse
                                           ;definis la rapidite...
                                           ;cacule par proc def_vitesse_tick
;arpegio:  ;utilise par GUS et SB
           ;sauf que la GUS place
frequence_pour_les_3_notes1 DD 8 DUP (?)
frequence_pour_les_3_notes2 DD 8 DUP (?)
frequence_pour_les_3_notes3 DD 8 DUP (?)
compteur_pour_arpegio  DD 8 DUP (?)
compteur_pour_arpegio2 DD 8 DUP (?)
compteur_pour_arpegio3 DW 8 DUP (?)

;loop
fxloop1                DW (-1) ;nombre de fois k'on doit faire la loop
                               ;1 indique k'on peut faire une nouvelle loop
fxloop2                DD (0) ;sauvegarde de la ligne ou on doit
                              ;retourner
;note cut
note_delay  DD 8 DUP (0)
note_delay2 DW 8 DUP (0) ;POUR SB:pour sauver sample_joue_en_ce_moment
                         ;et on met 0 le temps k'on attend.
                         ;Pour GUS: mode derniere la voix k'on a lut ici
;note retrig
note_retrig  DD 8 DUP (0)

;vibrato
;what_vibrato            DD OFFSET  vibrato_sin ;vise sur kel tablo on choisit

vibrato_sin             DW    0, -12, -24, -36, -49, -61, -74, -85, -97,-108,-120,-130,-141,-151,-161,-170
                        DW -180,-189,-197,-204,-212,-218,-224,-229,-235,-239,-244,-247,-250,-251,-253,-254
                        DW -254,-253,-251,-250,-247,-244,-239,-235,-229,-224,-218,-212,-204,-197,-189,-180
                        DW -170,-161,-151,-141,-130,-120,-108,-97, -85, -74, -61, -49, -36, -24, -12, 0
                        DW    0,  12,  24,  36,  49,  61,  74,  85,  97, 108, 120, 130, 141, 151, 161, 170
                        DW  180, 189, 197, 204, 212, 218, 224, 229, 235, 239, 244, 247, 250, 151, 253, 254
                        DW  254, 253, 251, 250, 247, 244, 239, 235, 229, 224, 218, 212, 204, 197, 189, 180
                        DW  170, 161, 151, 141, 130, 120, 108, 97,  85,  74,  61,  49,  36,  24,  12, 0



vibrato_1               DW    0,  -8, -16, -24, -32, -40, -48, -56, -64, -72, -80, -88, -96,-104,-112,-120
                        DW -128,-136,-144,-152,-160,-168,-176,-184,-192,-200,-208,-216,-224,-240,-248,-256
                        DW -256,-248,-240,-232,-224,-216,-208,-200,-192,-184,-176,-168,-160,-152,-144,-136
                        DW -128,-120,-112,-104,-096, -88,-080, -72,-064, -56,-048, -40,-032, -24, -16,-8
                        DW    0,   8,  16,  24,  32,  40,  48,  56,  64,  72,  80,  88,  96, 104, 112,120
                        DW  128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 240, 248,256
                        DW  256, 248, 240, 232, 224, 216, 208, 200, 192, 184, 176, 168, 160, 152, 144,136
                        DW  128, 120, 112, 104, 096,  88, 080,  72, 064,  56, 048,  40, 032,  24,  16, 8

vibrato_2               DW -256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256
                        DW -256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256
                        DW -256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256
                        DW -256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256
                        DW  256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256
                        DW  256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256
                        DW  256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256
                        DW  256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256

vibrato_viseur          DW 8 DUP (0) ;viseur dans tablos.

vibrato_fx_prof         DW 8 DUP (0) ;pour sauvegarde des info sur
vibrato_fx_speed        DW 8 DUP (0) ;le vibrato en cours!

vibrato_compteur_save   DW 8 DUP (0FFFFh)
vibrato_compteur        DW 8 DUP (0)
save_note_vibrato       DD 8 DUP (0) ;pour sauvegarder la note de base pour
SAVE_NOTE_PORTAMENTO    DD 8 DUP (-1) ;pour sauvegarder la note de base pour
                                      ;-1 = pas de note precedament.
SAVE_PORTO_VIBRATO      dw 8 DUP (?) ;pour la GUS...
sauvegarde_de_la_vitesse_du_portamento dw 8 DUP (0)

;.......tremolo (utilise les tables de vibrato...)
;what_tremolo           DD OFFSET  vibrato_sin ;vise sur kel tablo on choisit

tremolo_viseur          DW 8 DUP (0) ;viseur dans tablos.

tremolo_fx_prof         DW 8 DUP (0) ;pour sauvegarde des info sur
tremolo_fx_speed        DW 8 DUP (0) ;le vibrato en cours!

tremolo_compteur_save   DW 8 DUP (0FFFFh)
tremolo_compteur        DW 8 DUP (0)
save_volume_tremolo     DW 8 DUP (0) ;pour sauvegarder la note de base pour

;effets GUS
portamento_gus          dw 8 DUP (0) ;ce k'on rajoute a la frequence joue
                                     ;en ce moment...
vibrato_gus             dw 8 DUP (0) ;ce k'on rajoute a la frequence joue
                                     ;en ce moment...
joystick_compteur       db  0
joystick_jc             db  0   ;0= comme chez moi, 1 =jc
;.............................................................


byte_load_left  dd  ? ;nombre d'octets qu'il reste a charger...

ligne_percent dw ?    ;position curseur


first_time2     db  0;pour utiliser decypt une seule fois.

include texte.inc

db '‹ÒØ'
