%ifndef _MODUL_ASM_ ; continue if _FACTORIAL_ASM_ is undefined
%define _MODUL_ASM_ ; make sure that it is defined
                        ; otherwise, %include allows only one inclusion

;define the function
modul: ; int _stdcall factorial(int n)
    mov ecx, 0 
    mov ecx, [esp + 12]    ;lenght of a
    mov esi, [esp + 8]    ; a
    mov edi, [esp + 4]    ; sir_final
    repeta:
        lodsb
        stosb
    loop repeta
    ret 12
%endif