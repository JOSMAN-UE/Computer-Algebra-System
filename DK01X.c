

/* DK01X.C */




void XCsetdump(void)
{
int s,t,x,u;

assert(hXc<XCHX);
assert(vXc<XCVX);
s=0;
for(int i=0;i<vXc;i++)
  {
  x=0;u=0;
  for(I16 j=0;j<hXc;j++)
    {
    if(XC[i][j] EQ '1')u++;
    else if(XC[i][j] EQ 'X')x++;
    }
  t=PW2[x];s+=t;
  if(i<10)printf(" %2d (%s %d) u %02d x %02d t %02d \n"
  ,i,XC[i],Xlen(XC[i]),u,x,t);
  }
printf("En XC: %d \n",s);
}

int CnumerX(const int p)
{
char *xcp;
int c=0;

xcp=XC[p];
for(I16 i=0;i<hXc;i++)
  if(xcp[i] EQ 'X')c++;
return c;
} 

void evalsetXC(void)
{
int s,x;
float ratio;

assert(hXc<XCHX);assert(vXc<XCVX);
s=0;
for(int i=0;i<vXc;i++)
  {
  x=CnumerX(i);s+=PW2[x];
  }

ratio=((float)(100*vXc)/(float)s);
printf("XC: hXc %d vXc %d F %d (%4f) \n"
,hXc,vXc,s,ratio);
}



int wfus2AB(const int a,const int b)
{
int d,la,lb,nofus;
char aa,bb;
bool posib;

nofus=-1;d=-1;
if(CnumerX(a) NE CnumerX(b))return nofus;
la=strlen(XC[a]);lb=strlen(XC[b]);
if(la NE lb)return nofus;
posib=0;
for(I16 j=0;j<la;j++)
  {
  if(XC[a][j] NE XC[b][j])
    {
    if(posib)return nofus;
    posib=1;d=j;
    }
  }
aa=XC[a][d];bb=XC[b][d];
if(abs(aa-bb) NE 1)return nofus;
return d;
}

int Cinfofus(void)
{
int a,b,d,c;

assert(hXc<XCHX);assert(vXc<XCVX);
c=0;
for(a=  0;a<vXc;a++)
for(b=a+1;b<vXc;b++)
  {d=wfus2AB(a,b);if(d GE 0)c++;
  }
printf("I infofus: %d \n",c);
return c;
}

void fusion(void)
{
int a,b,d,ult,fus;

while(1)
  {
  ult=vXc-1;fus=0;
  for(a=1;a<vXc;a++)
  for(b=0;b<  a;b++)
    {
    d=wfus2AB(a,b);
    if(d<0)continue;
    XC[a][d]='X';
    strcpy(XC[b],XC[ult]);
    vXc--;ult--;fus++;
    }
  if(fus EQ 0)break;
  }
}



void Dexpan01X(int hor)
{
printf("I HX %d, VX %d \n",XCHX,XCVX);
for(int i=0;i<3;i++)strcpy(XC[i],INI[i]);
hXc=4;vXc=3;

while(hXc< hor)
  {
  int tin;

  assert(hXc<XCHX);assert(vXc<XCVX);
  evalsetXC();

  DKgen(hXc+1);strcpy(rga,m[hXc]);
  printf("r%02d %s \n",hXc,rga);
  tin=vXc;printf("tin %d \n",tin);

  for(int i=0;i<tin;i++)
    {
    bool fer,tir,fus;

    strcpy(ele,"?");strcat(ele,XC[i]);
    strcpy(els,ele);

    fer=0;
    for(I16 j=1;j<=hXc;j++)
      {
      if((rga[j] EQ '1')
      AND(ele[j] EQ '0'))
        {
        ele[0]='0';
        strcpy(XC[i],ele);
        fer=1;break;
        }
      }
    if(fer)continue;

    tir=1;
    for(I16 j=1;j<=hXc;j++)
      {
      char che,chr,chs;

      che=ele[j];chr=rga[j];
      if((chr EQ '1')AND (che EQ 'X'))
        {tir=0;chs=chr;}
      else chs=che;

      els[j]=chs;
      }
    if(tir)ele[0]='X'; else ele[0]='0';
    strcpy(XC[i],ele);
    if(tir)continue;

    assert(vXc<XCVX);
    els[0]='1';
    strcpy(XC[vXc++],els);
    fus=1;
    while(fus)
      {
      fus=0;
      int a,c,d;
      a=(vXc-1);c=0;
      for(int b=(a-1);b>=c;b--)
        {
        d=wfus2AB(a,b);if(d<0)continue;
        XC[b][d]='X';vXc=a;fus=1;
        break;
        }
      }
    }
  hXc++;
  printf("set [hsize %d,vsze %d] \n"
  ,hXc,vXc);
  assert(hXc<XCHX);
  }

evalsetXC();
}


void demo01X(void)
{
BNUM B;

Dexpan01X(10);

B=sum4();printf("sum4: %I64d \n",B);
}


