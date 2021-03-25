#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include<sys/wait.h>
#include<unistd.h>


int main(int argc, char **argv)
{
  int status;
  struct timeval t0,t1;
  pid_t child_pid;
  int child_status;
  char* args[8] = {"mpiexec", "-n", "4","-f", "~/hosts", "./test_mpi2","100",NULL};
  
  pid_t pid;
    if (fork()== 0){
        execvp(args[0], args);
    } else {
        waitpid(pid, &status, 0);
    }
        
    
}