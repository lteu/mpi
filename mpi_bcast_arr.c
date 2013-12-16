/*
* Bcast an array, Example
*
* In this example root process broadcasts an array to every process.
*
* Compile: mpicc mpi_bcast_arr.c -o bcast_arr
* Launch: mpirun -n 6 ./bcast_arr
*
* Modified by: Liu Tong
* Date: Dec 2013
* source: http://stackoverflow.com/questions/7864075/using-mpi-bcast-for-mpi-communication
*/

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char** argv) {

        int rank;
        int *dataset;
        int i, arr_sz = 5;//example
        const int root=0;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        //Initialize empty dataset for everyone
        dataset = malloc(arr_sz*sizeof(int));
        printf("[Process %d]: Before Bcast, dataset: \n", rank);
        for (i = 0; i < arr_sz; ++i)
        {
            dataset[i] = 0;
            printf("%d ", dataset[i]);
        }
        printf("\n");

        //Initialize dataset for broadcast
        if(rank == root) {
            printf("[Process ROOT]: Dataset for bcast: \n",rank);   
            for (i = 0; i < arr_sz; ++i)
            {
                dataset[i] = i+1;
                printf("%d ", dataset[i]);
            }
            printf("\n");
        }


        //MPI_Bcast(&msg, count, MPI_INT, source, MPI_COMM_WORLD);
        MPI_Bcast(dataset, arr_sz, MPI_INT, root, MPI_COMM_WORLD);

        //Print bcast result
        printf("[Process %d]: After Bcast, dataset: \n", rank);
        for (i = 0; i < arr_sz; ++i)
        {
            printf("%d ", dataset[i]);
        }
        printf("\n");

        MPI_Finalize();
        return 0;
}