//-----------------------------------------------------------
//Shift_Registers.cpp
//Chris Hamby
//Last Updated: 6-Apr-2020
//-----------------------------------------------------------
//this file includes:
//-functions to interface Arduino GPIO with Shift Registers
//-contextualized to make sense with the LED matrix
//-----------------------------------------------------------
#include "Shift_Registers.hpp"


// Basic Shift Register Procedure:
// SRCLR is kept at HIGH
// SER_LED is updated
// SER_VCC is updated
// SRCLK pulses
// if you want to update LEDS, pulse RCLK before SRCLK rises again


// pushByte functions perform bitwise operations, this helps
unsigned char checkBit[] = {BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7};



// pulses SRCLR to clear the storage register
void resetRegister() 
{
  digitalWrite(SRCLR, CLEAR_ALL);
  digitalWrite(SRCLR, 1-CLEAR_ALL);
}



// initialize the pin modes and clear the shift registers
void initShiftRegisterPins() 
{
  pinMode(SRCLK_VCC, OUTPUT);   // pin numbers are defined in Shift_Registers.h
  pinMode(SER_VCC, OUTPUT);
  pinMode(SER_LED, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(SRCLR, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(OUT_ENABLE, OUTPUT);
  resetRegister();               // Start running from a known state
}



// Push a byte into the LED storage register
// This determines which columns to show
// The storage isn't sent to the output during this function
// So feel free to push as many bytes as needed
void pushByte_LED(char myByte) {
  int i;
  for(i=0; i<BYTE_SIZE; i++) 
  {
    if(!(myByte & checkBit[i]))
      pushOff_LED();
    else
      pushOn_LED();
  }
}



// Push a byte into the VCC storage register
// This determines which rows to show
void pushByte_VCC(char myByte) {
  int i;
  for(i=BYTE_SIZE-1; i>=0; i--){
    if(!(myByte & checkBit[i]))
      pushOff_VCC();
    else
      pushOn_VCC();
  }
}


//These are used by the pushByte functions
//Load "ON" value to the VCC Shift Register's SERIAL port
//i.e. The next accepted value will be "ON"
//Then pulse SRCLK to "push" the value to the SR buffer
void pushOn_VCC() {
  digitalWrite(SER_VCC, VCC_ON);
  pulseClock(SRCLK_VCC);
}
void pushOff_VCC() {
  digitalWrite(SER_VCC, VCC_OFF);
  pulseClock(SRCLK_VCC);
}
void pushOn_LED() {
  digitalWrite(SER_LED, LED_ON);
  pulseClock(SRCLK);
}
void pushOff_LED() {
  digitalWrite(SER_LED, LED_OFF);
  pulseClock(SRCLK);
}



// pulse a clock pin (works for any clock)
// The pulse only needs to be high for 30ns 
// I don't think the arduino will go quicker than this
// A waiting period can be added if things don't work
void pulseClock(int CLK_PIN) {
  digitalWrite(CLK_PIN, CLK_HIGH);
  digitalWrite(CLK_PIN, CLK_LOW);
}



//this function push the storage to the output
//note that RCLK is shared by the LED and VCC SRs
void refreshDisplay() {
  pulseClock(RCLK);
}
