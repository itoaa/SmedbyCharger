/*
 * ChargeDB10.h
 *
 *  Created on: 17 sep. 2017
 *      Author: Ola Andersson
 *      Version 1.0
 *      	First version that only use Object oriented DB. ChargeDB task in main app is still C, and handles the Queue
 *      	Needs another class for communication to ChargeDB-task from other tasks.
 *      	Try to do a slim version only for SmedbyCharger
 */

#ifndef CHARGEDB10_H_
#define CHARGEDB10_H_


#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

	int	ChargerState;
	int ChargerPWM;
	int	ChargerOutVolt;
	int ChargerOutAmp;
	int ChargerTemp1;
	int ChargerExternalTemp1;
	int	ChargerInVolt;
	int ChargerInAmp;


struct GlobalVarStruct
{
	int	ChargerState = 0;
	int ChargerPWM = 2;
	int	ChargerOutVolt = 4;
	int ChargerOutAmp = 6;
	int ChargerTemp1 = 8;
	int ChargerExternalTemp1 = 10;
	int	ChargerInVolt = 12;
	int ChargerInAmp = 14;
};

class ChargeDB {
public:
	ChargeDB();								// Set up comm to ChargeDB
	virtual ~ChargeDB();
	void Set_var(int ID,int Value);		// Update global variable "ID" with value "Value"
	int Get_var(int ID);					// Get Global Variable "ID". Returns "Value"

	void Set_index(int Index,char Value);		// Update global variable "ID" with value "Value"
	char Get_index(int Index);					// Get Global Variable "ID". Returns "Value"

	int test();
	const int ChargeMaxVoltIndex = 0;
	const int ChargeMaxAmpIndex = 2;
	const int ChargeMaxBatteryTempIndex = 4;
	const int ChargeMinBatteryTempIndex = 6;
	const int CharteMagTimeMinIndex = 8;
	const int ChargeFastChargeCutoffAmpIndex = 10;
	const int ChargeStateIndex = 12;
private:
	GlobalVarStruct Global_vars;

};

#endif /* CHARGEDB10_H_ */
