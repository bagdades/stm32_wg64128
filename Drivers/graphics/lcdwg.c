/*
 * lcdwg.c
 *
 *  Created on: 10 ????. 2012
 *      Author: vovan
 */

/* #include <stdio.h> */
#include <string.h>
#include "stm32f1xx_hal.h"
#include "lcdwg.h"
#include "delay.h"
#include "main.h"
/* #include "src/stm32f10x.h" */

extern ug_t ug;

///* Variable to decide whether update Lcd Cache is active/nonactive */
static uint8_t lcdCache[LCD_CACHE_SIZE];
static uint16_t lcdCacheIdx;
static uint16_t loWaterMark;
static uint16_t hiWaterMark;
static uint8_t updateLcd;

const tFont* fontMenu;
const tFont* fontDigital;
uint8_t shiftRow;
uint8_t lcdMode;
char variableChar[VARIABLE_CHAR_DATA_LENGTH];


extern uint8_t ticksBlink;


/**
 * @name ug_Send
 * @param data-> byte of data or commant 
 * @param cd-> LCD_DATA or LCD_CMD. See enum in lcdwg.h
 * @param cs-> LCD_CS1 or LCD_CS2 or LCD_CS_BOTH . See enum in lcdwg.he
 */
static void ug_Send(uint8_t data, lcdDI_t cd, lcdCS_t cs) {
	int bitcnt;
	if (cd == LCD_DATA)
		HAL_GPIO_WritePin(LCD_DI_GPIO_Port, LCD_DI_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_DI_GPIO_Port, LCD_DI_Pin, GPIO_PIN_RESET);

	if (cs == LCD_CS1)
		HAL_GPIO_WritePin(LCD_CS1_GPIO_Port, LCD_CS1_Pin, GPIO_PIN_SET);
	else if (cs == LCD_CS2)
		HAL_GPIO_WritePin(LCD_CS2_GPIO_Port, LCD_CS2_Pin, GPIO_PIN_SET);
	else {
		HAL_GPIO_WritePin(LCD_CS1_GPIO_Port, LCD_CS1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LCD_CS2_GPIO_Port, LCD_CS2_Pin, GPIO_PIN_SET);
	}

	for (bitcnt = 8; bitcnt > 0; bitcnt--) {
		// Set Clock Idle level LOW.
		HAL_GPIO_WritePin(LCD_SHIFT_GPIO_Port, LCD_SHIFT_Pin, GPIO_PIN_RESET);
		if ((data & 0x80) == 0x80) {
			// clocks in the MSb first.
			HAL_GPIO_WritePin(LCD_DATA_GPIO_Port, LCD_DATA_Pin, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(LCD_DATA_GPIO_Port, LCD_DATA_Pin, GPIO_PIN_RESET);
		}
		// Data is clocked on the rising edge of SCK.
		HAL_GPIO_WritePin(LCD_SHIFT_GPIO_Port, LCD_SHIFT_Pin, GPIO_PIN_SET);
		data = data << 1; // Logical shift data by 1 bit left.
	}
	/* Strob */
	HAL_GPIO_WritePin(LCD_CLK_GPIO_Port, LCD_CLK_Pin, GPIO_PIN_SET);
	asm("nop");
	HAL_GPIO_WritePin(LCD_CLK_GPIO_Port, LCD_CLK_Pin, GPIO_PIN_RESET);
	asm("nop");
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
	/* uint8_t a; */
	/* for (a = 0; a < 72; a++) { */
	/* 	asm("nop"); */
	/* } */
	_delay_us(1);
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
	asm("nop");

	HAL_GPIO_WritePin(LCD_CS1_GPIO_Port, LCD_CS1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS2_GPIO_Port, LCD_CS2_Pin, GPIO_PIN_RESET);
}

void ug_Init(void) {
	ug.x_dim = LCD_X_RES;
	ug.y_dim = LCD_Y_RES;
	ug.mode = LCD_MODE_NORM;

	/* Reset LCD */
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);

	ug_Send(0x3F, LCD_CMD, LCD_CS_BOTH); //Display ON
	ug_Send(0x40, LCD_CMD, LCD_CS_BOTH); //Y address 0
	ug_Send(0xB8, LCD_CMD, LCD_CS_BOTH); //X address 0
	ug_Send(0xC0, LCD_CMD, LCD_CS_BOTH); //Display start line 0
	ug_Clear();
	ug_Update();
}

