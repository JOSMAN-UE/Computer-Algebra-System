I64 multmod(I64 aa,I64 bb,I64 modu)
{
I64 a,b,m,r;

a=aa;b=bb;m=modu;
r=0;
while(b) 
  {
  if((1 & b))r=(r+a)%m;
  a=(2*a)%m;b>>=1;
  }

return r;
}


I64 potmod(I64 aa,I64 ee,I64 modu)
{
I64 a,p,m,r;

a=aa;p=ee;m=modu;
r=1;
while(p) 
  {
  if((1 & p))r=(r*a)%m;
  a=(a*a)%m;p>>=1;
  }

return r;
}





/* ******** NUMERIC ********** */



I64 gcd(I64 pa,I64 pb)
{
I64 lit,gre,tmp;

if(pa<pb){lit=pa;gre=pb;}
else     {lit=pb;gre=pa;}
while(lit NE 0)
  {
  tmp=gre%lit;
  gre=lit;lit=tmp;
  }

if(gre<1)gre=1;
return gre;
}

I64 lcm(I64 pa,I64 pb)
{
I64 a,b,g,r;

a=pa;b=pb;
g=gcd(a,b);
a/=g;b/=g;
r=a*b*g;

return r;
}


bool isprime(I64 pp,int usevec)
{
I64 divi,q,rl,isp;

q=pp;isp=1;
if(q>2 && q%2 EQ 0)isp=0;
else if(q>3 && q%3 EQ 0)isp=0;
else if(q>5 && (q%10) EQ 5)isp=0;
else if(q>7 && q%7 EQ 0)isp=0;
if(isp EQ 0)return isp;

rl=sqrt(q)+2;divi=11;
if(usevec)
  {
  for(int i=0;i<NUMPRIM;i++)
    {
    divi=VPRIMOS[i];
    if(divi>rl)
      {isp=1;return isp;
      }

    if(q>divi && ((q%divi) EQ 0))
      {isp=0;return isp;
      }
    }
  }

for(;divi<=rl;divi+=2)
  {
  if(q>divi && (q%divi) EQ 0)
    {isp=0;return isp;
    }
  }

isp=1;return isp;
}

void setVPRIMOS(void)
{
I32 LIM;

LIM= potex(2,20);
NUMPRIM=0;VPRIMOS[NUMPRIM++]=2;
for(I32 N=3;N<LIM;N+=2)
  {
  if(!isprime(N,0))continue;
  VPRIMOS[NUMPRIM++]=N;
  assert(NUMPRIM<MXPRIM);
  }
}

void factor(void)
{
I64 i,n,e,t,nmi,nfac,npen,ndiv;
I64 sdiv,ncop,roti,rote,oddp,flatn,squareN;
int exp2;
bool prim,flat,square;

n=NN;
if(n<1)return;

exp2=0;oddp=n;
while(oddp%2==0){exp2++;oddp/=2;}
roti=sqrt(n);rote=n-(roti*roti);

prim=TRUE;square=TRUE;flat=TRUE;
nfac=1;npen=n;ndiv=1;sdiv=1;
ncop=1;flatn=1;squareN=1;
NUMFAC=0;
for(i=2;(npen>1) AND (i<n);)
  {
  nmi=n%i;
  if((nmi EQ 0) AND isprime(i,1))
    {
    prim=FALSE;e=0;t=n;
    while(t%i EQ 0){e++;t/=i;nfac*=i;}
    npen=n/nfac;
    printf("(%I64d^%I64d)",i,e);
    VFAC[NUMFAC]=i;VEXP[NUMFAC]=e;
    NUMFAC++;

    if(npen EQ 1)printf(". \n");
    if(e>1)flat=FALSE;
    if(e%2==1)square=FALSE;

    ndiv*=(e+1);

    sdiv*=(potex(i,e+1)-1)/(i-1);
    ncop*=(potex(i,e-1))  *(i-1); 

    if(e>1 && e%2 EQ 0)
      {squareN*=potex(i,(e/2));
      }
    if(e>0 && e%2 EQ 1)
      {flatn*=i;squareN*=potex(i,e-1);
      }
    }

  if(i EQ 2)i=3;
  else if(isprime(npen,1))i=npen;
  else i+=2;
  }

if(prim)
  {
  NUMFAC=1;VFAC[0]=n;VEXP[0]=1;
  square=FALSE;flat=TRUE;ndiv=2;
  sdiv=n+1;ncop=n-1;flatn=n;squareN=1;
  }

ROTI=roti;ROTE=rote;F2EXP=exp2;ODDN=oddp;
ISPRIME=prim;ISFLAT=flat;ISSQUARE=square;
SIGMA=sdiv;NUMDIV=ndiv;TOTI=ncop;
FLATN=flatn;SQUAREN=squareN;
}

int COLdivs(void)
{
I64 n,i,j,roti,sdiv;
int ndiv;

n=NN;
ndiv=0;roti=sqrt(n);sdiv=0;
for(i=1;i<=roti;i++)
  {
  if(n%i==0)
    {
    j=n/i;if(i>j)break;
    if(i EQ j)
      {
      VDIV[ndiv++]=i;
      sdiv+=i;
      printf(" (%I64d) SQUARE \n",i);
      }
    if(i<j)
      {
      VDIV[ndiv++]=i;
      VDIV[ndiv++]=j;
      sdiv+=i+j;
      printf(" ( %I64d  %I64d ) \n",i,j);
      }
    }
  }
printf("NUMDIV %d \n",ndiv);
printf("SIGMA= %I64d \n",sdiv);

SIGMA=sdiv;NUMDIV=ndiv;
return ndiv;
}


void coprimes()
{
I64 n,i,t,tx;

n=NN;t=0;tx=40;
printf("N %I64d Coprimes:(",NN);
for(i=1;i<=NN;i++)
  { 
  if(t>tx){printf(" etc");break;}
  if( gcd(i,n)==1){printf(" %I64d",i);t++;}
  }
printf(")\n");
if(t<tx)printf("Totient= %I64d. \n",t);
}



