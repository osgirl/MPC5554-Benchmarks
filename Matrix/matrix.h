// Matrix

#define ROWS 3
#define COLUMNS 3
#define KROWS 3
#define KCOL 3

void matrix_Mult(int data[ROWS][COLUMNS], int A[ROWS][COLUMNS], int B[ROWS][COLUMNS]);

void matrix_MultF(float data[ROWS][COLUMNS], float A[ROWS][COLUMNS], float B[ROWS][COLUMNS]);

void matrix_Transpose(int data[ROWS][COLUMNS], int A[ROWS][COLUMNS]);

void matrix_Conv(int data[ROWS][COLUMNS], int in[ROWS][COLUMNS], int kernel[KROWS][KCOL]);