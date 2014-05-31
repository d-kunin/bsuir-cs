[bits 32]
;;; solve quadratic equation
;; ax^2+bx+c = 0
;; 
;; compile: build.dat
;;; 

;;; <EXTERN>
	global task1
	extern atof
	extern puts
	extern printf
	extern scanf
;;; </EXTERN>
	

;;; <MACRO>
;; simple string printing
%macro 	dprint 1 ; macro with one argument
	push 	%1
	call 	puts
	add		esp, 4
%endmacro
;; doulbe print : 1 arg
%macro fprint 2
	push	dword[%2 + 4]
	push	dword[%2]
	push	%1
	call	printf
	add		esp, 12
%endmacro
;; double print: 3 args
%macro fprint 4
	push	dword[%4 + 4]
	push	dword[%4]
	push	dword[%3 + 4]
	push	dword[%3]
	push	dword[%2 + 4]
	push	dword[%2]
	push	%1
	call	printf
	add		esp, 28
%endmacro

;; read double from string
%macro parse_double 2
	push	dword[%1]
	call	atof
	add		esp, 4
	fstp	qword[%2]
%endmacro

;;; <MAIN>
section .text
task1:
	;; check arguments count
check_args:
	mov	eax, dword[esp + 4]
	cmp	eax, 4
	jne	error_num_args

	;; read arguments from argc/args
	mov		esi, dword [esp + 8]
	parse_double	esi+4,  a
	parse_double 	esi+8, b
	parse_double	esi+12, c
	fprint			eq_format, a, b, c
	
	;; discriminant
	fld		qword[c]
	fmul	qword[a]
	fld1
	fld1
	fadd
	fld1
	fld1
	fadd
	fmul
	fmul
	fld	qword[b]
	fmul	st0, st0	; b^2
	fsub	st0, st1	; b^2 - 4ac
	fst		qword[d]
	fprint	d_eq, d
	;; check d >= 0
	fldz
	fcomip	st0, st1
	ja		negative_d

	;; calc x1
	fld	qword[d]
	fsqrt
	fld	qword[b]
	fchs
	fsub	st0, st1	; -b - sqrt(d)
	fld1
	fld1
	fadd
	fdiv
	fdiv	qword[a]
	fstp	qword[x1]
	;; cals x2
	fld	qword[d]
	fsqrt
	fld	qword[b]
	fchs
	fadd	st0, st1	; -b + sqrt(d)
	fld1
	fld1
	fadd
	fmul	qword[a]
	fdiv
	fstp		qword[x2]

	;; print result
	fprint	x1_eq, x1
	fprint	x2_eq, x2

	jmp	done

error_num_args:
	dprint	badArgumentsCount
	jmp	done

negative_d:
	dprint	msgNegativeD
	jmp	done
	
done:
	dprint	str_done
	ret
;;; </MAIN>

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
;;; </DATA>