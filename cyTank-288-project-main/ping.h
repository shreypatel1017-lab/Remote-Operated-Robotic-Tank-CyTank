//#ifndef PING_H
//#define PING_H
//
//#include <inc/tm4c123gh6pm.h>
//#include <stdbool.h>
//#include <stdint.h>
//#include <stdio.h>
//#include "driverlib/interrupt.h"
////#include "driverlib/interrupt.h"
//
//void ping_init();
//
//
//void pulse_ping();
//
//void TIMER3B_Handler();
//
//
//extern volatile int start_time;
//extern volatile int stop_time;
//
////void ping_signal_ISR();
//
//
//#endif

#ifndef PING_H_
#define PING_H_

#include <stdint.h>
#include <stdbool.h>
//#include "driverlib/interrupt.h"
#include <inc/tm4c123gh6pm.h>
#include <stdio.h>

// Global variables for echo timing
extern volatile int start_time;
extern volatile int stop_time;

// Initializes the ping sensor (Timer3B + GPIO PB3)
void ping_init(void);

// Sends a trigger pulse to the ping sensor
void pulse_ping(void);

// ISR for Timer3B capture events
void TIMER3B_Handler(void);

#endif /* PING_H_ */
