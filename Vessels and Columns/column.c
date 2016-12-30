#include <stdio.h>
#include <conio.h>
#include <math.h>
#define PI 3.14
void main()
{
	//Sizing a column diameter
	float fFactor=1.22, velMax, vapDensity;//f-Factor is 1.22 in SI units Ref: Pg 12, Plantwide Dynamic Simulators in Chemical Processing and Control by W.Luyben
	float colCSArea, colDiameter;
	float volFlow;
	
	velMax=fFactor/sqrt(vapDensity);
	
	colCSArea=volFlow/velMax; //Convert units appropriately
	
	colDiameter= sqrt(4*colCSArea/PI);
	
	
	
}
