/*			ANALYSIS OF FLOW AND PRESSURE IN PIPE NETWORKS					*/
/*																			*/
/*						function one:										*/
/*																			*/
/*						Read an option data									*/
/*						Read pipe data										*/
/*						Read PRV data										*/
/*						Read pump data										*/
/*							Filename:										*/
/*						a:tesetin,a:tesetout								*/
/*==========================================================================*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>

#define PI 3.141592654

FILE *fili,*filo,*fill;

const kl=10;
void pip_data(int numPipes,int JC[],int JA[],int JB[],double lenPipe[],double dia[],double C[],double minorLoss[],double fixedGrNode[],int AAA[]);
void prv_input(int numPRV,int LY[],int LZ[],double EMIN[],int arrPipeJn[]);
void pumpdata(int AAA[],double AA[],double BB[],double CC[],double EE[],double FF[],double DD[],double GG[],double A3,double CQ,int numPumps,int pipeUniNum);

void main(void)
{
	int nd,numJunctions,numPipes,flowUnit,numPRV,kinViscosity,checkPipeConnection;
	double spGravity;//DDQ
	int LY[kl],LZ[kl],JC[kl],pipeStatus[kl];
	double EMIN[kl];
	int JD[kl];
	int arrPipeJn[kl],KC[kl];
	int KIP[kl],KPI[kl],JX[kl];
	int j;

	double Q[kl],S[kl],V[kl];
	int pipeUniNum,J1,J2,JPIN,NXX,a,g;
	int numPumps=0;
	int JA[kl],JB[kl];
	int JJUN[kl];
	double AA[kl],BB[kl],CC[kl],EE[kl],FF[kl];
	double A3,A4,Al,A2,CQ,P;
	int JPIP[kl],AAA[kl];
	double lenPipe[kl],dia[kl],C[kl],minorLoss[kl],fixedGrNode[kl];
	double DD[kl],GG[kl];
	int numFixedGrNode=0,	NXX=0,checkPipeConnection=0;
	char fnam2[20],fnam1[20];
	
	printf("Give:inputfilename\r\n");
	scanf("%s",fnam1);
	
	if((fili=fopen(fnam1,"w+"))==NULL)
	{
		printf("File%sdoesnotexist",fnam1);
		exit(0);
	}
	printf("Givefilenameforoutput\r\n");
	scanf("%s",fnam2);
	
	if((filo=fopen(fnam2,"w+"))==NULL)
	{
		printf("Cannotopenoutputf.%s",fnam2);
		exit(0);
	}

	/*============================================================================*/
	/*								variableoption:								  */
	/*																			  */
	/*							checkPipeConnection:Checkpipeconnectionjunction					  */
	/*				flowUnit:flowunite(0=CFS;1=GPM;2=MGD;3=SI(LITER/Sec)				  */
	/*							numPipes.-numberofpipes								  */
	/*						numJunctions:numberofjunction									  */
	/*						numPRV:numberofPRV									  */
	/*				spGravity:specficGravity(0)waterwith3G=1.0							  */
	/*			kinViscosity:kinematicviscosity(!=0Darcy-Weisbach							  */
	/*																			  */
	/*============================================================================*/
	
	fscanf(fili,"%d%d%d%d%d%d%lf%d",&checkPipeConnection,&flowUnit,&numPipes,&numJunctions,&numPRV,&nd,&spGravity,&kinViscosity);
	
		for(j=1;j<=20;++j)
		{
			KPI[j]=0;
			KC[j]=0;
			pipeStatus[j]=0;
			JD[j]=0;
		}
		
		for(j=1;j<=20;++j)
		{
			arrPipeJn[j]=0;
			JX[j]=0;
			KIP[j]=0;
		}
		
		/*get pressure regrulator valve*/
		if(numPRV!=0)
		{
			prv_input(numPRV,LY,LZ,EMIN,arrPipeJn);
		}
		
		/*get pipe data*/
		pip_data(numPipes,JC,JA,JB,lenPipe,dia,C,minorLoss,fixedGrNode,AAA);
		if(spGravity==0)
		{
			spGravity=1.0;
		}
		
		if(flowUnit==0)
		{//------------------------------------------------------------------------------------------------------------------1
			fprintf(filo,"\nFlowRateIsExpressedInCfSAndPressureInPsig");
			Al=4.73;
			A2=0.02517;
			A3=8.18/spGravity;
			A4=12.0;
			CQ=1.0;
		}
		else if(flowUnit==1)
		{
			fprintf(filo,"\nFlowRateIsExpessedIngpmAndPressureInpsig");
			Al=4.73;
			A2=0.02517;
			A3=8.18/spGravity;
			A4=12.0;
			CQ=448.86;
		}
		else if(flowUnit==2)
		{
			fprintf(filo,"\nFlowRateIsExpressedInmgdAndPressureInpsig");
			Al=4.73;
			A2=0.02517;
			A3=8.18/spGravity;
			CQ=0.646358;
		}
		else
		{
			fprintf(filo,"\nFlow Rate Is Expressed In Liter/Sec And Prssure IN(KN/M*M)");
			Al=10.69;
			A2=0.08265;
			A3=0.10197/spGravity;
			A4=100.0;
			CQ=1000.0;
		}
		
		if(kinViscosity==0)
		{
			P=1.852;
		}
		else
		{
			P=2.0;
		//printf("\nTHEDARCY-WEISHHEADLOSSEQUATIONISUSEDUU=");
		}
		
		for(j=1;j<=numPipes;++j)
		{
			pipeUniNum=j;
			fprintf(filo,"\nNIPE=%d",j);
			
			KIP[pipeUniNum]=j;
			fprintf(filo,"\nKIP[%d]=%d",pipeUniNum,j);
			
			KPI[j]=pipeUniNum;
			fprintf(filo,"\nKPI[%d]=%d",j,pipeUniNum);
			
			J1=JA[j];
			fprintf(filo,"\nJ1=%d",J1);
			
			J2=JB[j];
			fprintf(filo,l,\nJ2=%d",J1);
			
			if(arrPipeJn[pipeUniNum]==101)
			{
				goto Ntep;
			}
			if((J1+J2)<=abs(J1-J2))
			{
			Ntep:
			;
			numFixedGrNode=numFixedGrNode+1;
			fprintf(filo,"\nNTEP=%d",numFixedGrNode);
			
			JD[j]=2;
			if(numFixedGrNode==1)
			{
				JPIN=j;
			}
				if(arrPipeJn[numFixedGrNode]==101)
				{
					JJUN[numFixedGrNode]=JB[j];
				}
				else
				{
					JJUN[numFixedGrNode]=JA[j]+JB[j];
				}
				JPIP[numFixedGrNode]=j;
				}
			if(AAA[j]!=0)
			{
				numPumps=numPumps+1;
				pumpdata(AAA,AA,BB,CC,EE,FF,DD,GG,A3,CQ,numPumps,pipeUniNum);
			}/*--------------------------------------------------------------------------------------------------------------------*/
			
			fprintf(filo,"\nnumberofpumpint hesystemNPUMP=%d",numPumps);
			
			if(JA[j]!=0)
			{
				a=JA[j];
				JX[a]=JA[j];
			}
			
			if(JB[j]!=0)
			{
				q=JB[j];
				JX[q]=JB[j];
			}
			/*--------------------------------------------------------------------------------------------------------------------*/
			if(JC[j]==l)
			{
				if(nd==0&&KC[j]==0)
				{
					fprintf(filo,"\nThereIsaChekValveinLineNumber(%d)",pipeUniNum);
				}
			}
			if(JC[j]==2)
			{
				pipeStatus[j]=1;
				if(nd==0)
				{
					printf("\nThelineNumber(%d)IsClosed",pipeUniNum);
				}
			}
			
			dia[j]=dia[j]/A4;
			Q[j]=PI*pow(dia[j],2.0);
			S[j]=Al*l[j3/pow(C[j],P)*pow(dia[j],4.87);/*P=1.852*/
			V[j]=A2*minorLoss[j]/(pow(dia[j],4.0));
			
			fprintf(filo,"\n%d%d%lf%lf%lf%lf11,NXX,JPIN,dia[j],Q[j],S[j],V[j]);
			
		}/*----------------------------------------<<<<<<<<<landofthejloop*/
}
}
	/*============================================================================*/
	/*						PRVDATA												*/
	/*																			*/
	/*						functiondata										*/
	/**/
	/*readLY[],LZ[],EMIN[]*/
	/*LY[]:JUNCTIONNODEREPRESENTFIRSTPRV,*/
	/*LZ[]:PIPENUMBERDOWNSTREAMFROMFIRSTPRV,*/
	/*LY[]:GRADEWHICHTHEPRVSETTOMAint AIN,*/
	/*arrPipeJn[]=101idicatedthatthispipecontainePRV*/
	/**/
	/**/
	/*============================================================================*/
	void prv_input(int numPRV,int LY[],int LZ[],double EMIN[],int arrPipeJn[])
	{
		int j,J1;
		
		for(j=1;j<=numPRV;++j)
		{
			printf("\nJUNCTIONNODEREPRESNETFIRSTPRVLY[%d]=%d",j,LY[j]);
			scanf("%d",&LY[j]);
			
			fprintf(fili,"\nPIPENUMBERDOWENSTREAMFROMFIRSTPRVLZ[%d]=",j);
			scanf("%d",&LZ[j]);
			
			printf("\nGRADEWHICHTHE(PRV)SETTOMAint AINEMIN[%d]=",j);
			scanf("%lf",fEMIN[j]);
			
			J1=LZ[j];
			arrPipeJn[J1]=101;//arrPipeJn[]=101 there is PRV in the pipe
		}
	}
	
	
	/*=====---------======================================------==================*/
	/*Pipedata*/
	/*functiondata:*/
	/*numPipes:numberofpipes*/
	/*JA-JB:Codenumberconnectingthepipe*/
	/*1:length*/
	/*D:diameter*/
	/*C-.HAZEN-WILLIAMSroughhness*/
	/*minorLoss:minorelosses*/
	/*fixedGrNode:fixedgradenode*/
	/*AAA:PUMPchar */
	/*============================================================================*/
	void pip_data(int numPipes,int JC[],int JA[],int JB[],double lenPipe[],double dia[],double C[],double minorLoss[],double fixedGrNode[],int AAA[])
	{
		int j;
		
		for(j=1;j<=numPipes;++j)
		{
			scanf("%d",&JC[j]);
			fprintf(fili,"\n code2:indicate this pipe is closed code1: checkvalve JC[j]=%d",j,JC[j]);
			scanf("%d",&JA[j]);/*N1*/
			
			fprintf(fili,"\ncodenumberconnctingthispipeJA[%d]=%d",j,JA[j]);
			scanf("%d",&JB[j]);/*N2*/
			
			fprintf(fili,"\ncodenumberconnctingthispipeJB[%d]=%d",j,JB[j]);
			scanf("%lf",&1[j]);
			
			fprintf(fili,"\nlinelengthinfeetR[%d]=%lf",j,l[j]);
			scanf("%lf",&dia[j]);
			
			fprintf(fili,"\ninsidediameterD[%d]=%lf11,j,dia[j]);
			scanf("%lf",&C[j]);
			
			fprintf(fili,"\nHAZEN-WILLIAMESroughnessC[%d]=%lf",j,C[j]);
			scanf("%lf",&minorLoss[j]);
			
			fprintf(fili,"\nsumofthemainorlossforthispipeWW[%d]=%lf",j,minorLoss[j]);
			scanf("%d",&AAA[j]);
			
			fprintf(fili,"\npumpchar (+,-)(uesfulepower,opertaingdata)AAA[%d]=%d",j,AAA[j]);
			scanf("%lf",&fixedGrNode[j]);
			
			fprintf(fili,"\nfixedgradenodeENGY[%d]=%lf",j,fixedGrNode[j]);
		}
	}
	
	/*============================================================================*/
	/*PUMPDATA*/
	/**/
	/*AAA:inputforeverypipeint henetworks*/
	/*(0)thereisnopmupint hepipe*/
	/*(number(-,+)thereisapmupint hepipe*/
	/*numPumps=numPumps+l;*/
	/*if(jc[j]!=2)jc[j]=0*/
	/*kc[j]=npumpistoindiacteifthereispumpint helineornot=0Nopmup*/
	/*AA(numPumps)=AAAUESFULPOWER*/
	/*BB(numPumps)=0*/
	/*I=numPumps*/
	/*--------------------------------------------------------------------------------------------------------------------*/
	/*(+)UESFULEPOWER*/
	/*(-)OPERATINGDATA(-1,-2)*/
	/*(-1)PAIRSOFHEAD-DISchar GEDATA*/
	/*(-2)USEFULPOWERBECOMPUTEDFROMTHEOPERTAINGDATA*/
	/*AA[I=NPMUP]=X1*Y1+X2*Y2+X3*Y3/A3*3*CQ*/
	/*x,y:(head,flowrate)*/
	/*============================================================================*/
	void pumpdata(int AAA[],double AA[],double BB[],double CC[],double EE[],double FF[],double DD[],double GG[],double A3,double CQ,int numPumps,int pipeUniNum)
	{
		double XI,Y1,X2,Y2,X3,Y3,S,D,T1;
		int j,I;
		int NXX=0;
		int KC[k1];
		
		for(j=1;j<2;++j)
		{
			KC[j]=numPumps;
			AA[numPumps]=double (AAA[j]);
			BB[numPumps]=0;
			I=numPumps;
				
			if(AAA[j]<0)
			{
				//------------
				printf("\nxl=");//h
				scanf("%lf",&X1);
				printf("\nyl=");//f
				scanf("%lf",&Y1);
				printf("\nx2=");
				scanf("%lf",&X2);
				printf("\ny2=");
				scanf("%lf",&Y2);
				printf("\nX3=");
				scanf("%lf",&X3);
				printf("\ny3=");
				scanf("%lf",&Y3);
				
				if(X1<X2||X2<X3)
				{
					printf("\nPUMPDATAFORLINE(%d)ISNOTSIUTABLE",pipeUniNum);
					NXX=1;
				}
				
				AA[I]=(XI*Yl+X2*Y2+X3*Y3)/(A3*3.0*CQ);
			
				if(AAA[j]>-2)
				{
					AA[I]=Y1/CQ;
					S=log(X1-X3)/(X1-X2);
					D=log(Y3/Y2);
					BB[I]=S/D;
					Tl=pow((Y2/CQ),BB[I]);
					CC[I]=(X1-X2)/Tl;
					EE[I]=-BB[I]*CC[I]*pow((Y3/CQ),(BB[I]-1.0);
					FF[I]=X3-EE[I]*Y3/CQ;
					DD[I]=X1;
					GG[I]=Y3/CQ;
					
					fprintf(filo,"\n%lf%lf%lf%lf%lf%lf%lf",AA[I],BB[I],CC[I],EE[I],FF[I],DD[I],GG[I]);
				}
			}//AAA
		}
		printf("\nNXX=%d",NXX);
	}
