#include "gcbc.h"

int main()
{
	srand(55);
	unsigned int volume = 8;
	abn_t* block = abn_create(volume);
	abn_t* key = abn_create(volume);
	for(uint8_t i=0; i<block->volume; i++)
	{
		block->chain[i] = 4*rand();
		key->chain[i] = 4*rand();
	}
	printf("Przed:\n");
	abn_print(stdout, block, "block");
	abn_print(stdout, key, "key  ");
	printf("Po:\n");
	gcbc_shuffle(key, block, 16);
	abn_print(stdout, block, "block");
	gcbc_shuffle(key, block, 16);
	abn_print(stdout, block, "block");
	gcbc_shuffle(key, block, 16);
	abn_print(stdout, block, "block");
}
