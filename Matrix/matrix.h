// Matrix.h
// Created by Ryan Owens
// Last modified: 2/18/2017
//            By: Ryan Owens
//***********************************
// This file defines matrix functions to be
// used for benchmarking the MPC5554 evaluation board.
#define ROWS 10
#define COLUMNS 10
#define KSIZE 5 // sizes 3, 5, 7, 9

// User must check to make sure that dimensions allow multiplication
void matrix_Mult(int data[ROWS][COLUMNS], int A[ROWS][COLUMNS], int B[ROWS][COLUMNS]);

void matrix_MultF(float data[ROWS][COLUMNS], float A[ROWS][COLUMNS], float B[ROWS][COLUMNS]);

void matrix_Transpose(int data[ROWS][COLUMNS], int A[ROWS][COLUMNS]);

void matrix_Conv(int data[ROWS][COLUMNS], int in[ROWS][COLUMNS], int kernel[KSIZE][KSIZE]);