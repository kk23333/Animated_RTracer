//
// Created by KK on 16/9/15.
//

#ifndef RTRACER_KBSPLROT_H
#define RTRACER_KBSPLROT_H

/* this code originates from www.magic-software.com */
/* thanks to Dave Eberly for letting us use this */


/* Kochanek-Bartels tension-continuity-bias spline interpolation adapted
 * to quaternion interpolation.
 */
#include "quat.h"
#include <math.h>
#include <stdlib.h>
typedef struct
{
    double x, y, z;
    double angle;
} Rotation3;


typedef struct
{
    /* sample time */
    double t;

    /* sample rotation axis and angle */
    Rotation3 Rot;

    /* sample parameters for affecting tangential behavior at control point */
    double tension, continuity, bias;
} RotationKey;


void* KB_RotInitialize  (int numKeys, RotationKey* key);
void  KB_RotTerminate   (void* info);
void  KB_RotInterpolate (void* info, double t, Rotation3* Rot);


#endif //RTRACER_KBSPLROT_H
