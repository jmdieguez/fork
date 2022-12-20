#ifndef FIND_H_
#define FIND_H_
#include <dirent.h>

char *make_path(char *relative_path, char *dir);

void find(DIR *directory,
          char *relative_path,
          char *(*fun_ptr)(const char *, const char *),
          char *needle);

#endif  // FIND_H_