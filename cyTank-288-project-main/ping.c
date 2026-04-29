//#include "ping.h"
//#include "Timer.h"





//extern volatile int start_time;
//extern volatile int stop_time;
//extern volatile bool done;
//
////void TIMER3B_Handler();
//
//void ping_init(){
//
//    SYSCTL_RCGCGPIO_R |= BIT1; // enabling clock for port B
//    timer_waitMillis(10);
//    SYSCTL_RCGCTIMER_R |= BIT3; // provide clock to timer 3
//    timer_waitMillis(10);
//    GPIO_PORTB_DEN_R |= BIT3; // enalble digital functionality of PB3
//
//    GPIO_PORTB_DIR_R = (GPIO_PORTB_DIR_R & (~BIT3));  // make bit 3 input to catch the incoming ping data
//
//
//    // setting timer stuff
//    GPIO_PORTB_AFSEL_R |= BIT3; // configure PB3 as timer part 1
//    GPIO_PORTB_PCTL_R = 0x00007000;     // configure PB3 as timer part 1
//
//    TIMER3_CTL_R = (TIMER3_CTL_R & (~0x100)); // disable the timer when configuring
//
//    TIMER3_CFG_R = 0x04; // select the 16 bit timer config, to split into a and b
//    TIMER3_TBMR_R = 0b100; // set to edge time mode
//    TIMER3_TBMR_R |= 0b11; // set to capture mode
//    TIMER3_CTL_R = (TIMER3_CTL_R & ~0xC00) | 0x0C00;  // trigger on both edges
//
//    TIMER3_TBMR_R = (TIMER3_TBMR_R & (~0b10000)); // set the timer to count down
//
//    TIMER3_TBILR_R = 0xFFFF; // fill the initial value with FFFF
//    TIMER3_TBPR_R = 0xFF;    // set the prescaler to be 255, increment the counter every 255 clock ticks
//    IntMasterEnable();                        // enable global interrupts
//
//
//    IntRegister(INT_TIMER3B, ping_signal_ISR); // register ISR
//    IntEnable(INT_TIMER3B);
//
//    TIMER3_IMR_R |= 0x0400;                   // unmask Timer3B capture interrupt
//    TIMER3_CTL_R |= 0x100; // enable the timer after configuring
//
//}
//
//
//void send_pulse(){
//
//    GPIO_PORTB_DIR_R |= BIT3;  // make bit 3 an output to begin with
//    GPIO_PORTB_AFSEL_R = (GPIO_PORTB_AFSEL_R & (~BIT3)); // configure PB3 as GPIO (AFSEL = 0)
//
//    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & (~BIT3)); // clearing PB3
//
//    GPIO_PORTB_DATA_R |= BIT3; // Setting PB3
//    timer_waitMicros(50); // wating the minimum pulse amout
//    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & (~BIT3)); // clearing PB3
//    GPIO_PORTB_DIR_R = (GPIO_PORTB_DIR_R & (~BIT3));  // make bit 3 input to catch the incoming ping data
//
//    // setting timer stuff
//    GPIO_PORTB_AFSEL_R |= BIT3; // configure PB3 as timer part 1
//    GPIO_PORTB_PCTL_R = 0x00007000;     // configure PB3 as timer part 1
//    // the rest should be take care of
//
//}
//
//
//int ping_read(){
//    int local_start = 0;
//    int local_stop = 0;
//    send_pulse();
//    while (!done)
//    {
//    }
//    TIMER3_TBILR_R = 0xFFFF; // fill the initial value with FFFF
//    TIMER3_TBMR_R = (TIMER3_TBMR_R & (~0x0100)); // put in the new values
//    local_start = start_time;
//    local_stop = stop_time;
//    start_time = 0;
//    stop_time = 0;
//    return (local_start - local_stop)/16;
//}
//
//
//void ping_signal_ISR(){
//
//    if (!start_time)
//    {
//        start_time = TIMER3_TBR_R; // read the lowest 15 bits
//    }
//    else if(start_time){
//        stop_time = TIMER3_TBR_R ; // read the lowest 15 bits
//        done = true;
//    }
//    TIMER3_ICR_R |= 0x400; // clear the generated interrupt
//
//}


