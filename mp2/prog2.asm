.ORIG x3000

; NET IDS: austina5, akarshp2

; INTRODUCTION: This program serves as a five function calculator that can perform operations such as addition, subtraction, multiplication, division, and powers. This was created 
; utilizing a stack data structure, push and pop subroutines, and LC-3 instructions. The code starts by prompting the user to input numbers and operators. Every time a number
; 0-9 is entered, it will be pushed to the stack. When at least two numbers are entered, the program will pop two numbers from the stack and will perform an operation 
; on these inputs after an operator is pressed. Once the operation is completed, the result will be pushed onto the stack. Finally, when the equals sign is pressed, the program will
; pop the result from the stack and print the result onto the monitor in hexadecimal format. 

; The following code initializes all of the registers to be used later on in the program.
INIT              
           AND R0, R0, #0
           AND R1, R1, #0
           AND R2, R2, #0
           AND R3, R3, #0
           AND R4, R4, #0
           AND R5, R5, #0
           AND R6, R6, #0
           AND R7, R7, #0

; End Section.

; The following section of code takes the character input from the register and stores its ASCII Value in R0.

GET_INPUT
           AND         R0, R0, #0
           AND         R1, R1, #0
           AND         R3, R3, #0
           AND         R4, R4, #0
           AND         R7, R7, #0
           GETC
           OUT
           ADD         R1, R1, R0
           LD          R0, SPACE_CHAR
           OUT
           AND         R0, R0, #0
           ADD         R0, R1, #0
           AND         R1, R1, #0    
           BRnzp       FCHECK_INPUT

SPACE_CHAR       .FILL    x0020

; End Section.

; The following section will check if the character input from the keyboard is a valid input. Ensures that the ASCII Value of the Inputted Character is between x30 and x39.

FCHECK_INPUT
           BRnzp        CHECK_EQUALS
NEXT       ADD          R7, R7, #-6
           BRz          FINAL_CHECK
LAST       ADD          R0, R0, #-15
           ADD          R0, R0, #-15
           ADD          R0, R0, #-15
           ADD          R0, R0, #-13
           BRzp         FAILED
           BRnzp        SCHECK_INPUT

SCHECK_INPUT       
           ADD          R0, R0, #10       
           BRn          FAILED
           ADD          R6, R6, #1
           ADD          R0, R0, #15
           ADD          R0, R0, #15
           ADD          R0, R0, #15
           ADD          R0, R0, #3        
           BRnzp        PUSHTOSTACK

; End section.

; The following section checks whether the inputted value is an equals, plus, minus, multiply, divide, or power symbol. If it happens to be one of these, it'll branch to a new section of code
; that will perform the selected operation.

CHECK_EQUALS
           LD           R1, EQUALS_CHAR
           ADD          R1, R1, R0
           BRz          EVALUATE
           BRnzp        CHECK_PLUS

CHECK_PLUS
           LD           R4, ADDS
           LD           R1, PLUS_CHAR
           ADD          R1, R1, R0
           BRz          INCREMENT_OP
FNEXT      BRnzp        CHECK_SUB

CHECK_SUB
           LD           R4, SUBS
           LD           R1, MINUS_CHAR
           ADD          R1, R1, R0
           BRz          INCREMENT_OP
SNEXT      BRnzp        CHECK_MULT

CHECK_MULT
           LD           R4, MULS
           LD           R1, MULT_CHAR
           ADD          R1, R1, R0
           BRz          INCREMENT_OP
TNEXT      BRnzp        CHECK_DIV

CHECK_DIV
           LD           R4, DIV
           LD           R1, DIV_CHAR
           ADD          R1, R1, R0
           BRz          INCREMENT_OP
FONEXT     BRnzp        CHECK_POW

CHECK_POW
           LD           R4, POWS
           LD           R1, POW_CHAR
           ADD          R1, R1, R0
           BRz          INCREMENT_OP
           AND          R1, R1, #0
FINEXT     BRnzp        NEXT

; End Section.

; The following section keeps track of how many operators are being used in the equation. The number of operators in an equation has to be exactly one less than the number of operands.

ADDS             .FILL    x0001;
SUBS             .FILL    x0002;
MULS             .FILL    x0003;
DIVS             .FILL    x0004;
POWS             .FILL    x0005;
FAKE             .FILL    x0006;
           
INCREMENT_OP
           ADD          R2, R2, #1
           LD           R7, FAKE
           ADD          R4, R4, #-1
           BRz          FNEXT
           ADD          R4, R4, #1
           ADD          R4, R4, #-2
           BRz          SNEXT
           ADD          R4, R4, #2
           ADD          R4, R4, #-3
           BRz          TNEXT
           ADD          R4, R4, #3
           ADD          R4, R4, #-4
           BRz          FONEXT
           ADD          R4, R4, #4
           ADD          R4, R4, #-5
           BRz          FINEXT
           ADD          R4, R4, #5
           BRnzp        GET_INPUT

