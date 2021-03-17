#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define MATSIZE 5
#define aRows MATSIZE            
#define bRows MATSIZE            
#define bCols MATSIZE            
#define MASTER 0               
#define FROM_MASTER 1          
#define FROM_WORKER 2          

int main (int argc, char *argv[])
{
int	numtasks = aRows;              
int taskid;                
int numworkers;            
int source;            
int dest;                 
int mtype;             
int rows;              
int averow;
int extra;
int offset; 
int i, j, k, rc;            
MPI_Status status;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

numworkers = numtasks-1;

double *a = read_matrix_from_file("a.txt");
double *b = read_matrix_from_file("b.txt");
double *c_actual = read_matrix_from_file("c.txt");
double *c = malloc(MATSIZE * MATSIZE * sizeof(double));
c = (double*)malloc(sizeof(double) * 5);
   if (taskid == MASTER)
   {
      /* Measure start time */
      double start = MPI_Wtime();

      averow = aRows/numworkers;
      extra = aRows%numworkers;
      offset = 0;
      mtype = FROM_MASTER;
      for (dest=1; dest<=numworkers; dest++)
      {
         rows = (dest <= extra) ? averow+1 : averow;   	
         MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
         MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
         MPI_Send(&a, rows*bRows, MPI_DOUBLE, dest, mtype,
                   MPI_COMM_WORLD);
         MPI_Send(&b, bRows*bCols, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
         offset = offset + rows;
      }

      mtype = FROM_WORKER;
      for (i=1; i<=numworkers; i++)
      {
         source = i;
         MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
         MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
         MPI_Recv(&c, rows*bCols, MPI_DOUBLE, source, mtype, 
                  MPI_COMM_WORLD, &status);
      }

      double finish = MPI_Wtime();
      printf("Done in %f seconds.\n", finish - start);
   }


   if (taskid > MASTER)
   {
      mtype = FROM_MASTER;
      MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&a, rows*bRows, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&b, bRows*bCols, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);

      for (k=0; k<bCols; k++)
         for (i=0; i<rows; i++)
         {
            c[i * bCols + j] = 0;
            for (j=0; j<bRows; j++)
               c[i * bCols + j] += a[i * aRows + k] * b[k * bCols + j];
         }
      mtype = FROM_WORKER;
      MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
      MPI_Send(&c, rows*bCols, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
   }
   MPI_Finalize();
}