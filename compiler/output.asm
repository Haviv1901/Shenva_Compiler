
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

del_last_char PROC
	mov al, 8
	call writechar
	mov al, 0
	call writechar
	mov al, 8
	call writechar
	ret
del_last_char ENDP



get_char_func PROC
	mov cl, 0
	read_chars_here:
	call readChar
	cmp al, 0Dh
	jz finish_get_char_function
	mov bl, al
	cmp cl, 0
	jnz write_aquired_char
	mov cl, 1
	call writechar
	write_aquired_char:
	call del_last_char
	mov al, bl
	call writechar
	jmp read_chars_here
	
	finish_get_char_function:
	mov al, 10
	call writechar
	cmp cl, 1
	jnz close_get_char_function
	mov al, bl
	close_get_char_function:
	mov ah, 0
	ret
get_char_func  ENDP



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




push 119
pop eax
call WriteChar
push 104
pop eax
call WriteChar
push 97
pop eax
call WriteChar
push 116
pop eax
call WriteChar
push 32
pop eax
call WriteChar
push 121
pop eax
call WriteChar
push 101
pop eax
call WriteChar
push 97
pop eax
call WriteChar
push 114
pop eax
call WriteChar
push 32
pop eax
call WriteChar
push 119
pop eax
call WriteChar
push 101
pop eax
call WriteChar
push 114
pop eax
call WriteChar
push 101
pop eax
call WriteChar
push 32
pop eax
call WriteChar
push 121
pop eax
call WriteChar
push 111
pop eax
call WriteChar
push 117
pop eax
call WriteChar
push 32
pop eax
call WriteChar
push 98
pop eax
call WriteChar
push 111
pop eax
call WriteChar
push 114
pop eax
call WriteChar
push 110
pop eax
call WriteChar
push 58
pop eax
call WriteChar
push 32
pop eax
call WriteChar
call readInt
push eax
push [ebp - 4]
fild dword ptr [esp]
fstp dword ptr [esp]
push 0
fild dword ptr [esp]
fstp dword ptr [esp]
pop ebx
pop eax
xor edx, edx
cmp eax, ebx
jng label_1
mov edx, 1
label_1:
mov eax, edx
push eax
pop eax
cmp eax, 0
je label_2
push 85
pop eax
call WriteChar
push 114
pop eax
call WriteChar
push 32
pop eax
call WriteChar
push 97
pop eax
call WriteChar
push 103
pop eax
call WriteChar
push 101
pop eax
call WriteChar
push 32
pop eax
call WriteChar
push 105
pop eax
call WriteChar
push 115
pop eax
call WriteChar
push 58
pop eax
call WriteChar
push 32
pop eax
call WriteChar
push [ebp - 8]
call print_number_signed
add esp, 4
label_2:
push [ebp - 4]
fild dword ptr [esp]
fstp dword ptr [esp]
push 0
fild dword ptr [esp]
fstp dword ptr [esp]
pop ebx
pop eax
xor edx, edx
cmp eax, ebx
jnl label_3
mov edx, 1
label_3:
mov eax, edx
push eax
pop eax
cmp eax, 0
je label_4
push 69
pop eax
call WriteChar
push 82
pop eax
call WriteChar
push 82
pop eax
call WriteChar
push 79
pop eax
call WriteChar
push 82
pop eax
call WriteChar
add esp, 4
label_4:

mov esp, ebp
pop ebp

invoke ExitProcess, 0
end main
