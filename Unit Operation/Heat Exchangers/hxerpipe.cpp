#include <iostream>
#include <chrono>
#include <random>
#include <math.h>
#define PI 3.14

using namespace std;

int main()
{
//Heat exchanger code here
int numTubes;
int configType; //0 = Co Current; 1 = Counter Current
double diaInner, diaOuter, lenPipe;

double areaHX, areaFinHX, LMTD, heatDuty, U, UcorrectionFactor, delT_In, delT_Out;
int dutyCalcType=1;//Slave =0; Master =1 - Master drives the heat exchange- it calculates the duty, slave accepts the duty(-ve value)

double T1In, T1Out, T2In, T2Out;
double heatCapacity=3.5, massFlow=10.0;
 
/* unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);

  normal_distribution<double> distribution (0.0,1.0);

  cout << "some Normal-distributed(0.0,1.0) results:" << endl;
  for (int i=0; i<10; ++i)
    cout << distribution(generator) << endl;*/

cout << "OD: ";
cin >> diaOuter;
cout << "No. of tubes: ";
cin >> numTubes;
cout << "Length of the tubes: ";
cin >> lenPipe;
cout << "Area of Fins: ";
cin >> areaFinHX;

//Effective Heat exchange area
areaHX = areaFinHX + numTubes * PI * diaOuter * lenPipe * 0.25;

cout << "HX Area: " << areaHX << endl;

cout << "Approach temperatures:" << endl;
cout << "T1 In: ";
cin >> T1In;
cout << "T1 Out: ";
cin >> T1Out;
cout << "T2 In: ";
cin >> T2In;
cout << "T2 Out: ";
cin >> T2Out;

cout << "Heatexchanger configuration?\n0 = Co current; 1 = Counter current: ";
cin >> configType;

//delta T calculation changes depending on the configuration of heat exchanger 
if(configType==0)
{
  delT_In = T1In - T2In;
  delT_Out = T1Out - T2Out;
}
else
{
  delT_In = T1In - T2Out;
  delT_Out = T1Out - T2In;
}

if(delT_In!=delT_Out)
  LMTD = (delT_In-delT_Out)/log(delT_In/delT_Out);
else
  LMTD = delT_Out;

cout << "LMTD: " << LMTD << endl;

cout << "Heat exchange coefficient, U: ";
cin >> U;

//Depending on the duty calculation type, the heatDuty changes
if(dutyCalcType == 1)
	heatDuty = U * areaHX * LMTD ;
else
	heatDuty = 0;// -getHeatDuty();//slave type

cout << "Heat Duty: " << heatDuty << endl;

T1Out = T1In + heatDuty/ (massFlow * heatCapacity);//heatDuty becomes negative for the other stream
cout << "Outlet temperature: " << T1Out << endl;

//UcorrectionFactor * 


}
