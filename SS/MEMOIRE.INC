;--------------------- r‚serve de la m‚moire pour mettre les donn‚es. ----
;2.29 - Function 0501h - Allocate Memory Block:
;In:  AX     = 0501h
;  BX:CX  = size of block in bytes (must be non-zero)
;Out: if successful:
;    carry flag clear
;    BX:CX  = linear address of allocated memory block
;    SI:DI  = memory block handle (used to resize and free block)
mov eax,0200000h ;2mega
mov cx,ax
shr eax,16
mov bx,ax
mov ax,501h
int 31h
jNC ca_roule_roll
mov edx,offset pas_de_mem
mov ah,9
int 21h
mov ax,4c00h                    ; AH=4Ch - Exit To DOS
int 21h                         ; DOS INT 21h
ca_roule_roll:

push bx cx ; linear address of allocated memory block

;2.0 - Function 0000h - Allocate Descriptors:
;--------------------------------------------
;  Allocates one or more descriptors in the client's descriptor table. The
;descriptor(s) allocated must be initialized by the application with other
;function calls.
;In:
;  AX     = 0000h
;  CX     = number of descriptors to allocate
;Out:
;  if successful:
;    carry flag clear
;    AX     = base selector
xor ax,ax
mov cx,1
int 31h
jNC ca_roule_roll2
mov edx,offset pbs1
mov ah,9
int 21h
mov ax,4c00h                    ; AH=4Ch - Exit To DOS
int 21h                         ; DOS INT 21h
ca_roule_roll2:
;2.5 - Function 0007h - Set Segment Base Address:
; Sets the 32bit linear base address field in the descriptor for the specified
;segment.
; In:   AX     = 0007h
; BX     = selector
;  CX:DX  = 32bit linear base address of segment

pop  dx cx ; linear address of allocated memory block
mov  bx,ax
mov  fs,ax
mov ax,0007
mov cx,si
mov dx,di
int 31h
;dans FS: selector sur donn‚es.

;2.6 - Function 0008h - Set Segment Limit:
;-----------------------------------------
;  Sets the limit field in the descriptor for the specified segment.
;  In:
;  AX     = 0008h
;  BX     = selector
;  CX:DX  = 32bit segment limit
;  Out:
;  if successful:
;    carry flag clear
;  if failed:
;    carry flag set
mov eax,0200000h-1 ;2mega
mov dx,ax
shr eax,16
mov cx,ax
mov bx,fs
mov ax,08h
int 31h
jNC tca_roule_roll
mov edx,offset pbs2
mov ah,9
int 21h
mov ax,4c00h                    ; AH=4Ch - Exit To DOS
int 21h                         ; DOS INT 21h
tca_roule_roll:

;-------------------------------------------------------------------------

;----- pour la memoire video
mov ax,0002h
mov BX,0a000h
int 31h
mov es,ax


