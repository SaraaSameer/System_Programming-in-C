#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>
#define NUM 10

sem_t Weighting_Luggage;
sem_t Security_Check;
sem_t Boarding_Pass;

void* Customer_Synchronization(void* args)
{
   printf("Passenger %d is in **Weighting Luggage Phase**\n", *(int*) args);
   sem_wait(&Weighting_Luggage);
   sleep(4);    
   sem_post(&Weighting_Luggage);
   
   printf("Passenger %d is in **Luggage Checking Phase**\n", *(int*) args);
   sem_wait(&Security_Check);
   sleep(7);
   sem_post(&Security_Check);
   
   printf("Passenger %d is in **Acquiring Boarding Pass Phase**\n" ,*(int*) args);
   sem_wait(&Boarding_Pass);
   sleep(3);
   sem_post(&Boarding_Pass);
}


int main()
{
    pthread_t th[NUM];
    sem_init(&Weighting_Luggage,0,1);
    sem_init(&Security_Check, 0,1);  
    sem_init(&Boarding_Pass, 0,1);
    
    for ( int i=0; i<NUM; i++)
    {
       int *a = malloc(sizeof(int));
       *a =i;
       pthread_create (&th[i], NULL , &Customer_Synchronization, a);
    }
    for ( int i=0; i<NUM; i++)
    {
       pthread_join (th[i], NULL);
    }
 
}
