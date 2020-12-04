/* Name: Aryan GD Singh
   Roll No: 2019459 */

#include<pthread.h>
#include<stdio.h>

struct my_semaphore {
   int value;
   pthread_mutex_t wait;   // controls access to semaphore
   pthread_mutex_t mutex;  // protects value
};

void init_semaphore(struct my_semaphore s, int n)   {
      s.value = n;
      pthread_mutex_init(&s.wait, NULL);
      pthread_mutex_lock(&s.wait);
      pthread_mutex_init(&s.mutex, NULL);
   }

void signal(struct my_semaphore s)  {
   pthread_mutex_lock(&s.mutex);
   if(s.value<0)  {
      pthread_mutex_unlock(&s.wait);
   }
   s.value += 1;
   pthread_mutex_unlock(&s.mutex);
}

void wait(struct my_semaphore s) {
   pthread_mutex_lock(&s.mutex);
   s.value -= 1;
   if(s.value<=0) {
      pthread_mutex_unlock(&s.mutex);
      pthread_mutex_lock(&s.wait);
   }
   else  {
      pthread_mutex_unlock(&s.mutex);
   }
}

void signalValue(struct my_semaphore s)   {
   printf("Value of semaphore is %d\n", s.value);
}