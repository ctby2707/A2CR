# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0` -MMD
CFLAGS= -Wall  -std=c99 -O3 -g
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0`  -lm -ldl

all: main

main: Sources/main.o Sources/GTK.o Sources/pac-man.o Sources/ghost.o Sources/pathfinding.o
	${CC} Sources/main.o Sources/GTK.o Sources/pac-man.o -o Pac-Man Sources/ghost.o Sources/pathfinding.o ${LDLIBS} 



clean:
	${RM} Sources/*.o
	${RM} Sources/*.d
	${RM} Rwork/*.o
	${RM} Rwork/*.d
	${RM} Pac-Man
# END
