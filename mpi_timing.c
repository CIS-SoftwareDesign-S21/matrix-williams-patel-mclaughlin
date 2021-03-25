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
  char* args[5] = {"mpiexec", "-n", "4","./test_mpi2","10",NULL};
  
  pid_t pid;
//for(int i = 0; i < atoi(argv[1]); i++){
    if (fork()== 0){
            args[4] = "15";
            execvp(args[0], args);
        } else {
            waitpid(pid, &status, 0);
        }
//}
    
        
    
}