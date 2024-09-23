#include "bts7960.hpp"
#include <iostream>
#include <pigpio.h>

bts7960::bts7960(int R_EN, int L_EN, int RPWM, int LPWM)
{
    this->R_EN = R_EN;
    this->L_EN = L_EN;
    this->RPWM = RPWM;
    this->LPWM = LPWM;
    gpioSetMode(R_EN, PI_OUTPUT);
    gpioSetMode(L_EN, PI_OUTPUT);
    gpioSetMode(RPWM, PI_OUTPUT);
    gpioSetMode(LPWM, PI_OUTPUT);

    gpioWrite(R_EN, PI_HIGH);
    gpioWrite(L_EN, PI_HIGH);
   

    gpioSetPWMrange(RPWM, 255); 
    gpioSetPWMrange(LPWM, 255); 

    
    gpioPWM(RPWM, 0);
    gpioPWM(LPWM, 0);


    gpioSetPWMfrequency(RPWM, 500);
    gpioSetPWMfrequency(LPWM, 500);
}

void bts7960::set_pwm(int pwm_left, int pwm_right)
{
    gpioPWM(RPWM, pwm_right);
    gpioPWM(LPWM, pwm_left);
}

void bts7960::disable_motor(int number)
{
    switch (number)
    {
        case 0:
            gpioWrite(R_EN, PI_LOW);
            gpioWrite(L_EN, PI_LOW);
            break;
        case 1:
            gpioWrite(L_EN, PI_LOW);
            break;
        case 2:
            gpioWrite(R_EN, PI_LOW);
            break;
        default:
            std::cout << "Invalid parameter, valid parameter are: 0 1 2 for both, right, left disable" << std::endl;
            break;
    }
}