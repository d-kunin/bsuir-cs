;;; solve quadratic equation
;; ax^2+bx+c = 0
;; 
;; COMPILE:
;; nasm -felf64 quad.asm && gcc -o quad quad.o
;; RUN:
;; quad 1 5 4
;;; 
	global _main
	extern _atof
	extern _puts
	extern _printf
	

;;; <MACRO>
;; simple string printing
%macro 	dprint 1 ; macro with one argument
	mov	rdi,  %1 ; %1 means first argument
	call 	_puts
%endmacro
;; doulbe print : 1 arg
%macro fprint 2
	movq	xmm0, %2
	mov	rdi, %1
	mov	rax, 1
	call	_printf
%endmacro
;; double print: 3 args
%macro fprint 4
	movq	xmm0, %2
	movq	xmm1, %3
	movq	xmm2, %4
	mov	rdi, %1
	mov	rax, 3
	call	_printf
%endmacro
;; read double from string
%macro dread 2
	mov	rdi, %1
	call	_atof
	movq	%2, xmm0
%endmacro

;;; <MAIN>
_main:
	push	r12

	;; check arguments count
	cmp	rdi, 4
	jne	error_num_args

	mov 	r12, rsi
	;; read arguments
	dread	[r12+8],  [a]
	dread 	[r12+16], [b]
	dread	[r12+24], [c]

	fprint	eq_format, [a], [b], [c]

	
	;; discriminant
	fld	qword[c]
	fmul	qword[a]
	fmul	qword[four]	; 4ac
	fld	qword[b]
	fmul	st0, st0	; b^2
	fsub	st0, st1	; b^2 - 4ac
	fst	qword[d]
	fprint	d_eq, [d]
	
	;; check d >= 0
	cmp 	qword[d], 0
	jl	negative_d

	;; calc x1
	fld	qword[d]
	fsqrt
	fld	qword[b]
	fchs
	fsub	st0, st1	; -b - sqrt(d)
	fdiv	qword[two]
	fdiv	qword[a]
	fst	qword[x1]
	;; cals x2
	fld	qword[d]
	fsqrt
	fld	qword[b]
	fchs
	fadd	st0, st1	; -b + sqrt(d)
	fdiv	qword[two]
	fdiv	qword[a]
	fst	qword[x2]

	;; print result
	fprint	x1_eq, [x1]
	fprint	x2_eq, [x2]

	jmp	done

error_num_args:
	dprint	badArgumentsCount
	jmp	done

negative_d:
	dprint	msgNegativeD
	jmp	done
	
done:
	dprint	str_done
	pop	r12
	ret

;;; <DATA>
section .data		
	
badArgumentsCount:
        db      "Requires exactly three arguments", 0xA, 0
msgNegativeD:
	db	"Disriminant is less than 0. No solutions in R.", 0xA, 0
str_done:
	db	"Done!", 0xA, 0

eq_format:	db	"%f*x^2+%f*x+%f = 0", 0xA, 0
x1_eq:		db	"x1=%f", 0xA, 0
x2_eq:		db	"x2=%f", 0xA, 0
d_eq:		db	"D=%f",  0xA, 0
	
x1:	dq	0.0
x2:	dq	0.0
a:	dq	0.0
b:	dq	0.0
c:	dq	0.0
d:	dq	0.0
four:	dq	4.0
two:	dq	2.0
