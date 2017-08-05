/*
 * Filter10.cpp
 *
 *  Created on: 5 aug. 2017
 *      Author: Ola Andersson
 *      Dokumentation i h-filen
 */

#include "Filter10.h"

Filter::Filter(int bufferLength)
{
	_bufferLength = bufferLength;
	_bufferPosition = 0;
}

/*
Filter::~Filter()
{
	// TODO Auto-generated destructor stub
}
*/

// Add one value to the buffer.
void Filter::addValue(int value)
{
byte j;
int temp;
boolean done;

_bufferPosition = (_bufferPosition + 1) % filterSamples;    // increment counter and roll over if necc. -  % (modulo operator) rolls over variable
_sensArray1[_bufferPosition] = value;                       // input new data into new slot

for (j=0; j<filterSamples; j++)
{                                                           // transfer data array into anther array for sorting and averaging
   _sensArray1Sort[j] = _sensArray1[j];
}
done = 0;                                                   // flag to know when we're done sorting
while(done != 1)
{                                                           // simple swap sort, sorts numbers from lowest to highest
 done = 1;
 for (j = 0; j < (filterSamples -1); j++)
 {
   if (_sensArray1Sort[j] > _sensArray1Sort[j + 1])        // numbers are out of order - swap
   {
     temp = _sensArray1Sort[j + 1];
     _sensArray1Sort [j+1] =  _sensArray1Sort[j] ;
     _sensArray1Sort [j] = temp;
     done = 0;
   }
 }
}
}
                                                                       // Get filtered and averaged value based on buffer values.
int Filter::getFilteredValue(void)
{
int  top, bottom, k, l;
long total;
                                                                       // throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
bottom = max(((filterSamples * 15)  / 100), 1);
top = min((((filterSamples * 85) / 100) + 1  ), (filterSamples - 1));   // the + 1 is to make up for asymmetry caused by integer rounding
k = 0;
total = 0;
for ( l = bottom; l< top; l++)
{
 total += _sensArray1Sort[k];                                          // total remaining indices
 k++;
}
return( total / k);                                                     // divide by number of samples
}


int Filter::getValue(int index)                                           // Get valu from buffer. index = position in buffer. (0 = newest value)
{
return (_sensArray1[index]);
}
int Filter::getSortValue(int index)                                       // Get value from sorted buffer. index = position in sorted buffer. (0 = lowes value)
{
return (_sensArray1Sort[index]);
}
