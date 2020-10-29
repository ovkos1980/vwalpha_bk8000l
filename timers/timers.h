/******************************************************************************
File:			timers.h
Date:			16.09.2009
Version:		1.0
Author:			
Description:	        Implements simple timer pool. No timer chaining
Version Info:	        16.09.2009 - First version 
*******************************************************************************/
#ifndef _TIMERS_H
#define _TIMERS_H

//#include "datatypes.h"

/* API for Timers */
#define NUMTIMERS   10
//#define TIMERTIC    100		/* Timer period 1/secs		*/
#define BASETIMER   0		/* Free running system timer	*/

//#define DAY14       120960000/*(14*24*60*60*TIMERTIC)*/
//#define DAY1        8640000/*(24*60*60*TIMERTIC)*/
//#define HOUR24      8640000/*(24*60*60*TIMERTIC)*/
//#define HOUR1       360000/*(60*60*TIMERTIC)*/
//#define MIN60       360000/*(60*60*TIMERTIC)*/
//#define MIN30       180000/*(30*60*TIMERTIC)*/
//#define MIN5        (5*60*TIMERTIC)
//#define SEC60         (60*TIMERTIC)
//#define SEC30         (30*TIMERTIC) 

struct timers
 {
  uint32_t TimerField;
  uint8_t  Free;
 };

/* Timers function prototypes */

void     init_timerpool(void);
uint8_t  get_timer(void);
void     free_timer(uint8_t nbr);
void     init_timer(uint8_t nbr, uint32_t tout);
uint32_t check_timer(uint8_t nbr);
void     irqhandler_timer(void);

#endif //_TIMERS_H
/* EOF	*/
