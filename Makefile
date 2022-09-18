CC = gcc
CFLAGS = -g -MMD -Wall -L/home/wacfeld/con/clibs -I/home/wacfeld/con/clibs
LIBS = myutil
EXEC = $(shell basename $(CURDIR)).out
OBJECTS = main.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CC} ${OBJECTS} ${CFLAGS} -o ${EXEC} -l${LIBS}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

