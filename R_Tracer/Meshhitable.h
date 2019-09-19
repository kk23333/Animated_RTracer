//
// Created by KK on 16/10/5.
//

#ifndef RTRACER_MESHOBJECTS_H
#define RTRACER_MESHOBJECTS_H
#include "Hitable.h"
#include <queue>
#include "ContainBox.h"
#include "AnimatedXform.h"
#include "StaticXform.h"
#include <stack>

class Meshhitable : public Hitable{
public:
    int hitid = -1;

    vector<Triangle *> record;
    vector<Triangle *> current;

    Meshhitable(vector<Triangle *> _t)
            {
//                   box =new ContainBox(_t);
                    record = _t;
            }

    Meshhitable();

    double closestIntersection(HandlingRay * h);
    void GetPosition(double ct);

    //Triangle* targt = nullptr;
    ~Meshhitable(){
        delete box;
        for(vector<Triangle *>::iterator it = record.begin();it!=record.end();it++){
            Triangle * t1= *it;
            if(t1){
                delete t1;
                t1 = nullptr;
            }
        }
        record.clear();


        for(vector<Triangle *>::iterator it = current.begin();it!=current.end();it++){
            Triangle * t2 = *it;
            if(t2){
                delete t2;
                t2 = nullptr;
            }
        }
        current.clear();
    }


};


#endif //RTRACER_MESHOBJECTS_H
