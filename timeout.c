//
// Created by manu on 06/12/22.
//

#include "timeout.h"

#define N_ARGS 3
// argv[timeout, n_secs, bin, ... ] -> (...) = bin args

timer_t timerid;
struct itimerspec timer = { 0 };

void
initialize_timer(int n_secs)
{
	timer.it_value.tv_sec = n_secs;

	struct sigevent sigev;

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGTERM;

	if (timer_create(CLOCK_REALTIME, &sigev, &timerid) == ERROR ||
	    timer_settime(timerid, 0, &timer, (struct itimerspec *) NULL) == ERROR)
		exit(1);
}

void
initialize_bin(int argc, char *argv[], char *bin_argv[])
{
	int j = 0;
	for (int i = 2; i < argc; i++) {
		bin_argv[j] = argv[i];
		j++;
	}
	bin_argv[j] = NULL;
}

int
main(int argc, char *argv[])
{
	if (argc < N_ARGS)
		return ERROR;

	int n_secs = atoi(argv[1]);
	char *bin = argv[2];

	char *bin_argv[argc - 1];
	initialize_bin(argc, argv, bin_argv);  // Initialize bin argv for execvp

	int f = fork();
	if (f == 0) {
		if (execvp(bin, bin_argv) == ERROR) {
			perror("Error while exec");
			return ERROR;
		}
	} else {
		initialize_timer(n_secs);
		wait(NULL);
		if (timer_delete(timerid) == ERROR)
			exit(1);
	}

	return 0;
}