#Name: Tara Eicher
#WSU ID: z847x563

#Makefile for 8 puzzle A* search. 
# 
#Compiler: GCC 

CC=gcc -Wall

all: aStarSearch

aStarSearch: aStarSearch.c aStarSearch.h
	$(CC) -o eightPuzzle aStarSearch.c aStarSearch.h

clean: 
	rm -f *.o 
