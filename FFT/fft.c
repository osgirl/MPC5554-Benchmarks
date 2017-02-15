#include <math.h>
 
 
/* timing test for standardized (NOT OPTIMIZED!!!) fft.
/* from Numerical Recipes "C" algorithm
 
/* this was compiled on a Sun SPARC  with the Greenhills cross compiler
/* /usr/local/GreenHills/ccvxppc -O -fvolatile -ansi -pedantic -nostdlib \
	-nostdinc  -cpu=ppc603 -DCPU=PPC603 -D_GREEN_TOOL -c test.c
 
 
/* 1. load into vxWorks
/* 2. timexN four1, &xxxx-4, 512, 1                 =========> time fft
timex: 75 reps, time per rep = 10217 +/- 222 (2%) microsecs (on MVME167)
timex: 825 reps, time per rep = 767 +/- 20 (2%) microsecs (MVME 1600 PPC 604)
*/
 
 
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
unsigned int fftCount;
 
void four1(float data[], int nn, int isign)
{
     int n,mmax,m,j,istep,i;
     float wtemp,wr,wpr,wpi,wi,theta;
     float tempr,tempi;
 
     n=nn << 1;
     j=1;
     for (i=1;i<n;i+=2) {
          if (j > i) {
               SWAP(data[j],data[i]);
               SWAP(data[j+1],data[i+1]);
          }
          m=n >> 1;
          while (m >= 2 && j > m) {
               j -= m;
               m >>= 1;
          }
          j += m;
     }
    mmax=2;
     while (n > mmax) {
          istep=2*mmax;
          theta=6.28318530717959f/(isign*mmax);
          wtemp=sinf(0.5f*theta);
          wpr = -2.0f*wtemp*wtemp;
          wpi=sinf(theta);
          wr=1.0;
          wi=0.0;
 
          for (m=1;m<mmax;m+=2) {
               for (i=m;i<=n;i+=istep) {
                    j=i+mmax;
                    tempr=wr*data[j]-wi*data[j+1];
 
                    tempi=wr*data[j+1]+wi*data[j];
                    data[j]=data[i]-tempr;
                    data[j+1]=data[i+1]-tempi;
                    data[i] += tempr;
                    data[i+1] += tempi;
               }
               wr=(wtemp=wr)*wpr-wi*wpi+wr;
               wi=wi*wpr+wtemp*wpi+wi;
          }
          mmax=istep;
     }
    if (isign < 0)
        for (i=1;i<nn*2;i++)
            data[i] /= (nn*1.0);
}
 
#undef SWAP
