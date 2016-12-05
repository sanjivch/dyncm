#include<stdio.h>
#include<conio.h>
#include<math.h>
#define PI 3.1415

int main()
{
	float diaInner,diaOuter,epsilon,pipeLength,flowArea,flowVelocity,fluidDensity,massFlow, volFlow;
	
	//Flow Area calculation
	flowArea=PI*diaInner*diaInner/4;
	
	volFlow=massFlow/fluidDensity;
	
	flowVelocity=volFlow/flowArea;
	
	resTime=pipeLength/flowVelocity;
	
	
}
