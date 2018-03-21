#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "JHFIFOCli.h"

struct JHFIFO JHFIFOCli;

struct JHFIFO * JHFIFOCliInit()
{
	if (mkfifo(CLI_FIFO_FILE, 0666) < 0 && (errno != EEXIST)) {
		perror("mkfifo cli");
		return NULL;
	}
	JHFIFOCli.type = CLI_TERMINAL;
	return &JHFIFOCli;
}


int JHFIFOCliComm(struct JHFIFO * fifo, const char * req, int reqLen, char * resp, int respLen)
{
	int n, nresp;

	fifo->writeFd = open(SRV_FIFO_FILE, O_WRONLY);
	if (fifo->writeFd < 0) {
		perror("open pessfifo_srv");
		return -1;
	}
	write(fifo->writeFd, req, reqLen);

	fifo->readFd = open(CLI_FIFO_FILE, O_RDONLY);
	if (fifo->readFd < 0) {
		perror("open pessfifo_cli");
		return -1;
	}
	nresp = 0;
	while ((n = read(fifo->readFd, &resp[nresp], respLen - nresp)) > 0) {
		nresp += n;
	}

	return nresp;
}

void JHFIFOCliClose(struct JHFIFO * fifo)
{
	close(fifo->readFd);
	close(fifo->writeFd);
	unlink(CLI_FIFO_FILE);
}
