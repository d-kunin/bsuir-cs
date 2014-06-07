//
//  main.c
//  Pthreading
//
//  Created by Dzmitry Kunin on 07.06.14.
//  Copyright (c) 2014 BSUIR. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t mutex     = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  condition = PTHREAD_COND_INITIALIZER;

static int isThreadsSpawned = 0;

void * threadRoutine(void* args)
{
    int i;
    i = *(int*)args;
    
    pthread_mutex_lock(&mutex);
    while (!isThreadsSpawned) {
        pthread_cond_wait(&condition, &mutex);
    }
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&condition);
    
    printf("Thread %d is running\n", i);
    
    return NULL;
}

int main(int argc, const char * argv[])
{
    const int numberOfThreads = 10;
    int i;
    
    pthread_t threadsIds[numberOfThreads];
    
    pthread_mutex_lock(&mutex);
    
    int status;
    for (i = 0; i < numberOfThreads; ++i) {
        status = pthread_create(&threadsIds[i], NULL, threadRoutine, &i);
        if (status !=0) {
            printf("Cant create thread %d\n", i);
            pthread_mutex_unlock(&mutex);
            exit(-1);
        } else {
            printf("Created thread %d\n", i);
        }
    }
    
    
    pthread_mutex_unlock(&mutex);
    isThreadsSpawned = 1;
    pthread_cond_signal(&condition);
    
    
    for (i = 0; i < numberOfThreads; ++i) {
        pthread_join(threadsIds[i], NULL);
    }
    
    printf("Done\n");
    return 0;
}

