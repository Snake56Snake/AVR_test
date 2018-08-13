/*
 * main.c
 *
 *  Created on: 24.06.2018
 *      Author: User
 */
#define F_CPU 4000000 // CPU Clock
#define LM75_ADDRESS 0b10010000  // The LM75 is hard wirerd to addres 1001xxx (A2 A1 A0)


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lib/i2cmaster.h"
#include "lib/lcd-routines.h"


char c_buffer[10];
int8_t i_test;
int8_t i_temperatur;
int8_t i_temperatur_comma;
int8_t i_buffer_I2C_0;
int8_t i_buffer_I2C_1;
int8_t i_interrupt;

//Interrupt Service Routine for INT0
ISR(INT0_vect)
{
	i_interrupt ++;
}

int main(void)
{
	DDRD = (1<<PD5) | (1<<PD6)	;  // LED as Output
	lcd_init();
	i2c_init();
    unsigned char ret;

	GICR = 1<<INT0;					// Enable INT0
	MCUCR = 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on rising edge

	sei();				//Enable Global Interrupt

    while (1)
    {

    	PORTD |= (1<<PD5); // LED1 On
    	lcd_clear();

		i_test ++;
		itoa( i_test, c_buffer, 10);			// display  test Counter
		lcd_setcursor(12,1);
		lcd_string(c_buffer);


		itoa( i_interrupt, c_buffer, 10);			// display  test Counter
		lcd_setcursor(0,2);
		lcd_string(c_buffer);

		// I2C Übertragung
		ret = i2c_start(LM75_ADDRESS+I2C_READ);
		if (ret){
			i2c_stop();

			lcd_setcursor(0,1);
			lcd_string("Fehler I2C");

		}
		else{

			i_buffer_I2C_0 = i2c_read(1);
			i_buffer_I2C_1 = i2c_read(0);
			i2c_stop();

			lcd_setcursor(0,1);
			lcd_string("Erfolg I2C");

			i_temperatur = i_buffer_I2C_0;

			if (i_buffer_I2C_1 & (1<<8)){
				i_temperatur_comma = 5;
			}
			else{
				i_temperatur_comma = 0;
			}
		} // Ende I2C übertragung


		itoa( i_temperatur, c_buffer, 10);
		if(i_temperatur_comma==5){
			strcat(c_buffer,",5");
		}
		else{
			strcat(c_buffer,",0");
		}
		lcd_setcursor(0,4);
		lcd_string(c_buffer);
		lcd_string("°C");

	    PORTD &= ~(1<<PD5); 	// LED1 Off
	    _delay_ms(100);
	    _delay_ms(100);
	    _delay_ms(100);
	    _delay_ms(100);
	    _delay_ms(100);
    }
    return (1);	// should never happen
}


