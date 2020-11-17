/*!
\file   Blink.c
\date   2020-11-17
\author Jose Galindez <jrgalindez@unicauca.edu.co>
\brief  Example blink.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2020. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/
#include <xc.h>
#include <stdbool.h>
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/

#include "fuses.h"
#include "pinout.h"


void secuencial_Efecto1(void);
void secuencial_Efecto2(void);
void secuencial_Efecto3(void);
void secuencial_Efecto4(void);
void secuencial_Efecto5(void);
void secuencial_Efecto6(void);
void retardo_velocidad(void);
unsigned int lectura(void);


unsigned char efecto = 1;
unsigned long velocidad = 1;


#define INPUT 1
#define OUTPUT 0

#define HIGH 1
#define LOW 0

int main(void) {
    TRISD = 0;
    LATD = 0;
    efecto_pin = INPUT;
    velocidad_pin = INPUT;
    INTCON2bits.RBPU = 0;
    while (1) {
        //efecto
        
        switch (efecto) {
            case 1: secuencial_Efecto1();
                break;
            case 2: secuencial_Efecto2();
                break;
            case 3: secuencial_Efecto3();
                break;
            case 4: secuencial_Efecto4();
                break;
            case 5: secuencial_Efecto5();
                break;
            case 6: secuencial_Efecto6();
                break;
        }
    }
    return 1;
}

void secuencial_Efecto1(void) {
    for (int i = 0; i < 8; i++) {
        LATD = 1 << i;
        retardo_velocidad();
        if (lectura()){break;};
    }
}

void secuencial_Efecto2(void) {
    for (int i = 0, j = 7; i < 8; i++, j--) {
        LATD = (1 << i) + (1 << j);
        retardo_velocidad();
        if (lectura()){break;};
    }
}

void secuencial_Efecto3(void) {
    for (int i = 0; i < 9; i++) {
        LATD = (1 << i) - 1;
        retardo_velocidad();
        if (lectura()){break;};
    }
}

void secuencial_Efecto4(void) {
    volatile unsigned int m=0,n=0;
    for (int i = 0; i < 5; i++) {
        LATD = m+n;
        m += (1 << i) & 0x0f;
        n += (1 << (7-i)) & 0xf0;
        retardo_velocidad();
        if (lectura()){break;};
    }
}

void secuencial_Efecto5(void) {
    for (int i = 8; i >= 0; i--) {
        LATD = 1 << i;
        retardo_velocidad();
        if (lectura()){break;};
    }
}

void secuencial_Efecto6(void) {
    for (int i = 0; i < 7; i++) {
        LATD = 3 << i;
        retardo_velocidad();
        if (lectura()){break;};
    }
}

unsigned int lectura(void) {
    if (!efecto_value) {
        __delay_ms(50);
        if(++efecto>6){efecto=1;}
        return 1;
    }
    if (!velocidad_value) {
        __delay_ms(50);
        if(++velocidad==5){velocidad=1;}
    }
    return 0;
}

void retardo_velocidad(void){
    if(velocidad==1){__delay_ms(50);}
    else if(velocidad==2){__delay_ms(100);}
    else if(velocidad==3){__delay_ms(200);}
    else if(velocidad==4){__delay_ms(400);}
}
