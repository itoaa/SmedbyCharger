/*
 * GlobalDB.hpp
 *
 *  Created on: 12 aug. 2017
 *      Author: Ola Andersson
 *      rev 1
 */

#ifndef GLOBALDB_HPP_
#define GLOBALDB_HPP_


#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

struct QueueStruct
{
	byte command;					// Type of command sent to queue
	int ID;							// ID of source and dest unit sent/recived the question
	int	value;						// Value of question / responce
	QueueHandle_t returnHandle;		// Potential return queue-handler.
};

extern QueueHandle_t GlobalQ;

#define ChargeMaxVoltIndex = 0;
#define	ChargeMaxAmpIndex = 2;
#define	ChargeMaxBatteryTempIndex = 4;
#define ChargeMinBatteryTempIndex = 6;
#define CharteMagTimeMinIndex = 8;
static int ChargeFastChargeCutoffAmpIndex = 10;

#define ChargeStateIndex = 12;
struct GlobalVarStruct
{
	int ChargeMaxVolt;
	int	ChargeMaxAmp;					// ID är 2.
	int	ChargeMaxBatteryTemp;
	int ChargeMinBatteryTemp;
	int CharteMagTimeMin;
	int ChargeFastChargeCutoffAmp;

	int	ChargerState;
	int ChargerPWM;
	int	ChargerOutVolt;
	int ChargerOutAmp;
	int ChargerTemp1;
	int ChargerExternalTemp1;
	int	ChargerInVolt;
	int ChargerInAmp;

	int BatteryPackMaxChargeVolt;
	int BatteryPackMaxChargeAmp;
	int BatteryPackMaxChargeTemp;
	int BatteryPackMinChargeTemp;
	int BatteryPackMaxDischargeAmp;
	int BatteryPackMaxDischargeTemp;
	int BatteryPackMinDischargeTemp;
	int BatteryPackMinDischargeVolt;

	int BatteryPackVolt;
	int BatteryPackAmp;
	int BatteryPackTemp;
	int BatteryPackCell1Volt;
	int BatteryPackCell2Volt;
	int BatteryPackCell3Volt;

	int	DCCPWM;
	int	DCCRPM;
	int	DCCTPSPos;
	int	DCCTPSRaw;
	int	DCCOutAmp;
	int DCCOutAmpRaw;
	int	DCCInVolt;
	int DCCInAmp;
	int DCCTemp;
	int DCCTempRaw;
	int DCCMosfetDriverVolt;
};

extern GlobalVarStruct GDB;

void GlobalDBTask(void *pvParameters);

void SetGlobal(int ID,int Value);		// Update global variable "ID" with value "Value"

int GetGlobal(int ID, QueueHandle_t);					// Get Global Variable "ID". Returns "Value"



#endif /* GLOBALDB_HPP_ */
