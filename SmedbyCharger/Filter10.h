/*
 * Filter10.h
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *      Filter and buffer class ver 1.0 for Arduino ported to Eclipse and FreeRTOS
 *
 */

#ifndef FILTER10_H_
#define FILTER10_H_

#include <Arduino.h>
#define filterSamples   13                // filterSamples should  be an odd number, no smaller than 3

class Filter {
	private:
		int _sensArray1 [filterSamples];        // array for holding raw sensor values for sensor1
		int _sensArray1Sort [filterSamples];    // array for holding raw sensor values for sensor2
		int _bufferPosition;
		int	_bufferLength;
	public:
		Filter(int bufferLength);			// BuffesLength = number of samples in buffer.
//		virtual ~Filter();
		int getValue(int index);               // Get valu from buffer. index = position in buffer. (0 = newest value)
		int getSortValue(int index);           // Get value from sorted buffer. index = position in sorted buffer. (0 = lowes value)
		int getFilteredValue(void);             // Get filtered and averaged value based on buffer values.
		void addValue(int value);               // Add one valu to the buffer.
};

#endif /* FILTER10_H_ */
