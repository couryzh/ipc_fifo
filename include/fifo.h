#ifndef _FIFO_H_
#define _FIFO_H_

#define SRV_FIFO_FILE "/tmp/pessfifo_srv"
#define CLI_FIFO_FILE "/tmp/pessfifo_cli"

enum TerminalType {SRV_TERMINAL, CLI_TERMINAL};
struct fifo {
	enum TerminalType type;
	int readFd;
	int writeFd;
	int dummyFd;
	int except;
};

#endif
