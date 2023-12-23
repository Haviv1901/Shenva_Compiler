
include \masm32\include\irvine\Irvine32.inc
includelib \masm32\include\irvine\Irvine32.lib
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib


.code


ConvertFloatToInt PROC
    fld DWORD PTR [esp + 4]  ; Store the floating-point value from EAX onto the stack
    fistp DWORD PTR [esp + 4] ; Store the integer part back to the stack as a DWOR
    ret
ConvertFloatToInt ENDP


print_number_signed PROC
	
	push ebp
	mov ebp, esp
	pushad
	
	mov edx, [ebp + 8]
	mov eax, [ebp + 8]
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




push 97
pop eax
call WriteChar
push 10
pop eax
call WriteChar
push 15
push 10
push 1092878336
push -2
push -2
pop ebx
pop eax
push eax
fild dword ptr[esp]
mov dword ptr [esp], ebx
fild dword ptr[esp]
fmul
fstp dword ptr[esp]
pop ebx
pop eax
push eax
fld dword ptr[esp]
mov dword ptr [esp], ebx
fld dword ptr[esp]
fadd
fstp dword ptr[esp]
pop ebx
pop eax
push eax
fild dword ptr[esp]
mov dword ptr [esp], ebx
fld dword ptr[esp]
fadd
fstp dword ptr[esp]
pop ebx
pop eax
push eax
fild dword ptr[esp]
mov dword ptr [esp], ebx
fld dword ptr[esp]
fadd
fstp dword ptr[esp]
fld DWORD PTR [esp]
call WriteFloat
fstp dword ptr [esp]
pop eax

mov esp, ebp
pop ebp

invoke ExitProcess, 0
end main