/**
 * @name ug_Clear
 * @note Clear ram buffer for lcd
 */
void ug_Clear(void) {
	memset(lcdCache, 0, LCD_CACHE_SIZE);
	loWaterMark = 0;
	hiWaterMark = LCD_CACHE_SIZE - 1;

	/* Set update flag to be true */
	updateLcd = TRUE;
}

/**
 * @name ug_Update
 * @note Copy ram buffer to lcd
 */
void ug_Update(void) {
	uint16_t i = 0;
	uint8_t row, column;
	uint8_t rowEnd;
	lcdCS_t cs = LCD_CS1;

	/* if (loWaterMark < 0) */
		loWaterMark = 0;
	/* else if (loWaterMark >= LCD_CACHE_SIZE) */
	/* 	loWaterMark = LCD_CACHE_SIZE - 1; */
    /*  */
	/* if (hiWaterMark < 0) */
	/* 	hiWaterMark = 0; */
	/* else if (hiWaterMark >= LCD_CACHE_SIZE) */
		hiWaterMark = LCD_CACHE_SIZE - 1;

	row = loWaterMark / LCD_X_RES;
	rowEnd = hiWaterMark / LCD_X_RES;
	i = loWaterMark;
	for (; row <= rowEnd; row++) {
		ug_Send(0xB8 + row, LCD_CMD, LCD_CS_BOTH);
		ug_Send(0x40, LCD_CMD, LCD_CS_BOTH);
		for (column = 0; column < 64; column++) {
			ug_Send(lcdCache[i++], LCD_DATA, cs);
		}
		cs = LCD_CS2;
		for (column = 0; column < 64; column++) {
			ug_Send(lcdCache[i++], LCD_DATA, cs);
		}
		cs = LCD_CS1;
	}

	/*  Reset watermark pointers. */
	loWaterMark = LCD_CACHE_SIZE - 1;
	hiWaterMark = 0;

	/* Set update flag to be true */
	updateLcd = FALSE;
}
/**
 * @name ug_DrawChar
 * 
 * 
 * @param x ->absolute coordinate x in pixel
 * @param y ->absolute coordinate y in pixel
 * @param font-> font of the char
 * @param mode > LCD_MODE_INVERSE or LCD_MODE_NORM. See enum in lcdwg.h.
 * @param ch -> char
 * @return width of the char
 */
