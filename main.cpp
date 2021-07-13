#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define LOG(s) printf("%s\n", (s))
#define ECHO(n) printf("%d\n", (n));

int global_data = 0;
pthread_once_t once_control = PTHREAD_ONCE_INIT;

void InitOnce()
{
    global_data++;
}

void * thread_func(void * arg)
{
    pthread_t temp;
    pthread_once(&once_control, InitOnce);
    pthread_exit((void*)0);
}

int main()
{
    LOG("Pthread says hello");

    pthread_t t[3];
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&t[i], NULL, thread_func, (void*)&t[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(t[i], NULL);
    }

    ECHO(global_data);

    return 0;
}