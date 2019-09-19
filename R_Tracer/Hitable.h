//
// Created by KK on 16/10/4.
//

#ifndef RTRACER_HITABLE_H
#define RTRACER_HITABLE_H

#include "Ray.h"
#include "ContainBox.h"
class StaticXform;
#include <stack>

class AnimatedXform;
class Xform;

struct HandlingRay{
    Ray ray;
    double ray_t;
    Ray normal;
    HandlingRay (const Ray & _r):ray(_r){}
    HandlingRay (HandlingRay * a){
        ray = a->ray;
        ray_t = a->ray_t;
        normal = a->normal;
    }
    HandlingRay &operator = (const HandlingRay & a){
        ray = a.ray;
        ray_t = a.ray_t;
        normal = a.normal;
    }
};

struct Material{
    Vec3 amb;//Ia
    Vec3 diff;//Kd
    Vec3 spec;//Ks
    double Shine;//cosine POWER nshiny
    double T;//refraction_fact
    double N;// index of refraction
    Material(){}
    Material(Vec3 amb_,Vec3 diff_,Vec3 spec_,double Shine_,double T_,double N_){
        amb=amb_;
        diff=diff_;
        spec=spec_;
        Shine=Shine_;
        T=T_;
        N=N_;
    }
};

    class Hitable {
    public:
        Hitable(){};
        ~Hitable(){};
        Material *mtrl = nullptr;
        stack <Xform *> transform;
        ContainBox * box = nullptr;

        virtual double closestIntersection(HandlingRay * h) =0;
        virtual void GetPosition(double ct)=0;
//    virtual double foo(){};
        virtual Vec3 getDiffuse(const Vec3 & p) const;
        Ray reflect(HandlingRay *h);
        Ray refract(HandlingRay *h);

        Vec3 lambert(HandlingRay * h,const Vec3& light_color,bool &it);
        Vec3 lambert2(HandlingRay * h,const Vec3& light_color,bool &it);



    };


#endif //RTRACER_HITABLE_H
