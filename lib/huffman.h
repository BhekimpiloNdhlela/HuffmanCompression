#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdlib.h>
#include "heap.h"

typedef struct huffman_node {
	int huffman_code;
	int bit_size;
} HuffmanNode;

void huffman_build_tree(Heap *h, HeapNode **t);
void huffman_initialize_table(HuffmanNode *t);
void huffman_build_table(HeapNode *root, HuffmanNode *t, int code, int size);
void huffman_show_table(HuffmanNode *t);
void huffman_show_tree(HeapNode *t, int l);
void huffman_build_tree(Heap *h, HeapNode **t);
void huffman_initialize_table(HuffmanNode *t);
void huffman_build_table(HeapNode *root, HuffmanNode *t, int code, int size);

#endif
