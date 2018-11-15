#include "../lib/utils.h"

/**
 * Builds a Huffman tree <code>t</code> by consuming the minheap <code>h</code>.
 * does not construct the minheap of character frequencies; instead the minheap
 * is passed as <code>h</code>.
 *
 * @param[in/out] h     the minheap constructed to character frequencies
 * @param[out]    t     the root of the Huffman tree
 */
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

/**
 * Initializes the Huffman table by filling its memory area with 1 bits.  This
 * function assumes that its called has already allocated space for
 * <code>t</code> by a call to <code>malloc</code>.  It uses <code>malloc</code>
 * to allocate space for heap nodes.
 *
 * @param[in/out] t     a pointer to the space allocated for the Huffman table
 */
void huffman_initialize_table(HuffmanNode *t)
{
    int c;
    for (c = 0; c < MAX_HEAP_SIZE; c++) {
        t[c].huffman_code = 0;
        t[c].bit_size = 0;
    }
}

/**
 * Builds the Huffman table by recursively visiting nodes in-order in a Huffman
 * tree.
 *
 * @param[in]     root  the current node to visit; to be called from the main
 *                      routine with a Huffman tree built by
 *                      <code>huffman_build_tree</code>
 * @param[in/out] t     the Huffman table (an array)
 * @param[in]     code  the partial bitstring, determined by the left-right 1-0
 *                      label of the Huffman tree traversal; to be called from
 *                      the main routine with <code>0</code>
 * @param[in]     size  the current length of the bitstring; to be called from
 *                      the main routine with <code>0</code>
 */
void huffman_build_table(HeapNode *root, HuffmanNode *node, int code, int size)
{
    if (root->right) {
        huffman_build_table(root->right, node, (code << 1) + 1, size + 1);
    }
    if (root->left) {
        huffman_build_table(root->left, node, (code << 1), size + 1);
    }

    //disclaimer: help from CJ's
    if (root->right == NULL && root->left == NULL) {
        node[(int) root->c].huffman_code = code;
        node[(int) root->c].bit_size = size;
    }
}
