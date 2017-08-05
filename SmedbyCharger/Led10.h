/*
 * Led10.h
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *
 *      LED Class to contol LED:s
 */

#ifndef LED10_H_
#define LED10_H_

#include <Arduino.h>
#include "Arduino_FreeRTOS.h"
class Led {
private:
	int _LedPin;
	int	_OnTime;
	int _OffTime;
public:
	Led(int LedPin);					// Set up LED on pin LedPin
	virtual ~Led();
	void setOnTime(int OnTime);				// Set LED on time in ms
	void setOffTime(int OffTime);			// Set LED off time in ms
	void controleLed();						// Make Led blink
};

#endif /* LED10_H_ */