; End Section.

; The following section ensures that the number of operators is exactly one less than the number of operands. If the previous statement isn't true, the program will output "Invalid Expression".

NUMOP_COUNT
           ADD          R6, R6, #-2
           BRn          FAILED
           ADD          R6, R6, #2
           NOT          R2, R2
           ADD          R2, R2, #1
           AND          R7, R7, #0
           ADD          R7, R6, R2
           ADD          R7, R7, #-1
           BRp          FAILED
           BRnzp        RETURNS

; End Section.

; The following section determines what operator was selected and branches to a new section of code that performs its respective operation.

FINAL_CHECK
           LD           R7, PLUS_CHAR
           ADD          R7, R7, R0
           BRz          ADDX
           LD           R7, MINUS_CHAR
           ADD          R7, R7, R0
           BRz          SUBX
           LD           R7, MULT_CHAR
           ADD          R7, R7, R0
           BRz          MULTX
           LD           R7, DIV_CHAR
           ADD          R7, R7, R0
           BRz          DIVX
           LD           R7, POW_CHAR
           ADD          R7, R7, R0
           BRz          POWX
           BRnzp        GET_INPUT

; End Section.
           
PLUS_CHAR        .FILL    #-43;
MINUS_CHAR       .FILL    #-45;
MULT_CHAR        .FILL    #-42;
DIV_CHAR         .FILL    #-47;
POW_CHAR         .FILL    #-94;
EQUALS_CHAR      .FILL    #-61;

; The following section pushes the inputted number to the stack.

PUSHTOSTACK
           JSR          PUSH
           BRnzp        GET_INPUT

; End Section.

; The following section gets two operands from the stack, performs an operation on them using JSR, and then pushes the result to the stack.

ADDX
           AND          R3, R3, #0
           AND          R4, R4, #0
           AND          R7, R7, #0
           ADD          R7, R0, #0
           AND          R0, R0, #0
           JSR          POP
           ADD          R3, R0, #0
           AND          R0, R0, #0
           JSR          POP
           ADD          R4, R0, #0
           AND          R0, R0, #0
           ADD          R0, R7, #0
           JSR          PLUS
           BRnzp        LAST_STEP

SUBX
           AND          R3, R3, #0
           AND          R4, R4, #0
           AND          R7, R7, #0
           ADD          R7, R0, #0
           AND          R0, R0, #0
           JSR          POP
           ADD          R3, R0, #0
           AND          R0, R0, #0
           JSR          POP
           ADD          R4, R0, #0
           AND          R0, R0, #0
           ADD          R0, R7, #0
           JSR          MIN
           BRnzp        LAST_STEP

MULTX
           AND          R3, R3, #0
           AND          R4, R4, #0
           AND          R7, R7, #0
           ADD          R7, R0, #0
           AND          R0, R0, #0
           JSR          POP
           ADD          R3, R0, #0
           AND          R0, R0, #0
           JSR          POP
           ADD          R4, R0, #0
           AND          R0, R0, #0
           ADD          R0, R7, #0
           JSR          MUL
           BRnzp        LAST_STEP

DIVX
           AND          R3, R3, #0
           AND          R4, R4, #0
           AND          R7, R7, #0
           ADD          R7, R0, #0
           AND          R0, R0, #0
           JSR          POP
           ADD          R3, R0, #0
           AND          R0, R0, #0
           JSR          POP
           ADD          R4, R0, #0
           AND          R0, R0, #0
           ADD          R0, R7, #0
           JSR          DIV
           BRnzp        LAST_STEP

POWX
           AND          R3, R3, #0
           AND          R4, R4, #0
           AND          R7, R7, #0
           ADD          R7, R0, #0
           AND          R0, R0, #0
           JSR          POP
           ADD          R3, R0, #0
           AND          R0, R0, #0
           JSR          POP
           ADD          R4, R0, #0
           AND          R0, R0, #0
           ADD          R0, R7, #0
           JSR          EXP
           BRnzp        LAST_STEP

LAST_STEP
           AND          R7, R7, #0
           ADD          R7, R0, #0
           AND          R0, R0, #0
           ADD          R0, R0, R5
           JSR          PUSH
           AND          R0, R0, #0
           ADD          R0, R7, #0
           AND          R7, R7, #0
           BRnzp        GET_INPUT

; End Section

; The following section prints the string "Invalid Expression" to the monitor using the LEA instruction.

FAILED
           AND          R0, R0, #0
           LEA          R0, INVALID
           PUTS
           BRnzp        DONE

