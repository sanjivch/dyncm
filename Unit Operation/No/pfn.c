#include <stdio.h>
#include <conio.h>

void main()
{
	float elevation, initT, initP;//GUI level parameters
	int initCompIndex;//GUI level parameters 
	float nodeTemp, nodeDensity, nodePressure;
	
	
	//volumetric flows come directly from the solver- convert into mass flows
	
	//densities of the inletPorts are obtained from getProperty() function
	
	for(int inletPort=1; inletPort==numStreams; inletPort++)
		mass_density+=massFlowIn[inletPort]/densityIn[inletPort];
	
	nodeDensity = massOut/mass_density;
	
	
	//Temperature is calculated from the enthalpy H_mix = (Σ m_port * H_port)/massOut;
	enthalpySum += massFlowIn[inletPort]*enthalpyIn[inletPort];
	enthalpyMix = enthalpySum/massOut;
	nodeTemp = (enthalpyMix/spHeat)+ refTemp;
	
	//Pressure is calculated from the solver -  convert into the appropriate units (kPa or psi or barg)
	
	
	
	
}
