/* Exercise 7-4. Write a private version of scanf analogous to minprintf from 
 * the previous section. */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* minscanf: minimal scanf with variable argument list */
void minscanf(char *fmt, ...)
{
	va_list ap; /* points to ech unnamed arg in turn */
	char *p;
	void *output;

	va_start(ap, fmt); /* make ap point to 1st unnamed arg */
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}

		switch (*++p) {
			case 'c':
				output = va_arg(ap, char *);
				scanf("%c", (char *)output);
				break;
			case 'u':
				output = va_arg(ap, unsigned int *);
				scanf("%u", (unsigned int *)output);
				break;
			case 'd':
			case 'i':
				output = va_arg(ap, int *);
				scanf("%d", (int *)output);
				break;
			case 'f':
				output = va_arg(ap, float *);
				scanf("%f", (float *)output);
				break;
			case 's':
				output = va_arg(ap, char *);
				while (scanf("%s", (char *)output) == 1)
					;
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
	char *s = malloc(sizeof(char *) * 100);

	minscanf("%s", s);
	printf("%s", s);

	return 0;
}
