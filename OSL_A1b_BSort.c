#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/wait.h>

int main(int argc, char *argv[])

{
    pid_t child_pid, t_pid;
    int status;
    char* temp;
    char *args[argc-1];

    for(int i=0; i<argc-1; i++){
        args[i] = argv[i+1];
    }
    for(int i=0; i<argc-1; i++){
        for(int j=0; j<argc-i-2; j++){
            if(atoi(args[j]) > atoi(args[j+1])){
                temp = args[j];
                args[j] = args[j+1];
                args[j+1] = temp;
            }
        }
    }
    child_pid = fork();

    if(child_pid == 0){
        // sleep(1);
        printf("\n\nThis is Child process ID is %d ", getpid());
        printf("\nMy parent process ID is %d ", getppid());
        execv(args[0], args);
        // printf("\n\n");
        // system("ps");
        }
    else{
        t_pid = wait(&status);

        printf("\n\nThis is Parent process ID is %d", getpid());
        printf("\nMy Child proces ID is %d", child_pid);
        printf("\nMy Parent process ID is %d", getppid());
    }
    return 0;

}
