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

void push(square board[NUM_ROWS][NUM_COLUMNS], int i, int j, struct token *top){    
    top->next = board[i][j].stack;
    board[i][j].stack = top;    
}

void pop(square board[NUM_ROWS][NUM_COLUMNS], int i, int j, struct token *top){ 
    struct token *temp = malloc(sizeof(struct token));
    temp = board[i][j].stack;
    board[i][j].stack = board[i][j].stack->next;
    free(temp);
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
    int minNumOfTokens = 0;
    int selectedSquare = 0;
    
    struct token *top = NULL;
    
    for (int k=0;k<9;k++)
    {
        for (int l=0;l<6;l++)
        {
            board[k][l].numTokens = 0;
        }
    }
    
    
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<numPlayers;j++)
        {
            printf("\nPlayer %d please select a square: ", j);
            scanf("%d", &selectedSquare);
            
            while (selectedSquare < 0 || selectedSquare > 5)
            {
                printf("Select a valid square: ");
                scanf("%d", &selectedSquare);
            }
            
            while (board[selectedSquare][0].numTokens != minNumOfTokens)
            {
                printf("Please select a valid square: ");
                scanf("%d", &selectedSquare);
            }
            
            if (board[selectedSquare][0].numTokens != 0)
            {
                while (board[selectedSquare][0].stack->col == players[j].col)
                {
                    printf("Please select a valid square: ");
                    scanf("%d", &selectedSquare);
                }
            }
            
            // pushing
            token *t = (token *) malloc(sizeof(token));
            t->col = players[j].col;
            t->next = NULL;
            push(board, selectedSquare, 0, t);
            board[selectedSquare][0].numTokens++;       
            
            //updates the minimum number of Tokens
            if (((numPlayers * i) + j + 1)%NUM_ROWS == 0)
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
    //used to control whos turn it is and what names are printed etc
    int playerTurn = 0;
    //holds the dice roll number
    int dice;
    //variable to check if they want to do the optional move
    int optionalMove;
    int rowOptional;
    int columnOptional;
    int upOrDown;
    
    struct token *top;
    
    int rowCheck, sum;
    
    int mandatoryColumn;
    int win=0;
    int a;
    
    srand(time(NULL));
    
    for (int z=0;z<numPlayers;z++)
    {
        players[z].numTokensLastCol = 0;
    }
    
    while (win == 0)
    {
        //we set playerTurn to 0 here so that we get a loop of turns e.g. 1->2->3->1->2->3->1... etc
        playerTurn = 0;
        
        while ((playerTurn < numPlayers) && (win == 0))
        {
            //setting optionalMove to 2 intially so that the while loop where the player chooses whether they want to do the optionalMove enters correctly, see below
            optionalMove = 2;
            
            printf("It is now %s's turn!\n\n", players[playerTurn].playerName);
            
            //PART A
            dice = rand()%6;
            sum = 0;
            for (rowCheck=0;rowCheck<8;rowCheck++)
            {
                sum += board[dice][rowCheck].numTokens;
            }
            
            while (sum == 0)
            {
                printf("\nSince there are no tokens left in row %d, the dice will be re re-rolled until a row which contains tokens is found!\n", dice);
                dice = rand()%6;
                
                for (rowCheck=0;rowCheck<8;rowCheck++)
                {
                    sum += board[dice][rowCheck].numTokens;
                }
            }
            printf("The dice was rolled, and you got the number (and row) %d!\n\n", dice);
            
            
            //PART B
            printf("Would you like to do the optional move? (Move one of your tokens 'sideways').\n");
            printf("1 for yes, 0 for no: ");
            scanf("%d", &optionalMove);
            //while loop will enter since optionalMove does not equal 1 or 0
            while (optionalMove != 0 && optionalMove != 1)
            {
                printf("\n(1 for yes, 0 for no): ");
                scanf("%d", &optionalMove);
            }
            
            if (optionalMove == 1)
            {
                printf("Please select which of your tokens you want to move up or down\n");
                printf("Row: ");
                scanf("%d", &rowOptional);
                printf("\nColumn: ");
                scanf("%d", &columnOptional);
                
                while (board[rowOptional][columnOptional].numTokens == 0)
                {
                    printf("\nSelect a valid row and column!\n");
                    printf("Row: ");
                    scanf("%d", &rowOptional);
                    printf("\nColumn: ");
                    scanf("%d", &columnOptional);
                }
                
                while (board[rowOptional][columnOptional].stack->col != players[playerTurn].col)
                {
                    printf("\nSelect a valid row and column!\n");
                    printf("Row: ");
                    scanf("%d", &rowOptional);
                    printf("\nColumn: ");
                    scanf("%d", &columnOptional);
                }
                
                if (rowOptional == 0)
                {
                    printf("This token can only be moved down. It will now be moved down for you!\n");
                    token *t = (token *) malloc(sizeof(token));
                    t->col = board[rowOptional][columnOptional].stack->col;
                    t->next = NULL;
                    push(board, rowOptional+1, columnOptional, t);
                    board[rowOptional+1][columnOptional].numTokens++;
            
                    pop(board, rowOptional, columnOptional, board[rowOptional][columnOptional].stack);
            
                    if (board[rowOptional][columnOptional].numTokens != 0)
                    {
                        board[rowOptional][columnOptional].numTokens--;
                    }
                }
                
                else if (rowOptional == 5)
                {
                    printf("This token can only be moved up. It will now be moved up for you!\n");
                    token *t = (token *) malloc(sizeof(token));
                    t->col = board[rowOptional][columnOptional].stack->col;
                    t->next = NULL;
                    push(board, rowOptional-1, columnOptional, t);
                    board[rowOptional-1][columnOptional].numTokens++;
            
                    pop(board, rowOptional, columnOptional, board[rowOptional][columnOptional].stack);
            
                    if (board[rowOptional][columnOptional].numTokens != 0)
                    {
                        board[rowOptional][columnOptional].numTokens--;
                    }
                }
                
                else
                {
                    printf("Press 1 to move this token UP one row, press 2 to move this token DOWN one row: ");
                    scanf("%d", &upOrDown);
                    
                    while ((upOrDown != 1) && (upOrDown != 2))
                    {
                        printf("Press 1 to move this token UP one row, press 2 to move this token DOWN one row: ");
                        scanf("%d", &upOrDown);
                    }
                    
                    if (upOrDown == 1)
                    {
                        token *t = (token *) malloc(sizeof(token));
                        t->col = board[rowOptional][columnOptional].stack->col;
                        t->next = NULL;
                        push(board, rowOptional-1, columnOptional, t);
                        board[rowOptional-1][columnOptional].numTokens++;
            
                        pop(board, rowOptional, columnOptional, board[rowOptional][columnOptional].stack);
            
                        if (board[rowOptional][columnOptional].numTokens != 0)
                        {
                            board[rowOptional][columnOptional].numTokens--;
                        }
                    }
                    
                    else if (upOrDown == 2)
                    {
                        token *t = (token *) malloc(sizeof(token));
                        t->col = board[rowOptional][columnOptional].stack->col;
                        t->next = NULL;
                        push(board, rowOptional+1, columnOptional, t);
                        board[rowOptional+1][columnOptional].numTokens++;
            
                        pop(board, rowOptional, columnOptional, board[rowOptional][columnOptional].stack);
            
                        if (board[rowOptional][columnOptional].numTokens != 0)
                        {
                            board[rowOptional][columnOptional].numTokens--;
                        }
                    }
                }
            }
            
            print_board(board);
            
            sum = 0;
            for (rowCheck=0;rowCheck<8;rowCheck++)
            {
                sum += board[dice][rowCheck].numTokens;
            }
            
            while (sum == 0)
            {
                printf("\nSince there are no tokens left in row %d, the dice will be re re-rolled until a row which contains tokens is found!\n", dice);
                dice = rand()%6;
                
                for (rowCheck=0;rowCheck<8;rowCheck++)
                {
                    sum += board[dice][rowCheck].numTokens;
                }
            }
            
            //PART C
            printf("\nNow you must select a column which has the token you want to move one space forward!\n");
            printf("(Remember, you rolled row %d on the dice!)\n", dice);
            
            printf("\nSelect the column you want: ");
            scanf("%d", &mandatoryColumn);
            
            while (board[dice][mandatoryColumn].numTokens == 0)
            {
                printf("\nSelect a valid column: ");
                scanf("%d", &mandatoryColumn);
            }
            
            while (mandatoryColumn < 0 || mandatoryColumn >= 9)
            {
                printf("\nSelect a valid column: ");
                scanf("%d", &mandatoryColumn);
            }
            
            printf("\nYou chose to move the token in position (%d, %d) one column forward!", dice, mandatoryColumn);
            //board[dice][mandatoryColumn+1].stack = (token *) malloc(sizeof(token));
            //board[dice][mandatoryColumn+1].stack->col = board[dice][mandatoryColumn].stack->col;
            token *t = (token *) malloc(sizeof(token));
            t->col = board[dice][mandatoryColumn].stack->col;
            t->next = NULL;
            push(board, dice, mandatoryColumn+1, t);
            board[dice][mandatoryColumn+1].numTokens++;
           
            pop(board, dice, mandatoryColumn, board[dice][mandatoryColumn].stack);
            if (board[dice][mandatoryColumn].numTokens != 0)
            {
                board[dice][mandatoryColumn].numTokens--;
            }
            
            
            if ((mandatoryColumn+1) == 8)
            {
                players[playerTurn].numTokensLastCol++;
            }
            
            
            
            
            //END OF TURN MISC
            playerTurn++;
            
            printf("\n\nHere is what the board currently looks like!\n\n");
            print_board(board);
            for (a=0;a<numPlayers;a++)
            {
                if (players[a].numTokensLastCol == 3)
                {
                    win = 1;
                    printf("Congratulations %s, you have Won the game!", players[a].playerName);
                }
            }
            
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
