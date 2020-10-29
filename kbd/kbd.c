#include "../defs.h"
#include "../timers/timers.h"
#include "kbd.h"

uint8_t kbd_event[5] = {0};
uint8_t btn_timer;
uint8_t kbd_timer;
uint8_t kbd_mode = COLLECT;

void init_kbd()
{
  CTRL_DDR  |=  ((1<<NEXT_CTRL)|(1<<PREV_CTRL)|(1<<PP_CTRL)|(1<<MODE_CTRL));  //set btn ctrls as output 
  CTRL_PORT &= ~((1<<NEXT_CTRL)|(1<<PREV_CTRL)|(1<<PP_CTRL)|(1<<MODE_CTRL));  //set btn ctrls to low
  
  btn_timer = get_timer();
  init_timer(btn_timer, BTN_TIMEOUT);
  //kbd_timer = get_timer();
  //init_timer(kbd_timer, KBD_TIMEOUT);
}

uint8_t scan_kbd()
{
  if(!check_timer(btn_timer))  // btn timeout expired so read btn state
   {
    uint8_t pin;
    
    pin = KBD_PIN; 
    switch(kbd_mode)
     {
      case COLLECT: {
                     if( (pin & BTN_MASK) == 0x10) // prev+next pressed
                      {
                        kbd_event[PREV_NEXT_EVENT]++;
                        if(kbd_event[NEXT_EVENT]) kbd_event[NEXT_EVENT]--;
                        if(kbd_event[PREV_EVENT]) kbd_event[PREV_EVENT]--;
                        if(kbd_event[PP_EVENT]) kbd_event[PP_EVENT]--;
                        if(kbd_event[PREV_NEXT_EVENT] >= EVENT_THRESHOLD_VALUE) 
                         {
                           kbd_event[EVENT] = PREV_NEXT_EVENT;
                           kbd_mode = RELEASE;
                           return PREV_NEXT_EVENT;
                         } 
                      }
                     
                     if( (pin & BTN_MASK) == 0x18 ) // next pressed
                      {
                        kbd_event[NEXT_EVENT]++;
                        if(kbd_event[PREV_EVENT]) kbd_event[PREV_EVENT]--;
                        if(kbd_event[PP_EVENT]) kbd_event[PP_EVENT]--;
                        if(kbd_event[PREV_NEXT_EVENT]) kbd_event[PREV_NEXT_EVENT]--;
                        if(kbd_event[NEXT_EVENT] >= EVENT_THRESHOLD_VALUE) 
                         {
                           kbd_event[EVENT] = NEXT_EVENT;
                           kbd_mode = RELEASE;
                           return NEXT_EVENT;
                         }
                      }
                     
                     if( (pin & BTN_MASK) == 0x14 ) // prev pressed
                      {
                        kbd_event[PREV_EVENT]++;
                        if(kbd_event[NEXT_EVENT]) kbd_event[NEXT_EVENT]--;
                        if(kbd_event[PP_EVENT]) kbd_event[PP_EVENT]--;
                        if(kbd_event[PREV_NEXT_EVENT]) kbd_event[PREV_NEXT_EVENT]--;
                        if(kbd_event[PREV_EVENT] >= EVENT_THRESHOLD_VALUE) 
                         {
                           kbd_event[EVENT] = PREV_EVENT;
                           kbd_mode = RELEASE;
                           return PREV_EVENT;
                         }
                      }
                     
                     if( (pin & BTN_MASK) == 0x0C ) // play-pause pressed
                      {
                        kbd_event[PP_EVENT]++;
                        if(kbd_event[NEXT_EVENT]) kbd_event[NEXT_EVENT]--;
                        if(kbd_event[PREV_EVENT]) kbd_event[NEXT_EVENT]--;
                        if(kbd_event[PREV_NEXT_EVENT]) kbd_event[PREV_NEXT_EVENT]--;
                        if(kbd_event[PP_EVENT] >= EVENT_THRESHOLD_VALUE) 
                         {
                           kbd_event[EVENT] = PP_EVENT;
                           kbd_mode = RELEASE;
                           return PP_EVENT;
                         }
                      }
                    } break;
      case RELEASE: {
                     if( (pin & BTN_MASK) == 0x1C ) //none pressed
                      {
                        for(uint8_t i=1; i<=TOTAL_EVENTS; i++)
                         if(kbd_event[i]>0) kbd_event[i]--;
                        
                        uint8_t k = 0;
                        for(uint8_t i=1; i<=TOTAL_EVENTS; i++)
                         if(kbd_event[i]>0) k++;
                        
                        if(k == 0)
                         {
                           kbd_mode = RETURN;
                         }
                        //kbd_mode = RETURN;
                      } 
                    } break;
      case RETURN: {
                    kbd_mode = COLLECT;
                    //return kbd_event[EVENT];
                   } break;
      default: break;        
     }
    init_timer(btn_timer, BTN_TIMEOUT);
    return 0;
   } else return 0;  
}