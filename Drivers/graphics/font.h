/*
 * font.h
 *
 *  Created on: 16 вер. 2012
 *      Author: vovan
 */

#ifndef FONT_H_
#define FONT_H_
#include <stdint.h>


typedef struct {
	const uint8_t *data;
	uint8_t width;
	uint8_t height;
} tImage;


typedef struct {
	long int code;
	const tImage *image;
} tChar;

typedef struct {
	int length;
	const tChar *chars;
} tFont;

static const uint8_t image_data_test_Image[25] = {
	0x00, 0x00, 0x03, 0xff, 0xfc, 0x00, 0x00, 0x03, 0x3f, 0xcc, 0x33, 0x00, 0xc3, 0x00, 0xcc, 0x33, 0xf0, 0xc0, 0x00, 0x0c, 0x3f, 0xff, 0x00, 0x00, 0x00
};
static const tImage test_Image = { image_data_test_Image, 20, 10};

#endif
