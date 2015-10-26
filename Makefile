CC = gcc
CFLAGS = -c -Wall

all: a2-ece650

a2-ece650: graph.o queue.o search.o a2-ece650.o 
	$(CC) graph.c queue.c search.c a2-ece650.c -o a2-ece650

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) graph.c

queue.o: queue.c queue.h search.h
	$(CC) $(CFLAGS) queue.c

search.o: search.c search.h graph.h queue.h
	$(CC) $(CFLAGS) search.c

a2-ece650.o: a2-ece650.c graph.h search.h queue.h
	$(CC) $(CFLAGS) a2-ece650.c

clean:
	rm *o a2-ece650 
