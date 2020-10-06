


/* DKRULES.C */


void DKgen(int pn)
{
int dkn;
char l[DRX];
int a,b,k;

dkn=pn;a=3;b=3;
assert(pn LE DKX);

for(int r=0;r< dkn;r++)
  {
  assert(r LE DKX);

    if(r EQ 0){a=3;b=3;}
    for(int i=0;i<dkn;i++)l[i]='n';

    l[dkn]='f';l[dkn+1]=0;
    k=dkn-1-r;
    for(int i=a;i<=b;i++)
    {
      if(a EQ (a&i))l[k]='1';
      else l[k]='x';
      k++;
    }
    l[dkn-1-r]='e';l[dkn+1]=0;
    strcpy(m[r],l);
    a--;if(a<0){a=b;b=2*b+1;}
  }
m[0][dkn-1]='e';

  {
  LNUM rvn;char ch;

  for(int r=0;r<DKX;r++)RTU[r]=0;
  for(int r=0;r<DKX;r=2*r+1)RTU[r]=1;
  for(int r=0;r<dkn;r++)
    {
    int cox,uder;

    assert(r LE DKX);
    strcpy(l,m[r]);uder=0;
    for(int b=dkn-1;
      (l[b] EQ '1') AND (b>=0);b--)uder++;
    RUD[r]=uder;rvn=0;cox=0;
    for(int b=dkn;b>=0;b--)
      {
      assert(b LE DKX);
      ch=l[b];
      if(ch EQ '1')rvn++;
      else if(ch EQ 'x')cox++;
      else if(ch EQ 'e'){rvn++;break;}
      rvn<<=1;
      }
    RN[r]=rvn;RTX[r]=cox;
    }
  }
}


void DKreglas(int pn)
{
assert(pn LE DKX);DKgen(pn);
for(int r=0;r<pn;r++)
  {
  assert(r LE DKX);
  printf("%2d %s (%d)",r,m[r],(int)strlen(m[r]));
  printf("UD %2d TU %2d TX %2d \n"
  ,RUD[r],RTU[r],RTX[r]);
  }
}

void DKRdemo(void)
{
DKreglas(8);
}

