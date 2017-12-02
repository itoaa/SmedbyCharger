/*
 * LogViewSerial20.cpp
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 */

#include "LogViewSerial20.h"

LogViewSerial::LogViewSerial(word BaudRate)
{
	RTP.seconds = 0;
}

LogViewSerial::~LogViewSerial()
{
	// TODO Auto-generated destructor stub
}

// Suprutines to update values to send to logworks
void LogViewSerial::updateBatteryVolt(int volt)
{
  RTP.BatteryVolt = volt;
}
void LogViewSerial::updateBatteryCurrent(int current)
{
  RTP.BatteryCurrent = current;
}
void LogViewSerial::updateBatteryTemp(int temp)
{
  RTP.BatteryTemp = temp;
}
void LogViewSerial::updateInputVolt(int volt)
{
  RTP.InputVolt = volt;
}
void LogViewSerial::updatePWM(int pwm)
{
  RTP.Pwm = pwm;
}
void LogViewSerial::updatemAh(word mAh)
{
  RTP.mAh = mAh;
}


// Subrutine to send latest value to serialport/LogView.
// No parameters is needed, all valuse need to be updated before call
void LogViewSerial::sendSerial()
{
	// print all variables in Logview styel to serialport.
	// Need to mach Logview-ini-file.
	char ch[5];

	sPrint3("$1;");						// Channle 1

	itoa(RTP.state,ch,5);
	sPrint3(ch);			// State of charger (1, 2 or 3).

	sPrint3(";");
	sPrint3((RTP.seconds));
	sPrint3(";");
	sPrint3((RTP.BatteryVolt));
	sPrint3(";");
	sPrint3((RTP.BatteryCurrent));
	sPrint3(";");
	sPrint3((RTP.BatteryTemp));
	sPrint3(";");
	sPrint3((RTP.InputVolt));
	sPrint3(";");
	sPrint3((RTP.Pwm));
	sPrint3(";");
	sPrint3((RTP.mAh));
	sPrint3(";");
	sPrint3("0");						// BMS
	sPrint3(";0");

	RTP.seconds++;

 }


void LogViewSerial::sPrint(char str[20])
{

for ( int i = 0; str[i] != '\0' ; ++i )
	{
		Serial.write(str[i]);
	}
}

void LogViewSerial::sPrint2(String str2)
{
	char myArray[sizeof(str2)+1];//as 1 char space for null is also required
	strcpy(myArray, str2.c_str());


	for ( int i = 0; str2[i] != '\0' ; ++i )
		{
			Serial.write(str2[i]);
		}
}

void LogViewSerial::sPrint3(char str3[])
{
    char* p = str3;
    for (; *p != '\0'; ++p)
    {

    	// if '\0' happens to be valid data for your app,
         // then you can (maybe) use some other value as
         // sentinel
    }
    int arraySize = p - str3;

	for ( int i = 0; str3[i] != '\0' ; ++i )
		{
			Serial.write(str3[i]);
		}


    // now we know the array size, so we can do some thing
}
void LogViewSerial::sPrint3(int int1)
{
	char ch[5];
	itoa(int1,ch,5);
	sPrint3(ch);			// State of charger (1, 2 or 3).
}
