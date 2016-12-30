/*============================================================================*/
/*
com puter a n a ly s i s o f flo w and p e r e s s u r e in p ip e n etw o rks
*/
/* f u n c t i o n F i v e :
*/
/*
KTEP= THE NUMBER OF F G N - 1
*/
/*
K N - NUMBER OF J U N C T I O N I N THE S Y S T E M
*/
/*
B [ ] - THE DE FF E R E NT OF ENERGY BETWEEN EACH THE FGN (J+KN)
*/
/*
M AX T - MAXMUM NUMBER OF I T E R A T I O N
*/
/*
K C L O- F L AG E TO I N D I A C T E THE P I P E I S CLOSED OR NOT
*/
/*
I F THE P I P E I S CLOSED SO WE TAKE q f r o m t h e e q u a t i o n
*/
/*
*/
/*============================================================================*/
#include< s tdio.h>
#include<math.h>
#include<stdlib.h>
ttdefine MAXT
20
#define MAX_SIZ 8 0
//vo id
m ain ( v o i d ) ;
FILE *fili,*filo;
int
gauss
(double a[][MAX_SIZ],double
b[],int N,double *ptr_det);
void main, (void)
double AA[MAX_SIZ],BB[MAX_SIZ],CC[MAX_SIZ],EE[MAX_SIZ],FF[MAX_SIZ];
double DD[MAXSIZ],GG[MAX_SIZ];
int NCODE=l; / / i n t N R S T = 0 ;
int JC[MAX_SIZ],MPL[MAX_SIZ];
int i ,j ,k,NP,MBEG,j j ,s ,d,1,J8,J 9 ,L,NXX,n,moh;
double C[MAX_SIZ] ,R[MAX SIZ] ;
int LN, NN, N N S , II, N 1 , N2 , MJJ, J , NJTJNC, NEXT;
int JP[MAX_SIZ] ,NEX[MAX_SIZ] ,NIX[MAX_SIZ] ,KC[MAX_SIZ] ,JX[MAX_SIZ] ,IX[MAX SIZ] ;
int IP[MAX_SIZ] [13] ,JF[MAX_SIZ] ,JIJ[MAX SIZ] ,JA[MAX_SIZ] ,JB[MAX_SIZ] ;
int JPIP [MAX_SIZ] , JJTJN[MAX_SIZ] ,M[MAX_SIZ] , KCLO [MAXSIZ] ,NA[10] ,NB[10] ;
double Q[MAX_SIZ],D[MAX_SIZ],S[MAX_SIZ],V[MAX_SIZ];
double W9[MAX_SIZ] ,AM[MAX_SIZ] ,BM[MAX_SIZ] ,B[MAX_SIZ] ,YY[MAX_SIZ] ,ENGY[MAX_SIZ] ;
double H I ,G 1 ,E P ,T 1 ,T 2 ,Q I ,P03,P04,P05,P06,P07;
double a[MAX_SIZ][MAX_SIZ],b[MAX_SIZ],det;
int return_val,N;
int KTEP,K N ,NTEP,K K ,K J ,NEL;
double A3,P; / / d o u b l e U U = 0 ; d o u b l e A 2 = . 0 2 5 1 7 ;
//d o u b le
H D I F F , R E Y , FF A C, PW;
char fnaml[2 0],fnam2[2 0];
/*============================================================================*/
printf("Give: input file name\r\n");
scanf("%s",fnaml);
(
)==NULL)
.%s",
i f (fili=fopen(fnaml,"r+")
p rin tf("Cannot open input f
exit (0);
{
fnaml);
}
printf("Give output fule name\r\n");
scanf("%s",fnam2);
if ( (filo=fopen(fnam2,"w+"))==NULL){
printf("Cannot open output f,%s",fnam2);
exit(0);

/*============================================================================*/
fscanf(fili,"%d %d %d %d %d %d %lf %lf",KN,KK,KTEP,NTEP,KJ,NEL,A3,P);
f o r (j =1;j <=KK;+ +j ) {
fscanf(fili,"%d %d %lf %lf %lf %lf %lf %lf",J A [j],JB[j],Q[j],D[j],S[j] ,V[j] ,R[
j] ,C[j] , ENGY [ j ] ) ;
}
for(j =1;j <=KTEP;+ +j){
fscanf(fili,"%d %d",NA[j],NB[j]);
}
for(j =1;j <=KN;++j){
fscanf(fili,"%d %d %d",I X [j],J I J [j],B [j]);
}
for(i=l;i<=KK+l;++i){
fscanf(fili,M%d",M[i] );
}
for(j=l;j<=NEL;+ + j ) {
fscanf(fili,"%d",MPL[j]);
}
for(i=l;i<=NTEP;++i) {
fscanf(fili,"%d %d",JPIP[i],JJUN[i] ) ;
>
N=KK;
for(i=l;i<=20;++i){
KC [i]=0?
KCLO[i]=0;
}
for(j = l;j <=KTEP;+ +j){
S=NA[j];
d=NB [ j] ;
B [ j +KN] =ENGY [s] -ENGY [d] ;
}
/*
*/
for(i=l;i<=MAXT;++i){
NNS=0;
for(k=l;k<=KN;++k){
W9[k]= 0;
JP[k]=NNS +1 ;
NP=M[k+1]-1;
MBEG=M[k];
for (j j=MBEG; j j<=NP;+ + j j) {//-------------- > > j j
LN=MPL [j j] ;
NN=abs(LN);
if(KCLO[NN]!=1){
NNS=NNS+1;
JX[NNS]=NN;
AM[NNS]=1;
if(LN < 0){
AM [NNS] = -AM [NNS] ;
}
}
a [k] [NN] =AM [NNS] ;
} / / ----------------------------« 3 J
/*
}
*/
if(KN==KK){
goto Carne;
}
for (k=KJ; k<=KK; ++k) { / / -------------------------- k
W9[k]=0;
L=k-KJ+l;
JP[k]=NNS+1;
NP=M[k+1]-1;
M B E G = M [k] ;
for ( j j =MBEG; j j <=NP; + +j j ) {//----------- E
L N = M P L [j j] ;
NN=abs(LN);
NNS=NNS+1;
JX[NNS]=NN;
if(KCLO[NN]==1){
goto Ali;
}
if(Q[NN]<0 && KC[NN]>0){
Q[NN]=3.14 * D[NN] * D[NN];
}
QI=fabs(Q[NN]);
T1=0 ;
T2 = 0 ;
if(QI==0){
goto Ali;
}
if(KC [NN] = = 0) {
goto Rama;
}
II=KC[NN];
if(BB [II]= = 0) {
goto Omar;
}
JC[NN]=1;
if(QI < GG[II]){
goto Rajb;
}
T1 = FF[II]+EE [II] * QI;
T2=EE[II];
goto Rama;
Rajb :
7
P03 =pow(QI,BB[II] ) ;
T1=DD[II] - CC[II] * P03;
P04=pow(QI, (BB [II] -1. )) ;
T2=BB[II] * CC[II] * P04;
goto Rama;
Omar:
7
T1=AA[II]
T2=AA[II]
Rama:
* A3 / QI;
* A3/(QI * QI);
7
P05=pow(QI,P);
P06=pow(QI, (2.0-T1));
H l = (S [NN] * P05) + (V[NN] * P06);
P07 =pow(QI, (P-1.0));
G l= (P *S [N N ]*
P07)+ (
2
*
V [N N ]*
Q I)+ T 2;
AM[NNS]=G1*LN/NN;
EP=((G1 * QI) - HI)* Q[NN]* LN/(QI * NN);
Ali:
7
if(KCLO[NN] !=0 && QI = = 0){
AM[NNS]=1 * LN/NN;
EP = 0 ;
}
a [k] [NN] =AM[NNS] ;
W 9 [k]=W9[k]+EP;
}
}
/*
*/
Came:
;
JP[KK+1]=NNS+1;
if(NCODE==0){
goto Salam;
}
f or(j=l;j<=NNS;++j){
I X [j]=J X [j];
//printf ("\nIX[%d] =%d",j, IX[j]) ;
BM [ j ] = A M t j ] ;
printf("\nBM[%d]=%2.51f",j ,B M [j]);
printf(n\n moha= ");
scanf("%d",&moh) ;
}
for(j=l;j<=KK;+ + j) {
if (JP[j+l]==JP[j]){
printf("\nXXX[all pipe connection the junctionJJI[%d]=%d are closed]XXXX" ,j)
;
}
lP[j] [l]=JP[j] ;
printf("\n IP[%d] [1]=%d",j,J P [j]);
>
IP[KK+1][1]=NNS+1j
f or(j=l;j<=KJ;++j){
J F [j]=0;
}
NJUNC=0;
NEXT=NTEP;
*/
/ * ------------
for(1=1;1<=NTEP;++1){
J9=JPIP [1] ;
if(KCLOIJ9]1=0){
NEXT=NEXT-1;
goto Oalid;
//NEXT L
}
n=JJUN[1];
J8=JIJ[n];
if(JF[J8]==1){
NEXT=NEXT-
1 ;
goto Oalid;
}else{
//NEXT L
JF[J8]=1;
}
NJUNC=NJUNC+1 ;
NEX [NJÜNC] = J8 ;
Oalid:
;
}
/ * ---------------
Salim:
NXX=0;
if(NEXT==0){
goto Ahmed;
}
for(1=1;1<=NEXT;++1){
J=NEX[1 ];
MBEG=M[J] ;
M J J = M [J+l]-1;
for(k=MBEG;k<=MJJ;++k) { / / --------------- K
N1=MPL [k] ;
Nl=abs(Nl);
if (KCL0[N1] l=l){// FULL OUT PUT FOR THE JUNCTION NODE
N2=JA[N1]+JB[Nl]-J;
if(JA[N1]!=0){
if (JB[N1] ! =0) {
if (JF[N2] ! =1) {
JF[N2]-1;
NiTONC=NJUNC+l;
NXX=NXX+1;
NIX[NXX]=N2;
>
}
}
>
} / / ----------------------- K
} / / ------------------------------- L
NEXT=NXX;
if(NEXT 1=0){
fo r (1=1;1<=NEXT;++1){
N E X [1]= NIX[1];
}
goto Salim;
}
Ahmed:
/
if(NJUNCI=KN){
printf("\nXXXXXXX[no open connection to the system]XXXXXXXXX");
}
Salam:
for(j =1;j <=KK;++j){
YY[j]=B[j]+W9[j] ;
b [ j ] =»YY [ j ] ;
printf("\nYY[%d]=%lf",j,YY[j]) ;
}
printf(n\n L=%d",L);
/*
call gaussl function*/
return_val=gauss(a,b,KK,&det);
/*pritn rreslut*/
if (return_val == 0){
printf("\n\n \t the sluatio of the
printf("\n the sluation is ") ;
for(i=l;i<=N;++i){
printf("\n \t x(%d)=%lf",i,b[i]);
}
printf("\n determinat=%lfn,&det);
}else
printf(w\n\n \t the matrix is singular " );
for(j=l;j<=N;++j){
Q[j]=b[j] ;
printf("\nQ[%d]=%lf",j,Q [j])j
----------------------------- j
}
/* m a in * /
}
/*============================================================================*/
/*
fu n c tio n to s lo v e lin e a r eq u a tio n
*/
/*
*/
/*============================================================================*/
int
gauss (double a[][MAX SIZ],double
b[],int N,double *ptr_det)
double temp,inult, trt, toi;
int npivot,i,j,k,l,error_flag;
*ptr_det=l.0 ;
tol = le-3 0 ;
npivot=l;
for(k=l;k<=N-l;++k){
for(i=k;i<=N;++i){
printf("aik[%d][%d]=%lf",i,k,a[i][k] );
printf("akk[%d][%d]=%lf",k,k,a[k][k] );
if(fabs(a [i] [k])>fabs (a [k] [k])){
++npivot;
for(1=1;1<=N;++1){
temp=a[i] [1] ;
a [i] [1] =a [k] [1] ;
a[k][1]=temp;
}
temp=b[i];
b[i] =b [k] ;
b[k]=temp;
}
/*
printf("\n\t
*/
i f
b[%d]=%lf",i,b[i]);
>
trt=*ptr_det;
printf("\n\t atrt=%lf",trt );
printf("akk[%d][%d]=%lf",k,k,a[k][k]
trt =*ptr_det*a[k] [k] ;
if (fabs(trt)<tol){
error_flag=l;
return(error flag) ;
}
for(i=2;i<=N; ++i){
if(il=k){
mult—a[i][k]/a[k][k]>
b[i]=b[i]-b[k]*mult;
printf("\n\t mult=%lf11 ,mult );
fo r (j=l;j<=N;++j )
{
a [i] [j]=a[i] [j] -a [k] [j]*multj
p rin tf("aii[%d] [%d]=%lf",i , j ,a[i] [j] ) ;
}
}
}
}
/*
k
*/
for(i=l;i<=N;++i)
fo r(j=l;j<=N;++j )
p rin tf("\n\t a f [%d][%d] =%lf",i , j, a [ i] [ j ] ) ;
for(i=l;i<=N;++i)
{
printf(“\n\t
b[%d]=%lf",i,b[i]);
>
if (npivot %2==1)
*ptr_det=*ptr_det*(-1.0);
b [N] =b [N] /a [N] [N] ;
printf("\n\t b [%d]=%lf",N , b [N]);
printf("\n\t af[%d][%d]=%lf",N,N,a [N][N]);
for(i=N-l;i >=1;i --){
for(jai+ljj<=N;++j)
b[i]=b[i]-a[i] [ j ] *b [ j ] ;
b [i] =b [i] /a [i] [i] ;
}
error_flag=0 ;
return(error_flag);
>
