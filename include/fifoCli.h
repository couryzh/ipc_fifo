#ifndef JHFIFOCLI_H
#define JHFIFOCLI_H

#include "fifo.h"

struct fifo * fifoCliInit();

int fifoCliComm(struct fifo * fifo, const char * req, int reqLen, char * resp, int respLen);

void fifoCliClose(struct fifo * fifo);

#endif
