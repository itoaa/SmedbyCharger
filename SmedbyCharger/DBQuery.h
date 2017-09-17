/*
 * DBQuery.h
 *
 *  Created on: 3 sep. 2017
 *      Author: Ola Andersson
 *		Version	1.0
 *			Used to communicate with GlobalDB task
 */

#ifndef DBQUERY_H_
#define DBQUERY_H_

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

struct Queue_struct
{
	byte command;					// Type of command sent to queue
	int ID;							// ID of source and dest unit sent/recived the question
	int	value;						// Value of question / responce
	QueueHandle_t returnHandle;		// Potential return queue-handler.
};

extern QueueHandle_t Global_db_q;

void 	Global_db_set(int _ID, int _Value);
int 	Global_db_get(int _ID, QueueHandle_t Resice_queue);
void 	Global_db_index_set(int Index, char Value);
char 	Global_db_index_get(int Index, QueueHandle_t Resice_queue);

void 	Global_db_eprom_set(int _ID, int _Value);
int 	Global_db_eprom_get(int _ID, QueueHandle_t Resice_queue);

#endif /* DBQUERY_H_ */
