#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

//Matt Was here c:
int main(int argc, char **argv)
{
    int n_cpus, rank;
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_cpus);
    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);



    MPI_Finalize();
}