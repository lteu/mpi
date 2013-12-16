/* 
* MPI_Sendrecv func Example
* 
* In this example process 0 and process 1 exchange an integer  
*
* Launch with ONLY 2 processes.
*
* Compile with mpicc mpi_sendrecv.c -o sendrecv
* Run with mpirun -n 2 ./sendrecv
* 
* Author Liu Tong
* Date Dec 2013
*/


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
        int rank,size;
        int data, localdata;
        int dest;
        MPI_Status status;
        const int root=0;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        if (size != 2) { //Control input
          if (rank == root)
          printf("Please Launch with ONLY 2 processes  \n");
          MPI_Finalize();
          exit(0);
        }

        data = rank*2+1;//Generate data to send

        printf("[Process %d]: has data %d \n",rank,data);

        dest = (rank == root)? 1 : 0;//determine destination

        //MPI_Sendrecv(void *sendbuf, int sendcount, MPI_Datatype sendtype
        //,int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype,int source, int recvtag, MPI_Comm comm, MPI_Status *status)
        MPI_Sendrecv( &data, 1, MPI_INT, dest, 0, &localdata, 1, MPI_INT, dest, 0, MPI_COMM_WORLD, &status );

        printf("[Process %d]: has received data: %d\n", rank, localdata);

        MPI_Finalize();
        return 0;
}