; End Section.


INVALID         .STRINGZ "Invalid Expression";

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R5- value to print in hexadecimal

; The following section prints the result that was stored in R5 onto the monitor. 

PRINT_HEX    AND R2, R2, #0;
   			 ADD R2, R2, R5;
   			 AND R4, R4, #0
   			 ADD R4, R4, #4
PRINTVALUE   AND R0, R0, #0
   			 ADD R3, R0, #4
FLEFTSHIFT   ADD R0, R0, R0
   			 ADD R2, R2, #0;
   			 BRzp SLEFTSHIFT
   			 ADD R0, R0, #1
SLEFTSHIFT   ADD R2, R2, R2;
   			 ADD R3, R3, #-1
   			 BRp FLEFTSHIFT
   			 ADD R0, R0, #-10
   			 BRn FIXNUM
   			 ADD R0, R0, #7
FIXNUM   	 LD  R1, END_CASE
   			 ADD R0, R0, R1
   			 OUT
   			 ADD R4, R4, #-1
   			 BRp PRINTVALUE
DONE         HALT

END_CASE     .FILL #58
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
; The following section branches to an above section that determines if the expression is valid or not and after, branches to a function that prints the result of the expression in hexadecimal format.
EVALUATE
       
            BRnzp      NUMOP_COUNT
RETURNS     AND        R0, R0, #0
            AND        R3, R3, #0
            AND        R5, R5, #0
            JSR        POP
            ADD        R5, R5, R0
            BRnzp      PRINT_HEX

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here

         ADD R5, R3, R4   	 ; adds R3 and R4 together and outputs them in R5
         RET   				 ; returns to line after JSR
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here

         NOT R4, R4   		 ; this inverses the value of R4
         ADD R4, R4, #1    	 ; this adds 1 to the inverse of R4 to negate it
   		 ADD R5, R3, R4   	 ; this adds the value of R3 and the negated value of R4
   		 RET   				 ; returns to line after JSR
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here

                     ADD R3, R3, #0   	 ; checks if R3 is 0
   			         BRz FINISH   		 ; branches to ZERO if R3 is 0
   			         ADD R4, R4, #0   	 ; checks if R4 is 0
   			         BRz FINISH   		 ; branches to ZERO if R4 is 0
   			         BRn NEGATEMUL   	 ; checks if R4 is negative   		 
   				 
     MULT   		 ADD R5, R5, R3   	 ; starts iterative addition
     			     ADD R4, R4, #-1     ; ensures that it uses R4 is used for the branch
     			     BRp MULT   		 ; restarts loop until R4 is 0
   			         RET

     NEGATEMUL   	 NOT R3, R3   		 ; starts negating R3
   			         ADD R3, R3, #1   	 ; finishes negating R3
   			 
   			 
     NEGATIVEMUL   	 ADD R5, R5, R3   	 ; starts iterative addition
     			     ADD R4, R4, #1      ; ensures that it uses R4 is used for the branch
     			     BRn NEGATIVEMUL   	 ; restarts loop until R4 is 0
   			         RET
     	 
     FINISH   		 AND R5, R5, #0   	 ; sets R5 to 0
   			         RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here

                         NOT R4, R4   	   ; nots R4
   		                 ADD R4, R4, #1    ; finishes negating R4


         DIVISION        ADD R3, R3, R4    ; subtract original value of R4 from R3 and stores it in R3   		 
   		                 BRn DIVSKIP   	   ; branches to DIVISKIP
   		                 ADD R5, R5, #1    ; adds 1 to the counter R5
   		                 BRz DIVSKIP
   		                 BRnzp DIVISION    ; branch back to start of loop

         DIVSKIP   	     RET
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here

                             ADD R7, R7, R3   	 ; sets R4 to R7
   			                 ADD R1, R1, R3   	 ; holds original value of R3
   			                 ADD R4, R4, #-1   	 ; lowers  multiplication counter
   			                 BRp MULTEXP   		 ; branches to MULTEXP

            EXPNEXT   		 ADD R3, R5, #0   	 ; holds the multiplicated value to R3
   			                 ADD R4, R4, #-1   	 ; lowers multiplication counter
   			                 BRz FINISHEXP   	 ; finishes code
   			                 ADD R7, R1, #-1   	 ; resets iterative addition counter
   			                 ADD R4, R4, #0   	 ;
   			                 BRp    MULTEXP      ; branches to MULTEXP
   			 


            MULTEXP   		 ADD R5, R5, R3   	 ; starts iterative addition
     			             ADD R7, R7, #-1     ; lowers iterative addition counter
   			                 BRz EXPNEXT
   			                 BRp MULTEXP   		 ; restarts loop until R4 is 0


            FINISHEXP   	 RET
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
