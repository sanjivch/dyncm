
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

FILE *fili,*filo,*fill;
const kl=40,k2=100,k3=5,k4=8;

int nunk,np,nj,npump,nres,nj2,njp2,njp,nvar,jn[k2],nn[kl+1],ires[k4],ipump[k3] , II[k1],12[kl];
float l[kl] ,x [k2] , hi [kl] , ap [k3] ,bp [k3] , cp [k3] , d [k2] [k2] , sf1 = 8.0 , vis7, rg2 , hwc;
void solveq(int n, float a[] [k2], float b[],int itype, float &dd,int indx[]);
/*============================================================================*/

int rline(int *list,int in55)
{
	int i ,jj,ij,j ,ii,nl,nobl;
	nl= 0;//input from the user
	char line[80],rln[3],ch;

	if(in55)
		gets(line);
	else
		fgets(line,80,fill);

	for(i=0,ii = 0,jj=0,ij =0,nobl = 0 ;i<80;i++)
	{
		ch=line[i];
		switch(ch)
		 {
		case'1': case' 's case '/'¡case NULL:
		{
		if(nobl && ((ch=='1')||(ch==NULL)))
		{
			nobl++;
			if((nobl>10)||(ch==NULL)) return ii;
			ij =i+l;
		}
		else
		{
			for (j=0;j<(i-ij);j++)rln[j]=line[ij+j];
			if(jj)
			{
			for(j=nl;j<=atoi(rln);j++) list[ii++]=j; jj=0;
			} 
			else list[ii++]=atoi(rln);
			if ((ch=='/') ||(ch==NULL)) return ii;ij=i+l;
			if(ch==' ') nobl=l;
		}
		break;
		}
		case '1';
		{
		for(j=0;j<(i-ij);j++) rln[j]=line[ij+j];
		nl=atoi(rln);
		jj=i;
		ij =i + l;
		break;
		}
	default:nobl=0;
		 }
	}
	
	return ii;
} // End of function rline
/*============================================================================*/
void fun(float *f) 
{
	int i,j,ii,id,iq;
	float qa,re,fr,sf;
	sf=1;
	
	for(i=0;icnj;i++)
	{
		f[i] =x[i+nj];
		for(j=nn[i]; j<nn[i+l]; j++)
		{
			ii=abs(jn[j]);
			f[i]+ = (float) (jn[j]/ii)*x[ii-l+nj2] ;
		}
	}
	for(i=0;i<np;i++) 
	{ // / n p
		id=i+njp;
		iq=i+nj 2;
		qa=fabs(x[ig]);
		
		if(x[i+njp2]>20.) 
			hi[i]=hwc*l[i]*x[iq]*pow(qa,.85185185)/(pow(x[i+njp2],1.85185815)*pow(x[id],4.87037));
		else 
		{
			re=qa/(vis7*x[id]);
			if(re<21.8) 
				fr=.4;
			else 
			{
				if(re<286.0)
					fr=8.715223/re;
				else 
					do{
						sfl=sf;
						sf=l.14-2.*logl0(x[i+njp2]/x[id]+sf1/re);
						} while(fabs(sf-sf1)>5.e-6);
			}
			fr=l./sf/sf;
			hi[i]=rg2*fr*l[i]*x[iq]*qa/pow(x[id],5.);
		}///else
		if(ll[i]<0.) 
			f [i+nj ] =x [abs (11 [i] ) -1+nvar] -hl[i] -x[12 [i] -1] ;
		else
			f [i+nj]=x[ll[i] -1] -hl[i] -x[12 [i] -1] ;
	}/////n p
	for(i=0;icnpump;i++)
	{
		ii=ipump[i]-1;f[ii+nj]+ = (ap[i]*x[ii+nj2]+bp[i])*x[ii+nj2]+cp[i];
	}
}
// End of function fun
/* ============================================================================*/
void main(void)
{
	int njpp,m,min, ii,nct, in2 , in5, in4, i, j ,nnj , nnj l,muk [6] ,list[kl] , indx [k2] , ipuk [k2] ;
	char *cuk[]={"HGLs at nodes ","Nodal demands ","Pipe flowrates","Pipe diameters", "Pipe roughnesses","Reser. ws-elev"};
	char fnaml[2 0],fnam2[2 0],fnam3[2 0];
	float g=32.2,visc=1.317e-5,conv=.43333333;
	float ql,q2,q3,hl,h2,h3,xx,sum,dd,dx,elev[kl],f[k2],f1 [k2];
	
	printf("Give accel. of gravity & viscosity\r\n");
	scanf("%f %f",&g,&visc);
	
	vis7=7.343472 83*visc;
	
	printf("If network input from kybd give(l)(file=0);unknw input kybd 1;& output to monitor 1 (file=0)\r\n");
	scanf("%d %d %d",&in2,&in5,&in4);
	
	if(!in2)
	{
		printf("Give: input file name\r\n");
		scanf("%s", fnaml) ;
		if((fili=fopen(fnaml,"r"))==NULL)
		{
			printf("File %s does not exist",fnaml);
			exit(0);
		}
	}
	
	if(!in5)
	{
		printf("Give input of unkn file\r\n");
		scanf("%s",fnam3);
		
		if((fill=fopen(fnam3,"w"))==NULL) 
		{
			printf("Cannot open output f. %s",fnam3);
			exit(0);
		}
	}
	
	if(!in4)
	{
		printf("Give file name for output\r\n");
		scanf("%s",fnam2);
		
		if((filo=fopen(fnam2,"a+"))==NULL) 
		{
			printf("Cannot open output f. %s",fnam2);
			exit(0);
		}
	}
	
	if(g>20.0) 
		hwc=4.727328;
	else
	{
		conv=9.806;hwc=10.67417;
	}
	/*============================================================================*/
	/*
	/*
	Reads:
	*/
	//No-pipe-junction-reservoir-pump
	/*
	*/
	//*/
	/*============================================================================*/
	
	if(in2) scanf("%d %d %d %d",&np,&nj,Snres,fcnpump);
	else fscanf(fili,"%d %d %d %d",&np,&nj,tnres,&npump);
	
	nj2=2*nj;
	njp=nj2+np;
	njp2=njp+np;
	nvar=njp2 +np;
	njpp=nj+1;
	rg2=.81056947/g;
	sf1=8.0 ;
	
	/*============================================================================*/
	/* Reads reservoir data:
	/*
	No-line-elevation
	*/
	//*/
	/*
	*/
	/*============================================================================*/
	
	for(i=0;i<nres;i++)
	{
	if (in2) 
		scanf("%d %f", Sires[i] , &x[nvar+i] ) ;
	else 
		fscanf(fili, "%d %f ", fcires[i] ,&x[nvar+i]);
	/*============================================================================*/
	/* Reads pump data:
	/*
	No-line-(heaf-flow)
	*/
	//data */
	/*
	*/
	/* ============================================================================*/
	for(i=0;icnpump;i++)
	{
		if(in2)
			scanf("%d %f %f %f %f %f %f",fcipump[i],&ql,&hl,&q2,&h2,&q3,&h3) ;
		else 
			fscanf(fili, "%d %f %f %f %f %f %f",fiipump[i],&ql,&hl,&q2,fih2,&q3,&h3);
		
		hl/=((ql-q2)*(ql-q3));
		h2/= ((q2-ql)*(q2-q3));
		h3/=((q3-ql)*(q3-q2));
		ap[i]=hl+h2+h3;
		bp[i]=-(q2+q3)*hl-(ql+q3)*h2-(ql+q2)*h3 ;
		cp[i]=q2*q3*hl+ql*q3*h2+ql*q2*h3;
	}

	for(i=0;i<njpp;i++)
		nn[i]=0;
	/*============================================================================*/
	/* f u n c t i o n t o r e a d p i p e d a t a :
	*/
	/*
	R E A DS :
	N o d el, Node2, L en g th , D iam eter, roughness,
	/*
	& guess
	flo w ra te
	*/
	//*/
	/*============================================================================*/
	printf ("---------------- ") ;
	for(i=0;i<np;i++)
	{
		if(in2)
			scanf("%d %d %f %f %f %f" , all[i] , &l2[i] , &l[i], &x[njp+i],&x[njp2+i],&x[nj2+i]);
		else 
			fscanf(fili,"%d %d %f %f %f %f",&II[i],&l2[i],&l[i], &x[njp+i], &x[njp2+i] ,&x[nj2+i]) ;
		
		if(l2[i]==0)
		{
			printf(" 0 for reservoir must be 1st given node");
			exit(0) ;
		}
	}
	nnj = 0;
	for(i=0;i<np;i++)
	{
		if (II[i])
		{
			nnjl=nn[11[i]]+1;
			
			for(j=nnj-1;j>=(nnj1-1);j--) 
				jn[j+1]=jn[j];
				jn[nnj1-1]=i+l;
			for(j= 1 1 [i];jcnjpp;j++)
				nn [j]+=1;
				nnj=nn[njpp-1];
		}// '
		nnjl=nn[12[i]]+1;

		for (j=nnj -1; j>= (nnj 1-1) ;j--) 
			jn[j+l]=jn[j];
			jn[nnj1-1]=-(i + 1) ;
		for(j = 1 2 [i];j cnjpp;j ++) 
			nn[j]+=1;
			nnj=nn[njpp-1];
	}
	/*============================================================================*/
	/* R ea d s j u n c t i o n
	/*
	/*
	data:
	*/
	//Demands, H G L-ELEV-Elev
	*/
	*/
	/*============================================================================*/
	for(i=0;icnj;i++) if(in2) scanf("%f %f %f",&x[nj+i],& x[i],fielev[i]);
	else fscanf(fili,"%f %f %f",&x[nj+i],&x[i],&elev[i]);
	
	for(i = 0;i<nres;i + + ) 11[ires [ i ] -1]=-(i + 1); nunk=nj+np; m=0;
	do{
	if(in5) printf("%4d Unknowns must be given.Give no. of each of following\r\n",nunk);
	
	for(i=0;i<6;i++)
	{
		if(in5)
		{
			printf("%ld.%s ", i+1, cuk[i]) ;
			scanf("%d",&muk[i] ) ;
		}
		else 
			fscanf(fili,"%d",&muk[i]);
	}
	}while ( (muk[0]+muk[1]+muk[2]+muk[3]+muk[4]+muk[5]!=nunk)&&(m++<5));
	
	if(m>=5)
	{
		printf("Incorrect no. of unknowns\r\n");
		exit(0) ;
	}
	m=0 ; mm= 0;

	for(i=0;i<6;i++)
	{
		if(muk[i])
		{
			do{
			if(in5) printf ("\r\n %2d %s Numbers= " ,muk[i] , cuk[i]);
			} while (rline(list,in5)!=muk[i]);
			
			for(j=0;j<muk[i];j++) ipuk[m++]=nun+list[j];
		}
		if(i<2) iran+=nj;
		else mm+=np;
	}
	for(i=0;icnp;i++)
	{
		for(j=0;j<nunk;j++) if(ipuk[j]==i+l+nj2) goto L28;
		for (j=0;j<nj;j+ + ) if ((ipuk[j]= = 1 1 [i]) || (ipuk[j]==12 [i])) goto L28;
		if (11 [i]<0){xx=x[abs(11[i])-1+nvar] ;
		ii = 0 ;
		} else {xx=x[11[i]-1];ii = ll[i] ;
		}
		if ((xx-x[12[i]-1])*x[i-l+nj2]> -l.e-5) goto L28;
		printf("Specified flowrate not consistent with H's in pipe %3d %3d %3d\r\n",i+1, ii,l2[i]);
		printf("Hl= %8.2f H2= %8.2f Q= %8.2f must have HI > H2\r\n",xx,x[12[i]] ,x[i+nj2]);
		printf("Should I reverse direction of this flow? (l=yes, 0=no\r\n)\n");
		scanf("%d",&ii);
		
		if(ii) x[i+nj2]=-x[i+nj2];
		else exit(0);
		L28: continue;
	}
	nct=0;
	do {
		sum=0.0;
		fun(f1);
		for(j = 0;j <nunk;j++)
		{
			ii=ipuk[j]-1;
			
			if(fabs(x[ii])<1.e-3) dx=.001;
			else dx=.005*x[ii] ;
			x[ii]+=dx;
			fun(f);
			
			for(i=0;i<nunk;i++) d[i][j] = (f[i]-fl[i])/dx;
			x[ii]-=dx;
		}
		
		solveq(nunk,d,f1,1,dd,indx);
		
		for(i=0;icnunk;i++)
		{
			sum+=fabs(fl[i]);
			x[ipuk[i]-1]- = fl[i] ;
		}
		nct++;
		printf("NCT= %d SUM= %f\r\n",nct,sum) ;
	}while((nct<20) && (sum>.001));
	
	if(npump)
	{
		if(in4) printf("Devices caused the following changes in heads\r\n");
		else fprintf(filo,"Devices caused the following changes in heads\n");
		
		for(i=0;icnpump;i++)
		{
		ii=ipump[i];
		dx=x[ii-l+nj2];
		
		if(in4)printf("Device %3d in pipe %4d Change in head = % 8 .3f\r\n",i+1,ii,(ap[i]*dx+bp[i])*dx+cp[i]);
		else fprintf(filo,"Device %3d in pipe %4d Change in head = % 8 .3f\n",i+1,ii,(ap[i]*dx+bp[i])*dx+cp[i]);
		}
	}
	if(in4) 
	{
		printf("Pipe Data:\r\n");
		for(i=0;i<65;i++)printf;
		printf("\r\n");
		printf("Pipe Node Node	Length Diameter Roughness Flowrate Headloss\r\n") ;
		printf(" No.#1	#2		Coef.\r\n");
		for(i=0;i<65; i+ + ) printf("-");printf("\r\n");
	} 
	else 
	{
		fprintf(filo,"Pipe Data:\n");for(i = 0 ;i<65;i++) fprintf(filo,"-"); fprintf(filo,"\n") ;
		fprintf(filo,"Pipe Node Node Length	Diameter Roughness	Flowrate Headloss\n") ;
		fprintf(filo," No.	#1	#2	Coef.\n");
		
		for(i=0;i<65;i++) fprintf (filo, ; fprintf(filo,"\n");
	}
	
	for(i=0;icnp;i++)
	{
		ii=ll[i] ;if (ii<0) ii=0;
		if(in4)
			printf("%4d %4d %4d %9.1f %9.3f %9.6f %9.3f % 9 .3f\r\n",i+1,ii,1 2 [i],1[i] ,x	[njp+i], x[njp2+i],x[nj2+i],hi [i]);
		else
			fprintf(filo,"%4d %4d %4d %9.1f %9.3f %9.6f %9.3f % 9 .3f\n",i + 1,ii,1 2 [i] , 1 [i] ,x [njp+i] ,x[njp2+i],x[nj 2+i] ,hi[i]);
	}
	
	if(in4)
	{
		printf("Node Data:\r\n");
		for(i=0;i<54;i++)printf("-");
		printf("\r\n");
		printf(" Node Demand Elevation Head Pressure HGL-elev.\r\n") ;
		for(i = 0 ;i<54;i++)printf("-") ;
		printf("\r\n");
	} 
	else 
	{
		fprintf(filo,"Node Data:\n");for(i = 0;i<54;i++)fprintf(filo,"-") ; fprintf (filo, "\n")
	}

	fprintf(filo," Node Demand ElevationHead Pressure HGL-elev.\n");");
	for(i=0;i<54;i++)
		fprintf(filo,"-");
	fprintf(filo,"\r\n") ;

	}
	for(i=0;i<nj ; i++)
	{
		xx=x[i]-elev[i] ;
		if(in4)
			printf("%5d %9.3f %9.3f %9.3f %9.3f % 9 .3f\r\n",i+1,x[nj+i],elev[i] ,xx, conv*xx, x[i] ) ;
		else 
			fprintf(filo,"%5d %9.3f %9.3f %9.3f %9.3f % 9 .3f\n",i + 1,x[nj+i],elev[i] ,xx,conv*xx,x[i]);
	}
}
#define TINY 1.0e-20;
void dcompos (float a[][k2],int n,int indx[], float d) 
{
	int i,imax,j,k;
	float aamax, drnn, sum, temp;
	float * w ;
	w = (float*) calloc (n,sizeof (float)) ; d=1.0;
	for(i=0;i<n;i++) 
	{
		aamax=0.0;
		for(j = 0;j<n;j++) 
			if ((temp=fabs(a[i] [j])) > aamax) aamax=temp;

		if (aamax == 0.0) 
			printf("Singular matrix in routine DCOMPOS\n");
			w[i] =1.0/aamax;
	}
	for (j =0;j<n;j++)
	{
		for(i=0;i<j;i++)
		{
			sum=a[i][j];
			for(k=0;k<i;k++) 
				sum -= a[i][k]*a[k][j];
			a[i] [j] =sum;
		}
		aamax=0.0;
		
		for(i=j;i<n;i++)
		sum=a[i][j];
		{
		for(k=0;k<j;k++)sum -= a[i] [k]*a[k] [j];
		a[i] [j] =sum;
		if ( ( d u m = w [i] *fabs (sum)) >= aamax) {
		aamax=dum;imax=i;
		}
		}
		if (j != imax) 
		{
				for(k=0;ken;k++) 
				{
					dum=a[imax] tk] ;a [imax] [k]=a[j] [k] ;
					a [j] [k]=dum;
				}
			d = -(d);
			w[imax] = w[j];
		}
		indx[j]=imax;
		if (a[j] [j] == 0.0) 
			a[j][j]=TINY;
		if (j != n) 
		{
			dum=l.0/(a[j] [j]) ;
			for(i=j+l;i<n;i++) a[i][j] *= dum;
		}
	}
	free (w) ;
}

