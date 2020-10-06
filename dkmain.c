

/*** DKMAIN.C ******/


void DKinitialize(void)
{
printf("Config. DKX %d \n",DKX);
for(int e=0;e<DKX;e++)PW2[e]=DKpot(e);
}

void afterwait(void)
{
printf("-----------------");
printf(" Done. ");
printf("-----------------");
newl();
sleep(1);
getch();
}

void goDedekind(void)
{
char ch;

DKinitialize();
ch=' ';
while(ch NE '0')
  {
  printf(
"0 quit         1 C: Dupl/Expan  2 d7, Sin R. \n");

  printf(
"3 d(NN),con R. 4 XC, 01X.       5 Reglas  \n");

  printf(
"6 Matrix,xk.   7 1task. E(n).   8 4task. E(),F56 \n");

  printf(
"9 d8,R6  \n");

  ch=askcmd();
  switch(ch)
    {
    case '0': exit(1);
    case '1': DKCdemo();break;
    case '2': seqsmall();break;
    case '3': DRdemo(NN);break;
    case '4': demo01X();break;
    case '5': DKRdemo();break;
    case '6': DKBdemo();break;
    case '7': DKFdemo();break;
    case '8': DKFdemoMP();break;
    case '9': DRdemo(6);break;
    default:  exit(0);
    }
  afterwait();
  }
}

