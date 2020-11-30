#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"

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
  drawString5x7(40, 40, "Welcome!", COLOR_BLACK, COLOR_PINK);
  return 1;
}

void buttonTwoState() 
{
  clearScreen(COLOR_RED);
  buzzer_set_period(3500);
  clearScreen(COLOR_BLUE);
  buzzer_set_period(3000);
  clearScreen(COLOR_BLACK);
  buzzer_set_period(2500);
  clearScreen(COLOR_WHITE);
  buzzer_set_period(0);
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
