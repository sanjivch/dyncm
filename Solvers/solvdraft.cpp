#include <iostream>
{

size = numPF+numNode;
sp_mat A = sprandu<sp_mat>(size, size);
//Populate the matrix with 

//vec b = randu<vec>(1000);
mat B = randu<mat>(size, 1);

//vec x = spsolve(A, b);  // solve one system
mat X = spsolve(A, B);  // solve several systems

//bool status = spsolve(x, A, b);  // use default solver
//if(status == false)  { cout << "no solution" << endl; }

//spsolve(x, A, b, "lapack");   // use LAPACK  solver
//spsolve(x, A, b, "superlu");  // use SuperLU solver

/*superlu_opts settings;

settings.permutation = superlu_opts::NATURAL;
settings.refine      = superlu_opts::REF_NONE;

spsolve(x, A, b, "superlu", settings);*/
  
  
//Use approx_equal function to compare the convergence of the PF network. In this example the tolerance is 0.002. Tolerance can be set from the Settings window. 
bool same1 = approx_equal(A, B, "absdiff", 0.002);

//If converged within 25 iterations push the solution to the display interface

}
