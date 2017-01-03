#include <stdio.h>
#include <conio.h>
#include <solvers.h>//include this header file

void main()
{
	int arraySize, num_PFObjects, num_nodes;
	float a[10][10],h[10],q[10];
	float a12[10][10],a21[][];
	float n;
	float q_pipe[],k_pipe[],dE[];
	float h_node[], dq[];
	
	//get the details from the database/ whatever!!
	num_PFObjects = getnumPFO();
	num_nodes = getnumNodes();
	
	//get the count of number of pipes/valves/pumps/compressors/any PF object and the number of nodes. Ignore boundaries!
	arraySize = num_PFObjects + num_nodes;
	//float * pfArray = malloc(arraySize*sizeof(float)); 
	
    float *pfArray[arraySize];
    for (i=0; i<arraySize; i++)
         pfArray[i] = (float *)malloc(arraySize * sizeof(float));
 
    // Note that pfArray[i][j] is same as *(*(pfArray+i)+j)
    count = 0;
    for (i = 0; i <  arraySize; i++)
      for (j = 0; j < arraySize; j++)
         pfArray[i][j] = ++count; 
 
     
    /* Code for further processing and free the 
      dynamically allocated memory */
 
	/*Build the PF network array once before the simulation starts. This array should not change during the simulation. 
	Everytime a simulation is started the network is built from the scratch and will probably take few seconds to minutes for the build activity. Once the simulation is running the network array is solved for every timestep decided by the user. 
	
	1. Build a Node network
	2. Build a PF Object network	
	
	
	Hybrid or Gradient approach is being followed. Loops will be automatically taken care of! 
	
	All the flow equations are based on mass, because mass should be conserved and it is easier to convert the mass flow to volumetric flow!
	
	*/
	
	//PFObject equations
	
	
	//Node equations
	
	
	
	
}
