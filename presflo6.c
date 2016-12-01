y7'* — _ — _ — — —
— _= — — — = _- — — — _ — — — = — — — — — — — — — — — _ — —
/*
COMPUTER
F UNCT ION 6 :
/*
A N A L Y S I S OF FLOW AND
— — — — — — — — —
— = — — — — — — — — /
P R E S S U R E I N P I P E NETWORKS
/*
*/
*/
* /
/*
/*
FLOW: FLOW R A T E I N EACH P I P E
H L : HEAD L O S S E S I N THE P I P E
PUMP: PUMP HEAD
Z I N O R : MINOR L O S S E S I N THE P I P E
V E L: V E L O C I T Y
/*
/*
/*
*/
*/
*/
*/
*/
/*
*/
/ * ============================================================================*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PE 1.852
#define MAX_SIZ 20

FILE *fili,*filo;

void main(void)
{
double AA[MAX_SIZ] ,BB[MAX_SIZ] ,CC[MAX_SIZ] ,EE[MAX_SIZ] ,FF [MAX_SIZ] ;
double DD[MAX_SIZ],GG[MAX_SIZ];
int KPI[MAX_SIZ] ,JA[MAX_SIZ] ,JB[MAX_SIZ] ,JJI[MAX SIZ] ,KCL0[MAX_SIZ] ,KC[MAX_SIZ] ;
int j ,NN,II,LL,IPRINT,JAAAA,JBBBB,M;
int NPO[MAX_SIZ],JC[MAX_SIZ];
double Q[MAX_SIZ] ,V[MAX_SIZ] ,D[MAX_SIZ] ,R[MAX_SIZ] ,S[MAX_SIZ] ,YY[MAX_SIZ] ;
doub1e FLOW,H L ,PUMP,ZINOR,VEL,XHL,A3,C Q ,P ,QI;
int IOUT,NPOUT,KK,KN;
char fnaml[2 0],fnam2[2 0];
/ * ============================================================================*/
printf("Give file name for input\r\n");
scanf("%s",fnaml);
if ( (fili = fopen(fnaml,"r+"))==NULL){
printf("Cannot open input f. %s",fnaml);
exit(0);
}
printf("Give file name for output\r\n");
scanf("%s",fnam2);
if ((filo=fopen(fnam2,"a+"))==NULL) {
printf("Cannot open output f. %s",fnam2);
exit(0);
}
/ * ============================================================================*/
/ * ------------------------------------------------------------------------------------------------------------------------ */
/* I O U T = = l T HAT
I S MEAN N O T FULL OUT PUT THERE A R E SOME P I P E S LEE C TE D
NPOUT =2 HOW MANY P I P E H AS E B E EN SLEECTED
/* I F I O U T = 0 FULL OUT PUT
/*
*/
*/
*/
/ * ------------------------------------------------------------------------------------------------------------------------ */
fscanf(fili,"%d %d %d %lf %lf %lf",KK,KN,IOUT,NPOUT,A3,CQ,P);
for(j = 1 ; j <=KK;+ +j){
fscanf(fili,"%d %d %d %d %d %d",J A [j],J B [j],K C [j],K C L O [j],K P I [j],J C [j]);
}
for (j = 1 ; j <=KK;+ +j ){
fscanf (fili, "%lf %lf %lf %lf %lf",Q[j] ,S[j] ,V[j] ,R[j] ,D[j] ) ;
}
f o r (j = l;j <=KN;+ +j){
fscanf(fili,"%d %d",JJI[j],NPO[j]);
}
for(NN=1;NN<=KK;++NN){
LL=KPI[NN];
IPRINT=1;
if (IOUT! =0) {//-------------- » 9 5 2 0
IPRINT=0;
if (NPOUT! =0) { / / > > » > » » > !
for(j=l;j<=NPOUT;++j){
if(NPO[j]==LL){
IPRINT=1;
}
}
}//<<<<<<<<<<<<<<<<<<1
}//----------------------- « « 9 5 2 0
if (JA[NN] ! =0) {
M= JA [NN] ;
JAAAA=JJI [M] ;
}else{
JAAAA=0;
}
if(JB[NN]!=0){
M=JB[NN];
JBBBB=JJI[M];
}else{
JBBBB=0;
}
QI=fabs(Q[NN]);
HL=(S[NN] * pow(QI,P-1.0)) * Q[NN];
ZINOR=V[NN] * Q [NN] * fabs(Q[NN]);
PUMP=0;
if(KCLO[NN]==l) { / / - - » . 2 0
goto MO;
}
if (KC [NN] = = 0) {//--- » 2 0
goto MO;
}
IPRINT=1;
II=KC[NN];
if(BB[II]!=0 ) { / / - - > > 2 1
goto SA;
}
if(Q[NN]==0 ) { / / - - > > 2 0
goto MO;
}
PUMP=AA[II]
goto MO;
//p rin tf("\n
* A3/Q[NN];
th e number o f
the p ip
L L = % d " , L L ) ; / / - - > > 2 0
SA:
r
if (Q [NN] >= GG[II] ) { / / / 2 1 < < --- » 2 3
PUMP=FF[II]+EE[II] * Q[NN];
printf(" \n the number of the pipe LL=%d" , LL) ; / / - - » 2 0
goto MO;
}
PUMP=DD[II]-CC[II] * p o w (Q[NN],BB[II]);//--- 2 3
if (Q [NN] <= AA [II] ) {//------ » > 2 0
printf("\n the number of the pipe LL=%d",LL);
}
MO:
;
YY[NN]=HL - PUMP +ZINOR; / / - - - « 2 0
if(KCLO[NN]==1){
YY[NN]=HL;
}
PLOW=Q[NN]*CQj
VEL= (Q[NN]* 4)/(3.14159 * pow(D[NN],2.0));
XHL=HL * 1000 /R[NN] ;
if (KCLO [NN] ==1 &£ J C [NN]I=1){
printf("\n line (%d) is closed ",LL);
}
if(KCLO[NN]==1 && J C [NN]==1){
print£("\n the check valve in line %d
is closed",LL);
}
if(KCLO[NN]==1){
Q [NN]= 0 ;
continue;
}
if (IPRINT ==s0 ) {continue;}
printf ("\n LL=%d JAAAA=%d JBBBB=%d " ,LL, JAAAA, JBBBB) ;
printf("\n FLOW=%lf HL=%lf PUMP=%lf", FLOW,HL,PUMP)j
printf("\nZINOR=%lf VEL=%lf XHL=%lf",rZINOR,VEL,XHL);
}
}


