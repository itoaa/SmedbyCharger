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
	sPrint("$1;1;");
	Serial.write(RTP.seconds);
	sPrint(";");
	Serial.write(RTP.BatteryVolt);
	sPrint(";");
	Serial.write(RTP.BatteryCurrent);
	sPrint(";");
	Serial.write(RTP.BatteryTemp);
	sPrint(";");
	Serial.write(RTP.InputVolt);
	sPrint(";");
	Serial.write(RTP.Pwm);
	sPrint(";");
	Serial.write(RTP.mAh);
	sPrint(";0");

	RTP.seconds++;

 }


void LogViewSerial::sPrint(char str[20])
{

for ( int i = 0; str[i] != '\0' ; ++i )
	{
		Serial.write(str[i]);
	}
}
