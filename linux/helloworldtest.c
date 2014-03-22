#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int fd = 0;

#define FILE_TO_ACCESS "/proc/driver/helloworldmem"

int main(int argc, char *argv[])
{
	if (access(FILE_TO_ACCESS, F_OK) == -1) {
		printf("module not loaded.\n");
		goto error;
	}

	char *test = malloc(sizeof(char) * 10000);

	fd = open(FILE_TO_ACCESS, O_RDWR);
	if (fd == -1) {
		printf("error occured: %s\n", strerror(errno));
		goto error;
	}

	/* system calls to device */

	read(fd, test, 1000);
	printf("output: %s\n", test);
	char stufftowrite[] = "KAAS";
	int result = write(fd, stufftowrite, sizeof(stufftowrite));
	if (result < 0) {
		printf("error occured: %s\n", strerror(errno));
		goto error;
	} else 
		printf("amount of bytes written: %d\n", result);

	return 0;

	error:
		return -1;
}
