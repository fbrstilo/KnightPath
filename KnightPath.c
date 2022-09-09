#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE 0
#define GREY 1
#define BLACK 2
#define OFFSET_LETTER 'a'
#define OFFSET_NUMBER '1'

typedef struct _square{
    int color;
    struct _square* adjacent;
    int adjacent_count;
}square;

// create an 8x8 array of struct _square (to represent the board)
// link each square to the squares a knight can jump to
// run BFS algorithm to find shortest path(s) from one square to another

int link_squares(square** board);
int text_to_coords(const char* square, int* x, int* y);
int coords_to_text(int x, int y, char* square);
int inrange(int coordinate) {return (coordinate >= 0 && coordinate <= 8) ? 1:0;}

int main(){

    return 0;
}

int link_squares(square** board){
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
            if(!board[i][j].adjacent) return -1;
            memcpy(&board[i][j].adjacent, &temp_links, (size+1) * sizeof(square));
        }
    }
    return 0;
}


// convert chess coordinates to numeric by OFFSET_LETTERing from the start of ASCII table
int text_to_coords(const char* square, int* x, int* y){
    if(strlen(square) != 2) return 1;

    if(square[0] >= 'a' && square[0] <= 'h'){
        *x = square[0] - OFFSET_LETTER;
    }
    else return 1;

    if(square[1] >= '1' && square[1] <= '8'){
        *y = square[1] - OFFSET_NUMBER;
    }
    else return 1;

    return 0;
}

// convert numeric coordinates to chess notation by OFFSET_LETTERing from the start of ASCII table
int coords_to_text(int x, int y, char* square){
    if(!(x >= 1 && x <= 8 && y >= 1 && y <= 8)) return 1; // check for invalid coordinates
    square[0] = x + OFFSET_LETTER;
    square[1] = y + OFFSET_NUMBER;
    square[2] = '\0';
    return 0;
    // if sizeof(square) <3 this has undefined behaviour
    // too bad :(
}

