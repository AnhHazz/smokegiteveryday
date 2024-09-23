#include <pigpio.h>
#include <iostream>

int main() 
{
    if (gpioInitialise() < 0) 
    {
        return 1;
        std::cout << "can't init\n";
    }
    unsigned char Re_buf[11],counter=0;
    unsigned char sign=0;
    float a[3],w[3],angle[3],T;

    int serial = serOpen("/dev/ttyS0",115200,0);
    if(!(serial >= 0))
    {
        std::cout << "can't open serial port" << std::endl;
        return 0;
    }
    while (1)
    {
    while(serDataAvailable(serial))
    {
        Re_buf[counter]=(unsigned char)serReadByte(serial);
        if(counter==0&&Re_buf[0]!=0x55) continue;      //第0号数据不是帧头              
        counter++;       
        if(counter==11)             //接收到11个数据
        {    
            counter=0;               //重新赋值，准备下一帧数据的接收 
            sign=1;
        }
        if (sign)
        {
            sign=0;
            if(Re_buf[0]==0x55)      //检查帧头
            {  
                switch(Re_buf [1])
                {
                case 0x51:
                    a[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*16;
                    a[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*16;
                    a[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*16;
                    T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
                    break;
                case 0x52:
                    w[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*2000;
                    w[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*2000;
                    w[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*2000;
                    T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
                    break;
                case 0x53:
                angle[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*180;
                    angle[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*180;
                    angle[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*180;
                    T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
                    
                    std::cout << "a: a[0] " << a[0] << " a[1] " << a[1] << " a[2] " << a[2] << std::endl;
                    break;
	            } 
            }
        }
      
    }
    }
}
