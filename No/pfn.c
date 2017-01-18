#include <stdio.h>
#include <conio.h>

void main()
{
	float elevation, initT, initP;
	int initCompIndex;
	float nodeTemp, nodeDensity, nodePressure;
	
	
	//volumetric flows come directly from the solver- convert into mass flows
	
	//densities of the streams are obtained from getProperty() function
	
	for(int stream=1; stream==numStreams; stream++)
		mass_density+=massFlowIn[stream]/densityIn[stream];
	
	nodeDensity = massOut/mass_density;
	
	//nodeTemp = 
	
	
}
