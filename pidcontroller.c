#include <stdio.h>
#include <conio.h>
#include <math.h>

void main()
{

	float processValue, setPoint, error, previousError=0.0, remSetPoint, controllerOut, epsilon=0.001, Kp, Ki, Kd, integral, derivative;//epsilon is the tolerance and is decided by the user
	int controllerType, controllerMode, controllerAction;
	//controllerType: 0=P only; 1=PI; 2=PID;  3 PD - To be decided by the user
	//controllerMode: 0=Manual; 1=Auto: 2=Remote
	//controllerAction:0=Direct; 1=Reverse
	float time, simTime=100.0, deltaT=0.01;//deltaT to be decided by the user
	
	
	//Controller tuning parameters - defaults; User can tune the parameters to achieve satisfactory control 
	Kp=1.0;
	Ki=1.0;//Integral rate is used instead of time
	Kd=1.0;
	
	
	for(time=0.0; time=simTime; time+=deltaT)
	{
		error=setPoint-processValue;
			
		if(controllerAction==1)
			Kp=-Kp;
		//Incaseof error too small then stop integration
		if(abs(error)> epsilon)
		{
		integral += error*deltaT;
		}
		
		derivative = (error -previousError)/deltaT;
		
		controllerOut = Kp*error+ Ki*integral+ Kd*derivative;
		
		//Saturation Filter
		/*if(output> MAX)
		{
		output= MAX;
		}
		elseif(output< MIN)
		{
		output= MIN;
		}*/
		//Update error
		previousError= error;
	}
	
	
}
