//
// Created by KK on 16/9/15.
//

#ifndef RTRACER_TRIANGLE_H
#define RTRACER_TRIANGLE_H
#include "Geometry.h"

class Triangle: public Geometry{
public:
    Vec3 a ;
    Vec3 b ;
    Vec3 c ;
    bool ihn = false;
    Vec3 norm1 ;
    Vec3 norm2 ;
    Vec3 norm3 ;

    int id;

    Vec2d a_t = {0,0},b_t = {0,0},c_t = {0,0};


    Triangle(const Vec3 & _a, const Vec3 & _b, const Vec3 & _c,const Vec3 & _an, const Vec3 & _bn, const Vec3 & _cn,int tid)
    {

        a = Vec3 (_a);
        b = Vec3 (_b);
        c = Vec3 (_c);

        norm1 = Vec3(_an);
        norm2 = Vec3(_bn);
        norm3 = Vec3(_cn);
               ihn = true;

        id=tid;
    };


    Triangle(const Vec3 & _a, const Vec3 & _b, const Vec3 & _c,int tid):
            a(_a), b(_b), c(_c),id(tid){

    };
    Triangle(Vec3 aa, Vec3 bb,Vec3 cc,Vec3 naa,Vec3 nbb ,Vec3 ncc,Vec2d o, Vec2d oo,  Vec2d ooo, int tid);
    Triangle(Vec3 aa, Vec3 bb,Vec3 cc,Vec2d o, Vec2d oo,  Vec2d ooo, int tid);
    Triangle(){};

    double theNearestIntersection(Ray & ray);
    double _theNearestIntersection(Ray & ray, int test_count = 0);
    Vec3 getNormalVec3(const Vec3 & p);

    Vec3 & operator [] (int i);



};


#endif //RTRACER_TRIANGLE_H
