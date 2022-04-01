#include "game.h"

//NET IDs: austina5, akarshp2

//INTRODUCTION: This program was made to recreate the popular video game of 2048. This is a game where you use the a,s,w, and d keys to move each pointer right, down, up, or left. When moving the pointer if 2 of them have the same value in the same direction that you went, they will combine to be double the original value. The goal of the game is to get one of the blocks to have a total of 2048, but as you continue to combine the cells they will add to your score which is another measurement of achievement in the game. The program contains 8 different functions. These are the create_game,  remake_game, legal_move_check function, get_cell, move_a, move_s, move_w, and move_d. These each serve different purposes to make sure that the game functions properly. The create_game function returns a pointer to a game structure. The remake_game function works almost identically to the create_game function. The legal_move function checks if you can make the move without going off of the board. The move_ functions moves the pointer and adds the values of the boxes if they are identical. The legal_move_check function checks if the game board is filled up and there are no 2 identical pointers adjacent to each other.


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct

    (*mygame).rows = rows; //Initializes the rows of the game board
    (*mygame).cols = cols; //Initializes the cols of the game board
    (*mygame).score = 0; //Initializes the score of the game board

    for (int i = 0; i < (rows*cols); i++){ //Iterates through the entire game board and sets each cell to be equal to -1
      *((*mygame).cells + i) = -1;
    }
    
    return mygame; //Returns the initialized game board
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(**_cur_game_ptr).rows = new_rows; //Resets the game board with a new number of rows
        (**_cur_game_ptr).cols = new_cols; //Resets the game board with a new number of cols
        (**_cur_game_ptr).score = 0; //Resets the score of the game

        for (int i = 0; i < new_rows*new_cols; i++){ //Resets every cell of the game board to be equal to -1
	  *((**_cur_game_ptr).cells + i) = -1;
	}

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    int game_width = (*cur_game).cols; //Sets the horizontal size of the board
    int game_length = (*cur_game).rows; //Sets the vertical size of the board
    int index = row*game_width + col; //Position of the cell

    if (row >= game_length || row < 0 || col >= game_width || col < 0){ //Checks whether the cell is within the bounds of the board
      return NULL;
    }

    return (*cur_game).cells + index; //Returns a pointer to the corresponding cell on the game board
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
  int valid_move = 0; //Checks if a move has been made
  int empty_pos = 0; //Position of an empty cell
  int empty_loc = 0; //Essentially a boolean that checks whether a cell is empty or not
  int last_combo; //Makes sure that the last combination is not equal to 1 less than the position of an empty cell
  for (int j = 0; j < (*cur_game).cols; j++){ //Iterates through the columns of the board

    last_combo = -1;

    for (int i = 0; i < (*cur_game).rows; i++){ //Iterates through the rows of the board
      
      if (*((*cur_game).cells + i*(*cur_game).cols+j) != -1){ //Looks for the first non-empty cell

	empty_loc = 0;
	
        for (empty_pos = 0; empty_pos < i; empty_pos++){ //Iterates through the start of the column to the position of the non-empty cell
	  
	  if (*((*cur_game).cells + empty_pos*(*cur_game).cols+j) == -1){ //Finds an empty cell from the start of the column to the position of the non-empty cell
	    empty_loc = 1;
	    break;
	  }
	}
        
        if (empty_loc == 1){ //If an empty cell has been found, then the non-empty cell with replace the empty cell. The non-empty cell will be changed to -1 after.

	  *((*cur_game).cells + empty_pos*(*cur_game).cols+j) = *((*cur_game).cells + i*(*cur_game).cols+j);
          *((*cur_game).cells + i*(*cur_game).cols+j) = -1;
          valid_move = 1;

	}

	if (last_combo != (empty_pos-1)){

	  if (*((*cur_game).cells + empty_pos*(*cur_game).cols+j) == *((*cur_game).cells + (empty_pos-1)*(*cur_game).cols + j)){ 
            //Checks if the non-empty cell is equal to the one above it

	    *((*cur_game).cells + (empty_pos-1)*(*cur_game).cols+j) *= 2; //Adds both of the cells together and replaces its value
            (*cur_game).score += *((*cur_game).cells + (empty_pos-1)*(*cur_game).cols+j); //Adds the sum to the total score
            *((*cur_game).cells + empty_pos*(*cur_game).cols+j) = -1; //Resets the non-empty cell to be equal to 0
            last_combo = empty_pos-1;
            valid_move = 1;
	  }
	}
      }
    }
  }   

    return valid_move;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    //See the move_w function to understand the movement algorithm.
    int valid_move = 0;
    int empty_pos = 0;
    int last_combo;
    int empty_loc;
  for (int j = 0; j < (*cur_game).cols; j++){

    last_combo = -1;

    for (int i = (*cur_game).rows-1; i >= 0; i--){
      
      if (*((*cur_game).cells + i*(*cur_game).cols+j) != -1){

	empty_loc = 0;
	
        for (empty_pos = (*cur_game).rows-1; empty_pos > i; empty_pos--){
	  
	  if (*((*cur_game).cells + empty_pos*(*cur_game).cols+j) == -1){
	    empty_loc = 1;
	    break;
	  }
	}
        
        if (empty_loc == 1){

	  *((*cur_game).cells + empty_pos*(*cur_game).cols+j) = *((*cur_game).cells + i*(*cur_game).cols+j);
          *((*cur_game).cells + i*(*cur_game).cols+j) = -1;
          valid_move = 1;

	}

	if (last_combo != (empty_pos+1)){

	  if (*((*cur_game).cells + empty_pos*(*cur_game).cols+j) == *((*cur_game).cells + (empty_pos+1)*(*cur_game).cols + j)){

	    *((*cur_game).cells + (empty_pos+1)*(*cur_game).cols+j) *= 2;
            (*cur_game).score += *((*cur_game).cells + (empty_pos+1)*(*cur_game).cols+j);
            *((*cur_game).cells + empty_pos*(*cur_game).cols+j) = -1;
            last_combo = empty_pos+1;
            valid_move = 1;
	  }
	}
      }
    }
  }   

  return valid_move;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    //See the move_w function to understand the movement algorithm
    int valid_move = 0;
    int last_combo = 0;
    int empty_pos = 0;
  for (int i = 0; i < (*cur_game).rows; i++){

    last_combo = -1;

    for (int j = 0; j < (*cur_game).cols; j++){
      
      if (*((*cur_game).cells + i*(*cur_game).cols+j) != -1){

	int empty_loc = 0;
	
        for (empty_pos = 0; empty_pos < j; empty_pos++){
	  
	  if (*((*cur_game).cells + i*(*cur_game).cols+empty_pos) == -1){

	    empty_loc = 1;
	    break;

	  }
	}
        
        if (empty_loc == 1){

	  *((*cur_game).cells + i*(*cur_game).cols+empty_pos) = *((*cur_game).cells + i*(*cur_game).cols+j);
          *((*cur_game).cells + i*(*cur_game).cols+j) = -1;
          valid_move = 1;

	}

	if (last_combo != (empty_pos-1)){

	  if (*((*cur_game).cells + i*(*cur_game).cols+empty_pos) == *((*cur_game).cells + i*(*cur_game).cols + (empty_pos-1))){

	    *((*cur_game).cells + i*(*cur_game).cols+(empty_pos-1)) *= 2;
            (*cur_game).score += *((*cur_game).cells + i*(*cur_game).cols+(empty_pos-1));
            *((*cur_game).cells + i*(*cur_game).cols+empty_pos) = -1;
            last_combo = empty_pos-1;
            valid_move = 1;
	  }
	}
      }
    }
  }   

    return valid_move;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    //See the move_s algorithm to understand the movement algorithm.
    int valid_move = 0;
    int empty_pos = 0;
    int last_combo = 0;
    int empty_loc = 0;
  for (int i = 0; i < (*cur_game).rows; i++){

    last_combo = -1;

    for (int j = (*cur_game).cols-1; j >= 0; j--){
      
      if (*((*cur_game).cells + i*(*cur_game).cols+j) != -1){

	empty_loc = 0;
	
        for (empty_pos = (*cur_game).cols-1; empty_pos >= j; empty_pos--){
	  
	  if (*((*cur_game).cells + i*(*cur_game).cols+empty_pos) == -1){

	    empty_loc = 1;
	    break;

	  }
	}
        
        if (empty_loc == 1){

	  *((*cur_game).cells + i*(*cur_game).cols+empty_pos) = *((*cur_game).cells + i*(*cur_game).cols+j);
          *((*cur_game).cells + i*(*cur_game).cols+j) = -1;
          valid_move = 1;

	}

	if (last_combo != (empty_pos+1)){

	  if (*((*cur_game).cells + i*(*cur_game).cols+empty_pos) == *((*cur_game).cells + i*(*cur_game).cols + (empty_pos+1))){

	    *((*cur_game).cells + i*(*cur_game).cols+(empty_pos+1)) *= 2;
            (*cur_game).score += *((*cur_game).cells + i*(*cur_game).cols+(empty_pos+1));
            *((*cur_game).cells + i*(*cur_game).cols+empty_pos) = -1;
            last_combo = empty_pos+1;
            valid_move = 1;
	  }
	}
      }
    }
  }   

    return valid_move;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
  int row_size = (*cur_game).rows; //Size of rows
  int col_size = (*cur_game).cols; //Sizes of columns
  int my_cell; //Gets the value at a certain index on the board
  
  for (int i = 0; i < row_size; i++){
    for (int j = 0; j < col_size; j++){
      my_cell = *get_cell(cur_game, j, i);


      if (my_cell == -1){ //Checks if the cell is empty
	return 1;
      }

      cell* above = get_cell(cur_game, j-1, i); //Finds the value of the cell above the cell currently being checked
      cell* below = get_cell(cur_game, j+1, i); //Finds the value of the cell below the cell currently being checked
      cell* left = get_cell(cur_game, j, i-1); //Finds the value of the cell left of the cell currently being checked
      cell* right = get_cell(cur_game, j, i+1); //Finds the value of the cell right of the cell currently being checked

      //This next section checks whether the current cell being checked can be combined with the cells surrounding it.
      if (above != NULL && *above == my_cell){ 
	return 1;
      }
      if (below != NULL && *below == my_cell){
	return 1;
      }
      if (left != NULL && *left == my_cell){
	return 1;
      }
      if (right != NULL && *right == my_cell){
	return 1;
      }
    }
  }

    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
