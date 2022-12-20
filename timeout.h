//
// Created by manu on 06/12/22.
//

#ifndef SISOP_2022B_DIEGUEZ_TIMEOUT_H
#define SISOP_2022B_DIEGUEZ_TIMEOUT_H

#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include "fork.h"
#include <sys/wait.h>
#include <stdbool.h>

void initialize_timer(int n_secs);
void initialize_bin(int argc, char *argv[], char *bin_argv[]);

#endif  // SISOP_2022B_DIEGUEZ_TIMEOUT_H
