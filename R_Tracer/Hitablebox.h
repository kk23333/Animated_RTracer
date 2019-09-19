//
// Created by KK on 17/5/10.
//

#ifndef RTRACER_HITABLEBOX_H
#define RTRACER_HITABLEBOX_H

#include "Hitable.h"
#include <vector>
class Hitablebox {
public:
    static const int MaxElementNumber;
    vector<Hitable*> hitables;
    Vec3 start,size;
    Hitablebox(const vector<Hitable*>_t);

    Hitablebox * children[8];
    void split();
    void fitSize();

    bool isPassing(const Ray & ray);
    double _intersect(double p0,double p, double s);
    void _swap(double & a,double & b){
        double tmp = a;
        a = b;
        b = tmp;
    }
    ~Hitablebox(){
        for(int i = 0;i<8;i++){
            delete children[i];
        }
    }

};


#endif //RTRACER_HITABLEBOX_H
