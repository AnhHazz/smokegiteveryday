#ifndef BTS7960__HPP
#define BTS7960__HPP

class bts7960 
{
    public:
        bts7960(int R_EN, int L_EN, int RPWM, int LPWM);
        /*
            This function set mode for gpio pins as output
        */
        void set_pwm(int pwm_left, int pwm_right);
        /*
            set pwm for motors
        */
        void disable_motor(int number = 0);
        /*
            disable motors
            0 for all motors, 
            1 for left, 2 for right
        */
    private:
        int R_EN, L_EN, RPWM, LPWM;

};
#endif