
#include "mbed.h"
Serial pc(USBTX, USBRX);
SPI adc(NC, p6, p7);
DigitalOut cs(p8);
Timer timer;
int main() {
    pc.baud(115200);
    adc.format(16, 3);
    adc.frequency(40000000);
    timer.start();
    pc.printf("count,volt,time\r\n");
    
       while(1){
        cs=0;
        int val = adc.write(0x00)>>6;
        pc.printf("%d, %f, %f\r\n", val, (float)val/256*3.3, timer.read());
        cs=1;
        wait_ms(10);
        
    }
}