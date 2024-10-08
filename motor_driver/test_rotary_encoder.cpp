#include <iostream>

#include <pigpio.h>

#include "rotary_encoder.hpp"

/*

REQUIRES

A rotary encoder contacts A and B connected to separate gpios and
the common contact connected to Pi ground.

TO BUILD

g++ -o rot_enc_cpp test_rotary_encoder.cpp rotary_encoder.cpp -lpigpio -lrt

TO RUN

sudo ./rot_enc_cpp

*/

void callback(int way)
{
   static int pos = 0;

   pos += way;

   std::cout << "pos=" << pos << std::endl;
}

int main(int argc, char *argv[])
{
   if (gpioInitialise() < 0) return 1;

   re_decoder dec(7, 8);
   long int old_pos = 0;
   while (1)
{
	if(dec.pos != old_pos)
{
		std::cout << "pos: " << dec.pos << std::endl;
		old_pos = dec.pos;
}
 }  
   dec.re_cancel();

   gpioTerminate();
}

