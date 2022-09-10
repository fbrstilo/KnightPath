#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE 0
#define GREY 1
#define BLACK 2
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

typedef struct _queue{
    square** data;
    size_t head;
    size_t tail;
    size_t count;
    size_t size;
}Queue;


// create an 8x8 array of struct _square to represent the board
// link each square to the squares a knight can jump to
// run BFS algorithm to find shortest path (one of) from one square to another

int link_squares(square board[8][8]);
int inrange(int coordinate) {return (coordinate >= 0 && coordinate <= 8) ? 1:0;}
int text_to_coords(const char* square, int* x, int* y);
int coords_to_text(int x, int y, char* square);
void freeboard(square board[8][8]);
int queue_write(Queue Q, square* to_write);
int queue_read(Queue Q, square* data);

int main(){
    square board[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j].color = WHITE;
            board[i][j].coords.x = i;
            board[i][j].coords.y = j;
        }
    }
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

// free all heap allocated memory
void freeboard(square board[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            free(board[i][j].adjacent);
        }
    }
}

int queue_write(Queue Q, square* to_write){
    if(Q.count + 1 < Q.size){
        int newsize = Q.size + 5;
        square** newq = malloc((newsize) * sizeof(square));
        if(!newq){
            perror("malloc fail in func queue_write\n");
            return -1;
        }
        if(Q.tail <= Q.head){
            memcpy(newq, &Q.data[Q.head], (Q.size - Q.head) * sizeof(square)); // copy memory from head to end of old queue
            memcpy(&newq[Q.size - Q.head], Q.data, Q.tail * sizeof(square)); // copy memory from start of old queue to tail
        }
        else{
            memcpy(newq, &Q.data[Q.head], Q.count * sizeof(square));
        }
        free(Q.data);
        Q.data = newq;
        Q.size = newsize;
        Q.head = 0;
        Q.tail = Q.count;
    }
    Q.data[Q.tail] = to_write;
    ++Q.count;
    ++Q.tail;

    return 0;
}

int queue_read(Queue Q, square* data){
    data = Q.data[Q.head];
    ++Q.head;
    if(Q.head == Q.size) Q.head = 0;    // if head has reached over the end, reset it to 0
    --Q.count;
    return 0;
}