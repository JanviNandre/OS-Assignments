#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t child_pid, t_pid;
    int len, temp, status;
    int arr[30] ;
    if (argc > 1)                                           //conversion from string to int
    {                          
        len = argc - 1;                          
        for (int i = 0; i < len; i++){
            arr[i] = atoi(argv[i + 1]);     
        } 
    }
    else{
        printf("\nEnter the size of array : ");
        scanf("%d", &len);
        printf("\nEnter the %d array elements : ", len);
        for(int i=0; i<len; i++){
            scanf("%d", &arr[i]);
        }
    }
  

    child_pid = fork();

    if(child_pid == 0){
        sleep(1);
        printf("\n\nThis is Child process ID is %d ", getpid());
        printf("\nMy parent process ID is %d ", getppid());
        printf("\nGiven Array : ");
        for (int i = 0; i < len; i++){
            printf("%d, ", arr[i]);
        }
        for(int i=0; i<len; i++){
            for(int j=0; j<len-i-1; j++){
                if(arr[j] < arr[j+1]){
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
        printf("\nSorted Array : ");
        for(int i=0; i<len; i++){
            printf("%d, ", arr[i]);
        }
        printf("\n\n");
        system("ps");
    }
    else{
        sleep(1);
        //t_pid = wait(&status);
        printf("\n\nThis is Parent process ID is %d", getpid());
        printf("\nMy Child proces ID is %d", child_pid);
        printf("\nMy Parent process ID is %d", getppid());
        printf("\nGiven Array : ");
        for (int i = 0; i < len; i++){
            printf("%d, ", arr[i]);
        }
        for(int i=0; i<len; i++){
            for(int j=0; j<len-i-1; j++){
                if(arr[j] > arr[j+1]){
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
        printf("\nSorted Array : ");
        for(int i=0; i<len; i++){
            printf("%d, ", arr[i]);
        }
        printf("\n\n");
        system("ps");
    }
    return 0;
}
/*
Zombie State
janvi-nandre@ubuntu:~/Desktop$ gcc OS1.c -o OS1.out
janvi-nandre@ubuntu:~/Desktop$ ./OS1.out 55 33 1 88 33 10

This is Child process ID is 5901 
My parent process ID is 5900 
Given Array : 55, 33, 1, 88, 33, 10, 
Sorted Array : 88, 55, 33, 33, 10, 1, 

This is Parent process ID is 5900
My Child proces ID is 5901
My Parent process ID is 3677
Given Array : 55, 33, 1, 88, 33, 10, 
Sorted Array : 1, 10, 33, 33, 55, 88, 

    PID TTY          TIME CMD
   3677 pts/0    00:00:00 bash
   5900 pts/0    00:00:00 OS1.out
   5901 pts/0    00:00:00 OS1.out
   5902 pts/0    00:00:00 sh
   5903 pts/0    00:00:00 sh
   5904 pts/0    00:00:00 ps
   5905 pts/0    00:00:00 ps
    PID TTY          TIME CMD
   3677 pts/0    00:00:00 bash
   5900 pts/0    00:00:00 OS1.out
   5901 pts/0    00:00:00 OS1.out <defunct>
   5903 pts/0    00:00:00 sh
   5904 pts/0    00:00:00 ps

*/


/*
Orphan State
janvi-nandre@ubuntu:~/Desktop$ ./OS1.out 55 33 1 88 33 10
This is Parent process ID is 5837
My Child proces ID is 5838
My Parent process ID is 3677
Given Array : 55, 33, 1, 88, 33, 10, 
Sorted Array : 1, 10, 33, 33, 55, 88, 

    PID TTY          TIME CMD
   3677 pts/0    00:00:00 bash
   5837 pts/0    00:00:00 OS1.out
   5838 pts/0    00:00:00 OS1.out
   5839 pts/0    00:00:00 sh
   5840 pts/0    00:00:00 ps

This is Child process ID is 5838 
My parent process ID is 1430 
Given Array : 55, 33, 1, 88, 33, 10, 
Sorted Array : 88, 55, 33, 33, 10, 1, 

    PID TTY          TIME CMD
   3677 pts/0    00:00:00 bash
   5838 pts/0    00:00:00 OS1.out
   5841 pts/0    00:00:00 sh
   5842 pts/0    00:00:00 ps

*/
/*Wait Call Process
janvi-nandre@ubuntu:~/Desktop$ ./OS1.out 55 33 1 88 33 10

This is Child process ID is 5706 
My parent process ID is 5705 
Given Array : 55, 33, 1, 88, 33, 10, 
Sorted Array : 88, 55, 33, 33, 10, 1, 

    PID TTY          TIME CMD
   3677 pts/0    00:00:00 bash
   5705 pts/0    00:00:00 OS1.out
   5706 pts/0    00:00:00 OS1.out
   5707 pts/0    00:00:00 sh
   5708 pts/0    00:00:00 ps


This is Parent process ID is 5705
My Child proces ID is 5706
My Parent process ID is 3677
Given Array : 55, 33, 1, 88, 33, 10, 
Sorted Array : 1, 10, 33, 33, 55, 88, 

    PID TTY          TIME CMD
   3677 pts/0    00:00:00 bash
   5705 pts/0    00:00:00 OS1.out
   5709 pts/0    00:00:00 sh
   5710 pts/0    00:00:00 ps

*/