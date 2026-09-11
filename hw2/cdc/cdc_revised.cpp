#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string>
#include <iostream>

#define WIN_SIZE 16
#define PRIME 3
#define MODULUS 256
#define TARGET 0

uint64_t initial_hash(unsigned char *input, unsigned int pos)
{
	uint64_t hash = 0;
	uint64_t current_pow = PRIME;

	for (int i = 0; i < WIN_SIZE; ++i) {
		hash += (input[pos+WIN_SIZE-1-i]) * current_pow;

		current_pow = current_pow * PRIME;
	}
	return hash;
}

uint64_t hash_func(unsigned char *input, unsigned int pos, uint64_t previous_hash)
{
	uint64_t current_pow = std::pow(PRIME, WIN_SIZE+1);

	uint64_t hash = (previous_hash * PRIME) - input[pos]*current_pow + input[pos+WIN_SIZE]*PRIME;
	return hash;
}

void cdc(unsigned char *buff, unsigned int buff_size)
{
	uint64_t prev_hash = initial_hash(buff, WIN_SIZE);
	if (((prev_hash % MODULUS)) == TARGET){
			printf("%u\n", WIN_SIZE);
	}

	for (unsigned int i = WIN_SIZE+1; i < buff_size - WIN_SIZE; ++i) {
		uint64_t curr_hash = hash_func(buff, i-1, prev_hash);
		if (((curr_hash % MODULUS)) == TARGET){
			printf("%u\n", i);
		}
		prev_hash = curr_hash;
	}

}

void test_cdc( const char* file )
{
	FILE* fp = fopen(file,"r" );
	if(fp == NULL ){
		perror("fopen error");
		return;
	}

	fseek(fp, 0, SEEK_END); // seek to end of file
	int file_size = ftell(fp); // get current file pointer
	fseek(fp, 0, SEEK_SET); // seek back to beginning of file

	unsigned char* buff = (unsigned char *)malloc((sizeof(unsigned char) * file_size ));	
	if(buff == NULL)
	{
		perror("not enough space");
		fclose(fp);
		return;
	}

	int bytes_read = fread(&buff[0],sizeof(unsigned char),file_size,fp);

	cdc(buff, file_size);

    free(buff);
    return;
}

int main()
{
	test_cdc("prince.txt");
	return 0;
}