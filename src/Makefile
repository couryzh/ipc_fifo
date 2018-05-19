CC = gcc
CFLAGS := -Wall -g

LIBRARY_PATH=../lib
INCLUDE_PATH=../include

all: libfifocli.so libfifosrv.so

libfifocli.so: fifoCli.o
	gcc -shared $< -o $@

libfifosrv.so: fifoSrv.o 
	gcc -shared $< -o $@

JHFIFOCli.o: fifoCli.c
	gcc -c $(CFLAGS) -fPIC -I. $< -o $@

JHFIFOSrv.o: fifoSrv.c
	gcc -c $(CFLAGS) -fPIC -I. $< -o $@

clean:
	rm *.o *.so

install:
	cp *.h $(INCLUDE_PATH)
	mv *.so $(LIBRARY_PATH)

uninstall:
	rm -f $(INCLUDE_PATH)/*
	rm -f $(LIBRARY_PATH)/*
