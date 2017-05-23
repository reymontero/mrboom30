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
SIMAGE1 db 'R!'
        DB 64000 DUP ('')
        db 'R!'

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

handle_mod_file dw 0

Fichier1 db  "P.EXE",0
Fichier1B db "P.EXE",0

handlefichier dw 0
handlefichier2 dw 0

texteerreur db 'Fichier non trouv‚.$'

TEXTEFIN db  'Grossit P.EXE juska une taille de 35000 octets.$',13,10

POLLY2    ENDS

;-----------------------------------------
CODE      SEGMENT USE16
          ASSUME CS:CODE,DS:CODE,SS:PILE

tata2 db 0

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

affsigne proc near

add al,cs:[tata2]
add cs:[tata2],28

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

;IMAGE1 SEGMENT USE16   ;ou on place le fichier au debut
;SIMAGE1 DB 64000 DUP ('')
;IMAGE1 ENDS
;
;IMAGE2 SEGMENT USE16 ;ou on le retravaille
;SIMAGE2 DB 64000 DUP ('?')
;
;IMAGE2 ENDS
;
;IMAGE3 SEGMENT USE16
;SIMAGE3 DB 64000 DUP ('?')
;        DB 200 ;permet d'viter que la derniere pixel soit la meme ke celle d'avant
;               ;INDISPENCABLE
;IMAGE3 ENDS
;
;COPIE1 SEGMENT USE16
;SCOPIE1 DB 64000 DUP ('?')
;DB 200
;COPIE1 ENDS
;
;COPIE2 SEGMENT USE16
;SCOPIE2 DB 64000 DUP ('?')
;DB 200
;COPIE2 ENDS
;
;POLLY2     SEGMENT USE16
;
;Fichier1 db  "B.EXE",0
;Fichier1B db "B.EXE",0

mov ax,polly2
mov ds,ax
mov es,ax
mov dx,offset fichier1
mov ah,03dh
mov al,0010B
int 21h
jc erreur_fileedfsdfs
mov word ptr es:[handle_mod_file],ax

;... deplacement a l'interieur du fichier rmd ...
mov word ptr bx,es:[handle_mod_file]
mov ah,042h
mov al,02h ;debut du fichier
xor dx,dx
xor cx,cx
int 21h
jc erreur_fileedfsdfs
push ax
movzx eax,dx
shl eax,16
pop ax
;mov word ptr es:[mod_file_size],ax
;mov word ptr es:[mod_file_size+2],dx
;on va mettre ca a la place de la caracterisation !!!

call num

sub eax,255442 ;:513000
neg eax
mov ecx,eax
call num
;dans ecx on a ce k'on doit recopier a la fin du fichier

mov ax,polly2
mov ds,ax
mov es,ax
mov word ptr bx,es:[handle_mod_file]

push ds
mov ax,IMAGE1
mov ds,ax
xor dx,dx
;IMAGE1 SEGMENT USE16   ;ou on place le fichier au debut
;SIMAGE1 DB 64000 DUP ('')
;IMAGE1 ENDS
mov ax,04000h
int 21h
jc erreur_fileedfsdfs
pop ds

movzx eax,ax
call num

;...lecture du fichier...

mov ax,polly2
mov ds,ax
mov es,ax

mov dx,offset textefin
mov  ah,09h
int 21h
  MOV     AX,04C00H
  INT     21H

erreur_fileedfsdfs:

mov ax,polly2
mov ds,ax
mov es,ax


mov dx,offset texteerreur
mov  ah,09h
int 21h

  MOV     AX,04C00H
  INT     21H

CODE      ENDS

END START
