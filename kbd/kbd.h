#ifndef __KBD_H
#define __KBD_H

#define KBD_PORT         PORTD
#define KBD_DDR          DDRD
#define KBD_PIN          PIND

#define NEXT_BTN         2
#define PREV_BTN         3
#define PP_BTN           4
#define BTN_MASK         ((1<<NEXT_BTN)|(1<<PREV_BTN)|(1<<PP_BTN))

#define CTRL_PORT        PORTB
#define CTRL_DDR         DDRB
#define CTRL_PIN         PINB

#define NEXT_CTRL        2
#define PREV_CTRL        1
#define PP_CTRL          3
#define MODE_CTRL        0

#define TOTAL_EVENTS     4

#define EVENT            0
#define NO_EVENT         0
#define PREV_EVENT       1
#define NEXT_EVENT       2
#define PREV_NEXT_EVENT  3
#define PP_EVENT         4

#define COLLECT          0
#define RELEASE          1
#define RETURN           2

#define BTN_TIMEOUT      2   //2*4ms = 8ms poll timeout
//#define KBD_TIMEOUT     100 //100*4ms = 400ms kbd poll timeout

#define EVENT_THRESHOLD_VALUE 45
//------------------------------------------------------------------------------
void    init_kbd(void);
uint8_t scan_kbd(void);

#endif //__KBD_H