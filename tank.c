#include <stdio.h>
#include <conio.h>
#define PI 3.1415


void main()
{

		float tankHeight,diaInner, diaOuter, thickness, tankVolume, csArea;
		float massIn, massOut, massAccumulated=0,opPressure=101.3, fluidDensity, opHeight=0;//opPressure, opHeight should be an initial user input value. Need to change later.
		float botPressure;
		int tankShape, tankType;//tankType - 0=Open to atmosphere; 1=Pressurised; 
		float time, simTime=100.0,deltaT=0.1, dHeight; //simTime, deltaT should be user defined
		
	
		//Find outer dia 
		diaOuter=diaInner + thickness;
		
		//Cross-section Area of the tank
		csArea= PI*diaInner*diaInner/4;
		
		//Depending on the tank shape the tank volume changes. For now it is assumed that tank shape is cylindrical.
		tankVolume=PI*diaInner*diaInner*tankHeight/4;
		
		for(time=0.0; time=simTime; time+=deltaT)
		{
			//massIn= 
			
			//The instantaneous level in tank @ deltaT 
			dHeight=((massIn-massOut)*deltaT)/(csArea*fluidDensity);
			
			//opHeight is the Level of the tank at time 't'
			opHeight=opHeight+dHeight;
			if(opHeight >= 0.95*tankHeight)
				printf("Warning: tank possibly overflowing\n");
			
			//botPressure should be based on tankType- Units in KPa
			//add the opPressure to rho*g*h term- opPressure is the pressure at the top of the tank- depends on tankType
			botPressure=opPressure + (opHeight*fluidDensity*9.81*0.001);
		}
			

}
