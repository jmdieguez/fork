#include "ps0.h"

// Validate that all characters of a given d_name are digits
int
validate_dir(const char *d_name)
{
	int i = 0;

	while (d_name[i] != '\0') {  // iterate through d_name
		if (!isdigit(d_name[i]))  // if d_name has a non digit char, the directory doesn't refer to a pid
			return 1;  // then : return error
		i++;
	}

	return 0;  // if all chars are digits, then return success
}

// Set comm_name to "/proc/<d_name>/comm
void
set_path_to_comm(char *comm_name, const char *d_name)
{
	strcpy(comm_name, PATH_PROC);
	strcat(comm_name, "/");
	strcat(comm_name, d_name);
	strcat(comm_name, "/comm");
}

int
main(void)
{
	printf("%s", PRINT_PS0);
	FILE *comm_file;

	char *comm_name;
	comm_name = malloc(NAME_LEN);

	DIR *dir = opendir(PATH_PROC);
	struct dirent *entry;

	while ((entry = readdir(dir))) {
		if (entry->d_type == DT_DIR) {
			if (validate_dir(entry->d_name) == 0) {
				set_path_to_comm(comm_name, entry->d_name);
				comm_file = fopen(comm_name, "r");

				// If error while opening or reading comm_file, exit with error code = 1
				if (NULL == comm_file ||
				    !fgets(comm_name, NAME_LEN, comm_file))
					exit(1);

				printf("%7s %s", entry->d_name, comm_name);
				fclose(comm_file);
			}
		}
	}

	free(comm_name);

	return 0;
}
