

/* DXxK.C */

#define XCHX 66
#define XCVX 399111
static const char INI[3][5]={"0000","0XX1","1111"};
static char XC[XCVX][XCHX];
static char rga[XCHX],ele[XCHX],els[XCHX];
static const char CHZ='0';
static PNUM vXc;static U16 hXc;

static const U8 T2[3][3]
={{1,1,2},{0,1,1},{1,2,3}};
static const U8 L3[27]=
   {1,1,2,1,1,2,2,2,4,0,0,0,0,1,1,0,1,1
   ,1,1,2,1,2,3,2,3,5};
static U8 T3[3][3][3];
static U8 T4[3][3][3][3];


void filltablas(void)
{
int v;

v=0;
for(int i=0;i<3;i++)
for(int j=0;j<3;j++)
for(int k=0;k<3;k++)
  T3[i][j][k]=L3[v++];

for(int a=0;a<3;a++)
for(int b=0;b<3;b++)
for(int c=0;c<3;c++)
for(int d=0;d<3;d++)
  {
  int ei,ef,fi,ff,gi,gf,hi,hf;
  int s=0;
  if(a EQ 2){ei=0;ef=2;} else {ei=a;ef=a+1;}
  if(b EQ 2){fi=0;ff=2;} else {fi=b;ff=b+1;}
  if(c EQ 2){gi=0;gf=2;} else {gi=c;gf=c+1;}
  if(d EQ 2){hi=0;hf=2;} else {hi=d;hf=d+1;}

  for(int e=ei;e<ef;e++)
  for(int f=fi;f<ff;f++)
  for(int g=gi;g<gf;g++)
  for(int h=hi;h<hf;h++)
    {
    I16 p=1;
    p*=T2[e][f];p*=T2[e][g];
    p*=T2[f][h];p*=T2[g][h];
    s+=p;
    }
  T4[a][b][c][d]=s;
  }
}

void XCswapch(char a,char b)
{
assert(hXc<XCHX);assert(vXc<XCVX);
for(PNUM i=0;i<vXc;i++)
  {
  for(I16 j=0;j<hXc;j++)
    {if(XC[i][j] EQ a)XC[i][j]=b;
    }
  }
}

BNUM mul2(PNUM aa,PNUM bb)
{
BNUM rp;
char *a,*b,ca,cb;

a=XC[aa];b=XC[bb];rp=1;
for(int bi=0;bi<hXc;bi++)
  {
  ca=a[bi];cb=b[bi];
  rp*=T2[ca-CHZ][cb-CHZ];
  if(rp EQ 0)break;
  }
return rp;
}


BNUM sum2(void)
{
BNUM tot;

filltablas();XCswapch('X','2');
tot=0;
for(PNUM ia=0;ia<vXc;ia++)
  {
  BNUM r,sum;
  sum=0;
  for(PNUM ib=ia;ib<vXc;ib++)
    {
    r=mul2(ia,ib);
    if(r EQ 0)r=mul2(ib,ia);
    sum+=r;
    }
  tot+=sum;
  }
XCswapch('2','X');
return tot;
}


BNUM mul3(PNUM pa,PNUM pb,PNUM pc)
{
BNUM tot;
char *a,*b,*c;
  
a=XC[pa];b=XC[pb];c=XC[pc];tot=1;
for(I16 i=0;i<hXc;i++)
  {
  tot*=T3[a[i]-CHZ][b[i]-CHZ][c[i]-CHZ];
  if(tot EQ 0)break;
  }

return tot;
}

BNUM sum3(void)
{
BNUM tot;

filltablas();XCswapch('X','2');
tot=0;
for(PNUM ia=0;ia<vXc;ia++)
for(PNUM ib=0;ib<vXc;ib++)
for(PNUM ic=0;ic<vXc;ic++)
  {
  tot+=mul3(ia,ib,ic);
  }
XCswapch('2','X');
return tot;
}

PNUM mul4(PNUM pa,PNUM pb,PNUM pc,PNUM pd)
{
PNUM tot;
char *a,*b,*c,*d;
  
a=XC[pa];b=XC[pb];c=XC[pc];d=XC[pd];
tot=1;
for(I16 i=0;i<hXc;i++)
  {
  tot*=
T4[a[i]-CHZ][b[i]-CHZ][c[i]-CHZ][d[i]-CHZ];
  if(tot EQ 0)break;
  }

return tot;
}


BNUM sum4(void)
{
BNUM tot;
PNUM v;

printf("W x4 %d 01X \n",vXc);
filltablas();XCswapch('X','2');

tot=0;
for(PNUM ia=0;ia<vXc;ia++)
 {
 for(PNUM ib=0;ib<vXc;ib++)
  {
  for(PNUM ic=0;ic<vXc;ic++)
   {
   for(PNUM id=0;id<vXc;id++)
    {
    v=mul4(ia,ib,ic,id);tot+=v;
    }
   }
  } 
 }
newl();
XCswapch('2','X');
return tot;
}

