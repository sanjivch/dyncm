#include <iostream>
{

sp_mat A = sprandu<sp_mat>(1000, 1000, 0.1);

vec b = randu<vec>(1000);
mat B = randu<mat>(1000, 5);

//vec x = spsolve(A, b);  // solve one system
mat X = spsolve(A, B);  // solve several systems

bool status = spsolve(x, A, b);  // use default solver
if(status == false)  { cout << "no solution" << endl; }

spsolve(x, A, b, "lapack");   // use LAPACK  solver
spsolve(x, A, b, "superlu");  // use SuperLU solver

superlu_opts settings;

settings.permutation = superlu_opts::NATURAL;
settings.refine      = superlu_opts::REF_NONE;

spsolve(x, A, b, "superlu", settings);
}
