#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "JHFIFOSrv.h"

int simpleCopy(const char * req, int reqLen, char * resp, int respLen)
{
	snprintf(resp, respLen, "RESP: %s", req);
	return strlen(resp) + 1;
}


int main(void)
{
	struct JHFIFO * fifo;

	fifo = JHFIFOSrvInit();
	if (!fifo) {
		printf("test2 fifo init failed\n");
		return -1;
	}

	JHFIFOSrvLoop(fifo, simpleCopy);
	return 0;
}
