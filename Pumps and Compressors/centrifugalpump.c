#include<stdio.h>
#include<conio.h>
#include<math.h>

void main()
{
	float a0,a1,a2,ratedspeed, nomspeed, speedfactor,headDeveloped, flow, powerRating;
	
	scanf("%f %f",&ratedspeed, &nomspeed);
	
	speedfactor=nomspeed/ratedspeed;
	
	scanf("%f %f %f", &a0, &a1, &a2);
	scanf("%f",&flow);
	
	headDeveloped=a0*speedfactor*speedfactor+a1*speedfactor*flow+a2*flow*flow;
	
	printf("Head:%f",headDeveloped);
	
	powerRating=flow*fluidDensity*headDeveloped*9.81*0.000001/(3.6*efficiency);
	
	return 0;	
	
}
