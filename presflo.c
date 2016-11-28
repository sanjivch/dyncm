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
void pip_data(int np,int JC[],int JA[],int JB[],double l[],double D[],double C[],double ml[],double fgn[],int AAA[]);
void prv_input(int nprv,int LY[],int LZ[],double EMIN[],int MPL[]);
void pumpdata(int AAA[],double AA[],double BB[],double CC[],double EE[],double FF[],double DD[],double GG[],double A3,double CQ,int NPUMP,int NIPE);

void main(void)
{
	int nd,nj,np,fu,nprv,uu,ck;
	double sw;//DDQ
	int LY[kl],LZ[kl],JC[kl],KCLO[kl];
	double EMIN[kl];
	int JD[kl];
	int MPL[kl],KC[kl];
	int KIP[kl],KPI[kl],JX[kl];
	int j;

	double Q[kl],S[kl],V[kl];
	int NIPE,Jl,J2,JPIN,NXX,a,g;
	int NPUMP=0;
	int JA[kl],JB[kl];
	int JJUN[kl];
	double AA[kl],BB[kl],CC[kl],EE[kl],FF[kl];
	double A3,A4,Al,A2,CQ,P;
	int JPIP[kl],AAA[kl];
	double l[kl],D[kl],C[kl],ml[kl],fgn[kl];
	double DD[kl],GG[kl];
	int NTEP=0,	NXX=0,ck=0;
	char fnam2[20],fnaml[20];
	
	printf("Give:inputfilename\r\n");
	scanf("%s",fnaml);
	
	if((fili=fopen(fnaml,"w+"))==NULL)
	{
		printf("File%sdoesnotexist",fnaml);
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
	/*							ck:Checkpipeconnectionjunction					  */
	/*				fu:flowunite(0=CFS;1=GPM;2=MGD;3=SI(LITER/Sec)				  */
	/*							np.-numberofpipes								  */
	/*						nj:numberofjunction									  */
	/*						nprv:numberofPRV									  */
	/*				sw:specficGravity(0)waterwith3G=1.0							  */
	/*			uu:kinematicviscosity(!=0Darcy-Weisbach							  */
	/*																			  */
	/*============================================================================*/
	
	fscanf(fili,"%d%d%d%d%d%d%lf%d",&ck,&fu,&np,&nj,&nprv,find,&sw,tuu);
	
		for(j=l;j<=20;++j)
		{
			KPI[j]=0;
			KC[j]=0;
			KCLO[j]=0;
			JD[j]=0;
		}
		
		for(j=l;j<=20;++j)
		{
			MPL[j]=0;
			JX[j]=0;
			KIP[j]=0;
		}
		
		/*get pressure regrulator valve*/
		if(nprv!=0)
		{
			prv_input(nprv,LY,LZ,EMIN,MPL);
		}
		
		/*get pipe data*/
		pip_data(np,JC,JA,JB,l,D,C,ml,fgn,AAA);
		if(sw==0)
		{
			sw=1.0;
		}
		
		if(fu==0)
		{//------------------------------------------------------------------------------------------------------------------1
			fprintf(filo,"\nFlowRateIsExpressedInCfSAndPressureInPsig");
			Al=4.73;
			A2=0.02517;
			A3=8.18/sw;
			A4=12.0;
			CQ=1.0;
		}
		else if(fu==1)
		{
			fprintf(filo,"\nFlowRateIsExpessedIngpmAndPressureInpsig");
			Al=4.73;
			A2=0.02517;
			A3=8.18/sw;
			A4=12.0;
			CQ=448.86;
		}
		else if(fu==2)
		{
			fprintf(filo,"\nFlowRateIsExpressedInmgdAndPressureInpsig");
			Al=4.73;
			A2=0.02517;
			A3=8.18/sw;
			CQ=0.646358;
		}
		else
		{
			fprintf(filo,"\nFlowRateIsExpressedInLiter/SecAndPrssureIN(KN/M*M)U);
			Al=10.69;
			A2=0.08265;
			A3=0.10197/sw;
			A4=100.0;
			CQ=1000.0;
		}
		
		if(uu==0)
		{
			P=1.852;
		}
		else
		{
			P=2.0;
		//printf("\nTHEDARCY-WEISHHEADLOSSEQUATIONISUSEDUU=");
		}
		
		for(j=1;j<=np;++j)
		{
			NIPE=j;
			fprintf(filo,"\nNIPE=%d",j);
			
			KIP[NIPE]=j;
			fprintf(filo,"\nKIP[%d]=%d",NIPE,j);
			
			KPI[j]=NIPE;
			fprintf(filo,"\nKPI[%d]=%d",j,NIPE);
			
			J1=JA[j];
			fprintf(filo,"\nJl=%d",Jl);
			
			J2=JB[j];
			fprintf(filo,l,\nJ2=%d",Jl);
			
			if(MPL[NIPE]==101)
			{
				goto Ntep;
			}
			if((J1+J2)<=abs(J1-J2))
			{
			Ntep:
			;
			NTEP=NTEP+1;
			fprintf(filo,"\nNTEP=%d",NTEP);
			
			JD[j]=2;
			if(NTEP==1)
			{
				JPIN=j;
			}
				if(MPL[NTEP]==101)
				{
					JJUN[NTEP]=JB[j];
				}
				else
				{
					JJUN[NTEP]=JA[j]+JB[j];
				}
				JPIP[NTEP]=j;
				}
			if(AAA[j]!=0)
			{
				NPUMP=NPUMP+1;
				pumpdata(AAA,AA,BB,CC,EE,FF,DD,GG,A3,CQ,NPUMP,NIPE);
			}/*--------------------------------------------------------------------------------------------------------------------*/
			
			fprintf(filo,"\nnumberofpumpint hesystemNPUMP=%d",NPUMP);
			
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
					fprintf(filo,"\nThereIsaChekValveinLineNumber(%d)",NIPE);
				}
			}
			if(JC[j]==2)
			{
				KCLO[j]=1;
				if(nd==0)
				{
					printf("\nThelineNumber(%d)IsClosed",NIPE);
				}
			}
			
			D[j]=D[j]/A4;
			Q[j]=PI*pow(D[j],2.0);
			S[j]=Al*l[j3/pow(C[j],P)*pow(D[j],4.87);/*P=1.852*/
			V[j]=A2*ml[j]/(pow(D[j],4.0));
			
			fprintf(filo,"\n%d%d%lf%lf%lf%lf11,NXX,JPIN,D[j],Q[j],S[j],V[j]);
			
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
	/*MPL[]=101idicatedthatthispipecontainePRV*/
	/**/
	/**/
	/*============================================================================*/
	void prv_input(int nprv,int LY[],int LZ[],double EMIN[],int MPL[])
	{
		int j,Jl;
		
		for(j-1;j<=nprv;++j)
		{
			printf(11\nJUNCTIONNODEREPRESNETFIRSTPRVLY[%d]=%d",j,LY[j]);
			scanf("%d",&LY[j]);
			
			fprintf(fili,"\nPIPENUMBERDOWENSTREAMFROMFIRSTPRVLZ[%d]=",j);
			scanf("%d",&LZ[j]);
			
			printf("\nGRADEWHICHTHE(PRV)SETTOMAint AINEMIN[%d]=",j);
			scanf("%lf",fEMIN[j]);
			
			J1=LZ[j];
			MPL[Jl]=101;//MPL[]=101 there is PRV in the pipe
		}
	}
	
	
	/*=====---------======================================------==================*/
	/*Pipedata*/
	/*functiondata:*/
	/*np:numberofpipes*/
	/*JA-JB:Codenumberconnectingthepipe*/
	/*1:length*/
	/*D:diameter*/
	/*C-.HAZEN-WILLIAMSroughhness*/
	/*ml:minorelosses*/
	/*fgn:fixedgradenode*/
	/*AAA:PUMPchar */
	/*============================================================================*/
	void pip_data(int np,int JC[],int JA[],int JB[],double l[],double D[],double C[],double ml[],double fgn[],int AAA[])
	{
		int j;
		
		for(j=1;j<=np;++j)
		{
			scanf("%d",&JC[j]);
			fprintf(fili,"\n code2:indicate this pipe is closed code1: checkvalve JC[j]=%d",j,JC[j]);
			scanf("%d",&JA[j]);/*N1*/
			
			fprintf(fili,"\ncodenumberconnctingthispipeJA[%d]=%d",j,JA[j]);
			scanf("%d",&JB[j]);/*N2*/
			
			fprintf(fili,"\ncodenumberconnctingthispipeJB[%d]=%d",j,JB[j]);
			scanf("%lf",&1[j]);
			
			fprintf(fili,"\nlinelengthinfeetR[%d]=%lf",j,l[j]);
			scanf("%lf",&D[j]);
			
			fprintf(fili,"\ninsidediameterD[%d]=%lf11,j,D[j]);
			scanf("%lf",&C[j]);
			
			fprintf(fili,"\nHAZEN-WILLIAMESroughnessC[%d]=%lf",j,C[j]);
			scanf("%lf",&ml[j]);
			
			fprintf(fili,"\nsumofthemainorlossforthispipeWW[%d]=%lf",j,ml[j]);
			scanf("%d",&AAA[j]);
			
			fprintf(fili,"\npumpchar (+,-)(uesfulepower,opertaingdata)AAA[%d]=%d",j,AAA[j]);
			scanf("%lf",&fgn[j]);
			
			fprintf(fili,"\nfixedgradenodeENGY[%d]=%lf",j,fgn[j]);
		}
	}
	
	/*============================================================================*/
	/*PUMPDATA*/
	/**/
	/*AAA:inputforeverypipeint henetworks*/
	/*(0)thereisnopmupint hepipe*/
	/*(number(-,+)thereisapmupint hepipe*/
	/*npump=npump+l;*/
	/*if(jc[j]!=2)jc[j]=0*/
	/*kc[j]=npumpistoindiacteifthereispumpint helineornot=0Nopmup*/
	/*AA(NPUMP)=AAAUESFULPOWER*/
	/*BB(NPUMP)=0*/
	/*I=NPUMP*/
	/*--------------------------------------------------------------------------------------------------------------------*/
	/*(+)UESFULEPOWER*/
	/*(-)OPERATINGDATA(-1,-2)*/
	/*(-1)PAIRSOFHEAD-DISchar GEDATA*/
	/*(-2)USEFULPOWERBECOMPUTEDFROMTHEOPERTAINGDATA*/
	/*AA[I=NPMUP]=X1*Y1+X2*Y2+X3*Y3/A3*3*CQ*/
	/*x,y:(head,flowrate)*/
	/*============================================================================*/
	void pumpdata(int AAA[],double AA[],double BB[],double CC[],double EE[],double FF[],double DD[],double GG[],double A3,double CQ,int NPUMP,int NIPE)
	{
		double XI,Y1,X2,Y2,X3,Y3,S,D,T1;
		int j,I;
		int NXX=0;
		int KC[k1];
		
		for(j=1;j<2;++j)
		{
			KC[j]=NPUMP;
			AA[NPUMP]=double (AAA[j]);
			BB[NPUMP]=0;
			I=NPUMP;
				
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
					printf("\nPUMPDATAFORLINE(%d)ISNOTSIUTABLE",NIPE);
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
