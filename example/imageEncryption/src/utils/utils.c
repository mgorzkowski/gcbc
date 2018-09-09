#include "../../include/bitmap.h"
#include "../../../../include/gcbc.h"
#include <stdlib.h>

/*

// Changed RGBImage_t and this functions are not more necessery

RGBImage_t createRGBImageFromValueChain(color* chain, unsigned int x, unsigned int y)
{
  RGBImage_t result;
  result.size_x = x;
  result.size_y = y;
  result.vector = (RGBPixel*)malloc(sizeof(RGBPixel)*x*y);
  for(unsigned long i=0; i<3*x*y; i++)
  {
    if(i%3 == 0)
    {
      result.vector[i/3].R = chain[i];
    }
    else if(i%3 == 1)
    {
      result.vector[i/3].G = chain[i];
    }
    else if(i%3 == 2)
    {
      result.vector[i/3].B = chain[i];
    }
  }
  return result;
}

color* createValueChainFromRGBImage(RGBImage_t image, unsigned int x, unsigned int y)
{
  color *result = (color*)malloc(sizeof(color) * 3 * x * y);
  for(unsigned long i=0; i<3*x*y; i++)
  {
    if(i%3 == 0)
    {
      result[i] = image.vector[i/3].R;
    }
    else if(i%3 == 1)
    {
      result[i] = image.vector[i/3].G;
    }
    else if(i%3 == 2)
    {
      result[i] = image.vector[i/3].B;
    }
  }
  return result;
}
*/

abn_t* get_key(char* keyFileName, int bytes)
{
	FILE* keyFile = fopen(keyFileName, "r");
	if(keyFile == NULL)
	{
		printf("Cannot open file: %s\n", keyFileName);
		return abn_create_empty();
	}
	abn_t* result = abn_create(bytes / sizeof(abn_unit));
	for(int i=0; i<bytes/4; i++)
	{
		fscanf(keyFile, "%08X", &(result->chain[7-i]));
	}
	return result;
}
