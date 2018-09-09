#ifndef __GCBC_H__
#define __GCBC_H__

#include "../lib/abn/include/abn.h"

void gcbc_shuffle(abn_t* key, abn_t* block, unsigned int rounds);
void gcbc_initial_round(abn_t* r, abn_t* q);
void gcbc_round(abn_t* q, abn_t* r);
void gcbc_final_round(abn_t* r, abn_t* q);

#endif /* __GCBC_H__ */
