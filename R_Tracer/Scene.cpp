//
// Created by KK on 16/10/5.
//

#include "Scene.h"

using namespace std;
//Hitable * Scene::closestIntersection2(HandlingRay * h){
//    double ret_t = -1;
//    Hitable * ret = nullptr;
//    HandlingRay *tmp_h =(HandlingRay *)malloc(sizeof(HandlingRay));
//    *tmp_h = HandlingRay(h);
//    for(int i = 0 ; i < hitableList.size() ; i++){
//        double tmp;
////        Meshhitable *p;
////        p=(Meshhitable*)(hitableList[i]);
//
//        Hitable * p= hitableList[i];
//        tmp = p->closestIntersection( tmp_h);
//        if(tmp != -1 &&  (ret_t == -1 || tmp < ret_t)){
//            ret_t = tmp;
//            ret = hitableList[i];
//          //  free(h);
//            *h = *tmp_h;
//        }
//    }
//    free (tmp_h);
//    return ret;
//}

Hitable * Scene::closestIntersection2(HandlingRay * h){
    double ret_t = -1;
    Hitable * ret = nullptr;
    HandlingRay *tmp_h =(HandlingRay *)malloc(sizeof(HandlingRay));
    *tmp_h = HandlingRay(h);
    for(int i = 0 ; i < hitableList.size() ; i++){
        double tmp;
//        Meshhitable *p;
//        p=(Meshhitable*)(hitableList[i]);

        Hitable * p= hitableList[i];
        tmp = p->closestIntersection( tmp_h);
        if(tmp != -1 &&  (ret_t == -1 || tmp < ret_t)){
            ret_t = tmp;
            ret = hitableList[i];
            //  free(h);
            *h = *tmp_h;
        }
    }
    free (tmp_h);
    return ret;
}
//
//Vec3 random_in_half_sphere() {
//    Vec3 p;
//    do {
//        p = 2.0*Vec3(drand48(),drand48(),drand48()) - Vec3(1,1,1);
//        if (p.y()<0)
//            p.e[1] = -p.y();
//    } while (p.squared_length() >= 1.0);
//    return p;
//}

Vec3 Scene::shade(RayWithCoef * view, RayWithCoef * view_reflect, RayWithCoef* view_refract,Vec3 &am ){
    Vec3 color(0,0,0);
    HandlingRay *view_hr= new HandlingRay(view->first);
    Hitable * target_hit = this->closestIntersection2(view_hr);
    if(target_hit == nullptr){
        view->second *=0;
        return color;
    }
    Vec3 abc = view->second;
    Vec3 def = view_hr->ray.A+view_hr->ray.B*view_hr->ray_t;
//    Vec3 def = view->second/6;
    view_reflect->first = target_hit->reflect(view_hr);
    view_reflect->second = view->second * target_hit->mtrl->spec;
    view_refract->first = target_hit->refract(view_hr);
    view_refract->second = view->second * target_hit->mtrl->T;
    HandlingRay * light_hr = (HandlingRay *)malloc(sizeof(HandlingRay));
//


    bool iftexture = false;
    for(int i = 0; i<lightlist.size(); i++){
        Ray light_ray(lightlist[i]->pos,view_reflect->first.origin() - lightlist[i]->pos);

        *light_hr = HandlingRay(light_ray);
//        Hitable * target_hit2 = closestIntersection2(light_hr);

        Hitable* target_hit2 = closestIntersection2(light_hr);
        if(target_hit2 == nullptr){
            continue;
        }

        if(!isAlmostSame(light_hr->normal.origin(),view_reflect->first.origin())){

            continue;
        }


        view->second *=0;
        color += target_hit2->lambert(light_hr,lightlist[i]->lcolor,iftexture);
//        Ray light_reflect = target_hit2->reflect(light_hr);
//        double phong_s = dot(light_reflect.direction(),-(view->first.B));
//
//        if(phong_s <= 0) continue;
//        phong_s = pow(phong_s, target_hit2->mtrl->Shine);
//        Vec3 hl_color = phong_s * (lightlist[i]->lcolor);
//        hl_color *= target_hit->mtrl->spec;

//        color += hl_color;
//        color /= (light_hr->ray_t)*(light_hr->ray_t);
    }
//    if (color==Vec3(0,0,0)){

//    }


//    view->first= Ray(view_reflect->first.origin(),-light_hr->ray.B);
//    view->second *= target_hit->mtrl->diff;
//    color +=  (target_hit->mtrl->amb);
    color *= abc;
//    color += target_hit->getDiffuse(def)*target_hit->mtrl->amb;
//    view->first= Ray(view_reflect->first.origin(),random_in_half_sphere());
//    view->second *= target_hit->mtrl->diff;
  //  }//
//    if(light_amount){
//        texturecolor /= light_amount;
//        color *=view->second;
//        color += texturecolor; }
//    else{
//        color *= view->second;
//    }

    delete view;
    free(light_hr);
    free(view_hr);
//    return color;
        return color;
}

