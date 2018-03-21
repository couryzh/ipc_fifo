#ifndef JHFIFOSRV_H
#define JHFIFOSRV_H

#include "JHFIFO.h"

typedef int(*JHFIFOSrvHandler)(const char * req, int reqLen, char * resp, int respLen);

struct JHFIFO * JHFIFOSrvInit();

int JHFIFOSrvLoop(struct JHFIFO * fifo, JHFIFOSrvHandler handler);
#endif
