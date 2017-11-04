#include "huffman.h"
void c_huffman_build_tree(Heap *h, HeapNode **t)
{  
    while ((*h).n != 0) {
        if ((*h).n == 1) {
            HeapNode x;
            c_heap_remove(h, &x);
            (**t).frequency = x.frequency;
            (**t).c = x.c;
            (**t).right = x.right;
            (**t).left = x.left;
        } else {
            HeapNode *x = emalloc(sizeof(HeapNode));
            HeapNode *y = emalloc(sizeof(HeapNode));
            HeapNode *z = emalloc(sizeof(HeapNode));
            c_heap_remove(h, x);
            c_heap_remove(h, y);
            (*z).left = x;
            (*z).right = y;
            (*z).frequency = (*x).frequency + (*y).frequency;
            c_heap_insert(h, z);
        }
    }
}

void c_huffman_initialize_table(HuffmanNode *t)
{
    int c;
    for (c = 0; c < MAX_HEAP_SIZE; c++) {
        t[c].huffman_code = 0;
        t[c].bit_size = 0;
    }
}

void c_huffman_build_table(HeapNode *root, HuffmanNode *t, int c, int s)
{
    if (root->left == NULL && root->right == NULL) {
        int i = (unsigned char)root->c;
        t[i].bit_size = s + 1;
        t[i].huffman_code = c + 1;
        return;
    } else { 
        if (root->right) {
            c_huffman_build_table(root->right, t, c * 2, s + 1);
        }
        if (root->left) {
            c_huffman_build_table(root->left, t, (c * 2) + 1, s + 1);
        }
    }
}
