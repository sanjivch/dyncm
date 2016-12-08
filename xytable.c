#include <stdio.h>
#include <conio.h>
#include <math.h>

void main()
{
	int n; 
	float x,y,input,output=0;
	
	float x[100],y[100],a,s=1,t=1;
    int n,i,j,d=1;
    printf("\n\n Enter the number of the terms of the table: ");
    scanf("%d",&n);
    printf("\n\n Enter the respective values of the variables x and y: \n");
    for(i=0; i<n; i++)
    {
        scanf ("%f",&x[i]);
        scanf("%f",&y[i]);
    }

    while(d==1)
    {
        printf(" \n\n\n Enter the value of the x to find the respective value of y\n\n\n");
        scanf("%f",&input);
        for(i=0; i<n; i++)
        {
            s=1;
            t=1;
            for(j=0; j<n; j++)
            {
                if(j!=i)
                {
                    s=s*(input-x[j]);
                    t=t*(x[i]-x[j]);
                }
            }
            output=output+((s/t)*y[i]);
        }
        printf("\n\n The respective value of the variable y is: %f",output);
     
    }

}
