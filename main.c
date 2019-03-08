/*BLAHBLAHBLAH
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//I think blah is a great idea!
/* 
 * File:   main.c
 * Author: lpasqua
 *
 * Created on 06 March 2019, 12:11
 */

#include <stdio.h>
#include "game_init.h"
#include "game_logic.h"


/*
 * 
 */
int main(int argc, char** argv) {
    
    //the board is defined as a 2-Dimensional array of squares
    square board[NUM_ROWS][NUM_COLUMNS];
    
    //an array containing the players (MAX 6 players)
    player players[6];

    //the number of players
    int numPlayers =0;
    
    //creates the squares of the board
    initialize_board(board);
    
    //prints the board
    print_board(board);
    
    //creates the players
    numPlayers = initialize_players(players);
    
    printf("Num players = %d\n\n", numPlayers);
    printf("%s\n, %d\n\n", players[0].playerName, players[0].col);
    printf("%s\n, %d\n\n", players[1].playerName, players[1].col);
    printf("%s\n, %d\n\n", players[2].playerName, players[2].col);
    printf("%s\n, %d\n\n", players[3].playerName, players[3].col);
    printf("%s\n, %d\n\n", players[4].playerName, players[4].col);
    printf("%s\n, %d\n\n", players[5].playerName, players[5].col);
    
    
    
    //asks each player to place their tokens
    //on the first column of the board
    place_tokens(board, players, numPlayers);
    
    
    //manages the turns of the game and identifies a winner
    play_game(board, players, numPlayers);
    
    return 0;
}

