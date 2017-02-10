#include <stdio.h>
#include <conio.h>
#include <math.h>
#define PI 3.14

void main()
{
//Heat exchanger code here
float diaInner, diaOuter, lenPipe;
int numTubes;
float areaHX, areaFinHX, LMTD, heatDuty, U, UcorrectionFactor, delT_In, delT_Out;
int dutyCalcType;//Slave =0; Master =1; //Master drives the heat exchange- it calculates the duty, slave accepts the duty(-ve value)
int configType; //0 = Co Current; 1 = Counter Current 

areaHX = areaFinHX + numTubes * PI * diaOuter * lenPipe/ 4.0;


//delta T calculation changes depending on the configuration of heat exchanger 
delT_In = T1In - T2In;
delT_Out = T1Out - T2Out;

LMTD = (delT_In-delT_Out)/ln(delT_In/delT_Out)
//Depending on the duty calculation type, the heatDuty changes
if(dutyCalcType == 1)
{
	heatDuty = U * areaHX * LMTD ;
}
else
	heatDuty = -getHeatDuty();//slave type

T1Out = T1In + heatDuty/ (massFlow * heatCapacity);//heatDuty becomes negative for the other stream


//UcorrectionFactor * 


}
