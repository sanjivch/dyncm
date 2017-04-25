#include <iostream>
using namespace std;

int main()
{
	double inletPres, inletTemp;
	double elevation;
	double fluidDensity;
	int enableEquilibrium;//option helps in evaluating the saturated pressure or temp- may be for later- dummy variable
	int numComponents;
	cin >> numComponents;
	double sumComp = 0.0;
	double composition[numComponents];
	
	fluidDensity=1000.0;//default density is 1000 kg/m3. Fluid Density will be defined by the composition. Composition should be read from the Component db. Composition will in mass fraction or mol fraction
	//Part of the solver. Flows will be defined based on the downstream objects!
	
	for(int i= 0; i< numComponents; i++){
	  cin >> composition[i];
	  sumComp+= composition[i];
	}
	cout << sumComp << endl;
	//fluidDensity = 
	
	
}
