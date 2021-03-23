/**
 * This program multiplies a matrix aa times a vector b to produce a vector c using MPI.
 */

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mat.h"

#define min(x, y) ((x)<(y)?(x):(y))

int main(int argc, char* argv[])
{
    int nrows, ncols;


    int offset;
    double *times;
    double total_times;

    int run_index;
    int nruns;
    int myid, master, numprocs;
    
    double starttime, endtime;
    MPI_Status status;
    int i, j, numsent, sender;
    int anstype, row;

    srand(time(0));

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if (argc > 1) {
        nrows = atoi(argv[1]);
        ncols = nrows;
        // aa = (double*)malloc(sizeof(double) * nrows * ncols);
        // b = (double*)malloc(sizeof(double) * ncols);
        double a[nrows][ncols],b[nrows][ncols],c[nrows][ncols];
        master = 0;
        
        if (myid == master) {
            // Master Code goes here
            //aa = gen_matrix(nrows, ncols);
            for (int i = 0; i<ncols; i++) {
            for (int j = 0; j<ncols; j++) {
                a[i][j]= rand()%10;
                b[i][j]= rand()%10;
            }
            }

            printf("\nMatrix A\n\n");
            for (int i = 0; i<ncols; i++) {
            for (int j = 0; j<ncols; j++) {
                printf("%.0f\t", a[i][j]);
            }
                printf("\n");
            }
            printf("\nMatrix B\n\n");
            for (int i = 0; i<ncols; i++) {
            for (int j = 0; j<ncols; j++) {
                printf("%.0f\t", b[i][j]);
            }
                printf("\n");
            }
            starttime = MPI_Wtime();
            numsent = 0;
            offset = 0; //how we determine which row(s) we sending to which child process
            MPI_Bcast(b, ncols*nrows, MPI_DOUBLE, master, MPI_COMM_WORLD);
            for (i = 0; i < min(numprocs-1, nrows); i++) {
                MPI_Send(&a[numsent][0], ncols, MPI_DOUBLE,i+1,i+1, MPI_COMM_WORLD);
                MPI_Send(&b, ncols*nrows, MPI_DOUBLE,sender,numsent+1, MPI_COMM_WORLD);
                MPI_Send(&offset, 1, MPI_INT, sender, numsent+1, MPI_COMM_WORLD);
                numsent++;
                offset = numsent;
            }
            for (i = 0; i < nrows; i++) {
                MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                MPI_Recv(&c[offset][0], ncols, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, 
                    MPI_COMM_WORLD, &status);
                sender = status.MPI_SOURCE;
                if (numsent < nrows) {
                    MPI_Send(&a[numsent][0], ncols, MPI_DOUBLE,sender,numsent+1, MPI_COMM_WORLD);
                    MPI_Send(&b, ncols*nrows, MPI_DOUBLE,sender,numsent+1, MPI_COMM_WORLD);
                    MPI_Send(&offset, 1, MPI_INT, sender, numsent+1, MPI_COMM_WORLD);
                    numsent++;
                } else {
                    MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
                }
            } 
            endtime = MPI_Wtime();
            printf("Time taken: %f\n",(endtime - starttime));
            printf("\nResult Matrix C = Matrix A * Matrix B:\n\n");
            for (int i = 0; i<ncols; i++) {
              for (int j = 0; j<ncols; j++)
                printf("%.0f\t", c[i][j]);
              printf ("\n");
            }
            printf ("\n");
        } else {
            if (myid <= nrows) {
                while(1) {
                    MPI_Recv(&a, ncols, MPI_DOUBLE, master, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                    MPI_Recv(&b, ncols*nrows, MPI_DOUBLE, master, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                    MPI_Recv(&offset, 1, MPI_INT, master, 1, MPI_COMM_WORLD, &status);
                    if (status.MPI_TAG == 0){
                        break;
                    }
                    row = status.MPI_TAG;
                    for (int k = 0; k<ncols; k++) {
                        c[i][k] = 0.0;
                        for (int j = 0; j<ncols; j++)
                            c[i][k] = c[i][k] + a[i][j] * b[j][k];
                    }
                    MPI_Send(&offset, 1, MPI_INT, sender, numsent+1, MPI_COMM_WORLD);
                    MPI_Send(&c, ncols, MPI_DOUBLE, master, row, MPI_COMM_WORLD);
                }
            }
          }
        } else {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}
