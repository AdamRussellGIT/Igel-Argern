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

/*Function defenition for pushing the tokens on top of the stack*/
/*The arguments for the functions are the board, variables used for the row, column and dice of both the optional
 * and mandatory moves and pointer to the top token */
void push(square board[NUM_ROWS][NUM_COLUMNS], int i, int j, struct token *top){    
    top->next = board[i][j].stack; /*Assigning the stack to the next which is pointing to top*/
    board[i][j].stack = top;    /*Assigning top onto the stack*/ 
}

/*Function defenition for popping token elements from the stack*/
/*The arguments for the functions are the board, variables used for the row, column and dice of both the optional
 * and mandatory moves and pointer to the top token */
void pop(square board[NUM_ROWS][NUM_COLUMNS], int i, int j, struct token *top){ 
    struct token *temp = malloc(sizeof(struct token)); /*Allocating space for a temporary pointer to the token strut through malloc*/
    temp = board[i][j].stack; /*Assigning the the stack at a board position to the temporary variable*/
    board[i][j].stack = board[i][j].stack->next; /*Assigning the pointer next which points to the stack at a certain board position to the stack of a certain board position specified by i and j*/
    free(temp); /*Using the free function to free the variable that was temporarily stored in the temp variable*/
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

/*Function defenition for placing the tokens on the board */
/*The arguments that are included within the function are the board, the players array of type player,the variable for the number of players*/
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    int minNumOfTokens = 0; /*The minimum number of players variable*/
    int selectedSquare = 0; /*Selected Square variable*/
    
    struct token *top = NULL; /*Assigning the the pointer top to token to NULL */
    
    /*Iterating through the entire board (rows and columns)
     and assigning the number of tokens in each square to 0 in
     order to prevent any garbage values to cause possible errors*/
    for (int k=0;k<9;k++)
    {
        for (int l=0;l<6;l++)
        {
            board[l][k].numTokens = 0; /*Assigning all squares' number of tokens variable to zero*/
        }
    }
    
    
    /*Code block asking the users where the wish to place their tokens in order to set up the game*/
    for (int i=0;i<4;i++) /*Iterating 4 times as there is 4 tokens for eahc player*/
    {
        /*Iterating through each player asking them for their choice*/
        for (int j=0;j<numPlayers;j++)
        {
            printf("\nPlayer %d please select a square: ", j);
            scanf("%d", &selectedSquare);
            
            /*Keep asking the player to select a square within the bounds of the game*/
            while (selectedSquare < 0 || selectedSquare > 5)
            {
                printf("Select a valid square: ");
                scanf("%d", &selectedSquare);
            }
            
            /*While the number of tokens of a square selected by the user is not equal to the minimum number of tokens*/
            /*This prevents over-stacking when setting up the game which is one of the game conditions */
            while (board[selectedSquare][0].numTokens != minNumOfTokens)
            {
                printf("Please select a valid square: ");
                scanf("%d", &selectedSquare);
            }
            
            /*If the number of tokens of a square selected by the user is not equal to zero*/
            if (board[selectedSquare][0].numTokens != 0)
            {   /*While the color on top of the stack is equal to the current players color*/
                /*This is to prevent same color stacking*/
                while (board[selectedSquare][0].stack->col == players[j].col)
                {
                    printf("Please select a valid square: ");
                    scanf("%d", &selectedSquare);
                }
            }
            
            //Pushing
            token *t = (token *) malloc(sizeof(token)); /*Allocating space for a pointer t to token*/
            t->col = players[j].col; /*Assigning the current players color onto t which points to a color*/
            t->next = NULL; /*Assigning the t's pointer to next to NULL*/
            push(board, selectedSquare, 0, t); /*Calling the push function with the selected square, column 0 and row token*/
            board[selectedSquare][0].numTokens++; /*Incrementing the number of tokens on the selected square on column 0*/      
            
            //Updates the minimum number of Tokens
            if (((numPlayers * i) + j + 1)%NUM_ROWS == 0) /*If all the squares on the board have the same number of tokens
                                                           increment the minimum number of tokens*/
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
    //variable for the optional Row
    int rowOptional;
    //variable for the optional Column
    int columnOptional;
    //variable for either up or down
    int upOrDown;
    
    //pointer top to token 
    struct token *top;
    
    //variable for the row check, sum and obstacle check
    int rowCheck, sum, obstacleCheck;
    
    //variable for the mandatory column
    int mandatoryColumn;
    //Win variable used to confer if there has been a winner
    int win=0;
    //variable a is used for indexing for the last column on the board to check for the winning condition
    int a;
    
    srand(time(NULL)); //Seeding a random number
    
    /*Assigning the number of tokens for each square in the last column to 0 in order to prevent 
    garbage values from causing errors*/
    for (int z=0;z<numPlayers;z++)
    {
        players[z].numTokensLastCol = 0;
    }
    
    //Execute this code while the win=0; in other words until there is a winner 
    while (win == 0)
    {
        //we set playerTurn to 0 here so that we get a loop of turns e.g. 1->2->3->1->2->3->1... etc
        playerTurn = 0;
        
        while (playerTurn < numPlayers && win == 0)
        {
            //setting optionalMove to 2 intially so that the while loop where the player chooses whether they want to do the optionalMove enters correctly, see below
            optionalMove = 2;
            
            printf("It is your turn, %s\n", players[playerTurn].playerName);
            
            //PART A
            dice = rand()%6;
            
            //sum is set to 0 initially
            sum = 0;
            //we go through the current row and add up the amount of tokens in the entire row
            for (rowCheck=0;rowCheck<8;rowCheck++)
            {
                sum += board[dice][rowCheck].numTokens;
            }
            
            //while sum is equal to 0 we have to pick a new row for the player so that they can make their move
            while (sum == 0)
            {
                printf("\nSince there are no tokens left in row %d, the dice will be re re-rolled until a row which contains tokens is found!\n", dice);
                dice = rand()%6;
                
                //we now check the new row to see if there are tokens in it 
                for (rowCheck=0;rowCheck<8;rowCheck++)
                {
                    sum += board[dice][rowCheck].numTokens;
                }
            }   //the while loop continues until a valid row is found
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
            
            //If the user chooses the optional move
            if (optionalMove == 1)
            {
                printf("Please select which of your tokens you want to move up or down\n");
                printf("Row: ");
                scanf("%d", &rowOptional);
                printf("\nColumn: ");
                scanf("%d", &columnOptional);
                
                //Keep asking the user until he chooses a square that has a token on it
                while (board[rowOptional][columnOptional].numTokens == 0)
                {
                    printf("\nSelect a valid row and column!\n");
                    printf("Row: ");
                    scanf("%d", &rowOptional);
                    printf("\nColumn: ");
                    scanf("%d", &columnOptional);
                }
                
                //Keep asking the user until he chooses another players token instead of his own
                while (board[rowOptional][columnOptional].stack->col != players[playerTurn].col)
                {
                    printf("\nSelect a valid row and column!\n");
                    printf("Row: ");
                    scanf("%d", &rowOptional);
                    printf("\nColumn: ");
                    scanf("%d", &columnOptional);
                }
                
                //we check if the current square the player is trying to move a token on is an obstacle square
                if (board[rowOptional][columnOptional].type == OBSTACLE)
                {
                    //we set obstacleCheck = 0 initially
                    obstacleCheck = 0;
                    for (int p=0;p<6;p++)
                    {
                        for (int q=0;q<columnOptional;q++)
                        {
                            //obstacleCHeck checks if there are any tokens left in the squares behind the current obstacle square
                            obstacleCheck += board[p][q].numTokens;
                        }
                    }

                    //if there are tokens left behind the current obstacle sqaure
                    if (obstacleCheck > 0)
                    {
                        printf("\nYou cannot move the token in this position as it is in an Obstacle square and there are tokens behind you, choose another token now!\n");

                        //we get the player to pick another token which is not in an obstacle square
                        while (board[rowOptional][columnOptional].type == OBSTACLE)
                        {
                            do
                            {
                                printf("Select a valid Row: ");
                                scanf("%d", &rowOptional);
                                printf("Select a valid Column: ");
                                scanf("%d", &columnOptional);
                                //we make sure they pick a vlaid square, and that it has tokens on it
                            } while ((rowOptional < 0 || rowOptional > 8) && (mandatoryColumn < 0 || mandatoryColumn < 8) && (board[dice][mandatoryColumn].numTokens == 0));
                        }
                    }
                    
                    //if the token is in an obstacle sqaure, BUT it is allowed to move, we set this square to now be normal
                    else
                    {
                        board[rowOptional][columnOptional].type = NORMAL;
                    }
                }
                
                /*If the user chooses a token in row 0, only allowing them to move down*/
                if (rowOptional == 0)
                {
                    printf("This token can only be moved down. It will now be moved down for you!\n");
                    token *t = (token *) malloc(sizeof(token)); //Allocating memory space and assigning it to pointer t to token
                    t->col = board[rowOptional][columnOptional].stack->col; //Assigning the token color from the stack to the pointer color pointing to t
                    t->next = NULL; //Assigning the next which points to t as NULL
                    push(board, rowOptional+1, columnOptional, t); //Calling the push function with arguments board, optional row (plus one to move it down),optional column and t
                    board[rowOptional+1][columnOptional].numTokens++; //Incrementing the number of tokens where the token moved using the optional move has been placed
            
                    pop(board, rowOptional, columnOptional, board[rowOptional][columnOptional].stack); //Popping the token from it's original position after the optional move
            
                    if (board[rowOptional][columnOptional].numTokens != 0) /*If the number of tokens of the optional square does not equal to zero*/
                    {
                        board[rowOptional][columnOptional].numTokens--; //Decrement the number of tokens of the optional square
                    }
                }
                
                else if (rowOptional == 5)
                {
                    printf("This token can only be moved up. It will now be moved up for you!\n");
                    token *t = (token *) malloc(sizeof(token)); //Allocating memory space and assigning it to pointer t to token
                    t->col = board[rowOptional][columnOptional].stack->col; //Assigning the token color from the stack to the pointer color pointing to t
                    t->next = NULL; //Assigning the next which points to t as NULL
                    push(board, rowOptional-1, columnOptional, t); //Calling the push function with arguments board, optional row (plus one to move it down),optional column and t
                    board[rowOptional-1][columnOptional].numTokens++; //Incrementing the number of tokens where the token moved using the optional move has been placed
            
                    pop(board, rowOptional, columnOptional, board[rowOptional][columnOptional].stack); //Popping the token from it's original position after the optional move
            
                    if (board[rowOptional][columnOptional].numTokens != 0) /*If the number of tokens of the optional square does not equal to zero*/
                    {
                        board[rowOptional][columnOptional].numTokens--; //Decrement the number of tokens of the optional square
                    }
                }
                
                else /*Else ask the user to move the token up or down*/
                {
                    printf("Press 1 to move this token UP one row, press 2 to move this token DOWN one row: ");
                    scanf("%d", &upOrDown);
                    
                    /*Keep asking the user until he enters one of the valid responses defined in the while loop*/
                    while ((upOrDown != 1) && (upOrDown != 2))
                    {
                        printf("Press 1 to move this token UP one row, press 2 to move this token DOWN one row: ");
                        scanf("%d", &upOrDown);
                    }
                    
                    if (upOrDown == 1) //Moving the token UP
                    {
                        token *t = (token *) malloc(sizeof(token)); //Allocating space for the pointer t which points to the token
                        t->col = board[rowOptional][columnOptional].stack->col; //Assigning the token color from the stack to the pointer color pointing to t
                        t->next = NULL; //Assigning the next which points to t as NULL
                        push(board, rowOptional-1, columnOptional, t); //Calling the push function with arguments board, optional row (plus one to move it down),optional column and t
                        board[rowOptional-1][columnOptional].numTokens++; //Incrementing the number of tokens where the token moved using the optional move has been placed (-1 for moving it up)
            
                        pop(board, rowOptional, columnOptional, board[rowOptional][columnOptional].stack); //Popping the token from it's original position after the optional move
            
                        if (board[rowOptional][columnOptional].numTokens != 0) /*If the number of tokens of the optional square does not equal to zero*/
                        {
                            board[rowOptional][columnOptional].numTokens--; //Decrement the number of tokens of the optional square
                        }
                    }
                    
                    else if (upOrDown == 2) //Moving the token DOWN
                    {
                        token *t = (token *) malloc(sizeof(token)); //Allocating space for the pointer t which points to the token
                        t->col = board[rowOptional][columnOptional].stack->col; //Assigning the token color from the stack to the pointer color pointing to t
                        t->next = NULL; //Assigning the next which points to t as NULL
                        push(board, rowOptional+1, columnOptional, t); //Calling the push function with arguments board, optional row (plus one to move it down),optional column and t
                        board[rowOptional+1][columnOptional].numTokens++; //Incrementing the number of tokens where the token moved using the optional move has been placed (+1 for moving it down)
            
                        pop(board, rowOptional, columnOptional, board[rowOptional][columnOptional].stack); //Popping the token from it's original position after the optional move
            
                        if (board[rowOptional][columnOptional].numTokens != 0) /*If the number of tokens of the optional square does not equal to zero*/
                        {
                            board[rowOptional][columnOptional].numTokens--; //Decrement the number of tokens of the optional square
                        }
                    }
                }
            }
            
            print_board(board); //Printing the board
            
            /*After the optional move, we need to check if the row the player got at the beginning of their turn still has a token in it.
             They may have moved the only token in their given row out of the row, in which case they now need a new row for the mandatory move.*/
            
            //we set sum = 0 again
            sum = 0;
            for (rowCheck=0;rowCheck<8;rowCheck++)
            {
                //check all squares in given row to check if their are tokens left
                sum += board[dice][rowCheck].numTokens;
            }
            
            //if there are no tokens
            while (sum == 0)
            {
                //we find the player a new role
                printf("\nSince there are no tokens left in row %d, the dice will be re re-rolled until a row which contains tokens is found!\n\n", dice);
                dice = rand()%6;
                
                for (rowCheck=0;rowCheck<8;rowCheck++)
                {
                    //check if the new row has tokens
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
            
            while (mandatoryColumn < 0 || mandatoryColumn > 7)
            {
                printf("\nSelect a valid column: ");
                scanf("%d", &mandatoryColumn);
            }
            
            //check if the square they've chosen is an obstacle square
            if (board[dice][mandatoryColumn].type == OBSTACLE)
            {
                //set obstacleCheck = 0
                obstacleCheck = 0;
                for (int p=0;p<6;p++)
                {
                    for (int q=0;q<mandatoryColumn;q++)
                    {
                        //we check if there are any tokens left behind this square
                        obstacleCheck += board[p][q].numTokens;
                    }
                }

                //if there are tokens left
                if (obstacleCheck > 0)
                {
                    printf("\nYou cannot move the token in this position as it is in an Obstacle square and there are tokens behind you, choose another token now!\n\n");
                    
                    //set sum = 0
                    sum = 0;
                    for (rowCheck=0;rowCheck<8;rowCheck++)
                    {
                        //check if there are any tokens in this row
                        sum += board[dice][rowCheck].numTokens;
                    }

                    //we take away the number of tokens on the current sqaure, as it is an obstacle square that we already know has tokens that cannot be moved
                    sum -= board[dice][mandatoryColumn].numTokens;
            
                    //if the value of sum is = 0 after we take away the obstacle square tokens, we know there are no tokens in this row which can be moved
                    //we must then get a new row for them
                    while (sum == 0)
                    {
                        printf("\nSince there are no tokens left in row %d, the dice will be re re-rolled until a row which contains tokens is found!\n", dice);
                        dice = rand()%6;
                
                        for (rowCheck=0;rowCheck<8;rowCheck++)
                        {
                            //we add up all the tokens in our new row, minus any tokens in obstacle squares
                            if (board[dice][rowCheck].type != OBSTACLE)
                            {
                               sum += board[dice][rowCheck].numTokens; 
                            }  
                        }
                    }
                    
                    //once we find a new row, we tell them
                    printf("You now have row %d!", dice);
                    
                    printf("\nSelect column: ");
                    scanf("%d", &mandatoryColumn);
                    
                    //if they choose a square with no tokens, we make them choose again
                    while (board[dice][mandatoryColumn].numTokens == 0)
                    {
                        printf("Select a valid column: ");
                        scanf("%d", &mandatoryColumn);
                    }
                    
                    //if they choose another obstacle square, we make them choose a square which has tokens NOT in an obstacle square
                    //we know this square exists as the program would not have chosen this row if there wasn't one
                    while (board[dice][mandatoryColumn].type == OBSTACLE)
                    {
                        do
                        {
                            printf("\nSelect a valid Column: ");
                            scanf("%d", &mandatoryColumn);
                        } while ((mandatoryColumn < 0 || mandatoryColumn > 8) && (board[dice][mandatoryColumn].type == OBSTACLE));
                    }      
                }
                
                //if it was an obstacle square but the token was allowed to move out of it, we set this squares type to be NORMAL
                else
                {
                    board[dice][mandatoryColumn].type = NORMAL;
                }
            }
            
            printf("\nYou chose to move the token in position (%d, %d) one column forward!", dice, mandatoryColumn);
            //board[dice][mandatoryColumn+1].stack = (token *) malloc(sizeof(token));
            //board[dice][mandatoryColumn+1].stack->col = board[dice][mandatoryColumn].stack->col;
            token *t = (token *) malloc(sizeof(token)); //Allocating space for the pointer t which points to the token
            t->col = board[dice][mandatoryColumn].stack->col; //Assigning the token color from the stack to the pointer color pointing to t
            t->next = NULL; //Assigning the next which points to t as NULL
            push(board, dice, mandatoryColumn+1, t); //Calling the push function with arguments board, dice as row ,mandatory column(plus one to move it forward) and t
            board[dice][mandatoryColumn+1].numTokens++; //Incrementing the number of tokens where the token moved using the optional move has been placed (+1 for moving it down)
           
            pop(board, dice, mandatoryColumn, board[dice][mandatoryColumn].stack); //Popping the token from it's original position after the mandatory move
            if (board[dice][mandatoryColumn].numTokens != 0) /*If the number of tokens of the mandatory square does not equal to zero*/
            {
                board[dice][mandatoryColumn].numTokens--; //Decrement the number of tokens of the mandatory square
            }
            
            /*If the mandatory column +1 is equivalent to the last column 8*/
            if ((mandatoryColumn+1) == 8)
            {
                //If the player 0's color is equal to the token color from the mandatory move
                if (players[0].col == board[dice][mandatoryColumn+1].stack->col)
                {   //Increment that player's count for the number of his token's in the last column
                    players[0].numTokensLastCol++;
                }
                //If the player 1's color is equal to the token color from the mandatory move
                else if (players[1].col == board[dice][mandatoryColumn+1].stack->col)
                {
                    //Increment that player's count for the number of his token's in the last column
                    players[1].numTokensLastCol++;
                }
                //If the player 2's color is equal to the token color from the mandatory move
                else if (players[2].col == board[dice][mandatoryColumn+1].stack->col)
                {
                    //Increment that player's count for the number of his token's in the last column
                    players[2].numTokensLastCol++;
                }
                //If the player 3's color is equal to the token color from the mandatory move
                else if (players[3].col == board[dice][mandatoryColumn+1].stack->col)
                {
                    //Increment that player's count for the number of his token's in the last column
                    players[3].numTokensLastCol++;
                }
                //If the player 4's color is equal to the token color from the mandatory move
                else if (players[4].col == board[dice][mandatoryColumn+1].stack->col)
                {
                    //Increment that player's count for the number of his token's in the last column
                    players[5].numTokensLastCol++;
                }
                //If the player 5's color is equal to the token color from the mandatory move
                else if (players[5].col == board[dice][mandatoryColumn+1].stack->col)
                {
                    //Increment that player's count for the number of his token's in the last column
                    players[5].numTokensLastCol++;
                }
                //If the player 6's color is equal to the token color from the mandatory move
                else if (players[6].col == board[dice][mandatoryColumn+1].stack->col)
                {
                    //Increment that player's count for the number of his token's in the last column
                    players[6].numTokensLastCol++;
                }
            }
            
            
            
            
            //END OF TURN 
            playerTurn++;
           
            printf("\n\nHere is what the board currently looks like!\n\n");
            print_board(board);
            //Iterating for the amount of players within the game
            for (a=0;a<numPlayers;a++)
            {
                //If one of the player's variable is equal to 3 he has won the game;in other words he has three tokens in the last column - a winning condition
                if (players[a].numTokensLastCol == 3)
                {
                    win = 1; //Assigning win to 1 indicating that a player has won and the game concludes
                    printf("\n\n\n\nThe winner of the game is %s", players[a].playerName); //Printing the winners name
                }
            }     
        }
    }
}
