/** 
    @file   main.cpp
    @author Gastón SALAZAR  <gaston_salazar@yahoo.com>
*/

#include "mbed.h"

const unsigned long DELAY   = 5000000UL;

Serial  serial(USBTX, USBRX);

void 
setup()
{
    serial.baud(9600);
    serial.format(8, SerialBase::None, 1);
    
    serial.printf("Hello, world!\r\n\r\n");
}

void
loop()
{
    static unsigned short   display_count   = 0;
    static unsigned long    delay_count     = DELAY;    

    if (delay_count == 0)
      {
        serial.printf("Display: %x\r\n", display_count);
        display_count++;
        display_count &= 0x0F;
        delay_count = DELAY;
      }
    
    delay_count--;
}

int main()
{
    setup();
    while(1)
        loop();
}
