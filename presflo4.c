/ * ============================================================================*/
/*
/*
com puter a n a ly s is
fu n ctio n Four :
of
flo w
and p r e s s u r e
in
*/
*/
p ip e netw oks
/*
*/
/*
J A , J B : NODE CONNECTED P I P E
j a [ ] o r j b [ ] = = 0 i f i t i s FGN
I P : FOR EACH J U N C T I O N I N THE N E T AND A P I P E CONECCTED THE J U N C T I O N
M-.NUMBER OF P I P E CONEECTED EACH J U N C T I O N
J D : = = 2 FOR EACH F I X E D GRADE NODE I N THE N E T OTEHR ==0
P I N : N OF P I P E c o n e c t t o THE F I R S T F I X E D GRADE NODE I N THE NET>>>NTEP==1
KN: NUMBER OF J U N C T I O N I N THE N E T
KK: NUMBER OF P I P I N THE N E T
KJ:=KN+1
KP:=KK-KN
M P L : FOR EACH J U N C T I O N HOW MANY P I P E CONNEDTED EACH J U N C T I O N
/*
/*
/*
/*
/*
/*
/*
/*
/*
/*
*/
*/
*/
*/
*/
*/
*/
*/
*/
*/
*/
/*
the
fu n ctio n
do s p e f i e d
the p a th
and
the
loops
equation
for
the
system
*/
/ * ============================================================================*/
#include<stdio.h>
#include <math.h>
#include<stdlib.h>
#define
MAX_SIZ
8 0
// v o i d c o m b i n e ( i n t J F [] , i n t NZ ) ;
/ /
void
//vo id
com bine2(int
KN, i n t
/ / i n t M6, i n t M7, i n t
com bine3 ( i n t
KN, i n t
N P , i n t I P [20] [13] , i n t J A [ ] , i n t
M 8 ,in t M 9);
IX [ ] ,in t JE []);
J B [ ] , i n t J D [] , i n t M/7,
FILE *fili,*filo,*fill;
void combine4 (int MPL[],int M[],int NA[],int NB [] ) ;
void main(void)
{
int KN,KP, NEL,KJ,KK,NTEP,LNUM;
int M[MAX_SIZ],J D [ M A X S I Z ] ,JG[MAXSIZ],IX[2 0],MPL[MAX_SIZ],JE[MAX_SIZ];
int N A [20] ,N B [20] ,JA[20] ,J B [20] ,IP [20] [13] ,JF[MAX_SIZ] ;
int KL,J8,M1,NP,L8,L9,NZ,N8,j,k, I,jj ;
int JPIN,NZX,NXX;
int M6=0;int M7=0;int M8=0;int M9=0;
int J7=l;int J6=0;
int JXNIN,JXNJJN,JEM;
int i,ii,JJJJ,JJJ1,jjj;
int ERR=0;
char fnaml [20] , fnam2 [20] ;
/ * =================================================================3==========*/
printf("Give file name for input\r\n");
scanf("%s",fnaml);
i f ((fili=fopen(fnaml,"r+"))==NULL){
printf("Cannot open input f. %s",fnaml);
exit(0);
}
printf("Give file name for output\r\n");
scanf("%s",fnam2);
i f ((filo=fopen(fnam2,"at"))==NULL) {
printf("Cannot open output f. %s",fnam2);
exit(0);
}
/**/
fscanf{fili,"%d %d %d %d %d %d %d",KN,KP,NEL,KJ,KK,NTEP,LNUM);
fscanf(fili,"%d %d %d",JPIN,NZX,NXX);
for(j =1;j <=KK;++j){
fscanf(fili,"%d %d %d",J A [j],J B [j],JD [j]);
}
f or(j=l;j<=KN+l;++j){
fscanf(fili,"%d",M[j]);
>
f or(j=l;j<=KN;++j){
for(i=l;i<=3;++i){
fscanf(fili,"%d",IP[j][i]);
}
}
KL=KP-NTEP+1;
/*
c a ll function */
combine4(MPL,M,NA,NB);
JD[JPIN]=1;
M1=KN;
J8=JA [JPIN] + JB [JPIN] ;
i f (JA[JPIN]>JB[JPIN]){
JG[J8] =-JPIN;
}else{
JG[J8]=JPIN;
>
Age:
i
JE [J8] =1;
1.9 = 1 ;
IX [1]=J8;
/*
*/
for(k=l;k<=KN;++k){
NZ = 0 ;
L8=IX[k];
if(J7!=2 && L8==0){
fprintf(filo,"\n this system is disconnected");
NXX=1;
}
i f (J7o=2 && L8==0){
break;
}
NP=M[L8+1]-M[L8];
f or(j=l;j<=NP;++j){
N8=IP[L8] [j] ;
N8=abs(N8);
if(JA[N8]1=L8 && JB[N8]I=L8){
continue;
}else{
J8=JA[N8]+JB[N8]-L8;
}
if (JD[N8]= = 1) {
continue;
}
if(abs(J8-J6)>0){goto Rod;}
NZ=NZ+1;
M1=M1+1;
i f ((Ml-KN)<=NTEP){
NB[Ml-KN]=N8;
}
JF [NZ] =N8;
if(J7I=2){
JD[N8]=1;
}
if(JA[N8]!=L8){
JF[NZ]=-N8;
}
Fog:
7
J8=JA [N8] + JB [N8] -J8;
i f (J8I=J6){
goto Gof;
}
if((Ml-KN)<=NTEP){
NA[Ml-KN]=N8;
fprintf(filo,"\n NA[%d-%d]=%d",M1,KN,N8);
}
for (ii = 2 ; ii<=NZ ; + + ii){//------------------------------------- i i
JJJJ=ii-l7
for(jj=l;jj<=JJJJ;++jj){
JXNIN=JF[ii];
JXNJJN=JF[j j];
if(abs(JXNIN)>=abs(JXNJJN)){
continue;
}else{
JJJl=jj+1;
JEM=JF[ii];
for(jjj=JJJl;jjj<=ii;++jjj){
JF[ii+JJJl-jjj]=JF[ii+JJJl-jjj-1] ;
}
JF[jj]=JEM;
}
break;
> / / -------------- j j
} / / --------------------------------- H
LNUM=LNUM+1 ;
M[LNUM]=NEL + 1 ;
fprintf(filo,"\n M[%d]=%d",LNUM,NEL+1) ;
for(jj=l;jj<=NZ;+ + jj) {
NEL=NEL+1;
fprintf(filo,"\n NEL=%dn,NEL) ;
M P L [NEL]=JF [ j j] ;
fprintf(filo,"\nMPL[%d]=%d",NEL,M P L [NEL]);
printf ("\n-------- f l a g ----------- =%d",ERR);
scanf("%d",&ERR);
} / / -------------------------------------- » j j
NZ=0;
if(J7==2){goto Again;}
i f (J7==l){
continue;
}
Gof:
7
N8=abs(JG[J8] ) ;
NZ=NZ+1;
JF [NZ]=JG[J8];
goto Fog;
Rod:
7
if(JE[J8] l=l){
L9=L9+1;
IX[L9]=J8;
J E [J8]=1;
J G [J8]=N8 ;
if(abs(J8-JB[N8]) J =0){
J G [J8]= -N8;
}
}
} / / ------------- J
} //
»*
Again :
M9 = 0 ;
for(j =1;j<=KN;+ +j){ //------------------------------- > J
M7 = 0 ;
N P = M [j +1]-M [ j] ;
printf("\n NP=%d",NP);
for (k=l; k<=NP; ++k) {//--------------------------- >K
M8 = IP[j] [k] ;
M8=abs(M8);
if ( JA [M8] ! = j Sc Sc JB [M8] ! = j ) {
continue;
}
if (JD[M8] <1) {
M7=M7+1;
M6=M8;
} / /
}
>K
if(M7==l){
M9=l;
JD[M6]=1;
}
} //
2
if(M9==l){goto Again;}
if(M7==2){goto Num;}
1 = 1 ;
Sum:
?
if(JD[I]<0){
f or (k=l ; k<=KN;++k) {//--------------- >d
IX[k]=0;
J E [k]=0;
} //
>d
J6=JA [I] ;
J8=JB[I];
J7=2 ;
J G [J8]=1;
JD [I]=1;
goto Age;
}
Num:
1 = 1 + 1 ;
if(I<=KK){goto Sum;}
M[KK+1]=NEL+1;
KL=LNUM-KN-NTEP+1;
M[KK+1]=NEL+1;
printf ("\n---------s t o p ----------- =%d",ERR);
scanf(M%d",&ERR);
fprintf(filo,"\n KKs=%d KN=%d
KL=%d
NTEP=%d
fprintf(filo,"\n NXX=%d
NZX=%d",NXX,NZX){
KJ=%d",KK,KN,KL,NTEP,KJ) f
M[KK+1]=NEL+1;
if(LNUM I=KK){
fprintf(filo,"\nXXXXXXXXX[The Relation[P=J+L+T-1]IS NOT SATESFIED]XXXXXXXXX") ;
NXX=1;
}
if(NXX!=0){
fprintf(filo,"\nXXXXXXXX[Error in the data]XXXXXXXXXXXXXX");
}
}
/ * ============================================================================* /
/*
*/
/*===============================================================-============*/
void combine4 (int MPL[],int M[],int NA[],int NB [] )
{
int j ,i ;
for(j=l;j<80;++j) {
M P L [j]=0 ?
}
for(j =1;j<70;++j){
M[j+5] =0;
}
for(i=l;i<20;++i){
NA[i]=0;
NB[i]=0 ;
}
}
