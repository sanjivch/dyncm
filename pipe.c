#include<stdio.h>
#include<conio.h>
#include<math.h>

void main()
{
	float a0,a1,a2,ratedspeed, nomspeed, speedfactor,head, flow;
	
	scanf("%f %f",&ratedspeed, &nomspeed);
	speedfactor=nomspeed/ratedspeed;
	
	scanf("%f %f %f", &a0, &a1, &a2);
	scanf("%f",&flow);
	
	head=a0*speedfactor*speedfactor+a1*speedfactor*flow+a2*flow*flow;
	
	printf("Head:%f",head);
	
	return 0;	
	
}
