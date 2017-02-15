// Matrix  
#include "matrix.h"

void matrix_Mult(int data[ROWS][COLUMNS], int A[ROWS][COLUMNS], int B[ROWS][COLUMNS]) {
	int i, j, k;
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLUMNS; j++)
			for (k = 0; k < COLUMNS; k++)
				data[i][j] += A[i][k] * B[k][j];
}

void matrix_MultF(float data[ROWS][COLUMNS], float A[ROWS][COLUMNS], float B[ROWS][COLUMNS]) {
	int i, j, k;
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLUMNS; j++)
			for (k = 0; k < COLUMNS; k++)
				data[i][j] += A[i][k] * B[k][j];
}

void matrix_Transpose(int data[ROWS][COLUMNS], int A[ROWS][COLUMNS]) {
	int i, j;
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLUMNS; j++)
			data[j][i] = A[i][j];
}

void matrix_Conv(int data[ROWS][COLUMNS], int in[ROWS][COLUMNS], int kernel [KROWS][KCOL]) {
	int i,j,m,n,ii,jj,mm,nn, kCenterX, kCenterY;
	kCenterX = KCOL / 2;
	kCenterY = KROWS / 2;

	for(i=0; i < ROWS; ++i)              // rows
	{
		for(j=0; j < COLUMNS; ++j)          // columns
		{
			for(m=0; m < KROWS; ++m)     // kernel rows
			{
				mm = KROWS - 1 - m;      // row index of flipped kernel

				for(n=0; n < KCOL; ++n) // kernel columns
				{
					nn = KCOL - 1 - n;  // column index of flipped kernel

					// index of input signal, used for checking boundary
					ii = i + (m - kCenterY);
					jj = j + (n - kCenterX);

					// ignore input samples which are out of bound
					if( ii >= 0 && ii < ROWS && jj >= 0 && jj < COLUMNS )
						data[i][j] += in[ii][jj] * kernel[mm][nn];
				}
			}
		}
	}
}