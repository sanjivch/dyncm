/*	Boston-Britt Inside Out Calculation Sequence
1) Initialize A, B, C, D, E, F, αi
2) Guess R
3) Solve for pi, Kb, T, L, V, xi and yi using the above equations
4) Convert flow rates to a mass basis and evaluate simplified mass enthalpies for the
 balance equation:
ψ(R) = H'f + Q/F' + (L'/F') (H'l(x, T, P) - H'v (y, T, P)) - H'v (y, T, P).
5) If ψ(R) is within a zero tolerance, go to 6). Else, update the guess for R and go to
 step 3).
6) At first pass, obtain new values of A, B, C, D, E, F, αi by comparing with 
 nonideal expressions. Thereafter, update only A, C, E, and αi by using
 Broyden's method to match these parameters with the nonideal expressions */

#include <stdio.h>
#include <conio.h>

void main()
{
 float A, B, C, D, E, F, alpha[];
 float R;
 float p[], Kb, T, Tstar, L, V, f[], z[], x[], y[];//change the array declarations
 float 
 
 
 //Initialize A, B, C, D, E, F, alphai
 
	 A=0.0;
	 B=0.0;
	 C=0.0;
	 D=0.0;
	 E=0.0;
	 F=0.0;
	 
	for(i=0;i<numComponents;i++)
	{
		alpha[i]=0.0;
		//From the mass balance:  zi*F = fi = V*yi + L*xi;
		
		f[i] = z[i]*F; 
	  
		/* Using yi = Ki xi and by defining Ki = αi Kb, we have: fi = (V*Ki + L)*xi = (αi*V*Kb + L)*xi
		Dividing by (VKb + L) and substituting for R yields: fi /(V*Kb + L) = (αi*VKb + L)*xi /(V*Kb + L)
		fi /(VKb + L) = (αi*R + 1-R)*xi
		We now define a new set of variables: pi ≡ xi*(V*Kb + L) = xi*L/ (1-R)*/
		
		p[i]= f[i]/(alpha[i]*R + 1-R);
		
		sum_p+=p[i];
		sum_alphap+=alpha[i]*p[i];
	}
		//Note that the pi are determined only from R and quantities specified in the outer loop. From the summation and equilibrium equations we can recover:
		L = (1-R)*sum_p;
		V = F - L;
		Kb = (sum_p/sum_alphap);
	
	
	for(i=0;i<numComponents;i++)
	{
	
		x[i] = p[i]/(V*Kb + L);
		y[i] = alpha[i]*Kb*x[i];
		
	}
	
		T = 1/((ln Kb - A)/ B + 1/Tstar);
	
	
	
	//Using R as the iteration variable, the flash calculation is completed by checking the simplified enthalpy balance.

	//Simplified Enthalpy balance
	ψ(R) = Hf + Q/F + (L/F)*(Hl(x, T, P) - Hv (y, T, P)) - Hv (y, T, P);
	
	
	

}
