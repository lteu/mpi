/*
 *  An example of using both MPI and OMP
 *
 *  compile with:
 *  mpicc -fopenmp hello.c -o hello
 *
 *  run with:
 *  mpirun -n 2 ./hello 4
 *
 *
 */

#include "mpi.h"
#include <stdio.h>
#include <omp.h>

 void say_hello(int cpu)
{
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    printf("[process: %d]Hello from thread %d of %d\n",cpu, my_rank, thread_count);
}


int main( int argc, char *argv[] )
{
	
    int rank, size;
    MPI_Init( &argc, &argv ); /* no MPI calls before this line */
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    int thr = 2;
    if ( argc == 2 )
	thr = atoi( argv[1] );

    #pragma omp parallel num_threads(thr)
    say_hello(rank);


    MPI_Finalize(); /* no MPI calls after this line */
    return 0;
}
