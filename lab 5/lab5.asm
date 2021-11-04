             MOV DPTR, #0200H
                MOV P2,   #0FFH
REPEAT:         MOV P1,   #00H                    
                MOV P1,   #0EH        
                MOV A,    P2         
                CJNE A,   #0FH, PRESSED
                SJMP      REPEAT

KEYPRESSED:     ACALL     DELAY  
                MOV R0,   #00H                                  ; Assume key "0" pressed 
                MOV P1,   #0EH                                  ; checking for row P1.0
                MOV A,    P2                                    ; Read the columns 
                CJNE A,   #0FH, CHECK                           ; Identify the columns  

                MOV R0,   #04H                                  ; Assume key "4" pressed 
                MOV P1,   #0DH                                  ; checking for row P1.1
                MOV A,    P2                                    ; Read the columns 
                CJNE A,   #0FH, CHECK                           ; Identify the columns 

               MOV R0,   #08H                                   ; Assume key "8" pressed 
                MOV P1,   #0DH                                  ; checking for row P1.2
                MOV A,    P2                                    ; Read the columns 
                CJNE A,   #0FH, CHECK                           ; Identify the columns 

                MOV R0,   #0CH                                  ; Assume key "12" pressed 
                MOV P1,   #0DH                                  ; checking for row P1.3
                MOV A,    P2                                    ; Read the columns 
                CJNE A,   #0FH, CHECK                           ; Identify the columns 

DETECT:         RRC         A   
                JNC         GOT                                 
                INC         R0         
                SJMP        DETECT 

 GOT:            MOV A,     R0
                 MOVC A,    @+DPTR
                 MOV P0,    A
                 ACALL      DELAY      
                 SJMP       REPEAT