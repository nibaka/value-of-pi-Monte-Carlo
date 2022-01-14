#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>
#define SEED 35791246

int main(int argc, char* argv[])
{
    long niter = 1000000;
    int myid;                       //process's rank id
    double x,y;                     //random coordinate
    int i, count=0;                 //Count holds all the number of coordinates
    double z;                       //check if x^2+y^2<=1
    double pi;                      
    int nodenum;
    double s,e;
	

    MPI_Init(&argc, &argv);                         //Start MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           //get rank of node's process
    MPI_Comm_size(MPI_COMM_WORLD, &nodenum);
    s = MPI_Wtime();

    int recieved[nodenum];
    long recvniter[nodenum];
    srand(SEED+myid);                               //Give rand() 
	
	
	
    if(myid != 0)
    {
        for (i=0; i<niter; ++i)                  //main loop
        {
      
			x=(double)rand()/RAND_MAX*2.0-1.0; 
			y=(double)rand()/RAND_MAX*2.0-1.0; 
            z = sqrt(x*x+y*y);                  //if number in inside unit circle
            if (z<=1)
            {
                count++;                        //if it is, consider it a valid random point
            }
        }
        for(i=0; i<nodenum; ++i)
        {
            MPI_Send(&count,1,MPI_INT,0,1,MPI_COMM_WORLD);
            MPI_Send(&niter,1,MPI_LONG,0,2,MPI_COMM_WORLD);
        }
    }
    else if (myid == 0)
    {	
		if(nodenum == 1){
			for (i=0; i<niter; ++i){				   
				x= ((double)rand())/RAND_MAX;           
				y =((double)rand())/RAND_MAX;           
				z = sqrt(x*x+y*y);                     
				if (z<=1){
					count++;                         
				}

			}
			pi = ((double) count/(double) niter)*4.0;
			printf("Pi: %f\n", pi);
		}
		
		else{
			int finalcount = 0;
			long finalniter = 0;
			
			
			for(i=0; i<nodenum; ++i)
			{
				MPI_Recv(&recieved[i],nodenum,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
								 
				MPI_Recv(&recvniter[i],nodenum,MPI_LONG,MPI_ANY_SOURCE,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
			
			for(i = 0; i<nodenum; ++i)
			{
				finalcount += recieved[i];
				finalniter += recvniter[i];
			}

			pi = ((double)finalcount/(double)finalniter)*4.0;               //p = 4(m/n)
			printf("Pi: %f\n", pi);            
		}
        
    }

	
	

    e = MPI_Wtime();

    MPI_Finalize();   //Close

    printf("duration : %f --> rank =  %d\n",e-s,myid);
    return 0;
}
