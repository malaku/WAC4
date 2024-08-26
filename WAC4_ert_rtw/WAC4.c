/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: WAC4.c
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

#include "WAC4.h"
#include "rtwtypes.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h> // Add this line for write() and close()
#include <linux/can.h>
#include <linux/can/raw.h>
#include <arpa/inet.h>


#define CAN_INTERFACE "can1" // Adjust this interface name if needed

int openCANSocket() {
    int p;
    struct sockaddr_can addr;
    struct ifreq ifr;

    p = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (p == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    strcpy(ifr.ifr_name, CAN_INTERFACE);
    ioctl(p, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(p, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    return p;
}

void closeCANSocket(int socketDescriptor) {
    close(socketDescriptor);
}

void sendCANMessage(int socketDescriptor, uint32_t messageID, float value) {
    struct can_frame frame;

    frame.can_id = messageID;
    frame.can_id &= CAN_SFF_MASK; // Ensure it's a standard identifier
    frame.can_dlc = sizeof(float);

    // Serialize the float value into network byte order (big-endian)
    memcpy(frame.data, &value, sizeof(float));
    printf("Value sent: %f\n", value);

    if (write(socketDescriptor, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        perror("Error sending CAN message");
    }
}

void receiveCANMessage(int socketDescriptor, int targetID, float *tempvar) {
    struct can_frame frame;

    printf("Listening for CAN messages...\n");

    while (1) {
        ssize_t nbytes = read(socketDescriptor, &frame, sizeof(struct can_frame));
        if (nbytes < 0) {
            perror("read");
            break;
        }

        if ((frame.can_id & CAN_ERR_FLAG) == 0 && (frame.can_id & CAN_RTR_FLAG) == 0 &&
            (frame.can_id & CAN_SFF_MASK) == targetID && frame.can_dlc == sizeof(float)) {
            // Deserialize the float value from network byte order and copy it directly into *tempvar
            memcpy(tempvar, frame.data, sizeof(float));
            printf("Received CAN message with ID %x and float value: %f\n", frame.can_id, *tempvar);
            break;
        }
    }
}

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void MATLABFunction(real_T rtu_delta_f, real_T rtu_vx, real_T rtu_l1,
  real_T rtu_l2, real_T rtu_L, real_T rtu_m, real_T rtu_cs3, real_T rtu_cs2,
  real_T *rty_delta_r);

/*
 * Output and update for atomic system:
 *    '<S2>/MATLAB Function'
 *    '<S3>/MATLAB Function'
 */
static void MATLABFunction(real_T rtu_delta_f, real_T rtu_vx, real_T rtu_l1,
  real_T rtu_l2, real_T rtu_L, real_T rtu_m, real_T rtu_cs3, real_T rtu_cs2,
  real_T *rty_delta_r)
{
  real_T tmp;
  tmp = rtu_vx * rtu_vx;
  *rty_delta_r = (rtu_m * rtu_l1 / (rtu_cs3 * rtu_L) * tmp + -rtu_l2) / (rtu_m *
    rtu_l2 / (rtu_cs2 * rtu_L) * tmp + rtu_l1) * rtu_delta_f;
}

/* Model step function */
void WAC4_step(void)
{
  real_T desiredfw2_tmp;
  real_T rtb_Gain;

  /* MATLAB Function: '<S7>/MATLAB Function4' incorporates:
   *  UnitDelay: '<S7>/Unit Delay'
   */
  rtb_Gain = sin(rtDW.UnitDelay_DSTATE);

  /* Outport: '<Root>/desired fw1' incorporates:
   *  Constant: '<S7>/Constant4'
   *  Constant: '<S7>/Constant5'
   *  MATLAB Function: '<S7>/MATLAB Function4'
   *  UnitDelay: '<S7>/Unit Delay'
   */
  rtY.desiredfw1 = atan(2.0 * rtP.L * rtb_Gain / (2.0 * rtP.L * cos
    (rtDW.UnitDelay_DSTATE) - rtP.Bf * rtb_Gain));

  /* Gain: '<S1>/Gain' incorporates:
   *  Inport: '<Root>/In1'
   */
  rtb_Gain = rtP.Gain_Gain * rtU.Steeringwheelangle;

  /* MATLAB Function: '<S6>/MATLAB Function5' */
  desiredfw2_tmp = sin(rtb_Gain);

  /* Outport: '<Root>/desired fw2' incorporates:
   *  Constant: '<S6>/Constant6'
   *  Constant: '<S6>/Constant7'
   *  MATLAB Function: '<S6>/MATLAB Function5'
   */
  rtY.desiredfw2 = atan(2.0 * rtP.L * desiredfw2_tmp / (2.0 * rtP.L * cos
    (rtb_Gain) + rtP.Bf * desiredfw2_tmp));

  /* MATLAB Function: '<S3>/MATLAB Function' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/Constant1'
   *  Constant: '<S3>/Constant2'
   *  Constant: '<S3>/Constant3'
   *  Constant: '<S3>/Constant4'
   *  Constant: '<S3>/Constant5'
   *  Gain: '<S1>/Gain2'
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/vx'
   */
  MATLABFunction(rtP.Gain2_Gain * rtU.Steeringwheelangle, rtU.ActualVelocity,
                 rtP.l1, rtP.l2, rtP.L, rtP.m, rtP.cs3, rtP.cs2, &rtb_Gain);

  /* MATLAB Function: '<S5>/MATLAB Function' */
  desiredfw2_tmp = sin(rtb_Gain);

  /* Outport: '<Root>/desired rw1' incorporates:
   *  Constant: '<S5>/Constant'
   *  Constant: '<S5>/Constant1'
   *  MATLAB Function: '<S5>/MATLAB Function'
   */
  rtY.desiredrw1 = atan(2.0 * rtP.L * desiredfw2_tmp / (2.0 * rtP.L * cos
    (rtb_Gain) - rtP.Bf * desiredfw2_tmp));

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  Constant: '<S2>/Constant'
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S2>/Constant4'
   *  Constant: '<S2>/Constant5'
   *  Gain: '<S1>/Gain1'
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/vx'
   */
  MATLABFunction(rtP.Gain1_Gain * rtU.Steeringwheelangle, rtU.ActualVelocity,
                 rtP.l1, rtP.l2, rtP.L, rtP.m, rtP.cs3, rtP.cs2, &rtb_Gain);

  /* MATLAB Function: '<S4>/MATLAB Function3' */
  desiredfw2_tmp = sin(rtb_Gain);

  /* Outport: '<Root>/desired rw2' incorporates:
   *  Constant: '<S4>/Constant2'
   *  Constant: '<S4>/Constant3'
   *  MATLAB Function: '<S4>/MATLAB Function3'
   */
  rtY.desiredrw2 = atan(2.0 * rtP.L * desiredfw2_tmp / (2.0 * rtP.L * cos
    (rtb_Gain) + rtP.Bf * desiredfw2_tmp));

  /* Update for UnitDelay: '<S7>/Unit Delay' incorporates:
   *  Gain: '<S1>/Gain3'
   *  Inport: '<Root>/In1'
   */
  rtDW.UnitDelay_DSTATE = rtP.Gain3_Gain * rtU.Steeringwheelangle;
}

/* Model initialize function */
void WAC4_initialize(void)
{
  /* InitializeConditions for UnitDelay: '<S7>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtP.UnitDelay_InitialCondition;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
