/*============================================================================

NQ=1 FLOW UNIT IN GPM
SUPPRESS IN PUT DATA SUMMARY, IF
IT NOT EQUAL TO ZERO

*/
/* ============================================================================*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZ 20

FILE *fili,*filo;
void main(void)
{
	int JA[MAX_SIZ] ,JB[MAX_SIZ] , JIJ[MAX_SIZ] , JJTJN[MAXJ3IZ] ,MPL[30] , JD[MAX_SIZ] ;
	int M[MAX_SIZ] ,NEX[MAX_SIZ] ,NIX[MAX_SIZ] ,JPIP[MAX_SIZ] ,JJI[MAX_SIZ] ,NJO[MAX_SIZ] ;
	int KCLO[MAX_SIZ],KPI[MAXSIZ];
	double E[MAX_SIZ] ,B[MAX_SIZ] ,W9[MAX_SIZ] ,Y[MAX_SIZ] ,YY[MAX_SIZ] ,ENGY[MAX_SIZ] ;
	double Q[MAX_SIZ];
	int KK ,KN,KJ ,NEL,IPRINT,NXX ,NEXT,NTEP,N1 ,N2 ,N3 ,MBEG,MJJ,m ,JMAX,JMIN,II;
	double CQ,QEXTT,QEXT,PRES,SW,PMAX,PMIN,QEX,QIN,QOUT;
	int i, j, k, I, J8 ,J9,J,I,IOUT,NJOUT,NQ,NMOM,JDIFF,L,TT1;
	char fnaml[21],fnam2[21];

	/*============================================================================*/
	
	printf("Give file name for input\r\n");
	scanf("%s",fnaml);
	if((fili=fopen(fnaml,"r+"))==NULL)
	{
		printf("Cannot open input f. %s",fnaml);
		exit(0);
	}
	printf("Give file name for output\r\n");
	scanf("%s",fnam2);
	
	if((filo=fopen(fnam2,"a+"))==NULL)
	{
		printf("Cannot open output f. %s",fnam2);
		exit(0);
	}
	
	/*============================================================================*/
	
	fscanf(fili,"%d %d %d %d %d %d %d %d %d",KK,KN,KJ,NEL,NTEP,IOUT,NJOUT,NQ,NMOM);
	fscanf(fili, "%lf %lf",CQ,SW);
	
	for(j =1;j <=KK+1;++j ) 
	{
		fscanf(fili,"%d",M[j]);
	}
	
	for (j =1;j <=NEL;++j) 
	{
		fscanf(fili,"%d",MPL[j]);
	}
	
	for(j=1;j<=KK;++j)
	{
		fscanf(fili, "%lf %lf %1f",Q[j] ,ENGY[j],YY[j]);
	}

	for(j=1;j<=KK;++j)
	{
		fscanf(fili,"%d %d %d %d",JA[j],JB[j],KPI[j] ,KCLO[j]);
	}
	
	for(i=1;i<=NTEP;++i)
	{
		fscanf(fili,"%d %d",JJUN[j],JPIP[j]);
	}
	
	for(j=1;j<=KN;++j)
	{
		fscanf(fili, "%d %d %d %d",JIJ[j], JJI[j], E[j], B[j]);
	}
	
	/*============================================================================*/
	/* IOUT== ZERO FOR FULL OUTPUT
	*/
	/* IOUT!=0 FOR SELCTED JUNCTION FOR THE RESULT
	*/
	/* NJOUT!=0 THERE ARE JUNCTION SELCTED TO SHOW A RESULT
	*/
	/* NJO[ ] ==1 HERE THE JUNCTION ONE IS SELCTED IN THE RESULT
	/* YY[] = THE HEAD LOSS IN THE PIPE =HL-PUMP HEAD+MINOR LOSSES
	/* THIS PROGRAM'S TO COMPUTE THE GRADE LINE AND THE PRESSURE AT EACH JUNCTION
	/ * AND TO SHOW THE MAXIMMUM PRESSURE AND THE MINIMUM PRESSURE IN THE NETWORKS.
	/ * SUMMARY OF INFLOW AND OUTFLOW FROM FIXED GRADE NODE.
	/ * THE NET FLOW INTO THE SYSTEM AND THE NET FLOW OUT OF THE SYSTEM
	/* ============================================================================*/
	for(i=1;i<=KJ;++i)
	{
		Y[i] =0.0;
	}
	
	NEXT=NTEP;
	for(j =1;j <=NEXT;++j)
	{
		m=JJUN[j];
		J8=JIJ[m];
		NEX[j]=J8;
		J9=JPIPtj];
		Y[J8]=ENGY[J9]+YY[J9];
		
		if (JA[J9]== 0)
		{
			Y[J8]=ENGY[J9]-YY[J9];
		}
	}
	MO:
	;
	NXX=0;
	for(i=1;i<=NEXT;++i)
	{
		J=NEX [i] ;
		MBEG=M[J];
		MJJ=M[J+1]-1;
		
		for(k=MBEG;k<=MJJ;++k)
		{
			N1=MPL[k];
			Nl=abs(Nl);
			N2=JA[Nl];
			N3=JB[Nl];
			if(N2==J)
			{
				if(N3==0)
				{
					continue;
				}
				
				if(Y[N3]!=0)
				{
					continue;
				}
				
				Y[N3] =Y[N2] -YY[Nl];
				NXX=NXX+1;
				NIX[NXX]=N3;
			}
			
			if(N2==0)
			{
				continue;
			}
			
			if(Y[N2]!=0)
			{
				continue;
			}
			
			Y[N2] =Y[N3] +YY [Nl] ;
			NXX=NXX+1;
			NIX[NXX]=N2;
		}
	}
	
	NEXT=NXX;
	if(NEXT!=0)
	{
		for(i=l;i<=NEXT;++i)
		{
			NEX[i] =NIX[i] ;
		}
	goto MO;
	}
	
	for(j=1;j <=KN;++j)
	{
		I=JJI[j];
		IPRINT=1;
		
		if(IOUT!=0)
		{
			IPRINT=0;
			if(NJOUT!=0)
			{
				for(l=1;l<=NJ0UT;++l)
				{//
					if(NJO[l]==I)
					{
						IPRINT=1;
						
					}
				} // --------------- L
			}
		}
		
		PRES = (Y[j]- E[j])*SW*62.4/144.0;
		
		if(NQ==3)
		{
			PRES=(Y[j] - E[j]) * SW * 9.807;
		}
		
		W9[j]=PRES;
		
		if(E[j]==0)
		{
			W9[j]=0;
		}
		
		QEXT=-B[j]*CQ;
		
		if (B[j]<=0)
		{
			QEXT=0;
		}
		
		QEXT=QEXTT+QEXT;// the net system demand
		
		if(IPRINT==0)
		{//------ > next j
			continue;
		}
		
		if(E[j]==0)
		{
			printf("\n I=%d	QEXT=%lf %lf %lf",I,QEXT,Y[j],W9[j]);
		}
		
		if(E[j]!=0)
		{
			printf ("\n I=%d QEXT=%lf %lf PRES=%lf",I ,QEXT,Y[j],PRES);
		}
	}
	
	if(NMOM!=0)
	{
		printf("\n Maximum pressure at the junction");
		for(i=l;i<=NMOM;++i)
		{
			PMAX=-100000.0;
			PMIN=1000.0;
		
			for (j=1; j<=KN; ++j) 
			{//-------- KN
				if(W9[j]!=0)
				{
					if (W9[j]>PMAX)
					{
						JMAX = j;
						PMAX=W9[j];
					}
					if (W9[j]<PMIN)
					{
						JMIN= j;
						PMIN=W9[j];
					}
				}
			}//<<<<<<<<<<<<<<< KN
		
			II=JJI[JMAX];
			JD[I]=JMIN;
			W9[KN+I]=PMIN;
			QEXT=-B[JMAX] * CQ;
			
			printf("\n %d	%lf	%lf %lf %lf", II,QEXT,Y[JMAX] ,E[JMAX] ,PMAX);
			W9[JMAX]= 0.0;
			W9[JMIN]= 0.0;
		}
		printf("\n Minummum pressure for the junction");
		
		for(i=1;i<=NMOM;++i)
		{
			JMIN=JD [i] ;
			PMIN=W9[KN+i];
			QEXT=-B[JMIN] * CQ;
			II=JJI[JMIN];
			printf("\n %d %lf %lf %lf %lf", II,QEXT,Y[JMIN],E[JMIN],PMIN);
			printf("\n The net system demand QEXTT=%lf",QEXTT);
		}
	}
	printf("\n Summary of the inflow(+)and out flow(-)from fixed grad node");
	printf("\n pipe number flow rate");
	/* ------*/
	for (j =1; j <=KK; ++j) 
	{//-------------------- >>>>>KK
		JDIFF=JA[j] -JB[j];
		if((JA[j]+JB[j])<=abs(JDIFF))
		{
			if(KCLO[j]!=1)
			{
				if(W9[j]!=9999.0)
				{
					TT1=(JA[j]+JB[j])/(JA[j]-JB[j]);
					QEX=-Q[j] * TT1 * CQ;
					
					if(QEX>0.0)
					{
						QIN=QIN+QEX;
					}
					
					if(QEX<0.0)
					{
						QOUT=QOUT+QEX;
					}
				}
			}
		}
		L=KPI[j];
		
		printf("\n 	L=%d 	QEX=%lf ",L,QEX);
	}//-------------------------------------- > » » KK
	printf("\n The net flow into the system from fixed grad node QIN=%lf",QIN);
	printf("\n The net flow out of the system into fixed grad node QOUT=%lf",QOUT);
}
