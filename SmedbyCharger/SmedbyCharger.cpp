#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "LogViewSerial20.h"
#include "LeadAcid10.h"
#include "Led10.h"


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

// Define if the charger will start chargin by its own.
#define AutoCharge

// Setup Hardware constatns for SmedbyCharger PCB Ver 1.1 without CAN-Bus
// *************************************************************************************************
#ifdef  SmedbyCharger11					// Parameter definition for SmedbyCharger 1.1 without CAN buss.
  #define     SerialEnabled				// Enable serial ouput on this hardware.
  #define     BaudRate 115200			// Sepeed for cerial comunication
  int  InputVoltPin  = A2;				// Pin used to measure Battery-volt
  int  OutputCurrentPin = A0;			// Pin used to measure Motor-volt
  int  OutputVoltPin = A1;				// Try to measure output-volt
  int  Pin12V = A3;						// Pin used to measure 12 volt rail
  int  TemperaturPin = 7;				// Pin used to measure mosfet-temperatur
  int  pwmPin = 9;						// Pin used for PWM-charge-output
  int  Temp_Measure_type = 2;			// Type 1 = NTC-resistor, 2 = DS1820 temp sensor.
  int  Current_Measure_type = 3;		// Type 1 = 5A, 2 = 20A, 3 = 30A              ( Defines witch type of current sense sensor is used.
  int  ChargeLed1 = 5;					// Red LED
  int  ChargeLed2 = 4;					// Yelow LED
  int  ChargeLed3 = 3;					// Green LED
  int  ButtonPin = 02;
#endif

// Setup Hardware constatns for SmedbyCharger PCB Ver 1.1 with CAN-Bus
// *************************************************************************************************
#ifdef  SmedbyCharger11CAN                    // Parameter definition for SmedbyCharger 1.1 without CAN buss.
  #define     SerialEnabled                 // Enable serial ouput on this hardware.
  #define     BaudRate 115200               // Sepeed for cerial comunication
  const byte  InputVoltPin  = PC4;          // Pin used to measure Battery-volt
  const int   OutputCurrentPin = PC1;       // Pin used to measure Motor-volt
  const byte  OutputVoltPin = PC2;          // Try to measure output-volt
  const byte  Pin12V = PC3;              	// Pin used to measure 12 volt rail
  const byte  TemperaturPin = PC5;          // Pin used to measure mosfet-temperatur
  const byte  PotPin = PC0;                 // Pin used to measure pot-position
  const byte  pwmPin = PD6;                 // Pin used for PWM-charge-output
  const byte  Temp_Measure_type = 1;        // Type 1 = NTC-resistor, 2 = DS1820 temp sensor.
  const int   Current_Measure_type = 3;     // Type 1 = 5A, 2 = 20A, 3 = 30A              ( Defines witch type of current sense sensor is used.
	#define  ChargeLed1 = 5;           		// Red LED
	#define  ChargeLed2 = 4;				// Yelow LED
	#define  ChargeLed3 = 3;				// Green LED
  int  ButtonPin = 02;

  #endif


  // Declare standard tasks used on all hardwares
void ChargeTask( void *pvParameters );
void Led1Task( void *pvParameters );
Led Led1(ChargeLed3);

// Declare tasks that is hardware specific
#ifdef SerialEnabled
	void SerialTask( void *pvParameters );
#endif

#ifdef AutoCharge
	void AutoChargeTask( void *pvParameters );
#endif

// Global Variables. Be carful when read and write (May need protection from wrong treatment).
//	Change to Database task, updated with functions or other inter task communication.
int   GChargeStatus;
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
		GChargeStatus = 1;                // Set Charger to monitor;
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

void Led1Function(void *pvParameters)
{
	(void) pvParameters;
	//extern Led Led1;
	Led1.setOnTime(500);
	Led1.setOffTime(500);
	for (;;)
	{
		Led1.controleLed();

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
	    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
	    ,  NULL
	    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	    ,  NULL );
    #endif

	xTaskCreate(
	    ChargeFunction
	    ,  (const portCHAR *)"ChargeFunktion"   // A name just for humans
	    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
	    ,  NULL
	    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	    ,  NULL );

	xTaskCreate(
		Led1Function
		,  (const portCHAR *)"LED1RedTaskFunktion"   // A name just for humans
		,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
		,  NULL
		,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
		,  NULL );

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




