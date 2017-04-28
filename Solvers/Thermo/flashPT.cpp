#include <iostream>
#include <math.h>

using namespace std;

int main(){
  
  cout << "=====================\n      PT Flash\n=====================" << endl;
  
  
  double Feed, Vap, Liq, alpha, newalpha;
  int components;
  double fv, dfv;
  cout <<"Enter num of components: "<< endl;
  cin >> components;
  
  double composition[components-1];
  double pSat[components-1], P;
  double K[components-1];

  
  cout << "Enter Pressure of the flash tank: "<< endl;
  cin >> P;
  
  cout << "Enter Feed: "<<endl;
  cin >> Feed;
  cout << "Enter compositions, pSat_i: " <<endl;
  for(int i=0; i<components; i++){
    
    cin >> composition[i] >> pSat[i];
    
    K[i] = pSat[i]/P;//Get pSat from Antonie's equation
  }
  fv = dfv =0;
  alpha =0;
  for(int iter =1; iter < 10; iter++){
    cout << iter << endl;
    for(int i=0; i<components; i++){
    
    fv+=composition[i]*(K[i] - 1)/(alpha*(K[i] - 1) + 1);
    dfv-=(composition[i]*pow(K[i]-1,2)/pow(alpha*(K[i]-1)+ 1,2));
     cout << fv <<" " << dfv << endl;
    
    }
    alpha-=(fv/dfv);
    if(abs(fv/dfv) < 0.01)
      break;
    cout << alpha << endl;
  }
  
  cout << alpha << endl;
  
  cout << "Vap =" <<alpha*Feed << endl;
  cout << "Liq =" << Feed - Vap << endl;
  
}
