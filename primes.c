#include "fork.h"
#include "primes.h"
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <errno.h>

void
primes(int array[], int n, int size)
{
	if (size == 0)
		return;

	int fds[2];
	if (pipe(fds) == ERROR) {
		perror("Error while creating pipes");
		return;
	}

	int f = fork();
	if (f == ERROR) {
		perror("Error while forking");
		return;
	} else if (f > 0) {
		for (int i = 0; i < size; i++)  // Send numbers
			if (write(fds[1], &(array[i]), sizeof(int)) < 0) {
				perror("Error while writing");
				return;
			}

		int send = -1;
		if (write(fds[1], &send, sizeof(send)) ==
		    ERROR) {  // Send -1, informing reading ends
			{
				perror("Error while writing");
				return;
			}
		}

		wait(NULL);
	} else {
		int filter;  // Read n-filter
		if (read(fds[0], &filter, sizeof(filter)) == ERROR) {
			perror("Error while reading");
			return;
		}
		printf("primo %d\n", filter);

		int recv;
		int counter = 0;

		while (read(fds[0], &recv, sizeof(recv)) > 0) {  // Read the numbers
			if (recv == -1) {
				close(fds[1]);  // Once reading ends, we can close pipes
				close(fds[0]);
				break;
			}
			if (recv % filter != 0)  // Filter the numbers
				array[counter++] = recv;
		}

		if (pow(filter, 2) < n) {  // Condition to keep forking
			int aux[counter];
			for (int i = 0; i < counter;
			     i++)  // Migrating numbers to a smaller array
				aux[i] = array[i];
			primes(aux, n, counter);
		}

		else {
			for (int i = 0; i < counter;
			     i++)  // Print resting values, end algorithm
				printf("primo %d\n", array[i]);
			return;
		}
	}
}

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "2 arguments expected, %d received. Example: ./primes 35\n", argc);
		return 1;
	}

	int n = atoi(argv[1]);
	int array[n - 2];

	int index = 0;

	for (int i = 2; i < n + 1; i++)
		array[index++] = i;

	primes(array, n, n - 2);

	return SUCCESS;
}