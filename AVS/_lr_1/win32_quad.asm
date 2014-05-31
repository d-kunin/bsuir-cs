[bits 32]
;;; solve quadratic equation
;; ax^2+bx+c = 0
;; 
;; compile: build.dat
;;; 

;;; <EXTERN>
	global task1
	extern atof
	extern printf
	extern scanf
;;; </EXTERN>
	

;;; <MACRO>
%macro 	print 1
	push 	%1
	call 	printf
	add		esp, 4
%endmacro

%macro fprint 2
	push	dword[%2 + 4]
	push	dword[%2]
	push	%1
	call	printf
	add		esp, 12
%endmacro

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

;; read double from stdin
;; args 1 -- dq variable
%macro parse_double 1
	push	%1
	push	format_double
	call	scanf
	add		esp, 8
	cmp		eax, 1
	jne		parse_error
%endmacro

;; read double from string
;; args 1 -- string, 2 -- dq variable
%macro parse_double 2
	push	dword[%1]
	call	atof
	add		esp, 4
	fstp	qword[%2]
%endmacro
;;; </MACRO>

;;; <MAIN>
section .text
task1:
	;; check arguments count
check_args:
	mov		eax, dword[esp + 4]
	cmp		eax, 4
	jne		ask_args
	jmp		read_args

ask_args:
	print	msg_ask_args
	print	a_eq  
	parse_double	a
	print	b_eq
	parse_double	b
	print	c_eq
	parse_double	c
	jmp		do_work
	
read_args:
	;; read arguments from argc/args
	mov		esi, dword [esp + 8]
	parse_double	esi+4,  a
	parse_double 	esi+8, b
	parse_double	esi+12, c
	jmp				do_work	

do_work:
	fprint	eq_format, a, b, c
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
	fld		qword[b]
	fmul	st0, st0	; b^2
	fsub	st0, st1	; b^2 - 4ac
	fst		qword[d]
	fprint	d_eq, d
	;; check d >= 0
	fldz
	fcomip	st0, st1
	ja		negative_d

	;; calc x1
	fld		qword[d]
	fsqrt
	fld		qword[b]
	fchs
	fsub	st0, st1	; -b - sqrt(d)
	fld1
	fld1
	fadd
	fdiv
	fdiv	qword[a]
	fstp	qword[x1]
	;; cals x2
	fld		qword[d]
	fsqrt
	fld		qword[b]
	fchs
	fadd	st0, st1	; -b + sqrt(d)
	fld1
	fld1
	fadd
	fmul	qword[a]
	fdiv
	fstp	qword[x2]

	;; print result
	fprint	x1_eq, x1
	fprint	x2_eq, x2

	jmp	done

done:
	print	str_done
	ret
	
;; Errors
negative_d:
	print	msgNegativeD
	ret
	
parse_error:
	print msg_dpe
	ret
;;; </MAIN>

;;; <DATA>
section .data		
msgNegativeD:
	db	"Disriminant is less than 0. No solutions in R.", 0xA, 0
str_done:
	db	"Done!", 0xA, 0

eq_format:	db	"%f*x^2+%f*x+%f = 0", 0xA, 0
x1_eq:		db	"x1=%f", 0xA, 0
x2_eq:		db	"x2=%f", 0xA, 0
d_eq:		db	"D=%f",  0xA, 0

;; arguments prompt
a_eq:	db	"a=", 0
b_eq:	db	"b=", 0
c_eq:	db	"c=", 0
msg_ask_args:	db	"Enter equation coefficients", 0xA, 0
format_double: 	db 	"%lf", 0
msg_dpe: 		db	"Are you sure that was floating point value?", 0xA, 0
	
x1:	dq	0.0
x2:	dq	0.0
a:	dq	0.0
b:	dq	0.0
c:	dq	0.0
d:	dq	0.0
;;; </DATA>