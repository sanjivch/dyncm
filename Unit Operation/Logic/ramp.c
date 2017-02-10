#include <stdio.h>
#include <conio.h>

void main()
{
	float initialValue,	finalValue,	rampUpTime,	rampDownTime;//GUI parameters
	float scaleUp, scaleDown, currentValue, previousValue;
	
	
	//Ramp the value of output from initial value to a final value for a given time input
	scaleUp = (finalValue - initialValue)/rampUpTime;
	scaleDown = (finalValue - initialValue)/rampDownTime;
	if(simRunFlag != 0)
		if(previousValue < currentValue)
			currentValue = initialValue + (scaleUp*delT);
		else
			currentValue = previousValue - (scaleDown*delT);
		
	
}
