/*
* Scatter & Gather func Example
*
* In this example root process scatters array values
* and collects elaborated datas from each process. 
*
* Compile: mpicc mpi_scatter_gather.c -o scatter_gather
* Launch: mpirun -n 6 ./scatter_gather
*
* Author: Liu Tong
* Date: Dec 2013
*/


#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char** argv) {

        int rank,size;
        int *dataset, localdata; 
        int i;
        const int root=0;


        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        //Prepare dataset for scatter
        if(rank == root) {
           dataset = malloc(size * sizeof(int));

           printf("[Process %d]: initialize the dataset: \n", rank);
           for (i = 0; i < size; ++i)
           {
                dataset[i] = 2*i+1;
                printf("%d ", dataset[i]);
           }
           printf("\n");
        }

        //MPI_Scatter(sendbuf, sendcnt, MPI_INT,recvbuf,recvcnt,MPI_INT, source, MPI_COMM_WORLD);
        MPI_Scatter(dataset, 1, MPI_INT,&localdata,1,MPI_INT, root, MPI_COMM_WORLD);

        //Data elaboration
        printf("[Process %d]: receive %d, and I double it to %d\n", rank, localdata, localdata*2);
        localdata *= 2;
        
        //MPI_Gather(sendbuf, sendcnt, MPI_INT,recvbuf,recvcnt,MPI_INT, source, MPI_COMM_WORLD);
        MPI_Gather(&localdata, 1, MPI_INT, dataset, 1, MPI_INT, root, MPI_COMM_WORLD);

        //Root shows results
        if (rank == root)
        {
           printf("[Process %d]: Dataset updated: \n", rank);
           for (i = 0; i < size; ++i)
           {
                printf("%d ",dataset[i]);
           }
           printf("\n");
        }

        MPI_Finalize();
        return 0;
}