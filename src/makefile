########################################################
CC=gcc
CFLAGS= -g -Wall
EJS = main
########################################################
OBJECTS = graph.o node.o main.o
########################################################

all: $(EJS)

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

node.o: node.c node.h types.h
	$(CC) $(CFLAGS) -c node.c

graph.o: graph.c graph.h node.h types.h
	$(CC) $(CFLAGS) -c graph.c

main.o: main.c graph.h node.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -rf *.o $(EJS)

vmain:
	valgrind --leak-check=yes --tool=memcheck --leak-check=full --track-origins=yes ./main
