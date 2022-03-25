#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

//NET IDs: austina5, akarshp2

//INTRODUCTION: This program solves a Sudoku puzzle by using recursive backtracking. A standard Sudoku puzzle contains
//81 cells, which are in a 9x9 grid, which is divided into 9 3x3 zones. Each cell on the board may contain a number from 1
//to 9 and each number can only occur once in every 3x3 zone, row, and column of the board. At the start of the puzzle,
//several cells will have numbers, while others will be empty or in other words, contain the number 0. The goal is to fill
//in those empty cells with numeric entries that satisfy the rules of Sudoku. For this MP, we had to create three functions
//that have very different purposes. The first function determines if a certain val exists in certain row of the board. The
//second function determines if a certain val exists in a certain column of the board. The third function checks whether a
//certain val exists in a certain zone of the board. The fourth function determines whether a certain val is valid entry on
//the board. The fifth and final function is responsible for completely solving the Sudoku puzzle using a recursive
//backtracking algorithm that was provided for us.



// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for (int c = 0; c < 9; c++){ //Iterates through the columns of the board.
    if (val == sudoku[i][c]){ //Checks if the input val is equal to a value in a
      return 1;               //cell in the input row of the board.
    }
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  
  for (int r = 0; r < 9; r++){ //Iterates through the rows of the board.
    if (val == sudoku[r][j]){ //Checks if the input val is equal to a value in a
      return 1;               //cell in the input col of the board.
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int row = int(i/3)*3; //Finds the top leftmost row of the 3x3 zone that
                        //the inputted cell is in.
  int col = int(j/3)*3; //Finds the top leftmost col of the 3x3 zone that
                        //the inputted cell is in.
  for (int x = row; x <= row+2; x++){ //Iterates through the rows of the board
    for (int y = col; y <= col+2; y++){ //Iterates through the cols of the board.
      if (val == sudoku[x][y]){ //Checks if the input val is equal to another cell
                                //in its respective 3x3 zone.
	  return 1;
	}
    }
  }
  
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if ((is_val_in_row(val, i, sudoku) == 1) || (is_val_in_col(val, j, sudoku) == 1) || (is_val_in_3x3_zone(val, i, j, sudoku) == 1)){ //Checks whether the input val exists in the input row, input col, or the respective 3x3 zone of the input cell.
        
    return 0;
  }

  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j; //Shown in pseudocode
  int counter = 0; //Initializes counter that checks whether all cells have been assigned by numbers.                 
  for (int x = 0; x < 9; x++){ //Iterates through the rows of the board.
    for (int y = 0; y < 9; y++){ //Iterates through the cols of the board.
      if (sudoku[x][y] == 0){ //If the cell is empty, then i and j will be set to the location of this empty cell.
	i = x;
	j = y;
        x = 9; //Breaks out of outer loop
        y = 9; //Breaks out of inner loop
      }
      else{
        counter++; //Increments the counter
      }
    }
  }

  if (counter == 81){ //Checks whether all cells have been assigned a value
    return 1;
  }
  
  for (int num = 1; num <= 9; num++){ //Iterates through the possible values for the cell.
    if (is_val_valid(num, i, j, sudoku) == 1){ //Checks if the input num is a valid entry for the cell.
      sudoku[i][j] = num; //Sets the cell val equal to the input num.
      if(solve_sudoku(sudoku) == 1){ //Checks if the sudoku board is complete or not.
	return 1;
      }
      sudoku[i][j] = 0; //Resets the cell entry.
    }
  }

  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





