; A file name and a text (defined in the data segment) are given.
;The text contains lowercase letters, digits and spaces. 
;Replace all the digits with the character ‘X’. 
;Create the file with the given name and write the generated text to file.

bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "ana.txt", 0   
    access_mode db "w", 0      
                               
    file_descriptor dd -1       
    text db "Ana are 2 mere.", 0  
    len equ $-text
    varianta_finala db 0

; our code starts here
segment code use32 class=code
    start:
        mov ecx, len
        mov esi, text
        mov edi, varianta_finala
        verifica:
            lodsb ; ajunge in al
            cmp al, "0"
            jb nu_convine
            cmp al, "9"
            ja nu_convine
            mov al, "X"
            nu_convine:
                stosb
        loop verifica
    
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2   

        mov [file_descriptor], eax  ; store the file descriptor returned by fopen
        
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final

        ; write the text to file using fprintf()
        ; fprintf(file_descriptor, text)
        push dword varianta_finala
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*2

        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

      final:

        ; exit(0)
        push dword 0      
        call [exit]   