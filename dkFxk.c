

/* DKFxk.c */


PNUM DFskanup(PNUM p)
{
LNUM vk,vab;
PNUM c;

c=0;vab=C[p];
for(PNUM k=0;k<=p;k++)
  {
  vk=C[k];if(Dleq(vk,vab))c++;
  }
return c;
}

PNUM DFskandown(PNUM p)
{
LNUM vk,vab;PNUM c;

c=0;vab=C[p];
for(PNUM k=(iC-1);k GE p;k--)
  {
  vk=C[k];
  if(Dleq(vab,vk))c++;
  }
return c;
}


BNUM Djmjk(PNUM pp)
{
LNUM aa,bb,mitab,jonab;
BNUM apo;
PNUM ii,mj,rmit,sjon;

ii=pp;aa=C[ii];apo=0;
for(I32 jj=ii;jj<iC;jj++)
  {
  bb=C[jj];
  mitab=aa&bb;mj=DbsearchC(mitab);
  rmit=QLE[mj];
  if(rmit EQ 0)
    {rmit=DFskanup(mj);QLE[mj]=rmit;
    }

  jonab=(aa|bb);mj=DbsearchC(jonab);
  sjon=QGE[mj];
  if(sjon EQ 0)
    {sjon=DFskandown(mj);QGE[mj]=sjon;
    }
  apo+=rmit*sjon;
  if(ii NE jj)apo+=rmit*sjon;
  }
return apo;
}



PNUM DKseqFx2(void)
{
LNUM a,b;
PNUM B;

printf("DKseqFx2 DKFxK.c \n");
printf("C wC %d iC %d \n",wC,iC);
B=0;
for(PNUM i=0;i<iC;i++)
  {
  a=C[i];
  for(PNUM j=i;j<iC;j++)
    {b=C[j];if(Dleq(a,b))B++;
    }
  }
return B;
}


LNUM DKFx4(void)
{
LNUM L;BNUM P;

printf("DKseqFx4 DKFxK.c \n");
printf("meet,join,cached. \n");
printf("C wC %d iC %d \n",wC,iC);

for(PNUM i=0;i<DCX;i++){QLE[i]=0;QGE[i]=0;}

L=0;
for(PNUM i=0;i<iC;i++)
  {
  P=Djmjk(i);L+=P;
  }
newl();

return L;
}


void seqsmall(void)
{
LNUM L,P,Q;
int n;

printf("seqsmall DKFxK.c \n");
printf("d7= F112+F120 \n");

n=28;DKexpanC(n);P=DKFx4();
printf("F(%d)=",4*n);print128(P);

n=30;DKexpanC(n);Q=DKFx4();
printf("F(%d)=",4*n);print128(Q);

printf("d7= \n");
L=P+Q;print128(L);
}


