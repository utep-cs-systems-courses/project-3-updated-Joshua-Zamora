#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "draw.h"

int song[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380}; // frequencies for song

void playSong()
{
  static char i = 0;

  if (i == 156) i = 0;
  buzzer_set_period(2000000 / song[i++]);
}

void buttonOneState() 
{
  buzzer_set_period(0);
  clearScreen(COLOR_GREEN);
  buzzer_set_period(1000);
  clearScreen(COLOR_BLUE);
  buzzer_set_period(1500);
  clearScreen(COLOR_BEIGE);
  buzzer_set_period(2000);
  clearScreen(COLOR_BLACK);
  buzzer_set_period(0);
  drawString5x7(40, 40, "Welcome!", COLOR_DEEP, COLOR_BLACK);
}

void buttonTwoState() 
{
  clearScreen(COLOR_RED);
  clearScreen(COLOR_BLUE);
  clearScreen(COLOR_GOLD);
  clearScreen(COLOR_BLACK);
  drawString5x7(40, 40, "SECOND!", COLOR_RED, COLOR_BLACK);
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
  clearScreen(COLOR_BLACK);
  buzzer_set_period(0);
  drawString5x7(40, 40, "THIRD!", COLOR_PURPLE, COLOR_BLACK);
}

char buttonFourState(char offset) 
{
  buzzer_set_period(0);
  clearScreen(COLOR_BLACK);
  char position = offset;
  
  drawOctagon(position, COLOR_YELLOW);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_WHITE, COLOR_YELLOW);
  position += 20;
  
  drawOctagon(position, COLOR_ORANGE);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_WHITE, COLOR_ORANGE);
  position += 20;

  drawOctagon(position, COLOR_RED);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_WHITE, COLOR_RED);

  position = -40;

  drawOctagon(position, COLOR_BLUE);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_WHITE, COLOR_BLUE);
  position += 20;
  
  drawOctagon(position, COLOR_PURPLE);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_WHITE, COLOR_PURPLE);
  position += 20;

  drawOctagon(position, COLOR_PINK);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_WHITE, COLOR_PINK);

  position = -40;

  drawOctagon(position, COLOR_CHOCOLATE);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_WHITE, COLOR_CHOCOLATE);
  position += 20;
  
  drawOctagon(position, COLOR_BROWN);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_WHITE, COLOR_BROWN);
  position += 20;

  drawOctagon(position, COLOR_SIENNA);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_WHITE, COLOR_SIENNA);

  position = -40;
  
  drawOctagon(position, COLOR_BLACK);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_BLACK, COLOR_BLACK);
  position += 20;

  drawOctagon(position, COLOR_BLACK);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_BLACK, COLOR_BLACK);
  position += 20;
  
  drawOctagon(position, COLOR_BLACK);
  drawString8x12(63 + position, 95 + position, "STOP", COLOR_BLACK, COLOR_BLACK);
  return 1;
}
