CC = gcc
LDLIBS = -fsanitize=address
CPPFLAGS=
CFLAGS = -Wall -Wextra -g

all: main

main: main.o pathfinding3.o ghost.o queue.o

.PHONY: clean

clean:
	${RM} main main.o pathfinding.o ghost.o
