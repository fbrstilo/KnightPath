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
void ll_reverse(square* head);


int main(){
    char start[3], end[3], pos[3];
    int startx, starty, endx, endy;
    square* curr;
    square board[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j].color = WHITE;
            board[i][j].coords.x = i;
            board[i][j].coords.y = j;
            board[i][j].previous = NULL;
            board[i][j].adjacent_count = 0;
        }
    }
    if(link_squares(board) != 0){
        freeboard(board);
        return -1;
    }

    //user input of start and end square
    while(1){
        printf("Enter start and end square (eg. f3 g8):\n");
        scanf(" %s", start);
        scanf(" %s", end);
        if(text_to_coords(start, &startx, &starty) == 0 && text_to_coords(end, &endx, &endy) == 0) break;
        else printf("Invalid input. Please try again:\n");
    }

    bfs(board, &board[startx][starty], &board[endx][endy]);
    ll_reverse(&board[endx][endy]);    //moves that BFS returns are in reverse order, so we reverse the created list
    curr = &board[startx][starty];
    while(curr){
        coords_to_text(curr->coords.x, curr->coords.y, pos);
        printf("%s ", pos);
    }
    printf("\n");



    return 0;
}

int link_squares(square board[8][8]){
    int size = 0, x, y;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            // check all legal moves from one square (max of 8) and add them to the list of adjacent squares
            size = 0;
            if(inrange(x = i+1) && inrange(y = j+3)) board[i][j].adjacent[size++] = &board[x][y];
            if(inrange(x = i+1) && inrange(y = j-3)) board[i][j].adjacent[size++] = &board[x][y];
            if(inrange(x = i-1) && inrange(y = j+3)) board[i][j].adjacent[size++] = &board[x][y];
            if(inrange(x = i-1) && inrange(y = j-3)) board[i][j].adjacent[size++] = &board[x][y];
            if(inrange(x = i+3) && inrange(y = j+1)) board[i][j].adjacent[size++] = &board[x][y];
            if(inrange(x = i+3) && inrange(y = j-1)) board[i][j].adjacent[size++] = &board[x][y];
            if(inrange(x = i-3) && inrange(y = j+1)) board[i][j].adjacent[size++] = &board[x][y];
            if(inrange(x = i-3) && inrange(y = j-1)) board[i][j].adjacent[size++] = &board[x][y];

            board[i][j].adjacent_count = size;
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

void ll_reverse(square* head){
    square* next = NULL;
    square* curr = head;
    square* prev = NULL;
    while(curr->previous){
        next = curr->previous;
        curr->previous = prev;
        prev = curr;
        curr = next;
    }
}
    