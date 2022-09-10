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
    coordinates coords;
    unsigned short int color;
    struct _square* adjacent;
    unsigned short int adjacent_count;
    struct _square* previous;
}square;

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
    // if sizeof(square) < 3 this has undefined behaviour
    // too bad :(
}

#endif