uint8_t ug_DrawChar(ug_t *ug, uint8_t x, uint8_t y, uint8_t ch) {
	uint8_t i, j, n, m;
	uint8_t block;
	uint8_t chr;
	if ((ch < 0x20) || (ch > 0xFF)) {
		/* Convert to a printable character. */
		ch = '#';
	}
	/* if (ch == '*') */
	/* 	chr = 0x9F; */
	/* else if (ch == '²') */
	/* 	chr = 0xA0; */
	/* else if (ch == '¯') */
	/* 	chr = 0xA1; */
	/* else if (ch == 'º') */
	/* 	chr = 0xA2; */
	/* else if (ch == '³') */
	/* 	chr = 0xA3; */
	/* else if (ch == '¿') */
	/* 	chr = 0xA4; */
	/* else if (ch > '~') */
	/* 	chr = ch - 0x61; */
	/* else */
	chr = ch - ug->font->chars[0].code;
	uint8_t width = ug->font->chars[chr].image->width;
	uint8_t height = ug->font->chars[chr].image->height;
	lcdCacheIdx = x + ((y / 8) * LCD_X_RES);
	if (lcdCacheIdx < loWaterMark) {
		/* Update low marker. */
		loWaterMark = lcdCacheIdx;
	}
	n = m = 0;
	// Read first byte block of the image char
	block = ug->font->chars[chr].image->data[m++];
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (ug->mode == LCD_MODE_INVERSE) {
				if (block & 0x80)
					varClrBitBB(lcdCache[lcdCacheIdx], y % 8);
				else
					varSetBitBB(lcdCache[lcdCacheIdx], y % 8);
			} else {
				if (block & 0x80)
					varSetBitBB(lcdCache[lcdCacheIdx], y % 8);
				else
					varClrBitBB(lcdCache[lcdCacheIdx], y % 8);
			}
			block = block << 1;
			// Count shift of the block
			n++;
			if (n == 8) {
				n = 0;
				// if shifted all block , read next block
				block = ug->font->chars[chr].image->data[m++];
			}
			lcdCacheIdx++; // next position x in pixel
		}
		y++;
		if (y >= LCD_Y_RES)
			break;
		lcdCacheIdx = x + ((y / 8) * LCD_X_RES);
	}
	if (lcdCacheIdx > hiWaterMark) {
		/* Update high marker. */
		hiWaterMark = lcdCacheIdx;
	}
	updateLcd = TRUE;
	return width;
}
/**
 * @name ug_DrawString
 * @param x-> absolute coordinate x in pixel
 * @param y-> absolute coordinate y in pixel
 * @param font-> font of char
 * @param mode ->LCD_MODE_INVERSE or LCD_MODE_NORM. See enum in lcdwg.h.
 * @param string -> pointer on the input string 
 */
void ug_DrawString(ug_t *ug, uint8_t x, uint8_t y, const char* string) {
	uint8_t i, j;
	uint8_t width = 0;
	uint8_t height = ug->font->chars[0].image->height;
	j = y;
	while (*string) {
		if (width) {
			/* Draw interval between char (width 1 pixel)*/
			lcdCacheIdx = x + ((y / 8) * LCD_X_RES);
			j = y;
			for (i = 0; i < height; i++) {
				if (ug->mode == LCD_MODE_INVERSE)
					varSetBitBB(lcdCache[lcdCacheIdx], j % 8);
				else
					varClrBitBB(lcdCache[lcdCacheIdx], j % 8);
				j++;
				if (j % 8 == 0) {
					j++;
					lcdCacheIdx = x + ((j / 8) * LCD_X_RES);
				}
			}
			x++;
			if (x >= LCD_X_RES)
				break;
			lcdCacheIdx = x + ((y / 8) * LCD_X_RES);
		}
		width = ug_DrawChar(ug, x, y, *string);
		string++;
		x += width;
		if (x >= LCD_X_RES)
			break;
	}
	updateLcd = TRUE;
}
/**
 * @name ug_DrawText
 * @param rect->rectangle for text
 * @param lcdFlags-> Flags for place text. See enum in lcdwg.h
 * @param font-> font of the text
 * @param mode->LCD_MODE_INVERSE or LCD_MODE_NORM. See enum in lcdwg.h.
 * @param str-> pointer on the string of text
 * @return
 */
