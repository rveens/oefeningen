#include <stdio.h>

int main(int argc, char *argv[]) {

	int i = 0;
	while(i < 5) {
		printf("%d: Hello world.\n", i + 1);
		i++;
	}
	return 0;
}
