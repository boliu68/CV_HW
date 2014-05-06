#ifndef _MYSTDAFX_H_
#define _MYSTDAFX_H_

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////
// Memory Management
#define SAFEDEL(x) { if(x!=NULL) { delete x; x = NULL; } }
#define SAFEDELARR(x) { if(x!=NULL) { delete [] x; x=NULL; } }
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Other user-defined function
#define nearzero(f) (f >= -EPLSION && f <= EPLSION)
#define RADIAN(deg)        (deg/180.0*PI)
#define DEGREE(rad) (rad/PI*180.0)
////////////////////////////////////////////////////////////////////////////

#define SIGN(a,b) ((b) > 0.0 ? fabs(a) : - fabs(a))

////////////////////////////////////////////////////////////////////////////
// Other Constants Definition
#define EPLSION                                        0.000001f
#define PI                                                3.141592653589793
#define MYINFINITE                                1000000000
////////////////////////////////////////////////////////////////////////////

double** allocate2DDouble(int y, int x);
void copyMatrix( double** from, double** to, int nRows, int nCols );
double det33( double** mat );

double dotProduct3D( double vectorA[3], double vectorB[3] );
double norm3D( double vector[3] );
void minus3D( double vectorA[3], double vectorB[3], double result[3] );
void add3D( double vectorA[3], double vectorB[3], double result[3] );

#endif