uint8_t ug_DrawText(ug_t *ug, rect_t rect, uint8_t lcdFlags, const char* str) {
	uint8_t w;
	uint8_t h;
	uint8_t _x, _y, i, j, bit;
	if ((rect.x + rect.length) >= LCD_X_RES)
		return OUT_OF_BORDER;
	if ((rect.y + rect.height) >= LCD_Y_RES)
		return OUT_OF_BORDER;
	w = ug_GetStrWidth(ug, ug->font, str);
	h = ug->font->chars[0].image->height;

	if (lcdFlags & DT_CENTER) { // Alignment center
		_x = rect.x + (rect.length - w) / 2;
	} else if (lcdFlags & DT_RIGHT) { // Aligment right
		_x = rect.x + rect.length - w;
	} else { // Alignment left (by default)
		_x = rect.x;
	}
	if (lcdFlags & DT_VCENTER) { // Alignment center by vertical
		_y = rect.y + (rect.height - h) / 2;
	} else if (lcdFlags & DT_BOTTOM) { // Alignment bottom
		_y = rect.y + rect.height - h;
	} else { // Alignment up (by default)
		_y = rect.y;
	}
	lcdCacheIdx = rect.x + ((rect.y / 8) * LCD_X_RES);
	if (lcdCacheIdx < loWaterMark) {
		/* Update low marker. */
		loWaterMark = lcdCacheIdx;
	}
	bit = rect.y;
	for (i = 0; i < rect.height; i++) {
		for (j = 0; j < rect.length; j++) {
			if (ug->mode == LCD_MODE_INVERSE)
				varSetBitBB(lcdCache[lcdCacheIdx], bit % 8);
			else
				varClrBitBB(lcdCache[lcdCacheIdx], bit % 8);
			lcdCacheIdx++;
		}
		bit++;
		lcdCacheIdx = rect.x + ((bit / 8) * LCD_X_RES);
	}
	if (lcdCacheIdx > hiWaterMark) {
		/* Update high marker. */
		hiWaterMark = lcdCacheIdx;
	}
	ug_DrawString(ug, _x, _y, str);

	/* Set update flag to be true */
	updateLcd = TRUE;
	return OK;
}
/*
 * Name         :	LcdGetStrWidth
 * Description  :
 * Argument(s)  :	font -> font of the string
 * Return value :	string width
 * Note         :
 */
uint8_t ug_GetStrWidth(ug_t *ug, const tFont *font, const char* str) {
	uint8_t width = 0;
	uint8_t length = 0;
	uint8_t chr;
	while (*str) {
		/* if (*str == 'ª') */
		/* 	chr = 0x9F; */
		/* else if (*str == '²') */
		/* 	chr = 0xA0; */
		/* else if (*str == '¯') */
		/* 	chr = 0xA1; */
		/* else if (*str == 'º') */
		/* 	chr = 0xA2; */
		/* else if (*str == '³') */
		/* 	chr = 0xA3; */
		/* else if (*str == '¿') */
		/* 	chr = 0xA4; */
		/* else if (*str > '~') */
		/* 	chr = *str - 0x61; */
		/* else */
		chr = *str - font->chars[0].code;
		if (width)
			length++;
		width = font->chars[chr].image->width;
		length += width;
		str++;
	}
	return length;
}
/*
 * Name         :  LcdDrawPixel
 * Description  :  Displays a pixel at given absolute (x, y) location.
 * Argument(s)  :  x, y -> Absolute pixel coordinates
 *                 mode -> LCD_MODE_INVERSE or LCD_MODE_NORM. See enum in lcdwg.h.
 * Return value :  see return value on lcdwg.h
 */
uint8_t ug_DrawPixel(uint8_t x, uint8_t y, lcdMode_t mode) {

	/* Prevent from getting out of border */
	if (x > LCD_X_RES)
		return OUT_OF_BORDER;
	if (y > LCD_Y_RES)
		return OUT_OF_BORDER;

	lcdCacheIdx = x + ((y / 8) * LCD_X_RES);

	if (lcdCacheIdx < loWaterMark) {
		/* Update low marker. */
		loWaterMark = lcdCacheIdx;
	}

	if (mode == LCD_MODE_INVERSE)
		varClrBitBB(lcdCache[lcdCacheIdx], y % 8);
	else
		varSetBitBB(lcdCache[lcdCacheIdx], y % 8);

	if (lcdCacheIdx > hiWaterMark) {
		/* Update high marker. */
		hiWaterMark = lcdCacheIdx;
	}

	return OK;
}
/*
 * Name         :  LcdLine
 * Description  :  Draws a line between two points on the display.
 * Argument(s)  :  x1, y1 -> Absolute pixel coordinates for line origin.
 *                 x2, y2 -> Absolute pixel coordinates for line end.
 *                 mode -> LCD_MODE_INVERSE or LCD_MODE_NORM. See enum in lcdwg.h.
 * Return value :  see return value on lcdwg.h
 */
