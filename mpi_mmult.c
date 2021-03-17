//mpiexec -f ~/hosts -n 4 ./test_mpi2 
#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#include <time.h>
#include <sys/time.h>



MPI_Status status;



int main(int argc, char **argv)
{
  int processCount, processId, workerTaskCount, source, dest, rows, offset;

  struct timeval start, stop;


  
  int N = 0;
  



  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &processId);
  MPI_Comm_size(MPI_COMM_WORLD, &processCount);

  workerTaskCount = processCount - 1;
  if (argc > 1) {
    N = atoi(argv[1]);
  }
  if(N % workerTaskCount != 0 || N == 0){
    fprintf(stderr, "Usage mpi_mmult <size>\n");
    MPI_Abort(1);
  }
double a[N][N],b[N][N],c[N][N];

 if (processId == 0) {
	
    srand ( time(NULL) );
    for (int i = 0; i<N; i++) {
      for (int j = 0; j<N; j++) {
        a[i][j]= rand()%10;
        b[i][j]= rand()%10;
      }
    }

   printf("\nMatrix A\n\n");
    for (int i = 0; i<N; i++) {
      for (int j = 0; j<N; j++) {
        printf("%.0f\t", a[i][j]);
      }
	    printf("\n");
    }

    printf("\nMatrix B\n\n");
    for (int i = 0; i<N; i++) {
      for (int j = 0; j<N; j++) {
        printf("%.0f\t", b[i][j]);
      }
	    printf("\n");
    }

    rows = N/workerTaskCount; //number of rows to be sent to the child processes
    offset = 0; //how we determine which row we sending to which child process

    for (dest=1; dest <= workerTaskCount; dest++)
    {
      //Offset, number of rows, the row of A to be computed, and matrix b are sent to a child process
      MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      MPI_Send(&a[offset][0], rows*N, MPI_DOUBLE,dest,1, MPI_COMM_WORLD);
      MPI_Send(&b, N*N, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
      offset = offset + rows; //increment offset so we aren't sending the same rows
    }

    for (int i = 1; i <= workerTaskCount; i++)
    {
      source = i;
      MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      MPI_Recv(&c[offset][0], rows*N, MPI_DOUBLE, source, 2, MPI_COMM_WORLD, &status);
    }

    printf("\nResult Matrix C = Matrix A * Matrix B:\n\n");
    for (int i = 0; i<N; i++) {
      for (int j = 0; j<N; j++)
        printf("%.0f\t", c[i][j]);
      printf ("\n");
    }
    printf ("\n");
  }
 //worker process
  if (processId > 0) {
    source = 0;
    MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&a, rows*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&b, N*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);

    for (int k = 0; k<N; k++) {
      for (int i = 0; i<rows; i++) {
        c[i][k] = 0.0;
        for (int j = 0; j<N; j++)
          c[i][k] = c[i][k] + a[i][j] * b[j][k];
      }
    }

    MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&c, rows*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}