#ifndef __UTILS_H__
#define __UTILS_H__

#include "../../include/bitmap.h"
#include "../../../../include/gcbc.h"

RGBImage_t createRGBImageFromValueChain(color* chain, unsigned int x, unsigned int y);
color* createValueChainFromRGBImage(RGBImage_t image, unsigned int x, unsigned int y);
abn_t* get_key(char* keyFileName, int bytes);

#endif /* __UTILS_H__ */
