/*============================================================================*/
/* c o m p u t e r a n a l y s i s o f f l o w a n d p r e s s u r e i n p i p e n e t w o r k s
*/
/* f u n c t i o n :
*/
/*
G aussin E lim in ta tio n
*/
/*
*/
/*============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define eps l.0e-6
#define one 1.0
#define onn -1.0

FILE *fili,*filo;
int gausel(int n,float **a,float *b,float *dd,float *error);

void main(void)
{
int n,i,j;
float **a,*b,*dd,*error;
char fnaml[20] ,fnam2[20] ;
printf ( "Give N 11 ) f scanf ( "%d" ,&n) ;
b=(float*)calloc(n,sizeof (float));
dd=(float*)calloc(n,sizeof(float));
error=(float*)calloc(n,sizeof(float));
a=(float**)malloc(n*sizeof(float*)); / / a l l o c a t e s p o i n t e r s
to
rows
for(i=0;i<n;i++) a[i]= (float*)malloc(n*sizeof(float));// a l l o c a t e s r o w s & p o i n t e r s to them
/*
printf("Give input file name\r\n");
scanf("%s",fnaml);
i f ((fili=fopen(fnaml,"r"))==NULL){
printf("File %s does not exist",fnaml);
exit(0);
}
printf("Give output file name\r\n");
scanf("%s",fnam2);
i f ((fili=fopen(fnam2,"w"))==NULL){
printf("File %s does not exist",fnam2);
exit(0);
}
for(i=0;i<n;i++){
f o r (j = 0 ; j < n;j + + )
fscanf(fili,"%f",&a[i][j]);
fscanf(fili,"%f",&b[i]);
}
j =gausel(n,a,b,dd,error);
printf("\nSolution;\n");for(i = 0;i<n;i + + )printf("%f ",b [i]);
printf (11 \nDeterminant=%f\n" , *dd) ;
// f r e e ( b ) ; f r e e ( e r r o r ) ; f o r ( i = n - l ; i > = 0 ; i - - )
free(a [i]);
f r e e (a) ;
/*
*/
int gausel(int n,float **a,float *b,float *det,float *errnor){
int n l ,i ,j ,k,il,*1;
float **ao,*bo,**xo,fac;
*det=one; nl=n-l;
1 = (int *)malloc((unsigned)n*sizeof(int));
bo=(float *)malloc((unsigned)n*sizeof(float));
ao=(float **)malloc((unsigned)n*sizeof(float *));
for(i=0;i<n;i++) ao[i]= (float *)malloc((unsigned)n*sizeof(float));
xo=(float **)malloc((unsigned)n*sizeof(float*));
for(i=0;i<n;i++) xo[i]= (float *)malloc((unsigned)n*sizeof(float));
/* C o p i e s o r i g i n a l a & b i n t o
ao
& bo
for
la ter
use
in
d eterm ining
error.
*/
for(i=0;i<n;i++)
{
  bo[i]=b[i] ;
  for(j=0;j<n;j++)
    ao[i][j] =a[i][j] ;
}
/* p i v o t s on l a r g e s t row & ke e p s track o f row no in 1 [k];*/
for(k=0;k<nl;k++)
{
fac=fabs(a[k][k]);
1 [k]=k;
for(i=k+l;i<n;i++)
if (fabs(a [i] [k])>fac)
{
fac=fabs(a[i][k]);
1 [k]=i;
}
if(fac<eps){printf("Matrix is singular"); return 1;}
i f (1[k] != k) {
*det *= onn;
f o r (j =k;j <n;j + + ) {
fac = a[k] [j] ;
a [k] [j] =a [1 [k] ] [j] ;
a [1[k]] [j] =fac;
}
}
/* G a u s s i a n e l i m i n a t i o n
(o n l y a b e c a u s e b m u s t b e
for(i=k+l;i<n;i++){
f ac=a [i] [k]/a[k] [k] ;
a[i][k]=fac;
for(j=k+l;jcnj j+ + )
a [i] [j] - = fac*a[k] [j] ;
>
>
/*
Computes determinant det */
for(i=0;i<n;i++) *det *= a[i][i]j
for(il=0 ; il<2 ; il++) { / *
now adjust b for orig. elim & iter, correction
for(k=0;k<nl;k++){
if (l[k] ! = k) {
fac=b[k];
b [k] -b [1 [k] ] ;
b [1 [k] ] =f ac ;
}
for(i=k+l;i<n;i++)
bti] -=a[i] [k] *b[k] ;
}
/*
Back substitution
*/
x o [ni] [il]=b[nl]/a[nl] [nl];
for(i=nl-l;i>=0;i--){
fac=b [i] ;
for(j=i+l;j<n;j++)
fac-=a [i] [j]*xo[j] [il];
x o [i] [il]=fac/a [i] [i] ;
}
/*
Computes residual vector
{r}={b}-[a](x) */
for (i=0 ; i<nj i++) {//----- ii
fac=bo[i];
for(j=0;j<n;j++)
f ac-=ao[ i ] [j ] *xo[j ] [ i l ] ;
b [i]=fac;
bo[i]=fac;
} / / ---------- ü
}
for (i=0;i<n;i++){b[i]=xo[i][0]+xo[i][1];
errnor[i]=fabs(xo[i] [1])/(fabs(b[i])+eps); }
free(1); free(bo);for(i=n-l>i>=0;i--)
free(xo[i])jfree(xo)j
for(i=n-l;i>=0;i--)free(ao[i ] ) ; free(ao)j
return 0;
}
