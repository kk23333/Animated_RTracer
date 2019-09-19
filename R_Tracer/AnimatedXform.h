//
// Created by KK on 16/10/22.
//

#ifndef RTRACER_ANIMATEDXFORM_H
#define RTRACER_ANIMATEDXFORM_H


#include <string.h>
#include "Xform.h"
#include "animation.h"
extern AnimationList *Animation_list;

using namespace std;
class AnimatedXform: public Xform{
public:
    AnimatedXform(string name);
    string Xformname;
    Animation *A;
    void GetTMatrix(double tm);
    AnimationList * anil;

};


#endif //RTRACER_ANIMATEDXFORM_H
