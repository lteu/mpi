/*
* MPI_Scatterv func Example
*
* In this example each process
* receives a sub segment of an array
*
* Launch with ONLY 4 processes
*
* compile: mpicc mpi_scatterv.c -o scatterv 
* launch: mpirun -n 4 ./scatterv 
*
* modified by Liu Tong
* Dec 2013
* source: http://www.sci.hkbu.edu.hk/tdgc/tutorial/ParallelProgrammingWithMPI/examples/scatterv.c 
*/


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
void main(int argv,char** argc)
{
    int size,rank;
    int stride=10; //avoid overlay
    int localdata[10], *dataset, *sendcnts, *displs; 
    int i;
    const int root = 0;

    MPI_Init(&argv, &argc); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    //Control input
    if (size != 4) {
        if (rank==root)
        printf("Error! # of processors must be equal to 4. \n" );
        MPI_Finalize();
        exit(0);
    }

    //set rules and prepare dataset
    if (rank==root) {
        dataset = (int *)malloc(size*stride*sizeof(int));
        displs = (int *)malloc(size*sizeof(int)); 
        sendcnts = (int *)malloc(size*sizeof(int)); 

        printf("[Process %d]: Dataset for distribution: \n", rank);
        for (i=0; i<size*stride; i++){ 
                dataset[i]=i+1;
                printf("%d ", dataset[i]);
        }
        printf("\n");

        for (i=0; i<size; i++) 
        { 
            displs[i] = i*stride; //try also 2+i*stride to see the difference
            sendcnts[i] = i+4; 
        }
    }

    //local preparation
    for (i=0; i<10; i++) 
        localdata[i]=0;

    //MPI_Scatterv(void *sendbuf,int *sendcnts,int *displs,MPI_Datatype sendtype
    // ,void *recvbuf,int recvcnt,MPI_Datatype recvtype,int root, MPI_Comm comm)
    MPI_Scatterv(dataset,sendcnts,displs,MPI_INT,localdata,10,MPI_INT,root,MPI_COMM_WORLD);

    //show results
    printf("[Process %d]: localdata[0:9]=",rank);
    for (i=0;i<10;i++)
        printf("%d ",localdata[i]);
    printf("\n");

    MPI_Finalize();
}