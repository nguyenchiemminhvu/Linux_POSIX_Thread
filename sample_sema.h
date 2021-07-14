#pragma once

#ifndef __SAMPLE_SEMA_H__
#define __SAMPLE_SEMA_H__

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_common;

extern int global_data;

void * try_sem(void * arg)
{
    sem_wait(&sem_common);
    printf("%d\n", (int)pthread_self());

    sleep(3);

    sem_post(&sem_common);
}

void SampleSema()
{
    sem_init(&sem_common, 0, 0);

    pthread_t t[3];
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&t[i], NULL, try_sem, NULL);
    }

    char c = getchar();
    sem_post(&sem_common);

    for (int i = 0; i < 3; i++)
    {
        pthread_join(t[i], NULL);
    }
}

#endif // __SAMPLE_SEMA_H__