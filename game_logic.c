#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>

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
    int k=0;
    int p=0;
    int tkn=1;
    
    
    while (counter < numPlayers*4)
    {
        if(k>=numPlayers)
        {
            k=0;
            tkn++;
        }
        if(counter>=numPlayers)
        {
            counter=0;
        }
        printf("%s:Which row (in the first column), would you like to place your token %d?(Choose between 0 and 5 inclusive): ", players[k].playerName,tkn);
        scanf("%d", &rowChoice);
       
        
        do
        {
            if(p<=5)
            {
                //prevents player from putting a token in a square where another token already lies while there are empty boxes
                while (board[rowChoice][0].stack != NULL)
                {
                    printf("\nCan't place a token on another one until all boxes are taken!, choose another row now: \n");
                    scanf("%d", &rowChoice);
                }
            }
            
            /*while(board[rowChoice][0].stack==players[k].col)//After all the rows in the first column have been filled , how do I prevent stacking on the same color and incorporate even stacking?
            {
                printf("Can't stack on your own color, choose another row: \n");
                scanf("%d",&rowChoice);
            }*/
            board[rowChoice][0].stack = &players[counter].col;
            p++;

        }while(board[0][0].stack==NULL&&board[1][0].stack==NULL&&board[2][0].stack==NULL&&board[3][0].stack==NULL&&board[4][0].stack==NULL&&board[5][0].stack==NULL);
        counter++;
        k++;
        print_board(board);
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
    
}
