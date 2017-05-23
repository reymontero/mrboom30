; CRYPTAGE XOR 1ø)
; NOT puis add ?,40
; amener ici les fichiers textes...


.386P
NPT=100                                 ;NOMBRE DE PT

stackseg segment para STACK 'STACK'
         dw   512   dup (?)
stackseg ends

PILE      SEGMENT STACK USE16
  DW      512 DUP (0)
PILE      ENDS

IMAGE1 SEGMENT USE16   ;ou on place le fichier au debut
SIMAGE1 DB 64000 DUP ('?')
        DB 200 ;permet d'viter que la derniere pixel soit la meme ke celle d'avant
               ;INDISPENCABLE
IMAGE1 ENDS

IMAGE2 SEGMENT USE16 ;ou on le retravaille
SIMAGE2 DB 64000 DUP ('?')

IMAGE2 ENDS

IMAGE3 SEGMENT USE16
SIMAGE3 DB 64000 DUP ('?')
        DB 200 ;permet d'viter que la derniere pixel soit la meme ke celle d'avant
               ;INDISPENCABLE
IMAGE3 ENDS

COPIE1 SEGMENT USE16
SCOPIE1 DB 64000 DUP ('?')
DB 200
COPIE1 ENDS

COPIE2 SEGMENT USE16
SCOPIE2 DB 64000 DUP ('?')
DB 200
COPIE2 ENDS

POLLY2     SEGMENT USE16

Fichier1 db  "texte.txt",0
Fichier1B db "texte.inc",0

handlefichier dw 0
handlefichier2 dw 0

texteerreur db 'Fichier non trouv‚.$'

TEXTEFIN db  'XOR -DA ULTIMATE ANTI LAMER CRYPTATOR- V6.0',13,10
         db  '',13,10
         db  'TEXTE.TXT -> TEXTE.INC',13,10
         db  '',13,10
         db  'convertis le fichier texte.txt (db ''appuyez sur une touche'',13,10...)',13,10
         db  'en un truc db 78,80,90, (...)',13,10
         db  'a partir du fichier c:\b\texte.txt avec un  a la fin vers c:\b\texte.inc',13,10
         db  'note: le fichier texte source n''a aucune valeur directement en db 0, (variables normales)',13,10
         db  '[seul les cas particuliers retour CHARIOT,13,10 et ,0 sont geres...'
         db  'ATTENTION NE PAS METTRE CES CAS PARTICULIER EN COMMENTAIRE !!!'
         db  'Technique de cryptage: PYRAMIDE$',13,10

POLLY2    ENDS

;-----------------------------------------
CODE      SEGMENT USE16
          ASSUME CS:CODE,DS:CODE,SS:PILE

tata2 db 0
tata3 db 0 ;dernier truc

affsigne proc near


;-------------------------------------------------------------------
push bx
mov bl,al
add al,cs:[tata3]
mov cs:[tata3],bl
pop bx
;-------------------------------------------------------------------
add al,cs:[tata2]
add cs:[tata2],15 ;1


;                push bx
;                mov bl,al
;                add al,cs:[tata3]
;                add cs:[tata3],bl
;                pop bx

push ax
pushf
add ax,0
jns nonsigne
push ax
mov al,'-'
;call affascii
pop ax
neg ax
jmp sdfsdfsdf
nonsigne:
push ax
mov al,'+'
;call affascii
pop ax
sdfsdfsdf:
call affdecimal
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
loop affichage
pop cx
pop bx
ret
affdecimal endp

affchiffre proc near
push dx ax es

;dans al
add al,48

mov es:[di],al
inc di
inc cs:[nombre_doctetcopie]

pop es ax dx
ret
affchiffre endp

tata dw 0
toto dw 3+205*0 ;ligne
nombre_doctetcopie dw 0

REWRITE PROC NEAR ;cree un fichier
mov ax,POLLY2     ;SEGMENT USE16
mov es,ax
mov ds,ax

mov ax,03c00h
mov cx,0 ;attribut!
int 21h
jnc sddddsdsds
call erreur
ret
sddddsdsds:
mov di,offset handlefichier
stosw
ret
REWRITE ENDP

RESET PROC NEAR ;ouvre un fichier --------------------------------------------
mov ax,POLLY2
mov es,ax
mov ds,ax
mov ax,03D42h
mov cx,0                     ;attribut!
int 21h
jnc sddddsdsdsq
call erreur
ret
sddddsdsdsq:
mov di,offset handlefichier
stosw
ret
RESET ENDP ;------------------------------------------------------------------

CLOSE PROC NEAR ;ferme un fichier
mov ax,POLLY2     ;SEGMENT USE16
mov es,ax
mov ds,ax
mov si,offset handlefichier
LODsw
mov bx,ax
mov ax,03E00h
int 21h
jnc esddddsdsdsq
call erreur
ret
esddddsdsdsq:
ret
CLOSE ENDP

WRITEFILE PROC NEAR ;ecris dans un fichier
push ds es
mov ax,POLLY2     ;SEGMENT USE16
mov es,ax
mov ds,ax
mov si,offset handlefichier
LODsw
mov bx,ax
pop es ds

mov ax,04000h
mov cx,BP ;!!!64000
int 21h

jnc zesddddsdsdsq
call erreur
ret
zesddddsdsdsq:
ret
WRITEFILE ENDP
READFILE PROC NEAR ;lis dans un fichier

