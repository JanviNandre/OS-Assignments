/*
JRN
Assignment 7 : Client.c
Inter-process Communication using Shared Memory using System V. Application to demonstrate: Client and Server Programs in which server process creates a shared memory segment and writes the message to the shared memory segment. Client process reads the message from the shared memory segment and displays it to the screen.
*/

#include<sys/shm.h>
#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define data_not_filled -1
#define data_filled 0
#define data_read_client 1 

typedef struct data
{
    int status;
    char buff[100];
}data1;

int main()
{
    int shm_id, ret_val;
    key_t key;
    data1 *shm_ptr;
    data1 *s;

    key=ftok(".",'A');
    shm_id=shmget (key, 0, 0666);

    if (shm_id<0)
    {
        printf ("\n shmget error");
        exit(-1);
    }
    else
    {
        printf ("\n shared memory id is=%d", shm_id);
    }

    shm_ptr=(data1 *) shmat (shm_id,0,0);
    system("ipcs -m"); 

    if ((int) shm_ptr==-1)
    {
        printf ("\n Error for shmat"); 
        exit(-1);
    }
    
    while (shm_ptr->status==data_not_filled) 
    {
        printf("\n Client waiting for message");
        sleep (3);
    }
    printf ("\n Contents recieved by client is::\n");

    printf ("%s", shm_ptr->buff); 
    shm_ptr->status=data_read_client;

    ret_val=shmdt((void *) shm_ptr); 
    if (ret_val==0)
    {
        printf ("\n shared memory detached");
    } 
    else
    {
        printf ("\n shmdt error");
    }

    return 0;
}

/*
$ gcc client.c -o c.out
$ ./c.out

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x41c10100 0          runner     666        104        2                       

 shared memory id is=0
 Client waiting for message
 Client waiting for message
 Contents recieved by client is::
Hello World
Java
Cpp
Python
 shared memory detached
*/