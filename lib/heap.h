#ifndef HEAP_H
#define HEAP_H

#define MAX_HEAP_SIZE 256

typedef struct heap_node HeapNode;
struct heap_node {
	int frequency;
	char c;
	HeapNode *left;
	HeapNode *right;
};

typedef struct heap {
	int n;
	HeapNode a[MAX_HEAP_SIZE];
} Heap;

void heap_initialize(Heap *H);
void heap_remove(Heap *H, HeapNode *node);
void heap_insert(Heap *H, HeapNode *node);
#endif
