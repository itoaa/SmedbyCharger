/*
 * Led10.cpp
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *      Documentation in h-file
 */

#include "Led10.h"

Led::Led(int LedPin)
{
	_LedPin = LedPin;						// Set private variable to LED pin
	pinMode(_LedPin, OUTPUT);				// Set LED-pin to output.
	_OnTime = 1000 / portTICK_PERIOD_MS;		// Dont turn on LED
	_OffTime = 	1000 / portTICK_PERIOD_MS;	// Wait 1 sec, wake up and see if LED should be turned on.
}

Led::~Led()
{
	// TODO Auto-generated destructor stub
}

void Led::setOnTime(int OnTime)				// Set LED on time in ms
{
	const TickType_t xDelay = OnTime / portTICK_PERIOD_MS;	// Set xDelay to one sec.
	_OnTime = xDelay;
}
void Led::setOffTime(int OffTime)			// Set LED off time in ms
{
	const TickType_t xDelay = OffTime / portTICK_PERIOD_MS;	// Set xDelay to one sec.
	_OffTime = xDelay;
}
void Led::controleLed()						// Run an infinit look to make the led blink
{
	for (;;)
	{
		digitalWrite(_LedPin,HIGH);
		vTaskDelay(_OnTime);
		digitalWrite(_LedPin,LOW);
		vTaskDelay(_OffTime);

	}
}

void Led::turnLedOn()						// Light up the led
{
	digitalWrite(_LedPin,HIGH);
}
void Led::turnLedOff()						// Turn off led
{
	digitalWrite(_LedPin,LOW);
}
