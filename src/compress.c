#include "../lib/utils.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage ./compress <path to file>\n");
        return EXIT_FAILURE;
    }
    init_compression(argv[1]);
    fprintf(stderr, "successfully compressed input file: <%s.cz> was generated\n", argv[1]);
    return EXIT_SUCCESS;
}

void init_compression(const char *input_file_name)
{
    Heap *heap = emalloc(MAX_HEAP_SIZE * sizeof(Heap));
    FILE *input_file = open_file(input_file_name, "r");

    int i, c, freq[MAX_HEAP_SIZE] = {0};
    int num_chars = 0;
    HuffmanNode *hnode;

    heap_initialize(heap);
    // count the unique characters
    while ((c = fgetc(input_file)) != EOF) freq[c] = freq[c] + 1;
    fclose(input_file);
    
    for (i = 0; i < MAX_HEAP_SIZE; i++) {
        if (!freq[i]) continue;
        HeapNode *node = emalloc(sizeof(HeapNode));
        node->frequency = freq[i];
        node->c = i;
        node->left = NULL;
        node->right = NULL;
        heap_insert(heap, node);
        num_chars = num_chars + 1;
    }

    HeapNode *node = emalloc(sizeof(HeapNode));
    huffman_build_tree(heap, &node);
    hnode = emalloc(MAX_HEAP_SIZE * sizeof(HuffmanNode));
    huffman_initialize_table(hnode);
    huffman_build_table(node, hnode, 0, 0);

    //write the compressed file
    write_compressed(freq, hnode, input_file_name, num_chars);
}
