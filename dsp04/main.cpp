/** @file   main.c
    @author Gastón SALAZAR <gaston_salazar@yahoo.com>
    @brief  Display a (hexadecimal-) number sequence on a display

# Interface #

## Physical connections ##

Port    Segment Color
----    ------- -----
PB0     A       blue
PB1     B       red
PB2     C       yellow
PB3     D       green
PB4     E       orange
PB5     F       violet
PB6     G       gray

## LEDS on a 7-segment Display ##

 AAA
F   B
F   B
F   B
 GGG
E   C
E   C
E   C
 DDD

*/

#include "mbed.h"

const unsigned long     DELAY   = 5000000UL;
const unsigned short    DISPLAY = 0x7F;

// The programming language is C++, not C as previously done.
DigitalOut  led(LED1);
PortOut     myDisplay(PortB, DISPLAY);
DigitalIn   myButton(USER_BUTTON);

typedef enum {
    ZERO =   0xc0,
    ONE =    0xf9,
    TWO =    0xa4,
    THREE =  0xb0,
    FOUR =   0x99,
    FIVE =   0x92,
    SIX =    0x82,
    SEVEN =  0xf8,
    EIGHT =  0x80,
    NINE =   0x90,
    CA =     0x88,
    CB =     0x83,
    CC =     0xc6,
    CD =     0xa1,
    CE =     0x86,
    CF =     0x8e
} digits;

// This was handle in automation, some time ago, with a cam or "drum".
// And in electronics, it was implemented with a decoder in a ROM.
// Of course you could implemented it with logic gates.
const unsigned short int segments[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE,
                                       SIX, SEVEN, EIGHT, NINE,
                                       CA, CB, CC, CD, CE, CF
                                      };

void setup()
{
    myDisplay = ZERO;
}

void loop()
{
    static short unsigned   display_count   = 0;
    static long unsigned    delay_count     = DELAY;

    if (!delay_count) {
        display_count++;
        display_count &= 0x0f;
        myDisplay = segments[display_count];
        delay_count = DELAY;
    }

    if (myButton == 1)    // User button NOT pressed
        delay_count--;
}

int main()
{
    setup();
    while(1) {
        loop();
    }
}
