/*
 * Current20.cpp
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *      Documentation in h-file.
 */

#include "Current20.h"

Current::Current(int pin, int ACS712_type)
{
	_acs712_type = ACS712_type;
	_analogIn = pin;
	pinMode(_analogIn,INPUT);
	_lastADCValue = 0;
}

Current::~Current() {
	// TODO Auto-generated destructor stub
}

int Current::readCurrent(void)
{
    int i;
    int mVperAmp;                  // use 185.0 for 5A module, 100 for 20A Module and 66 for 30A Module
    if       (_acs712_type == 1)    { mVperAmp = 185.0; }   // 5A.  using 185.0 for 5A module
    else if  (_acs712_type == 2)    { mVperAmp = 100.0; }   // 20A. using 100.0 for 20A Module
    else if  (_acs712_type == 3)    { mVperAmp = 66.0;  }   // 30A  using 66.0mv/amp for 30A Module
 //       mAperADC = 73.2422;                           // 73.2422mA per ADC tick.
    else {}

    int RawValue= 0;
    double Voltage = 0;
    double Amps = 0;
    int milliAmps = 0;

    Filter _raw(13);                                 // Use 13 position buffer
    for(int i=0;i<13;i++)                           // Fill all potitions with newly read values
    {
      RawValue = analogRead(_analogIn);             // Read ADC-Value
      _raw.addValue(RawValue);                        // put in to filter buffer
    }
      _lastADCValue = _raw.getFilteredValue();             // Get aveage value
      Voltage = (_lastADCValue / 1024.0) * _refVoltage;
      Amps = ((Voltage - _ACOffset) / mVperAmp);
      milliAmps = (int)(Amps * 1000.0);
      return (1-milliAmps);
}

// Reads voltage on pin and set offset value to that.
int Current::zeroAmpCallibrate()
{
    int RawValue= 0;
    int Voltage = 0;
    Filter adc(13);                                   // Use 13 position buffer
    for(int i=0;i<13;i++)                             // Fill all potitions with newly read values
    {
        RawValue = analogRead(_analogIn);             // Read ADC-Value. No current can flow when setting 0A offset.
        adc.addValue(RawValue);                       // put in to filter buffer
    }
    RawValue = adc.getFilteredValue();               // Get aveage value
    _ACOffsetADC = RawValue;
    Voltage = (RawValue / 1023) * _refVoltage;       // Remap averaged reading to mV
    _ACOffset = Voltage;                              // Set ACOffset to average reading
}



void Current::setRefVoltage(int RV)
{
    _refVoltage = RV;                           // Set ref voltage för ADC
}


int    Current::getLastADCValue()
{
  return (_lastADCValue);                 // Get ADC value from last readCurrent();
}
