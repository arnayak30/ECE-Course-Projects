
//NET IDs: austina5, akarshp2

//INTRODUCTION: This program essentially replicates the Game of Life, which is a cellular
//automaton that was devised by the British mathematician John Horton Conway in 1970. This
//game consists of a two-dimensional orthogonal grid of square cells, each of which can
//be classified as alive or dead. The program itself contains three functions: countLiveNeighbor,
//updateBoard, and aliveStable. The countLiveNeighbor function counts the number of living surrounding
//cells that a certain cell on the board has. The updateBoard function alters the current board to match
//the next generation of cells. Finally, the aliveStable function determines whether the board has changed
//from one generation to the next.

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

  int live_neighbors = 0; //Initializes a counter for the number of live neighbors
                          //a cell has.
  for (int i = row-1; i <= row+1; i++){ //Loops through the rows of the board

    if (i <= boardRowSize-1 && i >= 0){ //Checks whether the row of the cell is within the
                                        //bounds of the board.

      for (int j = col-1; j <= col+1; j++){ //Loops through the columns of the board

	if (j <= boardColSize-1 && j >= 0){ //Checks whether the col of the cell is within
                                            //the bounds of the board.

	  if (*(board + i*boardColSize + j) == 1){ //Checks if the cell is alive.   
                
	    live_neighbors++; //Increments counter for the number of live neighbors.
	  }
	}
      }
    }
  }
  live_neighbors-= *(board + row*boardColSize + col); //Subtracts the number of live neighbors by the value at the inputted cell location.
                                                      //This is to ensure that the number of live neighbors doesn't also account for the cell passed into this function.
  return live_neighbors; //Returns the number of live neighbors.
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {

  int nextGen[boardRowSize*boardColSize]; //Initializes an integer array that represents the next generation of cells.

  for (int i = 0; i < boardRowSize; i++){ //Loops through the board's rows.

    for (int j = 0; j < boardColSize; j++){ //Loops through the board's columns.

      nextGen[i*boardColSize + j] = *(board + i*boardColSize+j); //Sets the values in the array that was initialized above to match the current generations' cells.

    }
  }

  for (int i = 0; i < boardRowSize; i++){ //Loops through the board's rows.

    for (int j = 0; j < boardColSize; j++){ //Loops through the board's columns.

      int temp = countLiveNeighbor(board, boardRowSize, boardColSize, i, j); //Checks the number of live neighbors a specific cell has.

      if ((temp > 3) || (temp < 2)){ //If the number of live neighbors a cell has exceeds 3 or is less than 2, then the cell will die.
	nextGen[i*boardColSize + j] = 0;
      }
      if (temp == 3){ //If a dead cell has 3 live neighbors, then it will become alive.
	nextGen[i*boardColSize + j] = 1;
      }
    }
  }
  
  for (int i = 0; i < boardRowSize; i++){ //Loops through the board's rows.

    for (int j = 0; j < boardColSize; j++){ //Loops through the board's columns.

      *(board + i*boardColSize + j) = nextGen[i*boardColSize + j]; //Updates the game board to match the next generations' cells.
    }
  }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){

  int checkBoard[boardRowSize*boardColSize]; //START SECTION 1: This block of code essentially creates an integer array that contains the next generations' cells.
                                             //It is identical to some of the code found in updateBoard function seen above.

  for(int i = 0; i < boardRowSize; i++){
    for (int j = 0; j <boardColSize; j++){
      checkBoard[i*boardColSize + j] = *(board + i*boardColSize + j);
    }
  }

  for(int i = 0; i < boardRowSize; i++){
    for (int j = 0; j < boardColSize; j++){
      int temp = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);
      if (temp > 3 || temp < 2){
	checkBoard[i*boardColSize + j] = 0;
      }
      else if (temp == 3){
	checkBoard[i*boardColSize + j] = 1;
      }
    }
  }

  //END SECTION 1.
  
  for(int i = 0; i < boardRowSize; i++){ //Loops through the board's rows.

    for (int j = 0; j < boardColSize; j++){ //Loops through the board's columns.

      if (checkBoard[i*boardColSize + j] != *(board + i*boardColSize + j)){ //Checks whether the next generation's cells are the same as the current generation's cells.

	return 0;
      }
    }
  }
  
  return 1;
}

				
				
			

