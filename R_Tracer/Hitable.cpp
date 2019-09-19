//
// Created by KK on 16/10/4.
//

#include "Hitable.h"
#include <cmath>

Ray Hitable:: reflect(HandlingRay * h) {
    //~

   double cosd =dot(h->ray.B,  h->normal.B);
           if(cosd>0) cosd = -cosd;
    Vec3 delta =cosd * h->normal.B;
    Ray reflt(h->ray.origin()+h->ray.direction()*h->ray_t ,
              h->ray.direction()-2*delta);
 //   cout<<h.ray.origin()+h.ray.direction()*h.ray_t<<endl;
    return reflt;
}


Vec3 Hitable::lambert(HandlingRay *h, const Vec3 &light_color,bool &ift) {
    double theta =dot( h->normal.direction(),(-h->ray.direction()));
    if(theta <0) theta = -theta;
//    if(theta <0) theta = 0;
    Vec3 temp = light_color * theta;
    temp *=getDiffuse(h->normal.origin());
    ift = false;
    return temp;
}





Vec3 Hitable::getDiffuse(const Vec3 & p) const{

    return mtrl->diff;


}


Ray Hitable::refract(HandlingRay * h){
    double t = (ALMOST_ZERO(h->ray.N - 1.0)?(1.0 /this ->mtrl->N):this ->mtrl->N);
    double cos_theta = dot(h->ray.direction(),h->normal.direction());
    Vec3 law_dir = (cos_theta < 0 ? h->normal.direction():-h->normal.direction());
    double cos_theta_sqr = pow(cos_theta,2);
   double cos_theta2_sqr = 1 - t * t * (1 - cos_theta_sqr);
    //double cos_theta2_sqr = t* t  - t * t * (1 - cos_theta_sqr);
    if(cos_theta2_sqr < 0) return h->ray;
    Vec3 dir = t * h->ray.direction() +
            (t*dot (law_dir,-h->ray.direction())- sqrt(cos_theta2_sqr))* law_dir;
    Ray refr(h->normal.origin(), dir);
    if(ALMOST_ZERO(h->ray.N - 1.0)) refr.N = this->mtrl->N;
    else refr.N = 1.0;
    return refr;
//    double t = (h->ray.N/this ->mtrl->N);
//    double cos_theta = dot(h->ray.direction(),h->normal.direction());
//    Vec3 law_dir = (cos_theta < 0 ? h->normal.direction():-h->normal.direction());
//    double cos_theta_sqr = pow(cos_theta,2);
//    double cos_theta2_sqr = 1 - t * t * (1 - cos_theta_sqr);
//    if(cos_theta2_sqr < 0) return h->ray;
//    Vec3 dir = -t * h->ray.direction() +
//            (t*dot (law_dir,h->ray.direction())- sqrt(cos_theta2_sqr))* law_dir;
//    Ray refr(h->normal.origin(), dir);
//    if(ALMOST_ZERO(h->ray.N - 1.0)) refr.N = this->mtrl->N;
//    else refr.N = 1.0;
//  //  refr.N = this->mtrl->N;
//    return refr;

}