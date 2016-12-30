/*============================================================================*/
/*			computer analysis of flow and pressure in pipe networks			  */
/* 																			  */
/*functiontwo:																  */
/*																			  */
/*numFixedGrNode-NUMBER OF FIXED GRADE NODE in the SYSTEM									  */
/*countJn-COUNTER TO CHECK THE NUMBER OF JUNCTION                                        */
/*numJunctions:NO of Junction in the System                                                  */
/*JA-JB:JUNCTIONCONNECTEDTHEPIPe                                              */
/*IP[][]-MATRIX FOR EACH JUNCTION IN THES YSTEM,									  */
/*EMIN[]-GRADE WHICH THE PRV SET												  */
/*LZ[]-PIPENUMBERDOWENSTREAMFROMTEHFIRSTPRV									  */
/*numPipeAroundEachJn-NUMBEROFPIPEAROUNDEACHJUNCTION										  */
/*numPipeAroundAllJn-NUMBEROFPIPEAROUNDALLTHEJUNCTIONint HESYSTEM							  */
/*KJ-numJunctions-1..NUMBEROFJUNCTION-1												  */
/*KP-numPipes-numJunctions...NUMBEROFPIPE-NUMBEROFJUNCTION									  */
/*LNUM-NUMBEROFJUNCTION														  */
/*numPipes-Nnumberofpipes														      */
/*																			  */

