// Implemetation of a FIFO queue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chessboard.h"

#ifndef KNIGHT_QUEUE_
#define KNIGHT_QUEUE_

typedef struct _queue{
    square** data;
    size_t head;
    size_t tail;
    size_t count;
    size_t size;
}Queue;

int queue_write(Queue Q, square* to_write){
    if(Q.count + 1 < Q.size){
        int newsize = Q.size + 5;
        square** newq = (square**)malloc((newsize) * sizeof(square));
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

#endif