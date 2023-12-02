#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  pid_t pid;
  int status;
  if (argc < 2){
      printf("No command passed\n");
      exit(EXIT_FAILURE);
  }

  switch(pid = fork()) {
  case -1:
          perror("fork error");
          exit(1);
  case 0:
          if(execvp(argv[1], argv+1) == -1){
            perror("exec error");
            exit(EXIT_FAILURE);
          }
  default:
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid error");
                exit(EXIT_FAILURE);
            } else {
                printf("\nCode %d\n", status);
            }
  }
  return 0;
}
