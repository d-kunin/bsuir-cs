; ----------------------------------------------------------------------------------------
; Writes "Hola, mundo" to the console using a C library. Runs on Linux or any other system
; that does not use underscores for symbols in its C library. To assemble and run:
;
;     nasm -felf64 hola.asm && gcc hola.o && ./a.out
; ----------------------------------------------------------------------------------------
	global main
	extern puts

	section .text
main:
	mov     rdi, message
	call    puts
	ret
message:
	db "Holla-holla!", 0
