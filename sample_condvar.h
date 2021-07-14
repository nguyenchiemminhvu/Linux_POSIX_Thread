#pragma once

#ifndef __SAMPLE_CONDVAR_H__
#define __SAMPLE_CONDVAR_H__

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <pthread.h>

#define MIN_DEC 0
#define MAX_INC 0xFFFFFFF

pthread_mutex_t mutex_inc_dec;
pthread_cond_t cond_increase;
pthread_cond_t cond_decrease;

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
}

void * ViewGlobalData(void * arg)
{
    while (true)
    {
        printf("%d\n", global_data);
    }
}

void SampleCondVar()
{
    pthread_t inc, dec, view;
    pthread_create(&inc, NULL, IncreaseGlobalData, NULL);
    pthread_create(&dec, NULL, DecreaseGlobalData, NULL);
    pthread_create(&view, NULL, ViewGlobalData, NULL);

    pthread_join(inc, NULL);
    pthread_join(dec, NULL);
    pthread_join(view, NULL);
}

#endif // __SAMPLE_CONDVAR_H__