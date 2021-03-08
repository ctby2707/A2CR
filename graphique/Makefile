# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0` -MMD
CFLAGS= -Wall -Wextra  -std=c99 -O3 -lm -ldl 
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0`  -lm -ldl

main: main.o gui.o



clean:
	${RM} *.o
	${RM} *.d
	${RM} main
# END
