#ifndef MY_DATA
#define MY_DATA

#include "macros.hpp"

// how many data registers are there
#define NUM_REGS 0xFF

namespace data
{
    extern uint8_t reg[NUM_REGS];

    extern void init_reg();
    extern void show_reg();
    extern uint8_t get_reg(uint8_t addr);
    extern uint8_t set_reg(uint8_t addr, uint8_t val);

}



#endif 
