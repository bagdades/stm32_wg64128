/*
 * seg25.h
 *
 *  Created on: 16 ????. 2012
 *      Author: vovan
 */

#ifndef SEG25_H_
#define SEG25_H_

/*******************************************************************************
* filename: /home/vovan/document/seg25.xml
* name: seg25
* family: Arial
* size: 26
* style: Negreta
* included characters: 0123456789
* antialiasing: <value not defined>
* type: monospaced
* encoding: WINDOWS-1251
* unicode bom: yes
*
* preset name: Monochrome
* data block size: 8 bit(s), uint8_t
* conversion type: Monochrome, Diffuse Dither 128
* bits per pixel: 1
*
* preprocess:
*  rotate: <value not defined>
*  flip horizontal: <value not defined>
*  flip vertical: <value not defined>
*  inverse: yes
*******************************************************************************/

/*
 typedef struct {
     long int code;
     const tImage *image;
     } tChar;
 typedef struct {
     int length;
     const tChar *chars;
     } tFont;
*/

#include <stdint.h>
#include "font.h"

static const uint8_t image_data_seg25_0x30[54] = {
    0x00, 0x00, 0x7f, 0xfe, 0xbf, 0xfd, 0xdf, 0xfb, 0xef, 0xf7, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0xc0, 0x03, 0xe0, 0x07, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xef, 0xf7, 0xdf, 0xfb, 0xbf, 0xfd, 0x7f, 0xfe, 0x00, 0x00
};
static const tImage seg25_0x30 = { image_data_seg25_0x30, 16, 27};

static const uint8_t image_data_seg25_0x31[54] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x07, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x07, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
};
static const tImage seg25_0x31 = { image_data_seg25_0x31, 16, 27};

static const uint8_t image_data_seg25_0x32[54] = {
    0x00, 0x00, 0x7f, 0xfe, 0x3f, 0xfd, 0x1f, 0xfb, 0x0f, 0xf7, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x07, 0x1f, 0xfb, 0x3f, 0xfd, 0x7f, 0xfe, 0xbf, 0xfc, 0xdf, 0xf8, 0xe0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xef, 0xf0, 0xdf, 0xf8, 0xbf, 0xfc, 0x7f, 0xfe, 0x00, 0x00
};
static const tImage seg25_0x32 = { image_data_seg25_0x32, 16, 27};

static const uint8_t image_data_seg25_0x33[54] = {
    0x00, 0x00, 0x7f, 0xfe, 0x3f, 0xfd, 0x1f, 0xfb, 0x0f, 0xf7, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x07, 0x1f, 0xfb, 0x3f, 0xfd, 0x7f, 0xfe, 0x3f, 0xfd, 0x1f, 0xfb, 0x00, 0x07, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x0f, 0xf7, 0x1f, 0xfb, 0x3f, 0xfd, 0x7f, 0xfe, 0x00, 0x00
};
static const tImage seg25_0x33 = { image_data_seg25_0x33, 16, 27};

static const uint8_t image_data_seg25_0x34[54] = {
    0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0xc0, 0x03, 0xe0, 0x07, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xe0, 0x07, 0xdf, 0xfb, 0xbf, 0xfd, 0x7f, 0xfe, 0x3f, 0xfd, 0x1f, 0xfb, 0x00, 0x07, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x07, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
};
static const tImage seg25_0x34 = { image_data_seg25_0x34, 16, 27};

static const uint8_t image_data_seg25_0x35[54] = {
    0x00, 0x00, 0x7f, 0xfe, 0xbf, 0xfc, 0xdf, 0xf8, 0xef, 0xf0, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xe0, 0x00, 0xdf, 0xf8, 0xbf, 0xfc, 0x7f, 0xfe, 0x3f, 0xfd, 0x1f, 0xfb, 0x00, 0x07, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x0f, 0xf7, 0x1f, 0xfb, 0x3f, 0xfd, 0x7f, 0xfe, 0x00, 0x00
};
static const tImage seg25_0x35 = { image_data_seg25_0x35, 16, 27};

static const uint8_t image_data_seg25_0x36[54] = {
    0x00, 0x00, 0x7f, 0xfe, 0xbf, 0xfc, 0xdf, 0xf8, 0xef, 0xf0, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xe0, 0x00, 0xdf, 0xf8, 0xbf, 0xfc, 0x7f, 0xfe, 0xbf, 0xfd, 0xdf, 0xfb, 0xe0, 0x07, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xef, 0xf7, 0xdf, 0xfb, 0xbf, 0xfd, 0x7f, 0xfe, 0x00, 0x00
};
static const tImage seg25_0x36 = { image_data_seg25_0x36, 16, 27};

static const uint8_t image_data_seg25_0x37[54] = {
    0x00, 0x00, 0x7f, 0xfe, 0x3f, 0xfd, 0x1f, 0xfb, 0x0f, 0xf7, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x07, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x07, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00
};
static const tImage seg25_0x37 = { image_data_seg25_0x37, 16, 27};

static const uint8_t image_data_seg25_0x38[54] = {
    0x00, 0x00, 0x7f, 0xfe, 0xbf, 0xfd, 0xdf, 0xfb, 0xef, 0xf7, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xe0, 0x07, 0xdf, 0xfb, 0xbf, 0xfd, 0x7f, 0xfe, 0xbf, 0xfd, 0xdf, 0xfb, 0xe0, 0x07, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xef, 0xf7, 0xdf, 0xfb, 0xbf, 0xfd, 0x7f, 0xfe, 0x00, 0x00
};
static const tImage seg25_0x38 = { image_data_seg25_0x38, 16, 27};

static const uint8_t image_data_seg25_0x39[54] = {
    0x00, 0x00, 0x7f, 0xfe, 0xbf, 0xfd, 0xdf, 0xfb, 0xef, 0xf7, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xe0, 0x07, 0xdf, 0xfb, 0xbf, 0xfd, 0x7f, 0xfe, 0x3f, 0xfd, 0x1f, 0xfb, 0x00, 0x07, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x0f, 0xf7, 0x1f, 0xfb, 0x3f, 0xfd, 0x7f, 0xfe, 0x00, 0x00
};
static const tImage seg25_0x39 = { image_data_seg25_0x39, 16, 27};

static const uint8_t image_data_seg25_0x3a[54] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const tImage seg25_0x3a = { image_data_seg25_0x3a, 16, 27};

static const uint8_t image_data_seg25_0x3b[54] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const tImage seg25_0x3b = { image_data_seg25_0x3b, 16, 27};


static const tChar seg25_array[] = {

  // character: '0'
  {0x30, &seg25_0x30},
  // character: '1'
  {0x31, &seg25_0x31},
  // character: '2'
  {0x32, &seg25_0x32},
  // character: '3'
  {0x33, &seg25_0x33},
  // character: '4'
  {0x34, &seg25_0x34},
  // character: '5'
  {0x35, &seg25_0x35},
  // character: '6'
  {0x36, &seg25_0x36},
  // character: '7'
  {0x37, &seg25_0x37},
  // character: '8'
  {0x38, &seg25_0x38},
  // character: '9'
  {0x39, &seg25_0x39},
  // character: ':'
  {0x3a, &seg25_0x3a},
  // character: ';'
  {0x3b, &seg25_0x3b}
};


static const tFont seg25 = { 12, seg25_array };
#endif /* SEG25_H_ */
