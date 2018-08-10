/*
 * main.c
 *
 *  Created on: 24.06.2018
 *      Author: User
 */
// #define F_CPU 4000000 // CPU Clock
#define LM75_ADDRESS 0b10010000  // The LM75 is hard wirerd to addres 1001xxx (A2 A1 A0)


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lib/i2cmaster.h"
#include "lib/lcd-routines.h"


char c_buffer[10];
int8_t i_test;
int8_t i_temperatur;
float f_temperatur;
int8_t i_buffer_I2C;
int8_t i_buffer_I2C_2;


int main(void)
{
	DDRD = (1<<PD5) | (1<<PD6)	;  // LED as Output
	lcd_init();
	i2c_init();
    unsigned char ret;


    while (1)
    {

//    	dtostrf();

		lcd_setcursor(0,1);
		lcd_string("Zeile 1____________1");

		lcd_setcursor(0,2);
		lcd_string("Zeile 2____________2");

		lcd_setcursor(0,3);
		lcd_string("Zeile 3____________3");

		lcd_setcursor(0,4);
		lcd_string("Zeile 4____________4");


    	PORTD |= (1<<PD5); // LED1 On
		_delay_ms(50);



		PORTD &= ~(1<<PD5); 	// LED1 Off
	 	_delay_ms(50);
    /*
    	_delay_ms(50);

    	PORTD |= (1<<PD5); // LED1 On
		_delay_ms(50);

		i_test ++;

		itoa( i_test, c_buffer, 10);			// display  test Counter
		lcd_setcursor(0,3);
		lcd_string(c_buffer);

		lcd_setcursor(0,1);
		lcd_string("Schritt 1");


		lcd_setcursor(0,1);
		lcd_string("Schritt 2");


		lcd_setcursor(0,1);
		lcd_string("Schritt 3");


		ret = i2c_start(LM75_ADDRESS+I2C_READ);
		if (ret){

			i2c_stop();


			lcd_setcursor(0,1);
			lcd_string("Fehler I2C");


		}
		else{

			lcd_setcursor(0,1);
			lcd_string("Erfolg I2C");

			i_buffer_I2C_2 = i2c_readNak();
			i_buffer_I2C = i2c_readNak();
			i2c_stop();

			i_temperatur = i_buffer_I2C * 0.5;      // LM75 stores temp in 0.5 °

//			sprintf();

//			ftoa(f_temperatur, c_buffer, 10);

			itoa( i_temperatur, c_buffer, 10);		// display  test Counter
			lcd_setcursor(0,4);
			lcd_string(c_buffer);

		}





//		 i2c_start_wait(LM75_ADDRESS+I2C_READ); // device address and write mode
//		 i2c_read(i_buffer_I2C);
//
//		 i2c_start_wait(LM75_ADDRESS+I2C_WRITE); // device address and write mode
//		 i2c_write(0x00);                        // write address = 0 (temperature)
//		 i2c_rep_start(i_buffer_I2C+I2C_READ);   // set device address and read mode
//		 i_buffer_I2C = i2c_readNak();           // read one byte from LM75
//		 i2c_stop();


//		i_temperatur = i_buffer_I2C * 0.5;       // LM75 stores temp in 0.5 °
//
//		itoa( i_temperatur, c_buffer, 10); 		// display temperatur
//		lcd_setcursor(0,2);
//		lcd_string(c_buffer);

*/



		PORTD &= ~(1<<PD5); 	// LED1 Off

    }

    return (1);	// should never happen
}


