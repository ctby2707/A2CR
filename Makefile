CC=gcc

CFLAGS= -Wall  -std=c99 -O3 -g `pkg-config --cflags gtk+-3.0`
LDLIBS= `pkg-config --libs gtk+-3.0` -MMD -g

all: Pac-Man

Pac-Man: Sources/main.o Sources/GTK.o Sources/pac-man.o Sources/ghost.o Sources/pathfinding.o Sources/queue.o
	${CC} -o Pac-Man Sources/main.o Sources/GTK.o Sources/pac-man.o Sources/ghost.o Sources/pathfinding.o Sources/queue.o ${LDLIBS}

.PHONY: clean

clean:
	${RM} Sources/*.o
	${RM} Sources/*.d
	${RM} Rwork/*.o
	${RM} Rwork/*.d
	${RM} Pac-Man
# END
