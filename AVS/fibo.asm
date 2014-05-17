; -----------------------------------------------------------------------------
; A 64-bit Linux application that writes the first 90 Fibonacci numbers. To
; assemble and run:
;
;     nasm -felf64 fib.asm && gcc fib.o && ./a.out
; -----------------------------------------------------------------------------

	global main
	extern printf

	section .text
main:
	push	rdx

	mov	ecx, 90
	xor	rax, rax
	xor	rbx, rbx
	inc	rbx

print:
	push	rax
	push	rcx

	mov	rdi, format
	mov	rsi, rax
	xor	rax, rax

	call	printf

	pop	rcx
	pop	rax

	mov	rdx, rax
	mov	rax, rbx
	add	rbx, rdx
	dec	ecx
	jnz	print

	pop	rbx
	ret
format:
	db "%20ld", 10, 0
