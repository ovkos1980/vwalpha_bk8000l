#include "defs.h"
#include "timers\timers.h"
#include "kbd\kbd.h"

uint8_t mode = 0;
uint8_t kbdrez;
uint8_t timer1;


void init()
{
  init_timerpool();
  init_kbd();
  _SEI();
}

int main()
{
  init();
  timer1 = get_timer();
    
  while(1)
   {
     kbdrez = scan_kbd();
     
     if( kbdrez == PREV_NEXT_EVENT) 
      {
        if(mode == 0) { CTRL_PORT |= (1<<MODE_CTRL); } 
        if(mode == 1) { CTRL_PORT &= ~(1<<MODE_CTRL); }
        mode ^= 0x01;
        mode &= 0x01;
      }
     
     if( kbdrez == NEXT_EVENT) 
      {
        CTRL_PORT |= (1<<NEXT_CTRL);
        init_timer(timer1, 60);
        while(check_timer(timer1));
        CTRL_PORT &= ~(1<<NEXT_CTRL);        
      }
     
     if( kbdrez == PREV_EVENT) 
      {
        CTRL_PORT |= (1<<PREV_CTRL);
        init_timer(timer1, 60);
        while(check_timer(timer1));
        CTRL_PORT &= ~(1<<PREV_CTRL);        
      }
     
     if( kbdrez == PP_EVENT) 
      {
        CTRL_PORT |= (1<<PP_CTRL);
        init_timer(timer1, 60);
        while(check_timer(timer1));
        CTRL_PORT &= ~(1<<PP_CTRL);        
      }
   } 
  //return 0;
}
