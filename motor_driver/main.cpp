#include "bts7960.hpp"
#include "rotary_encoder.hpp"

#include <chrono>
#include <ctime>
#include <unistd.h>

#include <pigpio.h>
#include <iostream>

volatile int pos = 0;
void callback(int way)
{
   pos += way;
}

int main() 
{
    // using namespace std::chrono;
    // std::chrono::time_point<std::chrono::system_clock> start, end;
    
    time_t start, end;
    if (gpioInitialise() < 0) return 1;
    re_decoder dec(20, 21, callback);
    bts7960 motor(17,27,23,24);

    // start = std::chrono::system_clock::now();
    // end = std::chrono::system_clock::now();
    time(&start);
    sleep(1);
    time(&end);
    std::cout << "diff time: " << difftime(end,start) << std::endl;
    // while(difftime(end, start) < 3)
    // {
    //     motor.set_pwm(0,50);
    //     time(&end);
    // }
    while(pos < 390)
    {
        motor.set_pwm(0,30);
        time(&end);
    }
    // std::cout << "" << difftime(end,start) << std::endl;

    //motor.set_pwm(255,0);
    //sleep(3);
    motor.set_pwm(0,0);
    // gpioSetTimerFunc(0, 2000, bFunction);
    std::cout << "pos=" << pos << std::endl;
    gpioTerminate();
}