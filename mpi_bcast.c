/*
* MPI_Bcast func Example
*
* In this example, root process broadcasts an integer to every process.
*
* Compile: mpicc mpi_bcast.c -o bcast
* Launch: mpirun -n 6 ./bcast
*
* Modified by: Liu Tong
* Date: Dec 2013
* source: http://stackoverflow.com/questions/7864075/using-mpi-bcast-for-mpi-communication
*/


#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv) {

        int rank;
        int data=0;
        const int root=0;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if(rank == root) {
           data = 777;
        }

        printf("[Process %d]: Before Bcast, data is %d\n", rank, data);

        /* everyone calls bcast, data is taken from root and ends up in everyone's data */
        MPI_Bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);

        printf("[Process %d]: After Bcast, data is %d\n", rank, data);

        MPI_Finalize();
        return 0;
}