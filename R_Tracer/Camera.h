//
// Created by KK on 16/9/2.
//

#ifndef RTRACER_Camera_H
#define RTRACER_Camera_H

#include "math.h"
#include "Ray.h"
#include "AnimatedXform.h"


//Vec3 random_in_unit_disk() {
//    Vec3 p;
//    do {
//        p = 2.0*Vec3(drand48(),drand48(),0) - Vec3(1,1,0);
//    } while (dot(p,p) >= 1.0);
//    return p;
//}

class Camera {
public:
    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vfov,
           double aspect) { // vfov is top to bottom in degrees lens_radius = aperture / 2;
        double theta = vfov * M_PI / 180.0;
        half_height = tan(theta / 2);
        half_width = aspect * half_height;
        origin = lookfrom;
        at = lookat;
        up = vup;
            w = unit_Vector(lookfrom - at);//z'
            u = unit_Vector(cross(vup, w));//x‘
            v = cross(w, u);//y’

            lower_left_corner = origin - half_width * u - half_height * v - w;
            horizontal = 2 * half_width * u;
            vertical = 2 * half_height * v;

//
//
//
//
//            origin = lookfrom;
//
//
//            Vec3 w1 = lookfrom - lookat;
//
//
//            w = unit_Vector(w1);
//
//            u = unit_Vector(cross(vup, w));//x‘
//            v = cross(w, u);//y’


    }

    void GetCameraPosition(double cct, AnimationList *al) {
        Animation *a;

        /* is there an animation called "camera", then use it to animate the camera */
        a = FindAnimation("camera", al);
        if (a) {
            double m[4][4];
            double viewPos[3];

            /* get position of the camera, if any */
            if (a->translations) {

                _GetTranslation(a, cct, viewPos);

            }
               origin=Vec3(viewPos[0],viewPos[1],viewPos[2]);

            /* get view direction and up vector, if any */
            if (a->rotations) {
                /* get matrix (we use only the upper 3x3 matrix to extract dir, and up */
                _GetMatrix(a, cct, m);

                /* the viewer looks along the negative z-axis, with the y-axis up */
                dir[0] = m[0][2];
                dir[1] = m[1][2];
                dir[2] = m[2][2];

                /* the y-axis is up */
                up[0] = m[0][1];
                up[1] = m[1][1];
                up[2] = m[2][1];
//
                w = unit_Vector(dir);//z'
                u = unit_Vector(cross(up, w));//x‘
                v = cross(w, u);//y’
//                w = unit_Vector(dir);//z'
//
//
//                v = unit_Vector(up);//y’
//                u = unit_Vector(cross(up, w));//x‘
                lower_left_corner = origin - w - half_width * u - half_height * v ;
                horizontal = 2 * half_width * u;
                vertical = 2 * half_height * v;



            }
        }
    }



    Ray get_ray(double s, double t) {
//        Vec3 rd =random_in_unit_disk();
//        Vec3 offset = u * rd.x() + v * rd.y();
//        return Ray(corigin , lower_left_corner + s*horizontal + t*vertical - corigin );
        return Ray(origin , lower_left_corner + s*horizontal + t*vertical - origin);
    }

    double half_height;
    double half_width;
//    AnimatedXform * cmr = new AnimatedXform("camera") ;
    Vec3 origin,at,up;
    Vec3 horizontal,vertical;

//    Vec3 corigin,cup;
    Vec3 lower_left_corner;
    Vec3 u, v, w;
    Vec3 dir;

};


#endif //RTRACER_Camera_H
