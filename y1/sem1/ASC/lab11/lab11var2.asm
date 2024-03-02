; Three strings (of characters) are read from the keyboard.
; Identify and display the result of their concatenation.
bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf           
import exit msvcrt.dll    
import printf msvcrt.dll
import scanf msvcrt.dll 
%include "modul.asm"

segment data use32 class=data
	a dd 0 
    b dd 0
    c dd 0
    alenght dd 0
    blenght dd 0
    clenght dd 0
	amessage db "first string = ", 0 
    bmessage db "second string = ", 0
    cmessage db "third string = ", 0
    lenght db "lenght = ", 0
    format  db "%s", 0
    lenght_format db "%d", 0
    sir_final db 0

segment code use32 class=code

    start:
        push dword amessage 
        call [printf]      
        add esp, 4*1            
        ; we get a                     
        push dword a  
        push dword format
        call [scanf]    
        add esp, 4 * 2
        ;we get the lenght of add
        push dword lenght
        call [printf]
        add esp, 4
        push dword alenght
        push dword lenght_format
        call [scanf]
        add esp, 8        
               
               
        push dword bmessage 
        call [printf]      
        add esp, 4*1        
        ; we get b                    
        push dword b 
        push dword format
        call [scanf]    
        add esp, 4 * 2
        ;we get the lenght of b
        push dword lenght
        call [printf]
        add esp, 4
        push dword blenght
        push dword lenght_format
        call [scanf]
        add esp, 8 
        
        
        push dword cmessage 
        call [printf]      
        add esp, 4*1        
        ; we get c                    
        push dword c 
        push dword format
        call [scanf]    
        add esp, 4 * 2
        ;we get the lenght of c
        push dword lenght
        call [printf]
        add esp, 4
        push dword clenght
        push dword lenght_format
        call [scanf]
        add esp, 8
        
        
        ;we add a to the final string
        mov edx, 0
        mov edx, sir_final
        push dword [alenght]
        push a
        push edx
        call modul
        
        ;we add b to the final string
        add edx, [alenght]
        push dword [blenght] 
        push b
        push edx
        call modul
        
        ;we add c to the final string
        add edx, [blenght]
        push dword [clenght]
        push c
        push edx
        call modul
        
        
        ;we print the final string
        push dword sir_final
        push dword format
        call [printf]
        add esp, 4*2

        push dword 0 
        call [exit]