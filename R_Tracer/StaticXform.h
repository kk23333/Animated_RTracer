//
// Created by KK on 16/10/22.
//

#ifndef RTRACER_STATICXFORM_H
#define RTRACER_STATICXFORM_H

#include "Xform.h"
#include "quat.h"
#include "kbsplrot.h"
class StaticXform:public Xform {
public:
    StaticXform(double s[3],double r[4],double t[3]);
    void GetTMatrix(double tm){};
//    double bl[3];
//    double xz[4];
//    double wy[3];
};


#endif //RTRACER_STATICXFORM_H
