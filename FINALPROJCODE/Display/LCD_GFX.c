#include "LCD_GFX.h"
#include "ST7735.h"
#include <stdlib.h>

/******************************************************************************
* Local Functions
******************************************************************************/



/******************************************************************************
* Global Functions
******************************************************************************/

/**************************************************************************//**
* @fn			uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
* @brief		Convert RGB888 value to RGB565 16-bit color data
* @note
*****************************************************************************/
uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((((31*(red+4))/255)<<11) | (((63*(green+2))/255)<<5) | ((31*(blue+4))/255));
}

/**************************************************************************//**
* @fn			void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color)
* @brief		Draw a single pixel of 16-bit rgb565 color to the x & y coordinate
* @note
*****************************************************************************/
void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color) {
	LCD_setAddr(x,y,x,y);
	SPI_ControllerTx_16bit(color);
}

/**************************************************************************//**
* @fn			void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor)
* @brief		Draw a character starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor){
	uint16_t row = character - 0x20;		//Determine row of ASCII table starting at space
	int i, j;
	if ((LCD_WIDTH-x>7)&&(LCD_HEIGHT-y>7)){
		for(i=0;i<5;i++){
			uint8_t pixels = ASCII[row][i]; //Go through the list of pixels
			for(j=0;j<8;j++){
				if ((pixels>>j)&1==1){
					LCD_drawPixel(x+i,y+j,fColor);
				}
				else {
					LCD_drawPixel(x+i,y+j,bColor);
				}
			}
		}
	}
}


/******************************************************************************
* LAB 4 TO DO. COMPLETE THE FUNCTIONS BELOW.
* You are free to create and add any additional files, libraries, and/or
*  helper function. All code must be authentically yours.
******************************************************************************/

/**************************************************************************//**
* @fn			void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius,uint16_t color)
* @brief		Draw a colored circle of set radius at coordinates
* @note
*****************************************************************************/
void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius,uint16_t color)
{
	// Fill this out
	int16_t f = 1 - radius;
	int16_t dx = 1;
	int16_t dy = -2 * radius;
	int16_t x = 0;
	int16_t y = radius;

	LCD_drawPixel(x0, y0 + radius, color);
	LCD_drawPixel(x0, y0 - radius, color);
	LCD_drawPixel(x0 + radius, y0, color);
	LCD_drawPixel(x0 - radius, y0, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			dy += 2;
			f += dy;
		}
		x++;
		dx += 2;
		f += dx;

		LCD_drawPixel(x0 + x, y0 + y, color);
		LCD_drawPixel(x0 - x, y0 + y, color);
		LCD_drawPixel(x0 + x, y0 - y, color);
		LCD_drawPixel(x0 - x, y0 - y, color);
		LCD_drawPixel(x0 + y, y0 + x, color);
		LCD_drawPixel(x0 - y, y0 + x, color);
		LCD_drawPixel(x0 + y, y0 - x, color);
		LCD_drawPixel(x0 - y, y0 - x, color);
	}
}


/**************************************************************************//**
* @fn			void LCD_drawLine(short x0,short y0,short x1,short y1,uint16_t c)
* @brief		Draw a line from and to a point with a color
* @note
*****************************************************************************/
void LCD_drawLine(short x0,short y0,short x1,short y1,uint16_t c)
{
	// Fill this out
	int16_t dx = abs(x1 - x0);
	int16_t sx = x0 < x1 ? 1 : -1;
	int16_t dy = -abs(y1 - y0);
	int16_t sy = y0 < y1 ? 1 : -1;
	int16_t err = dx + dy; // error term

	while (1) {
		LCD_drawPixel(x0, y0, c);
		if (x0 == x1 && y0 == y1) break;
		int16_t e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
}



/**************************************************************************//**
* @fn			void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint16_t color)
* @brief		Draw a colored block at coordinates
* @note
*****************************************************************************/
void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint16_t color)
{
	// Fill this out
	if (x0 > x1) { uint8_t t = x0; x0 = x1; x1 = t; }
    if (y0 > y1) { uint8_t t = y0; y0 = y1; y1 = t; }
    if (x0 >= LCD_WIDTH || y0 >= LCD_HEIGHT) return;
    if (x1 >= LCD_WIDTH)  x1 = LCD_WIDTH  - 1;
    if (y1 >= LCD_HEIGHT) y1 = LCD_HEIGHT - 1;

    LCD_setAddr(x0, y0, x1, y1);
    uint32_t count = (uint32_t)(x1 - x0 + 1) * (uint32_t)(y1 - y0 + 1);
    while (count--) {
        SPI_ControllerTx_16bit(color);
    }
}

