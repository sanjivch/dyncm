#include <stdio.h>
#include <conio.h>

void main()
{
	float sliderPosition, minValue, maxValue, scalingFactor;
	
	scalingFactor = (maxValue - minValue)/100.0;
	
	sliderPosition = getposition()*scalingFactor;//getposition() is the value from the GUI
	
	
}