#include<stdio.h>
#include<conio.h>
#include<math.h>

void main()
{
	float a0,a1,a2,ratedSpeed, nomSpeed, speedFactor,head, flow;
	
	scanf("%f %f",&ratedSpeed, &nomSpeed);
	speedFactor=nomSpeed/ratedSpeed;
	
	scanf("%f %f %f", &a0, &a1, &a2);
	scanf("%f",&flow);
	
	head=a0*speedFactor*speedFactor+a1*speedFactor*flow+a2*flow*flow;
	
	printf("Head:%f",head);
	
	return 0;	
	
}
