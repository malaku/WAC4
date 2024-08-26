/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: WAC4.h
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

#ifndef RTW_HEADER_WAC4_h_
#define RTW_HEADER_WAC4_h_
#ifndef WAC4_COMMON_INCLUDES_
#define WAC4_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* WAC4_COMMON_INCLUDES_ */

#include <stddef.h>

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define WAC4_M                         (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<S7>/Unit Delay' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Steeringwheelangle;           /* '<Root>/In1' */
  real_T ActualVelocity;               /* '<Root>/vx' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T desiredfw1;                   /* '<Root>/desired fw1' */
  real_T desiredfw2;                   /* '<Root>/desired fw2' */
  real_T desiredrw1;                   /* '<Root>/desired rw1' */
  real_T desiredrw2;                   /* '<Root>/desired rw2' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  real_T Bf;                           /* Variable: Bf
                                        * Referenced by:
                                        *   '<S4>/Constant2'
                                        *   '<S5>/Constant'
                                        *   '<S6>/Constant6'
                                        *   '<S7>/Constant4'
                                        */
  real_T L;                            /* Variable: L
                                        * Referenced by:
                                        *   '<S2>/Constant2'
                                        *   '<S3>/Constant2'
                                        *   '<S4>/Constant3'
                                        *   '<S5>/Constant1'
                                        *   '<S6>/Constant7'
                                        *   '<S7>/Constant5'
                                        */
  real_T cs2;                          /* Variable: cs2
                                        * Referenced by:
                                        *   '<S2>/Constant5'
                                        *   '<S3>/Constant5'
                                        */
  real_T cs3;                          /* Variable: cs3
                                        * Referenced by:
                                        *   '<S2>/Constant4'
                                        *   '<S3>/Constant4'
                                        */
  real_T l1;                           /* Variable: l1
                                        * Referenced by:
                                        *   '<S2>/Constant'
                                        *   '<S3>/Constant'
                                        */
  real_T l2;                           /* Variable: l2
                                        * Referenced by:
                                        *   '<S2>/Constant1'
                                        *   '<S3>/Constant1'
                                        */
  real_T m;                            /* Variable: m
                                        * Referenced by:
                                        *   '<S2>/Constant3'
                                        *   '<S3>/Constant3'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<S7>/Unit Delay'
                                        */
  real_T Gain_Gain;                    /* Expression: 1/16
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T Gain2_Gain;                   /* Expression: 1/16
                                        * Referenced by: '<S1>/Gain2'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1/16
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T Gain3_Gain;                   /* Expression: 1/16
                                        * Referenced by: '<S1>/Gain3'
                                        */
};

/* Parameters (default storage) */
typedef struct P_ P;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P rtP;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void WAC4_initialize(void);
extern void WAC4_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('MalaksModelSub/WAC4')    - opens subsystem MalaksModelSub/WAC4
 * hilite_system('MalaksModelSub/WAC4/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MalaksModelSub'
 * '<S1>'   : 'MalaksModelSub/WAC4'
 * '<S2>'   : 'MalaksModelSub/WAC4/RWS'
 * '<S3>'   : 'MalaksModelSub/WAC4/RWS1'
 * '<S4>'   : 'MalaksModelSub/WAC4/Subsystem'
 * '<S5>'   : 'MalaksModelSub/WAC4/Subsystem1'
 * '<S6>'   : 'MalaksModelSub/WAC4/Subsystem2'
 * '<S7>'   : 'MalaksModelSub/WAC4/Subsystem3'
 * '<S8>'   : 'MalaksModelSub/WAC4/RWS/MATLAB Function'
 * '<S9>'   : 'MalaksModelSub/WAC4/RWS1/MATLAB Function'
 * '<S10>'  : 'MalaksModelSub/WAC4/Subsystem/MATLAB Function3'
 * '<S11>'  : 'MalaksModelSub/WAC4/Subsystem1/MATLAB Function'
 * '<S12>'  : 'MalaksModelSub/WAC4/Subsystem2/MATLAB Function5'
 * '<S13>'  : 'MalaksModelSub/WAC4/Subsystem3/MATLAB Function4'
 */
#endif                                 /* RTW_HEADER_WAC4_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
