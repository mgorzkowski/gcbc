#ifndef __BITMAP_H__
#define __BITMAP_H__

typedef unsigned char byte;
typedef byte color;

typedef struct {
	color R;
	color G;
	color B;
} RGBPixel;

typedef struct {
	color R;
	color G;
	color B;
	color Alfa;
} RGBAPixel;

typedef struct {
	unsigned int size_x;
	unsigned int size_y;
	//RGBPixel* vector;
	byte* vector;
	int maxColorValue;
} RGBImage_t;

typedef struct {
	unsigned int size_x;
	unsigned int size_y;
	//RGBAPixel* vector;
	byte* vector;
	int maxColorValue;
} RGBAImage_t;

#endif /* __BITMAP_H__ */