push es ds
mov ax,POLLY2     ;SEGMENT USE16
mov es,ax
mov ds,ax

mov si,offset handlefichier
LODsw
mov bx,ax
pop es ds

mov ax,03F00h
mov cx,64000
int 21h

jnc bbzesddddsdsdsq
call erreur
ret
bbzesddddsdsdsq:
ret
READFILE ENDP

ERREUR PROC NEAR
        mov    ax,3  ;MODE TEXTE
        int    10h   ;

mov ax,POLLY2     ;SEGMENT USE16
mov es,ax
mov ds,ax
        mov   ah,02h
        mov    dh,10
        mov    dl,10
        mov    bh,0
        int    10h

mov dx,offset texteerreur
mov  ah,09h
int 21h
  MOV     AX,04C00H               ;RETURN TO DOS (NOT WINDOWS OR SLOW OS PLEASE!)
  INT     21H
ret
ERREUR ENDP
AFFTEXT PROC NEAR
mov ax,IMAGE2     ;SEGMENT USE16
mov es,ax
mov ds,ax
        mov   ah,02h
        mov    dh,0
        mov    dl,0
        mov    bh,0
        int    10h

mov dx,offset simage2

mov  ah,09h
int 21h
  MOV     AX,04C00H               ;RETURN TO DOS (NOT WINDOWS OR SLOW OS PLEASE!)
  INT     21H
ret
AFFTEXT ENDP
;----------------------------------------------------------------------------
START:                                  ;DEBUT DU PROGRAMME

;-*--------*-*-*-*-*-**--*-*-* on charge les 4 fichierS.
mov dx,offset FICHIER1
call reset
mov bx,IMAGE1
mov dx,offset SIMAGE1
mov ax,image1
mov es,ax
mov ds,ax
mov dx,offset simage1
call readfile
call close
;-------------CONVERSION--------

;nombre_doctetcopie dw 0

mov cx,2000
mov ax,image2
mov es,ax
mov ax,image1
mov ds,ax
xor di,di
xor si,si

mov ax,0
mov bx,0 ;mode 'on modifie rien'

axxel:

;,13,10
;---- cas particulier
cmp dword ptr ds:[sI],',31,'
jne appletime
cmp dword ptr ds:[sI+2],'01,3'
jne appletime

mov byte ptr es:[di],','
inc di

add si,6
mov ax,13
call affsigne
add cs:[nombre_doctetcopie],2

mov byte ptr es:[di],','
inc di

mov ax,10
call affsigne
;fonctionne car on est de toute maniere en mode hors ''
appletime:
;------------------- cas particulier
cmp word ptr ds:[sI],'0,'
jne appletime2

mov byte ptr es:[di],','
inc di

add si,2
mov ax,0
call affsigne
inc cs:[nombre_doctetcopie]
;fonctionne car on est de toute maniere en mode hors ''
appletime2:
;---------------


cmp byte ptr ds:[sI],''
je trazetetetzertz

cmp byte ptr ds:[sI],''''
;---------- si c'est un ' on le recopie pas.
jne boomr

NOT BX ;change de mode
;mov al,ds:[si]
;mov es:[di],al  ;simple copie.
;movsb
;inc cs:[nombre_doctetcopie]
inc si
;;------ si c'est un double alors il faut afficher sa valeur (
cmp byte ptr ds:[sI],''''
jne axxel
not bx ;seconde fois cetait une  fausse alerte
jmp boomr
jmp axxel
boomr:
;---------------
cmp bx,0
je fddfgdfgdfge

mov al,ds:[si]

;and ax,0255
;
;push es ds
;pusha
call affsigne
;
;cmp cs:[tata],180
;jb okz
;add cs:[toto],205*1 ;ligne
;mov cs:[tata],0
;jmp pasdviurt
;okz:
;
;mov ax,image2
;mov es,ax
;mov di,offset SIMAGE2
;add di,cs:[tata]
;inc cs:[tata]
;add di,cs:[toto]


cmp byte ptr ds:[si+1],'''' ;si on est pas en fin de truc il faut mettre une virgule
jne pascettefois2
cmp byte ptr ds:[si+2],'''' ;sauf si c'est un double!
jne pascettefois
pascettefois2:

inc cs:[nombre_doctetcopie]
mov byte ptr es:[di],','
inc di
pascettefois:

;pasdviurt:
;popa
;pop  ds es

inc si
jmp axxel
fddfgdfgdfge:
;----recopie toute bete
inc cs:[nombre_doctetcopie]
movsb
jmp axxel

trazetetetzertz:

;--------------------------------
mov bp,cs:[nombre_doctetcopie]
mov dx,offset fichier1B
call REWRITE                             ;cree un fichier1

mov dx,offset fichier1B
call reset
mov ax,image2
mov es,ax
mov ds,ax
mov dx,offset image2
call WRITEFILE
call close
;......................................

        mov    ax,3  ;MODE TEXTE
        int    10h   ;

mov ax,POLLY2     ;SEGMENT USE16
mov es,ax
mov ds,ax
        mov   ah,02h
        mov    dh,0
        mov    dl,0
        mov    bh,0
        int    10h

mov dx,offset textefin
mov  ah,09h
int 21h

;int 12h
;mov ah,48h
;mov bx,0ffffh
;int 21h
;mov ax,bx
;call affsigne


  MOV     AX,04C00H
  INT     21H

CODE      ENDS

END START
