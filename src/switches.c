#include <msp430.h>
#include "switches.h"
#include "Main.h"
#include "led.h"

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  signed char state = (p2val & SW1) ? -1 : 1;     // -1 if switch 1 is up 
  if (state == -1) state = (p2val & SW2) ? -1 : 2; // -1 if switch 2 is up
  if (state == -1) state = (p2val & SW3) ? -1 : 3; // -1 if switch 3 is up
  if (state == -1) state = (p2val & SW4) ? -1 : 4; // -1 if switch 4 is up
  setButtonPress(state); // set next state
}
