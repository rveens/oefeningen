
/*
 *Add access to library functions like sin, exp and pow. See <math.h> in 
 *Appendix B, Section 4.
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

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

/* 4-4: Extra commands */
void clear(void);
double peek(void);
void duplicate(void);
void swap(void);

/*4-5 handle system functions*/
void deterfunc(char s[]);

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
			printf("\t%.8g\n\n", pop());
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
	int i, c, tc;

	i = 0;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if(isalpha(c)) { // Found alfanumeric.
		while ((isalpha(s[++i] = c = getch())) )
			;
		s[i] = '\0';
		return ALPHANUMERIC;
	}
	if (!isdigit(c) && c != '.' && c != '-') 
		return c;

	if( c == '-') {
		int temp = 0;
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
	} else if (strcmp(s, "s") == 0) {
		swap();
	} else if (strcmp(s, "d") == 0) {
		duplicate(); 
	} else if (strcmp(s, "p") == 0) {
		printf("\t%.8g\n\n", peek());
	} else if (strcmp(s, "c") == 0) {
		clear();
	}
}

int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
