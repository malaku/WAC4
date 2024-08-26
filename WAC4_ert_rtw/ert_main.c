/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'WAC4'.
 *
 * Model version                  : 1.63
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Thu Nov  9 17:46:37 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include <stdio.h>
#include <stdlib.h>
#include "WAC4.h"
#include "rtwtypes.h"
#include "limits.h"
#include "linuxinitialize.h"
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h> // Add this line for write() and close()
#include <linux/can.h>
#include <linux/can/raw.h>
#include <arpa/inet.h> 
#define UNUSED(x)                      x = x
#define NAMELEN                        16
#define CAN_INTERFACE "can1"

/* Function prototype declaration*/
int openCANSocket(void);
void closeCANSocket(int socketDescriptor);
void sendCANMessage(int socketDescriptor, uint32_t messageID, float value);
void receiveCANMessage(int socketDescriptor, int targetID, float *tempvar);

void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T stopRequested = false;
volatile boolean_T runModel = true;
sem_t stopSem;
sem_t baserateTaskSem;
pthread_t schedulerThread;
pthread_t baseRateThread;
void *threadJoinStatus;
int terminatingmodel = 0;
void *baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(rtM) == (NULL));
int socketDescriptor = openCANSocket();
    int targetMessageID1 = 0x053;
    int targetMessageID2 = 0x054;
float wheelangle;
float Velocity;
float t = 0;
    uint32_t messageID1 = 0x7F1;
uint32_t messageID2 = 0x7F2;
uint32_t messageID3 = 0x7F3;
uint32_t messageID4 = 0x7F4;

  while (runModel) {
    sem_wait(&baserateTaskSem);
    receiveCANMessage(socketDescriptor,targetMessageID1, &wheelangle);
    receiveCANMessage(socketDescriptor,targetMessageID2, &Velocity);

rtU.Steeringwheelangle = wheelangle;
rtU.ActualVelocity=10;

usleep(150000);


    WAC4_step();
float fw1= rtY.desiredfw1;
float fw2= rtY.desiredfw2;
float rw1= rtY.desiredrw1;
float rw2= rtY.desiredrw2;

sendCANMessage(socketDescriptor,messageID1, fw1);
usleep(100);

sendCANMessage(socketDescriptor,messageID2, fw2);
usleep(100);

sendCANMessage(socketDescriptor,messageID3, rw1);
usleep(100);

sendCANMessage(socketDescriptor,messageID4, rw2);
usleep(100);

t=t+0.01;

printf("%f\n",t);
    /* Get model outputs here */
    stopRequested = !((rtmGetErrorStatus(rtM) == (NULL)));
    runModel = !stopRequested;
  }
closeCANSocket(socketDescriptor);
  runModel = 0;
  terminateTask(arg);
  pthread_exit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(rtM, "stopping the model");
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;

  {
    runModel = 0;
  }

  sem_post(&stopSem);
  return NULL;
}

int main(int argc, char **argv)
{
  rtmSetErrorStatus(rtM, 0);

  /* Initialize model */
  WAC4_initialize();

  /* Call RTOS Initialization function */
  myRTOSInit(0.01, 0);

  /* Wait for stop semaphore */
  sem_wait(&stopSem);

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)

  {
    int i;
    for (i=0; i < MW_NUMBER_TIMER_DRIVEN_TASKS; i++) {
      CHECK_STATUS(sem_destroy(&timerTaskSem[i]), 0, "sem_destroy");
    }
  }

#endif

  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
