#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"

signed char previousState = -1;
short redrawScreen = 0;

void wdt_c_handler()
{
  static char count = 0;
  if (++count > 25 && previousState == 2)
  {
    playSong();
    
    P1OUT |= LED_GREEN;
    moveSquare();
    P1OUT &= ~LED_GREEN;
    
    count = 0;
  }
  else if (previousState == 4) dimLCD();
}

int setButtonPress(signed char state) // sets next state based on button press
{
  char var = 1;
  
  if (state == previousState || state < 0) return 0;
  previousState = state;
  
  P1OUT |= LED_GREEN;

  //and_sr(~0x10);

  if (var != 2) {
    switch (state)
    {
    case 1: state = buttonOneState(1);   break;
    case 2: buttonTwoState();   break;
    case 3: buttonThreeState(); break;
    case 4: buttonFourState();  break;
    }
  }

  //or_sr(0x10);
  
  P1OUT &= ~LED_GREEN;
  
  return 1;
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
