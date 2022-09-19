CC = gcc
CFLAGS = -g -MMD -Wall -L/home/wacfeld/con/clibs -I/home/wacfeld/con/clibs
LIBS = -lmyutil
EXEC = $(shell basename $(CURDIR)).out
OBJECTS = main.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CC} ${OBJECTS} ${CFLAGS} -o ${EXEC} ${LIBS}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

