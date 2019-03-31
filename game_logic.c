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
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
{
  //the min number of tokens placed on a square in the first column of the board
    int minNumOfTokens=0;
    int selectedSquare=0;
    
    for(int p=0;p<9;p++)
    {
        for(int k=0;k<6;k++)
        {
            board[p][k].numTokens=0;
        }
    }
    
    //Add a check for an invalid Row Selection

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<numPlayers;j++)
        {
                   printf("Player %d please select a square\n",j);
                   scanf("%d",&selectedSquare);

                while((board[selectedSquare][0].numTokens!=minNumOfTokens))
                {
                   printf("Player %d please select a square\n",j);
                   scanf("%d",&selectedSquare);
                }
                if(board[selectedSquare][0].numTokens!=0)
                {
                    while(board[selectedSquare][0].stack->col==players[j].col)
                    {
                        printf("Player %d please select a valid square\n",j);
                        scanf("%d",&selectedSquare);
                    }
                }
                
                
                board[selectedSquare][0].stack=(token*)malloc(sizeof(token));
                board[selectedSquare][0].stack->col=players[j].col;
                board[selectedSquare][0].numTokens++;
        

            //updates the minimum number of Tokens
            if(((numPlayers*i)+j+1)%NUM_ROWS==0)
            {
                minNumOfTokens++;
            }
            
            print_board(board);
        }
        
    }
    

}
        
    




/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    
    int optionMove=2;
    int tokenToMoveRow=2;
    int tokenToMoveColu=2;
    int upOrDown=2;
    
    int dice=0;
    
    srand(time(NULL));
    dice=rand()%6+1;
    
    
    
    //Add the catches for boundry conditions!
    //Add the option of choosing the row for the optional and mandatory move
    for(int c=0;c<numPlayers;c++)//c<4
    {
        for(int h=0;h<numPlayers;h++)
        {
            printf("Player %s\n",players[h].playerName);
            printf("Do you wish to Move one of your tokens up or down one row?\n(Press 1 for yes) and (Press 0 for no)\n");
            scanf("%d",&optionMove);
            
          if(optionMove==1)
          {
             
             printf("Please select one of your tokens you wish to move\n");
             
             printf("Please select the ROW of the token:\n");
             scanf("%d",&tokenToMoveRow);
             
             printf("Please select the COLUMN of the token:\n");
             scanf("%d",&tokenToMoveColu);
             
             while(board[tokenToMoveRow][tokenToMoveColu].stack->col!=players[h].col&&board[tokenToMoveRow][tokenToMoveColu].numTokens==0)
             {
               printf("Please select your own token and it's valid token position!\n");
             }
             
             printf("Do you wish to move it UP or DOWN?\n");
             printf("(Press 1 for UP) and (Press 0 for DOWN)\n");
             scanf("%d",&upOrDown);
             if(tokenToMoveRow==0)
             {
                 while(upOrDown!=1)
                 {
                     printf("You can only move DOWN\nPlease Select DOWN to continue\n");
                     scanf("%d",&upOrDown);
                 }
                 board[tokenToMoveRow+1][tokenToMoveColu].stack->col=players[h].col;
  
             }
             else if(tokenToMoveRow==5)
             {
                 while(upOrDown!=0)
                 {
                     printf("You can only move DOWN\nPlease Select DOWN to continue\n");
                     scanf("%d",&upOrDown);
                 }
                 board[tokenToMoveRow-1][tokenToMoveColu].stack->col=players[h].col;
             }
             else if(upOrDown==1)
             {
                 board[tokenToMoveRow-1][tokenToMoveColu].stack->col=players[h].col;
                 //Get rid of tokenToMove from the original position where it was
             }
             else if(upOrDown==0)
             {
                 board[tokenToMoveRow+1][tokenToMoveColu].stack->col=players[h].col;
                 //Get rid of tokenToMove from the original position where it was
             }
             print_board(board);
             
          }
          else if(optionMove==0) //Have a check here to make sure there is tokens in the row
          {
              printf("The row indicated by the Dice Roll is %d\n\n",dice);
              print_board(board);
              printf("Please choose one token (either yours or another player's)\nin the indicated ROW you wish to move forward one square\n");
              scanf("%d",&tokenToMoveColu);
              
              board[dice][tokenToMoveColu++].stack->col=board[dice][tokenToMoveColu].stack->col; //This does not appear to move the selected token as required; the board remains unchanged
              printf("Movement Right Test\n");
              print_board(board);
              tokenToMoveColu=0;
              
          }
             
        }
    }
   
    
        
    
    
    //PartA
    //check while if anyone has won
    //Check the same for three colors, print winner depending on the color they have chosen to comparing to the three chosen color
    //counter=0
    //while counter<numPlayers
    
    //Part B 
    //dice roll functionality
    //Ask if want option to move his own token 
    //Ask row and column
    //Ask up or down
    //Check for obstacle squares
    //Catch for out of bounds
    //Throw back to selection menu for the choosing desired token
    //if they don't give a valid response ask again
    
    //Part C
    //Check if any tokens in the row selected by dice (ASK THE DOC FOR RULES) re-roll if no tokens in row
    //Tell the dice roll row to the player
    //Do while Ask which column then want to make sure there is a token in it
    //Check for obstacles squares
    //Move token forward
    //Make sure the token that had the moved token has the correct token  
    
    
    
    
}

