#include<sys/shm.h>
/*
JRN
Assignment 7 : Server.c
Inter-process Communication using Shared Memory using System V. Application to demonstrate: Client and Server Programs in which server process creates a shared memory segment and writes the message to the shared memory segment. Client process reads the message from the shared memory segment and displays it to the screen.
*/

#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define data_not_filled -1
#define data_filled 0
#define data_read_client 1 


typedef struct data {
    int status; 
    char buff [100]; 
}data1;
    
    
int main ()
{
    int shm_id, ret_val, i=0;
    key_t key; 
    char ch;
    data1 *shm_ptr;
    data1 *s;

    key=ftok(".",'A');

    shm_id=shmget (key, sizeof (data1), IPC_CREAT | 0666) ;

    if (shm_id<0)
    {
        printf("\n shmget error");
        exit(-1);
    }
    else
    {
        printf("\n Shared memory created"); 
        printf("\n Shared memory id is =%d", shm_id);
    }
    system("ipcs -m"); 

    shm_ptr=(data1 *) shmat (shm_id,0,0);
    system("ipcs -m"); 

    if ((int) shm_ptr==-1)
    {
        printf("\n Error for shmat"); 
        exit(-1);
    }
    

    shm_ptr->status=data_not_filled; 
    printf("\n Enter data\n"); 
    ch=getchar(); 
    while (ch!='#')
    {
        shm_ptr->buff[i]=ch; 
        i++;
        ch=getchar();
    }
    
    shm_ptr->buff[i]='\0'; 
    shm_ptr->status=data_filled;

    while (shm_ptr->status != data_read_client)
    {
        printf("\n Server waiting for termination");
        sleep(1);
    }

    ret_val=shmdt( (void *) shm_ptr);
    if (ret_val==0)
    {
        printf("\n shared memory detached");
    }
    else
    {
        printf("\n shmdt error");
    }

    if (shmctl (shm_id, IPC_RMID, 0) < 0)
    {
        printf("shmctl error");
        exit(0);
    }
    return 0;
}

/*
Output : 
$ gcc server.c -o s.out
$ ./s.out

Shared memory created

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x41c10100 0          runner     666        104        0                       


------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x41c10100 0          runner     666        104        1                       

 Shared memory id is =0
 Enter data
Hello World
Java
Cpp
Python#

 Server waiting for termination
 shared memory detached
*/