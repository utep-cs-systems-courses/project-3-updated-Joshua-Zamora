#include "lcdutils.h"
#include "lcddraw.h"
#include "draw.h"

void drawSquare(int offc, int offr)
{
  for (int r = 0; r < 20; r++)
    for (int c = 0; c < 20; c++)
      drawPixel(c + offc, r + offr, COLOR_RED);
}

void drawOctagon()
{
  for (int r = 0; r < 20; r++) // top right triangle
    for (int c = 0; c <= r; c++)
      drawPixel(90 + c, 70 + r, COLOR_RED);

  for (int r = 0; r < 20; r++) // top left triangle
    for (int c = 0; c <= r; c++)
      drawPixel(70 - c, 70 + r, COLOR_RED);

  for (int c = 0; c < 20; c++) // bottom right triangle
    for (int r = 0; r <= 20-c; r++)
      drawPixel(90 + c, 109 + r, COLOR_RED);

  for (int c = 0; c < 20; c++) // bottom left triangle
    for (int r = 0; r <= 20-c; r++)
      drawPixel(70 - c, 109 + r, COLOR_RED);
  
  drawSquare(70, 70);
  drawSquare(70, 90);
  drawSquare(70, 110);
  drawSquare(50, 90);
  drawSquare(90, 90);
}

void moveSquare()
{
  static int i = 0;
  static int offSet = 60;
  
  if (i == screenWidth / 2) { i = 0; offSet += 20; }
  drawSquare(i++, offSet);
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
