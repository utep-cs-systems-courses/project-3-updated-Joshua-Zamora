#ifndef draw_included
#define draw_included


void drawString8x12(u_char col, u_char row, char *string, u_int fgColorBGR, u_int bgColorBGR);
void drawChar8x12(u_char rcol, u_char rrow, char c, u_int fgColorBGR, u_int bgColorBGR);
void drawOctagon(char position, int color);
void drawSquare(int offc, int offr, int color);
void moveSquare();

#endif // included
