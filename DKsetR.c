
/* DKsetR.c */


#define XPEE 6
#define XPEf 720
#define XPBX 64
#define XRMX 17000
static PNUM PEE,PEf,PBX,RVAL;

static bool DUPLI[DCX];
static PNUM RAIZ[DCX];
static PNUM  SZ[DCX];
static PNUM QLE[DCX];
static PNUM QGE[DCX];
static I8 PPsmall[XPEf][XPEE];
static I8 PPbig[XPEf][XPBX];
static PNUM RRR[XRMX];
static U64 APO[XRMX];


void DRfillPP(int e)
{
I8 PPcifra[XPEE];
I8 BITPBX[XPBX];
I8 d;
I16 perm,dig;
bool ok;
PNUM s,nx,t;
printf("DRfillPP DKsetR.c \n");
PEE=e;PEf=factorial(e);PBX=PW2[e];
printf("QQ matrix. PEE %d PEf %d PBX %d \n"
,PEE,PEf,PBX);
assert(PEE LE XPEE);assert(PEf LE XPEf);
assert(PBX LE XPBX);

perm=0;nx=pow(10,e);
for(PNUM n=0;n<nx;n++)
  {
  t=n;ok=TRUE;
  for(I8 c=0;c<e;c++)
    {dig=t%10;if(dig GE e){ok=FALSE;break;}
    PPcifra[c]=dig;t/=10;
    }
  if(!ok)continue;

  for(I8 c=0;c<e;c++)
   for(I8 f=c+1;f<e;f++)
    if(PPcifra[c] EQ PPcifra[f])
      {ok=FALSE;break;}

  if(!ok)continue;

  for(I8 c=0;c<e;c++)
    PPsmall[perm][c]=PPcifra[c];
  perm++;if(perm GE PEf)break;
  }
assert(perm EQ PEf);
printf("Permutaciones e!.\n");

for(int p=0;p<PEf;p++)
  {for(int n=0;n<PBX;n++)
    {PPbig[p][n]=0;
    for(int b=0;b<PEE;b++)
      {d=PPsmall[p][b];BITPBX[d]=nbiti(n,b);
      }
    s=0;
    for(int b=0;b<PEE;b++)
      {if(BITPBX[b])s+=PW2[b];
      }  
    PPbig[p][n]=s;
    }
  }
printf("Permutaciones calculadas.\n");
}    


