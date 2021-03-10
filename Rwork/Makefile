CC = gcc
CFALGS = -Wall - Wextra -g

all: main

main: main.o pathfinding.o
main.o: main.c pathfinding.h
pathfinding.o: pathfinding.c pathfinding.h

.PHONY: clean

clean:
	${RM} main main.o pathfinding.o
