//
// Created by KK on 16/10/6.
//

#ifndef RTRACER_CONTAINBOX_H
#define RTRACER_CONTAINBOX_H

#include <vector>
#include "Triangle.h"
#include <cstring>
#include <algorithm>
using namespace std;

class ContainBox {
public:
    static const int MaxElementNumber;
    vector<Triangle*> triangles;
    Vec3 start,size;
    ContainBox(const vector<Triangle *>_t);

    ContainBox * children[8];
    void split();
    void fitSize();

    bool isPassing(const Ray & ray);
    double _intersect(double p0,double p, double s);
    void _swap(double & a,double & b){
        double tmp = a;
        a = b;
        b = tmp;
    }
    ~ContainBox(){
        for(int i = 0;i<8;i++){
            delete children[i];
        }
    }
};


#endif //RTRACER_CONTAINBOX_H
