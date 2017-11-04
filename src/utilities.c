#include "utilities.h"

/**
 * convert decimal number to binary.
 *
 * @param[in]  n      the number in binary format
 * @param[in]  size   the size of the huffman code
 */
char *dec_to_bin(int n, int size)
{
    int k, j, i = 0;
    char *code = emalloc(size);
    for (j = size ; j >= 0; j--)  {
        k = n >> j;
        code[i++] = (k & 1) ? 1 + '0': 0 + '0';
    }
    code[i] = '\0';
    return  code;
}


/**
 * emalloc equivalent, dont have to check if memory was allocated successfully
 * in the client code.
 *
 * @param[in]   size      the size needed from the heap in bytes.
 * @param[out]  mem_add   the address of allocated space in the heap.
 */
void *emalloc(size_t size)
{
	void *mem_address;
	if ((mem_address = malloc(size)) == NULL) {
		fprintf(stderr,"error: malloc of %lu bytes failed:", size);
		exit(EXIT_FAILURE);
	}
	return mem_address;
}


/**
 * open file and then check if it was opened successfully. the client does not have
 * to check if the file was opended successfully.
 *
 * @param[in]    filename    the name of the file name to be opened.
 * @param[in]    mode        the mode of which the file is to be opened in.
 * @return[out]  file_ptr    the pointer of opened file
 */
FILE *open_file(const char *filename, const char *mode)
{
	FILE *file_ptr;
	if ((file_ptr = fopen(filename, mode)) == NULL) {
		fprintf(stderr, "error: could not read file: <%s>\n", filename);
		exit(EXIT_FAILURE);
	}
	return file_ptr;	
}


/**
 * the file that writes the compressed file. 
 *
 * @param[in]  in_name   name of input file.
 * @param[in]  fmap 	 the map with the huffman codes.
 * @param[in]  tchars    total chars in file.
 * @param[in]  nchars    number of unique chars.
 * @param[in]  freq      frequency map of the chars is the file.
 */
void write_compressed_file(const char *in_name, char **fmap, int tchars, int nchars, int *freq)
{
	unsigned int i, c;
	FILE *inf, *of;
    char out_name[100];
	strcpy(out_name, in_name);
	strcat(out_name, ".cz\0");
    of = open_file(out_name, "wb");

	fwrite(&nchars, 1, 4, of);
    for (i = 0; i < 256; i++){ 
		if (freq[i] == 0) continue;
		fwrite(&i, 1, 1 , of);
		fwrite(&freq[i], 1, 4 , of);
    }

    inf = open_file(in_name, "r");
	while ((c = fgetc(inf)) != EOF) { 
		fwrite(fmap[c], 1, strlen(fmap[c]), of);
    }
	
    fclose(inf);
    fclose(of);
}
