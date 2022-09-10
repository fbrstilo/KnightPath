// Implemetation of a FIFO queue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chessboard.h"

#ifndef BFS_
#define BFS_


#define WHITE 0
#define GREY 1
#define BLACK 2

typedef struct _queue{
    square** data;
    int head;
    int tail;
    int count;
    int size;
}queue;

int queue_write(queue* Q, square* to_write){
    if(Q->count + 1 < Q->size){
        int newsize = Q->size + 5;
        square** newq = (square**)malloc((newsize) * sizeof(square*));
        if(!newq){
            perror("malloc fail in func queue_write\n");
            return -1;
        }
        if(Q->tail <= Q->head){
            memcpy(newq, &Q->data[Q->head], (Q->size - Q->head) * sizeof(square*)); // copy memory from head to end of old queue
            memcpy(&newq[Q->size - Q->head], Q->data, Q->tail * sizeof(square*)); // copy memory from start of old queue to tail
        }
        else{
            memcpy(newq, &Q->data[Q->head], Q->count * sizeof(square*));
        }
        free(Q->data);
        Q->data = newq;
        Q->size = newsize;
        Q->head = 0;
        Q->tail = Q->count;
    }
    Q->data[Q->tail] = to_write;
    ++Q->count;
    ++Q->tail;

    return 0;
}

square* queue_read(queue* Q){
    square* data = Q->data[Q->head];
    ++Q->head;
    if(Q->head == Q->size) Q->head = 0;    // if head has reached over the end, reset it to 0
    --Q->count;
    return data;
}

void queue_free(queue* Q){
    free(Q->data);
}

int queue_init(queue* Q, int size){
    Q->data = (square**)malloc(size * sizeof(square*));
    if(!Q->data){
        perror("malloc fail in func queue_init\n");
        return -1;
    }
    Q->size = size;
    Q->count = 0;
    Q->head = 0;
    Q->tail = 0;
    return 0;
}

square* bfs(square board[8][8], square* start, square* end){
    square* current = NULL;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j].color = WHITE;
            board[i][j].coords.x = i;
            board[i][j].coords.y = j;
            board[i][j].previous = NULL;
        }
    }
    queue Q;
    queue_init(&Q, 5);

    start->color = GREY;
    queue_write(&Q, start);
    while(Q.count > 0){
        current = queue_read(&Q);
        for(int i = 0; i < current->adjacent_count; i++){
            if(current->adjacent[i]->color == WHITE){
                current->adjacent[i]->color = GREY;
                current->adjacent[i]->previous = current;
                if(current->adjacent[i] == end){
                    queue_free(&Q);
                    return end;
                }
                for(int j = 0; j < current->adjacent[i]->adjacent_count; j++){
                    queue_write(&Q, &(current->adjacent[i]->adjacent[j]));
                }
            }
        }
        current->color = BLACK;
    }

    queue_free(&Q);
    return NULL;    // in theory the function never reaches this 
}

#endif