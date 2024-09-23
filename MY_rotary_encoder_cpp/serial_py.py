import pigpio
import time

# Khởi tạo pigpio và kết nối với daemon pigpiod
pi = pigpio.pi()

if not pi.connected:
    exit(0)

# Mở cổng serial (ví dụ: /dev/serial0) với tốc độ baud là 9600
ser = pi.serial_open("/dev/ttyS0", 115200)
counter = 0
sign=0
T = 0

Re_buf = [0] * 11
a = [0]*3
w = [0]*3
angle = [0]*3

try:
    while True:
        # Kiểm tra có dữ liệu trong buffer
        while(pi.serial_data_available(ser)):
            # Re_buf[counter]=chr(pi.serial_read_byte(ser))
            Re_buf[counter]=pi.serial_read_byte(ser)
            # Re_buf[counter] = hex(Re_buf[counter])
            # print(Re_buf[counter])
            if(counter==0 and Re_buf[0]!= 85):#0x55):
                #print("continue ... ", counter, "rebuf: ", Re_buf[0])
                break                   
            counter = counter + 1
            # print(counter)       
            if(counter==11):             
                counter=0               
                sign=1
            # count, data = pi.serial_read(ser)
            # if count > 0:
            
            #     print("Received data:", data.decode('utf-8'))

            if(sign):
                sign=0
                #print("printing result ...")
                if(Re_buf[0]== 85):#0x55):      
                    if Re_buf[1] == 81: #0x51:
                        a[0] = ((Re_buf [3]<<8) | Re_buf [2])/32768.0*16
                        a[1] = ((Re_buf [5]<<8)| Re_buf [4])/32768.0*16
                        a[2] = ((Re_buf [7]<<8)| Re_buf [6])/32768.0*16
                        T = ((Re_buf [9]<<8)| Re_buf [8])/340.0+36.25
                        #print("accel ...")
                    elif Re_buf[1] == 82:#0x52:
                        w[0] = ((Re_buf [3]<<8)| Re_buf [2])/32768.0*2000
                        w[1] = ((Re_buf [5]<<8)| Re_buf [4])/32768.0*2000
                        w[2] = ((Re_buf [7]<<8)| Re_buf [6])/32768.0*2000
                        T = ((Re_buf [9]<<8)| Re_buf [8])/340.0+36.25
                        #print("angular ...")
                    elif Re_buf[1] == 83: #0x53:
                        angle[0] = ((Re_buf [3]<<8)| Re_buf [2])/32768.0*180
                        angle[1] = ((Re_buf [5]<<8)| Re_buf [4])/32768.0*180
                        angle[2] = ((Re_buf [7]<<8)| Re_buf [6])/32768.0*180
                        T = ((Re_buf [9]<<8)| Re_buf [8])/340.0+36.25
                        #print("angle ...")

                        print("a: ", a[0], " ", a[1], " ", a[2])
                        #print("w: ", w[0], " ", w[1], " ", w[2])
                        #print("angle: ", angle[0], " ", angle[1], " ", angle[2])
            
        # time.sleep(0.1)  # Đợi một khoảng thời gian ngắn trước khi đọc lại


except KeyboardInterrupt:
    pass
finally:
    # Đóng cổng serial và ngắt kết nối
    pi.serial_close(ser)
    pi.stop()
