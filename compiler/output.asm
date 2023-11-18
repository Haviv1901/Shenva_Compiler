.386
.model flat, stdcall
option casemap :none

include \masm32\include\kernel32.inc
include \masm32\include\masm32.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\masm32.lib


.code
; Function to print a string from the stack
print_to_console proc
    push ebp
    mov ebp, esp
    pushad
    
    mov edx, [ebp + 8]
    invoke StdOut, edx
    
    popad
    mov esp, ebp
    pop ebp
    ret
print_to_console endp

print_string proc
push ebp
mov ebp, esp
pushad

mov ecx, 1
mov eax, 12
mov edx, [ebp + 8]
cmp edx, 0
jz stop_printing_char


print_char:
mov esi, ebp
add esi, eax
push [esi]
push esi
call print_to_console
pop edx
pop edx
add eax, 4
cmp [ebp + 8], ecx  ; Compare edx with the length of the string
jz stop_printing_char
inc ecx
jmp print_char

stop_printing_char:
popad
mov esp, ebp
pop ebp
ret
print_string endp





print_number_signed proc
push ebp
mov ebp, esp
pushad
mov esi, 0
mov edi, 10
mov ecx, 0
mov eax, [ebp + 8]
test eax, 10000000000000000000000000000000b
jz convert
imul eax, -1
mov esi, 1
inc ecx


convert:
mov edx, 0
cmp eax, edi
jl last_chars
idiv edi
add edx, 48
push edx
inc ecx

jmp convert 




last_chars:
mov edx, eax
add edx, 48
push edx
inc ecx
cmp esi, 1
jnz pushing_len
push '-'

pushing_len:
push ecx
call print_string


pop ecx
cmp ecx, 0
jz close_print_number_signed_function

clear_stack_from_number:
pop edx
dec ecx

cmp ecx, 0
jnz clear_stack_from_number


close_print_number_signed_function:
popad
mov esp, ebp
pop ebp
retn 4
print_number_signed endp








main:
push ebp
mov ebp, esp


mov esp, ebp
pop ebp

invoke ExitProcess, 0
end main
