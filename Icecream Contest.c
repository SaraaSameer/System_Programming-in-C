#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include <time.h>
#define NUM 3       //Thread Numbers

sem_t semaphore;
int numOfIcecreams = 5;   //Number of ice-creams available in the contest

void *ice_cream(void* args)
{

   while(numOfIcecreams >0)
   {
      printf("Person %d waiting to get an icecream\n", *(int*) args);
      sem_wait(&semaphore);
      if( numOfIcecreams <= 0)
      {
        printf("Person %d didn't get ice-cream, ALL ICE-CREAMS ARE FINISHED\n \t\tContest Over!!!\n", *(int *) args);
        sem_post(&semaphore); //Release lock, so other contestants also get notified
        return NULL;
      }
      printf("Person %d got Ice-cream, wait till he finishes his ice-cream\n", *(int*)args);
      numOfIcecreams --;
      sleep(rand()%5 + *(int*) args);
      sem_post(&semaphore);
      printf("Person %d finished his ice-cream\n", *(int *)args);
      printf("CURRENT STATUS: %d Ice-creams Left int the contest\n\n", numOfIcecreams);
     
   }
   return NULL;
}

int main()
{
    pthread_t th[NUM];
    srand(time(NULL));
    sem_init(&semaphore,0,1);  //Only one person can get ice-cream at a time
    for ( int i=0; i<NUM; i++)
    {
       int *a = malloc(sizeof(int));
       *a =i;
       pthread_create (&th[i], NULL , &ice_cream, a);
    }
    for ( int i=0; i<NUM; i++)
    {
       pthread_join (th[i], NULL);
    }

}
