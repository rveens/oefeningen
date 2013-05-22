/*
 *Exercise 5-10. Write the program expr, which evaluates a reverse Polish 
 *expression from the command line, where each operator or operand is a seperate
 *argument. For example,
 *        expr 2 3 4 + *
 *evaluates 2 x (3+4).
 */

/*
 * Steps:
 * 1 - determine argument character:
 *      if operand, add to stack
 *      if operator, do specific action and remove, add to stack
 * 2 - if no arguments are left, print the top of the stack.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define STACK_MAX 50

void push(int x);
int pop();

int stack[STACK_MAX];
int stackindex = 0;

/* entry point into program */
int main(int argc, const char *argv[])
{
	int c, i;		// temp character, index
	int tempoperand;	// temp operand

	argv++;
	while (--argc > 0)
		while ( *argv && (c = *argv[0]) ) {
			printf("%c\n", c);
			if (c >= '0' && c <= '9') {
				printf("add operation: %d\n", c - '0'); //TODO test
				push(c - '0');
			} else if (stackindex >= 1) {
				switch (c) {
					case '*':
						push(pop() * pop());
						break;
					case '+':
						push(pop() + pop());
						break;
					case '-':
						tempoperand = pop();
						push(pop() - tempoperand);
						break;
					case '/':
						tempoperand = pop();
						if (tempoperand > 0)
							push(pop() / tempoperand);
						else
							printf("error: division by zero!\n");
						break;
				}
			} else
				printf("error: stack empty!\n");
			argv++;
		}

	printf("-------------\n");
	printf("STACK:\n");
	for (i = 0; i < stackindex; i++)
		printf("%d\n", stack[i]);

	return 0;
}

/* push an integer to the stack */
void push(int x)
{
	if (stackindex < STACK_MAX) {
		stack[stackindex++] = x;
	} else
		printf("error: stack full!\n");
}

/* pop an integer from the stack */
int pop()
{
	if (stackindex > 0)
		return stack[--stackindex];
	else 
		printf("error: stack is empty\n");
}
