/*
 * ChargeDB10.cpp
 *
 *  Created on: 17 sep. 2017
 *      Author: Ola Andersson
 *      Version 1.0
 *      Se h-file for info
 */

#include "ChargeDB10.h"


ChargeDB::ChargeDB()
{
//	Global_vars.Charger_state = 0;
}
ChargeDB::~ChargeDB()
{
}


void ChargeDB::Set_var(int ID, int Value)
{
	int * Temp_pointer;
	Temp_pointer = (int*)&Global_vars + (ID*2);
	*Temp_pointer = Value;
}

int ChargeDB::Get_var(int ID)
{
	int * Temp_pointer;
	Temp_pointer = (int*)&Global_vars + (ID * 2);
	return(*Temp_pointer);

}

void ChargeDB::Set_index(int Index, char Value)
{
	char * Temp_pointer;
	Temp_pointer = (char*)&Global_vars + (Index);
	*Temp_pointer = Value;
}

char ChargeDB::Get_index(int Index)
{
	char * Temp_pointer;
	Temp_pointer = (char*)&Global_vars + (Index);
	return(*Temp_pointer);

}