/*===========================================================================*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZ 50
#define MAX_PIP 40
#define MAX_PUM 40
#define MAX_FIX 40
#define MAX_PRV 40
#define MAX_CPIP 3

FILE *fili,*filo,*fill;

void main(void)
{
	int numJunctions,numPipes,NR,numFixedGrNode;
	int J99=30;
	int LZ[MAX_PRV],NUMJ[10];
	int IP[MAX_PIP][13],M[MAX_PIP],JA[MAX_PIP],JB[MAX_PIP];
	int arrPipeJn[MAX_SIZ],JX[MAX_SIZ],arrNumJn[MAX_SIZ],KIP[MAX_PIP],KPI[MAX_PIP],JJI[MAX_PIP];
	int countJn,numPipeAroundAllJn,numPipeAroundEachJn,J1,J2,MMM,JMAX;
	int KTEP;
	int ERR=0;
	int j,m,h,v,t,g,k,i;
	double ENGY[MAX_PIP],EMIN[MAX_SIZ];
	char fnaml[20],fnam2[20];
	
	/*============================================================================*/
	printf("Givefilenameforinput\r\n");
	scanf("%s",fnaml);
	
	if((fili=fopen(fnaml,"r+"))==NULL)
	{
		printf("Cannot open input f.%s",fnaml);
		exit(0);
	}
	
	printf("Give filename for output\r\n");
	scanf("%s",fnam2);
	
	if((filo=fopen(fnam2,"a+"))==NULL)
	{
		printf("Cannot open output f.%s",fnam2);
		exit(0);
		
		//======================================================
		fscanf(fili,"%d %d %d %d",numJunctions,numPipes,NR,numFixedGrNode);
		
		for(j=l;j<=numPipes;++j)
		{
			fscanf(fili,"%d %d %d %d %d",JA[j],JB[j],KPI[j],KIP[j],arrPipeJn[j]);
		}
		
		for(i=1;i<=numJunctions;++i)
		{
			fscanf(fili,"%d%d",NUMJ[i],JX[i]);
		}
		
		for(j=1;j<=50;++j)
		{
			M[j]=0;
		}
		
		KTEP=numFixedGrNode-1;
		countJn=0;
		numPipeAroundAllJn=0;
	}
	
	for(j=1;j<=99;++j)
	{
		//--------------------------->>j
		if(JX[j]!=0)
		{
			//ifJX[j]=0 means fixed grade node
			JMAX=j;
			countJn=countJn+1;
			fprintf(filo,"\nJJ=%d",countJn);
			JJI[countJn]=j;
			fprintf(filo,"\nJJX[%d]=%d",countJn,j);
			arrNumJn[j]=countJn;
			fprintf(filo,"\nJIJ[%d]=%d",j,countJn);
			printf("\n-----------matrix-------------------=");
			scanf("%d",&ERR);
		}
	}//-----------------------------------------------«j
	
	if(countJn!=numJunctions)
	{
		//countJn is COUNTER to CHECK the number of junction
		numJunctions=countJn;
	}
	
	for(j=1;j<=numPipes;++j)
	{
		countJn=KPI[j];
		fprintf(filo,"\nJJ=%d",KPI[j]);
		J1=0;
		J2=0;
		if(JA[j]!=0)
		{
			t=JA[j];
			Jl=Jl+JXJ[t];
			fprintf(filo,"\nJl=%d",arrNumJn[t]);
		}
		if(JB[j]!=0)
		{
			g=JB[j];
			J2=J2+arrNumJn[g]i
			fprintf(filo,"\nJ2=%d",JlJ[g]);
		}
		if(Jl!=0)
		{
			M[Jl]=M[Jl]+1;
			fprintf(filo,"\nM[%d]=%d",J1,M[Jl]);
			MMM=M[J1];
			fprintf(filo,"\nMMM=%d",MMM);
			IP[Jl][MMM]=j;
			fprintf(filo,11\nlP[%d][%d]=%d-,J1,MMM,j);
			printf("\n-------MATRIX[]----------=%d",ERR);
			scanf("%d",&ERR);
		}
		
		if(J2!=0)
		{
			M[J2]=M[J2]+1;
			fprintf(filo,"\n M[%d]=%d",J2,M[J2]);
			MMM=M[J2];
			fprintf(filo,"\n MMM=%d",MMM);
			IP[J2][MMM]=-j;
			fprintf(filo,"\n IP[%d][%d]=-%d",J2,MMM,j);
			printf("\n---------MATRIX[]----------=",ERR);
			scanf("%d",&ERR);
		}
		if(arrPipeJn[countJn]==101)
		{
			JA[j]=0;
		}
	}
	/**/
	if(NR!=0)
	{
		for(j=1;j<=NR;++j)
		{
			v=LZ[j];//LZ[j]=pipe number downstream from first prv
			countJn=KIP[v];
			ENGY[countJn]=EMIN[j];//the energy for this pipe is equal to grade with which prv is set
		}
	}
	
		for(j=1;j<=numJunctions;++j)
		{		//--------------------->>>>>>>>>>>>M
				numPipeAroundEachJn=M[j];//sum of the pipe around each junction
				fprintf(filo,"\nNOP=%d",numPipeAroundEachJn);
				if(numPipeAroundEachJn!=0)
				{
					for(k=1;k<=numPipeAroundEachJn;++k)
					{
						numPipeAroundAllJn=numPipeAroundAllJn+1;//the sum of all the pipe in all junction in the system
						fprintf(filo,"\nNEL=%d",numPipeAroundAllJn);
						arrPipeJn[numPipeAroundAllJn]=IP[j][k];//setting the matrix
						fprintf(filo,"\nMPL[%d]=IP[%d][%d]",numPipeAroundAllJn,j,k);
					}
				M[j]=numPipeAroundAllJn-numPipeAroundEachJn+1;
				fprintf(filo,"\nM[%d]=%d-%d+l",j,numPipeAroundAllJn,numPipeAroundEachJn);
				printf("\n---------matrix----------=%d",ERR);
				scanf("%d",&ERR);
				}
		}
		
		M[numJunctions+1]=numPipeAroundAllJn+1;
		
	for(j=1;j<=numPipes;++j)
	{
		if(JA[j]!=0)
		{
			m=JA[j];
			JA[j]=arrNumJn[m];
		}
		if(JB[j]!=0)
		{
			h=JB[j];
			JB[j]=arrNumJn[h];
		}
	}
	fprintf(filo,"\nKTEP=%dJMAX=%d",KTEP,JMAX);
}
