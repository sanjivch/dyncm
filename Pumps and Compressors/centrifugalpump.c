#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <methods.h>//include a methods.h file 
void main()
{
	float a0,a1,a2,ratedSpeed, nomSpeed, speedFactor,headDeveloped, flow, powerRating;
	float efficiency;
	int curveFitType;//0 = Generic; 1 = Lagrange method
	
	// Fields from the GFE
	scanf("%f %f",&ratedSpeed, &nomSpeed);
	
	speedFactor=nomSpeed/ratedSpeed;
	
	//Ref: http://math.stackexchange.com/questions/804460/fitting-a-quadratic-polynomial-to-two-points-such-that-it-is-always-concave-down
	
	if(curveFitType == 1) //XY table is used to enter the flow vs head relationship to find the pump curve coefficients
	{
		a[]=lagrange();//create and call a lagrange method. Obtain the coeffecients into an array
	}
	//else
		
	
	scanf("%f %f %f", &a0, &a1, &a2);
	scanf("%f",&flow);
	
	headDeveloped = a0*speedFactor*speedFactor+a1*speedFactor*flow+a2*flow*flow;
	
	printf("Head:%f",headDeveloped);
	
	powerRating = flow*fluidDensity*headDeveloped*9.81*0.000001/(3.6*efficiency);
	
	return 0;	
	
}
