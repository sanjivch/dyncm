// 	Variable definitions:
//  	diaInner,diaOuter,epsilon,pipeLength, fitResistance, K1, Kinf, NRe;
//	viscosity, refViscosity, opTemp, refTemp;
//	fitResType;
//	flowArea;
//	flowVelocity,fluidDensity,massFlow,volFlow,resTime;


#include <iostream>
#include <math.h>
#define PI 3.1415

using namespace std;

int main()
{
	double diaInner,diaOuter,epsilon,pipeLength, fitResistance, K1, Kinf, fricFactor, NRe;
	double viscosity, refViscosity, opTemp, refTemp;
	int fitResType;
	double flowArea;
	double flowVelocity,fluidDensity,massFlow,volFlow,resTime;
	
	//Flow Area calculation
	flowArea = 0.25*PI*diaInner*diaInner;
	
	//Volumetric flow
	volFlow = massFlow/fluidDensity;
	
	//Flow velocity should be 1-3 m/s for liquids and 10-40 m/s for gases
	flowVelocity = volFlow/flowArea;
	
	//Residence time - should be more than 1 sec to avoid computational leaks
	resTime = pipeLength/flowVelocity;
	
	
	//Viscosity needs to be calculated at the operating tempwerature from the power law mu/muo=(T/To)^0.7 
	//Ref: http://www-mdp.eng.cam.ac.uk/web/library/enginfo/aerothermal_dvd_only/aero/fprops/propsoffluids/node5.html
	viscosity = refViscosity*pow((opTemp/refTemp),0.7);
	
	//Reynolds number
	NRe = diaInner*flowVelocity*fluidDensity/viscosity;
	
	cin >> fitResType;
	//fitResType -Fitting Resistance type:
	//      0 = 2K method
	//      1 = 3K method
	//      2 = L/D method (Ref: Crane TP410)
	// Ref: Chemwork - http://www.chemwork.org/PDF/board/Select%20the%20Best%20Fitting%20Pressure%20Loss%20Correlation.pdf
	switch(fitResType) {
      case 0 :
         fitResistance = K1/NRe +Kinf*(1+1/diaInner);
         break;
     case 1 :
         fitResistance = K1/NRe +Kinf*(1+Kinf/pow(diaInner,0.3));
         break;
     case 2 :
         fricFactor = 16.0/NRe;
	 fitResistance = K1 * fricFactor;
         break;
     default :
        cout << "Invalid Fitting Resistance type" << endl;
   }
	cout << fitResistance <<endl;
	
	
	//2K method
	//In this Equation K∞ is the "classic" K for a large fitting in the fully turbulent flow regime and K1 is the resistance coefficient at a Reynolds Number of 1. Note that although the K's and Re are dimensionless the fitting inside diameter (D) must be given in inches. Ref: http://www.katmarsoftware.com/articles/pipe-fitting-pressure-drop.htm
}
