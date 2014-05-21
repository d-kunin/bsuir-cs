;; compile nasm -felf series_cos.asm && gcc -m32 -o runme series_cos.o

extern 	printf

section .test

global main

main:
	push	str
	call	printf
	add		esp, 4

	mov		ecx, d_d
	push 	dword [ecx]
	push 	format_d
	call	printf
	add		esp, 8


	push	dword [d_lf + 4]
	push 	dword [d_lf]
	push 	format_f
	call	printf
	add		esp, 12

	fld		dword [d_f]
	fstp	qword [some]
	
	push	dword [some + 4]
	push 	dword [some]
	push 	format_f
	call	printf
	add		esp, 12

loop:
	fld		qword [d_lf]
	fld		dword [d_f]
	fcomip
	fstp 	st0
	ja	greater

	push	ls
	call 	printf
	add		esp, 4

	;; increment
	fld		dword [d_f]
	fld		dword [h]
	fadd
	fstp	dword[d_f]
	
	jmp 	loop

greater:
	push	gt
	call	printf
	add		esp, 4

	fld		dword [d_f]
	fstp	qword [some]
	
	push	dword [some + 4]
	push 	dword [some]
	push 	format_f
	call	printf
	add		esp, 12


done:
	ret

section .data

str: 	db 		"Hello x86!", 0xA, 0
format_d:	db		"%d", 0xA, 0
format_f:	db		"%f", 0xA, 0
d_d:		dd		-4244
d_lf:		dq		-0.12342
d_f:		dd		-0.97 ; is less
h:			dd		0.01
some:		dq		0x1

gt: 	db	"Greater", 0xA, 0
ls:		db	"Less",	   0xA, 0
