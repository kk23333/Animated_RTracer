//
// Created by KK on 16/10/5.
//

#ifndef RTRACER_LIGHT_H
#define RTRACER_LIGHT_H

#include "Vec3.h"
class Light{
public:
    Vec3 pos;
    Vec3 lcolor;

    Light(const Vec3 &_p,const Vec3 &_c):
            pos(_p),lcolor(_c){}
};
#endif //RTRACER_LIGHT_H
