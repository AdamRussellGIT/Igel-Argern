#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    int counter = 0;
    int rowChoice;
    char colour;
    
    while (counter < numPlayers)
    {
        printf("%s:Which row (in the first column), would you like to place your first token?(Choose between 0 and 5 inclusive): ", players[counter].playerName);
        scanf("%d", &rowChoice);
        
        //prevents player from putting a token in a square where another token already lies
        while (board[rowChoice][0].stack != NULL)
        {
            printf("There is already a token there, choose another row now: ");
            scanf("%d", &rowChoice);
        }
        
        board[rowChoice][0].stack = &players[counter].col;
  
        counter++;
    }
    
    print_board(board);
    
    counter = 0;
    
    while (counter < numPlayers)
    {
        printf("%sWhich row (in the first column), would you like to place your second token?(Choose between 0 and 5 inclusive): ", players[counter].playerName);
        scanf("%d", &rowChoice);
        
        //prevents player from putting a token in a square where another token already lies
        /*while (board[rowChoice][0].stack != NULL)
        {
            printf("There is already a token there, choose another row now: ");
            scanf("%d", &rowChoice);
        }*/
        
        board[rowChoice][0].stack = &players[counter].col;
  
        counter++;
    }
    
    print_board(board);
}
        
    




/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    //used to control whos turn it is and what names are printed etc
    int playerTurn = 0;
    //holds the dice roll number
    int dice;
    //variable to check if they want to do the optional move
    int optionalMove;
    
    srand(time(NULL));
    
    while (/*check win*/)
    {
        //we set playerTurn to 0 here so that we get a loop of turns e.g. 1->2->3->1->2->3->1... etc
        playerTurn = 0;
        
        while (playerTurn < numPlayers)
        {
            //setting optionalMove to 2 intially so that the while loop where the player chooses whether they want to do the optionalMove enters correctly, see below
            optionalMove = 2;
            
            printf("It is now %s's turn!\n\n", players[playerTurn].playerName);
            
            //PART A
            dice = rand()%6;
            printf("The dice was rolled, and you got the number (and row) %d!\n\n", dice);
            
            
            //PART B
            printf("Would you like to do the optional move? (Move one of your tokens 'sideways').");
            //while loop will enter since optionalMove does not equal 1 or 0
            while (optionalMove != 0 && optionalMove != 1)
            {
                printf("\n(1 for yes, 0 for no): ");
                scanf("%d", &optionalMove);
            }
            
            if (optionalMove == 1)
            {
                //optionalMove code
            }
            
            
            
            //PART C
            printf("\nNow you must select a column which has the token you want to move one space forward!\n");
            printf("(Remember, you rolled row %d on the dice!)\n", dice);
            
            //mandatoryMove code
            
            
            
            //END OF TURN MISC
            printf("Here is what the board currently looks like!\n\n");
            print_board(board);
            
        }
        
        
        
    }
    
    
    
    
    
    
    
    //while(check for three of same colours in column 8, if yes print player with 3 colours as winner))
    
        //counter = 0 here
           
            //while(iterate through players counter < numPlayers)
            //{
                //PART A
                //dice role functionality
    
                //PART B
                //ask if want optional move
                //if they do
            
                    //do while: input for row and column
                    //CHECK OBSTACLE SQUARE TING
                       //catch for if top of stack of board[row][colum] is not their token
    
                     //allow them to select up or down motion
                        //if row 5 down or row 0 up, allow them,make them select token again
    
        
                //PART C
                //CHECK IF ROW HAS ANY TOKENS: ASK PASTRAMI
    
                //tell them the row they have
        
                //do while, until they pick a column that has tokens in it
                //CHECK OBSTACLE SQUARE TING
                    //move token at top of stack one column first
                    //colum that had token moved is set correctly?
    
        
            //print_board(board);
        //counter++;
        
    
    //}
}
