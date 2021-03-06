#include "MPC5554.h"

#define DATA_SIZE   64
#define NUM_ITERATIONS  50

static unsigned int ticks[NUM_ITERATIONS] = {};


float data[DATA_SIZE] = {};

extern void four1(float data[], int nn, int isign);

unsigned int __get_timebase(void)
{
	__asm__ volatile ("mfspr r3, 268\n\t"
	                  );
}

void __enable_cache(void)
{

	__asm__ volatile (
				"mfspr r3, 1010\n\t"
  				"ori   r3, r3, 0x1\n\t"
  				"msync\n\t"
  				"isync\n\t"
  				"mtspr 1010, r3\n\t"
                );
}

void __disable_cache(void)
{
	__asm__ volatile (
		"mfspr r3, 1010\n\t"
		"lis   r4, 0xFFFF\n\t"
		"ori   r4, r4, 0xFFFE\n\t"
		"and  r3, r3, r4\n\t"
		"msync\n\t"
		"isync\n\t"
		"mtspr 1010, r3\n\t"
       );	
	
}

unsigned int __invalidate_cache(void)
{
	  __asm__ volatile (
	  					"mfspr r3, 1010\n\t"
	  					"andi. r4, r3,0x2\n\t"
	  					"bne status_read\n\t"
	  					"ori   r3, r3,0x2\n\t"
	  					"msync\n\t"
	  					"isync\n\t"
	  					"mtspr 1010, r3\n\t"
	  					"status_read:\n\t"
	  					"mfspr r3, 1010\n\t"
	  					"andi. r4,r3,0x2\n\t"
	  					"bne status_read\n\t"
	  					"and r3, r3,0x4\n\t"
	  					"srawi r3,r3,0x2\n\t"
	  					);
	  					
	  					
}

void __invalidate_cache_by_way(void)
{
  unsigned int __reg;
  unsigned int i,j;
  
  //invalidate and flush set and way
  for(i=0; i< 8; i++)
  {
  	for(j=0; j<128; j++)
  	{
  		__reg = ((i << 24) | (j << 5) | 0x2);
  		__asm__ volatile (
  			"mtspr 1016, %[reg]\n\t"
  			: [reg]"+r" (__reg)
  			:
  		);
  	}
  }
	  					
	  					
}


void __enable_TB(void)
{
    __asm__ volatile (
                      "mfspr r3, 1008\n\t"
  					  "ori   r3, r3, 0x4000\n\t"
  					  "mtspr 1008, r3\n\t"
  					 );
	
}
 

int main(void) 
{
  volatile int i, j;
  
  unsigned int tb_before, tb_after, tb_diff;

  unsigned int __reg = 0;
  unsigned int __addr = 0;
  unsigned int L1INV_err = 0;
  
  //Enable Timebase
  __enable_TB(); 

  
  //Invalidate L11 Cache
  L1INV_err = __invalidate_cache();
  
  //Enable L1 Cache
  __enable_cache();
  
  
  //setup the data arrays
  i = 0;
  while(i < DATA_SIZE)
  {
  	data[i] = i;
  	i+=1;
  }
  
  //run the test  	 
  for(i = 0; i < NUM_ITERATIONS; i++)
  {
     
     tb_before = __get_timebase();
	  
     four1(data-1, DATA_SIZE/2, 1);

     tb_after = __get_timebase();
     tb_diff  = tb_after - tb_before;
     
     ticks[i] = tb_diff;
        
     for(j=0; j<DATA_SIZE; j++)
     {
     	data[j] = j;
     }
  }
  
  //disable cache
  __disable_cache();
  
  // check ticks
  while(1)
  {
  	;
  }

  
  return 0;
}