PNUM DRfillDRS(void)
{
LNUM GLBPPX[XPEf];
bool GLBNUL[XPEf];
I8   BITPBX[XPBX];
LNUM Ci,cmx;
I16 sze;
const int trz=1000000;

printf("DRfillDRS DKsetR.c \n");
assert(iC>0);

#pragma omp parallel for
for(PNUM i=0;i<DCX;i++)
  {
  DUPLI[i]=FALSE;SZ[i]=0;RAIZ[i]=0;
  }


printf("Generando R... \n");

for(PNUM iii=0;iii<iC;iii++)
  {
  if(iii%trz EQ 0)printf(" %d",iii/trz);
  if(DUPLI[iii])continue;

  cmx=C[iC-1];Ci=C[iii];
  for(I16 p=0;p<PEf;p++)
    {
    LNUM s;
    GLBPPX[p]=0;
    for(I16 b=0;b<PBX;b++)BITPBX[b]=0;

    for(I16 b=0;b<PBX;b++)
      {
      I8 d;
      d=PPbig[p][b];BITPBX[d]=nbiti(Ci,b);
      }
    s=0;
    for(I16 b=0;b<PBX;b++)s+=BITPBX[b]*PW2[b];
    GLBPPX[p]=s;
    }

  for(I16 i=0;i<PEf;i++)GLBNUL[i]=FALSE;
  for(I16 i=0;i<PEf;i++)
    {
    LNUM s;
    s=GLBPPX[i];
    for(I16 j=i+1;j<PEf;j++)
      {if(!GLBNUL[j] AND
        (GLBPPX[j] EQ s))GLBNUL[j]=TRUE;
      }
    }
  sze=0;
  for(I16 i=0;i<PEf;i++)
    {
    if(GLBNUL[i])continue;
    GLBPPX[sze++]=GLBPPX[i];
    }

  for(I16 i=0  ;i<sze;i++)GLBNUL[i]=0;
  for(I16 i=sze;i<PEf;i++)GLBNUL[i]=1;

  assert(sze GE 1);
  assert((PEf%sze) EQ 0);
  SZ[iii]=sze;RAIZ[iii]=iii;

  for(I16 p=0;p<sze;p++)
    {
    PNUM j;LNUM s;
    assert(!GLBNUL[p]);s=GLBPPX[p];
    if( (s EQ Ci)OR(s GT cmx)OR((s%2) EQ 0)
      OR(s LE Ci) )continue;
    j=DfindCi(0,(iC-1),s);
    assert(j NE iii);
    DUPLI[j]=TRUE;RAIZ[j]=iii;SZ[j]=sze;
    }
  }


  {
  PNUM ctd,sorb,ri,pore;
  U64 porb;

  newl();printf("Verificando SZ. \n");
  ctd=0;sorb=0;
  for(PNUM i=0;i<iC;i++)
    {
    if(DUPLI[i])continue;
    sorb+=SZ[i];RRR[ctd++]=i;
    }

  RVAL=ctd;
  assert(sorb EQ iC);
  printf("Checked SumOrb = iC. \n");

  printf("RVAL.  wC %d iC %d Rval= %d \n"
    ,wC,iC,RVAL);

  sorb=0;porb=1;
  pore=0;
  for(PNUM i=0;i<RVAL;i++)
    {
    ri=RRR[i];
    sorb+=SZ[ri];
    porb*=SZ[ri];

    while(porb>0 AND (porb%PEf) EQ 0)
      {porb/=PEf;pore++;}
    }
  printf("sumaorb= %8d   \n",sorb);
  printf("porb %I64d \n",porb);
  printf("pore %d PEf %d \n",pore,PEf);
  }

return RVAL;
}

void Rcheckcomon(void)
{
BNUM sumQLE=0,sumQGE=0;
PNUM sumsz=0;

printf("Rcheckcomon \n");
for(PNUM i=0;i<iC;i++)
  {
  sumQLE+=QLE[i];sumQGE+=QGE[i];
  }
assert(sumQLE EQ sumQGE);
printf("Checked QQ.\n");

for(PNUM i=0;i<iC;i++)
  {
  PNUM raiz=RAIZ[i];
  assert(SZ[i] GT 0);assert(QLE[i] GT 0);
  assert(QGE[i] GT 0);
  if(DUPLI[i])
    {
    assert(!DUPLI[raiz]);
    assert(SZ[i] EQ SZ[raiz]);    
    assert(QLE[i] EQ QLE[raiz]);    
    assert(QGE[i] EQ QGE[raiz]);    
    }
  else
    {assert(raiz EQ i);sumsz+=SZ[i];
    }
  }
assert(sumsz EQ iC);
printf("Checked iC structures.\n");

for(PNUM i=0;i<RVAL;i++)
  {
  PNUM ri=RRR[i];assert(!DUPLI[ri]);
  assert(RAIZ[ri] EQ ri);
  }
printf("Checked RVAL structures.\n");
}


void DRfillQQ(void)
{
const int trz=1000;
printf("DRfillQQ DKsetR.c \n");

#pragma omp parallel for
for(PNUM i=0;i<DCX;i++)
  {QLE[i]=0;QGE[i]=0;
  }

printf("Fill QQ.\n");
printf("DR scan up/down \n");
#pragma omp parallel for ordered
  for(PNUM i=0;i<RVAL;i++)
    {
    PNUM ri=RRR[i];
    QLE[ri]=DRskanup(ri);
    QGE[ri]=DRskandown(ri);
    if(i%trz EQ 0)
      {
#pragma omp critical
      printf(" %d",i/trz);
      }
    }

newl();printf("Copiando pares. \n");

#pragma omp parallel for ordered
for(PNUM i=0;i<iC;i++)
  {
  if(DUPLI[i])
    {QLE[i]=QLE[RAIZ[i]];QGE[i]=QGE[RAIZ[i]];}
  }
printf("QQ filled. \n");
}


