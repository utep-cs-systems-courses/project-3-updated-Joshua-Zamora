#include <msp430.h>
#include "p2switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

static unsigned char switch_mask;
static unsigned char switches_last_reported;
static unsigned char switches_current;
char state = 0;

char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  switches_current = P2IN & switch_mask;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (switches_current);  /* if switch up, sense down */
  P2IES &= (switches_current | ~switch_mask); /* if switch down, sense up */
  return p2val;
}

void 
p2sw_init(unsigned char mask)
{
  switch_mask = mask;
  P2REN |= mask;    /* enables resistors for switches */
  P2IE = mask;      /* enable interrupts from switches */
  P2OUT |= mask;    /* pull-ups for switches */
  P2DIR &= ~mask;   /* set switches' bits for input */

  switch_update_interrupt_sense();
}

/* Returns a word where:
 * the high-order byte is the buttons that have changed,
 * the low-order byte is the current state of the buttons
 */
unsigned int 
p2sw_read() {
  unsigned int sw_changed = switches_current ^ switches_last_reported;
  switches_last_reported = switches_current;
  return switches_current | (sw_changed << 8);
}

void

switch_interrupt_handler()

{
  char p2val = switch_update_interrupt_sense();
  state = (p2val & SW1) ? 0 : 1;            // 0 if switch 1 is up
  if (state == 0) state = (p2val & SW2) ? 0 : 2; // 0 if switch 2 is up
  if (state == 0) state = (p2val & SW3) ? 0 : 3; // 0 if switch 3 is up
  if (state == 0) state = (p2val & SW4) ? 0 : 4; // 0 if switch 4 is up
}

/* Switch on P2 (S1) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & switch_mask) {  /* did a button cause this interrupt? */
    P2IFG &= ~switch_mask;	/* clear pending sw interrupts */
    switch_interrupt_handler();
  }
}
