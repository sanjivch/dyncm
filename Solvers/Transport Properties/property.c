/*This file contains all of the thermodynamic and physical property
models available in ChemSep. The formulae for most methods are given here but
additional reading is available in the following sources:
A: R.C. Reid, J.M. Prausnitz and B.E. Poling, The Properties of Gases and Liquids,
4th Ed., McGraw-Hill, New York (1988).
B: S.M. Walas, Phase Equilibria in Chemical Engineering, Butterworth Publishers,
London (1985).
*/
#include <stdio.h>
#include <conio.h>
#includ <math.h>

void main()
{
	//Vapor pressure models
	//Antonie equation
	
	Psat= exp(A - B/(T+C));//T in K
	
	//Equation of State
	//Ideal
	P = n*R*T/V;

	//Virial
	P = (1+B)*R*T/V;
	
	//Cubic - Van der Waals (should not be used for liquid phase)
	P = (R*T/(V-b))-(a/(V*V)));
	
	//Cubic - Redlich-Kwong (should not be used for liquid phase)
	P = (R*T/(V-b))-(a/(sqrt(T)*V*(V+b))));
	
	//Cubic - Soave-Redlich-Kwong (suitable for hydrocarbon mixtures)
	P = (R*T/(V-b))-(a/(V*(V+b))));
	
	//Cubic - Peng Robinson (improved liquid densities)
	P = (R*T/(V-b))-(a/(V*(V+b) + b*(V-b))));
}
