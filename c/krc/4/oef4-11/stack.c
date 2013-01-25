#include <stdio.h>
#include "calc.h"

#define MAXVAL 		100 	 /* maximum depth of val stack */

static int sp = 0;		/* next free stack position */
static double val[MAXVAL]; 	/* value stack */

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
