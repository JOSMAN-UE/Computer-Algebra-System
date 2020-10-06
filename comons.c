


/* COMONS.C */


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <string.H>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <omp.h>


#define TASKMX 4
#define EQ ==
#define NE !=
#define GE >=
#define LE <=
#define GT >
#define LT <

#define FALSE 0
#define NO 0
#define TRUE 1
#define SI 1

#define AND &&
#define OR ||
#define NOT !

#define bitor |
#define bitand &
#define bitxor ^
#define bitnot ~

#define SXLEN 90

typedef unsigned char UCHAR;
typedef int_fast8_t I8;
typedef uint_fast8_t U8;
typedef int_fast16_t  I16;
typedef uint_fast16_t U16;
typedef int_fast32_t  I32;
typedef uint_fast32_t U32;
typedef int_fast64_t I64;
typedef uint_fast64_t U64;
typedef __int128       I128;
typedef unsigned __int128 U128;

typedef int_fast32_t   PNUM;
typedef int_fast64_t  BNUM;
typedef uint_fast64_t  LNUM;


#define MX 256
#define NUDI MX
#define MXPRIM 82100

#pragma pack(4)

static bool DREADY;
static bool ISPRIME,ISSQUARE,ISFLAT;

static I64 DEN,DRR;
static I64 F2EXP,NUMPRIM,NUMFAC,MXSEC;
static I64 NN,SIGMA,TOTI,NUMDIV;
static I64 ODDN,ROTI,ROTE,FLATN,SQUAREN;
static I64 ZVAL,ZPAS,ZDD;
static I64 VDIV[MX],TDE[MX],TRR[MX];
static I64 VFAC[MX],VEXP[MX];
static I32 VPRIMOS[MXPRIM];
static time_t CMDmark;

#define DKX 64
#define DRX 80
#define DCX 7999000
#define DKdev 20
#define DBX 200

static LNUM PW2[DRX];
static U8   RUD[DRX];
static bool RTU[DRX];
static U8   RTX[DRX];
static LNUM RN[DRX];
static char m[DRX][DRX];
static LNUM C[DCX];
static bool B[DBX][DBX];
static PNUM eC,iC,iC1;static int wC;



#include "VECCOM.C"
#include "NUMBERS.C"
#include "THEWORKS.C"
#include "DKRULES.C"
#include "DKFUN.C"
#include "DKSET.C"
#include "DKMATRIX.C"
#include "DKsetR.C"
#include "DKFXK.C"
#include "DXxK.C"
#include "DK01X.C"
#include "DKMAIN.C"


/***************************/

