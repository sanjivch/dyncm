#include <iostream>
#define PI 3.1415

using namespace std;

int main()
{

		double tankHeight, diaInner, diaOuter, thickness, tankVolume, csArea;
		double massIn, massOut, massAccumulated=0.0,opPressure=101.3, fluidDensity, opHeight=0.0, overFlowLimit;//opPressure, opHeight should be an initial user input value. Need to change later.
		double botPressure;
		int tankShape, tankType;//tankType - 0=Open to atmosphere; 1=Pressurised; 
		double tim, simTime=10000.0,deltaT=0.1, dHeight; //simTime, deltaT should be user defined
		
		//GUI level calculation
		//Find outer dia 
		cout << "ID and Thickness: ";
		cin >> diaInner >> thickness;
		diaOuter = diaInner + thickness;
		cout << "OD: " << diaOuter << endl;
		
		cout << "Tank height: ";
		cin >> tankHeight;
		
		//Cross-section Area of the tank
		csArea= PI*diaInner*diaInner*0.25;//multiplying by 0.25
		
		//Depending on the tank shape the tank volume changes. For now it is assumed that tank shape is cylindrical.
		tankVolume=csArea*tankHeight;//multiplying by 0.25
		cout << "Tank Volume: " << tankVolume << endl;
		overFlowLimit = 0.95*tankHeight;
		
		cout << "Mass flows: In, Out ";
		cin >> massIn >> massOut;
		
		cout << "Fluid density";
		cin >> fluidDensity;
		
		for(tim=0.0; tim<=simTime; tim+=deltaT)//this "for" loop should go. the global sim controller should take care of sim time 
		{
			//massIn= getFlowIn(BN);
			
			//massOut = getFlowOut(BN);//from connected d/s BN; Usually oscillates when the level in tank is empty. User should ensure that the tank is not empty. If empty, the user should ensure that d/s does not draw any fluid to stabilise the network d/s.
			
			//The instantaneous level in tank @ deltaT 
			dHeight=((massIn-massOut)*deltaT)/(csArea*fluidDensity);
			
			//opHeight is the Level of the tank at time 't'
			opHeight+= dHeight;
			if(opHeight >= overFlowLimit)//probably a limit can be defined at the GUI level, need not calculate the value everytime
			  cout <<"Warning: tank possibly overflowing\n";
			
			//botPressure should be based on tankType- Units in KPa
			//add the opPressure to rho*g*h term- opPressure is the pressure at the top of the tank- depends on tankType
			botPressure=opPressure + (opHeight*fluidDensity*0.00981);//9.81*0.001 is changed to 0.00981
			cout << "Pressure: " << botPressure <<endl;
		}
			

}

