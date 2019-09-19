//
// Created by KK on 16/10/20.
//

#ifndef RTRACER_XFORM_H
#define RTRACER_XFORM_H


#include "animation.h"

class Xform {
public:

    double m[4][4];
    bool vis = true;
    Xform(){
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                m[i][j]=(i==j);
    }

    virtual void GetTMatrix(double tm)=0;
    double bl[3] = {1,1,1};
    double xz[4] = {1,0,0,0};
    double wy[3] = {0,0,0};

};


#endif //RTRACER_XFORM_H
