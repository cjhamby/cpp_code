//-------------------------------------------------
//Shift_Registers.hpp
//Chris Hamby
//Last Updated: 25-Feb-2019
//-------------------------------------------------
//this file includes:
//-Shift register macros 
//-Shift register function declarations
//-------------------------------------------------
#ifndef INCL_SR
#define INCL_SR

#include "macros.hpp"

#define BYTE_SIZE   8
#define EMPTY       0
#define CLEAR_BYTE  0x00

//PINS
#define SRCLK_VCC   7      // The VCC Shift Register has its own SRCLK 
#define SER_VCC     8      // column (common anode) control
#define SER_LED     9      // serial data line
#define SRCLK      10      // rising edge shifts bits over
#define SRCLR      11      // driving low clears the register
#define RCLK       12      // rising edge stores data from register
#define OUT_ENABLE 14      // high enables outputs 


// pushByte functions use this for bitwise operations
extern unsigned char checkBit[8];
#define BIT0 0x80  // The MSB is sent to the shift register first
#define BIT1 0x40  
#define BIT2 0x20  
#define BIT3 0x10
#define BIT4 0x08
#define BIT5 0x04
#define BIT6 0x02
#define BIT7 0x01



// State Definitions
#define LED_OFF     1   //  LED pins are cathodes (-)
#define LED_ON      0   //  these define the state of the LED (not the applied voltage)
#define VCC_OFF     0   //  VCC pins are anodes (+)
#define VCC_ON      1   //  these define the state of the VCC pin
#define CLK_LOW     0   //  Clock Low
#define CLK_HIGH    1   //  Clock High 
#define CLEAR_ALL   0   //  SRCLR is never used - this ensures that
#define LEDS_ON     0   //  OUT_ENABLE uses this
#define LEDS_OFF    1   //  OUT_ENABLE uses this 


extern void initShiftRegisterPins();
extern void resetRegister();
extern void pulseClock(int CLKPIN);

extern void pushOn_LED();
extern void pushOff_LED();
extern void pushOn_VCC();
extern void pushOff_VCC();

extern void pushByte_LED(char myByte);
extern void pushByte_VCC(char myByte);
extern void refreshDisplay();

#endif