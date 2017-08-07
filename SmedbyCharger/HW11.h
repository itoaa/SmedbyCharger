/*
 * HW11.h
 *
 *  Created on: 7 aug. 2017
 *      Author: Ola Andersson
 *
 *      All definitions spesific to Smedbycharger ver 1.1 PCB
 */

#ifndef HW11_H_
#define HW11_H_


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

  Led Led1(ChargeLed1);
  Led Led2(ChargeLed2);
  Led Led3(ChargeLed3);

 #endif




#endif /* HW11_H_ */
