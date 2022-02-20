#include <stdio.h>
#include <stdlib.h>

// NET IDs: austina5, akarshp2

// INTRODUCTION: This program prints the entries of Pascal's Triangle given
// the user's input for a specific row number. Row 0 serves as the starting
// row of Pascal's Triangle in this context.

int main()
{
  int row; // User input for row

  unsigned long i;

  unsigned long j;

  printf("Enter a row index: "); // Prompts user for row input

  scanf("%d",&row); // Stores user input in variable row

  // Write your code here
  for (i = 0; i < row+1; i++){ // Iterates through the number of rows.
     
    unsigned long start = 1; // Serves as starting num for Pascal's Triangle.

    for (j = 1; j < i+1; j++){ // Iterates through each number in the specified row.

      start = (((row + 1) - j) * start)/j; // Expression to calculate each number in the specified row.

    }

    printf("%lu ", start); // Prints each number in the row to the monitor.

  }

  printf("\n"); // Prints new line.

  return 0;

}
