/*
 * Volt20.cpp
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *      Dokumentation in h-file
 */

#include "Volt20.h"

Volt::Volt(int pin, int MaxVolt)
{
	pinMode(pin, INPUT);
	_maxVolt = MaxVolt;
	_analogIn = pin;
	pinMode(_analogIn,INPUT);
}

Volt::~Volt() {
	// TODO Auto-generated destructor stub
}

// Subrutine to measure inputvoltagePin (multiple times for normalization)
word Volt::readVolt(void)
{
    Filter volt(13);                                                    // Setuf filter with 13 positions
    for(int i=0;i<13;i++)                                               // Fill Filter buffer with reads.
    {
      volt.addValue(map(analogRead(_analogIn),0,1023,0,_maxVolt));      // Read ADC-Value, remap to 0 to _maxVolt and put in to filter buffer
    }
    return (volt.getFilteredValue());                                   // Return average value
}
