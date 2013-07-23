/* Exercise 7-3. Revise minprintf to handle more of the other facilities of 
 * printf. */

#include <stdio.h>
#include <stdarg.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
	va_list ap; /* points to ech unnamed arg in turn */
	char *p, *sval;
	int ival;
	double dval;

	va_start(ap, fmt); /* make ap point to 1st unnamed arg */
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
			case 'c':
				ival = va_arg(ap, int);
				printf("%c\n", ival);
				break;
			case 'u':
				ival = va_arg(ap, unsigned int);
				printf("%u\n", ival);
				break;
			case 'd':
			case 'i':
				ival = va_arg(ap, int);
				printf("%d\n", ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap); /* clean up when done */
}

int main(int argc, char *argv[])
{
	minprintf("%u", 12345);
	return 0;
}
