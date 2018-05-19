#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "JHFIFOSrv.h"

struct JHFIFO JHFIFOSrv;

int runFlag = 1;

void handleSigint(int signum)
{
	runFlag = 0;
}

struct JHFIFO * JHFIFOSrvInit()
{
	struct sigaction sa;

	if (mkfifo(SRV_FIFO_FILE, 0666) < 0 && (errno != EEXIST)) {
		perror("mkfifo srv");
		return NULL;
	}

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handleSigint;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &sa, NULL);

	JHFIFOSrv.type = SRV_TERMINAL;
	return &JHFIFOSrv;
}

int JHFIFOSrvLoop(struct JHFIFO * fifo, JHFIFOSrvHandler handler)
{
	int dummyFd;
	char recvBuff[256], sendBuff[4096];
	int nrecv, nsend;

	fifo->readFd = open(SRV_FIFO_FILE, O_RDONLY);
	dummyFd = open(SRV_FIFO_FILE, O_WRONLY);

	while (runFlag) {
		nrecv = read(fifo->readFd, recvBuff, sizeof(recvBuff) - 1);
		if (nrecv < 0) {
			if (errno == EINTR) {
				continue;
			}
			else {
				break;
			}
		}
		recvBuff[nrecv] = 0;
		//printf("read: %s\n", recvBuff);

		nsend = handler(recvBuff, nrecv, sendBuff, sizeof(sendBuff) - 1);

		//printf("write: %s\n", sendBuff);
		fifo->writeFd = open(CLI_FIFO_FILE, O_WRONLY);
		if (fifo->writeFd < 0) {
			perror("open pessfifo_cli");
			continue;
		}
		write(fifo->writeFd, sendBuff, nsend);
		close(fifo->writeFd);
	}

	unlink(SRV_FIFO_FILE);
	close(fifo->readFd);
	close(dummyFd);
	return 1;
}
