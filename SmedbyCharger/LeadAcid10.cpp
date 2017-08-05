/*
 * LeadAcid10.cpp
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *      Documentation in h-file
 */

#include "LeadAcid10.h"

LeadAcid::LeadAcid(int NumberOfCels, int AmpHour)
{
	// TODO Auto-generated constructor stub
}

LeadAcid::~LeadAcid	() {
	// TODO Auto-generated destructor stub
}

// Subrutine to test pack for fast charge volt calulation
  int QuickTest()                                                                  // Test pack for calculated fast charge volt. Return fast charge volt.
{

}

// Subrutine to quick charge Lead Acid battery
LeadAcid::Charge()                                                                // Charge task. Get instructions from global variables.
{
  extern int OutputCurrentPin;
  extern int Current_Measure_type;
  extern int InputVoltPin;
  extern int OutputVoltPin;
  extern int Pin12V;
  extern int pwmPin;


// Global Chage parameters and max values
  extern int GChargeStatus;
  extern int GMaxChargeVolt;
  extern int GMaxChargeCurrent;
  extern int GMaxChargeBatteryTemp;
  extern int GMinChargeBatteryTemp;
  extern int GMaxChargeTimeMin;
  extern int GFastChargeShutofCurrent;


// Global measured charge conditions.
  extern int GBatteryVolt;
  extern int GBatteryCurrent;
  extern int Gpwm;
  extern int GInputVolt;



// local measured charge conditions.
  int BatteryCurrent;
  int BatteryVolt;
  int InputVolt;
  int Volt12;

  int I_FAST = GMaxChargeCurrent;
  int pwm = 0;

  Current Battery_current(OutputCurrentPin,Current_Measure_type);
  Volt Volt_in(InputVoltPin,6500  );        // Pin to measure inputvoltage, Max Voltage * 100
  Volt Volt_out(OutputVoltPin,5500);        // Pin to measure output voltage, Max Voltage * 100
  Volt Volt_12(Pin12V,2000);                // Pin to measure 12v suply, Max Voltage * 100

  Filter OVolt_Filtered(13);                    // Filter function for Output Voltage
  Filter OCurrent_Filtered(13);                 // Filter function for Output Current


}

// Subrutine to quick charge Lead Acid battery
LeadAcid::FastCharge()								// Charge task. Get instructions from global variables.
{
	  extern int OutputCurrentPin;
	  extern int Current_Measure_type;
	  extern int InputVoltPin;
	  extern int OutputVoltPin;
	  extern int Pin12V;
	  extern int pwmPin;


	// Global Chage parameters and max values
	  extern int GChargeStatus;
	  extern int GMaxChargeVolt;
	  extern int GMaxChargeCurrent;
	  extern int GMaxChargeBatteryTemp;
	  extern int GMinChargeBatteryTemp;
	  extern int GMaxChargeTimeMin;
	  extern int GFastChargeShutofCurrent;


	// Global measured charge conditions.
	  extern int GBatteryVolt;
	  extern int GBatteryCurrent;
	  extern int Gpwm;
	  extern int GInputVolt;

	  // local measured charge conditions.
	  	  int BatteryCurrent;
	  	  int BatteryVolt;
	  	  int InputVolt;
	  	  int Volt12;

	  	  int I_FAST = GMaxChargeCurrent;
	  	  int pwm = 0;

	  	  Current Battery_current(OutputCurrentPin,Current_Measure_type);
	  	  Volt Volt_in(InputVoltPin,6500  );        // Pin to measure inputvoltage, Max Voltage * 100
	  	  Volt Volt_out(OutputVoltPin,5500);        // Pin to measure output voltage, Max Voltage * 100
	  	  Volt Volt_12(Pin12V,2000);                // Pin to measure 12v suply, Max Voltage * 100

	  	  Filter OVolt_Filtered(13);                    // Filter function for Output Voltage
	  	  Filter OCurrent_Filtered(13);                 // Filter function for Output Current


	GChargeStatus = 2;								// Changen to function to set global fastcharge
	int FindCurrent = I_FAST / 100;

  while ((GChargeStatus == 2)  )                                // While charge status = Fast and no error
  {
      BatteryCurrent = Battery_current.readCurrent();           // Measure Battery Current:
      while (BatteryCurrent/100 != FindCurrent)                          // Loop until charge current == I_FAST, "soft start"
      {
        BatteryCurrent = Battery_current.readCurrent();     // Measure Battery Current in mA.
        if (BatteryCurrent/100 < FindCurrent)                       // Increase pwm if current to low
        {
          if (pwm > 250) { pwm = 250; }                         // Battery not connected or input voltage to low.
          pwm++;
          analogWrite(pwmPin, pwm);
          delay(10);
        }
        else if (BatteryCurrent/100 > FindCurrent)                         // Decrease pwm if current to high
        {
            if (pwm < 1) { pwm = 1; }                               // Output shortcut ??
            pwm--;
            analogWrite(pwmPin, pwm);
        }

      InputVolt = Volt_in.readVolt();                                       // Measure input voltage (With filtering and buffering)
      Volt12 = Volt_12.readVolt();                                          // Measure 12V suply voltage (With filtering and buffering).
      BatteryVolt = Volt_out.readVolt();                                    // Measure Batery voltage (With filtering and buffering)
 //     OVolt_Filtered.addValue(BatteryVolt);                                 // Add value to voltage smooting
 //     BatteryVolt = OVolt_Filtered.getFilteredValue();                      // Get filtered output volt.

          GBatteryVolt = BatteryVolt;
          GBatteryCurrent = BatteryCurrent;
          Gpwm = pwm;
          GInputVolt = InputVolt;

      }                                                           // I_FAST is set now.

   }                                                // Fast charge ends
}
