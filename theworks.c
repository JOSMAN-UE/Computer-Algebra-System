

/*** WORKS.C ******/


void Colatz(void)
{
I64 t,e0,e,es,g,pad;
I64 M,n,D,prod,step;

e0=NN;M=0;step=0;pad=1;e=e0;
printf("Colatz. \n");
do
  {
  kbcheck();

  step++;t= 3*e+1;es=t;
  g=0;
  while(es>1 && es%2 EQ 0)
    {
    es/=2;g++;
    }
  M+=g;

  printf(
"(%I64d): %I64d *(3^ %I64d )+ %I64d = %I64d *(2^%I64d)\n"
,step,e0,step,pad,es,M);

  e=es;
  if(e EQ 1)break;
  pad=3*pad+(potex(2,M));e=es;

  }while(1);

newl();

n=NN;e=pad;M=0;D=1;prod=0;step=0;
printf("Mersenne. \n");
do
  {
  kbcheck();

  step++;t= n+e;es=t;
  g=0;
  while(es>1 && es%2 EQ 0)
    { es/=2;g++;
    }

  M+=g;

printf("(%I64d) %I64d+%I64d = %I64d*(2^%I64d) \n"
,step,n,e,es,g);
printf("  D %I64d \n",D);

  if(es NE 1)
    {
    prod+=g;
    D+=potex(2,prod);
    }

  e=es;
  }while(e NE 1);

printf("  2^M() - pad = N*D \n");
printf("  bits(3^pasos-colatz) = pasos-Mersenne. \n");

newl();
}


I64 mifunM(I64 pp,bool traza)
{
I64 nn,im0,im,tt,g,gg;
I64 stp,prod,dd,comu;

nn=pp;
if(nn%2 EQ 0)return 0;

im0=1;
gg=0;stp=0;prod=1;dd=1;
im=im0;
while(1)
  {
  kbcheck();
  tt=nn + im;
  stp++;g=0;
  while(tt>1 && (tt%2 EQ 0))
    {
    tt/=2;g++;
    prod*=2;
    }
  gg+=g;
  comu=gcd(nn,dd);
  if(traza)
   if((stp<6) OR (tt EQ im0) OR (comu NE 1))
    {

printf(
"(%I64d) %I64d + %I64d = %I64d *(2.%I64d)" 
,stp,nn,im,tt,g);

printf(",gcd: %I64d. \n",gcd(nn,dd) );
printf("dd: %I64d, prod: %I64d. \n",dd,prod);
    }
  im=tt;
  if(im EQ   1)break;
  if(im EQ im0)break;
  assert(gcd(nn,im) EQ 1);
  dd+=prod;
  if(dd<1){dd=1;prod=0;}
  }
printf(" 2^M()-1 = N*D \n");

ZVAL=gg;ZPAS=stp;ZDD=dd;
return gg;
}

void fPQRS(void)
{
I64 su,re,p,q,r,s; 

newl();COLdivs();
for(int i=0;i<NUMDIV;i++)
  {
  printf(" %I64d",VDIV[i]);
  }
newl();

for(int i=    0;i<NUMDIV;i+=2)
for(int j=(i+2);j<NUMDIV;j+=2)
  {
  re=VDIV[i+1]-VDIV[i];
  su=VDIV[j+1]+VDIV[j];
  if(su EQ re)
    {
    printf("N es Congruente. N PQRS. \n");
    r=VDIV[i];s=VDIV[i+1];
    p=VDIV[j];q=VDIV[j+1];
    printf(
"N=(%I64d)*(%I64d)=(%I64d)*(%I64d+%I64d+%I64d)\n"
,p,q,r,p,q,r);
printf(
"N-Squares: (%I64d)->(%I64d)->(%I64d).\n"
,q-p,s-r,r+s);

printf("pq=r(p+q+r) \n");
printf(" [q-p] [s-r] [r+s] \n");
    }
  }
newl();
}


