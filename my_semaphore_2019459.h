/* Name: Aryan GD Singh
   Roll No: 2019459 */

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

struct my_semaphore {
   int value, max;
   pthread_cond_t var;
   pthread_mutex_t mutex;  // protects value
};

void init_semaphore(struct my_semaphore s, int n)   {
      s.value = n;
      s.max = n;
      pthread_mutex_init(&s.mutex, NULL);
      pthread_cond_init(&s.var, NULL);
   }

void signal(struct my_semaphore s)  {
   pthread_mutex_lock(&s.mutex);
   if(s.value==s.max)   {
      return;
   }
   s.value += 1;
   pthread_cond_signal(&s.var);
   pthread_mutex_unlock(&s.mutex);
}

void wait(struct my_semaphore s) {
   pthread_mutex_lock(&s.mutex);
   s.value -= 1;
   while(s.value==0) {
      pthread_cond_wait (&s.var, &s.mutex);
   }
   s.value -= 1;
   pthread_mutex_unlock(&s.mutex);
}

int trywait(struct my_semaphore s) {
   pthread_mutex_lock(&s.mutex);
   if(s.value<=0) {
      return -EAGAIN;
   }
   s.value -= 1;
   pthread_mutex_unlock(&s.mutex);
   return 0;
}

void signalValue(struct my_semaphore s)   {
   printf("Value of semaphore is %d\n", s.value);
}