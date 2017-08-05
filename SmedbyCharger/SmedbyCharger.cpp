#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

/* ------------------------------------------------------------------
 * SMedbyCharger ver 3 utvecklas i Eclipse och byter kernel från
 * OS48 till FreeRTOS V9
 * Utvecklas paralellt med V2.0
 * Version 3.0 kommer att ta ett nytt grepp om globala variabler och
 * ersätta dessa med en databa-process som övriga processer kan komunisera
 * med för att få tillgång till data i systemet.
 */

// define tasks
void TaskBlink( void *pvParameters );
void TaskCount( void *pvParameters );

void setup()
{
	Serial.begin(115200);
	while (!Serial)  { ; }  // wait for serial port to connect.

	  pinMode(LED_BUILTIN, OUTPUT);
	xTaskCreate(
	    TaskBlink
	    ,  (const portCHAR *)"Blink"   // A name just for humans
	    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
	    ,  NULL
	    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	    ,  NULL );

	xTaskCreate(
	    TaskCount
		,  (const portCHAR *)"Serial"   // A name just for humans
		,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
		,  NULL
		,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
		,  NULL );


}

void loop()
{
}

void TaskCount(void *pvParameters)
{
	(void) pvParameters;
	const TickType_t xDelay = 50 / portTICK_PERIOD_MS;

	int i;
	for (;;) // A Task shall never return or exit.
	{
		for (i=0; i<100; i++)
		{
			Serial.println(i);
			vTaskDelay( xDelay ); // wait for 100ms
		}
	}
}
void TaskBlink(void *pvParameters)
{
//	(void) pvParameters;

	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

	  for (;;) // A Task shall never return or exit.
	  {
		  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
		    vTaskDelay( xDelay ); // wait for one second
		  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
		    vTaskDelay( xDelay ); // wait for one second
	  }
}
