//Lagrange interpolation to obtain the pump curve coefficients

#include <stdio.h>
#include <conio.h>

void main()
{
	float Q1,Q2,Q3,H1,H2,H3,a0,a1,a2;
	
	printf("Enter Q and H in (x,y) pairs\n");
	scanf("%lf %lf %lf %lf %lf %lf", &Q1, &H1, &Q2, &H2, &Q3, &H3);
	
	
	a0=(H1/(Q1-Q2)*(Q1-Q3))+(H2/(Q2-Q1)*(Q2-Q3))+(H3/(Q3-Q1)*(Q3-Q2));
	a1=-((Q2+Q3)*(H1/(Q1-Q2)*(Q1-Q3))+(Q1+Q3)*(H2/(Q2-Q1)*(Q2-Q3))+(Q1+Q2)*(H3/(Q3-Q1)*(Q3-Q2)));
	a2=(Q2*Q3)*(H1/(Q1-Q2)*(Q1-Q3))+(Q1*Q3)*(H2/(Q2-Q1)*(Q2-Q3))+(Q1*Q2)*(H3/(Q3-Q1)*(Q3-Q2));
	
	printf("a0=%lf a1=%lf a2=%lf\n",a0,a1,a2);
	
	
}
