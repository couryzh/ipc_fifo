#ifndef JHFIFOCLI_H
#define JHFIFOCLI_H

#include "JHFIFO.h"

struct JHFIFO * JHFIFOCliInit();

int JHFIFOCliComm(struct JHFIFO * fifo, const char * req, int reqLen, char * resp, int respLen);

void JHFIFOCliClose(struct JHFIFO * fifo);

#endif
