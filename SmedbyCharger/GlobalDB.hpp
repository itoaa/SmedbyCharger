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

class GlobalDB {
private:
	int getVar(int _ID);
	void setVar(int _ID, int _Value);

	QueueHandle_t _GlobalQ;
public:
	GlobalDB(QueueHandle_t _GlobalQ);								// Set up comm to GlobalDB
	virtual ~GlobalDB();
	void SetGlobal(int ID,int Value);		// Update global variable "ID" with value "Value"
	int GetGlobal(int ID);					// Get Global Variable "ID". Returns "Value"
	const int ChargeMaxVoltIndex = 0;
	const int ChargeMaxAmpIndex = 2;
	const int ChargeMaxBatteryTempIndex = 4;
	const int ChargeMinBatteryTempIndex = 6;
	const int CharteMagTimeMinIndex = 8;
	const int ChargeFastChargeCutoffAmpIndex = 10;
	const int ChargeStateIndex = 12;

};


void GlobalDBTask(void *pvParameters);




#endif /* GLOBALDB_HPP_ */
