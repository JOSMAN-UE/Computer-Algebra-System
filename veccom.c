

/*** VECCOM.C ******/

#define TBFX 16

typedef struct
  {
  PNUM i;
  LNUM C;
  } PAIR;
static PAIR TBI[TBFX];

typedef struct
  {
  U32 W[2];
  } LEQUW;
typedef union
  {
  LNUM L;
  LEQUW V;  
  } LEQLL;




bool Dleq(LNUM pa,LNUM pb)
{
LEQLL ua,ub,und;

ua.L=pa;ub.L=pb;

und.V.W[0]=(ua.V.W[0] & ub.V.W[0]);
if(und.V.W[0] NE ua.V.W[0])return 0;
und.V.W[1]=(ua.V.W[1] & ub.V.W[1]);
if(und.V.W[1] NE ua.V.W[1])return 0;

return 1;
}

void DKbfillCi(void)
{
PNUM j,k;

j=0;k=floor((iC-1)/TBFX);
for(U8 i=0;i<TBFX;i++)
  {
  assert(j<iC);
  TBI[i].i=j;TBI[i].C=C[j];
  j+=k;
  }
TBI[0].i=0;TBI[0].C=C[0];
TBI[TBFX-1].i=iC-1;TBI[TBFX-1].C=C[iC-1];
printf("Filled TBI bfind. \n");
}

PNUM DfindCi(PNUM ini,PNUM ult,LNUM wtf)
{
PNUM i,n,nm1;
LNUM se,Cmi; 
PNUM fi,la,mi,di;

se=wtf;n=iC;nm1=n-1;
fi=ini;la=ult;
while(fi LE la) 
  {
  di=(la-fi);di=di>>1;mi=fi+di;
  Cmi=C[mi];
  if(se GT Cmi){fi=mi;fi++;}    
  else if(se LT Cmi){la=mi;la--;}
  else
    {
    assert(C[mi] EQ wtf);
    return mi;
    }
  }
assert(se GE C[0]);
assert(se LE C[nm1]);
printf("ABORT DfindCi \n");
exit(0);
}

static int DKcmpC(const void *c,const void *d);
static int DKcmpC(const void *c,const void *d)
{
LNUM cc,dd;

cc=*(LNUM*)c;dd=*(LNUM*)d;
if(cc LT dd)return -1;
else if(cc GT dd)return +1;

return 0;
}


PNUM DbsearchC(LNUM wtf)
{
PNUM dif;
LNUM balue,*pres;

const LNUM *pbal=&balue;
const LNUM *base=&C[0];
int (*fuu)(const void*,const void*)=DKcmpC;
const size_t esz=sizeof(C[0]);
const size_t vsz=(size_t)iC;

balue=wtf;
pres=bsearch(pbal,base,vsz,esz,fuu);
if(pres EQ NULL)return 0;
dif=(pres-base);
assert(C[dif] EQ wtf);

return dif; 
}


PNUM DRskanup(PNUM pp)
{
LNUM vab;PNUM p,c;

c=0;p=pp;vab=C[p];
for(PNUM k=0;k<=p;k++)
  {
  if(Dleq(C[k],vab))c++;
  }
return c;
}

PNUM DRskandown(PNUM pp)
{
LNUM vab;PNUM p,c;

c=0;p=pp;vab=C[p];
for(PNUM k=p;k LE iC1;k++)
  {
  if(Dleq(vab,C[k]))c++;
  }
return c;
}


PNUM Xlen(char *p)
{
PNUM r;

r=strlen(p);
return r;
}

void newl(void)
{
printf("\n");
}

void newline(int p)
{
int i;
for(i=0;i<p;i++)newl();
}

void kbflu(void)
{
while(kbhit())getch();
}


I64 askB(void)
{
I64 B,tmp;
char line[SXLEN];
int slen,lx;

B=0;
while(B<1)
  {
  lx= 16;newl();
  printf(
"       nnnnnnnnnDnnnnnn (16) \n");
  printf(
"  int> ");
  scanf("%s",line);slen=strlen(line);
  if(slen>lx)printf(
" toobig %d digits. ",slen);
  newl();
  if(slen<1 || slen>lx)continue;
  tmp=_atoi64(line);
  /* atoll(line) */
  B=tmp;
  }
return B;
}


void tmark(time_t *p)
{
time(p);
}

I32 lapsed(time_t *p)
{
time_t a,b;
I64 v;
I32 r;
a=*p;time(&b);v=difftime(b,a);
r=(I32)v;

return r;
}

