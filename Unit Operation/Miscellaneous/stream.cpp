#include <iostream>
using namespace std;
struct Stream
{
        float T;
        float P;
        float fluidDensity;
        float enthalpy;
        float comp[i];  
};

int main()
{
    Stream s1;

    cout << "Temperature: ";
    cin>> s1.T;
    cout << "Pressure: ";
    cin >> s1.P;
    cout << "Density: ";
    cin >> s1.fluidDensity;
    cout << "enthalpy";
    cin >> s1.enthalpy;
    cout << "Composition";
        
}
