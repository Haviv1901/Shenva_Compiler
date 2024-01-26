
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




function_0 PROC
push ebp
mov ebp, esp
label_1:
push [ebp - -8]
fild dword ptr [esp]
fstp dword ptr [esp]
push 0
fild dword ptr [esp]
fstp dword ptr [esp]
pop ebx
pop eax
xor edx, edx
cmp eax, ebx
jng label_3
mov edx, 1
label_3:
mov eax, edx
push eax
pop eax
cmp eax, 0
je label_2
xor eax, eax
mov al, byte ptr [ebp - -12]
push eax
pop eax
call WriteChar
push [ebp - -8]
push 1
pop ebx
pop eax
push eax
fild dword ptr[esp]
mov dword ptr [esp], ebx
fild dword ptr[esp]
fsub
fstp dword ptr[esp]
call ConvertFloatToInt
pop eax
mov [ebp - -8], eax
jmp label_1
label_2:
xor eax, eax
label_0:
mov esp, ebp
pop ebp
retn 5
function_0 ENDP
main:
push ebp
mov ebp, esp
mov esi, ebp
finit
sub esp, 2
fstcw word ptr[esp]
mov ax, [esp]
and ax, 0FCFFh
or ax, 00C00h
mov[esp], ax
fldcw word ptr[esp]
add esp, 2
push 3
push 97
pop eax
sub esp, 1
mov byte ptr [esp], al
push 10
call function_0
push eax
pop eax
push 98
pop eax
sub esp, 1
mov byte ptr [esp], al
push 10
call function_0
push eax
pop eax

mov esp, ebp
pop ebp

invoke ExitProcess, 0
end main
