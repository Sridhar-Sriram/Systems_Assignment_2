CC = gcc
CCFLAGS = -Wall

all: memgrind mymalloc

 memgrind: memgrind.c
 	$(CC) $(CCFLAGS) -g -o memgrind memgrind.c

mymalloc: mymalloc.c mymalloc.h
	$(CC) $(CCFLAGS) -g -o mymalloc mymalloc.c mymalloc.h 

clean:
	rm mymalloc memgrind