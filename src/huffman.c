#include "../lib/utils.h"

void huffman_build_tree(Heap *h, HeapNode **t)
{
    while ((*h).n) {
        if ((*h).n == 1) {
            HeapNode x;
            heap_remove(h, &x);
            (**t).frequency = x.frequency;
            (**t).c = x.c;
            (**t).right = x.right;
            (**t).left = x.left;
        } else {
            HeapNode *x = emalloc(sizeof(HeapNode));
            HeapNode *y = emalloc(sizeof(HeapNode));
            HeapNode *z = emalloc(sizeof(HeapNode));
            heap_remove(h, x);
            heap_remove(h, y);
            (*z).left = x;
            (*z).right = y;
            (*z).frequency = (*x).frequency + (*y).frequency;
            heap_insert(h, z);
        }
    }
}

void huffman_initialize_table(HuffmanNode *t)
{
    int c;
    for (c = 0; c < MAX_HEAP_SIZE; c++) {
        t[c].huffman_code = 0;
        t[c].bit_size = 0;
    }
}

void huffman_build_table(HeapNode *root, HuffmanNode *node, int code, int size)
{
    if (root->right) {
        huffman_build_table(root->right, node, (code << 1) + 1, size + 1);
    }
    if (root->left) {
        huffman_build_table(root->left, node, (code << 1), size + 1);
    }
    if (root->right == NULL && root->left == NULL) {
        node[(int) root->c].huffman_code = code;
        node[(int) root->c].bit_size = size;
    }
}
