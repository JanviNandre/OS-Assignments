/*
JRN
Assignment 6 : 
Reader-Writer problem 
*/
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>    
#include<pthread.h>
#include <unistd.h>
#include <sys/types.h>

sem_t rd, wrt;    
int rcount = 0;   
FILE *rw;

void *writer(void *w)
{
	  sem_wait(&wrt);   
    //   rw=fopen("op.txt","a");  
      fprintf(rw,"\nData writen by the writer\n\n");     
	  printf("\nData writen by the writer\n\n");
	  sleep(1);
	  sem_post(&wrt);     
    //   fclose(rw);
}


void *reader(void *r)
{
	int reader ;
  	reader = *(int*)r;
  	sem_wait(&rd);    
  	rcount = rcount + 1;  
  	if(rcount == 1)
  	{
  		sem_wait(&wrt);  
  	}
  	sem_post(&rd);
        fprintf(rw,"Data read by the reader %d \n", reader); 
        printf("Data read by the reader %d \n", reader);
        sleep(1);
  	sem_wait(&rd);
  	rcount = rcount - 1;    
  	if(rcount==0)
  	{
  		sem_post(&wrt);   
  	}
  	sem_post(&rd);     
}


int main()
{
	  int i; 
	  pthread_t rtid[10],wtid;    
	  sem_init(&rd,0,1);         
	  sem_init(&wrt,0,1);    
      rw=fopen("op.txt","w+");
      pthread_create(&wtid,NULL,writer,(void *)&i);         
	  for(i=0;i<=10;i++)
	  {
	    	pthread_create(&rtid[i],NULL,reader,(void *)&i);
	  }
      pthread_join(wtid,NULL);
	  for(i=0;i<=10;i++)
	  {
	    	pthread_join(rtid[i],NULL);
	  }
      fclose(rw);
	  return 0;
}

/*
Output:
$ gcc RW.c -pthread -o RW.out
$ ./RW.out
Data read by the reader 1 
Data read by the reader 3 
Data read by the reader 3 
Data read by the reader 7 
Data read by the reader 7 
Data read by the reader 7 
Data read by the reader 7 
Data read by the reader 8 
Data read by the reader 9 
Data read by the reader 10 
Data read by the reader 11 

Data writen by the writer

*/