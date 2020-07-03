//modular i2c functions


#include "i2c_mod.hpp"


namespace i2c{
    // this function is called when the master i2c device sends us data
    void foo(int x) {
        unsigned char my_addr = 0x00;
        unsigned char new_val = 0x00;


        // get the address, if available
        if(Wire.available() <= 0)    return;
        my_addr = Wire.read();


        // get the data, if available
        if(Wire.available() <= 0)    return;
        new_val = Wire.read();


        // clear any additional data received
        while(Wire.available() > 0)  Wire.read();


        data::set_reg( my_addr , new_val );
        //data::show_reg();
    }



    void bar() {
        //nothing happens when data is requested 
    }



    // note that this definition has to be below the definition of the onReceive function
    void init_i2c(int a){
        Wire.begin(a);
        Wire.onReceive(foo);
        Wire.onRequest(bar);
    }
}