#undef TINY

void finsol(float a[][k2],int n,int indx[],float b[])
{
	int i,ii,ip,j;
	float sum;
	ii=-l;
	for(i=0;i<n;i++) 
	{
		ip=indx[i];
		sum=b[ip];
		b [ip] =b [i] ;
		if (ii!= -1)
		{
			for(j=ii;j<i;j++) sum -= a [i][j] *b [j] ;
		} 
		else if (sum!=0.) 
			ii=i;
		b[i]=sum; 
	}
	for(i=n-1;i>=0;i--) 
	{
		sum=b[i];
		if (i < (n-1))
		{
			for (j =i+l;j<n;j ++) sum -= a[i][j]* b[j] ;
		}
		b[i] =sum/a[i][i];
	}
}


void solveq(int n, float a[][k2], float b[],int itype,float &dd,int indx[])
{
	int detrm=0,eqsol=0,invsol=0,i ,j ; 
	FILE *fil;

	if ((itype==3)||(itype>4)) detrm=l;
	if ((itype==l)||(itype==4)||(itype==6)) eqsol=l;
	if ((itype==2)||(itype>3)) invsol=l;

	dcompos(a,n,indx,dd);

	if(detrm) 
		for(i=0;i<n;i++) dd*=a[i][i];
	if(eqsol) 
		finsol(a,n,indx,b);
	if(invsol)
	{
		if(eqsol)
		{
			printf("\nSolution Vector\n");
			for(i=0;i<n;i++)
			{
				printf("%10,3f",b [i]);
				if (!(i%8)) 
					printf("\n");
			}
		}
		if ((fil=fopen("OMARIN","wt"))==NULL)
		printf("Data file OMARIN cannot be opened\n");
		for(j = 0;j <n;j++)
		{
			for(i=0;i<n;i++) b[i]=0;
			b [j] =1;

			finsol(a,n,indx,b);

			for(i=0;i<n;i++) fprintf(fil,"%15.7f",b[i]);
		}

		rewind(fil);

		for(j=0;j<n;j++) for(i=0;icn;i++) fscanf(fil,"%15.7f",a[i][j]);
		fclose(fil); remove("TEMP.DAT");
	}
	return;
}
