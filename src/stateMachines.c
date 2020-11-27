#include <msp430.h>
#include <libTimer.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

int song[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380}; // frequencies for song

static int ratioOne = 1100; 
static int ratioTwo = 380;

void buttonOneState() // Plays a siren noise
{
  static char goUp = 1; // Bool for increasing/decreasing frequency
  
  if (ratioOne > 1400) goUp = 0;
  else if (ratioOne < 1100) goUp = 1;

  if (goUp) ratioOne += 5;
  else ratioOne -= 5;
  
  buzzer_set_period(2000000 / ratioOne);

  static char redState = 0;

  switch (redState) { // green off 80% of time
  case 0: redState++;   red_on = 1; break;
  case 1:
  case 2:
  case 3: redState++;   red_on = 0; break;
  case 4: redState = 0; red_on = 0; break;
  }
}

void buttonTwoState() // Plays a song
{
  static int i = 0;
  static int timer = 0;

  if (i == 156) i = 0;
  if (timer++ > 25) { // Plays each note for 100ms
    timer = 0;
    buzzer_set_period(2000000 / song[i++]);
  }
  
  static char redState = 0;

  switch (redState) { // Green off 40% of the time
  case 0:
  case 1:
  case 2: redState++; red_on = 1; break;
  case 3: redState++; red_on = 0; break;
  case 4: redState = 0; red_on = 0; break;
  }
}

void buttonThreeState() // Increases frequency by 5 every call
{
  ratioTwo += 5;
  if (ratioTwo > 6000) ratioTwo = 380;
  
  buzzer_set_period(2000000 / ratioTwo);
  red_on = 1;
}

void buttonFourState() // Turns off green led and sounds
{
  buzzer_set_period(0);
  red_on = 0;
}

