/*
 * servo.c
 *
 *  Created on: Nov 7, 2025
 *      Author: jaypp123
 */



#include "servo.h"
#include "Timer.h"
#include <inc/tm4c123gh6pm.h>

void servo_init(void){
    SYSCTL_RCGCGPIO_R |= 0x02;
    SYSCTL_RCGCTIMER_R |= 0x02;
    while ((SYSCTL_PRGPIO_R & 0x02) == 0);


    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R &= ~0x00F00000;
    GPIO_PORTB_PCTL_R |= 0x00700000;


    GPIO_PORTB_DEN_R |= 0x20;
    GPIO_PORTB_DIR_R |= 0x20;

    TIMER1_CTL_R &= ~0x100;
    TIMER1_CFG_R = 0x04;
    TIMER1_TBMR_R |= 0x0A;
    TIMER1_CTL_R &= ~0x4000;
    TIMER1_TBPR_R  |= 0x04;
    TIMER1_TBILR_R = 0xE200;
    TIMER1_TBMATCHR_R = 0xA700;
    TIMER1_TBPMR_R = 0x04;
    TIMER1_CTL_R |= 0x100;
}






//int servo_move(int degrees){
//
//
////
////    TIMER1_TBILR_R = 0xE200;     // Lower 16 bits of 320,000 (20 ms period)
////    TIMER1_TBPR_R  = 0x04;       // Upper 8 bits of 320,000
////
////    TIMER1_TBMATCHR_R = 0x45e0;  // Lower 16 bits of 304,000 (1 ms high pulse)
////    TIMER1_TBPMR_R    = 0x04;
//
//// 0x4bed8; for 0 deg  0x445e0; for 360
//
//
//    int32_t match_deg0 = 0x4bed8;
//    int32_t match_deg180 = 0x445e0;
//
//
//    if (degrees < 0) degrees = 0;
//    if (degrees > 180) degrees = 180;
//
//
//    float ratio = degrees/ 180.0;
//    int32_t match_value = (int32_t) (match_deg0 + ratio * (match_deg180-match_deg0));
//
//
//        TIMER1_TBMATCHR_R = match_value & 0xFFFF;  // Lower 16 bits of 304,000 (1 ms high pulse)
//        TIMER1_TBPMR_R    = (match_value >> 16) & 0xFF;
//    return match_value;
//}


int servo_move(int degrees) {
    if (degrees < 0) degrees = 0;
    if (degrees > 180) degrees = 180;

    // Correct match values for 0° and 180°
    int32_t match_deg0 = 0x4CB50;   // 304,000 ticks for 0°
    int32_t match_deg180 =0x45000; // 288,000 ticks for 180°

    float ratio = degrees / 180.0;
    int32_t match_value = (int32_t)(match_deg0 + ratio * (match_deg180 - match_deg0));

    TIMER1_TBMATCHR_R = match_value & 0xFFFF; // Lower 16 bits
    TIMER1_TBPMR_R = (match_value >> 16) & 0xFF; // Upper 8 bits

    return match_value;
}

//#include "servo.h"
//#include <inc/tm4c123gh6pm.h>
//#include "Timer.h"
//
//#define SYS_CLK 16000000
//#define PWM_PERIOD_MS 20
//#define TICKS_PER_MS (SYS_CLK / 1000)
//#define PWM_PERIOD_TICKS (PWM_PERIOD_MS * TICKS_PER_MS)
//
//void servo_init(void) {
//    SYSCTL_RCGCTIMER_R |= 0x02;    // Enable Timer1
//    SYSCTL_RCGCGPIO_R |= 0x02;     // Enable Port B
//    GPIO_PORTB_AFSEL_R |= 0x20;    // PB5 alternate function
//    GPIO_PORTB_PCTL_R &= ~0x00F00000;
//    GPIO_PORTB_PCTL_R |= 0x00700000; // Configure PB5 for T1CCP1
//    GPIO_PORTB_DEN_R |= 0x20;
//
//    TIMER1_CTL_R &= ~0x0100;       // Disable Timer1B
//    TIMER1_CFG_R = 0x04;           // 16-bit mode
//    TIMER1_TBMR_R = 0x0A;          // PWM mode, periodic
//    TIMER1_TBILR_R = PWM_PERIOD_TICKS & 0xFFFF;
//    TIMER1_TBPR_R = PWM_PERIOD_TICKS >> 16;
//
//    int match_val = degrees_to_match(90.0); // Start at 90°
//    TIMER1_TBMATCHR_R = match_val & 0xFFFF;
//    TIMER1_TBPMR_R    = match_val >> 16;
//
//    TIMER1_CTL_R |= 0x0100;        // Enable Timer1B
//}
//
//int degrees_to_match(float degrees) {
//    float pulse_width_ms = 1.0 + (degrees / 180.0);
//    int high_ticks = (int)(pulse_width_ms * TICKS_PER_MS);
//    return PWM_PERIOD_TICKS - high_ticks;
//}
//
//int servo_move(float degrees) {
//    int match_val = degrees_to_match(degrees);
//    TIMER1_TBMATCHR_R = match_val & 0xFFFF;
//    TIMER1_TBPMR_R = match_val >> 16;
//    return match_val;
//}
