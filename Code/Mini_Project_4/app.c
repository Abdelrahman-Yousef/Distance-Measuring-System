/******************************************************************************
 *
 * APP: measuring distance
 *
 * File Name: app.c
 *
 * Description: Measure the distance using the Ultra-sonic sensor HC-SR04
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h>

int main(void) {

	/*
	 * enable the global interrupt pit
	 */
	SREG |= (1 << 7);

	/*
	 * initialize the modules used in the project
	 */
	LCD_init();
	Ultrasonic_init();

	/*
	 * variable the store the measured distance
	 */
	uint16 distance;

	/*
	 * display the measured distance on the LCD
	 */
	LCD_displayString("Distance =    CM");

	while (1) {

		/*
		 * read the value measured by the ultra-sonic sensor
		 */
		distance = Ultrasonic_readDistance();

		/*
		 * display the distance on the LCD
		 */
		LCD_moveCursor(0, 11);
		if (distance >= 100) {
			LCD_intgerToString(distance);
		} else {
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
		}
	}

	return 0;
}

