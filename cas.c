


/****  CAS.c **********/

/*****************************************
(C) J.M. Montolio Aranda. Spain. UE. 2020.
Related and derived fron own author works.
*****************************************/


#include "COMONS.C"

void funcMn(void)
{
I64 MN;
bool prim,partin;

newl();
if(NN%2==0)
  {
  printf("N not odd. \n");
  return;
  }

MN=mifunM(NN,TRUE);
prim=isprime(MN,1);
partin=FALSE;
if(2*ZPAS EQ (NN-1))partin=TRUE;

printf("Info. (2^M)-1=N*D. \n");
printf("N %I64d \n",NN);
printf(
"M(N)= %I64d. Prime:%d; Compl:%d. \n"
,ZVAL,prim,partin);
printf("ZPAS: %I64d (bits D); D=%I64d \n"
,ZPAS,ZDD);
printf("(2^%I64d)-1 = %I64d *%I64d \n"
,ZVAL,NN,ZDD);

}

void funcPQ(void)
{
I64 p,q;

newl();
p=pqFUNCIONP();
q=pqFUNCIONQ();
printf(
"N %I64d p()= %I64d q()= %I64d \n"
,NN,p,q);
}

void funcRDE1(void)
{
I64 R,S,U;

newl();
R=fRDE(NN-1);
S=fRDE(NN+1);
U=gcd(R,S);U=(R/U)*(S/U)*U;
printf("  Ambos-> factor %I64d \n",U);

}

void funcNBPmers(void)
{
I64 div,R;

div=fNBPmers();
if(div<3)
  {printf("Not found Divisor. \n");
  return;
  }

R=mifunM(div,FALSE);

printf(
"N %I64d Div= %I64d M(Div)= %I64d \n"
,NN,div,R);
assert(NN EQ R);
}

void nexprimN(void)
{
I64 v;

v=NN;v++;while(isprime(v,1) NE 1)v++;
NN=v;DREADY=FALSE;
}

void funcRSA(void)
{
I64 p,q,n,e,d,m,c,toti;

p=53;q=61;n=p*q;toti=(p-1)*(q-1);
e=17;

assert(isprime(e,1));
assert(gcd(e,toti) EQ 1);
assert(e<n);assert(e>1);

d=1;
while(d>0)
  {
  I64 t;

  t=e*d-1;
  if((t%toti) EQ 0)break;
  d++;
  }
printf("Calculado d= %I64d \n",d);
printf("n %I64d toti %I64d \n",n,toti);

printf("Cifrado RSA mediante n,e. \n");
m=35;
for(m=21;m<100;m+=20)
  {
  I64 t;

  c=potmod(m,e,n);
  printf("msg:%I64d ->cifr:%I64d \n",m,c);
  t=potmod(c,d,n);assert(t EQ m);
  }
}


void PRhelp(void)
{
newl();
printf("h:help; q:quit; w:workspace; \n");
printf("n:setN; x:neXt; \n");
printf("f:factor; s:sigma; c:coprimes;\n");
printf("\n");
printf("z:znorder; p:partition;\n");
printf("r: RDE; 1: eqn.Straus. 2: NBPmers;\n");
printf("3: RSA; 4: eqn.Colatz. \n");
newl();
printf("5: Dedekind; \n");
showWS();
}

void PRintro(void)
{
newl();
printf("CAS/BI Version BETA. \n");
printf("Related to Author works. \n");
printf("Use h for help \n");
newline(2);
}

int main(void)
{

PRintro();
configOMP();
NN=0;DREADY=FALSE;
setVPRIMOS();
printf(
"Loaded %I64d small factors. \n",NUMPRIM);

MXSEC=5;
while(1)
  {
  char cm1;

  cm1=askcmd();

  tmark(&CMDmark);

  if(!DREADY)factor();
  switch(cm1)
    {
    case 'n':
      {
      NN=askB();
      factor();DREADY=TRUE;
      }
      break; 
    case 'h':PRhelp();break;
    case 'w':showWS();break;
    case 'x':
      {
      nexprimN();showWS();
      factor();DREADY=TRUE;
      }
      break;
    case 'f':
      { 
      if(!DREADY)factor();
      DREADY=TRUE;
      showWS();showCOM(DREADY);
      }
      break;

    case 's':fPQRS();break;
    case 'z':
      {
      funcMn();

      if(DREADY AND ISPRIME)
        {
printf("(N-1): %I64d =",NN-1);
printf(" %I64d*Tot \n",(NN-1)/TOTI);
printf("Tot = %I64d*M \n",TOTI/ZVAL);
        }
      }
      break;

    case 'c':newl();coprimes();break;
    case 'p':funcPQ();break;
    case 'r':funcRDE1();break;
    case '1':eqnSTRAUS();break;
    case '2':funcNBPmers();break;
    case '3':funcRSA();break;
    case '4':Colatz();break;
    case '5':goDedekind();break;
    default:
      {
      newl();printf(
"  Unknow cmd. Use h help. \n");newl(); 
      }
      break;

    }/** end switch **/

  lapsed(&CMDmark);

  } /** main while **/
return 1;
}


