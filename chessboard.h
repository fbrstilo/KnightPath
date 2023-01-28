#include <stdio.h>
#include <stdlib.h>

#ifndef CHESSBOARD_
#define CHESSBOARD_

#define OFFSET_LETTER 'a'
#define OFFSET_NUMBER '1'

typedef struct _coordinates{
    unsigned short int x, y;
}coordinates;

typedef struct _square{
    coordinates coords; // coordinates of the current square
    unsigned short int color; // 'color' is used for checking wether BFS algorithm has visited the square
    struct _square* adjacent[8]; // the (maximum) 8  squares a knight can jump to from current square
    unsigned short int adjacent_count; // count of actual squares the knight can jump to
    struct _square* previous; // square from which this one was reached (used for printing the path)
}square;

// convert chess coordinates to numeric by offseting from the start of ASCII table
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

// convert numeric coordinates to chess notation by offseting from the start of ASCII table
int coords_to_text(int x, int y, char* square){
    if(!(x >= 0 && x <= 7 && y >= 0 && y <= 7)) return 1; // check for invalid coordinates
    square[0] = x + OFFSET_LETTER;
    square[1] = y + OFFSET_NUMBER;
    square[2] = '\0';
    return 0;
    // if sizeof(square) < 3 this has undefined behaviour
    // too bad :(
}

#endif