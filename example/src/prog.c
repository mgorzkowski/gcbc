#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abn.h"

void logistic_map(abn_t* result, abn_t* op)
{
	abn_t* _op = abn_create_copy(op);
	abn_neg(_op);
	abn_mul(result, op, _op);
	abn_free(_op);
	abn_shift_left(result, 2);
}

//TODO: Add padding in argument value
void gcbc_lm(abn_t* arg)
{
	abn_t* tmp = abn_create(2 * arg->volume);
	logistic_map(tmp, arg);
	abn_unit offset = arg->volume;
	for(uint8_t i=0; i<arg->volume; i++)
	{
		arg->chain[i] = tmp->chain[offset+i];
	}
	abn_free(tmp);
}

void print_abn_t(abn_t* arg, char* name)
{
	char* representation = abn_to_string(arg);
	printf("%s = [ 0x%s ]\n", name, representation);
	fflush(stdout);
	free(representation);
}

int main()
{	
	srand(time(NULL));
	uint8_t volume = 8;
	abn_t* a = abn_create(volume);
	for(uint8_t i=0; i<volume; i++)
	{
		a->chain[i] = rand();	
	}
	print_abn_t(a, "a");
	for(uint8_t i=0; i<99; i++)
	{
		gcbc_lm(a);
		print_abn_t(a, "a");
	}
	return 0;
}
