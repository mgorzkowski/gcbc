#include "../include/gcbc.h"

#define LM_PADDING_ON

// Public functions prototypes
void gcbc_shuffle(abn_t* key, abn_t* block, unsigned int rounds);
void gcbc_initial_round(abn_t* r, abn_t* q);
void gcbc_round(abn_t* q, abn_t* r);
void gcbc_final_round(abn_t* r, abn_t* q);

// Private functions prototypes
void gcbc_lm(abn_t* arg);
void logistic_map(abn_t* result, abn_t* arg);
uint8_t abn_t_value(abn_t* arg);

// Public functions

// gcbc shuffle - basic function in gcbc library
void gcbc_shuffle(abn_t* key, abn_t* block, unsigned int rounds)
{
	// Setting r and q variables
	abn_t* r = abn_create_copy(key);
	abn_t* q = abn_create_copy(block);
	gcbc_initial_round(r, q);
	for(unsigned int i=0; i<rounds; i++)
	{
		gcbc_round(q, r);
	}
	gcbc_final_round(r, q);
	abn_copy(block, q);
	abn_free(r);
	abn_free(q);
}

// Initial round of gcbc shuffle
void gcbc_initial_round(abn_t* r, abn_t* q)
{
	byte rt = abn_t_value(r);
	abn_rotate_right(q, rt);
	gcbc_lm(q);
}

// Basic round of gcbc shuffle
void gcbc_round(abn_t* q, abn_t* r)
{
	byte qt = abn_t_value(q);
	byte rt = abn_t_value(r);
	abn_rotate_right(q, rt);
	abn_rotate_right(r, qt);
	gcbc_lm(q);
	abn_xor(r, r, q);
	gcbc_lm(r);
	abn_xor(q, q, r);
}

// Final round of gcbc shuffle
void gcbc_final_round(abn_t* r, abn_t* q)
{
	byte qt = abn_t_value(q);
	byte rt = abn_t_value(r);
	abn_rotate_right(q, rt);
	abn_rotate_right(r, qt);
	abn_xor(q, q, r);
}

// Private functions

// returns value of 4*op*(1-op), the results volume is 2 times widest than ops one.
void logistic_map(abn_t* result, abn_t* arg)
{
	abn_t* _arg = abn_create_copy(arg);
	abn_neg(_arg);

//padding: seting the oldest nibble on XX10
#ifdef LM_PADDING_ON
	_arg->chain[_arg->volume-1] |= 1<<( sizeof(abn_unit) * _arg->volume-3 );
	_arg->chain[_arg->volume-1] &= ~(1<<( sizeof(abn_unit) * _arg->volume-4));
#endif

	abn_mul(result, arg, _arg);
	abn_free(_arg);
	abn_shift_left(result, 2);
}

// changing arg into lm(arg)
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

byte abn_t_value(abn_t* arg)
{
	abn_unit tmp = 0;
	byte result = 0;
	for(unsigned int i=0; i<arg->volume; i++)
	{
		tmp ^= arg->chain[i];
	}
	for(unsigned int i=0; i<sizeof(abn_unit); i++)
	{
		result ^= (tmp >> (8*i)) & 0xFF;
	}
	return result;
}
