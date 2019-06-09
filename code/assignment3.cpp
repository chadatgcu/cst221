/*
Chad Weirick
GCU
CST-221

Overview:   This program is my simplest possible way to demonstrate a timer being used to 
            prevent resource starvation.

 */

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

using namespace std;

pthread_t myThreads[100]; // for managing theads.
pthread_mutex_t limitedResourceLock; // for locking the limitedResource integer.
int limitedResource = 0; // this is what the threads will compete to add to in basic ++ fashion.
FILE * outputFile; // for capturing results.

void* finishSomething(){
    char messageArray[512];
    strcpy(messageArray, "manually locking\n");;
    fprintf(outputFile, "%s", messageArray);
    printf("%s", messageArray);
    pthread_mutex_lock(&limitedResourceLock); // do this first to avoid any issues.
    sleep(10); // to exacerbate/make this easier to see hold the lock for a moment.
    limitedResource++;


    strcpy(messageArray, "resource updated.\n");
    fprintf(outputFile, "%s", messageArray);
    printf("%s", messageArray);
    pthread_mutex_unlock(&limitedResourceLock);
    return NULL;
}

void* threadCoreLogic(void*){
    // establish a base clock & counterClock
    clock_t baseClock;
    clock_t counterClock;
    bool counterClockInUse = false;

    // a string is set up to display output to screen and file

    char messageArray[512];

    // check resource

    strcpy(messageArray, "Checking lock\n");;
    fprintf(outputFile, "%s", messageArray);
    printf("%s", messageArray);
    while (!pthread_mutex_trylock(&limitedResourceLock)){
        strcpy(messageArray, "locked\n");;
        fprintf(outputFile, "%s", messageArray);
        printf("%s", messageArray);
        if (counterClock){
            counterClock = clock();
            // wait 10 and try again
            if((clock() - counterClock) > 10){ 
                strcpy(messageArray, "resource starved.  Sleeping\n");;
        
                fprintf(outputFile, "%s", messageArray);
                printf("%s", messageArray);
                sleep(10);
            } else {
            // change counterClock back
            counterClockInUse = false;
                strcpy(messageArray, "waking up.\n");;

    fprintf(outputFile, "%s", messageArray);
    printf("%s", messageArray);
            }
        } else {
            // change counterClock to true and establish baseClock time.
            counterClockInUse = true;
            baseClock = clock();
        }
        
        
    }
    strcpy(messageArray, "not locked\n");;
    fprintf(outputFile, "%s", messageArray);
    printf("%s", messageArray);
    // no more congestion, go ahead and do it.
    finishSomething();
}

// in this program my doSomething is to simply add 1 to limitedResource, if it is free.  
void* doSomething() {
    pthread_t thisThread;
    pthread_create(&thisThread, NULL, threadCoreLogic, NULL);
}
 

void* startTheCompetition(int howManyForks) {
    char messageArray[512];
    /* 
    old code here - just going to manually fork 3 times for now
    for (int i = 0; i < howManyForks; i++){
        fork();
        strcpy(messageArray, "making new fork.\n");;
        fprintf(outputFile, "%s", messageArray);
        printf("%s", messageArray);
    }
    
    
    
    
    
     */

    fork();
    strcpy(messageArray, "making new fork.\n");;
        fprintf(outputFile, "%s", messageArray);
        printf("%s", messageArray);
    fork();
    strcpy(messageArray, "making new fork.\n");;
        fprintf(outputFile, "%s", messageArray);
        printf("%s", messageArray);
    fork();
    strcpy(messageArray, "making new fork.\n");;
        fprintf(outputFile, "%s", messageArray);
        printf("%s", messageArray);
    doSomething();
}

int main (void){
    char messageArray[512];
    // set up outputfile
    outputFile = fopen("results.txt", "w");
    strcpy(messageArray, "Starting.\n");;

    fprintf(outputFile, "%s", messageArray);
    printf("%s", messageArray);
    // this will simply start a process which will launch n# different forks of itself. 
    startTheCompetition(10);
    return 0;
}

