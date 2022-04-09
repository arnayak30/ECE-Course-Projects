#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

//NET IDs: austina5, akarshp2

//INTRODUCTION: This program focuses on navigating through a maze from the start point of “S” to the end point of “E” and avoiding  walls marked by “%”. The way we completed this MP was by utilizing four separate functions that each have different roles when making and solving the maze. These functions include createMaze, destroyMaze, printMaze, and solveMazeDFS. The first function createMaze allocates memory for maze_t and defines several variables for its struct. The second function destroyMaze is supposed to free the allocated memory that was designated for the maze. The third function printMaze prints the maze into the terminal. The fourth and final function solveMazeDFS uses a recursive algorithm in order to navigate up, down, right, and left through the maze around the walls from the start to the end to determine whether or not a solution path exists.

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
  int height; //Size of the maze's rows
  int width; //Size of the maze's columns
  char myCell; //Current cell being checked

  FILE *file = fopen(fileName, "r"); //Opens a file containing the maze structure
  
  fscanf(file, "%d", &height); //Stores the size of the maze's rows in a variable called height.
  fscanf(file, "%d", &width); //Stores the size of the maze's columns in a variable called width.
  fgetc(file); //Reads a single character from the maze file.

  maze_t *maze = malloc(sizeof(maze_t)); //Allocates memory for the maze.

  (*maze).height = height; //Sets struct values for the different aspects of the maze including height and width.
  (*maze).width  = width;
  (*maze).cells = (char**) malloc(height*sizeof(char*)); //Allocates memory for the maze's cells array.

  int i;
  
  for (i = 0; i < height; i++){ //Iterates through the maze's rows and allocates memory for every single one.
    (*maze).cells[i] = (char*) malloc(width*sizeof(char)); 
  }

  int x, y;

  for (x = 0; x < height; x++){ //Iterates through the maze's rows.
    for (y = 0; y < width + 1; y++){ //Iterates through the maze's columns.
      myCell = fgetc(file); //Gets a single character from the stream.

      if (myCell == 'S'){ //If the character is an 'S', then set the starting position of the maze.
	(*maze).startRow = x;
        (*maze).startColumn = y;
      }
      if (myCell == 'E'){ //If the character is an 'E', then set the end position of the maze.
	(*maze).endRow = x;
        (*maze).endColumn = y;
      }
      if (myCell == '\n'){ //If the character is a new line, then disregard it.
	continue;
      }
      
      (*maze).cells[x][y] = myCell; //Copies over the character from the file to the cells array for the maze.
    }
  }

  fclose(file);
  return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
  int a;
  for (a = 0; a < (*maze).height; a++){ //Iterates through the rows of the maze, and frees (clears) the memory for each one.
    free((*maze).cells[a]);
  }

  free((*maze).cells); //Frees all of the cell array's rows.
  free(maze); //Frees the rest of the struct that was defined for the file.
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
  int x, y;
  for (x = 0; x < (*maze).height; x++){ //Iterates through the maze's rows
    for (y = 0; y < (*maze).width; y++){ //Iterates through the maze's columns
      printf("%c", (*maze).cells[x][y]); //Prints the character at position x, y in the maze.
    }
    printf("\n"); //Prints a new line.
  }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
  char myCell = (*maze).cells[row][col]; //Current cell being checked
  
  //The following four conditions are the base cases that are provided in the MP9 document.
  if (row == (*maze).endRow && col == (*maze).endColumn){ return 1; } //Checks if the cell is at the end of the maze.
  if (row < 0 || row >= (*maze).height || col < 0 || col >= (*maze).width){ return 0; } //Checks if the current cell is within the bounds of the cell.
  if (myCell == '%' || myCell == '*' || myCell == '~'){ return 0; } //Checks if the current cell is not an empty cell.
  if (myCell != 'S'){ (*maze).cells[row][col] = '*'; } //Marks the current cell as part of the solution path as long as it isn't the starting cell of the maze.

  //The following four conditionals are the recursive cases that are provided in the MP9 document.
  
  if (solveMazeDFS(maze, col+1, row)){ return 1;} //Checks the cell that is right of current cell.
  if (solveMazeDFS(maze, col, row-1)){ return 1;} //Checks the cell that is above the current cell.
  if (solveMazeDFS(maze, col, row+1)){ return 1;} //Checks the cell that is below the current cell.
  if (solveMazeDFS(maze, col-1, row)){ return 1;} //Checks the cell that is left  of the current cell.
  
  if (myCell != 'S'){ (*maze).cells[row][col] = '~';} //Unmarks the current cell as part of the solution and marks it as being visited.

  return 0;
}
