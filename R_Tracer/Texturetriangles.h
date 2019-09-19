//
// Created by KK on 17/4/17.
//

#ifndef RTRACER_TEXTURETRIANGLES_H
#define RTRACER_TEXTURETRIANGLES_H
#include "texture.h"
#include "Meshhitable.h"
class Texturetriangles: public Meshhitable {
public:

    Texture *textureimage = nullptr ;



    Texturetriangles (vector<Triangle *> _t)
    {
        record = _t;
    }

    Vec3 getDiffuse(const Vec3 & p) const;

    Vec3 lambert(HandlingRay *h, const Vec3 &light_color,bool &ift);


    ~Texturetriangles();

};



#endif //RTRACER_TEXTURETRIANGLES_H
