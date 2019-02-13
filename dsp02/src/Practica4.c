/// @file Practica3_aa1.c
/// @autor Gaston H. SALAZAR SILVA
/// @brief Práctica 3 - Actividad de aprendizaje autónomo

///
/// Configurar PB5 como flotante
// Evidencia:

// Interfaz
#define DISPLAY GPIOC_ODR

// rojo       PC9
// azul       PC8
// violeta    PC13
// gris       PC14
// naranja    PC12
// verde      PC11
// amarillo   PC10


// Constantes para los 7 segmentos en anodo común
typedef enum {
       CERO =     0xc0,
       UNO =      0xf9,
       DOS =      0xa4,
       TRES =     0xb0,
       CUATRO =   0x99,
       CINCO =    0x92,
       SEIS =     0x82,
       SIETE =    0xf8,
       OCHO =     0x80,
       NUEVE =    0x90,
       CA =       0x88,
       CB =       0x83,
       CC =       0xc6,
       CD =       0xa1,
       CE =       0x86,
       CF =       0x8e
} digits;

const unsigned short int segmentos[] = {CERO, UNO, DOS, TRES, CUATRO, CINCO,
                                        SEIS, SIETE, OCHO, NUEVE,
                                        CA, CB, CC, CD, CE, CF};

// setup() se divide en dos procedimientos.
void conf_maq();
void ini_var();
// loop()
void proceso1();

void main()
{
 conf_maq();
 ini_var();
     
 while(1)
 {
  proceso1();
 }
}

void proceso1()
{
 static short int contador = 0;
 DISPLAY = segmentos[contador] << 8;
 contador++;
 contador &= 0x0f;
 Delay_ms(1000);
}

void ini_var()
{
 DISPLAY &= 0x00 << 8;
}

void conf_maq()
{
 RCC_AHB1ENR |= 1 << GPIOCEN;
 
 GPIOC_MODER &= ~(0b11 <<  (2*8)) & ~(0b11 <<  (2*9)) & ~(0b11 << (2*10))
             & ~(0b11 << (2*11)) & ~(0b11 << (2*12)) & ~(0b11 << (2*13))
             & ~(0b11 << (2*14)) & ~(0b11 << (2*15));
 GPIOC_MODER |= (0b01 <<  (2*8)) | (0b01 <<  (2*9)) | (0b01 << (2*10))
             |  (0b01 << (2*11)) | (0b01 << (2*12)) | (0b01 << (2*13))
             |  (0b01 << (2*14)) | (0b01 << (2*15));

 GPIOC_OTYPER |= (0b1 <<  8) | (0b1 <<  9) | (0b1 << 10) | (0b1 << 11)
              |  (0b1 << 12) | (0b1 << 13) | (0b1 << 14)|  (0b1 << 15);

 GPIOC_OSPEEDR &= ~(0b11 <<  2*8) & ~(0b11 <<  2*9) & ~(0b11 << 2*10)
               & ~(0b11 << 2*11) & ~(0b11 << 2*12) & ~(0b11 << 2*13)
               & ~(0b11 << 2*14) & ~(0b11 << 2*15);
 GPIOC_OSPEEDR |= (0b01 <<  2*8) | (0b01 <<  2*9) | (0b01 << 2*10)
               |  (0b01 << 2*11) | (0b01 << 2*12) | (0b01 << 2*13)
               |  (0b01 << 2*14) | (0b01 << 2*15);

 GPIOC_PUPDR &= (0b11 <<  2*8) & ~(0b11 <<  2*9) & ~(0b11 << 2*10)
             & ~(0b11 << 2*11) & ~(0b11 << 2*12) & ~(0b11 << 2*13)
             & ~(0b11 << 2*14) & ~(0b11 << 2*15);
}