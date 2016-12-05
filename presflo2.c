/*============================================================================*/
/*			computer analysis of flow and pressure in pipe networks			  */
/* 																			  */
/*functiontwo:																  */
/*																			  */
/*numFixedGrNode-NUMBEROFFIXEDGRADENODEintESYSTEM									  */
/*JJ-COUNTERTOCHECKTHENUMBEROFJUNCTION                                        */
/*KN:NOFJunctionintheSystem                                                  */
/*JA-JB:JUNCTIONCONNECTEDTHEPIPe                                              */
/*IP[][]-MATRIXFOREACHJUNCTIONint HESYSTEM,									  */
/*EMIN[]-GRADEWHICHTHEPRVSET												  */
/*LZ[]-PIPENUMBERDOWENSTREAMFROMTEHFIRSTPRV									  */
/*NOP-NUMBEROFPIPEAROUNDEACHJUNCTION										  */
/*NEL-NUMBEROFPIPEAROUNDALLTHEJUNCTIONint HESYSTEM							  */
/*KJ-KN-1..NUMBEROFJUNCTION-1												  */
/*KP-KK-KN...NUMBEROFPIPE-NUMBEROFJUNCTION									  */
/*LNUM-NUMBEROFJUNCTION														  */
/*KK-Nnumberofpipes														      */
/*																			  */
/*fileNmaemonain.monao														  */
/*===========================================================================*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZ 50
#define MAXPIP 40
#define MAX_PUM 40
#define MAX_FIX 40
#define MAX_PRV 40
#define MAX_CPIP 3

FILE *fili,*filo,*fill;

void main(void)
{
	int KN,KK,NR,numFixedGrNode;
	int J99=30;
	int LZ[MAXPRV],NUMJ[10];
	int IP[MAX_PIP][13],M[MAX_PIP],JA[MAX_PIP],JB[MAX_PIP];
	int MPL[MAX_SIZ],JX[MAX_SIZ],JIJ[MAX_SIZ],KIP[MAX_PIP],KPI[MAXPIP],JJI[MAX_PIP];
	int JJ,NEL,NOP,J1,J2,MMM,JMAX;
	int KTEP;
	int ERR=0;
	int j,m,h,v,t,g,k,i;
	double ENGY[MAX_PIP],EMIN[MAXSIZ];
	char fnaml[20],fnam2[20];
	
	/*============================================================================*/
	printf("\Givefilenameforinput\r\n");
	scanf("%s",fnaml);
	
	if((fili=fopen(fnaml,"r+"))==NULL)
	{
		printf("Cannotopeninputf.%s",fnaml);
		exit(0);
	}
	
	printf("Givefilenameforoutput\r\n");
	scanf("%s",fnam2);
	
	if((filo=fopen(fnam2,"a+"))==NULL)
	{
		printf("Cannotopenoutputf.%s",fnam2);
		exit(0);
		
		//======================================================
		fscanf(fili,"%d%d%d%d",KN,KK,NR,numFixedGrNode);
		
		for(j=l;j<=KK;++j)
		{
			fscanf(fili,"%d%d%d%d%d",JA[j],JB[j],KPI[j],KIP[j],MPL[j]);
		}
		
		for(i=l;i<=KN;++i)
		{
			fscanf(fili,"%d%d",NUMJ[i],JX[i]);
		}
		
		for(j=1;j<=50;++j)
		{
			M[j]=0;
		}
		
		KTEP=numFixedGrNode-1;
		JJ=0;
		NEL=0;
	}
	
	for(j=1;j<=99;++j)
	{
		//--------------------------->>j
		if(JX[j]!=0)
		{
			//ifJX[j]=0 means fiexd grade node
			JMAX=j;
			JJ=JJ+1;
			fprintf(filo,"\nJJ=%d",JJ);
			JJI[JJJ=j;
			fprintf(filo,"\nJJX[%d]=%d",JJ,j);
			JIJ[j]=JJ;
			fprintf(filo,"\nJIJ[%d]=%d",j,JJ);
			printf("\n-----------marix-------------------=");
			scanf("%d",&ERR);
		}
	}//-----------------------------------------------«j
	
	if(JJ!=KN)
	{
		//JJisCOUNTERtoCHECKthenumberofjunction
		KN=JJ;
	}
	
	for(j=1;j<=KK;++j)
	{
		JJ=KPI[j];
		fprintf(filo,"\nJJ=%d",KPI[j]);
		J1=0;
		J2=0;
		if(JA[j]!=0)
		{
			t=JA[j];
			Jl=Jl+JXJ[t];
			fprintf(filo,"\nJl=%d",JIJ[t]);
		}
		if(JB[j]!=0)
		{
			g=JB[j];
			J2=J2+JIJ[g]i
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
			fprintf(filo,"\nM[%d]=%d",J2,M[J2]);
			MMM=M[J2];
			fprintf(filo,,l\nMMM=%d",MMM);
			IP[J2][MMM]=-j;
			fprintf(filo,"\nIP[%d][%d]=-%d",J2,MMM,j);
			printf("\n---------MATRIX[]----------=",ERR);
			scanf("%d",&ERR);
		}
		if(MPL[JJ]==101)
		{
			JA[j]=0;
		}
	}
	/**/
	if(NR!=0)
	{
		for(j=1;j<=NR;++j)
		{
			v=LZ[j];//LZ[j]=pipenumberdowenstreamfromfirstprv
			JJ=KIP[v];
			ENGY[JJ]=EMIN[j];//theenrgyforthispipeisequaltogradewhichprvset
		}
	}
	
		for(j=1;j<=KN;++j)
		{		//--------------------->>>>>>>>>>>>M
				NOP=M[j];//sumofthepipearoundeachjunction
				fprintf(filo,"\nNOP=%d",NOP);
				if(NOP!=0)
				{
					for(k=l;k<=NOP;++k)
					{
						NEL=NEL+1;//thesumofallthepipeinalljunctionint hesystem
						fprintf(filo,"\nNEL=%d",NEL);
						MPL[NEL]=IP[j][k];//settingthematrix
						fprintf(filo,"\nMPL[%d]=IP[%d][%d]",NEL,j,k);
					}
				M[j]=NEL-N0P+1;
				fprintf(filo,"\nM[%d]=%d-%d+l",j,NEL,NOP);
				printf("\n---------matrix----------=%d",ERR);
				scanf("%d",&ERR);
				}
		}
		
		M[KN+1]=NEL+1;
		
	for(j=1;j<=KK;++j)
	{
		if(JA[j]!=0)
		{
			m=JA[j];
			JA[j]=JIJ[m];
		}
		if(JB[j]1=0)
		{
			h=JB[j];
			JB[j]=JIJ[h];
		}
	}
	fprintf(filo,"\nKTEP=%dJMAX=%d",KTEP,JMAX);
}
