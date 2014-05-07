
#ifndef SVDCMP_H_
#define SVDCMP_H_

#include "StdAfx.h"
#include <math.h>
#include <stdio.h>


static double maxarg1, maxarg2;
#define FMAX(a,b) (maxarg1 = (a),maxarg2 = (b),(maxarg1) > (maxarg2) ? (maxarg1) : (maxarg2))

static int iminarg1, iminarg2;
#define IMIN(a,b) (iminarg1 = (a),iminarg2 = (b),(iminarg1 < (iminarg2) ? (iminarg1) : iminarg2))

static double sqrarg;
#define SQR(a) ((sqrarg = (a)) == 0.0 ? 0.0 : sqrarg * sqrarg)

int svdcmp(double **a, int nRows, int nCols, double *w, double **v);
double pythag(double a, double b);

void inverse( double** a, int nRows, int nCols);  // remember to do transpose after this function call

#endif