
include \masm32\include\irvine\Irvine32.inc
includelib \masm32\include\irvine\Irvine32.lib
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib


.code


print_number_signed PROC
	
	push ebp
	mov ebp, esp
	pushad
	
	mov edx, [ebp + 8]
	test edx, 80000000h
	js print_negative
	
	call writeDec
	jmp finish_print_num_signed_function
	print_negative:
	call writeInt
	
	finish_print_num_signed_function:
	call Crlf
	popad
	mov esp, ebp
	pop ebp
	retn 4
print_number_signed  ENDP




main:
    push ebp
    mov ebp, esp

push 0
push 5
pop eax
mov [ebp - 4], eax
push [ebp - 4]
pop eax
push eax
call print_number_signed

mov esp, ebp
pop ebp

invoke ExitProcess, 0
end main
