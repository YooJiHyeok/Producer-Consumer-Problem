# Producer-Consumer Problem
## Code

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
## Implementation Result
![PCP_snapshot](https://github.com/YooJiHyeok/OSS-final/blob/main/PCP_snapshot.png)
음수와 30이상의 값이 출력되지 않는 모습을 볼 수 있다. 

## Evaluation
세마포어를 이용해서 구현 했고, 총 10번의 테스트 결과 음수 및 30 이상의 값은 출력되지 않았다.
## Conclusion
직접 Producer-Consumer Problem을 구현 해 보니 초반에는 막막했지만 수업 영상을 다시 보며 따라가보니 구현 할 수 있었고 생각보다 어렵지 않았음을 느꼈다.
