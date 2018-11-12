#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "heap.h"
#include "huffman.h"

FILE *open_file(const char *, const char *);
void *emalloc(size_t);
void init_compression(const char *);
void write_compressed(int *, HuffmanNode *, const char *, int);

#endif
