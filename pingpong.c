#include "fork.h"
#include "pingpong.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

void
describe(int fork)
{
	printf("Donde fork me devuelve %d:\n", fork);
	printf("  - getpid me devuelve: %d\n", getpid());
	printf("  - getppid me devuelve: %d\n", getppid());
}

int
main(void)
{
	int fds_parent[2];  // Parent to child
	int fds_child[2];   // Child to parent

	if (pipe(fds_child) == ERROR || pipe(fds_parent) == ERROR) {
		perror("Error while creating pipes");
		return ERROR;
	}

	printf("Hola, soy PID %d:\n", getpid());
	printf("  - primer pipe me devuelve: [%d, %d]\n",
	       fds_parent[0],
	       fds_parent[1]);
	printf("  - segundo pipe me devuelve: [%d, %d]\n\n",
	       fds_child[0],
	       fds_child[1]);

	int i = fork();  // Spawn child process

	if (i == ERROR) {
		fprintf(stderr, "Error while forking\n");
		return ERROR;
	} else if (i > 0) {
		describe(i);

		srandom(time(NULL));
		int random_send = random();
		printf("  - random me devuelve: %d\n", random_send);

		printf("  - envío valor %d a través de fd=%d\n\n",
		       random_send,
		       fds_parent[1]);

		if (write(fds_parent[1], &random_send, sizeof(random_send)) ==
		    ERROR) {  // Send -1, informing reading ends
			perror("Error while writing");
			return ERROR;
		}

		wait(NULL);  // Wait for child process to end

		if (read(fds_child[0], &random_send, sizeof(random_send)) ==
		    ERROR) {
			perror("Error while reading");
			return ERROR;
		}

		printf("Hola, de nuevo PID %d:\n", getpid());
		printf("  - recibí valor %d vía fd=%d\n",
		       random_send,
		       fds_child[0]);

		close(fds_parent[0]);  // Close parent to child pipe
		close(fds_parent[1]);
	} else {
		int random_recv;
		if (read(fds_parent[0], &random_recv, sizeof(random_recv)) ==
		    ERROR) {
			perror("Error while reading");
			return ERROR;
		}
		describe(i);

		printf("  - recibo valor %d vía fd=%d\n",
		       random_recv,
		       fds_parent[0]);
		printf("  - reenvío valor en fd=%d y termino\n\n", fds_child[1]);

		if (write(fds_child[1], &random_recv, sizeof(random_recv)) ==
		    ERROR) {
			perror("Error while writing");
			return ERROR;
		}

		close(fds_child[0]);  // Close child to parent pipe
		close(fds_child[1]);
	}

	return SUCCESS;
}
