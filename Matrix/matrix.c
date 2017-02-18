// Matrix.c
// Created by Ryan Owens
// Last modified: 2/18/2017
//            By: Ryan Owens
//***********************************
// This file implements matrix functions to be
// used for benchmarking the MPC5554 evaluation board.
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

void matrix_Conv(int data[ROWS][COLUMNS], int in[ROWS][COLUMNS], int kernel [KSIZE][KSIZE]) {
	int i,j,m,n,ii,jj,mm,nn, kCenterX, kCenterY;
	kCenterX = KSIZE / 2;
	kCenterY = KSIZE / 2;

	for(i=0; i < ROWS; ++i)              // rows
	{
		for(j=0; j < COLUMNS; ++j)          // columns
		{
			for(m=0; m < KSIZE; ++m)     // kernel rows
			{
				mm = KSIZE - 1 - m;      // row index of flipped kernel

				for(n=0; n < KSIZE; ++n) // kernel columns
				{
					nn = KSIZE - 1 - n;  // column index of flipped kernel

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