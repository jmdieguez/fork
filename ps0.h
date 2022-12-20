//
// Created by manu on 06/12/22.
//

#ifndef SISOP_2022B_DIEGUEZ_PS0_H
#define SISOP_2022B_DIEGUEZ_PS0_H

#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include "fork.h"

#define PRINT_PS0 "    PID COMMAND\n"
#define PATH_PROC "/proc"
#define NAME_LEN 256

int validate_dir(const char *d_name);
void set_path_to_comm(char *comm_name, const char *d_name);

#endif  // SISOP_2022B_DIEGUEZ_PS0_H
