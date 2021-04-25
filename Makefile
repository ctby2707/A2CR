CC=gcc

CFLAGS= -Wall  -std=c99 -g `pkg-config --cflags gtk+-3.0`
LDLIBS= `pkg-config --libs gtk+-3.0` -MMD -g -lm

all: Pac-Man

Pac-Man: Sources/NeuralNetwork.o Sources/NeuralNetworks_Detections.o Sources/saverfile.o Sources/sigmoid.o Sources/neuron.o Sources/NeuralNetworks_manager.o Sources/main.o Sources/GTK.o Sources/pac-man.o Sources/ghost.o Sources/pathfinding.o Sources/queue.o 
	${CC} -o Pac-Man Sources/main.o Sources/GTK.o Sources/pac-man.o Sources/ghost.o Sources/pathfinding.o Sources/queue.o Sources/NeuralNetwork.o Sources/NeuralNetworks_Detections.o Sources/saverfile.o Sources/sigmoid.o Sources/neuron.o Sources/NeuralNetworks_manager.o ${LDLIBS}

.PHONY: clean

clean:
	${RM} Sources/*.o
	${RM} Sources/*.d
	${RM} Pac-Man
# END
