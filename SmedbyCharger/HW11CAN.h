/*
 * HW11CAN.h
 *
 *  Created on: 7 aug. 2017
 *      Author: Ola Andersson
 *
 *      Hardware specific settings for Smedbycharger PCB with CAN-BUS module connected.
 */

#ifndef HW11CAN_H_
#define HW11CAN_H_


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


#endif /* HW11CAN_H_ */
