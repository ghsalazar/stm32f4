/** 
    @file   main.cpp
    @author Gastón SALAZAR  <gaston_salazar@yahoo.com>
    
    @brief  dsp07 - A small example of an PWM out
*/

#include "mbed.h"
#include "arm_math.h"

const float SAMPLING_PERIOD = 1.0/60.0;
const float SIGNAL_PERIOD   = 10.0;

PwmOut  led(LED1);

void
setup()
{
    led.period(SAMPLING_PERIOD);
}

void
loop()
{
    static unsigned long count   = 0;    
    
    float   output  = 0;
    
    output  = sin(2*PI/SIGNAL_PERIOD*SAMPLING_PERIOD*count);
    if (output <= 0)
        output = 0;
    led.write(output);
    count++;
    
    wait(SAMPLING_PERIOD);
}

int main()
{
    setup();
    while(1)
        loop();
}
