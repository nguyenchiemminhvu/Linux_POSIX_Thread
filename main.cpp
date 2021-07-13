#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define LOG(s) printf("%s\n", (s))
#define ECHO(n) printf("%d\n", (n));

void * FetchData(void * arg)
{
    int &n = *(int*)arg;
    n = 100;
    pthread_exit((void*)0);
}

int main()
{
    LOG("Pthread says hello");

    int data = 0;

    pthread_t t;
    pthread_create(&t, NULL, FetchData, (void*)&data);
    pthread_join(t, NULL);

    ECHO(data);

    return 0;
}