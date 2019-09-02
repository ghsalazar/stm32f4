/** @file   main.S
    @author Gastón Hugo SALAZAR SILVA <gaston_salazar@yahoo.com>
    @author Abraham RODRÍGUEZ GALEOTTE

    @brief  A blink program for the STM32F446re. It implements a state machine.
            It requires a basic link script. The interrupts vectors must be
            defined.

    This example is used as a didactical resource.
*/
    .syntax unified
    .arch   armv7e-m
    .cpu    cortex-m4
    .thumb

/**
    Interface

    @def    LED
    @brief  The bit address of pin 5 on port A.

    @def    DELAY
    @brief  The number of loops to execute before changing th state of LED.
*/
    .equ    LED,            (1 << 5)
    .equ    DELAY,          5000000

@ Register for enabling the AHB1 clock for GPIOA
    .equ    RCC_AHB1ENR,    0x40023830
    .equ    GPIOAEN,        (1 << 0)

@ Base address of port-A registers
    .equ    GPIOA,          0x40020000

@ Offsets of the registers for port X, using as base the port address
    .equ    GPIO_MODER,     0x00
    .equ    GPIO_PUPDR,     0x0c
    .equ    GPIO_ODR,       0x14

@ Bit addresses in the port registers, in order to configure the behaviour of the output pin
    .equ    RESET_MODER5,   (3 << 10)
    .equ    SET_MODER5,     (1 << 10)
    .equ    RESET_PUPDR5,   (3 << 10)

/**
    @fn     _start
    @brief  After the reset the fuction _start is the entry point.
*/
    .text
    .global _start
    .type   _start,   %function
_start:
/*
    Machine setup
*/
    @ Enable port A
    ldr r0, =RCC_AHB1ENR    @ r0 = RCC_AHB1ENR
    ldr r1, [r0]            @ r1 = *r0
    orr r1, r1, GPIOAEN     @ r1 = r1 | GPIOAEN
    str r1, [r0]            @ *r0 = r1

    @ A minimal initialization for PA5 as output (LED) on the STM32F446re
    ldr r4, =GPIOA

    ldr r1, [r4, GPIO_MODER]    @ r1 = r4[GPIO_MODER]
    bic r1, r1, RESET_MODER5    @ r1 = r1 & ~RESET_MODER5
    orr r1, r1, SET_MODER5
    str r1, [r4, GPIO_MODER]    @ r4[GPIO_MODER] = r1

    ldr r1, [r4, GPIO_PUPDR]
    bic r1, r1, RESET_PUPDR5
    str r1, [r4, GPIO_PUPDR]

/*
    State initilization
*/
    @ LED = 0
    ldr r1, [r4, GPIO_ODR]
    bic r1, r1,LED
    str r1, [r4, GPIO_ODR]

    ldr r0, =DELAY

loop:
/*
    State update
*/
    cbnz    r0, wait           @ if (r0!=0) goto wait
    ldr     r1, [r4, GPIO_ODR]
    eor     r1, r1, LED        @ r1 = r1 ^ LED
    str     r1, [r4, GPIO_ODR]
    ldr     r0, =DELAY
wait:
    sub     r0, r0, 1           @ r0 = r0 - 1
    b       loop                @ goto loop

    bx      lr  @ end of function main, to never be reached

    .size   _start, . - _start

    .section    .int_vector_table, "a", %progbits
    .type       basic_vectors,  %object
basic_vectors:
    .word   _estack
    .word   _start
    .size   basic_vectors, . - basic_vectors
