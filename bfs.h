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
    if(Q->count + 1 > Q->size){
        int newsize = Q->size + 5;
        square** newq = (square**)malloc((newsize) * sizeof(square*));
        if(!newq){
            perror("malloc fail in func queue_write\n");
            return -1;
        }
        if(Q->tail <= Q->head){
            for(int i = Q->head; i < Q->size; i++){
                newq[i - Q->head] = Q->data[i]; // copy memory from head to end of old queue
            }
            for(int i = 0; i < Q->tail; i++){
                newq[i + Q->size - Q->head] = Q->data[i]; // copy memory from begining to tail of old queue
            }
        }
        else{
            for(int i = 0; i < Q->count; i++){
                newq[i] = Q->data[i + Q->head]; // copy memory block from head to tail of olf queue
            }
        }
        free(Q->data);
        Q->data = newq;
        Q->size = newsize;
        Q->head = 0;
        Q->tail = Q->count;
    }
    else if(Q->tail >= Q->size) Q->tail = 0; // wrap arround to start of allocated memory
    Q->data[Q->tail] = to_write;
    ++Q->count;
    ++Q->tail;

    return 0;
}

square* queue_read(queue* Q){
    if(Q->count == 0){
        perror("Reading from empty queue");
        return NULL;
    }
    square* data = Q->data[Q->head];
    Q->head += 1;
    if(Q->head == Q->size) Q->head = 0;    // if head has reached over the end, reset it to 0
    Q->count -= 1;
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

int bfs(square board[8][8], square* start, square* end){
    square* current = NULL;
    queue Q;
    if(queue_init(&Q, 5) != 0){
        return -1;
    }

    start->color = GREY;
    queue_write(&Q, start);
    while(Q.count > 0){
        current = queue_read(&Q);
        if(current == NULL){
            queue_free(&Q);
            return -1;
        }
        for(int i = 0; i < current->adjacent_count; i++){
            if(current->adjacent[i]->color == WHITE){
                current->adjacent[i]->color = GREY;
                current->adjacent[i]->previous = current;
                if(current->adjacent[i] == end){
                    queue_free(&Q);
                    return 0;
                }
                if(queue_write(&Q, current->adjacent[i]) != 0){
                    queue_free(&Q);
                    return -1;
                }
            }
        }
        current->color = BLACK;
    }
    printf("shid\n");
    queue_free(&Q);
    return -1;    // in theory the function never reaches this
}

#endif