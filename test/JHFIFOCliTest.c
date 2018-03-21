#include <stdio.h>
#include <string.h>
#include "JHFIFOCli.h"

int main()
{
	char input[64], s[128];
	struct JHFIFO * fifo;
	int n = 5;

	fifo = JHFIFOCliInit();

	while (n--) {
		fgets(input, 64, stdin);
		JHFIFOCliComm(fifo, input, strlen(input), s, 127);
		printf("%s\n", s);
		memset(s, 0, sizeof(s));
	}

	JHFIFOCliClose(fifo);
	return 0;
}
