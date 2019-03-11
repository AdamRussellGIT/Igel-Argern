/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#include <stdio.h>
#include <string.h>

#include "game_init.h"
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
    
    //YOU WILL NEED TO IMPLEMENT THIS FUNCTION IN THIS LAB
    int finInput=1;
    int i=0;
    int j=1;
    int color;
    
    while(finInput!=0)
    {
        printf("\nPlease enter the name of the Player %d:\n",j++);
        printf("Name:");
        scanf("%s",&players[i].playerName[i]);
        //fgets(players[i].playerName[i],30, stdin);
        
        printf("\nPlease enter the color for the player:\n");
        printf("RED=1, BLU=2, GREEN=3, YELLOW=4, PINK=5, ORANGE=6\n");
        scanf("%d",&color);
        //fgetc(stdin);//Eats the last character inputted ?
                 
        switch(color)
        {
            case 1: 
                
                    players[i].col=RED;
                    break;
            
            case 2: 
                
                    players[i].col=BLU;
                    break;
                
            case 3: 
                
                    players[i].col=GREEN;
                    break;
            case 4: 
                
                    players[i].col=YELLOW;
                    break;
            case 5: 
                
                    players[i].col=PINK;
                    break;
            case 6: 
                
                    players[i].col=ORANGE;
                    break;
                
            default:
                printf("\nInvalid color!\n");
                break;
                    
                
        }
        i++;

            //max 6 players and min 2 players
            if(i>=2)
            {
               printf("Do you want to input another player (Press 1 for yes) (Press 0 for no)\n");
               scanf("%d",&finInput);
                if(finInput==0||i==6)
                { 
                  printf("\nThe players array at position 0 \n%s\n%d\n",players[0].playerName,players[0].col);
                  printf("\nThe players array at position 1 \n%s\n%d\n",players[1].playerName,players[1].col);
                  printf("\nThe players array at position 2 \n%s\n%d\n",players[2].playerName,players[2].col);
                  printf("\nThe players array at position 3 \n%s\n%d\n",players[3].playerName,players[3].col);
                  printf("\nThe players array at position 4 \n%s\n%d\n",players[4].playerName,players[4].col);
                  printf("\nThe players array at position 5 \n%s\n%d\n",players[5].playerName,players[5].col);
                  break;  
                } 
            }
            
            
        }
        return i;
    }
        
    
    
   
     

