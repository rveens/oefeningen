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
#define STACK_MAX 50

int *stack;

int main(int argc, const char *argv[])
{
        stack = malloc(sizeof(int) * STACK_MAX);
        while (--argc > 1)
                ;
	// emacs test
        return 0;
}
