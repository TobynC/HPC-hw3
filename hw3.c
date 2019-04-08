#include <math.h>
#include <mpi.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void initialize_matrix(char**, double**, int);
void free_matrix(double**, int);
void print_matrix(double**, int);

int main(int argc, char** argv) {
    int n_cpus, rank;
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_cpus);
    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double start_time = MPI_Wtime();

    //read command line arguments
    if (argc < 3 || argv[1][0] != '-') {
        printf("Invalid arguments.");
        return 0;
    }

    int n = 0, dim = 0;
    if (!strcmp(argv[1], "-f")) {
        FILE* fp;
        fp = fopen(argv[2], "r");
        if (!fp) {
            printf("File not found.");
            exit(0);
        }
        fscanf(fp, "%d", &n);
        fclose(fp);
        printf("n: %d", n);
    }
    if (!n)
        dim = atoi(argv[2]);
    else
        dim = n;

    double** matrix;
    matrix = malloc(dim * sizeof *matrix);

    int i;
    for (i = 0; i < dim; i++) {
        matrix[i] = malloc(dim * sizeof *matrix[i]);
    }
    initialize_matrix(argv, matrix, dim);
    print_matrix(matrix, dim);
    free_matrix(matrix, dim);

    if (!dim) {
        printf("Invalid number for dimensions.\n");
        exit(0);
    }

    printf("\nTotal time: %f\n", MPI_Wtime() - start_time);
    MPI_Finalize();
}

void initialize_matrix(char** argv, double** matrix, int dim) {
    if (!strcmp(argv[1], "-f")) {
        printf("\nENTERED THE REST OF FILE PART\n");
        int n;
        FILE* fp;
        fp = fopen(argv[2], "r");
        if (!fp) {
            printf("File not found.");
            exit(0);
        }
        fscanf(fp, "%d", &n);
        int i, j;
        for (i = 0; i < n; i++) {
            for(j = 0; j < n; j++){                
                fscanf(fp, "%lf", &matrix[i][j]);
            }
        }
        fclose(fp);
    }
    if (!strcmp(argv[1], "-r")) {
        //create matrix of random numbers
        int i, j;
        int const high = 10;
        int const low = 1;
        srand(time(NULL));
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim; j++) {
                matrix[i][j] = ((double)rand() * (high - low)) / (double)RAND_MAX + low;
            }
        }
    }
    if (!strcmp(argv[1], "-d")) {
        //create diagonal matrix of row indices
        int i, j;
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim; j++) {
                if (i == j)
                    matrix[i][j] = ++i;
            }
        }
    }
}

void free_matrix(double** matrix, int dim) {
    int row;
    for (row = 0; row < dim; row++) {
        free(matrix[row]);
    }
    free(matrix);
}

void print_matrix(double** matrix, int dim) {
    int i, j;
    for (i = 0; i < dim; i++) {
        printf("\n");
        for (j = 0; j < dim; j++) {
            printf("%.2f ", matrix[i][j]);
        }
    }
    printf("\n");
}