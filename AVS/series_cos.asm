;; compile nasm -felf series_cos.asm && gcc -m32 -o runme series_cos.o

%macro clear_fpu 0
	fstp	st0
%endmacro
	
extern 	printf

section .test

global main

main:
	push	str
	call	printf
	add	esp, 4

	mov	ecx, d_d
	push 	dword [ecx]
	push 	format_d
	call	printf
	add	esp, 8


	push	dword [d_lf + 4]
	push 	dword [d_lf]
	push 	format_f
	call	printf
	add	esp, 12

	fld	dword [d_f]
	fstp	qword [some]
	
	push	dword [some + 4]
	push 	dword [some]
	push 	format_f
	call	printf
	add	esp, 12

	;; set up x
	fld	qword [a]
	fstp	qword [x]
loop_x:
	fld	qword [b]
	fld	qword [x]
	fcomip
	clear_fpu
	ja	done

	;; reset vars
	fld1
	fstp	qword [xi] 	; xi = 1
	fldz
	fstp	qword [sum]	; sum = 0
	mov	eax, 1
	mov	dword [n], eax 	; n = 1
	;; ! reset vars

	push	dword [x + 4]
	push	dword [x]
	push	format_f
	call	printf
	add	esp, 12		; print current x
	
loop_n:	
	;; increment n while does not precise
	fld	qword [x]
	fcos 			; cosX st0
	fld	qword [sum]
	fld	qword [xi]
	fadd			; sum + xi st0
	fsub			; sum - cosX st0
	fabs			; abs(sum - cosX) st0
	fld	qword [prs]	; prs st0
	fcomip
	clear_fpu
	ja	print_row	; if (prs > abs) { print_result }
	
	;; inc n
	add	dword [n], 1
	;; inc xi
	fld	dword [n]
	fld1
	fld1
	fadd
	fmul			; 2*n
	fld	dword [n]
	fld1
	fld1
	fadd
	fmul			; 2*n
	fld1
	fsub			; 2*n - 1
	fmul			; 2n*(2n-1) st0

	fld1
	fchs			; -1 st0
	fld	qword [xi]
	fld	qword [x]
	fld	qword [x]
	fmul
	fmul
	fmul			; -1*xi*x*x st0
	fdiv			; -1*xi*x*x/(2n*(2n-1))
	fstp	qword [xi]

	mov	ecx, n
	push	dword [ecx]
	push	format_d
	call	printf
	add	esp, 8
	
	jmp	loop_n

print_row:	
	;; print result here
	;; some printf [x, n]
	
;;; end loop_n

	;; inc x
	fld	qword [x]
	fld	qword [h]
	fadd
	fstp	qword[x]
	jmp 	loop_x
;;; end loop_x

greater:
	push	gt
	call	printf
	add	esp, 4

	fld	dword [d_f]
	fstp	qword [some]
	
	push	dword [some + 4]
	push 	dword [some]
	push 	format_f
	call	printf
	add	esp, 12


done:
	ret

section .data

str: 	db 		"Hello x86!", 0xA, 0
format_d:	db		"%d", 0xA, 0
format_f:	db		"%f", 0xA, 0
d_d:		dd		-4244
d_lf:		dq		-0.12342
d_f:		dd		-0.97 ; is less
h:			dd		0.1
some:		dq		0x1

gt: 	db	"Greater", 0xA, 0
ls:		db	"Less",	   0xA, 0

;; For problem
x:		dq	0.0
a:		dq	-1.0
b:		dq	1.0
n:		dd	0
prs:		dq	0.01

xi:		dq	1
sum:		dq	0
