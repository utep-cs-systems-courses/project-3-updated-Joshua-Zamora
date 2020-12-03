#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "draw.h"

int song[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770}; // frequencies for song

void playSong()
{
  static char i = 0;

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

  if (++count > 8)
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

void buttonOneState() 
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
  drawString5x7(40, 40, "Welcome!", COLOR_BLACK, COLOR_PINK);
}

void buttonTwoState() 
{
  clearScreen(COLOR_RED);
  clearScreen(COLOR_BLUE);
  clearScreen(COLOR_BLACK);
  clearScreen(COLOR_WHITE);
  drawString5x7(40, 40, "Second!", COLOR_BLACK, COLOR_WHITE);
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
  drawString5x7(40, 40, "Third!", COLOR_BLACK, COLOR_PURPLE);
}

void buttonFourState() 
{
  buzzer_set_period(0);
  clearScreen(COLOR_BLACK);
  drawOctagon();
  drawString8x12(63, 95, "STOP", COLOR_WHITE, COLOR_RED);
}
