bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fread, fclose, fprintf, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "input.txt", 0   ; filename to be read
    access_mode db "r", 0       ; file access mode:
                                ; r - opens a file for reading. The file must exist.
    file_descriptor dd -1       ; variable to hold the file descriptor
    
    file_name2 db "ana.txt", 0
    access_mode2 db "w", 0       ; file2 access mode
    file_descriptor2 dd -1
    
    len equ 100                 ; maximum number of characters to read
    text times (len+1) db 0     ; string to hold the text which is read from file
    format db "%s", 0
    format2 db "%d", 0
    format3 db "%s", 0
    sir db 0

; our code starts here
segment code use32 class=code
    start:
        ; call fopen() to create the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        mov eax, 0
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor], eax  ; store the file descriptor returned by fopen

        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final

        ; read the text from file using fread()
        ; after the fread() call, EAX will contain the number of chars we've read 
        ; eax = fread(text, 1, len, file_descriptor)
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword text        
        call [fread]
        add esp, 4*4

        ; display the number of chars we've read and the text
        ; printf(format, eax, text)
        push dword text
        push dword format
        call [printf]
        add esp, 4*2

        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        
        mov esi, text
        mov edi, sir
        mov ebx, 0
        mov edx, 0
        mov ecx, 100
        verify:
            lodsb
            cmp al, ' '
            jne not_space
            add bx, 1
            add dx, 1
            not_space:
                    cmp edx, 0
                    jne not_first_word
                    stosb
                    not_first_word:
                        cmp al, '.'
                        jne not_dot
                        add bx, 1
                        mov edx, 0
                        not_dot:
                    
                
        loop verify
        
        push dword sir
        push format3
        call [printf]
        add esp, 8
        
        push dword ebx
        push format2
        call [printf]
        add esp, 8
        
        
        
        
        ;file 2 ******************
        mov eax, 0
        push dword access_mode2     
        push dword file_name2
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor2], eax  ; store the file descriptor returned by fopen
        
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final

        ; write the text to file using fprintf()
        ; fprintf(file_descriptor, text)
        
        push dword sir
        push dword [file_descriptor2]
        call [fprintf]
        add esp, 4*3
        
        ; push EBX
        ; push dword [file_descriptor2]
        ; call [fprintf]
        ; add esp, 4*3
        

        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor2]
        call [fclose]
        add esp, 4

      final:

        ; exit(0)
        push dword 0
        call [exit]