/**************************************************************************//**
* @fn			void LCD_setScreen(uint16_t color)
* @brief		Draw the entire screen to a color
* @note
*****************************************************************************/
void LCD_setScreen(uint16_t color) 
{
	// Fill this out
	LCD_setAddr(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
    uint32_t count = (uint32_t)LCD_WIDTH * (uint32_t)LCD_HEIGHT;
    while (count--) {
        SPI_ControllerTx_16bit(color);
    }
}

/**************************************************************************//**
* @fn			void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
* @brief		Draw a string starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
{
	// Fill this out
	uint8_t cx = x;
    uint8_t cy = y;

    while (*str) {
        char ch = *str++;
        if (ch == '\n') {
            cx = x;
            cy += 8;                       
            if (cy > LCD_HEIGHT - 8) break;
            continue;
        }
        if (cx > LCD_WIDTH - 6) {          
            cx = x;
            cy += 8;
            if (cy > LCD_HEIGHT - 8) break;
        }
        LCD_drawChar(cx, cy, (uint8_t)ch, fg, bg);
        for (uint8_t j = 0; j < 8; j++) LCD_drawPixel(cx + 5, cy + j, bg);
        cx += 6;                          
    }
}

//Smiley offsets
#define FACE_CENTER_X 40
#define FACE_CENTER_Y 64
#define FACE_RADIUS 30
#define EYE_OFFSET_X 12
#define EYE_OFFSET_Y 10
#define EYE_RADIUS 3

/**************************************************************************//**
* @fn			void display_happy_face(void)
*****************************************************************************/
void display_happy_face(void) {
    uint8_t x = FACE_CENTER_X;
    uint8_t y = FACE_CENTER_Y;
    
    LCD_setScreen(BLACK);
    LCD_drawString(55, 10, "HAPPY!", YELLOW, BLACK);
    
    LCD_drawCircle(x, y, FACE_RADIUS, YELLOW);
    LCD_drawCircle(x - EYE_OFFSET_X, y - EYE_OFFSET_Y, EYE_RADIUS, YELLOW);
    LCD_drawCircle(x + EYE_OFFSET_X, y - EYE_OFFSET_Y, EYE_RADIUS, YELLOW);
    
    for (int i = -15; i <= 15; i++) {
        int mouth_y = y + 20 - (i * i) / 30;
        LCD_drawPixel(x + i, mouth_y, YELLOW);
    }
}

/**************************************************************************//**
* @fn			void display_sad_face(void)
*****************************************************************************/
void display_sad_face(void) {
    uint8_t x = FACE_CENTER_X;
    uint8_t y = FACE_CENTER_Y;
    
    LCD_setScreen(BLACK);
    LCD_drawString(50, 10, "SAD...", CYAN, BLACK);
    
    LCD_drawCircle(x, y, FACE_RADIUS, CYAN);
    LCD_drawCircle(x - EYE_OFFSET_X, y - EYE_OFFSET_Y, EYE_RADIUS, CYAN);
    LCD_drawCircle(x + EYE_OFFSET_X, y - EYE_OFFSET_Y, EYE_RADIUS, CYAN);
    
    for (int i = -15; i <= 15; i++) {
        int mouth_y = y + 8 + (i * i) /30;
        LCD_drawPixel(x + i, mouth_y, CYAN);
    }
}


/**************************************************************************//**
* @fn			void display_angry_face(void)
*****************************************************************************/
void display_angry_face(void) {
    uint8_t x = FACE_CENTER_X;
    uint8_t y = FACE_CENTER_Y;
    
    LCD_setScreen(BLACK);
    LCD_drawString(50, 10, "ANGRY. Grrr.", RED, BLACK);
    
    LCD_drawCircle(x, y, FACE_RADIUS, RED);
    LCD_drawCircle(x - EYE_OFFSET_X, y - EYE_OFFSET_Y, EYE_RADIUS, RED);
    LCD_drawCircle(x + EYE_OFFSET_X, y - EYE_OFFSET_Y, EYE_RADIUS, RED);
    
    LCD_drawLine(x - EYE_OFFSET_X - 6, y - EYE_OFFSET_Y - 6, 
                 x - EYE_OFFSET_X + 6, y - EYE_OFFSET_Y - 4, RED);
    LCD_drawLine(x + EYE_OFFSET_X - 6, y - EYE_OFFSET_Y - 4, 
                 x + EYE_OFFSET_X + 6, y - EYE_OFFSET_Y - 6, RED);
    
    LCD_drawLine(x - 12, y + 18, x + 12, y + 18, RED);
}

/**************************************************************************//**
* @fn			void display_wink_face(void)
*****************************************************************************/
void display_wink_face(void) {
    uint8_t x = FACE_CENTER_X;
    uint8_t y = FACE_CENTER_Y;
    
    LCD_setScreen(BLACK);
    LCD_drawString(52, 10, "WINK ;)", MAGENTA, BLACK);
    
    LCD_drawCircle(x, y, FACE_RADIUS, MAGENTA);
    
    LCD_drawLine(x - EYE_OFFSET_X - 4, y - EYE_OFFSET_Y, 
                 x - EYE_OFFSET_X + 4, y - EYE_OFFSET_Y, MAGENTA);
    
    LCD_drawCircle(x + EYE_OFFSET_X, y - EYE_OFFSET_Y, EYE_RADIUS, MAGENTA);
    
   for (int i = -15; i <= 15; i++) {
        int mouth_y = y + 20 - (i * i) / 30;
        LCD_drawPixel(x + i, mouth_y, MAGENTA);
    }
}

/**************************************************************************//**
* @fn			void display_idle_face(void)
*****************************************************************************/
void display_idle_face(void) {
    uint8_t x = FACE_CENTER_X;
    uint8_t y = FACE_CENTER_Y;
    
    LCD_setScreen(BLACK);
    LCD_drawString(52, 10, "Bored", WHITE, BLACK);
    
    LCD_drawCircle(x, y, FACE_RADIUS, WHITE);
    
    LCD_drawLine(x - EYE_OFFSET_X - 4, y - EYE_OFFSET_Y, 
                 x - EYE_OFFSET_X + 4, y - EYE_OFFSET_Y, WHITE);
    
    LCD_drawLine(x + EYE_OFFSET_X - 4, y - EYE_OFFSET_Y, 
                 x + EYE_OFFSET_X + 4, y - EYE_OFFSET_Y, WHITE);
    
    LCD_drawLine(x - 12, y + 18, x + 12, y + 18, WHITE);
    }