uint8_t ug_DrawLine(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2,
		lcdMode_t mode) {
	uint8_t i;

	if (y1 == y2) {
		if (x1 < x2) {
			for (i = x1; i <= x2; i++)
				ug_DrawPixel(i, y1, mode);
		} else {
			for (i = x2; i <= x1; i++)
				ug_DrawPixel(i, y1, mode);
		}
	} else if (x1 == x2) {
		if (y1 < y2) {
			for (i = y1; i <= y2; i++)
				ug_DrawPixel(x1, i, mode);
		} else {
			for (i = y2; i <= y1; i++)
				ug_DrawPixel(x1, i, mode);
		}
	} else
		return OUT_OF_BORDER;
	/* Set update flag to be true */
	updateLcd = TRUE;
	return OK;
}
/*
 * Name         :  LcdDrawRect
 * Description  :  Display a rectangle.
 * Argument(s)  :  x1   -> absolute first x axis coordinate
 *                 y1   -> absolute first y axis coordinate
 *				   x2   -> absolute second x axis coordinate
 *				   y2   -> absolute second y axis coordinate
 *				   mode -> LCD_MODE_INVERSE or LCD_MODE_NORM. See enum in lcdwg.h.
 * Return value :  see return value on lcdwg.h.
 */
uint8_t ug_DrawRect(rect_t rect, lcdMode_t mode) {
	uint8_t i, j;

	/* Checking border */
	if ((rect.x > LCD_X_RES) || ((rect.x + rect.length) > LCD_X_RES)
			|| (rect.y > LCD_Y_RES) || ((rect.y + rect.height) > LCD_Y_RES))
		/* If out of border then return */
		return OUT_OF_BORDER;

	lcdCacheIdx = rect.x + ((rect.y / 8) * LCD_X_RES);
	if (lcdCacheIdx < loWaterMark) {
		/* Update low marker. */
		loWaterMark = lcdCacheIdx;
	}

	uint8_t bit = rect.y;
	for (i = 0; i < rect.height; i++) {
		for (j = 0; j < rect.length; j++) {
			if (mode == LCD_MODE_INVERSE)
				varClrBitBB(lcdCache[lcdCacheIdx], bit % 8);
			else
				varSetBitBB(lcdCache[lcdCacheIdx], bit % 8);
			lcdCacheIdx++;
		}
		bit++;
		lcdCacheIdx = rect.x + ((bit / 8) * LCD_X_RES);
	}
	if (lcdCacheIdx > hiWaterMark) {
		/* Update high marker. */
		hiWaterMark = lcdCacheIdx;
	}
	updateLcd = TRUE;
	return OK;
}
/**
 * @name LcdDrawFrame
 * @param x1 -> absolute first x axis coordinate 
 * @param x2 -> absolute second x axis coordinate
 * @param y1 -> absolute first y axis coordinate
 * @param y2 -> absolute second y axis coordinate
 * @param mode -> LCD_MODE_INVERSE or LCD_MODE_NORM. See enum in lcdwg.h.
 * @return	see return value on lcdwg.h.
 */
uint8_t ug_DrawFrame(ug_t *ug, uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
	uint8_t i;
	uint8_t x1 = x + w;
	uint8_t y1 = y + h;
	if (x > (LCD_X_RES - 1)) return OUT_OF_BORDER;
	if (y > (LCD_Y_RES - 1)) return OUT_OF_BORDER;
    if((x + w - 1) >= LCD_X_RES) w = LCD_X_RES - x;
    if((y + h - 1) >= LCD_Y_RES) h = LCD_Y_RES - y;
	for (i = x; i <= x1; i++)
		ug_DrawPixel(i, y, ug->mode);
	for (i = y; i <= y1; i++)
		ug_DrawPixel(x1, i, ug->mode);
	for (i = y; i <= y1; i++)
		ug_DrawPixel(x, i, ug->mode);
	for (i = x; i <= x1; i++)
		ug_DrawPixel(i, y1, ug->mode);
	if (lcdCacheIdx > hiWaterMark) {
		/* Update high marker. */
		hiWaterMark = lcdCacheIdx;
	}
	updateLcd = TRUE;
	return OK;
}

