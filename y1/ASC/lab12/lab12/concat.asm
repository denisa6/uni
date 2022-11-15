bits 32
extern _readString
extern _printf
global _asmConcat

segment data public data use32

    lenRez                  dd        0
    resultStringAddress     dd        0
    paramStringAddress1     dd        0
    paramStringAddress2     dd        0
    paramStringAddress3     dd        0
    len_str1                dd        0
    len_str2                dd        0
    len_str3                dd        0
    
segment code public code use32
; int asmConcat(char[], int, char[], int, char[], int, char[])
_asmConcat:
    push ebp
    mov ebp, esp
    ; reserving space on the stack for local variables
    sub esp, 4 * 8
    ; [ebp + 32] result string adress
    ; [ebp + 28] lenght of string 3
    ; [ebp + 24] third string adress
    ; [ebp + 20] lenght of string 2
    ; [ebp + 16] second string adress
    ; [ebp + 12] lenght of string 1
    ; [ebp + 8] first string adress
	; [ebp+4] we have the return address (the value of EIP at the moment of the call)
    ; [ebp] we have the value of ebp for the caller
    
    
    mov eax, [ebp + 8]
    mov [paramStringAddress1], eax
    mov eax, [ebp + 12]
    mov [len_str1], eax
    
    mov eax, [ebp + 16]
    mov [paramStringAddress2], eax
    mov eax, [ebp + 20]
    mov [len_str2], eax
    
    mov eax, [ebp + 24]
    mov [paramStringAddress3], eax
    mov eax, [ebp + 28]
    mov [len_str3], eax
    
    mov eax, [ebp + 32]
    mov [resultStringAddress], eax
    
    
    ; concatenate the strings
    ; copy the string passed as parameter to the asmConcat function (string1) in the result string
    cld
    mov edi, [resultStringAddress]
    mov esi, [paramStringAddress1]
    mov ecx, [len_str1]
    rep movsb
    
    ; copy the second string
    mov esi, [paramStringAddress2]
    mov ecx, [len_str2]
    rep movsb
    
    ; copy the string read using the readString function in the result string
    mov esi, [paramStringAddress3]
    mov ecx, [len_str3]
    rep movsb

	add esp, 4 * 8
    ; restore the stack frame for the caller program
    mov esp, ebp
    pop ebp
    ret