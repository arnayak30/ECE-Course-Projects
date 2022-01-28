;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

; partners: austina5, akarshp2

; INTRODUCTION
; The purpose of this program is to look at a string of characters and display how many instances
; of each alphanumeric character (letters A-Z and numbers 1-9) are present.
; The process starts by looking at the histogram data and simply checking what characters are respresented and
; printing it to the monitor in an organized format. The histogram data is in hexidecimal notation and
; needs to be divided into groups of four bits in order to see what ASCII character should be displayed.
; Once all ASCII characters are checked for their occurrences in the given string, the program will be halted.

PRINT_HIST

; Table of Registers
; R0 will hold the value that is going to be printed to the monitor.
; R1 holds the value of the next ASCII character to be printed.
; R2 is the data that is found in the histogram address list (referenced in the explanation for R7)
; R3 tells the user how many characters have been checked and printed to the screen.
; R4 is a digit counter
; R5 is a bit counter
; R6 stores the start of the histogram data addresses
; R7 stores the value of one of the groups of four digits from the histogram data.


INIT 			LD R3, NUM_BINS		; This section initiaizes values for R3, R1, and R6, which are registers that control 
                LD R1, AT_CHAR      ; what and how many characters gets printed to the monitor.		
				LD R6, HIST_ADDR	

NUM_PRINT		ADD R3, R3, #0		; This section checks whether every alphanumeric character has been accounted for and also, ensures that the
				BRz DONE			; formatting of what is being printed is correct.
				ADD R0, R1, #0		 
				OUT				
				LD R0, SPACE_CHAR	
				OUT					
				LDR R2, R6, #0		
				LD R4, DIGITS		
	
OUTERLOOP		ADD R4, R4, #0		; This section is responsible for checking whether all of the digits of the value in the histogram address
				BRz NEXT			; have accounted for before moving onto the next memory location.
				LD R5, DIGITS		
				AND R7, R7, #0		

INNERLOOP		ADD R5, R5, #0		; This section checks whether the data (in groups of 4) being passed is negative or positive.
				BRz PRINT_CHAR		; Once it does this, either '1' or '0' will be added to the digits register. Once all four digits in the group are checked and 
				ADD R7, R7, R7		; added over, the program will then move on to the PRINT_CHAR section of the code.
				ADD R2, R2, #0		
				BRzp #1				
				ADD R7, R7, #1		
				ADD R2, R2, R2		
				ADD R5, R5, #-1		
				BRnzp INNERLOOP 		
	
PRINT_CHAR		ADD R0, R7, #-9		; This section determines what ASCII character is being represented by the four digits in the data. 				
				BRnz #2				; If the decimal value of the binary data is less than or equal to 9, then #48 will be added to the data 
				LD R0, SUBTEN_CHAR	; because all such values represent the ASCII codes for numbers 0 through 9.
				BRnzp #1			
				LD R0, ZERO_CHAR	
				ADD R0, R7, R0		
				OUT					
				ADD R4, R4, #-1		
				BRnzp OUTERLOOP 		

NEXT			LD R0, ASCII_LINE	; This section makes sure that the program prints to the next line after one 	
				OUT					; specific alphanumeric character has been checked and printed.
				ADD R3, R3, #-1		
				ADD R1, R1, #1		
				ADD R6, R6, #1		
				BRnzp NUM_PRINT		


DONE			HALT				; This section ensures that the program will stop running after all characters have been checked and printed to the screen.





; the data needed by the program
NUM_BINS		.FILL #27	; 27 loop iterations
NEG_AT			.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z		.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ		.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR		.FILL x3F00 ; histogram starting address
STR_START		.FILL x4000	; string starting address
SUBTEN_CHAR		.FILL #55	; Needed to represent the ASCII values of letters "A-Z"
ZERO_CHAR		.FILL #48	; ASCII value for '0'
SPACE_CHAR  	.FILL x0020 ; ASCII for ' '
AT_CHAR			.FILL x0040 ; ASCII value for '@'
DIGITS			.FILL #4	; Tells us how many times the INNERLOOP should be run
ASCII_LINE    	.FILL x000A ; ASCII value for the next line



; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END;
