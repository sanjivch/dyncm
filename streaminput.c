#include <stdio.h>
#include <conio.h>

void main()
{
	float inletPres, inletTemp;
	float elevation;
	float fluidDensity;
	int enableEquilibrium;//option helps in evaluating the saturated pressure or temp- may be for later- dummy variable
	
	fluidDensity=1000.0;//default density is 1000 kg/m3. Fluid Density will be defined by the composition. Composition should be read from the Component db. Composition will in mass fraction or mol fraction
	//Part of the solver. Flows will be defined based on the downstream objects!
}
