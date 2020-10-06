

/*** DKFUN.C ******/

BNUM DKFmagicE(int pm)
{
LNUM can,cin,cfi;
LNUM cun,cpas;
BNUM expa;
int m,rm;

m=pm;rm=m-1;
assert(m>0);assert(m<129);

if(RTU[rm])
  {cfi=DKpot(rm+1)-1;cin=cfi;cpas=2;
  }
else
  {
  cin=DKpot(rm)+1;cfi=DKpot(rm+1)-1;
  cpas=PW2[RUD[rm]];
  while((cin%cpas) NE (cpas-1))cin+=2;
  }

expa=0;if(m EQ (0+1))expa++;
for(can=cin;can<=cfi;can+=cpas)
  {
  cun=can;
  for(int r=rm;r>1;r--)
    {if( (can&PW2[r]) NE 0)can=(can|RN[r]);
    }

  expa++;
  }

return expa;
}


void DKFdemoMP(void)
{
#define dkfdemo01 150
BNUM E[dkfdemo01];BNUM F;
int n,ncpu;


printf("DKFdemoMP DKfun.c \n");

#pragma omp master
omp_set_num_threads(1);
ncpu=omp_get_num_procs();

n= 56;assert(n< dkfdemo01);
DKgen(n);
for(int m=0;m< dkfdemo01;m++)E[m]=0;

omp_set_num_threads(ncpu);
#pragma omp parallel
  {
  for(int m= 1;m<= n;m++)
    {
    int ntask;
#pragma omp single
    if(E[m] EQ 0)
      {
      E[m]= DKFmagicE(m);
      ntask=omp_get_thread_num();
      printf("E(%d)=%I64d (task %d) \n"
      ,m,E[m],ntask);
      }
    }
  }

#pragma omp master
  {
  F=0;
  for(int m=1;m<=n;m++)F+=E[m];
  printf("F(%d)= %I64d \n",n,F);
  }
}


void DKFdemo(void)
{
BNUM E;

for(int n=5;n<=64;n=2*n-1)
  {
  DKgen(n);E= DKFmagicE(n);
  printf("E(%d)= %I64d \n",n,E);
  }
}


