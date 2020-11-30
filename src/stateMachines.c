#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"

int song[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380}; // frequencies for song

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
  
  if (i == screenWidth) { i = 0; offSet += 20; }
  drawSquare(i++, offSet);
}

void playSong()
{
  static int i = 0;

  if (i == 156) i = 0;
  
  buzzer_set_period(2000000 / song[i++]);
}

void dimLCD()
{
  static char dim[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static char i = 0;
  static char state = 0;
  static char count = 0;
  static char goDown = 0;
  
  if (dim[9] == 1) { goDown = 1; i = 9; }
  else if (dim[0] == 0) { goDown = 0; i = 0; }

  if (++count > 4)
  {
    if (goDown) dim[i--] = 0;
    else dim[i++] = 1;
    count = 0;
  }
  
  switch (state++)
  {
  case 0: red_on = dim[0];            break;
  case 1: red_on = dim[1];            break;
  case 2: red_on = dim[2];            break;
  case 3: red_on = dim[3];            break;
  case 4: red_on = dim[4];            break;
  case 5: red_on = dim[5];            break;
  case 6: red_on = dim[6];            break;
  case 7: red_on = dim[7];            break;
  case 8: red_on = dim[8];            break;
  case 9: red_on = dim[9]; state = 0; break;
  }
  
  led_changed = 1;
  led_update();
}

signed char buttonOneState(int i) 
{
  buzzer_set_period(0);
  clearScreen(COLOR_GREEN);
  buzzer_set_period(1000);
  clearScreen(COLOR_BLUE);
  buzzer_set_period(1500);
  clearScreen(COLOR_YELLOW);
  buzzer_set_period(2000);
  clearScreen(COLOR_PINK);
  buzzer_set_period(0);
  return 1;
}

void buttonTwoState() 
{
  clearScreen(COLOR_RED);      
  clearScreen(COLOR_BLUE);
  clearScreen(COLOR_WHITE);
  drawString8x12(40, 20, "MARIO", COLOR_BLACK, COLOR_WHITE);
  drawString8x12(40, 40, "TIME", COLOR_BLACK, COLOR_WHITE);
}

void buttonThreeState()
{
  buzzer_set_period(0);
  clearScreen(COLOR_ORANGE);
  buzzer_set_period(2000);
  clearScreen(COLOR_GREEN);
  buzzer_set_period(1500);
  clearScreen(COLOR_GOLD);
  buzzer_set_period(1000);
  clearScreen(COLOR_PURPLE);
  buzzer_set_period(0);
}

void buttonFourState() 
{
  buzzer_set_period(0);
  clearScreen(COLOR_BLACK);
  drawOctagon();
  drawString8x12(63, 95, "STOP", COLOR_WHITE, COLOR_RED);
}
