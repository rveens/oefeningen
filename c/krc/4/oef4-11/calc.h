#define NUMBER 	 	'0' /* signal that a number was found */
#define ALPHANUMERIC 	'a' /* signal that a alphanumeric string was found */

//Stack functions
void push(double);
double pop(void);

//Getch
int getch(void);
void ungetch(int);
static int getline1(char s[]);

//Getop
int getop(char []);
