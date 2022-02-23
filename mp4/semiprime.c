#include <stdlib.h>
#include <stdio.h>

// Net IDs: austina5, akarshp2

// INTRODUCTION: Error Analysis

// First Error: Occurs in the is_prime function and deals with the return statements.
// This error causes all prime numbers to be recognized as composite numbers and vice versa.

// Second Error: Occurs in the print_semiprimes function and has to do with always counting the lower bound as a semiprime number.
// Since the lower bound is not always a semiprime number, this error causes an incorrect output to be produced.

// Third Error: Occurs in the print_semiprimes function and deals with determining whether a factor of a number in the inputted range is prime or not.
// This error is caused by checking if the remainder of a number divided by its factor is prime rather than checking if its quotient is prime.
// If this error were to be kept uncorrected, then the program would again produce an inaccurate output.

// Fourth Error: Occurs in the print_semiprimes function and has to do with printing a number multiple times after already determining that it is semiprime.
// If this error was not fixed, then every semiprime number might be printed to the monitor more than once. 

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
              if (i/j == 1){
		  continue;
	      }else{
		  if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
                        break;
                    }
                  }
              }
            }
        }

    }
    printf("\n");
    return ret;

}
