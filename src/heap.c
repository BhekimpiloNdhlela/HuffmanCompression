#include "../lib/utils.h"

/**
 * Initializes the heap by filling its memory area with 0 bits.
 *
 * @param[in/out]  H     the heap space to initialize
 */
void heap_initialize(Heap *H) {
    H = emalloc(sizeof(struct heap));
    (*H).n = 0;
    memset((*H).a, 0, sizeof(HeapNode) * MAX_HEAP_SIZE);
}

/**
 * iInserts the <code>node</code> into the heap <code>H</code>
 *
 * @param[in]      H     the heap
 * @param[in]      node  the node to insert
 */
void heap_insert(Heap *H, HeapNode *n) {
    int c, p;
    H->a[H->n] = *n;
    c = H->n;
    p = (c - 1) / 2;
    while (p >= 0) {
        if (H->a[p].frequency > H->a[c].frequency) {
            HeapNode hold;
            hold = H->a[p];
            H->a[p] = H->a[c];
            H->a[c] = hold;
            c = p;
            p = (c - 1) / 2;
        } else {
            p = -1;
        }
    }
    H->n = H->n + 1;
}

/**
 * Removes a node from the heap <code>H</code>
 *
 * @param[in]      H     the heap
 * @param[out]     node  the node that was removed
 */
void heap_remove(Heap *H, HeapNode *node) {
    int p, c;
    HeapNode hold;
    if (H->n >= 0) {
        *node = H->a[0];
        H->a[0] = H->a[H->n - 1];
        H->n = H->n - 1;
        p = 0;
        c = 2 * p + 1;
        while (c <= H->n - 1) {
            if (H->a[c].frequency >= H->a[c + 1].frequency)
                c = c + 1;
            if (H->a[c].frequency <= H->a[p].frequency) {
                hold = H->a[c];
                H->a[c] = H->a[p];
                H->a[p] = hold;
                p = c;
                c = 2 * p + 1;
            } else {
                c = H->n;
            }
        }
    }
}
