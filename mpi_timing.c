#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include<sys/wait.h>
#include<unistd.h>


int main(int argc, char **argv)
{
  struct timeval t0,t1;
  pid_t child_pid;
  int child_status;
  char* args[8] = {"mpiexec", "-f", "~/hosts", "-n", "4", "./test_mpi2"};
  if (argc > 1) {
    args[6] = atoi(argv[1]);
    args[7] = NULL;
  }
  pid_t cpid;
    if (fork()== 0){
        gettimeofday(&t0, 0);
        execvp(args[5], args);
        gettimeofday(&t1, 0);
        long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
        printf("%ld ms.\n", elapsed);
    } else {
        cpid = wait(NULL);
    }
        
}