//
// Created by KK on 16/9/15.
//

#ifndef RTRACER_KBSPLPOS_H
#define RTRACER_KBSPLPOS_H

/* this code originates from www.magic-software.com */
/* thanks to Dave Eberly for letting us use this */


/* Kochanek-Bartels tension-continuity-bias spline interpolation for
 * positional data.
 */
//#include "quat.h"
#include <math.h>
#include <stdlib.h>

#ifndef POINT3
#define POINT3
typedef struct
{
    double x, y, z;
} Point3;
#endif


typedef struct
{
    /* sample time */
    double t;

    /* sample position */
    Point3 P;

    /* sample parameters for affecting tangential behavior at control point */
    double tension, continuity, bias;
}PositionKey;

/* private structures to hide details of polynomials */
typedef struct
{
    /* P(u) = C0 + u*C1 + u^2*C2 + u^3*C3,  0 <= u <= 1 */
    Point3 C0, C1, C2, C3;

    /* sample time interval on which polynomial is valid, tmin <= t <= tmax */
    double tmin, tmax, trange;
}CubicPolynomial;

typedef struct
{
    int numPolys;
    CubicPolynomial* poly;

    /* partial sums of arc length */
    double* length;
    double totalLength;
}SplineInfo;

void* KB_PosInitialize  (int numKeys, PositionKey* key);
void  KB_PosTerminate   (void* info);
void  KB_PosInterpolate0 (void* info, double t, Point3* P);  // F(t)
void  KB_PosInterpolate1 (void* info, double t, Point3* P);  // F'(t)
void  KB_PosInterpolate2 (void* info, double t, Point3* P);  // F"(t)

/* Evaluate position and derivatives by specifying arc length s along the
 * curve.  If L is the total length of the curve, then 0 <= s <= L is
 * required.
*/
void KB_PosInterpolate0_AL (void* info, double s, Point3* P);
void KB_PosInterpolate1_AL (void* info, double s, Point3* P);
void KB_PosInterpolate2_AL (void* info, double s, Point3* P);
double KB_PosLength (void* info, double t);  // tmin <= t <= tmax
double KB_PosTotalLength (void* info);

static void ComputeArcLength (SplineInfo* info);
double Length (CubicPolynomial* poly, double u);




#endif //RTRACER_KBSPLPOS_H
