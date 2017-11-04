#include "utilities.h"

/**
 * 
 */
char *dec_to_bin(int n, int size)
{
    int k, j, i = 0;
    char *code = emalloc(size - 1);
    for (j = size - 1; j >= 0; j--)  {
        k = n >> j;
        code[i++] = (k & 1) ? 1 + '0': 0 + '0';
    }
    code[i] = '\0';
    return  code;
}

/**
 *
 *
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
 *
 *
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
 *
 */
void write_compressed_file(const char *in_name, char **fmap, int tchars, int nchars, int *freq)
{
    unsigned int i, c;
	FILE *input_f, *output_f;
    char out_name[100];
	strcpy(out_name, in_name);
	strcat(out_name, ".cz\0");
    output_f = open_file(out_name, "w");
    fprintf(output_f, "%d", nchars);
    
    for (i = 0; i < 256; i++){ 
       if (freq[i] == 0) continue;
       fprintf(output_f, "%c%d", i, freq[i]);
    }

    /*should i put a line after the header*/
    input_f = open_file(in_name, "r");
    while ((c = fgetc(input_f)) != EOF) 
        fprintf(output_f, "%s", fmap[c]);
    
    /*close the files*/
    fclose(input_f);
    fclose(output_f);
	fprintf(stderr, "<%s> successfully compressed to <%s>\n", in_name, out_name);
}

/**
 *
 *
 */
void view_freq_map(int *frequency_map, int tchars, int nchars)
{
	int i;
	printf("TOTAL OF CHARS  = \t\t< %d >\n", tchars);
	printf("NUMBER OF CHARS = \t\t< %d >\n", nchars);
    for (i = 0; i < 256; i++) {
        if (frequency_map[i] == 0) continue;
        if (i == 10)
           printf("c:[nl],\t i:[%d], \tf:[%d]\n", i, frequency_map[i]);
		else if (i == 9)
           printf("c:[tb],\t i:[%d], \tf:[%d]\n", i, frequency_map[i]);
        else
            printf("c:[%c],\t i:[%d], \tf:[%d]\n", i, i, frequency_map[i]);
    }
}

/**
 *
 * @param t[in]  
 */
void view_code_table(char *t[])
{
	int i;
	for (i = 0; i < 256; i++) 
		if (t[i] != '\0') {
			fprintf(stderr,"size: [%lu], char index: [%c], code: %s\n", strlen(t[i]),i, t[i]);  
    }
}