//#include "ping.h"
//#include "Timer.h"
//
//
//
//#define BIT0    0x01
//#define BIT1    0x02
//#define BIT2    0x04
//#define BIT3    0x08
//#define BIT4    0x10
//#define BIT5    0x20
//#define BIT6    0x40
//#define BIT7    0x80
//
//volatile int start_time = 0;
//volatile int stop_time = 0;
//
//
//
//void ping_init(void)
//{
//    SYSCTL_RCGCGPIO_R |= BIT1;    // Enable clock for Port B
//    SYSCTL_RCGCTIMER_R |= BIT3;   // Enable clock for Timer 3
//    timer_waitMillis(10);
//
//    GPIO_PORTB_DEN_R |= BIT3;     // Enable digital function on PB3
//    GPIO_PORTB_DIR_R &= ~BIT3;    // PB3 input
//    GPIO_PORTB_AFSEL_R |= BIT3;   // Enable alternate function on PB3
//    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFF0FFF) | 0x00007000;
//
//    // Configure Timer3B for edge-time capture mode
//    TIMER3_CTL_R &= ~0x100;       // Disable Timer3B while configuring
//    TIMER3_CFG_R = 0x04;          // Configure as 16-bit timer
//    TIMER3_TBMR_R = 0x07;         // Capture mode + edge-time mode
//    TIMER3_CTL_R |= 0xC00; // Capture on rising and falling edges
//    TIMER3_TBILR_R = 0xFFFF;      // Start value (max)
//    TIMER3_TBPR_R = 0xFF;         // Prescaler (max)
//    TIMER3_IMR_R |= 0x0400;       // Enable capture event interrupt
//
//    IntRegister(INT_TIMER3B, TIMER3B_Handler); // Register ISR
//    IntEnable(INT_TIMER3B);
//    IntMasterEnable();             // Enable global interrupts
//
//    //TIMER3_CTL_R |= 0x100;         // Enable Timer3B
//}
//
//void pulse_ping(void)
//{
//    // Make PB3 GPIO output
//    GPIO_PORTB_AFSEL_R &= ~BIT3;   // Disable alternate function
//    GPIO_PORTB_DIR_R |= BIT3;      // PB3 output
//    GPIO_PORTB_DATA_R &= ~BIT3;    // Clear PB3
//    timer_waitMicros(2);
//
//    GPIO_PORTB_DATA_R |= BIT3;     // Send trigger pulse
//    timer_waitMicros(50);          // 50 µs pulse
//    GPIO_PORTB_DATA_R &= ~BIT3;    // Clear PB3
//    timer_waitMicros(2);
//
//    // Switch PB3 back to input and timer capture
//    GPIO_PORTB_DIR_R &= ~BIT3;     // Input
//    GPIO_PORTB_AFSEL_R |= BIT3;    // Enable alternate function
//    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFF0FFF) | 0x00007000;
//    TIMER3_CTL_R |= 0x100;         // Enable Timer3B
//}
//
//void TIMER3B_Handler(void)
//{
//    TIMER3_ICR_R |= 0x400; // Clear capture interrupt
//
//    if (start_time == 0)
//    {
//        // Rising edge detected
//        start_time = TIMER3_TBR_R;
//    }
//    else
//    {
//        // Falling edge detected
//        stop_time = TIMER3_TBR_R;
//
//        // Reset for next measurement
//        TIMER3_CTL_R &= ~0x100;       // Disable Timer3B while configuring
//        TIMER3_TBILR_R = 0xFFFF; // fill the initial value with FFFF
//        TIMER3_TBMR_R = (TIMER3_TBMR_R & (~0x0100)); // put in the new values
//    }
//}


#include "ping.h"
#include "Timer.h"

#include <stdbool.h>
#include "driverlib/interrupt.h"  // For IntRegister, IntEnable, IntMasterEnable

#define BIT3 0x08

volatile int start_time = 0;
volatile int stop_time = 0;

void ping_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x02;  // Enable clock for Port B
    SYSCTL_RCGCTIMER_R |= 0x08; // Enable clock for Timer 3
    timer_waitMillis(10);

    GPIO_PORTB_DEN_R |= BIT3;   // Enable digital function on PB3
    GPIO_PORTB_DIR_R &= ~BIT3;  // PB3 input
    GPIO_PORTB_AFSEL_R |= BIT3; // Alternate function
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFF0FFF) | 0x00007000;

    TIMER3_CTL_R &= ~0x100;     // Disable Timer3B during config
    TIMER3_CFG_R = 0x04;        // 16-bit mode
    TIMER3_TBMR_R = 0x07;       // Capture mode + edge-time
    TIMER3_CTL_R |= 0x0C00;     // Capture both edges
    TIMER3_TBILR_R = 0xFFFF;    // Max interval
    TIMER3_TBPR_R = 0xFF;       // Prescaler
    TIMER3_IMR_R |= 0x0400;     // Enable capture interrupt

    IntRegister(INT_TIMER3B, TIMER3B_Handler);
    IntEnable(INT_TIMER3B);
    IntMasterEnable();
}

void pulse_ping(void)
{
    // Configure PB3 as GPIO output
    GPIO_PORTB_AFSEL_R &= ~BIT3;
    GPIO_PORTB_DIR_R |= BIT3;
    GPIO_PORTB_DATA_R &= ~BIT3;
    timer_waitMicros(2);

    GPIO_PORTB_DATA_R |= BIT3;  // Trigger pulse
    timer_waitMicros(50);
    GPIO_PORTB_DATA_R &= ~BIT3;
    timer_waitMicros(2);

    // Switch PB3 back to input and timer capture
    GPIO_PORTB_DIR_R &= ~BIT3;
    GPIO_PORTB_AFSEL_R |= BIT3;
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFF0FFF) | 0x00007000;

    TIMER3_CTL_R |= 0x100; // Enable Timer3B
}

void TIMER3B_Handler(void)
{
    TIMER3_ICR_R = 0x400; // Clear interrupt
    if (start_time == 0)
    {
        start_time = TIMER3_TBR_R; // Rising edge
    }
    else
    {
        stop_time = TIMER3_TBR_R;  // Falling edge
        TIMER3_CTL_R &= ~0x100;    // Disable Timer3B
    }
}
