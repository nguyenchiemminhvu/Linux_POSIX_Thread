#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#include "sample_mutex.h"
#include "sample_condvar.h"
#include "sample_sema.h"

#define LOG(s) printf("%s\n", (s))
#define ECHO(n) printf("%d\n", (n));

int global_data = 0;
pthread_once_t once_control = PTHREAD_ONCE_INIT;

pthread_attr_t common_attr;

void InitOnce()
{
    global_data++;
}

void * thread_func(void * arg)
{
    pthread_t temp;
    pthread_once(&once_control, InitOnce);

    for (int i = 0; i < 3; i++)
    {
        sleep(1);
    }

    pthread_exit((void*)0);
}

void * detached_func(void * arg)
{
    while (true)
    {
        LOG("daemon service is running...");
        sleep(1);
    }
    pthread_exit((void*)0);
}

int main()
{
    // LOG("Pthread says hello");

    // pthread_t service;
    // pthread_attr_t service_attr;
    // pthread_attr_init(&service_attr);
    // pthread_attr_setdetachstate(&service_attr, PTHREAD_CREATE_DETACHED);
    // pthread_attr_setscope(&service_attr, PTHREAD_SCOPE_PROCESS);
    // pthread_create(&service, &service_attr, detached_func, NULL);
    // pthread_attr_destroy(&service_attr);

    // pthread_attr_init(&common_attr);
    // pthread_attr_setscope(&common_attr, PTHREAD_SCOPE_PROCESS);
    // pthread_attr_setdetachstate(&common_attr, PTHREAD_CREATE_JOINABLE);
    // pthread_t t[3];
    // for (int i = 0; i < 3; i++)
    // {
    //     pthread_create(&t[i], &common_attr, thread_func, (void*)&t[i]);
    // }

    // for (int i = 0; i < 3; i++)
    // {
    //     int scope;
    //     pthread_attr_getscope(&common_attr, &scope);

    //     if (scope == PTHREAD_SCOPE_PROCESS)
    //     {
    //         LOG("PROCESS level");
    //     }
    //     else if (scope == PTHREAD_SCOPE_SYSTEM)
    //     {
    //         LOG("SYSTEM level");
    //     }
    // }

    // pthread_attr_destroy(&common_attr);

    // for (int i = 0; i < 3; i++)
    // {
    //     pthread_join(t[i], NULL);
    // }

    // ECHO(global_data);

    SampleMutex();
    SampleCondVar();
    SampleSema();

    return 0;
}