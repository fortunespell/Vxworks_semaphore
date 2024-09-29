#include <stdio.h>
#include <vxWorks.h>
#include <taskLib.h>
#include <semLib.h>

void task1(), task2();
int tid1, tid2;
char t1Status[20];
char t2Status[20];

SEM_ID semMutex;

void start (void) {
    /* Spawning task1 and task2 from start task */
    tid1 = taskSpawn("tTask1", 101, 0, 2000, (FUNCPTR) task1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    tid2 = taskSpawn("tTask2", 102, 0, 2000, (FUNCPTR) task2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void task1 (void) {
    /* Create a binary semaphore that is initially full.
     * Tasks blocked on semaphore wait in priority order. */
    semMutex = semBCreate (SEM_Q_PRIORITY, SEM_FULL);
    
    semTake(semMutex, WAIT_FOREVER);
    /* Start of critical section */
    taskDelay(10);
    taskStatusString(tid1, t1Status);
    printf("\n\t task1 status in critical section of task1: %s\n", t1Status);
    
    /* Critical region, only accessible by a single task at a time */
    taskStatusString(tid2, t2Status);
    printf("\n\t task2 status in critical section of task1: %s\n", t2Status);
    /* End of critical section */
    semGive(semMutex);
}

void task2 (void) {
    /* task1 trying to enter into task2 critical section */
    semTake(semMutex, WAIT_FOREVER);
    
    taskStatusString(tid2, t2Status);
    printf("\n\t task2 status in critical section after task1 completes: %s\n", t2Status);
    
    /* task2 in critical section after task1 completes */
    semGive(semMutex);
}
