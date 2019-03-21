#include "../lib/utils.h"

/**
 * emalloc equivalent, dont have to check if memory was allocated successfully
 * in the client code.
 *
 * @param[in]   size      the size needed from the heap in bytes.
 * @param[out]  mem_add   the address of allocated space in the heap.
 */
void *emalloc(size_t requested_bytes) {
    void *allocated;
    if ((allocated = malloc(requested_bytes)) == NULL) {
        fprintf(stderr, ".:size of <%u bytes> failed\n", requested_bytes);
        exit(EXIT_FAILURE);
    }
    return allocated;
}

/**
 * open file and then check if it was opened successfully. the client does not have
 * to check if the file was opended successfully.
 *
 * @param[in]    filename    the name of the file name to be opened.
 * @param[in]    mode        the mode of which the file is to be opened in.
 * @return[out]  file_ptr    the pointer of opened file
 */
FILE *open_file(const char *filename, const char *mode) {
    FILE *file;
    if ((file = fopen(filename, mode)) == NULL) {
        fprintf(stderr, ".:failed to open file <%s>\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

/**
 * the file that writes the compressed file.
 *
 * @param[in]  in_name   name of input file.
 * @param[in]  fmap      the map with the huffman codes.
 * @param[in]  tchars    total chars in file.
 * @param[in]  nchars    number of unique chars.
 * @param[in]  freq      frequency map of the chars is the file.
 */
void write_compressed(int *freq, HuffmanNode *hnode, const char *input_file_name, int num_chars) {
    int bit_size = 0;
    char buffer = 0;
    FILE *input_file, *output_file;
    int c, i;
    char output[100];
    sprintf(output, "%s.cz", input_file_name);
    output_file = open_file(output, "w");

    for (i = 0; i < 4; i++) {
        fprintf(output_file, "%c", (char) num_chars);
        num_chars >>= 8;
    }

    for (i = 0; i < MAX_HEAP_SIZE; i++) {
        int j, freq_binary;
        if ((freq_binary = freq[i]) == 0) continue;
        fprintf(output_file, "%c", (char) i);
        for (j = 0; j < 4; j++) {
            fprintf(output_file, "%c", (char) freq_binary);
            freq_binary >>= 8;
        }
    }

    input_file = open_file(input_file_name, "r");
    while ( (c = fgetc(input_file)) != EOF) {
        for (i = hnode[c].bit_size - 1; i >= 0; i--) {
            if (((hnode[c].huffman_code >> i) % 2) == 1) {
                buffer = (buffer | (1 << (7 - bit_size)));
            }
            bit_size = bit_size + 1;

            if (bit_size == 8) {
                fprintf(output_file, "%c", buffer);
                bit_size = 0;
                buffer = 0;
            }
        }
    }

    if (bit_size) fprintf(output_file, "%c", buffer);

    fclose(output_file);
    fclose(input_file);
}
