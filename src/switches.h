#ifndef switches_included
#define switches_included

#define SW1 BIT0		/* switch1 is p1.3 */
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES 15		/* only 1 switch on this board */

void switch_init();
void switch_interrupt_handler();

#endif // included
