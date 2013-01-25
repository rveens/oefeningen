calculator: main.o getop.o getch.o stack.o
	gcc main.o getop.o getch.o stack.o -o calculator -lm 

main.o: main.c calc.h
	gcc -c main.c
	
getop.o: getop.c calc.h
	gcc -c getop.c

stack.o: stack.c calc.h
	gcc -c stack.c

getch.o: getch.c calc.h
	gcc -c getch.c

clean:
	rm -rf *o calculator
