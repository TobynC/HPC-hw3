#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

int** initialize_matrix(char**);

int main(int argc, char **argv)
{
    int n_cpus, rank;
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_cpus);
    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    //read command line arguments
    if (argc < 2 || argv[1][0] != '-')
    {
        printf("Invalid arguments.");
        return 0;
    }
    initialize_matrix(argv);
    
    MPI_Finalize();
}

int** initialize_matrix(char** argv){
    if (!strcmp(argv[1], "-f"))
    {
        //create matrix from file
    }
    else if (!strcmp(argv[1], "-r"))
    {
        //create matrix of random numbers
    }
    else if (!strcmp(argv[1], "-d"))
    {
        //create diagonal matrix of row indices
    }
    else
    {
        printf("Invalid flag: %s.\n", argv[1]);
        exit(0);
    }
}