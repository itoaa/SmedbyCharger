/*
 * LeadAcid10.h
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *
 *		Ported to Eclipse Arduino FreeRTOS
 *
 *      Charge Led Acide battery.
 * 	  	Version	1.0
 *       	Initial release.
 */

#ifndef LEADACID10_H_
#define LEADACID10_H_

#include <Arduino.h>
#include "Arduino_FreeRTOS.h"
#include "Filter10.h"
#include "Current20.h"
#include "Volt20.h"
#include "GlobalDB.hpp"

extern QueueHandle_t LeadAcidQ;

/*
class GlobDB
{
	GlobalDB x;
public:
	GlobDB() : x(1) {};
};
*/
class LeadAcid
{
private:
	QueueHandle_t LadAcidQ;
	int   _FastChargeVolt;
	int   _FastChargemAmp;
	int   _FastChargeMaxTime;
	int   _TrickleChargeVolt;
	int   _TrickleChargemAmp;
	int   _TrickleChargeMaxTime;
public:
	LeadAcid(int NumberOfCels, int AmpHour);					// Number och cels in the pack (6 = 12V). AH of the pack.
	virtual ~LeadAcid();
//	int Charge();												// Start Charger and wait for input.
	int CheckIfBtteryConnetcted();
	int QuickTest();											// Test pack för calculated fast charge volt. Return fast charge volt.
	int Monitor();												// Monitor battery volt. Loop untill battery is found.
	int FastCharge();											// Fastcharge pack. Return error or OK.
	int TrickleCharge(int ChargeVoltPerCell, int MaxTCTime);	// Tricklecharge pack. Terurn error or OK.
	int LongtermCharge();										// If TrickleCharge exits. Monitor battery volt vith low current charge, and start trickle if needed.
};

#endif /* LEADACID10_H_ */
