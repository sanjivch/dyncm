/*============================================================================*/
COMPUTER ANALYSIS OF FLOW IN PIPE NETWORKS
/*
/*
FUNCTION
7:
/*
*/
*/
*/
NQ=1 FLOW UNIT IN GPM
SUPPRESS IN PUT DATA SUMMARY, IF
IT NOT EQUAL TO ZERO
/*
/*NSD=0
*/
*/
/*
*/
/ * ============================================================================* /
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define M A X S I Z
20
FILE * fili,* filo;
void main(void)
{
int JA[MAX_SIZ] ,JB[MAX_SIZ] , JIJ [MAX_SIZ] , JJTJN [MAXJ3IZ] ,MPL[30] , JD[MAX_SIZ] ;
int M[MAX_SIZ] ,NEX[MAX_SIZ] ,NIX[MAX SIZ] ,JPIP[MAX SIZ] ,JJI[MAX SIZ] ,NJO[MAX SIZ] ;
int KCLO[MAX_SIZ],KPI[MAXSIZ];
double E[MAX_SIZ] ,B[MAX_SIZ] ,W9 [MAX SIZ] ,Y[MAX_SIZ] ,YY[MAX_SIZ] ,ENGY[MAX SIZ] ;
double Q[MAX_SIZ];
int K K ,KN,K J ,NEL,IPRINT,N X X ,NEXT,NTEP,N I ,N 2 ,N 3 ,MBEG,MJJ,m ,JMAX,JMIN,11;
double CQ,QEXTT,QEXT,PRES,SW,PMAX,PMIN,QEX,QIN,QOUT;
int i , j , k, 1, J 8 ,J9,J,I,IOUT,NJOUT,NQ,NMOM,JDIFF,L,TT1;
char fnaml[21],fnam2[21];
/*============================================================================*/
printf("Give file name for input\r\n");
scanf("%s",fnaml);
i f ((fili=fopen(fnaml,Mr+"))==NULL){
printf("Cannot open input f. %s",fnaml);
exit(0);
}
printf("Give file name for output\r\n");
scanf("%s",fnam2);
i f ((filo=fopen(fnam2,"a+"))==NULL){
printf("Cannot open output f. %s",fnam2);
exit(0);
}
/*============================================================================*/
fscanf(fili,"%d %d %d %d %d %d %d %d %d",KK,KN,KJ,NEL,NTEP,IOUT,NJOUT,NQ,NMOM) ;
fscanf(fili, "%lf %lf",CQ,SW);
for(j =1;j <=KK+1;++j ) {
fscanf(fili,"%d",M [j]);
>
f o r (j =1;j <=NEL;+ +j ) {
fscanf(fili,"%dM,MPL[j] ) ;
}
for(j = l;j<=KK;+ + j ) {
fscanf(fili, "%lf %lf %1f",Q [j] ,E NGY[j],Y Y [j]);
}
for(j=l;j<=KK;++j){
fscanf(fili,"%d %d %d %d",J A [j],J B [j],K P I [j ] ,K C L O [j]) ;
}
for(i=l;i<=NTEP;++i){
fscanf( f i l i , "%d %d",JJUN[j],JPIP[j] ) ;
}
fo r(j =1;j<=KN;++j ){
fscanf( f i l i , "%d %d %d %d",JIJ[j ] , JJI[j ] , E[j ] , B[j ]);
}
/*============================================================================*/
/* I OUT== ZERO FOR FULL OUT PUT
*/
/* I O U T ! =0 FOR SE CL E ECTE D J U N C T I O N FOR THE R E S L U T
*/
/ * N J O U T I =0 THERE A R E J U N C T I O N S LEC TE E D TO SHOW A S R E S L U T
*/
/ * N J O [ ] ==1 HER THE J U N C T I O N ONE I S S L EC T E ED I N THE R E S L U T
/ * Y Y [ ] = THE HEAD L O S S I N THE P I P E =HL-PUMP HEAD+MIONR L O S S E S
/* T H I S PROGRAMMS TO COMPTE THE QRADE L I N E AND THE P R E S S U R E A T EACH J U N CT IO N
/ * AND TO SHOW THE MAXMMUMPRESSURE AND THE MINMMUM P R E S S U R E I N WHERE
/ * I N THE N E T WORKS.
/ * SUMMARY OF I NF LO W AND OUT FLOW FROM F I X E D GRADE NODE.
/ * THE N E T FLOW I N T O THE S Y S T E M AND THE N E T OUT OF THE S Y S T E M
*/
*/
*/
*/
*/
*/
*/
/* ============================================================================*/
for(i=l;i<=KJ;++i){
Y [ i ] =0.0;
}
NEXT=NTEP;
fo r(j =1;j <=NEXT;+ +j ){
m=JJUN[j ];
J8=JIJ[m];
NEX[j]=J8;
J9=JPIPtj];
Y[J8]=ENGY[J9]+YY[J9];
i f (JA[J9]= = 0){
Y[J8]=ENGY[J9]-YY[J9];
}
}
MO:
/
NXX=0;
for(i=l;i<=NEXT;++i){
J=NEX [ i ] ;
MBEG=M[J ];
MJJ=M[J+l]-1;
for(k=MBEG;k<=MJJ;++k){
N1=MPL[k];
Nl=abs(Nl);
N2=JA[Nl];
N3=JB[Nl];
if(N2==J){
if(N3==0){
continue;
}
if(Y[N3]1=0){
continue;
}
Y[N3] =Y[N2] -YY[Nl];
NXX=NXX+1;
NIX[NXX]=N3;
}
if(N2==0){
continue;
}
if(Y[N2]!=0){
continue;
}
Y[N2] =Y[N3] +YY [Nl] ;
NXX=NXX+1;
NIX[NXX]=N2;
}
}
NEXT=NXX;
if(NEXT!=0){
for(i=l;i<=NEXT;++i){
NEX[i] =NIX[i] ;
}
goto MO;
}
'
f or(j =1;j <=KN;+ +j){
I=JJI[j];
IPRINT=1;
if(IOUT!=0){
IPRINT=0;
if(NJOUT!=0){
f o r (1=1;1<=NJ0UT;++1){//
if(NJO[1]==I){
IPRINT=1;
L
}
} / / --------------- L
}
}
PRES = (Y[j] - E [j]) * SW * 62.4/144.0;
if(NQ==3){
PRES=(Y[j] - E[j]) * SW * 9.807;
}
W 9 [j]=PRES;
if (E[j]= = 0){
W9 [ j]=0;
>
QEXT=- B [j] * CQ;
if (B[j]«0){
QEXT=0;
}
QEXT=QEXTT+QEXT ; / / t h e n e t s y s t e m d e m a n d
if (IPRINT= = 0) {//------ > n e x t j
continue;
}
if (E[j]= = 0){
printf("\n I=%d
QEXT=%lf
%lf
%lf",I,QEXT,Y[j],W9[j]);
}
if(E [ j] !=0){
printf (11 \n I=%d
QEXT=%lf
%lf
PRES=%lf",I ,QEXT,Y[j],PRES);
}
}
if(NMOM!=0){
printf("\n Maxmmum pressure at the junction");
for(i=l;i<=NMOM;++i){
PMAX=-100000.0;
PMIN=1000.0;
for (j=l; j<=KN; + +j ) {//-------- KN
if(W9[j]!=0){
if (W9[j]>PMAX){
J M A X = j;
PMAX=W9[j];
>
if (W9[j]<PMIN){
JMIN= j ;
PMIN=W9 [j] ;
}
}
}//<<<<<<<<<<<<<<< KN
11=JJI[JMAX];
JD[i]=JMIN;
W9[KN+i]=PMIN;
QEXT=-B[JMAX] * CQ;
printf("\n %d
%lf
%lf
W9[JMAX]= 0.0;
W9[JMIN]= 0.0;
%lf
%lf", II,QEXT,Y[JMAX] ,E [JMAX] ,PMAX);
}
printf("\n Minummum pressure for the junction");
for(i=l;i<=NMOM;++i){
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
/* ---
-
-
-*/
for (j =1; j <=KK; ++j) {//-------------------- >>>>>KK
JDIFF=JA[j] -JB[j];
i f ((J A [j]+JB[j])<=abs(JDIFF)){
if(KCLO[j ] !=1){
if(W9[j] !=9999 . 0){
T T1=(J A [j]+J B [j])/(J A [j] -JB[j]);
QEX=-Q[j] * TT1 * CQ;
if(QEX>0.0){
QIN=QIN+QEX;
}
if(QEX<0.0){
QOUT=QOUT+QEX;
}
}
}
}
L=KPI[j];
printf("\n
L=%d
QEX=%lf ",L,QEX);
}//-------------------------------------- > » » K K
printf("\n The net flow into the system from fixed grad node QIN=%lf",QIN);
printf("\n The net flow out of the system into fixed grad node QOUT=%lf",QOUT) ;
}
