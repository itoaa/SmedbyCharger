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

	const int	ChargerState = 0;
	const int 	ChargerPWM = 2;
	const int	ChargerOutVolt = 4;
	const int 	ChargerOutAmp = 6;
	const int 	ChargerTemp1 = 8;
	const int 	ChargerExternalTemp1 = 10;
	const int	ChargerInVolt = 12;
	const int 	ChargerInAmp = 14;


struct GlobalVarStruct
{
	int	ChargerState;
	int ChargerPWM;
	int	ChargerOutVolt;
	int ChargerOutAmp6;
	int ChargerTemp1;
	int ChargerExternalTemp1;
	int	ChargerInVolt;
	int ChargerInAmp;
};

class ChargeDB {
public:
	ChargeDB();									// Set up comm to ChargeDB
	virtual ~ChargeDB();
	void Set_var(int ID,int Value);				// Update global variable "ID" with value "Value"
	int Get_var(int ID);							// Get Global Variable "ID". Returns "Value"

	void Set_index(int Index,char Value);		// Update global variable "ID" with value "Value"
	char Get_index(int Index);					// Get Global Variable "ID". Returns "Value"

private:
	GlobalVarStruct Global_vars;

};

#endif /* CHARGEDB10_H_ */
