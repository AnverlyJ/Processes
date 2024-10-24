#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>


#define MAX_ITERATION 30
#define MAX_SLEEP 10

void  ChildProcess(void){
  int iteration = rand() % MAX_ITERATION + 1;
  int i;
  for (i = 0; i < iteration; i++){
    printf(" “Child Pid: <pid> is going to sleep!”");
    int sleep_time = rand() % MAX_SLEEP +1;
    sleep(sleep_time);
    printf(" “Child Pid: %d<pid> is awake! Where is my parent %d?”", getpid(), getppid());
  }

  exit(0);
}

void  ParentProcess(void){
  int state;
  pid_t prev_pid;

  prev_pid = wait(&state);
  printf("Child Pid: %d has completed\n", prev_pid);

  prev_pid = wait(&state);
  printf("Child Pid: %d has completed\n", prev_pid);
}


int main(void)
{
  pid_t  pid1, pid2;


  pid1 = fork();
  if (pid1 < 0){
    perror("fork failed");
    exit(1);
    }

  if (pid1 == 0) {
    ChildProcess();
  }
  else {

    pid2 = fork();
    if(pid2<0){
      perror("fork failed");
      exit(1);
    }
  if (pid2 == 0){
    ChildProcess();
  }
  else{
    ParentProcess();
  }


     }

    exit(0);
        
}

