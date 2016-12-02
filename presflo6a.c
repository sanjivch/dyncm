/*============================================================================*/
//Newton method to solve DARCY Equation

/* = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define sqr(x) x*x

void main(void)
{
float x[6] ,cu[2]={.15865 99,.2 874489},c v[2]= {l.1651147,2.110871},vise,g,g2;
float ucl,uc2,uc3,dx,hdl,adl,f ,fl,dif, xx;
int ii,i,iv,i6,iu,m;
char *v[]={"hf","D","e","L","Q" ,"V"};

LI:
printf("Give 1=ES or 2=SI (or 0 0=STOP) & Vise ");
scanf("%d %f",&ii,&visc);

if(ii<l) exit(0);

if(ii==l) g=32.2; else g=9.81; g2=2.*g;

printf (11 \r\nGive No. of Unknown\r\n") ;

for(i=0;i<6;i++)
	printf("%d %s\r\n",i ,v[i]);

scanf ( "%d" , &iu) ;
if(iu<4) 
{
	printf ("\r\nGive 1 if Q will be given or 2 if V is known ") ;
	scanf("%d",&iv);
} 
else 
	iv=iu-3; ii--;
ucl=cu[ii]; uc2=cv[ii]*visc;
uc3=.78539816*ucl;
printf (11 \r\nGive value to knowns\r\n") ;
i = 0;

if(iu>3)i6=4;
else i6=5;

do 
{
	if(i==iu)i++;
	
	if(i==6-iv)i++;
	
	printf ("%s = 11, v [ i ] ) ;
	scanf("%f",ix[i]);
	i++;
} while (i<i6);
//Initialize unknowns

switch(iu)
{
	case 0: if(iv==l) x [5]= x [4]/(.7853982*sqr(x[1]));
	x [0]=.02* x [3]*sqr(x[5])/g2; break;
	
	case 1: if(iv==l) x [1]=pow(.02*x[3]*sqr(x[4])/(.6185*g2*x[0]),.2);
	else x [1]=.02*x[3]*sqr(x[5])/(g2*x[0]); break;
	
	case 2: x[2]=.0006; break;
	
	case 3: if(iv==l) x [3]=.6185*g2*x[0]*pow(x[1],5.)/(.02*sqr(x[4]));
	else x [3]=g2*x[0]* x [1]/(.02*sqr(x[5])); break;
	
	case 4: x [4]=sqrt(.6185*g2*x[0]*pow(x[1],5.)/(.02*x[3])); break;
	
	case 5: x [5]=sqrt(g2*x[0]* x [1]/(.02*x[3]));
}
// Newton Method
m= 0 ;
do 
{
	xx=x[iu];
	x[iu]*=1.005;
	dx=x[iu]-xx;
	L2 :
	hdl = sqrt(x[3]/x[0]);
	adl=2.0*logl0(x[2]/x[l]+uc2*hdl/pow(x[1],1.5))-1.14;
	
	if(iv==l) f=ucl*hdl*x[4]/pow(x[1],2.5)+adl;
	else f=uc3*hdl*x[5]/sqrt(x[1])+adl;
	m++;
	
	if(m %2!=0)
	{
		x[iu]=xx;fl=f;
		goto L2;
	}
	
	dif=dx*f/(fl-f);
	
	if(fabs(dif)>.8*x[iu])
	dif*=.5;
	x[iu]=xx-dif;
} while ((fabs(dif)>.00005) && (m<30));

if(m>29) printf("Failed to converge %f\r\n",dif);
if(iv==l) x [5]= x [4]/(.78539816*sqr(x[l]));
else x [4]=.7 8539 816*sqr(x[1])* x [5];

for(i=0;i<6;i++)printf("%s = %f\r\n",v[i],x[i]);
printf("f = %f\r\n",x[0]* x [1]*g2/(x[3]*sqr(x[5])) );
goto LI;
}
