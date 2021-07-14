#pragma once

#ifndef __SAMPLE_MUTEX_H__
#define __SAMPLE_MUTEX_H__

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex_common;
pthread_mutexattr_t mutex_common_attr;
extern int global_data;

void * TryMutex(void * arg)
{
    pthread_mutex_lock(&mutex_common);
    for (int i = 0; i < 1000000; i++)
    {
        global_data++;
    }
    pthread_mutex_unlock(&mutex_common);

    pthread_exit((void*)0);
}

void SampleMutex()
{
    int rc = 0;

    rc = pthread_mutexattr_init(&mutex_common_attr);
    rc = pthread_mutexattr_setpshared(&mutex_common_attr, PTHREAD_PROCESS_PRIVATE);
    rc = pthread_mutexattr_settype(&mutex_common_attr, PTHREAD_MUTEX_DEFAULT);

    pthread_mutex_init(&mutex_common, &mutex_common_attr);
    pthread_mutex_consistent_np(&mutex_common);

    pthread_t t[3];
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&t[i], NULL, TryMutex, NULL);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(t[i], NULL);
    }

    printf("%d\n", global_data);

    rc = pthread_mutexattr_destroy(&mutex_common_attr);
}

#endif // __SAMPLE_MUTEX_H__