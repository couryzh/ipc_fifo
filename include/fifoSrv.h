#ifndef JHFIFOSRV_H
#define JHFIFOSRV_H

#include "fifo.h"

typedef int(*fifoSrvHandler)(const char * req, int reqLen, char * resp, int respLen);

struct fifo * fifoSrvInit();

int fifoSrvLoop(struct fifo * fifo, fifoSrvHandler handler);
#endif
