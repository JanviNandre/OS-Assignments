/*
JRN
Assignment 5 : 
Producer-consumer problem 
*/
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>    
#include<pthread.h>
#include <unistd.h>
#include <sys/types.h>

sem_t f,s,e;             
pthread_mutex_t mutex;    
int arr[5];             


int in=0;
int out=0;

void *producer(void *data)    
{
	int i,n,value;    
	value=(int) data;  
	for(i=0;i<4;i++)  
	{
		sem_wait(&e);     
		sem_wait(&s);     
		
		n=value;          
		arr[in]=n;    
		printf("\nProducer %d produced value %d at buffer location %d",i,arr[in],in);
		in=(in+1)%5;
		
		sem_post(&s);
		sem_post(&f);
		sleep(2);
	}
}

void print*

void *consumer(void *data)   
{
	int i,n,x;
	do
	{
		sem_wait(&f);
		sem_wait(&s);
		
		n=arr[out];    
		printf("\n\tConsumer consumed value %d from buffer location %d",n,out);
		out=(out+1)%5;
		
		sem_post(&s);
		sem_post(&e);
		sleep(2);
		sem_getvalue(&e,&x);
	}while(x!=5);
}

int main()
{
	pthread_t tid[5],tid1;
	int i;
	sem_init(&f,0,0);     
	sem_init(&e,0,5);    
	sem_init(&s,0,1);   
	for(i=0;i<4;i++)
	{
		pthread_create(&tid[i],NULL,producer,(void *) i);
	}
	pthread_create(&tid1,NULL,consumer,NULL);
	for(i=0;i<4;i++)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_join(tid1,NULL);
	return 0;
}

/*
Output : 
$ gcc -pthread PC.c
$ ./a.out

Producer 0 produced value 0 at buffer location 0
    Consumer consumed value 0 from buffer location 0
Producer 0 produced value 3 at buffer location 1
Producer 0 produced value 2 at buffer location 2
Producer 0 produced value 1 at buffer location 3
Producer 1 produced value 0 at buffer location 4
    Consumer consumed value 3 from buffer location 1
Producer 1 produced value 3 at buffer location 0
Producer 1 produced value 2 at buffer location 1
    Consumer consumed value 2 from buffer location 2
Producer 2 produced value 3 at buffer location 2
    Consumer consumed value 1 from buffer location 3
Producer 2 produced value 0 at buffer location 3
    Consumer consumed value 0 from buffer location 4
Producer 2 produced value 2 at buffer location 4
    Consumer consumed value 3 from buffer location 0
Producer 1 produced value 1 at buffer location 0
    Consumer consumed value 2 from buffer location 1
Producer 3 produced value 3 at buffer location 1
    Consumer consumed value 3 from buffer location 2
Producer 3 produced value 0 at buffer location 2
    Consumer consumed value 0 from buffer location 3
Producer 3 produced value 2 at buffer location 3
    Consumer consumed value 2 from buffer location 4
Producer 2 produced value 1 at buffer location 4
    Consumer consumed value 1 from buffer location 0
Producer 3 produced value 1 at buffer location 0
    Consumer consumed value 3 from buffer location 1
    Consumer consumed value 0 from buffer location 2
    Consumer consumed value 2 from buffer location 3
    Consumer consumed value 1 from buffer location 4
    Consumer consumed value 1 from buffer location 0
*/