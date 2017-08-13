#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "LogViewSerial20.h"
#include "LeadAcid10.h"
#include "Led10.h"
#include "GlobalDB.hpp"

/* ------------------------------------------------------------------
 * SmedbyCharger ver 3 utvecklas i Eclipse och byter kernel från
 * OS48 till FreeRTOS V9
 * Utvecklas paralellt med V2.0
 * Version 3.0 kommer att ta ett nytt grepp om globala variabler och
 * ersätta dessa med en databas-process som övriga processer kan kommunisera
 * med för att få tillgång till data i systemet.
 */

// Define for witch hardware to compile
 #define SmedbyCharger11
// #define SmedbyCharger11CAN

#include "HW11.h"
#include "HW11CAN.h"

GlobalVarStruct GBD;
QueueHandle_t GlobalQ;

// Global Variables. Be carful when read and write (May need protection from wrong treatment).
//	Change to Database task, updated with functions or other inter task communication.

// int   GChargeStatus;
int   GBatteryVolt;
int   GBatteryCurrent;
int   Gpwm;
int   GInputVolt;

// Global Chage parameters and max values
int GMaxChargeVolt;
int GMaxChargeCurrent;
int GMaxChargeBatteryTemp;
int GMinChargeBatteryTemp;
int GMaxChargeTimeMin;
int GFastChargeCutofCurrent;

void SendSerialFunction(void *pvParameters)
{
	(void) pvParameters;
	LogViewSerial mySerial(BaudRate);
	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;	// Set xDelay to one sec.
	for (;;) // A Task shall never return or exit.
	{
        mySerial.updateBatteryVolt(GBatteryVolt);
        mySerial.updateBatteryCurrent(GBatteryCurrent);   // Update _BatteryCurrent private variable
        mySerial.updateBatteryTemp(25);                   // Update _BatteryTemp private variable
        mySerial.updateInputVolt(GInputVolt);             // Update _InputVoltage private variable
        mySerial.updatePWM(Gpwm);                         // Update _pwm private variable
        mySerial.updatemAh(2200);                         // Update _mAh private variable
        mySerial.sendSerial();

        vTaskDelay(xDelay);

	}
}

void AutoChargeFunction(void *pvParameters)
{
	(void) pvParameters;
	const TickType_t xDelay = 2000 / portTICK_PERIOD_MS;	// Set xDelay to one sec.

	for (;;) // A Task shall never return or exit.
	{
		vTaskDelay(xDelay);

	}

}

void ChargeFunction(void *pvParameters)
{
	(void) pvParameters;
	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;	// Set xDelay to one sec.
	for (;;) // A Task shall never return or exit.
	{
		LeadAcid MyPack(1,75);              // Setup batterypack
		GDB.(GDB.,1);  			    // Set Charger to monitor;
		MyPack.Charge();                  // Start charger
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

void Led3Function(void *pvParameters)
{
	int LedPin = (int)pvParameters ;
	Led3.setOnTime(500);
	Led3.setOffTime(500);
	for (;;)
	{
		Led3.controleLed();

	}
}

void setup()
{
    analogReference(EXTERNAL);					// Set ADC reference voltage to external reference

    pinMode(pwmPin, OUTPUT);					// sets pwm pin as output
    setPwmFrequency(pwmPin, 1);					// pin,prescaler   pin9 default freq 32k.
    // setPwmFrequency(pwmPin, 8);					// pin,prescaler   pin9 default freq 3.9k.

    Serial.begin(BaudRate);
	while (!Serial)  { ; }						// wait for serial port to connect.

	#ifdef SerialEnabled
	xTaskCreate(
	    SendSerialFunction
	    ,  (const portCHAR *)"SerialTaskFunktion"   // A name just for humans
	    ,  256  		// This stack size can be checked & adjusted by reading the Stack Highwater
	    ,  NULL		// Parameter
	    ,  2  		// Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	    ,  NULL );	// Handler
    #endif

	Led1.turnLedOn();						// Make RED LED turn on
	Led2.turnLedOff();						// Yellow LED off.

	xTaskCreate(
	    ChargeFunction
	    ,  (const portCHAR *)"ChargeFunktion"   // A name just for humans
	    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
	    ,  NULL
	    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	    ,  NULL );

	xTaskCreate(									// Make Green LED blink.
		Led3Function
		,  (const portCHAR *)"LED1RedTaskFunktion"   // A name just for humans
		,  128  		// This stack size can be checked & adjusted by reading the Stack Highwater
		,  NULL		// Parameter
		,  2  		// Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
		,  NULL );	// Handler

    #ifdef AutoCharge
	xTaskCreate(
	    AutoChargeFunction
	    ,  (const portCHAR *)"AutoStartChargeFunktion"   // A name just for humans
	    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
	    ,  NULL
	    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	    ,  NULL );
    #endif
}

void loop()
{
	for (;;){};// Nothing happens in loop. Everyting happends in deklared task-funktions ...
}




