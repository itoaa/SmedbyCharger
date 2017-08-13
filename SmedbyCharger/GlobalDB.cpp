/*
 * GlobalDB.cpp
 *
 *  Created on: 12 aug. 2017
 *      Author: Ola Andersson
 *      rev 1
 */

#include "GlobalDB.hpp"

void setVar(int _ID, int _Value)
{
	int * temppointer;
	temppointer = (int*)&GDB + (_ID*2);
	*temppointer = _Value;
}

int getVar(int _ID)
{
	int * temppointer;
	temppointer = (int*)&GDB + (_ID * 2);
	return(*temppointer);

}

void GlobalDBTask(void *pvParameters)
{
	(void) pvParameters;
//	int TickType_t;
	const  TickType_t xDelay = 5000 / portTICK_PERIOD_MS;	  // Set xDelay to one sec.
	QueueStruct messin,messout;
	messout.command = 11;
	messout.value = 0;
	messin.command = 0;
	messin.value = 0;

	for (;;) // A Task shall never return or exit.
	{
		if (xQueueReceive(GlobalQ,&messin,xDelay))
		{
			if (messin.command == 10)						// Some process ask for a value
			{
//				Serial.print("Global Recived command : " );
//				Serial.println(messin.command);
//				Serial.println("Global Sends a command 11 back" );

				messout.value = getVar(messin.ID);
				messout.command = 11;
				messout.value = getVar(messin.ID);
				messout.ID = messin.ID;

				xQueueSendToBack(messin.returnHandle,&messout,100);
			}
			if (messin.command == 11)						// Some process sent a value
			{
//				Serial.print("Global Recived command : " );
//				Serial.println(messin.command);
//				Serial.print("Global will update ID ");
//				Serial.print(messin.ID );
//				Serial.print(" with value ");
//				Serial.println(messin.value);
				setVar(messin.ID,messin.value);
			}

		}

/*		Serial.print("Global: var 2 CgargeMagAmp = ");
		Serial.println(GDB.ChargeMaxAmp);
		Serial.print("Global: var 3 ChargeMasBatteryTemp = ");
		Serial.println(GDB.ChargeMaxBatteryTemp);
*/
	}

}

GlobalDB::GlobalDB(QueueHandle_t _q)
{
	_GlobalQ = _q;
}
void GlobalDB::SetGlobal(int _ID, int _Value)
{
	QueueStruct messout;

	messout.command = 11;
	messout.ID = _ID;
	messout.value = _Value;
	messout.returnHandle = NULL;
    xQueueSendToBack(GlobalQ,&messout,100);
}

int GlobalDB::GetGlobal(int _ID)
{
	QueueStruct messin,messout;

	messout.command = 10;
	messout.ID = _ID;
	messout.returnHandle = _GlobalQ;
    xQueueSendToBack(GlobalQ,&messout,100);
	xQueueReceive(_GlobalQ,&messin,100);
	 return(messin.value);

}

