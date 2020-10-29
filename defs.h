#ifndef __DEFS_H
#define __DEFS_H

#include <iotiny2313.h>
#include <stdint.h>
#include <ina90.h>

//#define BQ1  //7.3728 MHz
#define BQ2  //inbuild rezonator 8.0000 MHz
//#define BQ3  //11.059 MHz 

#ifdef BQ1
 #define F_CLK  7372800UL   //7.3728 MHz
#endif
#ifdef BQ2
 #define F_CLK  8000000UL   //8.0 MHz
#endif 
#ifdef BQ3
 #define F_CLK  11059200UL  //11.059 MHz 
#endif

#define RADIO     0
#define BLUETOOTH 1

#endif //__DEFS_H