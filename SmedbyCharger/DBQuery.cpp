/*
 * DBQuery.cpp
 *
 *  Created on: 3 sep. 2017
 *      Author: olaandersson
 */

#include "DBQuery.h"

void Global_db_eprom_set(int _ID, int _Value) {}
int Global_db_eprom_get(int _ID, QueueHandle_t Recive_queue) {return(0);}


void Global_db_set(int ID, int Value)
{
	Queue_struct Mess_out;

	Mess_out.command = 11;
	Mess_out.ID = ID;
	Mess_out.value = Value;
	Mess_out.returnHandle = NULL;
    xQueueSendToBack(Global_db_q,&Mess_out,1000);
}

int Global_db_get(int ID, QueueHandle_t Recive_queue)
{
	Queue_struct Mess_in,Mess_out;

	Mess_out.command = 10;
	Mess_out.ID = ID;
	Mess_out.returnHandle = Recive_queue;
    xQueueSendToBack(Global_db_q,&Mess_out,1000);
	xQueueReceive(Recive_queue,&Mess_in,1000);
	return(Mess_in.value);

}

void Global_db_index_set(int Index, char Value)
{
	Queue_struct Mess_out;

	Mess_out.command = 21;
	Mess_out.ID = Index;
	Mess_out.value = Value;
	Mess_out.returnHandle = NULL;
    xQueueSendToBack(Global_db_q,&Mess_out,1000);
}

char Global_db_index_get(int ID, QueueHandle_t Recive_queue)
{
	Queue_struct Mess_in,Mess_out;

	Mess_out.command = 20;
	Mess_out.ID = ID;
	Mess_out.returnHandle = Recive_queue;
    xQueueSendToBack(Global_db_q,&Mess_out,1000);
	xQueueReceive(Recive_queue,&Mess_in,1000);
	return(Mess_in.value);

}
