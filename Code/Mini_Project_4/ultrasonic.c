/******************************************************************************
 *
 * Module: Ultra-sonic Sensor
 *
 * File Name: ultrasonic.c
 *
 * Description: source file for the ultra-sonic sensor
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include "gpio.h"
#include "icu.h"
#include <util/delay.h>

/*
 * variable to store the distance measured by
 * the ultra-sonic sensor
 */
volatile static uint16 g_distance = 0;

/*
 * variable to track the measurement process
 */
volatile static uint8 tick = 0;

/*
 * variable to store the pulse high time measured by
 * the ICU module
 */
volatile static uint16 g_highTime = 0;

/*
 * Description :
 * initialize the ultra-sonic sensor by setting the Trigger pin as output pin
 * and configure the ICU module as required and set the call back function
 */
void Ultrasonic_init(void) {

	/*
	 * structure used to configure the ICU module with the clock source
	 * and detection of rising edge
	 */
	Icu_ConfigType configType = { F_CPU_8, RISING };

	/*
	 * initialize the ICU module with the required settings
	 */
	Icu_init(&configType);

	/*
	 * setting the call back function
	 */
	Icu_setCallBack(Ultrasonic_edgeProcessing);

	/*
	 * configure the trigger pin as an output pin
	 */
	GPIO_setupPinDirection(TRIGGER_PORT, TRIGGER_PIN, PIN_OUTPUT);
}

/*
 * Description :
 * trigger the ultra-sonic sensor to start operation to measure distance
 */
void Ultrasonic_Trigger(void) {

	/*
	 * send trigger pulse for 10us seconds
	 */
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

/*
 * Description :
 * read the distance measured by the ultra-sonic sensor
 */
uint16 Ultrasonic_readDistance(void) {

	/*
	 * trigger the ultra-sonic sensor for start measuring
	 */
	Ultrasonic_Trigger();

	/*
	 * wait until measuring finishes
	 */
	while (tick < 2) {
	}

	/*
	 * set the tick back to zero for next measurement
	 */
	tick = 0;

	/*
	 * return the measured distance to the calling function
	 */
	return g_distance;
}

/*
 * Description :
 * calculate the high pulse time and then calculate distance
 */
void Ultrasonic_edgeProcessing(void) {

	/*
	 * increment the tick after capturing a new edge
	 */
	tick++;

	switch (tick) {
	case 1:
		/*
		 * start counting when ultra-sonic echo pin rises to high
		 */
		Icu_clearTimerValue();

		/*
		 * configure the ICU to capture falling edge
		 */
		Icu_setEdgeDetectionType(FALLING);
		break;

	case 2:

		/*
		 * get the high pulse time by reading the ICR1 register value
		 */
		g_highTime = Icu_getInputCaptureValue();

		/*
		 * configure the ICU to capture rising edge for next measurement
		 */
		Icu_setEdgeDetectionType(RISING);
	}

	if (tick == 2) {

		/*
		 * calculate the distance
		 */
		g_distance = g_highTime * 0.01715;
	}
}
