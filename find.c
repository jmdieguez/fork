#define _GNU_SOURCE

#include "fork.h"
#include "find.h"
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PATH "."
#define MIN_N_PARAMS 2
#define MAX_N_PARAMS 3
#define FLAG_INSENSITIVE "-i"

char *
make_path(char *relative_path, char *dir)
{
	char *aux = malloc(PATH_MAX);
	strcpy(aux, "");
	strcat(aux, relative_path);
	strcat(aux, dir);
	strcat(aux, "/");

	return aux;
}

void
find(DIR *directory,
     char *relative_path,
     char *(*fun_ptr)(const char *, const char *),
     char *needle)
{
	struct dirent *entry;
	while ((entry = readdir(directory))) {
		if (entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name, ".") ==
			            0 ||  // Skip current and superior directories
			    strcmp(entry->d_name, "..") == 0)
				continue;

			DIR *next =
			        fdopendir(openat(dirfd(directory),
			                         entry->d_name,
			                         O_DIRECTORY));  // Recursive find
			find(next,
			     make_path(relative_path, entry->d_name),
			     fun_ptr,
			     needle);
		}
		if ((*fun_ptr)(entry->d_name, needle))  // Print matched file
			printf("%s%s\n", relative_path, entry->d_name);
	}

	closedir(directory);
	free(relative_path);
}

int
main(int argc, char *argv[])
{
	if (argc > MAX_N_PARAMS || argc < MIN_N_PARAMS) {
		fprintf(stderr,
		        "Unexpected n-arguments - use : find [-i] <string> \n");
		return ERROR;
	}

	char *needle;
	char *(*fun_ptr)(const char *,
	                 const char *);  // Pointer to sub-string comparer function

	if (argc == MAX_N_PARAMS && strcmp(argv[1], FLAG_INSENSITIVE) == 0) {
		needle = argv[2];
		fun_ptr = &strcasestr;  // Insensitive
	} else {
		needle = argv[1];
		fun_ptr = &strstr;  // Sensitive
	}

	DIR *directory = opendir(PATH);  // Open current folder
	if (!directory) {
		perror("Error on opendir");
		return ERROR;
	}

	char *relative_path = malloc(PATH_MAX);
	strcpy(relative_path, "./");

	find(directory, relative_path, fun_ptr, needle);

	return SUCCESS;
}
