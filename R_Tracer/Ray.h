#ifndef RTRACER_RAY_H
#define RTRACER_RAY_H
#include "Vec3.h"
//#include <utility>
using namespace std;

class Ray {
public:
    Ray(const Vec3& a, const Vec3& b){ A=a; B =unit_Vector(b); N=1.0;in = false;}
//    Ray(const Vec3& a, const Vec3& b){ A=a; B =unit_Vector(b); }
    Ray():N(1.0){}

    Vec3 origin() const { return A;}
    Vec3 direction() const {return B;}
 //   Vec3 point_at_parameter(double t) const {return A + t*B;}

    Vec3 A;
    Vec3 B;
    double N;//index of refraction;
    bool in;


};


typedef pair<Ray,Vec3>  RayWithCoef ;
#endif //RAYTRACING_RAY_H
