/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <string.h>


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){
   
    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) 
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;
        }
    }
}
    
    
 /*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){
    int i=0;
    int morePlayers;
    int colour;
    
    while (i<6)
    {
        printf("\nEnter the name for player %d: ", i);
        fgets(players[i].playerName, 30, stdin);
        if(players[i].playerName[strlen(players[i].playerName)]=='\n'){
            players[i].playerName[strlen(players[i].playerName)] = '\0';
        }
        
        printf("\nEnter the color for this player.\n");
        printf("(Enter 0 for Red, 1 for Blu, 2 for Green, 3 for Yellow, 4 for Pink, 5 for Orange).\n");
        printf("(Don't use the same color as another player).\n");
        scanf("%d", &colour);
        
        fgetc(stdin);
        
        switch (colour) {
            case 0: players[i].col = RED;
                    break;
            
            case 1: players[i].col = BLU;
                    break;
            
            case 2: players[i].col = GREEN;
                    break;
            
            case 3: players[i].col = YELLOW;
                    break; 
            
            case 4: players[i].col = PINK;
                    break;
            
            case 5: players[i].col = ORANGE;
                    break;
            
            default: printf("You did not enter a valid number, please close the program and try again :/\n");
                     break;
        }
        
        if (i >= 1 && i < 5)
        {
            printf("\nIs there another player? (1 for yes, 0 for no): ");
            do
            {
                scanf("%d", &morePlayers);
            } while (morePlayers != 1 && morePlayers != 0);
            
            fgetc(stdin);
            
            if (morePlayers == 0)
            {
                return i+1;
            }
        }
        i++;
    }
    
    
        return i;
    }
    
   