#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void *emalloc(size_t);
char *dec_to_bin(int, int);
void view_code_table(char **);
void view_freq_map(int *, int, int);
void success(const char *, const char *);
FILE *open_file(const char *, const char *);
void write_compressed_file(const char *, char **, int, int, int *);

#endif
