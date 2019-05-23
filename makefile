CC=g++
CFLAGS=-I.
DEPS = linuxMSTPFunctions.h
OBJ = main.o linuxMSTPFunctions.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mstpCallbackTest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)    