void RDEdivs(I64 dist,I64 refe)
{
I64 n,L;

n=dist;DEN=0;
L=sqrt(n);
if(n<60)L=n;
for(I64 d=1;d<=L;d++)
  {
  if(n%d NE 0)continue;
  if(DEN>MX)break;
  TDE[DEN++]=d;
  TDE[DEN++]=(n/d);
  }

n=refe;DRR=0;
L=sqrt(n);
if(n<60)L=n;
for(I64 d=1;d<=L;d++)
  {
  if(n%d NE 0)continue;
  if(DRR>MX)break;
  TRR[DRR++]=d;
  TRR[DRR++]=(n/d);
  }
}


I64 fRDE(I64 refe)
{
I64 N,R,de,dea,ASOL,tmp;

N=NN;R=refe;de=R-N;
dea=de;if(dea<0)dea=-dea;
if(dea EQ 0)return 1;

tmp=gcd(N,R);if(tmp>1)return tmp;
tmp=gcd(N,dea);if(tmp>1)return tmp;

RDEdivs(dea,R);
ASOL=1;
for(int i=0;i<DEN;i++)
  {
  I64 d,e;

  d=TDE[i];e=de/d;
  for(int j=0;j<DRR;j++)
    {
    I64 R1,R2;

    R1=TRR[j];R2=R/R1;
    for(int r=-1;r<2;r+=2)
    for(int s=-1;s<2;s+=2)
      {
      I64 Ab,Ac,A,tmp;

      Ab=r*R1-s*d;Ac=r*R2-s*e;
      if(Ab*Ac EQ 0)continue;
      A=gcd(Ab,Ac);
      if(A<0)A=-A;
      if(A<2)continue;
      tmp=gcd(ASOL,A);
      if(tmp EQ 0)continue;
      if(tmp NE A)
        {
        ASOL*=(A/tmp);

        assert(A NE 0);
        assert((N%A) EQ 0);
        assert(ASOL NE 0);
        assert((N%ASOL) EQ 0);

        printf(
"Ref:(%I64d+%I64d)(%I64d+%I64d)=> %I64d \n"
,Ab,s*d,Ac,s*e,A);
        }}}}

printf(" Ref=(Ab+d)(Ac+e); \n");
printf("   N=(A)(Abc+be+cd); \n");

return ASOL;
}


I64 fNBPmers(void)
{
I64 e,e2,div;

e=NN;
e2=2*e;

if(!isprime(e,1))
  {
  printf("Exponent not prime. \n");
  return 1;
  }

printf("Mers(%I64d): \n",e);

for(div=(1+e2);div>0;div+=e2)
  {
  I64 a,t,i,lmin,l,ma,p,pot,pott,ml;
  I64 si,patt,plsi,sp,vmin,lop;

  kbcheck();
  if(lapsed(&CMDmark)> MXSEC )break;

  if(!isprime(div,1))continue;

  lmin=expceil(div);
  vmin=0;lop=lmin;
  for(l=lmin;l<e;l++)
    {
    I64 v;

    kbcheck();
    a=e%l;t=(e-a)/l;v=l*t;
    if((vmin EQ 0) || (v<vmin))
      {vmin=v;lop=l;}
    }

  l=lop;
  a=e%l;t=(e-a)/l;
  pot=potmod(2,l,div);
  ml =pot-1;
  ma =potmod(2,a,div)-1;

  si=0;p=1;
  for(i=0;i<t;i++)
    {
    kbcheck();

    si+=p;si%=div;
    p=(p*pot)%div;
    }
  pott=p;
  patt=(ma)*(pott);patt%=div;
  plsi=(ml)*(si);plsi%=div;
  sp=patt+plsi;sp%=div;
  if(sp NE 0)continue;


  newl();
  printf(
"SOL. Mers(%I64d): div= %I64d. \n"
,e,div);

  return div;
  }
printf("S= M.a*Pot.b + M.l*(SUM pot.i) \n");
printf("div|S \n");

return 1;
}

