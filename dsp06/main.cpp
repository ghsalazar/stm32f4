/** 
    @file   main.cpp
    @author Gastón SALAZAR  <gaston_salazar@yahoo.com>
    
    @brief  A small example of an interrupt application.
*/

#include "mbed.h"

const float SAMPLING_PERIOD  = 2.0;

Serial      serial(USBTX, USBRX);
InterruptIn button(USER_BUTTON);

volatile unsigned short interruptCount;

void
count()
{
    interruptCount++;
}

void
setup()
{
    button.fall(&count);

    interruptCount = 0;

    serial.baud(9600);
    serial.format(8, SerialBase::None, 1);
}

void
loop()
{
    serial.printf("Frequency = %f\r\n", interruptCount/SAMPLING_PERIOD);
    interruptCount = 0;
    wait(SAMPLING_PERIOD);
}

int
main()
{
    setup();
    while(1)
        loop();
}
