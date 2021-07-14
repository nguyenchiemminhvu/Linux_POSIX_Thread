#pragma once

#ifndef __SAMPLE_CONDVAR_H__
#define __SAMPLE_CONDVAR_H__

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>

#define MIN_DEC -0xFFFFFFF
#define MAX_INC 0xFFFFFFF

pthread_mutex_t mutex_inc_dec;
pthread_mutex_t mutex_view;
pthread_cond_t cond_increase;
pthread_cond_t cond_decrease;
pthread_cond_t cond_view;

extern int global_data;

void * IncreaseGlobalData(void * arg)
{
    pthread_mutex_lock(&mutex_inc_dec);
    while (true)
    {
        while (global_data >= MAX_INC)
        {
            pthread_cond_wait(&cond_increase, &mutex_inc_dec);
        }

        global_data++;

        if (global_data >= MAX_INC)
        {
            pthread_cond_signal(&cond_decrease);
        }
    }
    pthread_mutex_unlock(&mutex_inc_dec);

    pthread_exit((void*)0);
}

void * DecreaseGlobalData(void * arg)
{
    pthread_mutex_lock(&mutex_inc_dec);
    while (true)
    {
        while (global_data <= MIN_DEC)
        {
            pthread_cond_wait(&cond_decrease, &mutex_inc_dec);
        }

        global_data--;

        if (global_data <= MIN_DEC)
        {
            pthread_cond_signal(&cond_increase);
        }
    }
    pthread_mutex_unlock(&mutex_inc_dec);

    pthread_exit((void*)0);
}

void * ViewGlobalData(void * arg)
{
    struct timespec to;
    clock_gettime(CLOCK_REALTIME, &to);
    to.tv_sec += 3;

    pthread_mutex_lock(&mutex_view);
    pthread_cond_timedwait(&cond_view, &mutex_view, &to);

    while (true)
    {
        printf("%d\n", global_data);
    }

    pthread_mutex_unlock(&mutex_view);

    pthread_exit((void*)0);
}

void SampleCondVar()
{
    pthread_cond_init(&cond_view, NULL);
    pthread_cond_init(&cond_increase, NULL);
    pthread_cond_init(&cond_decrease, NULL);

    pthread_mutex_init(&mutex_view, NULL);
    pthread_mutex_init(&mutex_inc_dec, NULL);

    pthread_t inc, dec, view;
    pthread_create(&inc, NULL, IncreaseGlobalData, NULL);
    pthread_create(&dec, NULL, DecreaseGlobalData, NULL);
    pthread_create(&view, NULL, ViewGlobalData, NULL);

    pthread_join(inc, NULL);
    pthread_join(dec, NULL);
    pthread_join(view, NULL);
}

#endif // __SAMPLE_CONDVAR_H__