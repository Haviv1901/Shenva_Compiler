
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
label_2:
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
jng label_4
mov edx, 1
label_4:
mov eax, edx
push eax
pop eax
cmp eax, 0
je label_3
push 10
push [ebp - -8]
pop ebx
pop eax
push eax
fild dword ptr[esp]
mov dword ptr [esp], ebx
fild dword ptr[esp]
fprem
fstp dword ptr[esp]
sub esp, 4
fstp dword ptr[esp]
add esp, 4
push 7
fild dword ptr [esp]
fstp dword ptr [esp]
pop ebx
pop eax
xor edx, edx
cmp eax, ebx
jne label_7
mov edx, 1
label_7:
mov eax, edx
push eax
pop eax
cmp eax, 0
je label_6
push 1
fild dword ptr [esp]
fstp dword ptr [esp]
pop eax
jmp label_1
jmp label_5
label_6:
label_5:
push [ebp - -8]
push 10
pop ebx
pop eax
push eax
fild dword ptr[esp]
mov dword ptr [esp], ebx
fild dword ptr[esp]
fdiv
fstp dword ptr[esp]
call ConvertFloatToInt
pop eax
mov [ebp - -8], eax
jmp label_2
label_3:
push 0
fild dword ptr [esp]
fstp dword ptr [esp]
pop eax
jmp label_1
xor eax, eax
label_1:
mov esp, ebp
pop ebp
retn 4
function_0 ENDP
function_1 PROC
push ebp
mov ebp, esp
push 1
label_10:
push [ebp - 4]
fild dword ptr [esp]
fstp dword ptr [esp]
push [ebp - -8]
fild dword ptr [esp]
fstp dword ptr [esp]
pop ebx
pop eax
xor edx, edx
cmp eax, ebx
jg label_12
mov edx, 1
label_12:
mov eax, edx
push eax
pop eax
cmp eax, 0
je label_11
push 7
push [ebp - 4]
pop ebx
pop eax
push eax
fild dword ptr[esp]
mov dword ptr [esp], ebx
fild dword ptr[esp]
fprem
fstp dword ptr[esp]
sub esp, 4
fstp dword ptr[esp]
add esp, 4
push 0
fild dword ptr [esp]
fstp dword ptr [esp]
pop ebx
pop eax
xor edx, edx
cmp eax, ebx
jne label_15
mov edx, 1
label_15:
mov eax, edx
push eax
cmp dword ptr [esp], 1
je label_16
push [ebp - 4]
call function_0
push eax
push 1
fild dword ptr [esp]
fstp dword ptr [esp]
pop ebx
pop eax
xor edx, edx
cmp eax, ebx
jne label_16
mov edx, 1
label_16:
mov eax, edx
push eax
pop eax
mov dword ptr [esp], eax
label_17:
pop eax
cmp eax, 0
je label_14
push 66
pop eax
call WriteChar
push 79
pop eax
call WriteChar
push 79
pop eax
call WriteChar
push 77
pop eax
call WriteChar
jmp label_13
label_14:
push [ebp - 4]
call print_number_signed
label_13:
push 10
pop eax
call WriteChar
push [ebp - 4]
push 1
pop ebx
pop eax
push eax
fild dword ptr[esp]
mov dword ptr [esp], ebx
fild dword ptr[esp]
fadd
fstp dword ptr[esp]
call ConvertFloatToInt
pop eax
mov [ebp - 4], eax
jmp label_10
label_11:
xor eax, eax
label_9:
mov esp, ebp
pop ebp
retn 4
function_1 ENDP
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
call readInt
push eax
call function_1
push eax
pop eax
call readInt
push eax
call function_1
push eax
pop eax
call readInt
push eax
call function_1
push eax
pop eax
label_0:

mov esp, ebp
pop ebp

invoke ExitProcess, 0
end main
