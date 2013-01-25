
/* Exercise 4-4:  Add commands to print the top element of the stack without 
 * to popping, to duplicate it, and to swap the top two elements. Add a command
 * to clear the stack. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> /* for atof() */
#include <ctype.h>

#define MAXOP 	100 /* max size of operand or operator */
#define NUMBER 	'0' /* signal that a number was found */

#define MAXVAL 	100 /* maximum depth of val stack */

#define BUFSIZE 100

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

/* reverse Polish calculator */
int main(int argc, const char *argv[])
{
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case 's':
			swap();
			break;
		case 'd':
			duplicate(); 
			break;
		case 'p':
			printf("\t%.8g\n\n", peek());
			break;
		case 'c':
			clear();
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

void swap(void)
{
	int t = val[0];
	val[0] = val[1];
	val[1] = t;
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
