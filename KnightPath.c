#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chessboard.h"
#include "bfs.h"


/*
    Console program that outpust a set of chess moves a knight would need to make in order to get to a desired square
    Implemented using a BFS algorithm
*/

int link_squares(square board[8][8]);
int inrange(int coordinate) {return (coordinate >= 0 && coordinate <= 8) ? 1:0;}
void freeboard(square board[8][8]);


int main(){
    square board[8][8];
    if(link_squares(board) != 0){
        freeboard(board);
        return -1;
    }

    return 0;
}

int link_squares(square board[8][8]){
    int size = 0, x, y;
    square* temp_links[8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            // check all legal moves from one square (max of 8) and add them to the list of adjacent squares
            if(inrange(x = i+1) && inrange(y = j+3)) temp_links[size++] = &board[x][y];
            if(inrange(x = i+1) && inrange(y = j-3)) temp_links[size++] = &board[x][y];
            if(inrange(x = i-1) && inrange(y = j+3)) temp_links[size++] = &board[x][y];
            if(inrange(x = i-1) && inrange(y = j-3)) temp_links[size++] = &board[x][y];
            if(inrange(x = i+3) && inrange(y = j+1)) temp_links[size++] = &board[x][y];
            if(inrange(x = i+3) && inrange(y = j-1)) temp_links[size++] = &board[x][y];
            if(inrange(x = i-3) && inrange(y = j+1)) temp_links[size++] = &board[x][y];
            if(inrange(x = i-3) && inrange(y = j-1)) temp_links[size++] = &board[x][y];

            board[i][j].adjacent_count = size + 1;
            board[i][j].adjacent = (square*)malloc((size+1) * sizeof(square));
            if(!board[i][j].adjacent){
                perror("malloc fail in func link_squares\n");
                return -1;
            }
            memcpy(&board[i][j].adjacent, &temp_links, (size+1) * sizeof(square));
        }
    }
    return 0;
}

// free all heap allocated memory
void freeboard(square board[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            free(board[i][j].adjacent);
        }
    }
}
