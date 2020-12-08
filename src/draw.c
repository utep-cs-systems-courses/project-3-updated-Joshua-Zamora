#include "lcdutils.h"
#include "lcddraw.h"
#include "draw.h"

void drawSquare(int offc, int offr, int color)
{
  for (int r = 0; r < 20; r++)
    for (int c = 0; c < 20; c++)
      drawPixel(c + offc, r + offr, color);
}

void drawOctagon(char position, int color)
{
  
  for (int r = 0; r < 20; r++) // top right triangle
    for (int c = 0; c <= r; c++)
      drawPixel(90 + c + position, 70 + r + position, color);

  for (int r = 0; r < 20; r++) // top left triangle
    for (int c = 0; c <= r; c++)
      drawPixel(70 - c + position, 70 + r + position, color);

  for (int c = 0; c < 20; c++) // bottom right triangle
    for (int r = 0; r <= 20-c; r++)
      drawPixel(90 + c + position, 109 + r + position, color);

  for (int c = 0; c < 20; c++) // bottom left triangle
    for (int r = 0; r <= 20-c; r++)
      drawPixel(70 - c + position, 109 + r + position, color);
  
  drawSquare(70 + position, 70  + position, color);
  drawSquare(70 + position, 90  + position, color);
  drawSquare(70 + position, 110 + position, color);
  drawSquare(50 + position, 90  + position, color);
  drawSquare(90 + position, 90  + position, color);
}

void moveSquare()
{
  static int i = 0;
  static int offSet = 60;
  
  if (i == screenWidth / 2) { i = 0; offSet += 20; }
  drawSquare(i++, offSet, COLOR_BLACK);
}

void drawChar8x12(u_char rcol, u_char rrow, char c, u_int fgColorBGR, u_int bgColorBGR)
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x80;
  u_char oc = c - 0x20;
  
  lcd_setArea(rcol, rrow, rcol + 7, rrow + 11);
  
  while (row < 12) {
    u_char holder = font_8x12[oc][row];
    while (col < 8) {
      u_int colorBGR = (holder & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
      bit >>= 1;
    }
    bit = 0x80;
    col = 0;
    row++;
  }
  
}

void drawString8x12(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar8x12(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 9;
  }
}
