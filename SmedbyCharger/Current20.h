/*
 * Current20.h
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *
 *      V2 Ported to Arduino Eclipse and FreeRTOS
 *
 *      Version 1.0
            		Mät ström från en ACS712-strömmätare. Support för 5, 20 och 30A variant.
            		Mätning görs 13 ggr efter varandra. Returnerar avrage av de 70% i mitten.
 	 	Version 1.1
            		Uppdaterar med stöd för att mäta -ström (ex. regen).
            		Smothing delen görs på inkommande ADC-värden isf på utgående ström-värde.
            		_refVoltage och _ACOffset är nu instans globala, privata variabler.
            		zeroAmpCallibrate(), setRefVoltage() och setADCmAValue() Added.
  	  	 Version 2.0
  	  	 		Change name to Current. Ready for OS48.
       	   		Changed output to mA. 30 000 = 30 Amp.
 */

#ifndef CURRENT20_H_
#define CURRENT20_H_

#include <Arduino.h>
#include "Filter10.h"

class Current
{
private:
	int  _acs712_type;							// 1=5A version, 2=20A and 3=30A
	int  _analogIn;
	int  _refVoltage = 5000;						// Analog reference voltage, in mV.
	int  _ACOffset = 2500;						// mili voltage for 0 A.
	int  _ACOffsetADC = 512;						// ADC value for 0A.
	int _lastADCValue;
public:
	Current(int pin, int ACS712_type);			// pin = arduino pin where AC712 is connected.
	virtual ~Current();
	int   readCurrent(void);						// Performe a measurement
	int   zeroAmpCallibrate();					// Read and set ADC-value at 0A. (Zero amp calibration). Returns input voltage.
	void  setRefVoltage(int);					// define whitch reverece voltage used for ADC-convertion.
	int    getLastADCValue();					// Get ADC value from last getTPS();
};

#endif /* CURRENT20_H_ */
