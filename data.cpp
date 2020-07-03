#include "data.hpp"

namespace data{
    uint8_t reg[NUM_REGS] = {0};
    
    void init_reg(){
        // set all values in the data registers to 0
        int i;
        for(i=0; i<NUM_REGS; i++)
            reg[i] = 0;
    }
    
    uint8_t set_reg(uint8_t addr, uint8_t val){
        // give a register a new value 
        reg[addr] = val;
        return reg[addr];
    }

    
    uint8_t get_reg(uint8_t addr){
        // get a register's contents 
        return reg[addr];
    }


    void show_reg(){
        // print the contents of non-zero registers to serial 
        int i;
        for(i=0; i<NUM_REGS; i++){
            if(reg[i] != 0){
                Serial.print("Value in Register ");
                Serial.print(i);
                Serial.print(" = ");
                Serial.println((char)(reg[i]));
            }
        }
    }
}
