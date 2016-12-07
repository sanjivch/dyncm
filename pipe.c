#include<stdio.h>
#include<conio.h>
#include<math.h>
#define PI 3.1415

void main()
{
	float diaInner,diaOuter,epsilon,pipeLength, fitResistance;
	int fitResType;
	float flowArea;
	float flowVelocity,fluidDensity,massFlow,volFlow,resTime;
	
	//Flow Area calculation
	flowArea=PI*diaInner*diaInner/4;
	
	//Volumetric flow
	volFlow=massFlow/fluidDensity;
	
	//Flow velocity should be 1-3 m/s for liquids and 10-40 m/s for gases
	flowVelocity=volFlow/flowArea;
	
	//Residence time - should be more than 1 sec to avoid computational leaks
	resTime=pipeLength/flowVelocity;
	
	//fitResType -Fitting Resistance type - 0=2K method, 1=3K method, 2=L/D method (Refer Crane TP410)
	fitResistance=1000.0;
	
}
