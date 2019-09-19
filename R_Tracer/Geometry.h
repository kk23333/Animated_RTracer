//
// Created by KK on 16/9/15.
//

#ifndef RTRACER_GEOMETRY_H
#define RTRACER_GEOMETRY_H

#include "Ray.h"

class Geometry {
public:
    virtual  double theNearestIntersection(Ray & ray) = 0;
    virtual  Vec3 getNormalVec3(const Vec3 & p) = 0;

};


#endif //RTRACER_GEOMETRY_H
