#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define ITER 30
void* thread_increment(void* arg);
void* thread_decrement(void* arg);
int x = 0;
sem_t sem_inc_done;

int main() {
    pthread_t tid1, tid2;
    sem_init(&sem_inc_done, 0, 0);

    pthread_create(&tid1, NULL, thread_increment, NULL);
    pthread_create(&tid2, NULL, thread_decrement, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    if (x != 0)
        printf("BOOM! counter=%d\n", x);
    else
        printf("OK counter=%d\n", x);

    sem_destroy(&sem_inc_done);
}

void* thread_increment(void* arg) {
    int i;
    for (i = 0; i < ITER; i++) {
        x = x + 1;
        printf("%lu: %d\n", pthread_self(), x);
    }
    sem_post(&sem_inc_done);
    return NULL;
}

void* thread_decrement(void* arg) {
    sem_wait(&sem_inc_done);
    int i;
    for (i = 0; i < ITER; i++) {
        x = x - 1;
        printf("%lu: %d\n", pthread_self(), x);
    }
    return NULL;
}