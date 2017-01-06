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


areaHX = areaFinHX + numTubes * PI * diaOuter * lenPipe/ 4.0;

delT_In =
delT_Out =

LMTD = (delT_In-delT_Out)/ln(delT_In/delT_Out)

heatDuty = U * areaHX * LMTD ;

T1Out = T1In + heatDuty/ (massFlow * heatCapacity);//heatDuty becomes negative for the other stream



heatDuty = getHeatDuty();
//UcorrectionFactor * 


}
