[bits 32]
;; compile:
;; 1) linux: nasm -felf series_cos.asm && gcc -m32 -o runme series_cos.o
;; 2) windows: build.bat

;;; <EXTERN>
global task2
extern 	printf
extern 	scanf
extern 	atof
;;; </EXTERN>

;;; <MACRO>
%macro clear_fpu 0
	fstp	st0
%endmacro

%macro fpu_top 0
	fst		qword [tmp_f]
	push	dword [tmp_f + 4]
	push 	dword [tmp_f]
	push 	format_fpu
	call	printf
	add	esp, 12
%endmacro

%macro print 	1
	push %1
	call printf
	add esp, 4
%endmacro

%macro parse_double 1
	push	%1
	push	format_double
	call	scanf
	add		esp, 8
	cmp		eax, 1
	jne		parse_error
%endmacro

;;; <MAIN>
section .text
task2:
	;; check arguments
check_args:
	mov	eax, dword[esp + 4]
	cmp	eax, 5
	je	read_args
	jmp ask_args
	
;; argument from main(argc, argv)
;; <argc/args>
read_args:	
	mov	esi, dword [esp + 8]
	push	dword [esi + 4]
	call	atof
	add	esp, 4
	fstp	qword [a]	; a

	push	dword [esi + 8]
	call	atof
	add	esp, 4
	fstp	qword [b]	; b

	push	dword [esi + 12]
	call	atof
	add	esp, 4
	fstp	qword [h]	; h
	
	push	dword [esi + 16]
	call	atof
	add	esp, 4
	fstp	qword [prs]	; epsilon
;; </argc/args>

;; <scanf>
ask_args:
	print msg_input
	print msg_a
	parse_double a
	print msg_b
	parse_double b
	print msg_h
	parse_double h
	print msg_eps
	parse_double prs
	jmp		do_work
;;</scanf>

do_work:	
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
	fld1
	fstp	qword [sum]	; sum = 1
	mov		dword [n], 0 	; n = 1
	;; ! reset vars
loop_n:	
	;; increment n while is not precise
	fld	qword [x]
	fcos 			; cosX st0
	fld	qword [sum]
	fsub			; sum - cosX st0
	fabs			; abs(sum - cosX) st0
	fld	qword [prs]	; prs st0
	fcomip
	clear_fpu
	ja	print_row	; if (prs > abs) { print_result }
	
	;; inc n
	add	dword [n], 1
	
	;; <calc xi>
	;; top
	fld1
	fchs			; -1 st0
	fld	qword [xi]
	fld	qword [x]
	fld	qword [x]
	fmul
	fmul
	fmul			; -1*xi*x*x st0
	;; bottom
	fild	dword [n]
	fld1
	fld1
	fadd
	fmul			; 2*n
	fild	dword [n]
	fld1
	fld1
	fadd
	fmul			; 2*n
	fld1
	fsub			; 2*n - 1
	fmul			; 2n*(2n-1) st0
	;; div
	fdiv			; -1*xi*x*x/(2n*(2n-1))
	fstp	qword [xi]

	;; update sum
	fld		qword [xi]
	fld		qword [sum]
	fadd
	fstp	qword [sum]	
	jmp	loop_n

print_row:	
	;; number of iters = n + 1
	add	dword [n], 1

	;; print result here	
	push 	dword[n]
	push 	dword[x + 4]
	push 	dword[x]
	push	format_row
	call	printf
	add	esp, 16
	
;;; end loop_n

	;; inc x
	fld	qword [x]
	fld	qword [h]
	fadd
	fstp	qword[x]
	jmp 	loop_x
;;; end loop_x

done:
	ret
	
parse_error:
	print msg_dpe
	ret

;;; <DATA>
section .data
format_d:	db		"%d", 0xA, 0
format_f:	db		"%f", 0xA, 0
format_fpu:	db		"st0=%f", 0xA, 0
format_row:	db		"[x=%f, n=%d]", 0xA, 0
;; for input reads
msg_input:  db		"Enter a,b,h and epsilon", 0xA, 0
msg_dpe: 	db		"Are you sure that was floating point value?", 0xA, 0
msg_a: 		db		"a=", 0
msg_b:		db		"b=", 0
msg_h:		db		"h=", 0
msg_eps:	db		"eps=", 0
format_double: db 	"%lf", 0

;; vars for problem
x:		dq	0.0
a:		dq	0.0
b:		dq	0.0
h:		dq	0.0
n:		dd	0
prs:	dq	0.00000001
;;; 

xi:			dq	0.0
sum:		dq	0.0
tmp_f:		dq	0.0
;; </DATA>