#Makefile voor gtkmm test

CC = g++
CFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`

all: assgn3

assgn3: main.o assgn3.o
	$(CC) main.o assgn3.o $(CFLAGS) -o assgn3

main.o: main.cpp 
	$(CC) -c main.cpp $(CFLAGS) 

assgn3.o: assgn3.cpp 
	$(CC) -c assgn3.cpp $(CFLAGS) 

clean:
	rm -rf *o assgn3 *h.gch

run:
	./assgn3
