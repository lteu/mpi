/*
* MPI_Scan func Example
* An example of prefix sum 
*
* Compile: mpicc mpi_scan.c -o scan
* Launch: mpirun -n 5 scan
*
* Author: Liu Tong
* Date: Dec 2013
*/


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
        int rank,size;
        int *dataset, localdata, localrecv;
        const int root=0;        

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        //Prepare local data
        localdata = rank;
        printf("[Process %d]: has local data %d\n", rank, localdata);

        //MPI_Scan(sendbuf,recvbuf, count, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        MPI_Scan(&localdata,&localrecv, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

        //Just be a little in order
        MPI_Barrier(MPI_COMM_WORLD);

        printf("[Process %d]: has received data: %d \n", rank,localrecv);

        MPI_Finalize();
        return 0;
}