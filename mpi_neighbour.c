/*
* Neighbour exchange
* illustrate the use of MPI_Sendrecv
* 
* a more sophisticate use of  MPI_Sendrecv
* 0<->1   2<->3   4<->5   6<->7 8<->mpi-proc-null  
*
* Compile with mpicc mpi_neighbour.c -o neighbour
* Run with mpirun -n 8 ./neighbour
* 
* Author Liu Tong
* Date Dec 2013
*/


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define xmax 3

int main(int argc, char** argv) {
        int rank,size;
        int *home, *post;
        MPI_Status status;
        const int root=0;

        int up_nbr, down_nbr;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        home = malloc(xmax * sizeof(int));
        post = malloc(xmax * sizeof(int));
        
        int i;
        for (i = 0; i < xmax; ++i)
        {
            home[i] = rank;
            post[i] = 0;
        }
        

        up_nbr = rank + 1;
        if (up_nbr >= size) up_nbr = MPI_PROC_NULL;
        
        down_nbr = rank - 1;
        if (down_nbr < 0) down_nbr = MPI_PROC_NULL;

        if ((rank % 2) == 0) {
        /* exchange up */
        MPI_Sendrecv( home, xmax, MPI_INT, up_nbr, 0, 
                      post, xmax, MPI_INT, up_nbr, 0, 
                      MPI_COMM_WORLD, &status );
        }
        else {
        /* exchange down */
        MPI_Sendrecv( home, xmax, MPI_INT, down_nbr, 0,
                      post, xmax, MPI_INT, down_nbr, 0, 
                      MPI_COMM_WORLD, &status );
        }

        printf("[%d]: After exchange, post is %d\n", rank, post[0]);

        MPI_Finalize();
        return 0;
}