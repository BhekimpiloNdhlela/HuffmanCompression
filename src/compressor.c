#include "utilities.c"
#include "heap_c.c"
#include "huffman_c.c"

/* function proto-types */
void compress(int *, const char *);
void set_char_frequency(const char *, int *);
void make_huffman_code(HuffmanNode *, char **);

/* static variables*/
static unsigned int total_chars = 0;    /* the total number of chars in the input file */
static unsigned int number_chars = 0;   /* the number of distinct  chars in input file */

/**
 * The Huffman compressor client, calls the get_char_frequency and other relevant functions before
 * initiating the compression process.
 *
 * @param[in] argc    the length of the std in
 * @param[in] argv    the input file
 */
int main(int argc, char **argv)
{
    int frequency[MAX_HEAP_SIZE] = { 0 };
    set_char_frequency(argv[1], frequency);
    return EXIT_SUCCESS;
}

/**
 * Makes the char frequency table with the aid of a struct defined in the utilities.h
 * the structure is an array that stores both the char and the frequency of individual
 * chars that are present in the file being compressed.
 *
 * @param[in]       input_file_name      the name of the input file.
 * @param[in/out]   frequency map        the frequency map for chars.
 */
void set_char_frequency(const char *input_file_name, int *frequency)
{
    FILE *input_file = open_file(input_file_name, "r");
    unsigned int c;
    while ((c = fgetc(input_file)) != EOF) {
        total_chars  = total_chars + 1;
        frequency[c] = frequency[c] + 1;
        number_chars = (frequency[c] == 1) ? number_chars + 1 : number_chars;
    }
    fclose(input_file);
    compress(frequency, input_file_name);
}

/**
 * The heart of the Huffman compressor, initiates the compression of the input filie and
 * also build both the Heap and the huffman table, of the chars in the input file.
 *
 * @param [in] char_frequency_ptr    char and frequency of individual chars
 */
void compress(int *char_freq, const char *in_name)
{
    HuffmanNode *t = emalloc(sizeof(HuffmanNode) * MAX_HEAP_SIZE);
    char *fmap[MAX_HEAP_SIZE];
    HeapNode *HN;
    Heap H;
    int i;
    /* initialise the heap and also the table and the huffman tree. */
    heap_initialize(&H);
    for (i = 0; i < MAX_HEAP_SIZE; i++) {
        if (char_freq[i] != 0) {
            HN = emalloc(sizeof(HeapNode));
            HN->frequency = char_freq[i];
            HN->c = i;
            heap_insert(&H, HN);
        }
    }
    huffman_initialize_table(t);
    huffman_build_tree(&H, &HN);
    huffman_build_table(HN, t, 0, 0);
    /* making the huffman encoding with the aid of dec_to_bin from utilities.c */
    for ( i = 0; i < MAX_HEAP_SIZE; i++) {
        fmap[i] = (t[i].bit_size != 0) ? dec_to_bin(t[i].huffman_code, t[i].bit_size) : '\0';
    }
    write_compressed_file(in_name, fmap, total_chars, number_chars, char_freq);
    view_code_table(fmap);
    free(t);
}
