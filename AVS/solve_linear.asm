	;; solver linear equation in for
	;; ax - b = 0

;;; <MACRO>
;; simple string printing
%macro 	dprint 1 ; macro with one argument
	push	rdi
	mov	rdi,  %1 ; %1 means first argument
	call 	puts
	pop	rdi
%endmacro
;; doulbe printing
%macro fprint 2
	movq	xmm0, %2
	mov	rdi, %1
	mov	rax, 1
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
	push	r12
	push	r13
	push	r14
	
	;; prepared registers

	;; check arguments
	cmp	rdi, 3
	jne	error_num_args

	mov 	r12, rsi
	;; read arguments
	;; read 'a'
	dread	[r12+8], xmm1 
	;; todo if 0?
	fprint	a_eq, xmm1


	;; read 'b'
	dread [r12+16], xmm2
	fprint	b_eq, xmm0

	jmp	done


error_num_args:
	dprint	badArgumentsCount
	jmp	done

done:
	dprint	str_done
	pop	r14
	pop	r13
	pop	r12
	ret
		
badArgumentsCount:
        db      "Requires exactly two arguments", 10, 0

test1:
	db	"read first", 0xA, 0
test2:
	db	"read second", 0xA, 0
str_done:
	db	"done",	0xA, 0

a_eq:
	db	"a=%f", 0xA, 0
b_eq:
	db	"b=%f", 0xA, 0
