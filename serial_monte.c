#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[])
{
    long niter = 1000000;
	double x,y,z,pi;
	int count=0;
	
	for(int i = 0; i< niter ; i++){
		x=(double)rand()/RAND_MAX*2.0-1.0; 
		y=(double)rand()/RAND_MAX*2.0-1.0; 
		z = sqrt(x*x+y*y);                  
            if (z<=1)
            {
                count++;                
            }
	}
	pi = ((double) count/(double) niter)*4.0;
			printf("Pi: %f\n", pi);
			return 0;
			
}