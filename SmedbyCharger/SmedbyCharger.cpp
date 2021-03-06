#include "FreeRTOSConfig.h"

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "LogViewSerial20.h"
#include "Led10.h"
#include "ChargeDB10.h"
#include "DBQuery.h"
#include <WString.h>


/* ------------------------------------------------------------------
 * SmedbyCharger ver 3 utvecklas i Eclipse och byter kernel från
 * OS48 till FreeRTOS V9
 * Utvecklas paralellt med V2.0
 * Version 3.0 kommer att ta ett nytt grepp om globala variabler och
 * ersätta dessa med en databas-process som övriga processer kan kommunisera
 * med för att få tillgång till data i systemet.
 * rev. För att spara minne  kommer bara två prosesser att användas.
 * 1 "Real time" där laddare och DB ligger
 * 2 "Interactive" där kommunikation till CAN och/eller Serieport ordnas.
 */

// Define for witch hardware to compile
 #define SmedbyCharger11
// #define SmedbyCharger11CAN

#include "HW11.h"
//#include "HW11CAN.h"

GlobalVarStruct GBD;

QueueHandle_t Global_db_q,Serial_q,Charger_q;

void Real_time_task(void *pvParameters)
{
	// Task to manage real time things and GlobalDatabase (GlobalDB).
	// Uses class DB to store data.
	// Class DBQueue is used for querying GlobalDB.
	// Queue Global_DB_Q is used to get and set values.

	(void) pvParameters;
	const  TickType_t xDelay = 100 / portTICK_PERIOD_MS;	  // Set xDelay to one sec.
	Queue_struct messin,messout;
	ChargeDB myDB;

	messout.command = 11;
	messout.value = 0;
	messin.command = 0;
	messin.value = 0;

	for (;;) // A Task shall never return or exit.
	{


// *************  Handle Queue. when other processes need info from global db. *****************
		if (xQueueReceive(Global_db_q,&messin,xDelay))
		{
			if (messin.command == 10)						// Some process ask for a value
			{
				messout.value = myDB.Get_var(messin.ID);
				messout.command = 11;
				messout.value = myDB.Get_var(messin.ID);
				messout.ID = messin.ID;

				xQueueSendToBack(messin.returnHandle,&messout,100);
			}
			if (messin.command == 11)						// Some process sent a value
			{
				myDB.Set_var(messin.ID,messin.value);
			}

			if (messin.command == 20)						// Some process ask for a value
			{
				messout.value = myDB.Get_var(messin.ID);
				messout.command = 21;
				messout.value = myDB.Get_var(messin.ID);
				messout.ID = messin.ID;

				xQueueSendToBack(messin.returnHandle,&messout,100);
			}
			if (messin.command == 21)						// Some process sent a value
			{
				myDB.Set_var(messin.ID,messin.value);
			}

		}
	}

}

void Interactive_task(void *pvParameters)
{
	(void) pvParameters;
	LogViewSerial mySerial(BaudRate);
	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;	// Set xDelay to one sec.
	for (;;) // A Task shall never return or exit.
	{
        mySerial.updateBatteryVolt( Global_db_index_get( ChargerOutVolt,Serial_q) );
        mySerial.updateBatteryCurrent( Global_db_index_get( ChargerOutAmp,Serial_q) );   // Update _BatteryCurrent private variable
        mySerial.updateBatteryTemp(25);                   // Update _BatteryTemp private variable
        mySerial.updateInputVolt(Global_db_index_get( ChargerInVolt,Serial_q) );             // Update _InputVoltage private variable
        mySerial.updatePWM( Global_db_index_get( ChargerPWM,Serial_q ) );                         // Update _pwm private variable
        mySerial.updatemAh(2200);                         // Update _mAh private variable
        mySerial.sendSerial();

        vTaskDelay(xDelay);

	}
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = (TCCR0B & 0b11111000) | mode;
    } else {
      TCCR1B = (TCCR1B & 0b11111000) | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = (TCCR2B & 0b11111000) | mode;
  }
}


void setup()
{
    analogReference(EXTERNAL);					// Set ADC reference voltage to external reference

    pinMode(pwmPin, OUTPUT);					// sets pwm pin as output
    setPwmFrequency(pwmPin, 1);					// pin,prescaler   pin9 default freq 32k.
    // setPwmFrequency(pwmPin, 8);					// pin,prescaler   pin9 default freq 3.9k.

    Serial.begin(115200);
	while (!Serial)  { ; }						// wait for serial port to connect.
	Serial.print("Begin");
	Global_db_q = xQueueCreate(3,sizeof(Queue_struct));
	Serial_q = xQueueCreate(1 , sizeof(Queue_struct ) );
	Charger_q = xQueueCreate(1 , sizeof(Queue_struct ) );


//	#ifdef SerialEnabled

	xTaskCreate(
	    Interactive_task
	    ,  (const portCHAR *)"SerialTaskFunktion"   // A name just for humans
	    ,  256  		// This stack size can be checked & adjusted by reading the Stack Highwater
	    ,  NULL		// Parameter
	    ,  2  		// Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	    ,  NULL );	// Handler
//     #endif

	xTaskCreate(
	    Real_time_task
	    ,  (const portCHAR *)"GlobalDBTask"   // A name just for humans
	    ,  180  // This stack size can be checked & adjusted by reading the Stack Highwater
	    ,  NULL
	    ,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	    ,  NULL );
}

void loop()
{
	for (;;){};// Nothing happens in loop. Everyting happends in deklared task-funktions ...
}




