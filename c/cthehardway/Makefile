CFLAGS= -Wall -Wextra -g

# Project 'ex3' heeft het bestand ex3.o nodig voor het linken.
cthehardway: ex6.o ex5.o ex3.o ex1.o ex7.o
	cc ex1.o -o ex1
	cc ex3.o -o ex3
	cc ex5.o -o ex5
	cc ex6.o -o ex6
	cc ex7.o -o ex7

# Bestand 'ex1.o' heeft het bestand ex1.c nodig. 
ex1.o: ex1.c
	cc -c ex1.c
# Bestand 'ex3.o' heeft het bestand ex3.c nodig om het o bestand te maken (compile -> assemble -> link)
ex3.o: ex3.c
	cc -c ex3.c
ex5.o: ex5.c
	cc -c ex5.c
ex6.o: ex6.c
	cc -c ex6.c
ex7.o: ex7.c
	cc -c ex7.c

clean:
	rm -f ex3.o
	rm -f ex1.o
	rm -f ex5.o
	rm -f ex6.o
	rm -f ex7.o
