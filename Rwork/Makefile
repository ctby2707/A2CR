CC = gcc
CFALGS = -Wall - Wextra

all: test

test: test.o pathfinding.o fifo.o
test.o: test.c pathfinding.h
pathfinding.o: pathefinding.c pathfinding.h fifo.h
fifo.o: fifo.c fifo.h cell.h

.PHONY: clean

clean:
	${RM} test.o pathfinding.o fifo.o
