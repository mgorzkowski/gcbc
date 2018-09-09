#include "gcbc.h"
#include "../include/bitmap.h"
#include "../include/LoadBMP/loadbmp.h"
#include "utils/utils.h"

#define KEY_LENGTH 256

void encryptBMP(RGBImage_t image, abn_t* key, abn_t* IV);
unsigned int load_block_from_image(abn_t* block, RGBImage_t image, int whichOne);
unsigned int save_block_into_image(abn_t* block, RGBImage_t image, int whichOne);

int main(int argc, char* argv[])
{
	if(argc != 4)
	{
		printf("Usage: %s keyFile IVFile BMPFile\n", argv[0]);
		return 1;
	}
	abn_t* key = get_key(argv[1], KEY_LENGTH/8);
	abn_t* IV = get_key(argv[2], KEY_LENGTH/8);
	RGBImage_t BMPFile;
	BMPFile.maxColorValue = 255;
	unsigned int err = loadbmp_decode_file(argv[3], &BMPFile.vector, &BMPFile.size_y, &BMPFile.size_x, LOADBMP_RGB);
	if (err)
	{
		printf("Cannot open %s file. Error %u\n", argv[3], err);
		return 2;
	}
	abn_print(stdout, IV, "IV ");
	abn_print(stdout, key, "key");

	// encryption
	encryptBMP(BMPFile, key, IV);

	err = loadbmp_encode_file(argv[3], BMPFile.vector, BMPFile.size_y, BMPFile.size_x, LOADBMP_RGB);
	if (err)
	{
		printf("Cannot write to %s file. Error %u\n", argv[3], err);
		return 3;
	}

	printf("done!\n");
	return 0;
}

void encryptBMP(RGBImage_t image, abn_t* key, abn_t* IV)
{
	abn_t* block = IV;
	unsigned int interator=0;
	abn_t* tmp = abn_create(block->volume);
	while(load_block_from_image(tmp, image, interator))
	{
		gcbc_shuffle(key, block, 4);
		abn_xor(tmp, tmp, block);
		save_block_into_image(tmp, image, interator);
		interator++;
	}
}

// Inserts particular bytes form image into block
unsigned int load_block_from_image(abn_t* block, RGBImage_t image, int whichOne)
{
	unsigned int bytes_in_image = image.size_x * image.size_y * 3;
	unsigned int bytes_in_block = block->volume * sizeof(abn_unit);
	byte* byteArr = (void*)image.vector;

	if((whichOne+1) * bytes_in_block <= bytes_in_image)
	{
		for(unsigned int i=0; i<bytes_in_block; i++)
		{
			byte bt = byteArr[bytes_in_block*whichOne + i];
			abn_set_byte(block, bt, i);
		}
		return bytes_in_block;
	}
	else if((whichOne+1) * bytes_in_block <= bytes_in_image + block->volume * sizeof(abn_unit))
	{
		unsigned int bytes_in_last_block = bytes_in_image % bytes_in_block;
		if(bytes_in_last_block != 0)
		{
			for(unsigned int i=0; i<bytes_in_last_block; i++)
			{
				byte bt = byteArr[bytes_in_block*whichOne + i];
				abn_set_byte(block, bt, i);
			}
		}
		return bytes_in_last_block;
	}
	else
	{
		return 0;
	}
}

unsigned int save_block_into_image(abn_t* block, RGBImage_t image, int whichOne)
{
	unsigned int bytes_in_image = image.size_x * image.size_y * 3;
	unsigned int bytes_in_block = block->volume * sizeof(abn_unit);
	byte* byteArr = (void*)image.vector;

	if((whichOne+1) * bytes_in_block <= bytes_in_image)
	{
		for(unsigned int i=0; i<bytes_in_block; i++)
		{
			byte bt = abn_get_byte(block, i);
			byteArr[bytes_in_block*whichOne + i] = bt;
		}
		return bytes_in_block;
	}
	else if((whichOne+1) * bytes_in_block <= bytes_in_image + block->volume * sizeof(abn_unit))
	{
		unsigned int bytes_in_last_block = bytes_in_image % bytes_in_block;
		if(bytes_in_last_block != 0)
		{
			for(unsigned int i=0; i<bytes_in_last_block; i++)
			{
				byte bt = abn_get_byte(block, i);
				byteArr[bytes_in_block*whichOne + i] = bt;
			}
		}
		return bytes_in_last_block;
	}
	else
	{
		return 0;
	}
}
