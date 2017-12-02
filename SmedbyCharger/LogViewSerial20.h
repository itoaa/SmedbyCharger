/*
 * LogViewSerial20.h
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *
 * 		Ported to Arduino Eclipse FreeRTOS
 *
 *      LogView serial comunication class
 *		Ver 2.0  Added structures in the same way as megatune.
 *		That way task switching only need to be blocked for one character on the serial port.
 *
 */

#ifndef LOGVIEWSERIAL20_H_
#define LOGVIEWSERIAL20_H_
#include <Arduino.h>
#include <stdio.h>
#include <string.h>


// The structure of the realtime data sent on the Serial port to LogViewer
struct __attribute__((packed)) RPageVarsStruct {

	int		state;								// Charger state. 1 = Fastcharge, 2= Slowcharge, 3 = monitor
	int     seconds;                        	// Number of seconds from Charge start
    int     BatteryVolt;                    	// Battery Volt
    int     BatteryCurrent;                 	// ADC value for TPS measurement
    int     BatteryTemp;                    	// Output current.
    int     InputVolt;                     	// Power supply volt
    int     Pwm;                            	// Pwm (0-1024)
    int32_t     mAh;                         // Energy.
    int		BMS;							// bool if BMS has triggered an over volt event.
};

class LogViewSerial {
private:
	RPageVarsStruct RTP;
	void sPrint(char str[20]);
	void sPrint2(String str);
	void sPrint3(char str3[]);
	void sPrint3(int int1);


public:
	LogViewSerial(word BaudRate);
	virtual ~LogViewSerial();
	void sendSerial();						// Send all variables to logview
	void updateBatteryVolt(int volt);        // Update _BatteryVoltage private variable
	void updateBatteryCurrent(int current);	// Update _BatteryCurrent private variable
	void updateBatteryTemp(int temp);		// Update _BatteryTemp private variable
	void updateInputVolt(int volt);          // Update _InputVoltage private variable
	void updatePWM(int pwm);					// Update _pwm private variable
	void updatemAh(word mAh);				// Update _mAh private variable
};

#endif /* LOGVIEWSERIAL20_H_ */
