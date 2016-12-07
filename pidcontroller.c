#include <stdio.h>
#include <conio.h>
#include <math.h>

void main()
{

	float processValue, setPoint, error, previousError, remSetPoint, controllerOut, epsilon=0.001, Kp, Ki, Kd, integral, derivative;//epsilon is the tolerance and is decided by the user
	float time, simTime, deltaT=0.01;//deltaT to be decided by the user
	
	
	for(time=0.0; time=simTime; time+=deltaT)
	{
		error=setPoint-processValue;
  
	
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

  
  


