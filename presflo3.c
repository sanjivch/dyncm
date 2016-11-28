/* = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
/* c o m p u t e r a n a l y s i s o f f l o w a n d p r e s s u r e i n p i p e n e t w o r k s */
/* FUNCTION T h r e e : */
/* GGGG[ ] -DEMAND OF THE JUNCTION */
/* EEEE[ ] -ELEVATION OF THE JUCNTION */
/* NUMJ[ ] - NUMBER OF JUNCTION */
/* J I J [] -ARRAY CONTAINE THE NUMBER OF JUNCTION */
/* MPL[ ] -ARRAY CONTINE THE NUMBER OF P IEP CONNECTED TO THE JUNCTI*/
/* NCK-NONZERO INTRY WILL INDICATED TO CHECKED PIPE CONNECTED J */
/* NSD NONZERO INTRY WOULDN'T SHOW DATA OF THE JUNCTION */
/* */
/* f i l e n ame ; m o h am e d i n -m o h am e d o u t */
/* */
/* ============================================================================*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAXSIZ 50
#define MAX_PIP 40
#define MAX_PUM 40
#define MAX_FIX 40
#define MAXPRV 40
#define MAX CPIP 3
FILE *fili,*filo,*fill;

void main()
{
	int NCK,NSD,KN,KK,NTEP;
	int NPOIIO],NUMJ[10];
	int JG[MAX_PIP],M[MAX_PIP],JA[MAX_PIP],JB[MAX_PIP];
	int MPL[MAX_SIZ] ,JX[MAX_SIZ] ,JIJ[MAX_SIZ] ,KIP[MAX_PIP] ,KPI[MAX PIP] ,JJI[MAX_PIP] ;
	int NEL,NOP,L ,J1,J2,MAXJ;
	int MBEG,KJ,LNUM,KP,NAB,NZX,NXX,NUJ,KTEP;
	int j,i,wl,l,k,tem,II;
	double E[MAX_PIP],BI[MAX_PIP],B[MAX_PIP];
	double GGGG[10] ,EEEE [10] ;
	double CQ;
	char fnaml[20],fnam2 [20];
	
	// = = = = ====================================^---------
	printf("Give file name for input\r\n");
	scanf ("%s11, fnaml) ;
	
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
	fscanf(fili,"%d %d %d %d %d %d %lf",NCK,NSD,KN,KK,NTEP,NEL,CQ);
	for(j =1;j <=KK;++j)
	{
	fscanf(fili,"%d %d %d %d",J A [j],J B [j],KPI[j],KIP[j]);
	
	for(j =1;j <=KN+1;+ +j){
	fscanf(fili,"%d",M[j]);
	}
	for(i=l;i<=KN;++i){
	fscanf(fili,"%d %d %d",NUMJ[i],JG[i],JX[i]);
	}
	for(j =1;j <=NEL;+ +j){
	fscanf(fili,"%dH,MPL[j]);
	>
	KTEP=NTEP-1;
	NEL=0;
	KJ=KN+1;
	KP=KK-KN;
	LNUM=KN;
	NZX=0;
	/ /M [KN+1 ] =NEL + 1 ;
	for (k=l; k<KJ; ++k){//-------------------------------- >>S
	printf ("\nDemand of the junction GGGG [%d] =11,k) ;
	scanf("%lf",&GGGG[k]);
	printf("\nElevation of the junction EEEE[%d]=",k);
	scanf("%lf",&EEEE[k]);
	printf (11 \nNumber of the junction NUMJ [%d] =" , k) ;
	scanf("%d",&NUMJ[k]);
	for(j=l;j<=MAX_CPIP;++j){ // p r i n t f ( " \ n JG[%d ] =",j ) ;
	scanf("%d",tJG[j]);
	}
	if(k==KJ){break;}
	tem=NUMJ[k];
	L=JIJ[tem] ¡ / /NUMBER OF JUNCTION
	if(L==0){ / /ME AN THERE I S NO JUNCTION NUMBER WRONG DATA HAS BEEN GIVEN
	fprintf(filo,"\nData is input for Jun nod NUMJ(%d)WHICHISNOT used INTHE PIPEDATA"
	,NUMJ,k);
	NXX=1;
	}
	B[L]=-GGGG[k]/CQ;
	BI[L]=B[L] ;
	E[L]=EEEE[k];
	if(NCKI=0) { / / n o t e q u a l e t o z e r o t h e me a n t h e d a t a f o r t e h s y s t e m m u s t b e c h e k c d
	NUJ=M[L+l]-M[L] ; / / NUJ THE NUMBER OF PIPE AROUND EACH JUNCTION
	fprintf(filo,"\n+++++++NUJ=%d",NUJ);
	for (i = l; i<=MAX_CPIP;++i) {//------->>i
	if(i<=NUJ){
	wl=M[L] ; / / L NUMBER OF JUNCTION
	NAB=MPL[wl+i-1] ; / /M P L ARRAY CONTAINE THE NUMBER OF PIPE CONN TH JUNCTI
	NAB=abs(NAB);
	NAB=KPI[NAB];
	fprintf(filo,"\n+++++++NAB=%d",NAB);
	}else{
	NAB=0;
	}
	if(abs(NAB)!=JG[i]){//
	fprintf(filo,"\nDATA IN PUT FOR PIPE CONNECTION JUNC(%d)DOES NOT CHECK",NUMJ
	}
	) ;
	NZX=1;
	}
	} // ----------------------<<<<<i
	} // <<<<<<
	}//---- .-------------------------- -----<<jc l o o p — S
	if(NCK !=0 && NZX==0){ // P I P E CONEECTED JUNCTION HAS BEEN CHECKED
	fprintf(filo,"\nSuccessfuly Geometric Verification Hase Been Compiteci");
	}
	if(NZX==1){ //E R ROR IN THE INPUT DATA
	NXX=1;
	fprintf(filo,"\n Error in the input data");
	exit(0);
	}
	if(NSD==0){ //W R I T E THE DATA FOR THE JUNCTION NODE
	fprintf(filo,"\n Junction No# Demand Elevation Conccection Pipe#");
	}
	for (1 = 1 ; 1<=KN;+ + 1 ) {//----------------------------- >>>>>>p
	NUMJ[1]=JJI[1];
	MAXJ=M[1+1]-1;
	MBEG=M[1];
	NOP=M[1 + 1]-M[1] ;
	fprintf(filo,"\n NOP=%d",NOP);
	for(Jl=l;J1<=N0P;++J1){
	J2=MPL[MBEG+J1-1];
	NPO[Jl]=abs(J2);
	}
	GGGG[1]=-B[1]*CQj//lFB[L]==0»»»GGGG=0;
	if(NSD<=0){//------------------------->>
	//printf("\nNUM[%d]=%dGGGG[%d]=%lf",1,NUMJ[1],GGGG[1]);//E[l];
	for(j=l;j<=NOP;++j){//----------->>
	J2=MPL[MBEG+j-1];
	NPO[j]=abs(J2);
	II=NPO [j] ;
	fprintf (filo, "\nJ2---------->>=%d" , J2) ;
	printf("\r\n");
	printf("\nKPI[%d]=%d",II,KPI[II]);
	}//------------------------- > » j
	} //---------------------------------- > » i f
	}
	fprintf (filo, "\nJ2=%d KTEP=%d NTEP=%d NEL=%d KJ=%d 11, J2 , KTEP, NTEP, NEL, K J ) ;
	fprintf(filo,"\nKP=%d LNUM=%d MAXJ=%d ",KP,LNUM,MAXJ);
	fprintf(filo,"\n NXX=%d",NXX);
	}
}
