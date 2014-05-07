 
// stdafx.cpp : source file that includes just the standard includes
//        skeleton.pch will be the pre-compiled header
//        stdafx.obj will contain the pre-compiled type information

#include "StdAfx.h"
#include <string.h>

double** allocate2DDouble( int y, int x )
{
        double** mat = new double*[y];
        int i;
        for( i =0; i<y; i++)
        {
                mat[i] = new double[x];
                memset(mat[i], 0, sizeof(double) * x );
        }

        return mat;
}

void copyMatrix( double** from, double** to, int nRows, int nCols )
{
        int i, j;
        for( i=0; i<nCols; i++ )
                for( j=0; j<nRows; j++)
                {
                        to[j][i] = from[j][i];
//                        printf("to[%d][%d] = %lf\n", j, i, to[j][i]);
                }
}

double det33( double** mat )
{
        return( mat[0][0] * mat[1][1] * mat[2][2]
                + mat[1][0] * mat[2][1] * mat[0][2]
                + mat[2][0] * mat[0][1] * mat[1][2]
                - ( mat[2][0] * mat[1][1] * mat[0][2]
                + mat[1][0] * mat[0][1] * mat[2][2]
                + mat[0][0] * mat[2][1] * mat[1][2] ) );
}

double dotProduct3D( double vectorA[3], double vectorB[3] )
{
        int i;
        double result = 0;
        for( i=0; i<3; i++)
                result += vectorA[i] * vectorB[i];

        return result;
}

double norm3D( double vector[3] )
{        
        return sqrt( vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2] );
}

void minus3D( double vectorA[3], double vectorB[3], double result[3] )
{
        result[0] = vectorA[0] - vectorB[0];
        result[1] = vectorA[1] - vectorB[1];
        result[2] = vectorA[2] - vectorB[2];
}

void add3D( double vectorA[3], double vectorB[3], double result[3] )
{
        result[0] = vectorA[0] + vectorB[0];
        result[1] = vectorA[1] + vectorB[1];
        result[2] = vectorA[2] + vectorB[2];
}
 
