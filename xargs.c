#include "fork.h"
#include "xargs.h"
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#ifndef NARGS
#define NARGS 4
#endif

void
clean(char *v[])
{
	for (int i = 1; i < (NARGS + 1); i++) {
		free(v[i]);
		v[i] = NULL;
	}
}

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Error: Expected 2 arguments, %d received. Use: ./xargs <bin>\n", argc);
		return ERROR;
	}

	char *line = NULL;
	size_t args = 0;
	ssize_t nread;

	char *lines[NARGS + 2];  // [bin, arg1, arg2, arg3, arg4, NULL]

	char *bin = malloc(strlen(argv[1]));
	strcpy(bin, argv[1]);


	for (int i = 0; i < NARGS + 2; i++)  // Initialize array indexes on NULL
		lines[i] = NULL;

	lines[0] = bin;  // Set bin as first index

	bool flag = true;
	while (flag) {
		size_t len = 0;
		nread = getline(&line, &len, stdin);

		if (nread <= 0)
			flag = false;
		else {
			strtok(line, "\n");  // Get rid of endl
			lines[++args] = line;
		}

		if (((args) % NARGS == 0) || !flag) {
			int f = fork();

			if (f == 0) {
				if (execvp(bin, lines) == ERROR) {
					perror("Error while exec");
					return ERROR;
				}
			} else {
				if (wait(&f) == ERROR) {
					perror("Error while wait");
					return ERROR;
				}
			}
			clean(lines);
			args = 0;
		}
	}

	free(bin);
	return SUCCESS;
}