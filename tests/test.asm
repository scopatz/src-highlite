;
; screen handling primitives
;

.model large

.data

vseg    dw      0b000h
vmode   db      ?
x       dw      0
y       dw      0
color   db      07h
ofs     dw      0
xhite   db      8

; video information block

VIOinfo struc
	level   db      ?
		db      ?
		dw      ?
	flags   dw      ?
	mode    db      ?
		db      ?
	colors  dw      ?
	pixcol  dw      ?
	pixrow  dw      ?
	txtcol  dw      ?
	txtrow  dw      ?
VIOinfo ends

info    VIOinfo <0,0,14,1,0,0,2,0,0,80,25>

.code

public _VIOopen, _VIOclose, _VIOcolumns, _VIOrows, _VIOmode

_VIOheight proc

	mov al, xhite;
	xor ah,ah;
	ret

_VIOheight endp

odos4:  mov ax,440ch
	mov bx,0
	mov cx,037fh
	mov dx,offset info
	int 21h
	jnc l1
	pop ds
	ret

cga:    mov info.txtrow,25

	mov ax,[bp+8]
	mov bx,[bp+12]

_VIOsetCols endp

end