I64 pqLXN(I64 pp)
{
I64 n,l,a,b;

n=pp;
l=1;
do
  {
  a=l*(l+1);a=a/2;b=l*(l+3);b=b/2;
  if(n>=a && n<=b) break;
  l++;
  } while(l<n);

return l;
}


I64 pqCRENL(I64 mm,I64 pp)
{
I64 n,l,sum,iz,de,lx,nn,ll;

n=mm;l=pp;
if(n<1)return 0;
if(l EQ 1)return 1;
if(l<1)return 0;

lx=pqLXN(n);if(l>lx)return 0;
if(n<5)return 1;
nn=n-l;
if( nn<1 )return 0;

if(l==2)
  {
  if(n%2==1) return (n-1)/2;
  else return (n-2)/2;
  }

ll=l-1;
iz=pqCRENL(nn,ll);de=pqCRENL(nn,l);
sum=iz+de;

return sum;
}

I64 pqFUNCIONQ(void)
{
I64 n,sum,l,lx;

n=NN;
if(n<1)return 0;
if(n<3)return 1;
if(n<5)return 2;

sum=0;
lx=pqLXN(n);
for(l=1;l<=lx;l++) sum+=pqCRENL(n,l);

return sum;
}


I64 pqFUNCIONP(void)
{
I64 p,i,s,f;

p=NN;
if(p<1)return 0;

s=0;for(i=1;i<=p;i++)s+=i;
f=pqCRENL(s,p-1)+1;

return f;
}


void eqnSTRAUS(void)
{
I64 n,m,nm,m4;
int td;

n=NN;if(n<0)n=-n;
if(n EQ 0)return;

newline(2);
printf("eqn. Straus. (Equiv.) \n");
printf("Para todo n, existe un m par tq \n");
printf("tres divisores de nm, suman 4m. \n");
printf("Con (4/n)=(4m/nm). \n");
newl();
m=2;
do
  {
  int td0;

  kbcheck();
  nm=n*m;m4=4*m;td=0;
  for(int d=1;d<=m;d++)
    if(nm%d EQ 0)TDE[td++]=d;

  td0=td;
  for(int i=0;i<td0;i++)
    if((n*TDE[i])<=m4)TDE[td++]=(n*TDE[i]);
  printf(" %I64d",m);

  for(int i= 0;i<td;i++)
    {
    for(int j= i;j<td;j++)
    {
    if((TDE[i]+TDE[j])>=m4)break;

    for(int k= j;k<td;k++)
    {
    I64 S,a,b,c,aa,bb,cc;

    kbcheck();
    aa=TDE[i];bb=TDE[j];cc=TDE[k];
    S=aa+bb+cc;if(S>m4)break;
    if(S<m4)continue;
    a=nm/aa;b=nm/bb;c=nm/cc;

    newl();
    printf(
"Para n %I64d, m= %I64d; 4m %I64d. nm %I64d. \n"
,n,m,m4,nm);
    printf("  divisores:(");
    for(int i=0;i<td;i++)printf(" %I64d",TDE[i]);
    printf(")\n");
    printf(
"  4m. 4*%I64d = %I64d+%I64d+%I64d. \n"
,m,aa,bb,cc);
    printf("  (1/%I64d)=(%I64d/nm);",a,aa);
    printf(" (1/%I64d)=(%I64d/nm);",b,bb);
    printf(" (1/%I64d)=(%I64d/nm); \n",c,cc);
    printf("  (4m/nm)=(1/%I64d)+(1/%I64d)+(1/%I64d) \n"
,a,b,c);
    printf(
"  (4/%I64d) = (1/%I64d)+(1/%I64d)+(1/%I64d). \n"
    ,n,a,b,c);
    newline(2);

    return;
    }}}
  m+=2;
  } while(m<=n);
}

