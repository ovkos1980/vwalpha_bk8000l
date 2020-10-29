/******************************************************************************
File:			timers.c
Date:			16.09.2009
Version:		1.0
Author:			
Description:	        Implements simple timer pool. No timer chaining
Version Info:	        16.09.2009 - First version
*******************************************************************************/
#include "../defs.h"
#include "timers.h"

struct timers TimerPool[NUMTIMERS];

/******************************************************************************
Function:		init_timerpool
Parameters:		none
Return val:		void
Date:			18.7.2001
Desc:			Initialize timer pool
*******************************************************************************/
void init_timerpool (void)
 {
   uint8_t i;
   
   for( i=0; i < NUMTIMERS; i++)
    {
     TimerPool[i].TimerField = 0;
     TimerPool[i].Free = 1; //TRUE;
    }
   
   TIMSK  |= (1<<OCIE0A);             /* разрешить прерывание по совпадению timer0 */ 
   OCR0A   = 0x7D;                    /* значение для сравнения 0x7D -> 4 мс. ( TIMERTIC = ~ 4.0 мс. ) */
   TCNT0   = 0x00;                    /* сбросить таймер/счетчик */
   TCCR0B |= (1<<CS02);               /* делитель на 256, запустить таймер/счетчик */
 }



/******************************************************************************
Function:		get_timer
Parameters:		none
Return val:		Return handle of free timer
Date:			18.7.2001
Desc:			Gets free timer from the timer pool
*******************************************************************************/
uint8_t get_timer (void)
 {
  uint8_t i;
  uint8_t FirstMatch;

  for( i=0; i < NUMTIMERS; i++)
   {
    if( TimerPool[i].Free == 1 ) //TRUE
     {
	/* We found a free timer! Mark is reserved */
	TimerPool[i].Free = 0; //FALSE;
	FirstMatch = i;
	return FirstMatch;		/* Return Handle	*/
     }
   }
	/* Error Check	*/
	//DEBUGOUT("No Timers, Resetting..\n\r");
	//RESET_SYSTEM();
  return(0);
 }



/******************************************************************************
Function:		free_timer
Parameters:		none
Return val:		UINT8 nbr - number
Date:			18.7.2001
Desc:			puts the given timer back to the timer pool
*******************************************************************************/
void free_timer (uint8_t nbr)
 {
  /* Make a simple check */
  if( nbr > (NUMTIMERS-1) )
   return;
  TimerPool[nbr].Free = 1; //TRUE;
 }



/******************************************************************************
Function:		init_timer
Parameters:		UINT8 nbr - number
			UINT32 tout -  time out
Return val:		none
Date:			18.7.2001
Desc:			Initializes given timer to given time-out
*******************************************************************************/
void init_timer ( uint8_t nbr, uint32_t tout )
 {
  uint32_t val;
        
        /* Make a simple check */
  if( nbr > (NUMTIMERS-1) )
   return;
  if( TimerPool[nbr].Free == 1 ) //TRUE
   return;
	/* All OK */
  val = tout;
  TIMSK &= ~(1<<OCIE0A); //DISABLE_TIMER_IRQ();
  /* Normalize seconds to timer tics */
  TimerPool[nbr].TimerField = val;
  TIMSK |= (1<<OCIE0A);  //ENABLE_TIMER_IRQ();
 }



/******************************************************************************
Function:		check_timer
Parameters:		UINT8 nbr - number
Return val:		return the value of given timer
Date:			18.7.2001
Desc:			return the value of given timer
*******************************************************************************/
uint32_t check_timer (uint8_t nbr)
 {
  /* This should be quite fast function! 		*/
  /* Interrupts are not disabled when fetching the	*/
  /* value, therefore returned value possible has 	*/
  /* an error component +/- TIMERTIC.			*/
  /* Just live with it!					*/
  return TimerPool[nbr].TimerField;
 }



/******************************************************************************
Function:		irqhandler_timer
Parameters:		void
Return val:		void
Date:			18.7.2001
Desc:			Call this function on timer interrupt
*******************************************************************************/
/* завязываем прерывание от таймера0 на службу времени */
#pragma vector = TIMER0_COMPA_vect
__interrupt void Timer0_Compare_Interrupt(void)
 {
  uint8_t i;
  
  TCNT0 = 0x00;
  for( i=0; i<NUMTIMERS; i++ )
   {
    if( TimerPool[i].Free == 0 /*FALSE*/ && TimerPool[i].TimerField != 0)
     TimerPool[i].TimerField --;
   }
 }


/* EOF	*/
