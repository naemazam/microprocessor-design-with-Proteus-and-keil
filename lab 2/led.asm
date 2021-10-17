    
	 ORG    0000H
	 LJMP   MAIN
	 ORG    0003H
	 RETI 
	 ORG    000BH
	 RETI
	 ORG    0013H
	 RETI  
	 ORG    001BH
	 RETI
	 ORG    0023H
	 RETI
	 ORG    0030H
MAIN: MOV   A,#0FEH
LOOP: MOV   P1,A
      RL    A
      CALL DELAY
      LJMP LOOP
	  
DELAY: MOV R7,#10
D0:   MOV  R5,#250
D1:    MOV R6,#200
       DJNZ R6,$
	   DJNZ  R5,D1
	   DJNZ  R7,D0
	   RET   ;NAEM AZAM 
	   END    