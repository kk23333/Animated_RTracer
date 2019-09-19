//
// Created by KK on 17/4/17.
//

#include "Texturetriangles.h"


int  read_bit(char c,int   pos)
{
    char   b_mask=0x01;
    b_mask=b_mask <<pos;
    if((c&b_mask)==b_mask)             //字符c和b_mask做位运算如果还是等于b_mask,说明该位为1
        return   1;
    else
        return   0;
}


int bto_d(char c)
{
    char cc = c;
    int  i,de =0;
    for(i=0;i <=7;i++)
    {
        de +=pow(2,i)*(read_bit(cc,i));
    }
    return de;
};

Vec3 Texturetriangles::lambert(HandlingRay *h, const Vec3 &light_color,bool &ift) {
    double theta =dot( h->normal.direction(),(-h->ray.direction()));
    if(theta <0) theta = 0;
//    Vec3 temp = light_color * theta;
////    temp *=getDiffuse(h.normal.origin());
    Vec3 temp =getDiffuse(h->normal.origin());
    ift = true;
    return temp;
}

Vec3 Texturetriangles::getDiffuse(const Vec3 & p) const{
    Vec3 s = p;
    Vec3 pa = current[hitid]->a - s;
    Vec3 pb =  current[hitid]->b - s;
    Vec3 pc = current[hitid]->c -s ;

    Vec3 ab = current[hitid]->b - current[hitid]->a;
    Vec3 ac = current[hitid]->c - current[hitid]->a;
    long double ss = cross(ab,ac).length();
    long double c1 = cross(pb,pc).length()/ss;//a
    long double c2 = cross(pa,pc).length()/ss;//b

//    double zinver = (1/tri.a[2]) *c1 + (1/tri.b[2]) *c2 + (1/tri.c[2])*(1-c1-c2);
//
//    double u_p = (1/zinver)*(1/tri.a[2]) *c1*a_t.first + (1/tri.b[2]) *c2*b_t.first + (1/tri.c[2])*(1-c1-c2*c_t.first);
//    double v_p = (1/zinver)*(1/tri.a[2]) *c1*a_t.second + (1/tri.b[2]) *c2*b_t.second + (1/tri.c[2])*(1-c1-c2*c_t.second);

    long double u_p = c1*record[hitid]->a_t[0] + c2*record[hitid]->b_t[0] + (1-c1-c2)*record[hitid]->c_t[0];
    long double v_p = c1*record[hitid]->a_t[1] + c2*record[hitid]->b_t[1]+ (1-c1-c2)*record[hitid]->c_t[1];
    int aa = labs(u_p);
    int bb =labs(v_p);
    if(u_p<0){
        u_p = 1+u_p + aa;
    }else{
        u_p = u_p - aa;
    }
    if(v_p<0){
        v_p = 1+v_p +bb;
    }else{
        v_p = v_p -bb;
    }
//    Texture *textureimage = viReadPPM(tname);

    int wi = textureimage->mWidth;
    int hi = textureimage->mHeight;
    int wp = labs(u_p*wi);
    int hp = labs(v_p*hi);


    Vec3 a =Vec3((double)bto_d(textureimage->mRGB[3*hp*wi+3*wp])/255,(double)bto_d(textureimage->mRGB[3*hp*wi+3*wp+1])/255,(double)bto_d(textureimage->mRGB[3*hp*wi+3*wp+2])/255);
    return a;
}



Texturetriangles::~Texturetriangles(){


    free (textureimage->mRGB);
    free (textureimage);
}

