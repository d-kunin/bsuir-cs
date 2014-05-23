;; compile nasm -felf series_cos.asm && gcc -m32 -o runme series_cos.o


;;; <MACRO>
%macro clear_fpu 0
	fstp	st0
%endmacro

%macro fpu_top 0
	fst	qword [tmp_f]
	push	dword [tmp_f + 4]
	push 	dword [tmp_f]
	push 	format_fpu
	call	printf
	add	esp, 12		; print temp mult
%endmacro

%macro log_d_var	2
	
	section .data
	.str:	db %1, 0
	
	section .text
	push	dword [%2 + 4]
	push 	dword [%2]
	push 	.str
	call	printf
	add	esp, 12		; print temp mult
	
%endmacro

%macro new_line 0
	section .data
	eol:	db "", 0xA, 0

	section .text
	push	eol
	call	printf
	add	esp, 4
%endmacro

;;; <EXTERN>
extern 	printf
extern 	atof
;;; 

;;; <MAIN>
section .text
global main
main:
	;; check arguments
check_args:
	mov	eax, dword[esp + 4]
	cmp	eax, 5
	je	read_args
error_args:
	push	msg_error
	call	printf
	add	esp, 4
	jmp	done
	;; arguments

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
	mov	dword [n], 0 	; n = 1
	;; ! reset vars

	;; log_d_var "x=%f", x
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
	fld	qword [xi]
	fld	qword [sum]
	fadd
	fstp	qword [sum]

	;; log_d_var	"sum=%f ", sum
	;; log_d_var	"xi=%f", xi
	;; new_line
	
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

;;; <DATA>
section .data

format_d:	db		"%d", 0xA, 0
format_f:	db		"%f", 0xA, 0
format_fpu:	db		"st0=%f", 0xA, 0
format_row:	db		"[x=%f, n=%d]", 0xA, 0
	
;; For problem
x:		dq	0.0
a:		dq	-3.15
b:		dq	3.15
h:		dq	0.1
n:		dd	0
prs:		dq	0.00000001
;;; 

xi:		dq	0.0
sum:		dq	0.0

tmp_d:		dd	0
tmp_f:		dq	0.0

msg_error:	db	"Needs exactly 4 arguments: a b h eps", 0xA, 0
