section .text

global main
extern printf

main:
	push dword [esp + 4] ;argc is located at esp+4
	push fmt1
	call printf
	add esp, 8

	mov eax, dword [esp+8]	;pointer to argv[0] is located at esp+8
	push dword [eax]		;argv[0] pointer
	push fmt2
	call printf
	add esp, 8
	
	mov eax, dword [esp+8] ;pointer to argv[0]
	mov edx, dword [eax]	;argv[0]
	push dword [edx]		;argv[0][0] or [edx+1] for next character
	push fmt3
	call printf
	add esp, 8
	
	mov eax, dword [esp+8]	;pointer to argv[0]
	push dword [eax+4]		;move to next pointer / argv[1]
	push fmt4
	call printf
	add esp, 8
	
	mov eax, 0
	ret
	

section .data
fmt1 db 'argc = %d', 10, 0
fmt2 db 'argv[0] =  %s', 10, 0
fmt3 db 'argv[0][0] = %c', 10, 0
fmt4 db 'argv[1] = %s', 10, 0
