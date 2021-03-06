#include<stdio.h>
#include<conio.h>
#include<math.h>
#define PI 3.1415

void main()
{
	float diaInner,diaOuter,epsilon,pipeLength, fitResistance, K1, Kinf, NRe, Cv, maxCv;//maxCv is defined by the user
	float viscosity, refViscosity, opTemp,refTemp;
	int fitResType, valveType;
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
	
	//Reynolds number
	//Viscosity needs to be calculated at the operating tempwerature from the power law mu/muo=(T/To)^0.7 Ref: http://www-mdp.eng.cam.ac.uk/web/library/enginfo/aerothermal_dvd_only/aero/fprops/propsoffluids/node5.html
	viscosity=refViscosity*(opTemp/refTemp)^0.7;
	NRe=diaInner*flowVelocity*fluidDensity/viscosity;
	
	//fitResType -Fitting Resistance type - 0=2K method, 1=3K method, 2=L/D method (Ref: Crane TP410)
	fitResistance=1000.0;
	
	fitResistance=K1/NRe +Kinf(1+1/diaInner);//2K method
	//In this Equation K∞ is the "classic" K for a large fitting in the fully turbulent flow regime and K1 is the resistance coefficient at a Reynolds Number of 1. Note that although the K's and Re are dimensionless the fitting inside diameter (D) must be given in inches. Ref: http://www.katmarsoftware.com/articles/pipe-fitting-pressure-drop.htm
	
	//The only difference between a pipe and control valve is the flow coefficent Cv in the valve. This is kind of a dynamically changing fitting resistance and depends on the valve type 0=Linear; 1=Equal Percentage; 2=Quick Opening
	
	
	
}
