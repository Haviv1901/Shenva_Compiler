
include \masm32\include\irvine\Irvine32.inc
includelib \masm32\include\irvine\Irvine32.lib
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib


.code


ConvertFloatToInt PROC
    sub esp, 4          ; Reserve space for the local variable
	mov dword ptr[esp], eax
    fld DWORD PTR [esp]  ; Store the floating-point value from EAX onto the stack


    fistp DWORD PTR [esp] ; Store the integer part back to the stack as a DWORD
    pop eax        ; Move the integer part from memory to EAX register

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




push 1085276160
pop eax
push eax
push 1074580685
pop eax
push eax
push [ebp - 4]
push [ebp - 8]
push 10
push 1056964608
pop ebx
pop eax
push eax
fild dword ptr[esp]
pop eax
push ebx
fld dword ptr[esp]
pop ebx
fadd
push 0
fstp dword ptr[esp]
pop eax
push eax
pop ebx
pop eax
push eax
fld dword ptr[esp]
pop eax
push ebx
fld dword ptr[esp]
pop ebx
fadd
push 0
fstp dword ptr[esp]
pop eax
push eax
pop ebx
pop eax
push eax
fld dword ptr[esp]
pop eax
push ebx
fld dword ptr[esp]
pop ebx
fadd
push 0
fstp dword ptr[esp]
pop eax
push eax
pop eax
call ConvertFloatToInt
push eax
call print_number_signed

mov esp, ebp
pop ebp

invoke ExitProcess, 0
end main
