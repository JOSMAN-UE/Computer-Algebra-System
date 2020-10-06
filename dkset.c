

/*** DKSET.C ******/


void DKCe0()
{
for(int i=0;i<DCX;i++)C[i]=0;
iC=0;C[iC++]=0;C[iC++]=1;
wC=1;
}

void DKCprint(void)
{
printf("C: %d %d \n",iC,wC);
for(int i=0;i<iC;i++)DKbin(C[i]);
newl();
}

void DKCx2(void)
{
PNUM k;
LNUM a,b;

k=iC;
for(int i=1;i<k;i++)
for(int j=0;j<k;j++)
  {
  assert(iC<DCX);
  a=C[i];b=C[j];
  if(Dleq(a,b))C[iC++]=(a<<wC)+b;
  }
wC*=2;
}


void DKexpanC(int pn)
{
LNUM tmp,rnm,pwm,mit;
PNUM lowC,kC;
int n;

n=pn;
assert(n>2);

DKgen(n);
printf("Loaded %d rules. \n",n);

C[0]=0;C[1]=1;C[2]=3;C[3]=5;C[4]=7;

lowC=5;kC=lowC;wC=3;

for(int m=wC;m<n;m++)
  {
  wC++;pwm=PW2[m];rnm=RN[m];

  for(int i=1;i<lowC;i++)
    {
    tmp=C[i];tmp=tmp|pwm;
    mit=tmp&rnm;
    if(mit NE rnm)continue;
    assert(kC LT DCX);
    C[kC++]=tmp;
    }
  lowC=kC;
  }

iC=lowC;
printf("Expan. C(%d)=[%d*%d] \n",n,wC,iC);
}



void DKCdemo(void)
{
int e,n;

printf("DKCdemo DKset.c \n");
printf("Duplicar C=(C*C); \n");
e=0;n=1;DKCe0();
while(e LT 5)
  {
  printf("C(%d,%d)  ",e,n);
  DKCx2();e++;n*=2;
  printf(
"  C(%d) [%d*%d] \n",n,wC,iC);
  }
printf("Expandir desde cero.\n");
for(int n=14;n<17;n++)DKexpanC(n);
}



