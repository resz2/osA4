/* Name: Aryan GD Singh
   Roll No: 2019459 */

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include "my_semaphore_2019459.h"

#define NUMBER_OF_PHILOS 5
enum state{THINKING, EATING, HUNGRY};

enum state states[NUMBER_OF_PHILOS];
struct my_semaphore forks[NUMBER_OF_PHILOS];
struct my_semaphore bowls;

void *philosopher(void *num)    {
    int i = *((int*)num);
    int left = i;
    int right = (i+1)%NUMBER_OF_PHILOS;
    while(1)    {
        sleep(1);
        states[i] = HUNGRY;
        if(i==0)    {
            wait(forks[left]);
            wait(forks[right]);
        }
        else    {
            wait(forks[right]);
            wait(forks[left]);
        }
        printf("philosopher %d has forks %d and %d, waiting for bowls\n", i, left, right);
        wait(bowls);
        states[i] = EATING;
        printf("philosopher %d eats using forks %d and %d\n", i, left, right);

        signal(bowls);
        printf("philosopher %d puts down bowls\n", i);
        signal(forks[left]);
        signal(forks[right]);
        printf("philosopher %d puts down forks %d and %d\n", i, left, right);
        sleep(1);
        states[i] = THINKING;
    }
}

int main()  {
    int pvals[NUMBER_OF_PHILOS];
    pthread_t philos[NUMBER_OF_PHILOS];
    init_semaphore(bowls, 1);
    for(int i=0;i<NUMBER_OF_PHILOS;i++) {
        init_semaphore(forks[i], 1);
        pvals[i] = i;
        states[i] = THINKING;
    }
    for(int i=0;i<NUMBER_OF_PHILOS;i++) {
        pthread_create(&philos[i], NULL, philosopher, &pvals[i]);
        printf("philosopher %d is thinking\n", i);
    }
    for(int i=0;i<NUMBER_OF_PHILOS;i++) {
        pthread_join(philos[i], NULL);
    }
    return 0;
}