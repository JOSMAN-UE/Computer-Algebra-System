

/*** DKMATRIX.C ******/


void DKBfromC(void)
{
bool v;

assert(iC<DBX);
for(int i=0;i<iC;i++)
for(int j=0;j<iC;j++)
  {
  v=FALSE;
  if(Dleq(C[i],C[j]))v=TRUE;
  B[i][j]=v;
  }

printf("Set matrix B. iC %d \n",iC);
}

void DKBprint(void)
{
bool v;

printf("matrix B: \n");
for(int i=0;i<iC && i<DKdev;i++)
  {
  for(int j=0;j<iC && j<DKdev;j++)
    {
    v=B[i][j];
    if(v)printf(" 1");
    else printf(" _");
    }
    newl();
  }
newl();
}

BNUM DKBxRE(void)
{
BNUM st,sl;
PNUM q;
st=0;
for(int i=0;i<iC;i++)
  {
  sl=0;
  for(int j=i;j<iC;j++)
    {
    q=0;
    for(int k=i;k<=j;k++)
      {q+=(B[i][k] AND B[k][j]);}
    sl+=q*q;
    }
  st+=sl;
  }

return st;
}

BNUM DKBx2(void)
{
BNUM s;

s=0;
for(int i=0;i<iC;i++)
for(int j=i;j<iC;j++)
  {
  if(B[i][j])s++;
  }
return s;
}

BNUM DKBx3(void)
{
BNUM s;

s=0;
for(int j=0;j<iC;j++)
  {
  for(int i=j;i<iC;i++)
    {
    if(!B[j][i])continue;
    for(int k=j;k<iC;k++)
      {
      if(B[j][k])s++;
      }
    }
  }

return s;
}


BNUM DKBx4(void)
{
BNUM s;

s=0;
for(int i=0;i<iC;i++)
  {
  for(int j=i;j<iC;j++)
    {
    if(!B[i][j])continue;
    for(int k=i;k<iC;k++)
      {
      if(!B[i][k])continue;
      for(int l=Imaxim(j,k);l<iC;l++)
        {
        if(!B[j][l])continue;
        if(!B[k][l])continue;
        s++;
        }}}}

return s;
}


void DKBdemo(void)
{
BNUM v;

DKexpanC(8);DKBfromC();DKBprint();
v=DKBx2(); printf("DKBx2  %I64d \n",v);
v=DKBxRE();printf("DKBxRE %I64d \n",v);
v=DKBx3(); printf("DKBx3  %I64d \n",v);
v=DKBx4(); printf("DKBx4  %I64d \n",v);
}
