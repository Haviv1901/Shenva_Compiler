
include \masm32\include\irvine\Irvine32.inc
includelib \masm32\include\irvine\Irvine32.lib
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib


.code




ConvertFloatToInt PROC
    push ebp
    mov ebp, esp

    sub esp, 4          ; Reserve space for the local variable

    fstp DWORD PTR [ebp-4]  ; Store the floating-point value from EAX onto the stack

    mov eax, [ebp-4]        ; Move the floating-point value from memory to EAX register

    fistp DWORD PTR [ebp-4] ; Store the integer part back to the stack as a DWORD
    mov eax, [ebp-4]        ; Move the integer part from memory to EAX register

    leave
    ret
ConvertFloatToInt ENDP


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
	popad
	mov esp, ebp
	pop ebp
	retn 4
print_number_signed  ENDP




main:
    push ebp
    mov ebp, esp
	finit
	sub esp, 2
	fstcw word ptr[esp]
	mov ax, [esp]
	and ax, 0FCFFh         
	or ax, 00C00h
	mov [esp], ax
	fldcw word ptr [esp]
	add esp, 2




push 1078523330
push 5
pop ebx
pop eax

push eax
fld dword ptr[esp]
add esp, 4
push ebx
fild dword ptr[esp]
add esp, 4
fadd


call writeFloat




push 0
fstp dword ptr[esp]
pop eax
push eax
fld dword ptr [esp]
fistp dword ptr[esp]
pop eax
push eax
;call print_number_signed

;call dumpRegs


mov esp, ebp
pop ebp

invoke ExitProcess, 0
end main
