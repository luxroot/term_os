CC = gcc -std=c11

main: process.o queue.o main.c
	$(CC) main.c -o main.o process.o queue.o

process.o:
	$(CC) process.c -c -o process.o

queue.o:
	$(CC) queue.c -c -o queue.o

clean:
	rm *.o