U64 DandorQQ(PNUM pp)
{
LNUM aa,bb,mitab,jonab;
PNUM ii,mj,mk,n,nm1,mjp,mkp,cj,rmit,sjon;
U64 apo,rs,tmp;

apo=0ll;cj=0;
mjp=0;mkp=0;ii=pp;aa=C[ii];n=iC;nm1=n-1;
for(PNUM j=0;j<iC;j++)
  {
  cj++;
  bb=C[j];
  mitab=(aa&bb);mj=mjp+1;
  if(mitab NE C[mj])mj=DfindCi(0,ii,mitab);
  rmit=QLE[mj];mjp=mj;

  jonab=(aa|bb);mk=mkp+1;
  if(jonab NE C[mk])mk=DfindCi(ii,nm1,jonab);
  sjon=QGE[mk];mkp=mk;

  rs=(U64)rmit;
  rs*=(U64)sjon;
  tmp=apo;apo+=rs;
  assert(apo GT tmp);
  }
assert(cj EQ iC);
return apo;
}


#define RV32MX 2147483647L
#define RV64MX 9223372036854775807ll

typedef struct
  {
  I64 W[2];
  } RDI64;
typedef union
  {
  U128 L;
  RDI64 D;  
  } RUS128;

void DRx4magic(PNUM R)
{
PNUM TC[TASKMX];

printf("DRx4magic DKsetR.c  \n");
printf("Calculando APOs. \n");

for(int i=0;i<TASKMX;i++)TC[i]=0;

#pragma omp parallel for
for(PNUM i=0;i<XRMX;i++)APO[i]=0LL;

#pragma omp parallel for ordered 
for(I32 i=0;i<RVAL;i++)
  {
  U64 v;I32 ri;

  ri=RRR[i];v=DandorQQ(ri);

#pragma omp critical
    {
    int tnum;PNUM TCS;

    APO[i]=v;
    tnum=omp_get_thread_num();
    TC[tnum]++;
    if(tnum EQ 0)
      {
      TCS=0;
      for(int i=0;i<TASKMX;i++)TCS+=TC[i];
      printf(" %d",TCS);
      }
    }
  }

  {
  FILE *f;PNUM ri;int tnum;

  newl();
  tnum=omp_get_num_threads();
  assert(tnum EQ 1);

  f=fopen("APOS.LOG","w");
  for(PNUM i=0;i<RVAL;i++)
    {
    ri=RRR[i];
    fprintf(f,"%6d %I64d \n",SZ[ri],APO[i]);
    }
  fclose(f);
  printf("filed LOG \n");
  }

#pragma omp master
  {
  U128 sum,tmp,sapo;
  U64 ss;
  PNUM TCS;

  sum=0LL;sapo=0LL;
#pragma omp critical
  for(PNUM i=0;i<RVAL;i++)
    {
    ss=(U64)SZ[RRR[i]];

    tmp=0LL;tmp=ss;
    ss=(U64)APO[i];
    sapo+=(U128)ss;
    tmp*=(U128)ss;assert(tmp GT 0LL);
    sum+=(U128)tmp;assert(sum GT 0LL);
    }
  printf("d%d= \n",PEE+2);
  print128(sum);
  printf("Sum APO = \n");
  print128(sapo);

  TCS=0;for(int i=0;i<TASKMX;i++)TCS+=TC[i];
  printf("TCS %d \n",TCS);
  assert(TCS EQ RVAL);
  }
}



void DRdemo(int ee)
{
PNUM P;int e;

e=ee;
printf("DRdemo DKsetR.c \n");
DKCe0();for(int i=0;i<e;i++)DKCx2();
iC1=iC-1;eC=e;
printf("C%d= %d \n",e,iC);
DRfillPP(e);
DKbfillCi();
P=DRfillDRS();
printf("R(%d)=[%d*%d] \n",e,wC,P);
DRfillQQ();
Rcheckcomon();
DRx4magic(P);
}


