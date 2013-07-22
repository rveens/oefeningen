/* Exercise 6-5. Write a function undef that will remove a name and definition 
 * from the table maintained by lookup and install. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist {
	struct nlist *next; 	/* next entry in chain */
	char *name;		/* defined name */
	char *defn;		/* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
struct nlist *lookup(char *s);
unsigned hash(char *s);
struct nlist *install(char *name, char *defn);

/* Write a function undef that will remove a name and definition 
 * from the table maintained by lookup and install. */
int undef(char *name)
{
	struct nlist *np, *last;
	int depth = 0;

	for (last = np = hashtab[hash(name)]; np != NULL; np = np->next) {
		depth++;
		if (strcmp(name, np->name)) {
			if (depth == 1)
				hashtab[hash(name)] = np->next;
			else
				last->next = np->next;
			free(np->name);
			free(np->defn);
			free(np);
			return 1;
		}
		last = np;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	install("kaas", "appel");
	printf("%s\n", lookup("kaas")->defn);
	
	return 0;
}

unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np; 	/* found */

	return NULL;			/* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	/* not found */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else 					/* already there */
		free((void *) np->defn); 	/* free previous defn */
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}
