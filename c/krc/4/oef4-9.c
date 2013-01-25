
/*
 * Exercise 4-9
 * Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what
 * their properties ought to be if an EOF is pushed back, then implement your
 * design.
 * TODO fix string input bug.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> /* for atof() */
#include <ctype.h>
#include <string.h>

#define MAXOP 		100 /* max size of operand or operator */
#define NUMBER 	 	'0' /* signal that a number was found */
#define ALPHANUMERIC 	'a' /* signal that a alphanumeric string was found */
#define MAXVAL 		100 /* maximum depth of val stack */

#define BUFSIZE 	100

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0;		/* next free stack position */
double val[MAXVAL]; 	/* value stack */

char buf = '\0';	/* buffer for ungetch */

/* 4-4: Extra commands */
void clear(void);
double peek(void);
void duplicate(void);
void swap(void);

/*4-5 handle system functions*/
void deterfunc(char s[]);

/*4-6 variables*/
int varamount = 0; 	// First available empty position.
struct pcvar {
	int value;
	char name[];
};
struct pcvar var[BUFSIZE];
int getvar(char name[]);
void setvar(char var[], int val);
int removechar(char s[], int pos);

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

/* push: push f onto value stack */
void push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can`t push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c, tc, temp;

	i = 0;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if(c == '=') {
		c = temp = s[++i] = getch();
		if(!isalpha(temp)) {
			ungetch(temp);
			c = s[--i] = '=';
		}
	}
	if(isalpha(c)) { // Found alfanumeric.
		while ((isalpha(s[++i] = c = getch())) )
			;
		s[i] = '\0';
		return ALPHANUMERIC;
	}
	if (!isdigit(c) && c != '.' && c != '-') 
		return c;

	if( c == '-') {
		temp = 0;
		if( !isdigit( (temp = getch()) ) ) {
			ungetch(temp);
			return c; // return '-'
		} else
			s[++i] = c = temp; // c becomes the int.
	}

	if (isdigit(c)) 	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')		/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

/*clear the stack of every item.*/
void clear(void)
{
	/*while the next free stack position isn't the first, keep popping.*/
	while(sp != 0)
		pop();
}

/*look at the first element, return 0 if the stack is empty. The stack remains the same.*/
double peek(void)
{
	return val[0];
}

/*Duplicate the first stack entry.*/
void duplicate(void)
{
	int i = sp;

	while(i > 0)
		val[i--] = val[i-1];
	sp++;
}

/*Swap the first two elements*/
void swap(void)
{
	int t = val[0];
	val[0] = val[1];
	val[1] = t;
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
	if (varamount < BUFSIZE) {
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

int removechar(char s[], int pos)
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

int getch(void) /* get a (possibly pushed back) character */
{
	int retval;

	if(buf != '\0') {
		retval = buf;
		buf = '\0';
		return retval;
	}
	else
		return getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (buf != '\0')
		printf("ungetch: too many characters\n");
	else
		buf = c;
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
