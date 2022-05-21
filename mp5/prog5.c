/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

//NET IDs: austina5, akarshp2

//INTRODUCTION: This program is essentially a game whether the user is given 12 attempts to guess a four digit solution pseudo-randomly generated by the computer. After the user
//makes his or her guess, the program outputs how many perfect matches (guess number is the same position as the solution number) and how many misplaced matches (guess number is
//in the solution set, but is not the correct position) the user has. Our task for this MP was to set the seed value for the srand() function, generate the solution_set for the game,
//and finally, determine how many perfect and misplaced matches the user had. Other information on how this program was created is specified in the various functions below.
#include <stdio.h>
#include <stdlib.h>
#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;
int seed;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]){

//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
      char post[2];
//    The sscanf statement below reads the integer into seed. 
      int check = sscanf(seed_str, "%d%1s", &seed, post);
      if (check == 1){
        srand(seed);
	return 1;

      }else{
        printf("set_seed: invalid seed\n");
        return 0;
      }
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
  solution1 = (rand() % 8 )+ 1; //The following four lines of code generate random numbers between 1-8 using the rand() function.
  solution2 = (rand() % 8) + 1;
  solution3 = (rand() % 8) + 1;
  solution4 = (rand() % 8) + 1;
  // printf("%d %d %d %d", solution1, solution2, solution3, solution4);
  guess_number = 1; //initializes guess_number to 1
  *one = solution1; //The following four lines of code set the pointers specified in the parameters equal to their respective solution values.
  *two = solution2;
  *three = solution3;
  *four = solution4;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two, int* three, int* four){
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

    char post[2];
    int w, x, y, z;
    int test = sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post); //Checks whether the user's input is only four integers and nothing else.
    if (test == 4){

        *one = w; //The following four lines of code set the pointers specified in the parameters of this function to the user's guess.
        *two = x;
        *three = y;
        *four = z;
        
        if((w >= 1 && w <= 8) && (x >= 1 && x <= 8) && (y >= 1 && y <= 8) && (z >= 1 && z <= 8)){ //Conditional statement that determines whethers the user's guess consists of
	                                                                                          //only integers between 1 through 8.
	    int misplaced_count = 0; //Initializes the number of misplaced guesses to 0.
            int perfect_count = 0; //Initializes the number of perfect guesses to 0.
            int paired[4] = {0, 0, 0, 0}; //Initializes the number of paired guesses and solutions to 0 in an integer array.
            int solution_set[4] = {solution1, solution2, solution3, solution4}; //Initializes an integer array of the solution.
        
      	    if(w == solution1){perfect_count++; paired[0] = 1;} //The following four lines of code check if the user's guess contains any perfect matches and sets the respective
            if(x == solution2){perfect_count++; paired[1] = 1;} //paired values equal to 1 if there is a perfect match.
            if(y == solution3){perfect_count++; paired[2] = 1;}
            if(z == solution4){perfect_count++; paired[3] = 1;}

            //The four conditional statements below follow the algorithm for misplaced matches specified in the provided MP5 document.
            if(paired[0] == 0){
	      for (int i = 0; i < 4; i++){
		if ((solution_set[i] == *one) && (paired[i] == 0)){
		  misplaced_count++;
                  paired[i] = 1;
                  break;
                }
	      }
	    }

            if(paired[1] == 0){
	      for (int i = 0; i < 4; i++){
		if ((solution_set[i] == *two) && (paired[i] == 0)){
		  misplaced_count++;
                  paired[i] = 1;
                  break;
                }
	      }
	    }

            if(paired[2] == 0){
	      for (int i = 0; i < 4; i++){
		if ((solution_set[i] == *three) && (paired[i] == 0)){
		  misplaced_count++;
                  paired[i] = 1;
                  break;
                }
    
	      }
	    }

            if(paired[3] == 0){
	      for (int i = 0; i < 4; i++){
		if ((solution_set[i] == *four) && (paired[i] == 0)){
		  misplaced_count++;
                  paired[i] = 1;
                  break;
                }
	      }
	    }

        
            printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_count, misplaced_count); 
            //The above line prints how many perfect and misplaced matches the user got to the monitor.
            guess_number++; //Increments the guess that the user is on.
            return 1;
        }
        else{
          
	    printf("make_guess: invalid guess\n"); //Prints invalid guess to the monitor if the user's guess does not contain values between 1 and 8.
            return 0;

        }
    }else{

        printf("make_guess: invalid guess\n"); //Prints invalid guess to the monitor if the user's guess contains more than four integers.
        return 0;

    }

    return 0;
}

