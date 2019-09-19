//
// Created by KK on 16/10/5.
//

#ifndef RTRACER_SCENE_H
#define RTRACER_SCENE_H

//#include "animation.h"
//#include "Ray.h"
#include "Meshhitable.h"
#include "Hitablebox.h"
#include "Light.h"
#include <vector>
#include <stack>
//#include "Camera.h"
//#include "AnimatedXform.h"
//#include "StaticXform.h"
class Scene {
public:
    Scene () {};
    double startime,endtime;
    int numoframes;

    vector<Hitable *> hitableList;
    Hitablebox *hitbvh;

    vector<Light *> lightlist;
//    AnimationList *Animation_list;

    double height;
    double width;
    Vec3 backcolor = Vec3(0,0,0);
//    Vec3 view_point;
    Vec3 ambient_light;
    Material *caizhi;
    stack<Xform*> Xformstack;
//    Camera *camera;



    Hitable * closestIntersection2(HandlingRay *h);
    Vec3 shade(RayWithCoef * view, RayWithCoef * view_reflect, RayWithCoef *view_refract, Vec3 &aaaaac);

    ~Scene(){
        for(vector<Hitable *>::iterator it = hitableList.begin();it!=hitableList.end();it++){
            Hitable * h = *it;
            if(h){
                delete h;
                h = 0;
            }
        }
        hitableList.clear();

        for(vector<Light *>::iterator it = lightlist.begin();it!=lightlist.end();it++){
            Light * l = *it;
            if(l){
                delete l;
                l = 0;
            }
        }
        lightlist.clear();

        for(int it = 0;it <Xformstack.size();it++){
            Xform *x = Xformstack.top();
            if(x){
                delete x;
            }
        }


    }

};


#endif //RTRACER_SCENE_H
