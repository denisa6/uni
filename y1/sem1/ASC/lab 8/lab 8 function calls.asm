bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
                          
segment data use32 class=data
	a dd  0       ; in this variable we'll store the value read from the keyboard
    b dd  0
    ; char strings are of type byte
	amessage  db "a=", 0  ; char strings for C functions must terminate with 0(value, not char)
    bmessage db "b=", 0
    divide db "/", 0
	aformat  db "%d", 0  ; %d <=> a decimal number (base 10)
    bformat db "%d", 0
    equal_result db " = %d"
segment code use32 class=code

;6) Two natural numbers a and b (a: dword, b: dword, defined in the data segment) are given. 
;Calculate a/b and display the quotient in the following format: "<a>/<b> = <quotient>". 
;Example: for a = 200, b = 5 it will display: "200/5 = 40".

    start:
       
        push dword amessage 
        call [printf]      ; call function printf for printing
        add esp, 4*1       ; free parameters on the stack; 4 = size of dword; 1 = number of parameters
                     
        ; we get a                     
        push dword a  
        push dword aformat
        call [scanf]    
        add esp, 4 * 2  
                           
        push dword bmessage 
        call [printf]   
        add esp, 4*1
              
        ; we get b              
        push dword b       
        push dword bformat
        call [scanf]       
        add esp, 4 * 2 

        ; this part prints a/b
        push dword [a]
        push dword aformat
        call[printf]
        add esp, 4 * 2
        push dword divide
        call[printf]
        add esp, 4*1
        push dword [b]
        push dword bformat
        call[printf]
        add esp, 4 * 2

        ; we find the result of the division
        mov eax, [a]
        cdq
        mov ebx, [b]
        div ebx
        
        ; we print the result 
        push dword eax
        push dword equal_result
        call[printf]
        add esp, 4*2
        
        mov al, -2
mov bl, -128
imul al
Rezultatul este:
The result is:
        
        
        ; exit(0)
        push dword 0      ; place on stack parameter for exit
        call [exit]       ; call exit to terminate the program