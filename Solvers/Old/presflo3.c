/* demandJn[] -DEMAND OF THE JUNCTION */
/* elevationJn[] -ELEVATION OF THE JUNCTION */
/* NUMJ[] - NUMBER OF JUNCTION */
/* arrNumJn[] -ARRAY CONTAINE THE NUMBER OF JUNCTION */
/* arrPipeJn[] -ARRAY CONTINE THE NUMBER OF PIPE CONNECTED TO THE JUNCTI*/
/* checkData-NONZERO INTRY WILL INDICATED TO CHECKED PIPE CONNECTED J */
/* showData NONZERO INTRY WOULDN'T SHOW DATA OF THE JUNCTION */
/* */
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

void main()
{
	int checkData,showData,numJunctions,numPipes,numFixedGrNode;
	int NPO[1O],NUMJ[10];
	int JG[MAX_PIP],M[MAX_PIP],JA[MAX_PIP],JB[MAX_PIP];
	int arrPipeJn[MAX_SIZ] ,JX[MAX_SIZ] ,arrNumJn[MAX_SIZ] ,KIP[MAX_PIP] ,KPI[MAX_PIP] ,JJI[MAX_PIP] ;
	int numPipeAroundAllJn,numPipeAroundEachJn,junctionNo,J1,J2,MAXJ;
	int MBEG,KJ,LNUM,KP,NAB,errorInputData,NXX,NUJ,KTEP;
	int j,i,wl,l,k,tem,II;
	double E[MAX_PIP],BI[MAX_PIP],B[MAX_PIP];
	double demandJn[10] ,elevationJn [10] ;
	double CQ;
	char fnaml[20],fnam2 [20];
	
	//========================================
	printf("Give file name for input\r\n");
	scanf ("%s11, fnaml);
	
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
	/* ============================================*/
	fscanf(fili,"%d %d %d %d %d %d %lf",checkData,showData,numJunctions,numPipes,numFixedGrNode,numPipeAroundAllJn,CQ);
	for(j =1;j <=numPipes;++j)
	{
		fscanf(fili,"%d %d %d %d",JA[j],JB[j],KPI[j],KIP[j]);
		
		for(j =1;j <=numJunctions+1;++j)
		{
		fscanf(fili,"%d",M[j]);
		}
		
		for(i=1;i<=numJunctions;++i)
		{
		fscanf(fili,"%d %d %d",NUMJ[i],JG[i],JX[i]);
		}
		
		for(j =1;j <=numPipeAroundAllJn;++j)
		{
		fscanf(fili,"%d",arrPipeJn[j]);
		}
		
		KTEP=numFixedGrNode-1;
		numPipeAroundAllJn=0;
		KJ=numJunctions+1;
		KP=numPipes-numJunctions;
		LNUM=numJunctions;
		errorInputData=0;
		
		//M [numJunctions+1] =numPipeAroundAllJn + 1 ;
		
		
		for (k=1; k<KJ; ++k)
		{//-------------------------------- >>S
			printf ("\nDemand of the junction demandJn [%d] =",k);
			scanf("%lf",&demandJn[k]);
			printf("\nElevation of the junction elevationJn[%d]=",k);
			scanf("%lf",&elevationJn[k]);
			printf ("\nNumber of the junction NUMJ [%d] =", k);
			scanf("%d",&NUMJ[k]);
			
			for(j=1;j<=MAX_CPIP;++j)
			{ // printf ( " \ n JG[%d ] =",j ) ;
				scanf("%d",&JG[j]);
			}
			
			if(k==KJ)
			{
				break;
			}
			
			tem=NUMJ[k];
			junctionNo=arrNumJn[tem]; //NUMBER OF JUNCTION
			
			if(junctionNo==0)
			{ //MEANS THERE IS NO JUNCTION NUMBER WRONG DATA HAS BEEN GIVEN
			fprintf(filo,"\nData is input for Jun nod NUMJ(%d)WHICH IS NOT used IN THE PIPEDATA",NUMJ,k);
			NXX=1;
			}
			
			B[junctionNo]=-demandJn[k]/CQ;
			BI[junctionNo]=B[junctionNo] ;
			E[junctionNo]=elevationJn[k];
			
			if(checkData!=0) 
			{ 
				// not equal to zero this means the data for the system must be checked
				NUJ=M[junctionNo+l]-M[junctionNo] ; // NUJ THE NUMBER OF PIPE AROUND EACH JUNCTION
				fprintf(filo,"\n+++++++NUJ=%d",NUJ);
				
				for (i=1;i<=MAX_CPIP;++i) 
				{//------->>i
					if(i<=NUJ)
					{
						w1=M[junctionNo] ; // junctionNo NUMBER OF JUNCTION
						NAB=arrPipeJn[w1+i-1] ; //arrPipeJn ARRAY CONTAINING THE NUMBER OF PIPE CONNECTING THE JUNCTION
						NAB=abs(NAB);
						NAB=KPI[NAB];
						fprintf(filo,"\n+++++++NAB=%d",NAB);
					}
					else
					{
						NAB=0;
					}
					
					if(abs(NAB)!=JG[i])
					{//
						fprintf(filo,"\nDATA IN PUT FOR PIPE CONNECTION JUNC(%d)DOES NOT CHECK",NUMJ) ;
					}
					
					errorInputData=1;
				}
			} // ----------------------<<<<<i
		} // <<<<<<
	}
	//-----------------------------------<<k loop  S
	if(checkData !=0 && errorInputData==0)
	{ //PIPE CONEECTED JUNCTION HAS BEEN CHECKED
		fprintf(filo,"\nSuccessfuly Geometric Verification Hase Been Compiteci");
	}
	
	if(errorInputData==1)
	{ //ERROR IN THE INPUT DATA
		NXX=1;
		fprintf(filo,"\n Error in the input data");
		exit(0);
	}
	
	if(showData==0)
	{ //WRITE THE DATA FOR THE JUNCTION NODE
		fprintf(filo,"\n Junction No# Demand Elevation Conccection Pipe#");
	}
	
	for(l=1; l<=numJunctions; ++l) 
	{//----------------------------- >>>>>>p
		NUMJ[l]=JJI[l];
		MAXJ=M[l+1]-1;
		MBEG=M[l];
		numPipeAroundEachJn=M[l+1]-M[l] ;
		fprintf(filo,"\n numPipeAroundEachJn=%d",numPipeAroundEachJn);
		
		for(Jl=1;J1<=N0P;++J1)
		{
			J2=arrPipeJn[MBEG+J1-1];
			NPO[Jl]=abs(J2);
		}
		
		demandJn[l]=-B[l]*CQ;//lF B[junctionNo]==0 demandJn=0;
		
		if(showData<=0)
		{//------------------------->>
			//printf("\nNUM[%d]=%dGGGG[%d]=%lf",1,NUMJ[1],demandJn[1]);//E[l];
			for(j=1;j<=numPipeAroundEachJn;++j)
			{//----------->>
				J2=arrPipeJn[MBEG+j-1];
				NPO[j]=abs(J2);
				II=NPO [j] ;
				fprintf (filo, "\nJ2---------->>=%d" , J2) ;
				printf("\r\n");
				printf("\nKPI[%d]=%d",II,KPI[II]);
			}//------------------------- > » j
		} //---------------------------------- > » if
	}
	fprintf (filo, "\nJ2=%d KTEP=%d numFixedGrNode=%d numPipeAroundAllJn=%d KJ=%d ", J2 , KTEP, numFixedGrNode, numPipeAroundAllJn, KJ ) ;
	fprintf(filo,"\nKP=%d LNUM=%d MAXJ=%d ",KP,LNUM,MAXJ);
	fprintf(filo,"\n NXX=%d",NXX);
}
}
