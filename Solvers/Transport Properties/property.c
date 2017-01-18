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
	
}
