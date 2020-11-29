#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"

char previousState = 0;
short redrawScreen = 0;

void wdt_c_handler()
{
  static char count = 0;
  if (++count > 25 && previousState == 2)
  {
    playSong();
    count = 0;
  }
  if (previousState == 3) dimLCD();
}

void setButtonPress(char state) // sets next state based on button press
{
  if (state == previousState || state == 0) return;
  previousState = state;
  
  P1OUT |= LED_GREEN;

  //and_sr(~0x10);
  
  switch (state)
    {
    case 1: buttonOneState();   break;
    case 2: buttonTwoState();   break;
    case 3: buttonThreeState(); break;
    case 4: buttonFourState();  break;
    }

  //or_sr(0x10);
  
  P1OUT &= ~LED_GREEN;
}

void main(void) 
{  
  configureClocks();
  buzzer_init();
  switch_init();
  lcd_init();
  led_init();
  enableWDTInterrupts();
  or_sr(0x8);  
  clearScreen(COLOR_BLACK);
} 
