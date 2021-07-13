#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define LOG(s) printf("%s\n", (s))

void * PthreadSaysHello(void * arg)
{
    pthread_exit(NULL);
}

int main()
{
    LOG("Pthread says hello");

    pthread_t t;
    pthread_create(&t, NULL, PthreadSaysHello, NULL);

    return 0;
}