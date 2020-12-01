#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "Main.h"

signed char buttonPressed = -1;
char buttonChanged = 0;
short redrawScreen = 0;

void wdt_c_handler()
{
  static char count = 0;
  if (++count > 30)
  {
    count = 0;
    redrawScreen = 1;
  }
}

void setState(signed char state)
{
  buttonPressed = state;
  buttonChanged = 1;
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
  while (1) {/* forever */
    /*if (redrawScreen) {
      redrawScreen = 0;
      moveSquare();
    }*/
    if (buttonChanged)
    {
      state_advance(buttonPressed);
      buttonChanged = 0;
    }
    
    P1OUT &= ~LED_GREEN;/* green off */
    or_sr(0x10);/**< CPU OFF */
    P1OUT |= LED_GREEN;/* green on */
  }
}
