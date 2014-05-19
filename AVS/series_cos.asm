;;; calculate cos as series
;; S(x) = cos(x)
;; 
;; COMPILE:
;; nasm -felf64 series_cos.asm && gcc -o series_cos series_cos.o
;; RUN:
;; ./series_cos a b h eps
;;; 

;;; <MACRO>
;; simple string printing
%macro 	dprint 1 ; macro with one argument
	mov	rdi,  %1 ; %1 means first argument
	call 	puts
%endmacro
;; doulbe print : 1 arg
%macro fprint 2
	movq	xmm0, %2
	mov	rdi, %1
	mov	rax, 1
	call	printf
%endmacro
;; format, int, double print
%macro fprint 3
	movq	xmm0, %3
	mov		rsi, %2
	mov		rdi, %1
	mov	rax, 1
	sub		rsp, 8
	call	printf
	add		rsp, 8
%endmacro
;; double print: 4 args
%macro fprint 5
	movq	xmm0, %2
	movq	xmm1, %3
	movq	xmm2, %4
	movq	xmm3, %5
	mov	rdi, %1
	mov	rax, 4
	call	printf
%endmacro
;; read double from string
%macro dread 2
	mov	rdi, %1
	call	atof
	movq	%2, xmm0
%endmacro

;;; <MAIN>	
	global main
	extern atof
	extern puts
	extern printf
	
section .text
main:
	push	r12 ;; args
	push	r13 ;; current x
	push	r14 ;; is n
	push	r15 ;; is sum
	push	rcx ;; is cosx

	;; check arguments count
	cmp	rdi, 5
	jne	error_num_args

	mov 	r12, rsi
	;; read arguments
	dread	[r12+8],  [a]
	dread 	[r12+16], [b]
	dread	[r12+24], [h]
	dread	[r12+32], [eps]
	fprint	input_format, [a], [b], [h], [eps]

	;; prepare variables
	mov	r13, qword[a] ;; r13 -- is x

while_x_le_b:
	cmp		r13, qword[b] 
	jg		done
	;;
	 
	;; set sum to 1
	mov		qword[sum], 1
	mov 	r14, 1	;; r14  -- is n
	mov		r15, 1	;; r15  -- is xi
	
while_delta_le_eps: ;; for every n
	;; check precision here
	fld		qword[r13]
	fcos
	fld		qword[sum]
	fsub
	fabs
	fst		qword[rcx] ;; diff
	cmp		rcx, qword[eps]
	jl		print_res

	
	;; calc mult
	inc 	r14 		;; ++n
	fld		qword[r13]
	fmul	qword[r13]
	fchs
	fld		qword[two]
	fld		qword[r14]
	fmul
	fsub	qword[one]
	fld		qword[two]
	fld		qword[r14]
	fmul
	fmul
	;; store current mult
	fst		qword[mult] 

	;; update sum
	fld		qword[r15]
	fld		qword[mult] 
	fmul 				;; x_n=x_(n-1)*x_mult_n
	fadd	qword[sum]	;; sum+=xn
	fst		qword[sum]

	jmp		while_delta_le_eps

print_res:
	;; print x, n
	fprint		x_n_eq, r14, qword[r13]
	add		r13, [h]


error_num_args:
	dprint	badArgumentsCount
	jmp	done
	
done:
	dprint	str_done
	pop		r12
	pop		r13
	pop		r14
	pop		r14
	pop		rcx
	ret

;;; <DATA>
section .data		
	
badArgumentsCount:
        db      "Requires exactly four arguments: a b h eps", 0xA, 0
msgNegativeD:
	db	"Disriminant is less than 0. No solutions in R.", 0xA, 0
str_done:
	db	"Done!", 0xA, 0

input_format:	db	"a=%f b=%f h=%f eps=%f", 0xA, 0
x_n_eq:			db	"x=%f n=%d", 0xA, 0

a:		dq	0.0
b:		dq	0.0
h:		dq	0.0
mult:	dq	0.0
eps:	dq	0.0
two:	dq	2.0
one:	dq	1.0
sum:	dq	0.0