/**
 * @name LcdDrawImage
 * @param x-> absolute coordinate x in pixel
 * @param y-> absolute coordinate y in pixel
 * @param mode-> LCD_MODE_INVERSE or LCD_MODE_NORM. See enum in lcdwg.h.
 * @param image-> pointer to image
 */
void ug_DrawImage(uint8_t x, uint8_t y, uint8_t mode, tImage image) {
	uint8_t i, j, n, m, bit;
	uint8_t block;
	uint8_t width = image.width;
	uint8_t height = image.height;
	lcdCacheIdx = x + ((y / 8) * LCD_X_RES);
	if (lcdCacheIdx < loWaterMark) {
		/* Update low marker. */
		loWaterMark = lcdCacheIdx;
	}
	bit = y;
	n = m = 0;
	block = image.data[m++];
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (mode == LCD_MODE_INVERSE) {
				if (block & 0x80)
					varClrBitBB(lcdCache[lcdCacheIdx], bit % 8);
				else
					varSetBitBB(lcdCache[lcdCacheIdx], bit % 8);
			} else {
				if (block & 0x80)
					varSetBitBB(lcdCache[lcdCacheIdx], bit % 8);
				else
					varClrBitBB(lcdCache[lcdCacheIdx], bit % 8);
			}
			block = block << 1;
			n++;
			if (n == 8) {
				n = 0;
				block = image.data[m++];
			}
			lcdCacheIdx++;
		}
		bit++;
		lcdCacheIdx = x + ((bit / 8) * LCD_X_RES);
	}
	if (lcdCacheIdx > hiWaterMark) {
		/* Update high marker. */
		hiWaterMark = lcdCacheIdx;
	}
}

void ug_FillRectangle(ug_t* ug, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
	uint8_t i, j;
	if (x > (LCD_X_RES - 1)) return;
	if (y > (LCD_Y_RES - 1)) return;
    if((x + w - 1) >= LCD_X_RES) w = LCD_X_RES - x;
    if((y + h - 1) >= LCD_Y_RES) h = LCD_Y_RES - y;
	lcdCacheIdx = x + ((y / 8) * LCD_X_RES);
	if (lcdCacheIdx < loWaterMark) {
		/* Update low marker. */
		loWaterMark = lcdCacheIdx;
	}

	uint8_t bit = y;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			if (ug->mode == LCD_MODE_INVERSE)
				varSetBitBB(lcdCache[lcdCacheIdx], bit % 8);
			else
				varClrBitBB(lcdCache[lcdCacheIdx], bit % 8);
			lcdCacheIdx++;
		}
		bit++;
		lcdCacheIdx = x + ((bit / 8) * LCD_X_RES);
	}
	if (lcdCacheIdx > hiWaterMark) {
		/* Update high marker. */
		hiWaterMark = lcdCacheIdx;
	}
}

inline uint16_t ug_GetYDim(ug_t *ug) {
    return ug->y_dim;
}

inline uint16_t ug_GetXDim(ug_t *ug) {
    return ug->x_dim;
}

inline void ug_SetFont(ug_t* ug, const tFont* font) {
    ug->font = font;
}

const tFont* ug_GetFont(ug_t *ug) {
    const tFont *font;
    font = ug->font;
    return font;
}

inline void ug_SetMode(ug_t *ug, lcdMode_t mode) {
	ug->mode = mode;
}

lcdMode_t ug_GetMode(ug_t *ug) {
	lcdMode_t mode;
	mode = ug->mode;
	return mode;
}
