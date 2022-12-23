/******************************************************************************
 *
 * Module: Ultra-sonic Sensor
 *
 * File Name: ultrasonic.h
 *
 * Description: header file for the ultra-sonic sensor
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TRIGGER_PORT PORTB_ID
#define TRIGGER_PIN PIN5_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * initialize the ultra-sonic sensor by setting the Trigger pin as output pin
 * and configure the ICU module as required and set the call back function
 */
void Ultrasonic_init(void);

/*
 * Description :
 * trigger the ultra-sonic sensor to start operation to measure distance
 */
void Ultrasonic_Trigger(void);

/*
 * Description :
 * read the distance measured by the ultra-sonic sensor
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description :
 * calculate the high pulse time and then calculate distance
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
