vbl proc near

push dx ax

call raster1

		mov     dx,3dah
vbl1:           in      al,dx
		test    al,8
		jne     vbl1
vbl2:           in      al,dx
		test    al,8
		je      vbl2

call raster2

pop ax dx
ret
vbl endp

raster1 proc near

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
ret
raster1 endp


raster2 proc near

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
ret
raster2 endp



