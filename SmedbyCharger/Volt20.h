/*
 * Volt20.h
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *
 *      Ver 2.0 is ported to Arduino Eclipse and FreeRTOS
 *
 *      Konstruktor av IVOLT. ex (IVOLT(8,50). sätter pin 8 som mätpinner för matningsspänning och högsta värde (1023) motsvarar 50V.
 *
 *		Ver		2.0
 *		Change name to Volt. Ready for OS48
 *
 */

#ifndef VOLT20_H_
#define VOLT20_H_
#include <Arduino.h>
#include "Filter10.h"

class Volt
{
private:
	int  _maxVolt;
	int  _analogIn;
public:
	Volt(int pin, int MaxVolt);						// pin = Arduino pin where Input Voltage is connected.
    // MaxVolt = Maximum voltage thet is measurable. ADC-value 1023 vonverts to MaxVolt
	virtual ~Volt();
	unsigned int  readVolt(void);                     // Performe a measurement

};

#endif /* VOLT20_H_ */
