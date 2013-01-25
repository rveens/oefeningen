
/*Exercise 4-11. 
 * Modify getop so that it doesn't need to use ungetch. Hint: use an internal 
 * static variable. 
 */
#include <stdio.h>
#include <math.h> /* for atof() */
#include <stdlib.h>
#include <string.h>
#include "calc.h"

#define MAXOP 		100 /* max size of operand or operator */

/* 4-4: Extra commands */
void clear(void);
double peek(void);
void duplicate(void);
void swap(void);

/*4-5 handle system functions*/
void deterfunc(char s[]);

/*4-6 variables*/
static int varamount = 0; 	// First available empty position.
struct pcvar {
	int value;
	char name[];
};
static struct pcvar var[MAXOP];
int getvar(char name[]);
void setvar(char var[], int val);
static int removechar(char s[], int pos); 
/*4-7 ungets(s) */
void ungets(char s[]);

/* reverse Polish calculator */
int main(int argc, const char *argv[])
{
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF) {
		switch (type) {
		case ALPHANUMERIC:
    			deterfunc(s);
			break;
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else 
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			if(op2 != 0.0)
				push((double) ((int)pop() % (int)op2));
		else 
				printf("error: zero divisor\n");
			break;
		case '\n':
			op2 = pop();
			setvar("last", op2);
			printf("\t%.8g\n\n", op2);

			break;
		default:
			printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}


/*Assign the variable to the last value on the stack*/
void setvar(char variable[], int val)
{
	int i;
	//TODO: save variables. struct?
	// Look if the variable already exists:
	for(i = 0; i < varamount; i++)
		if(strcmp(var[i].name, variable) == 0) {
			var[i].value = val;
			return;
		}
	// Variable doesn't exist yet. Create a new one.
	if (varamount < MAXOP) {
		strcpy(var[varamount].name, variable);
		var[varamount].value = val;
		varamount++;
	}
}

int getvar(char name[])
{
	int i;

	for(i = 0; i < varamount; i++)
		if(strcmp(var[i].name, name) == 0) {
			return var[i].value;
		}
	printf("Variable not found.\n");
	return -1;
}

static int removechar(char s[], int pos)
{
	int i, c;

	if(pos < 0 && pos <= strlen(s))
		return -1;
	for(i = pos; i < strlen(s); i++)
		s[i] = s[i+1];
	return 1;
}

/*Add access to library functions like sin, exp and pow. See <math.h> in */
void deterfunc(char s[])
{
	if (strcmp(s, "sin") == 0) {
		push(sin(pop()));
	} else if (strcmp(s, "exp") == 0) {
		push(exp(pop()));
	} else if (strcmp(s, "pow") == 0) {
		int t = pop();
		push(pow(pop(), t));
	} else if (strcmp(s, "swap") == 0) {
		swap();
	} else if (strcmp(s, "duplicate") == 0) {
		duplicate(); 
	} else if (strcmp(s, "peek") == 0) {
		printf("\t%.8g\n\n", peek());
	} else if (strcmp(s, "clear") == 0) {
		clear();
	} else if (s[0] == '=') {
		// Assign the last number on the stack to the variable.
		removechar(s, 0);
		setvar(s, peek());
	} else	 // Must be a variable then.
		push((double)getvar(s));
}

/*
 * Write a routine unget(s) that will push back an entire string onto the 
 * input. Should ungets know about buf and bufp, or should it just use ungetch?
 */
void ungets(char s[])
{
	int i, size;

	size = strlen(s);

	while (i > 0)
		ungetch(s[--i]);
}