LNUM DKpot(int e)
{
LNUM r;

r=1;
r=r<<e;
return r;
}

U64 potex(U64 a,U64 p) 
{
U64 r;

r=1;
while(p) 
  {
  if((1 & p))r=r*a;
  a*=a;p>>= 1;
  }
return r;
}

I64 expceil(U64 pp)
{
U64 n,l;

n=pp;l=3;while(potex(2,l)<n)l++;
return l;
}


bool ispot2(I64 pp)
{
I64 n; 

n=pp;
while(n GT 1 AND n%2 EQ 0)n/=2;
if(n EQ 1)return TRUE;
return FALSE;
}

void DKsortC(void)
{
int (*p)(const void*,const void*);
size_t esz,vsz;

p=DKcmpC;
esz=sizeof(C[0]);vsz=(size_t)iC;
qsort(&C[0],vsz,esz,p);
}

void DKbin(LNUM p)
{
LNUM n;
char ch;

n=p;
for(int b=DKdev;b>=0;b--)
  {
  ch='0';
  if((n&PW2[b]) NE 0)ch='1';
  printf("%c",ch);
  if(b%4 EQ 0)printf(" ");
  }
newl();
}

PNUM factorial(int e)
{
PNUM f;

f=1;
for(int i=2;i<=e;i++)f*=i;
return f;
}

void print128(I128 p)
{
const int BX=40,cc=10;
char buf[BX];
const char CHZ='0';
int k,m;
I128 n;

n=p;
for(int i=0;i<BX;i++)buf[i]=CHZ;
k=BX-1;buf[k]=0;
while(n NE 0)
  {
  m=n%cc;buf[--k]=CHZ+m;
  n=(n-m);n=n/cc;
  }

printf("%s \n",buf);
}

int Imaxim(int a,int b)
{
if(a>b)return a;
return b;
}

int Iminim(int a,int b)
{
if(a<b)return a;
return b;
}

bool nbiti(LNUM n,PNUM b)
{
LNUM v;

v=n&PW2[b];if(v NE 0)v=1;
return v;
}

void pause(void)
{
char ch;

kbflu();
printf(
"PAUSED. Letter A to ABORT.");
ch=getch();
if(ch EQ 'A')exit(1);
kbflu();
printf("RESUMED. \n");
}

void kbcheck(void)
{
int x;

x=kbhit();
if(x EQ 0)return;
pause();
}

void configOMP(void)
{
int v;

omp_set_num_threads(1);
v=omp_get_num_procs();
printf("OpenMP on N.Cores: %d \n",v);
omp_set_nested(0);
omp_set_dynamic(0);
omp_set_schedule(omp_sched_static,1);
omp_set_max_active_levels(1);
omp_set_num_threads(v);
}

void checkOMP(void)
{
PNUM ncores,ntask;

ncores=omp_get_num_procs();
ntask=omp_get_num_threads();
assert(ntask EQ 2*ncores);
printf("N.Cores: %d \n",ncores);
}


void showWS(void)
{
int v;

v=omp_get_num_procs();
printf("N.PROCS: %2d  \n",v);
printf("WS. N: %I64d. \n",NN);
newl();
}


void showCOM(int ready)
{
if(!ready)return;

newl();
printf("N= ");
for(int i=0;i<NUMFAC;i++)
  {
  printf("(%I64d^%I64d)",VFAC[i],VEXP[i]);
  }
newl();

if(ISPRIME) printf(" PRIME NUMBER.");
if(ISFLAT)  printf(" FLAT.");
if(ISSQUARE)printf(" SQUARE.");
if((SIGMA%NN) EQ 0)printf(" PERFECT NUMBER.");
printf("\n");

printf(
"NUMDIV= %I64d. NUMFAC=%I64d. \n"
,NUMDIV,NUMFAC);

printf("SIGMA= %I64d. \n",SIGMA);
printf("TOTIENT= %I64d. \n",TOTI);

printf("N= (%I64d^2)+(%I64d). \n",ROTI,ROTE);
if(SQUAREN>1)printf(
"N= (%I64d)(%I64d^2). \n",FLATN,SQUAREN);
if(F2EXP>0)printf(
"N= (2^%I64d)(%I64d) \n",F2EXP,ODDN);
printf("\n");
}

char askcmd(void)
{
char cm1;

kbflu();
do 
  {
  newl();printf("cas> ");
  cm1=getche();if(cm1>32)break;
  showWS();
  printf("  q: quit \n");
  } while(1);
newl();  
if(cm1 EQ 'q')exit(0);

return cm1;
}




